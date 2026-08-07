#!/usr/bin/env python3
"""Score a native BZRNet trace against the targeted protocol capture matrix."""

from __future__ import annotations

import argparse
import json
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Callable

from analyze_bzrnet_trace import details, load_trace


@dataclass(frozen=True)
class Check:
    name: str
    required: tuple[str, ...] = ()
    any_of: tuple[str, ...] = ()
    predicate: Callable[[list[dict[str, Any]]], bool] | None = None
    note: str = ""


def message_set(events: list[dict[str, Any]]) -> set[str]:
    return {
        str(event.get("messageType"))
        for event in events
        if event.get("event") in {"BZR_WS_TX", "BZR_WS_RX"} and event.get("messageType")
    }


def has_udp_port(events: list[dict[str, Any]], port: int, direction: str | None = None) -> bool:
    for event in events:
        if event.get("event") not in {"UDP_WIRE_TX", "UDP_WIRE_RX"}:
            continue
        if direction and event.get("direction") != direction:
            continue
        if details(event).get("port") == port:
            return True
    return False


def has_reason(events: list[dict[str, Any]], *, success: bool) -> bool:
    for event in events:
        if event.get("messageType") not in {"OnLobbyJoined", "OnFailure"}:
            continue
        d = details(event)
        reason = d.get("reasonCode")
        success_value = d.get("success")
        if success and (reason == 0 or success_value is True):
            return True
        if not success and ((isinstance(reason, int) and reason != 0) or success_value is False):
            return True
    return False


CHECKS = [
    Check("Authorization + initial bootstrap", ("Authorization", "OnAuthorization")),
    Check("Enter lounge", ("DoEnterLounge",)),
    Check("Exit lounge", ("DoExitLounge",), any_of=("OnDoExitLounge",)),
    Check("Lobby list/snapshot", any_of=("OnLobbyListChanged", "OnLobbyChanged")),
    Check("Create public/private lobby or game", any_of=("CreateLobby", "CreateGame"), note="Privacy mode intentionally hides password contents."),
    Check("Successful join", ("DoJoinLobby",), predicate=lambda e: has_reason(e, success=True)),
    Check("Observed join/failure reasonCode", predicate=lambda e: has_reason(e, success=False), note="Scenario meaning still requires controlled UI notes."),
    Check("Lobby metadata set", ("SetLobbyData",)),
    Check("Lobby metadata delete", ("DeleteLobbyData",)),
    Check("Player metadata set", ("SetPlayerData",)),
    Check("Member limit change", ("SetLobbyMemberLimit",)),
    Check("Lock/unlock request", ("LockLobby",)),
    Check("Owner transfer", ("DoSetLobbyOwner",)),
    Check("Kick", ("DoKickUser",)),
    Check("Chat", ("DoSendChat", "OnChatMessage")),
    Check("WAN update", ("DoUpdateWAN", "OnWANUpdated")),
    Check("LAN update", ("DoUpdateLAN", "OnLANUpdated")),
    Check("P2P connect control", ("DoP2PConnect", "OnLobbyMemberP2PConnect")),
    Check("Relay route allocation control", ("DoP2PRoute", "OnP2PRoute")),
    Check("UDP 1338 endpoint discovery wire", predicate=lambda e: has_udp_port(e, 1338, "outbound") and has_udp_port(e, 1338, "inbound")),
    Check("UDP 1339 relay wire", predicate=lambda e: has_udp_port(e, 1339, "outbound") and has_udp_port(e, 1339, "inbound")),
    Check("Relay engine boundary", any_of=("PRE_RELAY_ENCAP", "POST_RELAY_DECAP"), note="Not expected until validated engine relay hooks are implemented."),
    Check("Server shutdown event", ("OnServerShutdown",), note="Only naturally observable if official service emits it."),
]


def evaluate(events: list[dict[str, Any]]) -> dict[str, Any]:
    messages = message_set(events)
    rows: list[dict[str, Any]] = []
    observed = 0
    partial = 0
    for check in CHECKS:
        required_hits = [name for name in check.required if name in messages]
        any_hits = [name for name in check.any_of if name in messages]
        predicate_hit = check.predicate(events) if check.predicate else None

        required_ok = not check.required or len(required_hits) == len(check.required)
        any_ok = not check.any_of or bool(any_hits)
        predicate_ok = check.predicate is None or bool(predicate_hit)
        complete = required_ok and any_ok and predicate_ok

        had_evidence = bool(required_hits or any_hits or predicate_hit)
        if complete:
            status = "OBSERVED"
            observed += 1
        elif had_evidence:
            status = "PARTIAL"
            partial += 1
        else:
            status = "NOT_SEEN"

        rows.append({
            "scenario": check.name,
            "status": status,
            "requiredSeen": required_hits,
            "alternativeSeen": any_hits,
            "note": check.note,
        })

    return {
        "observed": observed,
        "partial": partial,
        "notSeen": len(CHECKS) - observed - partial,
        "checks": rows,
        "importantCaveat": "This is trace coverage, not proof of semantic parity. Failure-code meaning, direct/LAN/WAN selection, relay framing, and engine state require controlled scenario evidence and/or validated semantic hooks.",
    }


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("trace", type=Path, help="bzrnet_trace.jsonl")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()

    report = evaluate(load_trace(args.trace))
    if args.json:
        print(json.dumps(report, indent=2, sort_keys=True))
        return

    print(f"observed={report['observed']} partial={report['partial']} not_seen={report['notSeen']}")
    for row in report["checks"]:
        print(f"{row['status']:9s} {row['scenario']}")
        if row["note"]:
            print(f"           note: {row['note']}")
    print(f"CAVEAT: {report['importantCaveat']}")


if __name__ == "__main__":
    main()
