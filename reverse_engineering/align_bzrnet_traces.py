#!/usr/bin/env python3
"""Align two OpenShim BZRNet traces onto one approximate UTC timeline."""

from __future__ import annotations

import argparse
import json
from dataclasses import dataclass
from pathlib import Path
from typing import Any

from analyze_bzrnet_trace import load_trace


HUNDRED_NS_PER_SECOND = 10_000_000


@dataclass(frozen=True)
class ClockCalibration:
    qpc: int
    qpc_frequency: int
    filetime_utc: int

    def event_filetime(self, event_qpc: int) -> int:
        if self.qpc_frequency <= 0:
            raise ValueError("qpcFrequency must be positive")
        delta_qpc = event_qpc - self.qpc
        delta_100ns = round(delta_qpc * HUNDRED_NS_PER_SECOND / self.qpc_frequency)
        return self.filetime_utc + delta_100ns


def load_calibration(path: Path) -> ClockCalibration:
    session = json.loads(path.read_text(encoding="utf-8"))
    calibration = session.get("clockCalibration")
    if not isinstance(calibration, dict):
        raise ValueError(f"{path} has no clockCalibration object")
    return ClockCalibration(
        qpc=int(calibration["qpc"]),
        qpc_frequency=int(calibration["qpcFrequency"]),
        filetime_utc=int(calibration["fileTimeUtc"]),
    )


def aligned_events(label: str, session_path: Path, trace_path: Path) -> list[dict[str, Any]]:
    clock = load_calibration(session_path)
    rows: list[dict[str, Any]] = []
    for event in load_trace(trace_path):
        if not isinstance(event.get("qpc"), int):
            continue
        rows.append({
            "label": label,
            "utcFileTime": clock.event_filetime(int(event["qpc"])),
            "seq": int(event.get("seq", 0)),
            "layer": str(event.get("layer", "")),
            "event": str(event.get("event", "")),
            "direction": str(event.get("direction", "")),
            "messageType": str(event.get("messageType", "")),
            "socketId": int(event.get("socketId", 0)),
            "socketGeneration": int(event.get("socketGeneration", 0)),
        })
    return rows


def merge_timelines(inputs: list[tuple[str, Path, Path]]) -> list[dict[str, Any]]:
    merged: list[dict[str, Any]] = []
    for label, session, trace in inputs:
        merged.extend(aligned_events(label, session, trace))
    merged.sort(key=lambda row: (row["utcFileTime"], row["label"], row["seq"]))
    if merged:
        origin = merged[0]["utcFileTime"]
        for row in merged:
            row["relativeMs"] = round((row["utcFileTime"] - origin) / 10_000, 3)
    return merged


def print_text(rows: list[dict[str, Any]]) -> None:
    for row in rows:
        type_suffix = f" {row['messageType']}" if row["messageType"] else ""
        print(
            f"+{row.get('relativeMs', 0):11.3f}ms "
            f"[{row['label']}] seq={row['seq']:06d} "
            f"{row['layer']}/{row['event']} {row['direction']}{type_suffix} "
            f"socket={row['socketId']}:{row['socketGeneration']}"
        )


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("session_a", type=Path)
    parser.add_argument("trace_a", type=Path)
    parser.add_argument("session_b", type=Path)
    parser.add_argument("trace_b", type=Path)
    parser.add_argument("--label-a", default="A")
    parser.add_argument("--label-b", default="B")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()

    rows = merge_timelines([
        (args.label_a, args.session_a, args.trace_a),
        (args.label_b, args.session_b, args.trace_b),
    ])
    if args.json:
        print(json.dumps(rows, indent=2, sort_keys=True))
    else:
        print_text(rows)


if __name__ == "__main__":
    main()
