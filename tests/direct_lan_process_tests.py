"""Run actual native client processes: no lobby server, account provider or game.

All sockets bind loopback. Each host is one of the participating clients using
the same embedded control node, not the earlier Python/Win32 helper service.
"""
import argparse
import queue
import socket
import struct
import sys
import subprocess
import threading
import time


class Peer:
    def __init__(self, executable, *args):
        flags = getattr(subprocess, "CREATE_NO_WINDOW", 0)
        self.process = subprocess.Popen([executable, *args], stdout=subprocess.PIPE,
                                        stderr=subprocess.STDOUT, text=True, creationflags=flags)
        self.lines = []
        self.pending = queue.Queue()
        self.reader = threading.Thread(target=self._read, daemon=True)
        self.reader.start()

    def _read(self):
        for line in self.process.stdout:
            line = line.strip()
            self.lines.append(line)
            self.pending.put(line)

    def expect(self, prefix, seconds=10):
        deadline = time.monotonic() + seconds
        while time.monotonic() < deadline:
            try:
                line = self.pending.get(timeout=max(0.01, deadline - time.monotonic()))
            except queue.Empty:
                break
            if line.startswith(prefix):
                return line
        raise AssertionError((prefix, self.lines, self.process.poll()))

    def finish(self):
        code = self.process.wait(timeout=10)
        self.reader.join(timeout=1)
        if code:
            raise AssertionError((code, self.lines))

    def cleanup(self):
        if self.process.poll() is None:
            self.process.terminate()  # only this test's own standalone client
            self.process.wait(timeout=5)
        self.reader.join(timeout=1)
        self.process.stdout.close()


def session(executable, count, abrupt=False):
    peers = []
    try:
        host = Peer(executable, "--host", "--players", str(count))
        peers.append(host)
        _, port, discovery = host.expect("LISTEN ").split()
        for index in range(count - 1):
            args = ["--players", str(count)]
            args += ["--discover", discovery] if index == 0 else ["--port", port]
            if abrupt and index == count - 2:
                args += ["--depart"]
            peers.append(Peer(executable, *args))
        peers[1].expect("DISCOVERED")
        for peer in peers:
            peer.expect(f"RUNNING {count}")
        identities = [peer.expect("NATIVE ").split()[1:] for peer in peers]
        assert all(f"P2P {2 * (count - 1)}" in peer.lines for peer in peers), [peer.lines for peer in peers]
        assert len({identity[0] for identity in identities}) == 1, identities
        assert len({identity[1] for identity in identities}) == 1, identities
        assert len({identity[2] for identity in identities}) == count, identities
        assert identities[0][1] == identities[0][2], identities
        host.expect(f"ROSTER {count - 1 if abrupt else count}")
        for peer in peers[1:]:
            if not (abrupt and peer is peers[-1]):
                peer.expect("CLOSED Host ended the session")
        for peer in peers:
            peer.finish()
        print(f"PASS: {count} independent clients, discovery/manual join, prepare/commit, "
              f"consistent native identity/roster projection, {'abrupt guest departure, ' if abrupt else ''}host shutdown")
    finally:
        if sys.exc_info()[0]:
            print("PEER DIAGNOSTICS", [peer.lines for peer in peers], flush=True)
        for peer in reversed(peers):
            peer.cleanup()


def mismatch(executable):
    peers = []
    try:
        host = Peer(executable, "--host", "--players", "2")
        peers.append(host)
        _, port, _ = host.expect("LISTEN ").split()
        guest = Peer(executable, "--port", port, "--mismatch", "--players", "2")
        peers.append(guest)
        guest.expect("CLOSED Game build or content differs")
        guest.finish()
        assert not any(line.startswith("RUNNING") for line in host.lines)
        print("PASS: incompatible content rejected before readiness/launch")
    finally:
        for peer in reversed(peers):
            peer.cleanup()


def hostile_input(executable):
    peers = []
    try:
        host = Peer(executable, "--host", "--players", "2")
        peers.append(host)
        _, port, _ = host.expect("LISTEN ").split()

        def closed(connection, seconds=3):
            connection.settimeout(seconds)
            try:
                while connection.recv(8192):
                    pass
            except ConnectionResetError:
                pass

        with socket.create_connection(("127.0.0.1", int(port))) as connection:
            connection.sendall(struct.pack("!I", 4097))
            closed(connection)
        with socket.create_connection(("127.0.0.1", int(port))) as connection:
            connection.sendall(b"\x00\x00")  # incomplete greeting cannot occupy a slot forever
            closed(connection, 7)
        with socket.create_connection(("127.0.0.1", int(port))) as connection:
            sender = bytes([100]) * 16

            def frame(kind, serial, payload=b"", session=bytes(16)):
                body = b"BZLANP02" + bytes([kind, 0, 0, 0]) + session + sender + struct.pack("!Q", serial) + payload
                return struct.pack("!I", len(body)) + body

            payload = b"\x072.2.301" + bytes([42]) + bytes(31) + b"\x05Flood" + struct.pack("!H", 21003)
            connection.sendall(frame(1, 1, payload))
            connection.settimeout(3)
            greeting = b""
            while len(greeting) < 56:
                part = connection.recv(8192)
                assert part, "host closed valid greeting"
                greeting += part
            session_id = greeting[16:32]
            connection.sendall(b"".join(frame(10, serial, session=session_id) for serial in range(2, 66)))
            closed(connection)
        # Malformed/idle/flooding peers must not poison the next real session.
        guest = Peer(executable, "--port", port, "--players", "2")
        peers.append(guest)
        host.expect("RUNNING 2")
        guest.expect("RUNNING 2")
        guest.expect("CLOSED Host ended the session")
        for peer in peers:
            peer.finish()
        print("PASS: malformed frame, stalled greeting and control flood isolated; valid clients still launch")
    finally:
        if sys.exc_info()[0]:
            print("PEER DIAGNOSTICS", [peer.lines for peer in peers], flush=True)
        for peer in reversed(peers):
            peer.cleanup()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--peer", required=True)
    args = parser.parse_args()
    session(args.peer, 3)
    session(args.peer, 4, abrupt=True)
    mismatch(args.peer)
    hostile_input(args.peer)


if __name__ == "__main__":
    main()
