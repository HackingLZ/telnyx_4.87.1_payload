# Windows PE Payload Analysis — `hangup.wav` / `msbuild.exe`

**Sample:** `7290353a3bc2b18e9ea574d3294b09e28edaa6b038285bb101cf09760f187dcd`
**MD5:** `d528effabbd9cd66aaa11bc8777bb110`
**Type:** PE32+ x86-64 (MinGW GCC 13/14-win32), GUI subsystem, stripped
**Framework:** [AdaptixC2](https://github.com/Adaptix-Framework/AdaptixC2) beacon agent (open-source post-exploitation framework)
**Delivery:** WAV steganography from `hxxp://83[.]142[.]209[.]203:8080/hangup.wav`
**Persistence:** `%APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup\msbuild.exe`

---

## Framework Identification — AdaptixC2

This implant is a **compiled build of the [AdaptixC2](https://github.com/Adaptix-Framework/AdaptixC2) Windows beacon agent** with TeamPCP's operator-specific C2 configuration. The PNG steganography delivery wrapper is not part of AdaptixC2 — it was added by TeamPCP as their staging mechanism.

### Source Code Matches

Every unique fingerprint in the binary maps directly to AdaptixC2 source:

| Binary Artifact | AdaptixC2 Source | File |
|---|---|---|
| `ConnectorHTTP` inherits `Connector` (RTTI) | `class ConnectorHTTP : public Connector` | `ConnectorHTTP.h` |
| Export `_Z11GetVersionsv` | `extern "C" __declspec(dllexport) void CALLBACK GetVersions(...)` | `main.cpp` |
| Inner DLL name `file.dll` | `buildPath = tempDir + "/file.dll"` | `pl_main.go` |
| Default UA `Firefox/20.0 on NT 6.2` | Default User-Agent constant | `pl_main.go` |
| DJB2 hash init=5381, mult=33 | `unsigned long h = 5381; h = ((h << 5) + h) + c` | `crt.cpp` |
| RC4 config `[LE uint32 size][data][16-byte key]` | `RC4Crypt()` output format | `pl_main.go` |
| Build flags `-nostdlib -mwindows -s` | `x86_64-w64-mingw32-g++` with exact flags | `pl_main.go` |
| Char-by-char DLL construction | `HdChrA()` calls for WinINet string building | `ConnectorHTTP.cpp` |
| 20-entry `SYSCALL_API` struct | 20 Nt* function entries | `beacon.h` |
| SSL cert bypass ORing `0x3380` | `SECURITY_FLAG_IGNORE_*` constants | `ConnectorHTTP.cpp` |
| WinINet flags `0x84480200` / `0x84C80200` | RELOAD + NO_CACHE + KEEP_CONNECTION ± SECURE | `ConnectorHTTP.cpp` |

### What's AdaptixC2 vs What's TeamPCP

| Component | Origin |
|---|---|
| Inner DLL (file.dll) — beacon, C2 comms, 35 commands, SOCKS, P2P mesh | AdaptixC2 framework |
| Reflective DLL loader | AdaptixC2 framework |
| Ntdll unhooking + direct syscalls | AdaptixC2 framework |
| C2 config (checkmarx[.]zone, URI, headers) | TeamPCP operator config |
| Outer PE wrapper with PNG steganography | TeamPCP custom staging |
| WAV steganography delivery via hangup.wav | TeamPCP custom delivery |
| Process injection into dllhost.exe | AdaptixC2 (operator-configurable spawn-to process) |

---

## C2 Configuration (RC4-encrypted)

| Field | Value |
|-------|-------|
| **Server** | `checkmarx[.]zone` |
| **Port** | `8443` |
| **Method** | `POST` |
| **URI** | `/telemetry/checkmarx.json` |
| **Custom Header** | `X-Content-ID` |
| **User-Agent** | `Mozilla/5.0 (Windows NT 6.2; rv:20.0) Gecko/20121202 Firefox/20.0` |
| **RC4 Key** | `331ab9c032cf95c89d877ee05b46f8d8` |

The config is stored RC4-encrypted in the inner DLL's `.rdata` section. Format: `[LE uint32 size][encrypted_data][16-byte RC4 key]`. See `extract_config.py` for automated extraction.

---

## Execution Chain

```
hangup.wav (WAV steganography: base64-decode frames → 8-byte XOR key + ciphertext)
    │
    ▼
msbuild.exe — Outer PE (this sample, 179,712 bytes)
    │
    ├─ [1] Reads clean ntdll.dll from disk (GetSystemDirectoryA + "\\ntdll.dll")
    │      Maps via CreateFileA → CreateFileMappingA → MapViewOfFile
    │      Walks .text section for syscall;ret (0F 05 C3) gadget
    │      Resolves ~20 Nt* syscall numbers via DJB2 hash (init=0x1505, mult=0x21)
    │
    ├─ [2] Resolves API by hash 0x24a8d022 from ntdll exports
    │
    └─ [3] Decodes embedded PNG from .data (VA 0x14000b120, 128,421 bytes)
           Uses stb_image.h (statically linked) to decode RGBA pixels
               │
               ▼
           PNG Steganography extraction:
             - Pixel 0 RGBA → big-endian uint32 = shellcode size (95,743)
             - Pixel 1: G,B channels = first 2 shellcode bytes
             - Pixels 2+: R,G,B channels = remaining shellcode bytes (alpha skipped)
               │
               ▼
           Creates dllhost.exe suspended (CreateProcessW, flags=0x8000004)
           Injects shellcode via direct syscalls (NtAllocateVirtualMemory,
             NtWriteVirtualMemory, NtResumeThread, etc.)
               │
               ▼
           Reflective loader stub (1,023 bytes) in dllhost.exe
             - Finds MZ header, maps PE sections, resolves imports
             - Calls DllMain, then exported GetVersions()
               │
               ▼
           Inner DLL: file.dll (94,720 bytes)
             - Constructs "wininet.dll" char-by-char to evade static detection
             - Resolves WinINet APIs via hash (InternetOpenA, HttpOpenRequestA, etc.)
             - RC4-decrypts config from .rdata
             - HTTP(S) beacon to checkmarx[.]zone:8443
             - Named pipe fallback: \\.\pipe\%08lx
             - C++ RTTI: ConnectorHTTP, Connector classes
```

---

## Stage Inventory

| Stage | File | SHA256 | Size |
|-------|------|--------|------|
| 0 — Outer PE | `7290353a...187dcd` | `7290353a3bc2b18e9ea574d3294b09e28edaa6b038285bb101cf09760f187dcd` | 179,712 |
| 1 — Embedded PNG | `stage1_embedded.png` | `7e270255567866d37ad56e3f06977b695e39530eede74a10a0848ba71560cb45` | 128,421 |
| 2 — Shellcode (loader+DLL) | `stage2_shellcode.bin` | `b92bd082bbd7d238089b2bb87d9cbf01be1bf8ab7213b67e9d27108e052ef75c` | 95,743 |
| 3a — Reflective loader | `stage3a_reflective_loader.bin` | `26b689749bc57991cbae2aab8ab6cf5acab6c64db4829ba2b1ced6c60d99a7a8` | 1,023 |
| 3b — Implant DLL | `stage3b_implant.dll` | `dafc1cc5d39bc303562d8587b698b6351e843b77c01764efa8b423a36b88fa6d` | 94,720 |
| 4 — Decrypted config | `stage4_decrypted_config.bin` | `1fdf1add3776bf91b28bdb2864afa1d24224a89f76f8705297d69bb9b4493cb7` | 229 |

---

## AdaptixC2 Beacon Capabilities

Standard AdaptixC2 beacon agent with 35 commands. Full capability documentation: [AdaptixC2 GitHub](https://github.com/Adaptix-Framework/AdaptixC2).

### Capability Summary

| Category | What the operator gets |
|----------|----------------------|
| **Filesystem** | Browse, read, write, upload, download, delete, move, create directories, list drives |
| **Process Control** | List all processes (with user/domain/elevation), execute commands, interactive shell, kill processes |
| **Token Theft** | Steal tokens from other processes, impersonate users, escalate privileges, run as other users |
| **Networking** | SOCKS proxy, reverse port forwards, peer-to-peer mesh for pivoting through internal networks |
| **Stealth** | Direct syscalls, ntdll unhooking, char-by-char string construction, API hashing, process injection into dllhost.exe |

---

## Network IOCs

| Indicator | Context |
|-----------|---------|
| `checkmarx[.]zone` | C2 domain (HTTPS beacon) |
| `checkmarx[.]zone:8443` | C2 endpoint |
| `/telemetry/checkmarx.json` | C2 URI path |
| `X-Content-ID` | Custom HTTP header used in C2 comms |
| `Mozilla/5.0 (Windows NT 6.2; rv:20.0) Gecko/20121202 Firefox/20.0` | User-Agent string |
| `83[.]142[.]209[.]203:8080` | Delivery server (WAV steganography) |

---

## Host IOCs

| Indicator | Type |
|-----------|------|
| `%APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup\msbuild.exe` | Dropped binary |
| `%APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup\msbuild.exe.lock` | Hidden lock file |
| `C:\Windows\System32\dllhost.exe` (spawned suspended) | Injection target |
| `\\.\pipe\%08lx` (random hex name) | Named pipe (fallback C2 channel) |

---

## References

- [Unit 42 — AdaptixC2: A New Open-Source Framework Leveraged in Real-World Attacks](https://unit42.paloaltonetworks.com/adaptixc2-post-exploitation-framework/)
- [Hunt.io — AdaptixC2 Uncovered: Capabilities, Tactics & Hunting Strategies](https://hunt.io/blog/adaptixc2-uncovered-capabilities-tactics-hunting)
- [SecurityInBits — AdaptixC2 Defender Guide](https://www.securityinbits.com/threat-intelligence/adaptixc2-defender-guide/)
- [AdaptixC2 Source Code](https://github.com/Adaptix-Framework/AdaptixC2)
