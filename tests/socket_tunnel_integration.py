"""Real Win32 sockets, no game/Steam/install changes. EXE from tools/socket_tunnel/build.ps1.

Checks byte-exact TCP/FIN, all 32 UDP destination ports, stable server source
endpoint, per-peer source IPs, retransmission through impairment, disconnect
cleanup, restart, listener conflicts, malformed input, and direct/tunnel metrics.
"""
import argparse
import concurrent.futures
import json
import pathlib
import socket
import statistics
import struct
import subprocess
import tempfile
import threading
import time


class Echo:
    def __init__(self):
        self.stop = threading.Event()
        self.seen = []
        self.tcp = socket.socket()
        self.tcp.bind(('127.0.0.2', 1337))
        self.tcp.listen()
        self.tcp.settimeout(.1)
        self.udp = []
        self.threads = []
        self.start(self.accept)
        for port in range(1338, 1370):
            sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            sock.bind(('127.0.0.2', port))
            sock.settimeout(.1)
            self.udp.append(sock)
            self.start(self.datagrams, sock)

    def start(self, function, *args):
        thread = threading.Thread(target=function, args=args, daemon=True)
        self.threads.append(thread)
        thread.start()

    def accept(self):
        while not self.stop.is_set():
            try:
                sock, address = self.tcp.accept()
            except TimeoutError:
                continue
            self.seen.append(('tcp', address))
            self.start(self.stream, sock)

    def stream(self, sock):
        with sock:
            sock.settimeout(20)
            try:
                while data := sock.recv(4096):
                    sock.sendall(data)
                # Requires the tunnel to carry FIN without truncating queued data.
                sock.sendall(b'AFTER-FIN')
            except (OSError, TimeoutError):
                pass

    def datagrams(self, sock):
        while not self.stop.is_set():
            try:
                data, address = sock.recvfrom(65535)
            except TimeoutError:
                continue
            self.seen.append(('udp', address, sock.getsockname()[1]))
            sock.sendto(data, address)

    def close(self):
        self.stop.set()
        for thread in self.threads:
            thread.join(.3)
        self.tcp.close()
        for sock in self.udp:
            sock.close()


class Proxy:
    """Drop first copy of selected reliable frames and duplicate subsequent copies."""
    def __init__(self, target):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(('127.0.0.1', 0))
        self.sock.settimeout(.05)
        self.target = target
        self.client = None
        self.impaired = False
        self.dropped = set()
        self.stop = threading.Event()
        self.thread = threading.Thread(target=self.run, daemon=True)
        self.thread.start()

    def run(self):
        while not self.stop.is_set():
            try:
                packet, source = self.sock.recvfrom(65535)
            except (TimeoutError, ConnectionResetError):
                continue
            if source == self.target:
                destination = self.client
            else:
                self.client = source
                destination = self.target
            if destination is None:
                continue
            if self.impaired and len(packet) >= 28 and 5 <= packet[4] <= 8:
                seq = struct.unpack_from('<I', packet, 16)[0]
                key = (source, seq)
                if seq % 7 == 0 and key not in self.dropped:
                    self.dropped.add(key)
                    continue
                self.sock.sendto(packet, destination)
            self.sock.sendto(packet, destination)

    def close(self):
        self.stop.set()
        self.thread.join(1)
        self.sock.close()


class Process:
    def __init__(self, exe, directory, name, *args):
        self.stop = directory / (name + '.stop')
        self.stop.unlink(missing_ok=True)
        self.path = directory / (name + '.log')
        self.log = self.path.open('w')
        self.process = subprocess.Popen([exe, *args, '--stop-file', str(self.stop)], stdout=self.log,
                                        stderr=subprocess.STDOUT, creationflags=subprocess.CREATE_NO_WINDOW)

    def close(self, expected=0):
        self.stop.touch()
        try:
            code = self.process.wait(5)
        except subprocess.TimeoutExpired:
            self.process.kill()  # standalone task-owned test exe, never a game
            self.process.wait()
            raise AssertionError('tunnel failed to stop in 5 seconds')
        finally:
            self.log.close()
        assert code == expected, self.path.read_text()
        if expected == 0:
            assert 'tunnel stopped:' in self.path.read_text()


