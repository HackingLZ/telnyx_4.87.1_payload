#!/usr/bin/env python3
"""Extract RC4-encrypted C2 config from the telnyx/TeamPCP Windows implant.

Handles the full extraction chain:
  Outer PE → embedded PNG → pixel steganography → inner DLL → RC4 config

Usage:
    python3 extract_config.py <outer_pe_path>
    python3 extract_config.py --dll <inner_dll_path>
"""

import argparse
import hashlib
import json
import struct
import sys
from pathlib import Path


def rc4(key: bytes, data: bytes) -> bytes:
    S = list(range(256))
    j = 0
    for i in range(256):
        j = (j + S[i] + key[i % len(key)]) % 256
        S[i], S[j] = S[j], S[i]
    i = j = 0
    out = bytearray()
    for byte in data:
        i = (i + 1) % 256
        j = (j + S[i]) % 256
        S[i], S[j] = S[j], S[i]
        out.append(byte ^ S[(S[i] + S[j]) % 256])
    return bytes(out)


def extract_png_from_pe(pe_data: bytes) -> bytes:
    """Extract the embedded PNG from the outer PE's .data section."""
    pe_off = struct.unpack_from("<I", pe_data, 0x3C)[0]
    num_sections = struct.unpack_from("<H", pe_data, pe_off + 6)[0]
    opt_hdr_size = struct.unpack_from("<H", pe_data, pe_off + 20)[0]
    section_start = pe_off + 24 + opt_hdr_size

    for i in range(num_sections):
        off = section_start + i * 40
        name = pe_data[off : off + 8].rstrip(b"\x00")
        va = struct.unpack_from("<I", pe_data, off + 12)[0]
        raw_off = struct.unpack_from("<I", pe_data, off + 20)[0]

        if name == b".data":
            png_va_offset = 0x120  # PNG starts at .data + 0x120
            png_file_offset = raw_off + png_va_offset
            png_size = 0x1F5A5
            return pe_data[png_file_offset : png_file_offset + png_size]

    raise ValueError("Could not find .data section in outer PE")


