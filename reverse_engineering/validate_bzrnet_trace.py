#!/usr/bin/env python3
"""Validate OpenShim BZRNet evidence integrity, redaction, and trace health."""

from __future__ import annotations

import argparse
import json
from pathlib import Path
from typing import Any

from analyze_bzrnet_trace import details, load_trace


SECRET_KEYS = {"steamAppTicket", "gogAppTicket", "authTicket", "platformTicket", "password"}
IDENTITY_KEYS = {"userId", "player", "speakerId", "owner", "member", "realname", "name"}
ENDPOINT_KEYS = {"wanAddress"}


def walk(value: Any, path: str = "$"):
    if isinstance(value, dict):
        for key, child in value.items():
            child_path = f"{path}.{key}"
            yield key, child, child_path
            yield from walk(child, child_path)
    elif isinstance(value, list):
        for index, child in enumerate(value):
            yield from walk(child, f"{path}[{index}]")


def validate_message_json(message: Any, private_forensic: bool, event_seq: int) -> list[str]:
    errors: list[str] = []
    if not isinstance(message, dict):
        return errors
    for key, value, path in walk(message):
        if key in SECRET_KEYS:
            if value != "<REDACTED>":
                errors.append(f"seq {event_seq}: secret field {path} is not redacted")
            continue
        if private_forensic or not isinstance(value, str) or not value:
            continue
        if key in IDENTITY_KEYS and not value.startswith(("player_", "identity_")):
            errors.append(f"seq {event_seq}: sanitized identity field {path} is not aliased")
        if key in ENDPOINT_KEYS and not value.startswith("endpoint_"):
            errors.append(f"seq {event_seq}: sanitized endpoint field {path} is not aliased")
        if key == "lanAddresses":
            # Handled below as a list; retain this branch for malformed strings.
            if isinstance(value, str) and not value.startswith("endpoint_"):
                errors.append(f"seq {event_seq}: sanitized LAN endpoint {path} is not aliased")
    for key, value, path in walk(message):
        if private_forensic or key != "lanAddresses" or not isinstance(value, list):
            continue
        for index, endpoint in enumerate(value):
            if isinstance(endpoint, str) and endpoint and not endpoint.startswith("endpoint_"):
                errors.append(f"seq {event_seq}: sanitized LAN endpoint {path}[{index}] is not aliased")
    return errors


def validate_trace(trace_path: Path, session_path: Path | None, allow_drops: bool = False) -> dict[str, Any]:
    events = load_trace(trace_path)
    session: dict[str, Any] = {}
    if session_path:
        parsed = json.loads(session_path.read_text(encoding="utf-8"))
        if not isinstance(parsed, dict):
            raise ValueError("session JSON must be an object")
        session = parsed

    private_forensic = bool(session.get("privateForensic", False))
    errors: list[str] = []
    warnings: list[str] = []
    capture_ids: set[str] = set()
    process_ids: set[int] = set()
    previous_seq: int | None = None
    dropped_total = 0
    websocket_messages = 0
    unknown_messages = 0

    for index, event in enumerate(events, 1):
        seq = event.get("seq")
        if not isinstance(seq, int):
            errors.append(f"record {index}: missing/integer-invalid seq")
            continue
        if previous_seq is not None and seq <= previous_seq:
            errors.append(f"seq {seq}: sequence is not strictly increasing after {previous_seq}")
        previous_seq = seq

        capture_id = event.get("captureId")
        if isinstance(capture_id, str) and capture_id:
            capture_ids.add(capture_id)
        else:
            errors.append(f"seq {seq}: missing captureId")

        process_id = event.get("processId")
        if isinstance(process_id, int):
            process_ids.add(process_id)
        else:
            errors.append(f"seq {seq}: missing/integer-invalid processId")

        qpc = event.get("qpc")
        qpc_frequency = event.get("qpcFrequency")
        if not isinstance(qpc, int) or not isinstance(qpc_frequency, int) or qpc_frequency <= 0:
            errors.append(f"seq {seq}: invalid QPC clock fields")

        d = details(event)
        if event.get("event") == "TRACE_DROPPED_EVENTS":
            delta = d.get("droppedSinceLastReport", 0)
            if isinstance(delta, int) and delta > 0:
                dropped_total += delta

        if event.get("event") in {"BZR_WS_TX", "BZR_WS_RX"}:
            websocket_messages += 1
            if d.get("knownMessage") is False:
                unknown_messages += 1
            text = d.get("messageJson")
            if not isinstance(text, str):
                errors.append(f"seq {seq}: WebSocket semantic event missing messageJson")
                continue
            try:
                message = json.loads(text)
            except json.JSONDecodeError as exc:
                errors.append(f"seq {seq}: messageJson is invalid JSON: {exc}")
                continue
            errors.extend(validate_message_json(message, private_forensic, seq))

    if len(capture_ids) > 1:
        errors.append(f"trace contains multiple captureId values: {len(capture_ids)}")
    if len(process_ids) > 1:
        errors.append(f"trace contains multiple processId values: {len(process_ids)}")

    if session:
        session_capture_id = session.get("captureId")
        if capture_ids and session_capture_id not in capture_ids:
            errors.append("session captureId does not match trace captureId")
        session_process_id = session.get("processId")
        if process_ids and session_process_id not in process_ids:
            errors.append("session processId does not match trace processId")
        calibration = session.get("clockCalibration")
        if not isinstance(calibration, dict) or int(calibration.get("qpcFrequency", 0) or 0) <= 0:
            errors.append("session clockCalibration is missing or invalid")
        if session.get("writerShutdownClean") is not True:
            errors.append("session writerShutdownClean is not true")
        session_drops = session.get("droppedEvents")
        if isinstance(session_drops, int):
            dropped_total = max(dropped_total, session_drops)

    if dropped_total:
        message = f"trace reports {dropped_total} dropped event(s)"
        if allow_drops:
            warnings.append(message)
        else:
            errors.append(message)

    if unknown_messages:
        warnings.append(f"trace preserved {unknown_messages} unknown BZRNet message(s); review before declaring parity")
    if websocket_messages == 0:
        warnings.append("trace contains no BZRNet WebSocket semantic messages")

    return {
        "valid": not errors,
        "records": len(events),
        "websocketMessages": websocket_messages,
        "unknownMessages": unknown_messages,
        "droppedEvents": dropped_total,
        "privateForensic": private_forensic,
        "errors": errors,
        "warnings": warnings,
    }


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("trace", type=Path, help="bzrnet_trace.jsonl")
    parser.add_argument("--session", type=Path, help="bzrnet_session.json")
    parser.add_argument("--allow-drops", action="store_true", help="downgrade dropped events from error to warning")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()

    report = validate_trace(args.trace, args.session, allow_drops=args.allow_drops)
    if args.json:
        print(json.dumps(report, indent=2, sort_keys=True))
    else:
        print(
            f"{'PASS' if report['valid'] else 'FAIL'}: records={report['records']} "
            f"ws={report['websocketMessages']} unknown={report['unknownMessages']} "
            f"dropped={report['droppedEvents']}"
        )
        for warning in report["warnings"]:
            print(f"WARNING: {warning}")
        for error in report["errors"]:
            print(f"ERROR: {error}")
    raise SystemExit(0 if report["valid"] else 1)


if __name__ == "__main__":
    main()