def tcp_exchange(host, size):
    payload = bytes(range(256)) * (size // 256)
    start = time.perf_counter()
    with socket.create_connection((host, 1337), 3) as sock:
        sock.settimeout(30)
        sock.sendall(payload)
        sock.shutdown(socket.SHUT_WR)
        result = bytearray()
        while data := sock.recv(65536):
            result.extend(data)
    assert result == payload + b'AFTER-FIN', (len(result), len(payload))
    return size / (time.perf_counter() - start)


def udp_metrics(host, count=100):
    samples = []
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        sock.settimeout(2)
        for i in range(count):
            port = 1338 + i % 32
            payload = struct.pack('<I', i) + bytes(range(256)) * 3
            start = time.perf_counter()
            sock.sendto(payload, (host, port))
            response, source = sock.recvfrom(65535)
            assert response == payload and source == (host, port)
            samples.append((time.perf_counter() - start) * 1000)
    return {'p50_ms': statistics.median(samples), 'p95_ms': sorted(samples)[int(count * .95)]}


def run(exe, output):
    output.mkdir(parents=True, exist_ok=True)
    server, proxy = Echo(), Proxy(('127.0.0.1', 27030))
    processes = []
    try:
        bridge = Process(exe, output, 'bridge', 'bridge')
        processes.append(bridge)
        agent = Process(exe, output, 'agent', 'agent', '--remote', '127.0.0.1:' + str(proxy.sock.getsockname()[1]))
        processes.append(agent)
        time.sleep(1.3)
        result = {'direct_loopback': udp_metrics('127.0.0.2'), 'tunnel_loopback': udp_metrics('127.0.0.1')}
        result['direct_tcp_bytes_sec'] = tcp_exchange('127.0.0.2', 256 * 1024)
        result['tunnel_tcp_bytes_sec'] = tcp_exchange('127.0.0.1', 256 * 1024)
        tunnel_udp = [x for x in server.seen if x[0] == 'udp' and x[1][0] == '127.0.0.10']
        assert len({x[1] for x in tunnel_udp}) == 1, 'UDP source endpoint changed between destination ports'
        assert {x[2] for x in tunnel_udp} == set(range(1338, 1370))
        proxy.impaired = True
        with concurrent.futures.ThreadPoolExecutor(4) as pool:
            list(pool.map(lambda _: tcp_exchange('127.0.0.1', 8192), range(4)))
        assert proxy.dropped
        result['impaired_dropped_frames'] = len(proxy.dropped)
        # Unknown/malformed frames, 8080 and non-server OPEN targets are rejected.
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as bad:
            for port in (8080, 1337):
                bad.sendto(struct.pack('<4sBBHQIIHH', b'BZT\x01', 9, 0, 0, 123, 0, 0, port, 8888), proxy.target)
            bad.sendto(b'garbage', proxy.target)
        conflict = Process(exe, output, 'conflict', 'agent')
        conflict.close(expected=2)
        # A second protocol peer is enough to prove independent bridge source IPs
        # on one PC (two agents cannot bind the same loopback listeners).
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as peer:
            peer.settimeout(2)
            session = 987654321
            def packet(kind, seq=0, stream=0, port=0):
                return struct.pack('<4sBBHQIIHH', b'BZT\x01', kind, 0, 0, session, seq, stream, port, 0)
            peer.sendto(packet(1), proxy.target)
            assert peer.recv(1024)[4] == 2
            peer.sendto(packet(5, 1, 1, 1337), proxy.target)
            deadline = time.monotonic() + 2
            while not any(x[:1] == ('tcp',) and x[1][0] == '127.0.0.11' for x in server.seen):
                assert time.monotonic() < deadline
                time.sleep(.01)
        agent.close()
        processes.remove(agent)
        proxy.impaired = False
        # Old session must time out; bridge then releases its source identity.
        time.sleep(16)
        restarted = Process(exe, output, 'restarted', 'agent', '--remote', '127.0.0.1:' + str(proxy.sock.getsockname()[1]))
        processes.append(restarted)
        time.sleep(1.3)
        tcp_exchange('127.0.0.1', 4096)
        assert 'peer timeout:' in bridge.path.read_text()
        # Bridge disappearance must close an established client stream, and a
        # replacement bridge must accept a fresh session without agent restart.
        with socket.create_connection(('127.0.0.1', 1337), 2) as active:
            active.settimeout(18)
            active.sendall(b'live-before-bridge-loss')
            assert active.recv(128) == b'live-before-bridge-loss'
            bridge.close()
            processes.remove(bridge)
            assert active.recv(128) == b''
        replacement = Process(exe, output, 'replacement', 'bridge')
        processes.append(replacement)
        time.sleep(1.3)
        tcp_exchange('127.0.0.1', 4096)
        result['checks'] = '32 UDP ports; stable source; distinct peers; TCP bytes/FIN; impaired concurrent streams; malformed/8080; exclusive bind; agent timeout/restart; bridge loss/restart; clean stop'
        (output / 'metrics.json').write_text(json.dumps(result, indent=2))
        print(json.dumps(result, indent=2))
    finally:
        for process in reversed(processes):
            process.close()
        proxy.close()
        server.close()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('exe')
    parser.add_argument('--out', type=pathlib.Path)
    args = parser.parse_args()
    run(args.exe, args.out or pathlib.Path(tempfile.mkdtemp(prefix='bzr-tunnel-test-')))