def extract_shellcode_from_png(png_data: bytes) -> bytes:
    """Extract steganographic shellcode from PNG RGBA pixel channels."""
    try:
        from PIL import Image
    except ImportError:
        print("ERROR: Pillow required. Install: uv add Pillow", file=sys.stderr)
        sys.exit(1)

    import io

    img = Image.open(io.BytesIO(png_data)).convert("RGBA")
    pixels = img.tobytes()

    sc_size = struct.unpack(">I", pixels[0:4])[0]
    extracted = bytearray()

    # Pixel 1: G, B channels
    extracted.append(pixels[5])
    extracted.append(pixels[6])

    # Pixels 2+: R, G, B channels (skip alpha)
    for i in range(2, len(pixels) // 4):
        base = i * 4
        extracted.append(pixels[base])
        if len(extracted) >= sc_size:
            break
        extracted.append(pixels[base + 1])
        if len(extracted) >= sc_size:
            break
        extracted.append(pixels[base + 2])
        if len(extracted) >= sc_size:
            break

    return bytes(extracted[:sc_size])


def extract_inner_dll(shellcode: bytes) -> bytes:
    """Extract the inner DLL from shellcode (starts after 0x3ff-byte loader stub)."""
    pe_offset = 0x3FF
    pe = shellcode[pe_offset:]

    e_lfanew = struct.unpack_from("<I", pe, 0x3C)[0]
    if pe[e_lfanew : e_lfanew + 4] != b"PE\x00\x00":
        raise ValueError(f"Invalid PE signature at offset {pe_offset}")

    return pe


def find_rdata_section(dll_data: bytes) -> tuple[int, int]:
    """Find .rdata section file offset and size in the inner DLL."""
    pe_off = struct.unpack_from("<I", dll_data, 0x3C)[0]
    num_sections = struct.unpack_from("<H", dll_data, pe_off + 6)[0]
    opt_hdr_size = struct.unpack_from("<H", dll_data, pe_off + 20)[0]
    section_start = pe_off + 24 + opt_hdr_size

    for i in range(num_sections):
        off = section_start + i * 40
        name = dll_data[off : off + 8].rstrip(b"\x00")
        raw_size = struct.unpack_from("<I", dll_data, off + 16)[0]
        raw_off = struct.unpack_from("<I", dll_data, off + 20)[0]

        if name == b".rdata":
            return raw_off, raw_size

    raise ValueError("Could not find .rdata section in inner DLL")


def decrypt_config(dll_data: bytes) -> dict:
    """Decrypt and parse the RC4-encrypted C2 config from the inner DLL."""
    rdata_off, _ = find_rdata_section(dll_data)

    # Config format: [LE uint32 size][encrypted_data][16-byte RC4 key]
    total_size = struct.unpack_from("<I", dll_data, rdata_off)[0]
    encrypted = dll_data[rdata_off + 4 : rdata_off + 4 + total_size]
    rc4_key = dll_data[
        rdata_off + 4 + total_size : rdata_off + 4 + total_size + 16
    ]

    decrypted = rc4(rc4_key, encrypted)

    import re

    strings = [s.decode("ascii") for s in re.findall(rb"[\x20-\x7e]{3,}", decrypted)]

    return {
        "rc4_key": rc4_key.hex(),
        "encrypted_size": total_size,
        "decrypted_hex": decrypted.hex(),
        "decrypted_sha256": hashlib.sha256(decrypted).hexdigest(),
        "strings": strings,
        "c2_config": {
            "server": strings[0] if len(strings) > 0 else None,
            "method": strings[1] if len(strings) > 1 else None,
            "uri": strings[2] if len(strings) > 2 else None,
            "header": strings[3] if len(strings) > 3 else None,
            "user_agent": strings[4] if len(strings) > 4 else None,
        },
    }


def main():
    parser = argparse.ArgumentParser(
        description="Extract C2 config from TeamPCP Windows implant"
    )
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("outer_pe", nargs="?", help="Path to outer PE (full chain)")
    group.add_argument("--dll", help="Path to already-extracted inner DLL")
    parser.add_argument(
        "--dump-stages",
        metavar="DIR",
        help="Dump all intermediate stages to directory",
    )
    args = parser.parse_args()

    if args.dll:
        dll_data = Path(args.dll).read_bytes()
        print(f"[*] Loaded inner DLL: {len(dll_data)} bytes", file=sys.stderr)
    else:
        pe_path = Path(args.outer_pe)
        pe_data = pe_path.read_bytes()
        print(
            f"[*] Outer PE: {pe_path.name} ({len(pe_data)} bytes)", file=sys.stderr
        )

        png_data = extract_png_from_pe(pe_data)
        print(f"[*] Embedded PNG: {len(png_data)} bytes", file=sys.stderr)

        shellcode = extract_shellcode_from_png(png_data)
        print(f"[*] Shellcode from pixels: {len(shellcode)} bytes", file=sys.stderr)

        dll_data = extract_inner_dll(shellcode)
        print(f"[*] Inner DLL: {len(dll_data)} bytes", file=sys.stderr)

        if args.dump_stages:
            out = Path(args.dump_stages)
            out.mkdir(parents=True, exist_ok=True)
            (out / "embedded.png").write_bytes(png_data)
            (out / "shellcode.bin").write_bytes(shellcode)
            (out / "reflective_loader.bin").write_bytes(shellcode[:0x3FF])
            (out / "implant.dll").write_bytes(dll_data)
            print(f"[*] Stages dumped to {out}/", file=sys.stderr)

    config = decrypt_config(dll_data)
    print(f"[*] RC4 key: {config['rc4_key']}", file=sys.stderr)
    print(f"[+] Config decrypted successfully\n", file=sys.stderr)
    print(json.dumps(config, indent=2))


if __name__ == "__main__":
    main()
