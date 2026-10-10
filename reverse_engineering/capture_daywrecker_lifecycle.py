"""Attach a bounded observation to existing GOG peers; never launch or stop a game."""
import argparse
import hashlib
import json
from pathlib import Path
import threading
import time

import frida
import psutil

EXPECTED_SHA256 = '8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--pid', type=int, action='append', required=True)
    parser.add_argument('--seconds', type=float, default=120)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    if not 0 < args.seconds <= 3600:
        parser.error('--seconds must be greater than zero and at most 3600')
    source = Path(__file__).with_name('daywrecker_lifecycle_trace.js').read_text(encoding='utf-8')
    # Validate all disk images before installing any instrumentation.
    identities = []
    for pid in dict.fromkeys(args.pid):
        exe = Path(psutil.Process(pid).exe())
        sha = hashlib.sha256(exe.read_bytes()).hexdigest()
        if exe.name.lower() != 'battlezone98redux.exe' or sha != EXPECTED_SHA256:
            raise RuntimeError(f'Unqualified executable for PID {pid}: {exe} SHA256={sha}')
        identities.append({'pid': pid, 'exe': str(exe), 'sha256': sha})
    args.output.parent.mkdir(parents=True, exist_ok=True)
    sessions = []
    scripts = []
    lock = threading.Lock()
    ready = set()
    failed = threading.Event()
    closing = threading.Event()
    with args.output.open('x', encoding='utf-8') as output:
        def record(payload):
            with lock:
                output.write(json.dumps(payload, allow_nan=False) + '\n')
                output.flush()

        def on_message(message, data):
            if message['type'] == 'send':
                payload = message['payload']
                if payload.get('event') == 'ready':
                    ready.add(payload['pid'])
                record(payload)
            else:
                record({'event': 'frida_error', 'message': message})
                failed.set()

        def on_detached(reason, crash):
            if not closing.is_set():
                record({'event': 'peer_detached', 'reason': reason, 'crash': str(crash)})
                failed.set()

        try:
            for identity in identities:
                record({'event': 'image_identity', **identity})
                session = frida.attach(identity['pid'])
                sessions.append(session)
                session.on('detached', on_detached)
                script = session.create_script(source)
                scripts.append(script)
                script.on('message', on_message)
                script.load()
            deadline = time.monotonic() + args.seconds
            while time.monotonic() < deadline and not failed.wait(0.25):
                pass
        except KeyboardInterrupt:
            pass
        finally:
            closing.set()
            for script in reversed(scripts):
                try:
                    script.unload()
                except frida.InvalidOperationError:
                    pass
            for session in reversed(sessions):
                session.detach()
            record({'event': 'capture_end', 'ready_pids': sorted(ready),
                    'error': failed.is_set()})
    print(f'Captured {len(ready)}/{len(identities)} peers to {args.output}')
    if failed.is_set() or len(ready) != len(identities):
        raise SystemExit(1)


if __name__ == '__main__':
    main()
