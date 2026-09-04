#!/usr/bin/env python3
"""Tiny local HTTP backend for Windows wrapper CI.

This intentionally implements only the support protocol surface needed by the
client integration test. It never contacts Cloudflare, Better Stack or Discord.
"""

from __future__ import annotations

import argparse
import json
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path

SUPPORT_ID = "OCP-TEST0001"
TOKEN = "test-session-token"


class Handler(BaseHTTPRequestHandler):
    server_version = "OpenShimSupportMock/1"

    def log_message(self, fmt: str, *args) -> None:
        # Keep Actions output quiet unless the test itself fails.
        return

    @property
    def output(self) -> Path:
        return self.server.output_dir  # type: ignore[attr-defined]

    def send_json(self, status: int, value: object) -> None:
        raw = json.dumps(value).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", str(len(raw)))
        self.end_headers()
        self.wfile.write(raw)

    def read_body(self) -> bytes:
        # HttpClient StreamContent may use HTTP/1.1 chunked transfer encoding
        # instead of publishing Content-Length. Support both so the mock server
        # exercises the transport the same way a real Worker endpoint will.
        transfer_encoding = self.headers.get("Transfer-Encoding", "").lower()
        if "chunked" in transfer_encoding:
            chunks: list[bytes] = []
            while True:
                size_line = self.rfile.readline()
                if not size_line:
                    raise ConnectionError("unexpected EOF in chunk header")
                size_text = size_line.strip().split(b";", 1)[0]
                if not size_text:
                    continue
                size = int(size_text, 16)
                if size == 0:
                    # Consume optional trailer headers and their terminating
                    # blank line.
                    while True:
                        trailer = self.rfile.readline()
                        if not trailer or trailer in (b"\r\n", b"\n"):
                            break
                    break
                chunks.append(self.rfile.read(size))
                terminator = self.rfile.read(2)
                if terminator != b"\r\n":
                    raise ConnectionError("invalid chunk terminator")
            return b"".join(chunks)

        length = int(self.headers.get("Content-Length", "0"))
        return self.rfile.read(length)

    def authorized(self) -> bool:
        return self.headers.get("Authorization") == f"Bearer {TOKEN}"

    def do_GET(self) -> None:
        if self.path == "/health":
            self.send_json(200, {"ok": True, "protocol": 1})
            return
        self.send_json(404, {"error": "not_found"})

    def do_POST(self) -> None:
        if self.path == "/v1/session":
            body = self.read_body()
            (self.output / "session-request.json").write_bytes(body)
            self.send_json(
                201,
                {
                    "support_id": SUPPORT_ID,
                    "session_token": TOKEN,
                    "expires_at": "2099-01-01T00:00:00Z",
                    "protocol": 1,
                },
            )
            return

        prefix = f"/v1/session/{SUPPORT_ID}/"
        if not self.path.startswith(prefix):
            self.send_json(404, {"error": "unknown_session"})
            return
        if not self.authorized():
            self.send_json(401, {"error": "invalid_token"})
            return

        action = self.path[len(prefix) :]
        if action == "logs":
            body = self.read_body()
            payload = json.loads(body.decode("utf-8-sig"))
            sequence = int(payload["sequence"])
            log_dir = self.output / "logs"
            log_dir.mkdir(exist_ok=True)
            (log_dir / f"{sequence:010d}.json").write_text(
                json.dumps(payload, indent=2), encoding="utf-8"
            )
            self.send_json(200, {"ok": True, "sequence": sequence})
            return

        if action == "artifact":
            body = self.read_body()
            name = self.headers.get("X-Artifact-Name", "artifact.bin")
            safe = Path(name).name
            artifact_dir = self.output / "artifacts"
            artifact_dir.mkdir(exist_ok=True)
            (artifact_dir / safe).write_bytes(body)
            self.send_json(201, {"ok": True, "key": safe, "bytes": len(body)})
            return

        if action == "finish":
            body = self.read_body()
            (self.output / "finish.json").write_bytes(body)
            self.send_json(200, {"ok": True})
            return

        self.send_json(404, {"error": "not_found"})


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--port", type=int, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()

    args.output.mkdir(parents=True, exist_ok=True)
    server = ThreadingHTTPServer(("127.0.0.1", args.port), Handler)
    server.output_dir = args.output  # type: ignore[attr-defined]
    (args.output / "ready").write_text("ready\n", encoding="ascii")
    server.serve_forever()


if __name__ == "__main__":
    main()
