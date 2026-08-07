#!/usr/bin/env python3
"""Semantic comparison of official-service and replacement BZRNet native traces."""

from __future__ import annotations

import argparse
import collections
import json
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any

from analyze_bzrnet_trace import details, load_trace, parse_message


IGNORED_MESSAGE_TYPES = {"OnHeartbeat"}
# These are server broadcasts whose relative ordering may legitimately vary
# while the client's causal request/reply sequence remains equivalent. They are
# compared as semantic multisets inside the gap between adjacent strict events.
ASYNC_MESSAGE_TYPES = {
    "OnLANUpdated",
    "OnWANUpdated",
    "OnLobbyListChanged",
    "OnLobbyChanged",
    "OnLobbyDataChanged",
    "OnUserDataChanged",
    "OnLobbyMemberListChanged",
    "OnWhitelistUpdated",
}
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


def canonical(row: dict[str, Any]) -> str:
    return json.dumps(row, sort_keys=True, separators=(",", ":"), ensure_ascii=False)


def partition_sequence(rows: list[dict[str, Any]]) -> tuple[list[dict[str, Any]], list[list[dict[str, Any]]]]:
    """Return strict events plus async broadcast gaps.

    async_gaps[0] is before the first strict event, async_gaps[1] lies between
    strict events 0 and 1, and the final gap follows the last strict event.
    This tolerates harmless reordering of broadcasts without allowing one to
    drift across a causal client request/reply boundary unnoticed.
    """
    strict: list[dict[str, Any]] = []
    gaps: list[list[dict[str, Any]]] = [[]]
    for row in rows:
        if str(row.get("messageType", "")) in ASYNC_MESSAGE_TYPES:
            gaps[-1].append(row)
        else:
            strict.append(row)
            gaps.append([])
    return strict, gaps


def compare_sequences(official: list[dict[str, Any]], replacement: list[dict[str, Any]]) -> dict[str, Any]:
    """Compare client-observable semantics with controlled async tolerance.

    Causal/non-broadcast events remain strictly ordered and value-sensitive.
    Known asynchronous broadcasts may reorder only within the same gap between
    strict events. Object-key ordering, generated identity-like values, and the
    explicitly variable protocol fields are normalized upstream. Missing fields,
    wrong values, reason-code differences, and messages crossing causal gaps are
    still reported as mismatches.
    """
    official_strict, official_gaps = partition_sequence(official)
    replacement_strict, replacement_gaps = partition_sequence(replacement)

    strict_mismatches: list[dict[str, Any]] = []
    common = min(len(official_strict), len(replacement_strict))
    for index in range(common):
        if official_strict[index] != replacement_strict[index]:
            strict_mismatches.append({
                "index": index,
                "official": official_strict[index],
                "replacement": replacement_strict[index],
            })
    if len(official_strict) != len(replacement_strict):
        strict_mismatches.append({
            "index": common,
            "officialRemaining": official_strict[common:],
            "replacementRemaining": replacement_strict[common:],
        })

    async_mismatches: list[dict[str, Any]] = []
    gap_count = max(len(official_gaps), len(replacement_gaps))
    for gap_index in range(gap_count):
        official_gap = official_gaps[gap_index] if gap_index < len(official_gaps) else []
        replacement_gap = replacement_gaps[gap_index] if gap_index < len(replacement_gaps) else []
        official_counter = collections.Counter(canonical(row) for row in official_gap)
        replacement_counter = collections.Counter(canonical(row) for row in replacement_gap)
        if official_counter == replacement_counter:
            continue
        missing = list((official_counter - replacement_counter).elements())
        extra = list((replacement_counter - official_counter).elements())
        async_mismatches.append({
            "gapIndex": gap_index,
            "missingFromReplacement": [json.loads(row) for row in missing],
            "extraInReplacement": [json.loads(row) for row in extra],
        })

    passed = not strict_mismatches and not async_mismatches
    return {
        "pass": passed,
        "officialCount": len(official),
        "replacementCount": len(replacement),
        "officialStrictCount": len(official_strict),
        "replacementStrictCount": len(replacement_strict),
        "strictMismatches": strict_mismatches,
        "asyncMismatches": async_mismatches,
        # Compatibility field for older callers.
        "mismatches": strict_mismatches + async_mismatches,
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
        print(
            f"{status}: official_messages={report['officialCount']} "
            f"replacement_messages={report['replacementCount']} "
            f"strict_mismatches={len(report['strictMismatches'])} "
            f"async_mismatches={len(report['asyncMismatches'])}"
        )
        for mismatch in report["mismatches"][:20]:
            print(json.dumps(mismatch, indent=2, sort_keys=True))
    raise SystemExit(0 if report["pass"] else 1)


if __name__ == "__main__":
    main()
