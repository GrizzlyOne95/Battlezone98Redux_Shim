#!/usr/bin/env python3
"""Summarize OpenShim buffer_log_v2 relay captures without dumping identities."""

from __future__ import annotations

import argparse
import collections
import json
import socket
import struct
from pathlib import Path


MAGIC = 0x474C5A42
HEADER = struct.Struct("<IIIIQIIIIIHHHH")
EVENT_NAMES = {
    1: "recvfrom",
    2: "WSARecvFrom",
    3: "ioctlsocket",
    4: "WSAIoctl",
    5: "sendto",
    6: "WSASendTo",
    7: "WSARecv_completion",
    8: "WSARecvFrom_completion",
}


def read_meta(path: Path) -> dict[str, str]:
    values: dict[str, str] = {}
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        if "=" in line:
            key, value = line.split("=", 1)
            values[key.strip()] = value.strip()
    return values


def endpoint_text(raw_ipv4: int, port: int) -> str:
    if not raw_ipv4:
        return "none"
    address = socket.inet_ntoa(struct.pack("<I", raw_ipv4))
    return f"{address}:{port}"


def bzr_header(payload: bytes) -> tuple[int, int, int, int, int] | None:
    if len(payload) < 18:
        return None
    return (
        payload[0],
        payload[1] & 0x0F,
        int.from_bytes(payload[2:10], "big"),
        int.from_bytes(payload[10:14], "big"),
        int.from_bytes(payload[14:18], "big"),
    )


def summarize_binary(bin_path: Path, meta_path: Path) -> None:
    meta = read_meta(meta_path)
    payload_bytes = int(meta["payload_bytes"])
    stride = int(meta["record_stride"])
    if stride != HEADER.size + payload_bytes:
        raise ValueError(f"unexpected stride {stride}; expected {HEADER.size + payload_bytes}")

    data = bin_path.read_bytes()
    if len(data) % stride:
        raise ValueError(f"capture size {len(data)} is not a multiple of stride {stride}")

    event_counts: collections.Counter[str] = collections.Counter()
    wire_counts: collections.Counter[tuple[str, int, int]] = collections.Counter()
    endpoint_aliases: dict[str, str] = {}
    first_tick: int | None = None
    last_tick: int | None = None
    truncated = 0

    for offset in range(0, len(data), stride):
        fields = HEADER.unpack_from(data, offset)
        (
            magic,
            version,
            event_type,
            _socket_id,
            tick_ms,
            _sequence,
            _requested,
            transferred,
            _error,
            raw_ipv4,
            port,
            _flags,
            payload_length,
            _reserved,
        ) = fields
        if magic != MAGIC or version != 2:
            raise ValueError(f"bad record at offset {offset}: magic={magic:#x} version={version}")
        if payload_length > payload_bytes:
            raise ValueError(f"bad payload length {payload_length} at offset {offset}")

        name = EVENT_NAMES.get(event_type, f"event_{event_type}")
        event_counts[name] += 1
        endpoint = endpoint_text(raw_ipv4, port)
        if endpoint != "none" and endpoint not in endpoint_aliases:
            endpoint_aliases[endpoint] = f"EP{len(endpoint_aliases) + 1}"

        payload_start = offset + HEADER.size
        payload = data[payload_start : payload_start + payload_length]
        header = bzr_header(payload)
        if header:
            wire_counts[(name, header[1], transferred)] += 1
        else:
            wire_counts[(name, -1, transferred)] += 1
        if transferred > payload_length:
            truncated += 1
        first_tick = tick_ms if first_tick is None else min(first_tick, tick_ms)
        last_tick = tick_ms if last_tick is None else max(last_tick, tick_ms)

    print(f"format={meta.get('format', 'unknown')}")
    print(f"records={len(data) // stride} payload_bytes={payload_bytes} truncated_records={truncated}")
    if first_tick is not None and last_tick is not None:
        print(f"duration_ms={last_tick - first_tick}")
    print("events:")
    for name, count in sorted(event_counts.items()):
        print(f"  {name}: {count}")
    print("wire_shapes (event, kind, transferred_bytes):")
    for (name, kind, length), count in sorted(wire_counts.items()):
        kind_text = "n/a" if kind < 0 else str(kind)
        print(f"  {name}, kind={kind_text}, bytes={length}: {count}")
    print(f"endpoint_count={len(endpoint_aliases)} (addresses intentionally not printed)")


def summarize_control(path: Path) -> None:
    counts: collections.Counter[tuple[str, str]] = collections.Counter()
    forbidden = 0
    for line_number, line in enumerate(path.read_text(encoding="utf-8", errors="replace").splitlines(), 1):
        if not line.strip():
            continue
        record = json.loads(line)
        message_type = str(record.get("type", ""))
        direction = str(record.get("direction", ""))
        counts[(direction, message_type)] += 1
        if message_type == "Authorization":
            forbidden += 1
            print(f"WARNING: Authorization record found at line {line_number}")

    print("control_messages:")
    for (direction, message_type), count in sorted(counts.items()):
        print(f"  {direction} {message_type}: {count}")
    print(f"authorization_records={forbidden}")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("capture", type=Path, help="bz_buffer_log.bin")
    parser.add_argument("--meta", type=Path, help="bz_buffer_log.meta.txt")
    parser.add_argument("--control", type=Path, help="bz_relay_control.jsonl")
    args = parser.parse_args()

    meta_path = args.meta or args.capture.with_name("bz_buffer_log.meta.txt")
    control_path = args.control or args.capture.with_name("bz_relay_control.jsonl")
    summarize_binary(args.capture, meta_path)
    if control_path.exists():
        summarize_control(control_path)


if __name__ == "__main__":
    main()
