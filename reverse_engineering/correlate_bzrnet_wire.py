#!/usr/bin/env python3
"""Correlate BZRNet JSONL wire events with lossless OpenShim buffer_log_v2 UDP records."""

from __future__ import annotations

import argparse
import collections
import json
import struct
from dataclasses import dataclass
from pathlib import Path
from typing import Any

from analyze_bzrnet_trace import details, hex_bytes, load_trace


MAGIC = 0x474C5A42
HEADER = struct.Struct("<IIIIQIIIIIHHHH")
UDP_DIRECTION = {
    1: "inbound",   # recvfrom
    2: "inbound",   # WSARecvFrom
    5: "outbound",  # sendto
    6: "outbound",  # WSASendTo
    8: "inbound",   # WSARecvFrom completion
}


@dataclass
class WireRecord:
    index: int
    event_type: int
    direction: str
    socket_id: int
    tick_ms: int
    sequence: int
    requested: int
    transferred: int
    error: int
    port: int
    flags: int
    payload: bytes
    payload_complete: bool


@dataclass
class WireMatch:
    trace_index: int
    trace_seq: int
    record_index: int
    direction: str
    port: int
    length: int
    delta_ms: int
    confidence: str


def read_meta(path: Path) -> dict[str, str]:
    values: dict[str, str] = {}
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        if "=" in line:
            key, value = line.split("=", 1)
            values[key.strip()] = value.strip()
    return values


def fnv1a64(data: bytes) -> str:
    value = 1469598103934665603
    for byte in data:
        value ^= byte
        value = (value * 1099511628211) & 0xFFFFFFFFFFFFFFFF
    return f"{value:016x}"


def load_buffer_records(bin_path: Path, meta_path: Path) -> list[WireRecord]:
    meta = read_meta(meta_path)
    payload_bytes = int(meta["payload_bytes"])
    stride = int(meta["record_stride"])
    if stride != HEADER.size + payload_bytes:
        raise ValueError(f"unexpected record_stride={stride}, expected {HEADER.size + payload_bytes}")

    blob = bin_path.read_bytes()
    if len(blob) % stride:
        raise ValueError(f"capture size {len(blob)} is not a multiple of stride {stride}")

    records: list[WireRecord] = []
    for index, offset in enumerate(range(0, len(blob), stride)):
        fields = HEADER.unpack_from(blob, offset)
        (
            magic,
            version,
            event_type,
            socket_id,
            tick_ms,
            sequence,
            requested,
            transferred,
            error,
            _raw_ipv4,
            port,
            flags,
            payload_length,
            _reserved,
        ) = fields
        if magic != MAGIC or version != 2:
            raise ValueError(f"bad record {index}: magic={magic:#x} version={version}")
        if payload_length > payload_bytes:
            raise ValueError(f"bad payload_length={payload_length} at record {index}")
        direction = UDP_DIRECTION.get(event_type)
        if direction is None:
            continue
        start = offset + HEADER.size
        payload = blob[start:start + payload_length]
        records.append(WireRecord(
            index=index,
            event_type=event_type,
            direction=direction,
            socket_id=socket_id,
            tick_ms=tick_ms,
            sequence=sequence,
            requested=requested,
            transferred=transferred,
            error=error,
            port=port,
            flags=flags,
            payload=payload,
            payload_complete=transferred <= payload_length,
        ))
    return records


def trace_wire_events(events: list[dict[str, Any]]) -> list[tuple[int, dict[str, Any]]]:
    return [
        (index, event)
        for index, event in enumerate(events)
        if event.get("event") in {"UDP_WIRE_TX", "UDP_WIRE_RX"}
    ]


def candidate_score(event: dict[str, Any], record: WireRecord, tolerance_ms: int) -> tuple[int, str] | None:
    d = details(event)
    direction = str(event.get("direction", ""))
    if direction != record.direction:
        return None
    length = d.get("payloadLength")
    if not isinstance(length, int) or length != record.transferred:
        return None
    event_port = d.get("port")
    if isinstance(event_port, int) and event_port and record.port and event_port != record.port:
        return None
    tick = event.get("tickMs")
    if not isinstance(tick, int):
        return None
    delta = abs(tick - record.tick_ms)
    if delta > tolerance_ms:
        return None

    expected_hash = d.get("fnv1a64")
    if record.payload_complete and isinstance(expected_hash, str) and expected_hash.lower() == fnv1a64(record.payload):
        return (delta, "hash_exact")

    prefix = hex_bytes(d.get("payloadPrefixHex"))
    if prefix and record.payload.startswith(prefix):
        return (delta + 1000, "prefix_length_time")
    return None


