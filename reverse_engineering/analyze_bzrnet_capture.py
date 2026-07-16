#!/usr/bin/env python3
"""Summarize BZRNet WebSocket and UDP traffic without emitting auth secrets.

Requires tshark. The report intentionally prints message types and wire-level
field shapes, not Steam tickets, player IDs, public addresses, or packet bodies.
"""

from __future__ import annotations

import argparse
import collections
import csv
import io
import json
import shutil
import subprocess
from pathlib import Path
from typing import Iterable


def find_tshark(explicit: str | None) -> str:
    candidates = [
        explicit,
        shutil.which("tshark"),
        r"C:\Program Files\Wireshark\tshark.exe",
    ]
    for candidate in candidates:
        if candidate and Path(candidate).is_file():
            return str(candidate)
    raise SystemExit("tshark was not found; install Wireshark or pass --tshark")


def tshark_fields(tshark: str, capture: Path, display_filter: str, fields: Iterable[str]) -> list[list[str]]:
    command = [tshark, "-n", "-r", str(capture), "-Y", display_filter, "-T", "fields"]
    for field in fields:
        command.extend(("-e", field))
    command.extend(("-E", "separator=/t", "-E", "quote=d", "-E", "occurrence=a", "-E", "aggregator=^"))
    result = subprocess.run(command, capture_output=True, text=True, check=True)
    return list(csv.reader(io.StringIO(result.stdout), delimiter="\t", quotechar='"'))


def websocket_counts(tshark: str, capture: Path) -> tuple[collections.Counter[tuple[str, str]], int]:
    rows = tshark_fields(
        tshark,
        capture,
        "websocket",
        ("ip.src", "tcp.srcport", "tcp.dstport", "websocket.payload.text"),
    )
    counts: collections.Counter[tuple[str, str]] = collections.Counter()
    malformed = 0
    for row in rows:
        if len(row) < 4:
            continue
        source_ip, source_port, destination_port, payloads = row[:4]
        direction = "client->server" if destination_port == "1337" else "server->client"
        for raw in payloads.split("^"):
            try:
                message = json.loads(raw)
            except (TypeError, json.JSONDecodeError):
                malformed += 1
                continue
            message_type = str(message.get("type") or "<missing>")
            # Direction is port-derived so no address value reaches the report.
            counts[(direction, message_type)] += 1
    return counts, malformed


def udp_shapes(tshark: str, capture: Path) -> tuple[collections.Counter[tuple[int, int, int]], int]:
    rows = tshark_fields(
        tshark,
        capture,
        "udp && udp.payload",
        ("frame.time_epoch", "udp.srcport", "udp.dstport", "udp.payload"),
    )
    shapes: collections.Counter[tuple[int, int, int]] = collections.Counter()
    invalid = 0
    for row in rows:
        if len(row) < 4:
            continue
        try:
            capture_ms = int(float(row[0]) * 1000)
            payload = bytes.fromhex(row[3].replace(":", ""))
        except (ValueError, OverflowError):
            invalid += 1
            continue
        if len(payload) < 18 or payload[0] & 0xC0 == 0:
            continue
        sent_ms = int.from_bytes(payload[2:10], "big")
        if abs(capture_ms - sent_ms) > 60_000:
            continue
        flags = payload[0] & 0xC0
        kind = payload[1] & 0x0F
        shapes[(flags, kind, len(payload))] += 1
    return shapes, invalid


def report(tshark: str, capture: Path) -> None:
    print(f"=== {capture.name} ===")
    websocket, malformed_ws = websocket_counts(tshark, capture)
    print("WebSocket message types:")
    for (direction, message_type), count in sorted(websocket.items()):
        print(f"  {direction:14} {count:5}  {message_type}")
    if malformed_ws:
        print(f"  non-JSON/control/fragment rows: {malformed_ws}")

    udp, invalid_udp = udp_shapes(tshark, capture)
    print("BZRNet UDP classes (flags, kind, count, common payload sizes):")
    classes: dict[tuple[int, int], collections.Counter[int]] = {}
    for (flags, kind, length), count in udp.items():
        classes.setdefault((flags, kind), collections.Counter())[length] += count
    for (flags, kind), lengths in sorted(classes.items()):
        common = ", ".join(f"{length}x{count}" for length, count in lengths.most_common(5))
        print(f"  0x{flags:02x}  0x{kind:x}  count={sum(lengths.values()):5}  sizes={common}")
    if invalid_udp:
        print(f"  malformed UDP rows: {invalid_udp}")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("captures", nargs="+", type=Path)
    parser.add_argument("--tshark")
    args = parser.parse_args()
    tshark = find_tshark(args.tshark)
    for capture in args.captures:
        if not capture.is_file():
            raise SystemExit(f"capture does not exist: {capture}")
        report(tshark, capture)


if __name__ == "__main__":
    main()
