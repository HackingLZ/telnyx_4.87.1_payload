#!/usr/bin/env python3
"""
C2 monitor — research tool for observing the telnyx C2 endpoint.

Polls the C2 server every 60 seconds, logs all responses, and saves
any new payloads to the payloads/ directory. Alerts (terminal bell)
when a new payload URL appears.

The C2 at 83.142.209.203:8080 serves WAV files containing hidden
payloads via steganography. This monitor watches for new URLs and
downloads them for analysis.

Usage:
    python3 monitor_c2.py
    # Ctrl+C to stop
"""
import urllib.request
import hashlib
import os
import sys
import time
from datetime import datetime

C2_URL = "http://83.142.209.203:8080/"
UA = "Mozilla/5.0"
INTERVAL = 60
OUTDIR = "payloads"

os.makedirs(OUTDIR, exist_ok=True)


def log(msg):
    ts = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    line = f"[{ts}] {msg}"
    print(line, flush=True)
    with open("c2_monitor.log", "a") as f:
        f.write(line + "\n")


def beep():
    sys.stdout.write("\a")
    sys.stdout.flush()
    for _ in range(5):
        sys.stdout.write("\a")
        sys.stdout.flush()
        time.sleep(0.3)


def fetch_c2():
    try:
        req = urllib.request.Request(
            C2_URL, headers={"User-Agent": UA}
        )
        with urllib.request.urlopen(req, timeout=10) as r:
            return r.read()
    except Exception as e:
        log(f"Fetch error: {e}")
        return None


def download_url(url):
    ts = datetime.now().strftime("%Y%m%d_%H%M%S")
    h = hashlib.sha256(url.encode()).hexdigest()[:8]
    filename = os.path.join(OUTDIR, f"payload_{ts}_{h}")
    try:
        req = urllib.request.Request(
            url, headers={"User-Agent": UA}
        )
        with urllib.request.urlopen(req, timeout=30) as r:
            data = r.read()
        with open(filename, "wb") as f:
            f.write(data)
        sha = hashlib.sha256(data).hexdigest()
        size = len(data)
        log(f"Downloaded: {filename} ({size} bytes)")
        log(f"SHA256: {sha}")
        return filename
    except Exception as e:
        log(f"Download error: {e}")
        return None


def main():
    log(f"Monitoring {C2_URL} every {INTERVAL}s")
    log(f"Payloads saved to {OUTDIR}/")
    seen = set()

    while True:
        resp = fetch_c2()
        if resp is None:
            log("No response from C2")
        else:
            sha = hashlib.sha256(resp).hexdigest()
            size = len(resp)
            if sha in seen:
                log(f"Same response ({size} bytes, sha256={sha[:16]}...)")
            else:
                log(f"NEW RESPONSE: {size} bytes, sha256={sha}")
                beep()
                ts = datetime.now().strftime("%Y%m%d_%H%M%S")
                filename = os.path.join(OUTDIR, f"response_{ts}_{sha[:8]}")
                with open(filename, "wb") as f:
                    f.write(resp)
                log(f"Saved to {filename}")
                seen.add(sha)

                # If response looks like a URL, try downloading it too
                try:
                    text = resp.decode("utf-8").strip()
                    if text.startswith("http"):
                        log(f"Response is URL: {text}")
                        download_url(text)
                except:
                    pass

                beep()

        time.sleep(INTERVAL)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        log("Stopped by user")
