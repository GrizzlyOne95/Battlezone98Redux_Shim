#!/usr/bin/env python3
"""Analyze OpenShim native BZRNet JSONL traces without printing sensitive fields."""

from __future__ import annotations

import argparse
import collections
import json
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Iterable


@dataclass
class Correlation:
    direction: str
    pre_seq: int
    wire_seq: int
    inner_len: int
    wire_len: int
    inner_offset: int | None
    prefix_len: int | None
    suffix_len: int | None


def load_trace(path: Path) -> list[dict[str, Any]]:
    events: list[dict[str, Any]] = []
    for line_no, line in enumerate(path.read_text(encoding="utf-8", errors="replace").splitlines(), 1):
        if not line.strip():
            continue
        try:
            row = json.loads(line)
        except json.JSONDecodeError as exc:
            raise ValueError(f"invalid JSONL at {path}:{line_no}: {exc}") from exc
        if not isinstance(row, dict):
            raise ValueError(f"non-object JSONL record at {path}:{line_no}")
        events.append(row)
    return events


def details(event: dict[str, Any]) -> dict[str, Any]:
    value = event.get("details")
    return value if isinstance(value, dict) else {}


def parse_message(event: dict[str, Any]) -> dict[str, Any] | None:
    text = details(event).get("messageJson")
    if not isinstance(text, str):
        return None
    try:
        value = json.loads(text)
    except json.JSONDecodeError:
        return None
    return value if isinstance(value, dict) else None


def hex_bytes(value: Any) -> bytes | None:
    if not isinstance(value, str) or len(value) % 2:
        return None
    try:
        return bytes.fromhex(value)
    except ValueError:
        return None


def event_payload(event: dict[str, Any], *, inner: bool) -> bytes | None:
    d = details(event)
    keys = ("payloadHex", "innerPayloadHex") if inner else ("wireHex", "payloadHex", "payloadPrefixHex")
    for key in keys:
        data = hex_bytes(d.get(key))
        if data is not None:
            return data
    return None


def correlate_relay(events: list[dict[str, Any]], window: int = 24) -> list[Correlation]:
    """Correlate future PRE_RELAY_ENCAP/POST_RELAY_DECAP events with wire records.

    The current first-pass native instrumentation only carries a bounded wire
    prefix. Once engine boundary hooks supply full inner/wire hex or a binary
    capture adapter supplies it, this routine automatically finds the inner
    payload offset instead of requiring manual hex inspection.
    """
    out: list[Correlation] = []
    for index, event in enumerate(events):
        name = str(event.get("event", ""))
        if name not in {"PRE_RELAY_ENCAP", "POST_RELAY_DECAP"}:
            continue
        outgoing = name == "PRE_RELAY_ENCAP"
        target = "UDP_WIRE_TX" if outgoing else "UDP_WIRE_RX"
        inner = event_payload(event, inner=True)
        if not inner:
            continue
        span = event.get("spanId") or details(event).get("spanId")
        parent_seq = event.get("parentSeq") or details(event).get("parentSeq")
        candidates = events[index + 1:index + 1 + window] if outgoing else events[max(0, index - window):index]
        if not outgoing:
            candidates = list(reversed(candidates))
        best: dict[str, Any] | None = None
        for candidate in candidates:
            if str(candidate.get("event", "")) != target:
                continue
            if span is not None and (candidate.get("spanId") or details(candidate).get("spanId")) == span:
                best = candidate
                break
            if parent_seq is not None and (candidate.get("parentSeq") or details(candidate).get("parentSeq")) == parent_seq:
                best = candidate
                break
            if candidate.get("socketId") == event.get("socketId") or event.get("socketId") in (0, None):
                best = candidate
                break
        if best is None:
            continue
        wire = event_payload(best, inner=False)
        if not wire:
            continue
        offset = wire.find(inner)
        if offset >= 0:
            prefix = offset
            suffix = len(wire) - offset - len(inner)
            found: int | None = offset
        else:
            prefix = suffix = found = None
        out.append(Correlation(
            direction="tx" if outgoing else "rx",
            pre_seq=int(event.get("seq", 0)),
            wire_seq=int(best.get("seq", 0)),
            inner_len=len(inner),
            wire_len=len(wire),
            inner_offset=found,
            prefix_len=prefix,
            suffix_len=suffix,
        ))
    return out