def correlate(events: list[dict[str, Any]], records: list[WireRecord], tolerance_ms: int = 50) -> list[WireMatch]:
    unused = set(range(len(records)))
    matches: list[WireMatch] = []
    for trace_index, event in trace_wire_events(events):
        best: tuple[int, int, str] | None = None
        for record_pos in list(unused):
            record = records[record_pos]
            scored = candidate_score(event, record, tolerance_ms)
            if scored is None:
                continue
            score, confidence = scored
            candidate = (score, record_pos, confidence)
            if best is None or candidate[0] < best[0]:
                best = candidate
        if best is None:
            continue
        _score, record_pos, confidence = best
        unused.remove(record_pos)
        record = records[record_pos]
        matches.append(WireMatch(
            trace_index=trace_index,
            trace_seq=int(event.get("seq", 0)),
            record_index=record.index,
            direction=record.direction,
            port=record.port,
            length=record.transferred,
            delta_ms=abs(int(event.get("tickMs", 0)) - record.tick_ms),
            confidence=confidence,
        ))
    return matches


def inner_payload(event: dict[str, Any]) -> bytes | None:
    d = details(event)
    for key in ("innerPayloadHex", "payloadHex"):
        value = hex_bytes(d.get(key))
        if value:
            return value
    return None


def relay_boundary_correlations(events: list[dict[str, Any]], records: list[WireRecord], matches: list[WireMatch], seq_window: int = 24) -> list[dict[str, Any]]:
    record_by_index = {record.index: record for record in records}
    rows: list[dict[str, Any]] = []
    for match in matches:
        wire_event = events[match.trace_index]
        wire_seq = int(wire_event.get("seq", 0))
        if match.direction == "outbound":
            candidates = [event for event in events[:match.trace_index] if event.get("event") == "PRE_RELAY_ENCAP"]
            candidates.reverse()
        else:
            candidates = [event for event in events[match.trace_index + 1:] if event.get("event") == "POST_RELAY_DECAP"]
        boundary: dict[str, Any] | None = None
        for event in candidates:
            seq = int(event.get("seq", 0))
            if abs(seq - wire_seq) > seq_window:
                if match.direction == "outbound" and seq < wire_seq - seq_window:
                    break
                if match.direction == "inbound" and seq > wire_seq + seq_window:
                    break
                continue
            if inner_payload(event):
                boundary = event
                break
        if boundary is None:
            continue

        record = record_by_index[match.record_index]
        if not record.payload_complete:
            continue
        inner = inner_payload(boundary)
        if not inner:
            continue
        offset = record.payload.find(inner)
        rows.append({
            "direction": match.direction,
            "boundarySeq": int(boundary.get("seq", 0)),
            "wireSeq": wire_seq,
            "bufferRecord": match.record_index,
            "innerLength": len(inner),
            "wireLength": len(record.payload),
            "innerOffset": offset if offset >= 0 else None,
            "prefixLength": offset if offset >= 0 else None,
            "suffixLength": len(record.payload) - offset - len(inner) if offset >= 0 else None,
            "innerVerbatim": offset >= 0,
        })
    return rows


def summarize(events: list[dict[str, Any]], records: list[WireRecord], tolerance_ms: int = 50) -> dict[str, Any]:
    matches = correlate(events, records, tolerance_ms=tolerance_ms)
    trace_count = len(trace_wire_events(events))
    exact = sum(match.confidence == "hash_exact" for match in matches)
    prefix = sum(match.confidence == "prefix_length_time" for match in matches)
    by_port = collections.Counter((match.direction, match.port) for match in matches)
    boundaries = relay_boundary_correlations(events, records, matches)
    return {
        "traceWireEvents": trace_count,
        "bufferUdpRecords": len(records),
        "matched": len(matches),
        "unmatchedTrace": trace_count - len(matches),
        "exactHashMatches": exact,
        "prefixMatches": prefix,
        "matchedByDirectionPort": {f"{direction}:{port}": count for (direction, port), count in sorted(by_port.items())},
        "relayBoundaryCorrelations": boundaries,
        "matches": [match.__dict__ for match in matches],
    }


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("trace", type=Path, help="bzrnet_trace.jsonl")
    parser.add_argument("buffer", type=Path, help="bz_buffer_log.bin")
    parser.add_argument("--meta", type=Path, help="bz_buffer_log.meta.txt")
    parser.add_argument("--tolerance-ms", type=int, default=50)
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()

    meta = args.meta or args.buffer.with_name("bz_buffer_log.meta.txt")
    report = summarize(load_trace(args.trace), load_buffer_records(args.buffer, meta), tolerance_ms=args.tolerance_ms)
    if args.json:
        print(json.dumps(report, indent=2, sort_keys=True))
        return

    print(
        f"trace_wire={report['traceWireEvents']} buffer_udp={report['bufferUdpRecords']} "
        f"matched={report['matched']} unmatched_trace={report['unmatchedTrace']} "
        f"exact_hash={report['exactHashMatches']} prefix={report['prefixMatches']}"
    )
    for key, count in report["matchedByDirectionPort"].items():
        print(f"  {key}: {count}")
    if report["relayBoundaryCorrelations"]:
        print("relay_boundaries:")
        for row in report["relayBoundaryCorrelations"]:
            print(
                f"  {row['direction']} boundary_seq={row['boundarySeq']} wire_seq={row['wireSeq']} "
                f"record={row['bufferRecord']} inner={row['innerLength']} wire={row['wireLength']} "
                f"offset={row['innerOffset']} suffix={row['suffixLength']} verbatim={row['innerVerbatim']}"
            )


if __name__ == "__main__":
    main()
