"""Real tunnel runtime over a test-only ordered message backend (no Steam SDK).

Checks native reliable dispatch/Busy/backpressure, TCP/FIN, unreliable UDP,
on-disk identity reuse after restart, corruption rejection and clean shutdown.
"""
import argparse
import concurrent.futures
import pathlib
import subprocess
import tempfile
import time
from socket_tunnel_integration import Echo, tcp_exchange, udp_metrics


def run(exe):
    directory = pathlib.Path(tempfile.mkdtemp(prefix='bzr-steam-runtime-'))
    identity = directory / 'peers.txt'
    server = Echo()
    try:
        for attempt in range(2):
            stop = directory / f'{attempt}.stop'
            with (directory / f'{attempt}.log').open('w') as log:
                process = subprocess.Popen([exe, str(identity), str(stop)], stdout=log, stderr=subprocess.STDOUT,
                                           creationflags=subprocess.CREATE_NO_WINDOW)
                try:
                    time.sleep(.5)
                    assert process.poll() is None
                    with concurrent.futures.ThreadPoolExecutor(4) as pool:
                        list(pool.map(lambda _: tcp_exchange('127.0.0.1', 64 * 1024), range(4)))
                    udp_metrics('127.0.0.1', 64)
                    if attempt == 0:
                        lock_log = directory / 'locked.log'
                        with lock_log.open('w') as other_log:
                            other = subprocess.run([exe, str(identity), str(directory / 'locked.stop')], stdout=other_log,
                                                   stderr=subprocess.STDOUT, timeout=5, creationflags=subprocess.CREATE_NO_WINDOW)
                        assert other.returncode == 2 and 'identity-map lock unavailable' in lock_log.read_text()
                        identity.with_suffix('.txt.disconnect').touch()
                        time.sleep(.5)
                        tcp_exchange('127.0.0.1', 8192)
                        identity.with_suffix('.txt.bad-reliability').touch()
                        rejected = False
                        try:
                            tcp_exchange('127.0.0.1', 8192)
                        except (ConnectionError, AssertionError):
                            rejected = True
                        assert rejected, 'unreliable stream frame was accepted'
                        time.sleep(.5)
                        tcp_exchange('127.0.0.1', 8192)
                finally:
                    stop.touch()
                    assert process.wait(5) == 0, (directory / f'{attempt}.log').read_text()
            state = identity.read_text()
            assert state == 'BZRSteamPeers1\n76561198000000002 1\n', state
            identity.with_suffix('.txt.disconnect').unlink(missing_ok=True)
            identity.with_suffix('.txt.bad-reliability').unlink(missing_ok=True)
        observed = {row[1][0] for row in server.seen}
        assert observed == {'127.0.1.1'}, observed
        # A corrupt map is never silently rebuilt, which could reassign bans.
        identity.write_text('corrupted\n')
        with (directory / 'corrupt.log').open('w') as log:
            result = subprocess.run([exe, str(identity), str(directory / 'corrupt.stop')], stdout=log,
                                    stderr=subprocess.STDOUT, timeout=5, creationflags=subprocess.CREATE_NO_WINDOW)
        assert result.returncode == 2
        assert identity.read_text() == 'corrupted\n'
        print('PASS: real runtime with ordered test backend; TCP/FIN and Busy sends; all UDP ports; disconnect/reconnect; reliability-mode rejection; persisted source identity; map locking/corruption. No Steam/SDR acceptance claim.')
    finally:
        server.close()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('exe')
    run(parser.parse_args().exe)