def prefix_stability(events: list[dict[str, Any]], correlations: Iterable[Correlation]) -> dict[str, Any]:
    by_seq = {int(e.get("seq", 0)): e for e in events}
    prefixes: list[bytes] = []
    for corr in correlations:
        if corr.inner_offset is None or corr.inner_offset <= 0:
            continue
        wire = event_payload(by_seq.get(corr.wire_seq, {}), inner=False)
        if wire is not None:
            prefixes.append(wire[:corr.inner_offset])
    if not prefixes:
        return {"samples": 0}
    min_len = min(map(len, prefixes))
    positions: list[dict[str, Any]] = []
    for i in range(min_len):
        values = {p[i] for p in prefixes}
        positions.append({
            "offset": i,
            "uniqueValues": len(values),
            "classification": "invariant" if len(values) == 1 else "variable",
            "value": next(iter(values)) if len(values) == 1 else None,
        })
    return {"samples": len(prefixes), "commonPrefixLength": min_len, "positions": positions}


def summarize(events: list[dict[str, Any]]) -> dict[str, Any]:
    event_counts = collections.Counter(str(e.get("event", "")) for e in events)
    message_counts = collections.Counter(
        (str(e.get("direction", "")), str(e.get("messageType", "")))
        for e in events if e.get("messageType")
    )
    reason_codes = collections.Counter()
    for event in events:
        d = details(event)
        if isinstance(d.get("reasonCode"), int):
            reason_codes[(str(event.get("messageType", "")), d["reasonCode"])] += 1
    dropped = sum(
        int(details(e).get("droppedSinceLastReport", 0))
        for e in events if e.get("event") == "TRACE_DROPPED_EVENTS"
    )
    first_seq = min((int(e.get("seq", 0)) for e in events), default=0)
    last_seq = max((int(e.get("seq", 0)) for e in events), default=0)
    first_tick = min((int(e.get("tickMs", 0)) for e in events), default=0)
    last_tick = max((int(e.get("tickMs", 0)) for e in events), default=0)
    correlations = correlate_relay(events)
    return {
        "records": len(events),
        "seqRange": [first_seq, last_seq],
        "durationMs": max(0, last_tick - first_tick),
        "eventCounts": dict(sorted(event_counts.items())),
        "messageCounts": {f"{direction} {message_type}": count for (direction, message_type), count in sorted(message_counts.items())},
        "reasonCodes": {f"{message_type}:{reason}": count for (message_type, reason), count in sorted(reason_codes.items())},
        "droppedEventsReported": dropped,
        "relayCorrelations": [corr.__dict__ for corr in correlations],
        "relayPrefixStability": prefix_stability(events, correlations),
    }


def print_text(summary: dict[str, Any]) -> None:
    print(f"records={summary['records']} seq={summary['seqRange'][0]}..{summary['seqRange'][1]} duration_ms={summary['durationMs']}")
    print(f"dropped_events_reported={summary['droppedEventsReported']}")
    print("events:")
    for name, count in summary["eventCounts"].items():
        print(f"  {name}: {count}")
    print("messages:")
    for name, count in summary["messageCounts"].items():
        print(f"  {name}: {count}")
    if summary["reasonCodes"]:
        print("reason_codes:")
        for name, count in summary["reasonCodes"].items():
            print(f"  {name}: {count}")
    if summary["relayCorrelations"]:
        print("relay_payload_correlations:")
        for row in summary["relayCorrelations"]:
            print(
                "  {direction} inner_seq={pre_seq} wire_seq={wire_seq} inner={inner_len} wire={wire_len} "
                "offset={inner_offset} prefix={prefix_len} suffix={suffix_len}".format(**row)
            )


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("trace", type=Path, help="bzrnet_trace.jsonl")
    parser.add_argument("--json", action="store_true", help="emit machine-readable summary JSON")
    args = parser.parse_args()
    summary = summarize(load_trace(args.trace))
    if args.json:
        print(json.dumps(summary, indent=2, sort_keys=True))
    else:
        print_text(summary)


if __name__ == "__main__":
    main()
