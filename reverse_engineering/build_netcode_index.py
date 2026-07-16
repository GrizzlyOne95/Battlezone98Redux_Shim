"""Build a focused, reproducible index over the repo's full decompilation corpora.

The current Redux binary is completely decompiled but mostly unnamed.  This
tool classifies the first-party networking ranges and optionally adds a bounded
static call closure, without copying tens of thousands of decompiler outputs.
"""

from __future__ import annotations

import argparse
import csv
import json
import re
from collections import deque
from dataclasses import dataclass
from pathlib import Path


REPO = Path(__file__).resolve().parents[1]
CORPUS = REPO / "reverse_engineering/repo_corpora/bzr_gog_best_effort"
DECOMPS = CORPUS / "ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps"
LEGACY_INDEX = REPO / "reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/function_index.tsv"
STRINGS = CORPUS / "binary_strings/ascii_strings.csv"
ADDRESS_RE = re.compile(r"-([0-9a-fA-F]{8})\.c$")
CALL_RE = re.compile(r"\b(?:FUN|Catch|Catch_All)@?_?([0-9a-fA-F]{8})\b")


@dataclass(frozen=True)
class Range:
    category: str
    start: int
    end: int
    rationale: str


RANGES = (
    Range("game_transport", 0x0056F0F0, 0x00579DC0, "Net/NetPlayer gameplay packets, sync, ping, bandwidth and host migration"),
    Range("bzrnet_control", 0x006BE3E0, 0x006C83F0, "WebSocket client adapter, JSON messages, endpoint discovery and UDP listener"),
    Range("platform_auth", 0x0073B130, 0x0073CFFF, "Steam/Galaxy authentication and platform callbacks"),
    Range("matchmaking", 0x0073D020, 0x00751560, "CNetGameLobby plus BZRNet, Galaxy and Steam lobby backends"),
    Range("peer_transport", 0x00758C90, 0x00763C90, "BZRNet direct LAN/WAN/relay plus Galaxy/Steam P2P adapters"),
    Range("multiplayer_ui", 0x0078E000, 0x007A2000, "Multiplayer readiness, lobby and create/join UI"),
    Range("startup_config", 0x007D5120, 0x007D5120, "BZRNet URL and /ipdirect, /iprelay, /bzrnetport option setup"),
)

ANCHOR_RE = re.compile(
    r"BZRNet|CNetGameLobby|NetPlayer|Net::|P2P|Lobby|Lounge|"
    r"DoJoinLobby|CreateLobby|SetLobbyData|SetPlayerData|WebSocket",
    re.IGNORECASE,
)
LEGACY_RE = re.compile(r"^(?:Net|NetPlayer)(?:::|$)|^NetPlayer_", re.IGNORECASE)


def address_of(path: Path) -> int | None:
    match = ADDRESS_RE.search(path.name)
    return int(match.group(1), 16) if match else None


def category_of(address: int) -> str | None:
    for item in RANGES:
        if item.start <= address <= item.end:
            return item.category
    return None


def current_functions(call_depth: int) -> list[dict[str, object]]:
    by_address = {
        address: path
        for path in DECOMPS.glob("*.c")
        if (address := address_of(path)) is not None
    }
    selected: dict[int, tuple[str, int]] = {}
    queue: deque[tuple[int, int]] = deque()
    for address in sorted(by_address):
        category = category_of(address)
        if category:
            selected[address] = (category, 0)
            queue.append((address, 0))

    while queue:
        address, depth = queue.popleft()
        if depth >= call_depth:
            continue
        text = by_address[address].read_text(encoding="utf-8", errors="replace")
        for match in CALL_RE.finditer(text):
            target = int(match.group(1), 16)
            if target in by_address and target not in selected:
                selected[target] = ("dependency", depth + 1)
                queue.append((target, depth + 1))

    rows = []
    for address, (category, depth) in sorted(selected.items()):
        path = by_address[address]
        rows.append({
            "address": f"0x{address:08X}",
            "category": category,
            "dependency_depth": depth,
            "path": path.relative_to(REPO).as_posix(),
        })
    return rows


def legacy_functions() -> list[dict[str, str]]:
    rows: list[dict[str, str]] = []
    with LEGACY_INDEX.open(encoding="utf-8", errors="replace", newline="") as source:
        reader = csv.reader(source, delimiter="\t")
        for fields in reader:
            if len(fields) < 3 or fields[0] == "address":
                continue
            name = fields[1]
            namespace = fields[2]
            if LEGACY_RE.search(name) or LEGACY_RE.search(namespace):
                rows.append({"address": f"0x{int(fields[0], 16):08X}", "name": name, "namespace": namespace})
    return rows


def protocol_strings() -> list[dict[str, str]]:
    rows: list[dict[str, str]] = []
    with STRINGS.open(encoding="utf-8", errors="replace", newline="") as source:
        for item in csv.DictReader(source):
            if ANCHOR_RE.search(item["text"]):
                rows.append({
                    "va": f"0x{int(item['rva']) + 0x400000:08X}",
                    "section": item["section"],
                    "text": item["text"],
                })
    return rows


def write_outputs(output: Path, current: list[dict], legacy: list[dict], strings: list[dict], depth: int) -> None:
    output.mkdir(parents=True, exist_ok=True)
    for name, rows in (("current_functions.csv", current), ("legacy_functions.csv", legacy), ("protocol_strings.csv", strings)):
        with (output / name).open("w", encoding="utf-8", newline="") as target:
            writer = csv.DictWriter(target, fieldnames=list(rows[0]) if rows else ["empty"])
            writer.writeheader()
            writer.writerows(rows)
    manifest = {
        "binary_sha256": "8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413",
        "full_decompile_function_count": 31948,
        "call_dependency_depth": depth,
        "counts": {"current": len(current), "legacy": len(legacy), "protocol_strings": len(strings)},
        "ranges": [item.__dict__ | {"start": f"0x{item.start:08X}", "end": f"0x{item.end:08X}"} for item in RANGES],
    }
    (output / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--call-depth", type=int, default=1, choices=range(0, 4))
    parser.add_argument("--output-dir", type=Path, help="Optional directory for CSV/JSON indexes")
    args = parser.parse_args()
    current = current_functions(args.call_depth)
    legacy = legacy_functions()
    strings = protocol_strings()
    summary = {"current": len(current), "legacy": len(legacy), "protocol_strings": len(strings)}
    print(json.dumps(summary, indent=2))
    if args.output_dir:
        write_outputs(args.output_dir, current, legacy, strings, args.call_depth)


if __name__ == "__main__":
    main()
