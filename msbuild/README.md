# Windows PE Implant — `msbuild.exe` (AdaptixC2 Beacon)

Reverse engineering of the Windows PE payload delivered via `hangup.wav` WAV steganography. The implant is a compiled build of the [AdaptixC2](https://github.com/Adaptix-Framework/AdaptixC2) open-source post-exploitation framework with TeamPCP's operator config. The PNG steganography delivery wrapper was added by TeamPCP outside the framework.

**SHA256:** `7290353a3bc2b18e9ea574d3294b09e28edaa6b038285bb101cf09760f187dcd`
**MD5:** `d528effabbd9cd66aaa11bc8777bb110`
**Type:** PE32+ x86-64 (MinGW GCC 13/14-win32), GUI subsystem, stripped
**Framework:** [AdaptixC2](https://github.com/Adaptix-Framework/AdaptixC2) beacon agent
**C2:** `checkmarx[.]zone:8443` via HTTPS POST to `/telemetry/checkmarx.json`

## Files

| File | Description |
|------|-------------|
| `ANALYSIS.md` | Full analysis — framework ID, execution chain, 35-command dispatch table, C2 traffic patterns, IOCs |
| `outer_pe_msbuild_decompiled.c` | Annotated Ghidra decompilation of the outer PE (ntdll unhooking, PNG steganography, process injection into dllhost.exe) |
| `inner_dll_implant_decompiled.c` | Annotated Ghidra decompilation of the AdaptixC2 beacon DLL (C2 comms, command handlers, SOCKS proxy, P2P mesh) |
| `extract_config.py` | Automated extraction: outer PE → PNG → shellcode → inner DLL → RC4 config. Usage: `python3 extract_config.py <pe_path>` |
| `stage1_embedded.png` | Steganographic PNG extracted from .data section (179x179 RGBA, shellcode in pixel channels) |
| `stage4_decrypted_config.bin` | Decrypted RC4 C2 config blob (229 bytes, key: `331ab9c032cf95c89d877ee05b46f8d8`) |
| `stages_manifest.json` | Hashes (MD5, SHA256) and metadata for all extraction stages |

## Execution Chain

```
hangup.wav (WAV stego: base64-decode frames → 8-byte XOR key + ciphertext)
    → msbuild.exe (outer PE, 179,712 bytes) [TeamPCP custom wrapper]
        → Maps clean ntdll.dll, resolves direct syscalls (EDR bypass)
        → Decodes embedded PNG via stb_image
        → Extracts 95,743 bytes of shellcode from RGBA pixels
        → Injects into suspended dllhost.exe via direct syscalls
            → Reflective loader (1,023 bytes) + inner DLL (file.dll, 94,720 bytes)
                → AdaptixC2 beacon — 35 commands, beaconing to checkmarx[.]zone:8443
```

## Stage Hashes

| Stage | SHA256 | Size |
|-------|--------|------|
| Outer PE | `7290353a3bc2b18e9ea574d3294b09e28edaa6b038285bb101cf09760f187dcd` | 179,712 |
| Embedded PNG | `7e270255567866d37ad56e3f06977b695e39530eede74a10a0848ba71560cb45` | 128,421 |
| Shellcode | `b92bd082bbd7d238089b2bb87d9cbf01be1bf8ab7213b67e9d27108e052ef75c` | 95,743 |
| Reflective loader | `26b689749bc57991cbae2aab8ab6cf5acab6c64db4829ba2b1ced6c60d99a7a8` | 1,023 |
| Implant DLL | `dafc1cc5d39bc303562d8587b698b6351e843b77c01764efa8b423a36b88fa6d` | 94,720 |
| Decrypted config | `1fdf1add3776bf91b28bdb2864afa1d24224a89f76f8705297d69bb9b4493cb7` | 229 |
