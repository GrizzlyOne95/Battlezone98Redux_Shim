"""Report which chunk manifest pieces resolve to a payload, and which do not.

This mirrors, offline, the lookup that TryResolveChunkPayloadMeshResourceForMeshAndGeom
performs in `src/patches/bzr_hooks.cpp`, so a piece listed as unresolved here is
one that falls through to a generic placeholder in game.

Plain CPython, no Blender required:

    python scripts/audit_chunk_payload_coverage.py
    python scripts/audit_chunk_payload_coverage.py --payload-root <dir> --verbose
"""

from __future__ import annotations

import argparse
import re
import sys
from collections import defaultdict
from pathlib import Path
from typing import Dict, List, Optional, Sequence, Set, Tuple

REPO_ROOT = Path(__file__).resolve().parents[1]
DEFAULT_MANIFEST = REPO_ROOT / "scripts" / "chunk_geo_manifest.txt"
DEFAULT_PAYLOAD_ROOT = (
    REPO_ROOT / "reverse_engineering" / "generated_chunk_payload_meshes_stock"
)

# Geo types that actually render. Everything else in the manifest is a marker
# (lights, POV, hardpoints); those spawn generic chunklets and never resolve a
# named payload, so they are counted separately rather than reported as gaps.
RENDERABLE_GEO_TYPES = {60, 61, 65, 66, 67, 81}

# Mirrors kSuppressedChunkPieces in src/patches/bzr_hooks.cpp: pieces the
# simulation fragments but the Redux model has no geometry for, deliberately
# drawn as nothing rather than as invented debris.
SUPPRESSED_PIECES = {
    ("abhang", "abh11drc"),
    ("abhang", "abh11drd"),
    ("abhang", "abh11bli"),
    ("abspow", "asp11bul"),
    ("bbspow", "asp11bul"),
}


def parse_manifest(path: Path) -> List[Tuple[str, str, int]]:
    rows: List[Tuple[str, str, int]] = []
    for line in path.read_text(encoding="latin-1").splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        fields = line.split("|")
        if len(fields) < 4:
            continue
        try:
            geo_type = int(fields[3])
        except ValueError:
            continue
        rows.append((fields[0].lower(), fields[1].lower(), geo_type))
    return rows


def load_payload_index(root: Path) -> Tuple[Dict[str, Set[str]], Set[str]]:
    per_craft = {
        entry.name.lower(): {p.stem.lower() for p in entry.glob("*.mesh")}
        for entry in root.iterdir()
        if entry.is_dir()
    }
    flat = {p.stem.lower() for p in root.glob("*.mesh")}
    return per_craft, flat


def resolve(
    craft: str,
    geo: str,
    per_craft: Dict[str, Set[str]],
    flat: Set[str],
) -> Optional[str]:
    """Name the rule that resolves this piece, or None if nothing does."""
    stems = per_craft.get(craft, set())

    if geo in stems:
        return "direct"
    if f"{craft}_{geo}" in stems:
        return "prefixed"

    # Punctuation-insensitive match, scoped to the craft directory and requiring
    # a unique hit -- ablpad's alp11_bda bone against the sim's alp11bda.
    wanted = re.sub(r"[^a-z0-9]", "", geo)
    if wanted:
        relaxed = [
            stem
            for stem in stems
            if stem != geo and re.sub(r"[^a-z0-9]", "", stem) == wanted
        ]
        if len(relaxed) == 1:
            return f"relaxed->{relaxed[0]}"

    # Suffix translation, scoped to the craft directory and requiring a unique
    # hit -- the bbhang abh11* -> bbh11* and bbsilo bss11* -> ass11* cases.
    if len(geo) > 4:
        matches = [
            stem
            for stem in stems
            if len(stem) == len(geo) and stem[3:] == geo[3:] and stem[:3] != geo[:3]
        ]
        if len(matches) == 1:
            return f"suffix->{matches[0]}"

    if geo in flat:
        return "flat"
    if geo in per_craft and geo in per_craft[geo]:
        return "geo-as-dir"
    return None


def main(argv: Sequence[str]) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--manifest", type=Path, default=DEFAULT_MANIFEST)
    parser.add_argument("--payload-root", type=Path, default=DEFAULT_PAYLOAD_ROOT)
    parser.add_argument(
        "--verbose",
        action="store_true",
        help="Also list payload files that no manifest piece can reach",
    )
    args = parser.parse_args(argv)

    if not args.manifest.exists():
        print(f"manifest not found: {args.manifest}", file=sys.stderr)
        return 2
    if not args.payload_root.exists():
        print(f"payload root not found: {args.payload_root}", file=sys.stderr)
        return 2

    rows = parse_manifest(args.manifest)
    per_craft, flat = load_payload_index(args.payload_root)

    by_rule: Dict[str, int] = defaultdict(int)
    unresolved_renderable: List[Tuple[str, str, int]] = []
    unresolved_markers = 0

    for craft, geo, geo_type in rows:
        if (craft, geo) in SUPPRESSED_PIECES:
            by_rule["suppressed"] += 1
            continue
        rule = resolve(craft, geo, per_craft, flat)
        if rule:
            by_rule[rule.split("->")[0]] += 1
        elif geo_type in RENDERABLE_GEO_TYPES:
            unresolved_renderable.append((craft, geo, geo_type))
        else:
            unresolved_markers += 1

    print(f"manifest pieces       : {len(rows)}")
    print(f"payload directories   : {len(per_craft)}")
    print()
    print("resolved by rule:")
    for rule, count in sorted(by_rule.items(), key=lambda item: -item[1]):
        print(f"  {rule:<12} {count}")
    print()
    print(f"UNRESOLVED renderable : {len(unresolved_renderable)}")
    print(f"unresolved markers    : {unresolved_markers} (expected; no payload needed)")

    if unresolved_renderable:
        print("\n--- renderable pieces that fall through to a placeholder ---")
        grouped: Dict[str, List[str]] = defaultdict(list)
        for craft, geo, geo_type in unresolved_renderable:
            grouped[craft].append(f"{geo}({geo_type})")
        for craft in sorted(grouped):
            state = "dir exists" if craft in per_craft else "NO PAYLOAD DIR"
            print(f"  {craft:<10} [{state}] {', '.join(sorted(grouped[craft]))}")

    if args.verbose:
        reachable: Dict[str, Set[str]] = defaultdict(set)
        for craft, geo, _geo_type in rows:
            rule = resolve(craft, geo, per_craft, flat)
            if rule == "direct":
                reachable[craft].add(geo)
            elif rule == "prefixed":
                reachable[craft].add(f"{craft}_{geo}")
            elif rule and ("->" in rule):
                reachable[craft].add(rule.split("->")[1])

        orphans: Dict[str, List[str]] = defaultdict(list)
        total = 0
        for craft, stems in per_craft.items():
            for stem in sorted(stems - reachable.get(craft, set())):
                orphans[craft].append(stem)
                total += 1
        print(f"\n--- payload files no manifest piece reaches: {total} ---")
        for craft in sorted(orphans):
            print(f"  {craft:<10} {', '.join(orphans[craft])}")

    return 1 if unresolved_renderable else 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
