#!/usr/bin/env python3
"""Semantic comparison of official-service and replacement BZRNet native traces."""

from __future__ import annotations

import argparse
import json
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any

from analyze_bzrnet_trace import details, load_trace, parse_message


IGNORED_MESSAGE_TYPES = {"OnHeartbeat"}
VARIABLE_KEYS = {"time", "steamAppTicket", "gogAppTicket", "authTicket", "platformTicket", "wanAddress", "lanAddresses"}
IDENTITY_KEYS = {"userId", "player", "owner", "speakerId", "member", "realname"}
LOBBY_KEYS = {"lobbyId", "lobby"}
ROUTE_KEYS = {"routeId", "route", "sessionId"}


@dataclass
class AliasState:
    tables: dict[str, dict[str, str]] = field(default_factory=lambda: {"player": {}, "lobby": {}, "route": {}})

    def alias(self, family: str, value: Any) -> Any:
        if value is None or isinstance(value, (bool, int, float)):
            return value
        key = json.dumps(value, sort_keys=True, separators=(",", ":")) if not isinstance(value, str) else value
        table = self.tables[family]
        if key not in table:
            table[key] = f"{family}_{len(table) + 1}"
        return table[key]


def normalize(value: Any, aliases: AliasState, parent_key: str | None = None) -> Any:
    if parent_key in VARIABLE_KEYS:
        return f"<{parent_key}>"
    if parent_key in IDENTITY_KEYS:
        return aliases.alias("player", value)
    if parent_key in LOBBY_KEYS and not isinstance(value, dict):
        return aliases.alias("lobby", value)
    if parent_key in ROUTE_KEYS and not isinstance(value, dict):
        return aliases.alias("route", value)
    if isinstance(value, dict):
        return {key: normalize(child, aliases, key) for key, child in sorted(value.items())}
    if isinstance(value, list):
        return [normalize(child, aliases, parent_key) for child in value]
    return value


def semantic_messages(path: Path, *, include_heartbeats: bool = False) -> list[dict[str, Any]]:
    aliases = AliasState()
    rows: list[dict[str, Any]] = []
    for event in load_trace(path):
        if event.get("event") not in {"BZR_WS_TX", "BZR_WS_RX"}:
            continue
        message_type = str(event.get("messageType", ""))
        if not include_heartbeats and message_type in IGNORED_MESSAGE_TYPES:
            continue
        message = parse_message(event)
        rows.append({
            "direction": event.get("direction"),
            "messageType": message_type,
            "message": normalize(message, aliases) if message is not None else None,
            "reasonCode": details(event).get("reasonCode"),
            "success": details(event).get("success"),
        })
    return rows


def compare_sequences(official: list[dict[str, Any]], replacement: list[dict[str, Any]]) -> dict[str, Any]:
    """Compare client-observable message semantics, not raw JSONL lines.

    Heartbeats are ignored by default and JSON object-key ordering/identity-like
    values are normalized. Meaningful missing/extra messages, fields, reason
    codes and success values remain mismatches.
    """
    mismatches: list[dict[str, Any]] = []
    common = min(len(official), len(replacement))
    for index in range(common):
        if official[index] != replacement[index]:
            mismatches.append({"index": index, "official": official[index], "replacement": replacement[index]})
    if len(official) != len(replacement):
        mismatches.append({
            "index": common,
            "officialRemaining": official[common:],
            "replacementRemaining": replacement[common:],
        })
    return {
        "pass": not mismatches,
        "officialCount": len(official),
        "replacementCount": len(replacement),
        "mismatches": mismatches,
    }


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("official", type=Path)
    parser.add_argument("replacement", type=Path)
    parser.add_argument("--include-heartbeats", action="store_true")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    official = semantic_messages(args.official, include_heartbeats=args.include_heartbeats)
    replacement = semantic_messages(args.replacement, include_heartbeats=args.include_heartbeats)
    report = compare_sequences(official, replacement)
    if args.json:
        print(json.dumps(report, indent=2, sort_keys=True))
    else:
        status = "PASS" if report["pass"] else "FAIL"
        print(f"{status}: official_messages={report['officialCount']} replacement_messages={report['replacementCount']}")
        for mismatch in report["mismatches"][:20]:
            print(json.dumps(mismatch, indent=2, sort_keys=True))
    raise SystemExit(0 if report["pass"] else 1)


if __name__ == "__main__":
    main()
