#!/usr/bin/env python3
"""Build one sanitized QA/coverage report from an OpenShim BZRNet session directory."""

from __future__ import annotations

import argparse
import json
from pathlib import Path
from typing import Any

from analyze_bzrnet_trace import load_trace, summarize as summarize_trace
from bzrnet_capture_coverage import evaluate as evaluate_coverage
from validate_bzrnet_trace import validate_trace


def safe_identity(path: Path) -> dict[str, Any] | None:
    if not path.exists():
        return None
    value = json.loads(path.read_text(encoding="utf-8-sig"))
    if not isinstance(value, dict):
        return None
    return {
        "formatVersion": value.get("formatVersion"),
        "platform": value.get("platform"),
        "gameExecutable": value.get("gameExecutable"),
        "openShim": value.get("openShim"),
        "launchProfile": value.get("launchProfile"),
        "captureStartUtc": value.get("captureStartUtc"),
        "captureStopUtc": value.get("captureStopUtc"),
        "note": value.get("note"),
    }


def build_report(session_dir: Path, *, allow_drops: bool = False) -> dict[str, Any]:
    trace_path = session_dir / "bzrnet_trace.jsonl"
    session_path = session_dir / "bzrnet_session.json"
    if not trace_path.exists():
        raise FileNotFoundError(trace_path)
    if not session_path.exists():
        raise FileNotFoundError(session_path)

    events = load_trace(trace_path)
    validation = validate_trace(trace_path, session_path, allow_drops=allow_drops)
    summary = summarize_trace(events)
    coverage = evaluate_coverage(events)
    identity = safe_identity(session_dir / "bzrnet_capture_identity.json")

    return {
        "validEvidence": validation["valid"],
        "validation": validation,
        "traceSummary": summary,
        "coverage": coverage,
        "captureIdentity": identity,
        "nextAction": (
            "If this is a paired /iprelay capture and UDP 1339 is observed on both clients, run correlate_bzrnet_wire.py on each bundle, then align_bzrnet_traces.py across the pair."
            if any(row["scenario"] == "UDP 1339 relay wire" and row["status"] == "OBSERVED" for row in coverage["checks"])
            else "Continue the targeted capture matrix; do not repeat already-observed scenarios unless evidence quality was invalid."
        ),
    }


def print_text(report: dict[str, Any]) -> None:
    validation = report["validation"]
    summary = report["traceSummary"]
    coverage = report["coverage"]
    identity = report.get("captureIdentity") or {}
    print(
        f"evidence={'VALID' if report['validEvidence'] else 'INVALID'} "
        f"platform={identity.get('platform', 'unknown')} records={summary['records']} "
        f"ws={validation['websocketMessages']} dropped={validation['droppedEvents']}"
    )
    print(f"coverage observed={coverage['observed']} partial={coverage['partial']} not_seen={coverage['notSeen']}")
    if validation["warnings"]:
        for warning in validation["warnings"]:
            print(f"WARNING: {warning}")
    if validation["errors"]:
        for error in validation["errors"]:
            print(f"ERROR: {error}")
    print("capture_matrix:")
    for row in coverage["checks"]:
        print(f"  {row['status']:9s} {row['scenario']}")
    print(f"NEXT: {report['nextAction']}")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("session_dir", type=Path)
    parser.add_argument("--allow-drops", action="store_true")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()

    report = build_report(args.session_dir, allow_drops=args.allow_drops)
    if args.json:
        print(json.dumps(report, indent=2, sort_keys=True))
    else:
        print_text(report)
    raise SystemExit(0 if report["validEvidence"] else 1)


if __name__ == "__main__":
    main()
