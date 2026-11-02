"""Explicit frozen-helper integration, without loading or launching the game.

Use a scratch game-shaped root containing tools/lan/BZRServer.exe. Default
ports must be free; do not run against an existing user's server.
"""
from __future__ import annotations
import argparse
import socket
import subprocess
import time


def ports_free() -> bool:
    held = []
    try:
        for kind, port in ((socket.SOCK_STREAM, 1337), (socket.SOCK_DGRAM, 1338),
                           (socket.SOCK_DGRAM, 1339), (socket.SOCK_DGRAM, 21337)):
            sock = socket.socket(socket.AF_INET, kind)
            held.append(sock)
            if hasattr(socket, "SO_EXCLUSIVEADDRUSE"):
                sock.setsockopt(socket.SOL_SOCKET, socket.SO_EXCLUSIVEADDRUSE, 1)
            sock.bind(("0.0.0.0", port))
        return True
    except OSError:
        return False
    finally:
        for sock in held:
            sock.close()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--client", required=True)
    parser.add_argument("--root", required=True)
    args = parser.parse_args()
    if not ports_free():
        raise SystemExit("Required ports are in use; no server was launched")
    for mode in ("--real-helper", "--owner-exit"):
        result = subprocess.run([args.client, mode, args.root], capture_output=True,
                                text=True, timeout=45, check=True)
        print(result.stdout, end="")
        deadline = time.monotonic() + 5
        while not ports_free() and time.monotonic() < deadline:
            time.sleep(0.05)
        if not ports_free():
            raise SystemExit(f"Ports still held after {mode}: helper shutdown failed")
        print(f"PASS: sockets released after {mode}")


if __name__ == "__main__":
    main()
