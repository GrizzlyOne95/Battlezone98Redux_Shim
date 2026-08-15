"""Recover Redux payload -> simulation piece names by matching legacy geometry.

Some Redux models bind their geometry to exporter node names (`hbhydr1_polymsh7`)
rather than the names the simulation fragments (`hhy11bdg`), so their payloads
resolve to nothing and every chunk becomes a placeholder. The Hadean relic
buildings are the largest group.

Legacy Battlezone ships one `.geo` per simulation piece, named exactly what the
simulation asks for, so it is ground truth for what each piece should look like.
This matches the two sides by bounding box and reports the mapping with a
confidence margin.

Redux remodelled these assets at higher detail, so bounding boxes agree to a few
percent rather than exactly. Calibration against pieces whose mapping is already
known -- ablpad's alp11_bda at 0.9%, obcurt/oblemb/hbspln at 0.0% -- puts a
correct match well under 12%, and the runner-up margin is what separates a real
match from a coincidence.

    python scripts/match_legacy_chunk_pieces.py --stock-root <BZ1_install>/stock
    python scripts/match_legacy_chunk_pieces.py --stock-root ... --craft hbhydr
"""

from __future__ import annotations

import argparse
import re
import struct
import sys
from pathlib import Path
from typing import Dict, List, Optional, Sequence, Tuple

REPO_ROOT = Path(__file__).resolve().parents[1]
DEFAULT_MANIFEST = REPO_ROOT / "scripts" / "chunk_geo_manifest.txt"
DEFAULT_PAYLOAD_ROOT = (
    REPO_ROOT / "reverse_engineering" / "generated_chunk_payload_meshes_stock"
)

RENDERABLE_GEO_TYPES = {60, 61, 65, 66, 67, 81}

# Payload stems that are markers rather than body geometry: POV cameras,
# hardpoints (gc1/gm1/gr1/gs1) and light billboards. Matching a hull piece onto
# one of these renders a flat sprite where a chunk should be, which is worse
# than the generic placeholder it replaces, so they are never match candidates.
# Piece codes are the trailing three characters of a <craft>11<code> name, so
# match the suffix rather than a delimited word: hat11pov and stu11pov are
# markers just as much as a standalone "pov" would be.
MARKER_STEM_PATTERN = re.compile(
    r"(?:(?:pov|g[cmrs]\d)$|hlgt|(?:^|[^a-z0-9])lgt\d*(?:$|[^a-z0-9]))",
    re.IGNORECASE,
)

Dims = Tuple[float, float, float]


# --- Ogre .mesh (payload side) ------------------------------------------------

def _chunks(data: bytes, offset: int, end: int):
    while offset + 6 <= end:
        chunk_id, length = struct.unpack_from("<HI", data, offset)
        if length < 6 or offset + length > end:
            return
        yield chunk_id, offset + 6, offset + length
        offset += length


def mesh_dims(path: Path) -> Optional[Dims]:
    """Bounding box of a single-submesh payload mesh."""
    data = path.read_bytes()
    try:
        offset = data.index(b"\n") + 1
        chunk_id, length = struct.unpack_from("<HI", data, offset)
        if chunk_id != 0x3000:
            return None
        mesh_body, mesh_end = offset + 6, offset + length

        points: List[Tuple[float, ...]] = []
        for cid, start, end in _chunks(data, mesh_body + 1, mesh_end):
            if cid != 0x4000:
                continue
            cursor = data.index(b"\n", start) + 1
            shared = data[cursor]
            cursor += 1
            index_count, = struct.unpack_from("<I", data, cursor)
            cursor += 4
            wide = data[cursor]
            cursor += 1
            cursor += index_count * (4 if wide else 2)
            if shared:
                continue

            geometry_id, geometry_length = struct.unpack_from("<HI", data, cursor)
            if geometry_id != 0x5000:
                continue
            body, geometry_end = cursor + 6, cursor + geometry_length
            vertex_count, = struct.unpack_from("<I", data, body)

            elements, buffers = [], {}
            for cid3, start3, end3 in _chunks(data, body + 4, geometry_end):
                if cid3 == 0x5100:
                    for cid4, start4, _e in _chunks(data, start3, end3):
                        if cid4 == 0x5110:
                            elements.append(struct.unpack_from("<HHHH", data, start4))
                elif cid3 == 0x5200:
                    bind, vertex_size = struct.unpack_from("<HH", data, start3)
                    for cid4, start4, end4 in _chunks(data, start3 + 4, end3):
                        if cid4 == 0x5210:
                            buffers[bind] = (vertex_size, data[start4:end4])

            for source, elem_type, semantic, elem_offset in elements:
                if semantic != 1 or source not in buffers or elem_type != 2:
                    continue
                vertex_size, raw = buffers[source]
                for index in range(vertex_count):
                    points.append(
                        struct.unpack_from("<3f", raw, index * vertex_size + elem_offset)
                    )
        return _dims(points)
    except (struct.error, ValueError, IndexError):
        return None


# --- Legacy .geo (ground-truth side) -----------------------------------------

def geo_dims(path: Path) -> Optional[Dims]:
    """Bounding box of a legacy piece. Header is '=4si16siii', then float triples."""
    data = path.read_bytes()
    try:
        magic, _unknown, _name, vertex_count, _faces, _unknown2 = struct.unpack_from(
            "=4si16siii", data, 0
        )
        if magic != b"OEG.":
            return None
        return _dims(
            [struct.unpack_from("=fff", data, 36 + i * 12) for i in range(vertex_count)]
        )
    except struct.error:
        return None


def _dims(points) -> Optional[Dims]:
    if not points:
        return None
    axes = list(zip(*points))
    return tuple(sorted(max(axis) - min(axis) for axis in axes))  # type: ignore[return-value]


def cost(a: Dims, b: Dims) -> float:
    """Worst relative difference across the sorted bounding-box axes."""
    return max(
        abs(x - y) / max(abs(x), abs(y), 1e-6) for x, y in zip(a, b)
    )


# --- Matching -----------------------------------------------------------------

def load_manifest(path: Path) -> Dict[str, List[str]]:
    crafts: Dict[str, List[str]] = {}
    for line in path.read_text(encoding="latin-1").splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        fields = line.split("|")
        if len(fields) < 4:
            continue
        try:
            if int(fields[3]) not in RENDERABLE_GEO_TYPES:
                continue
        except ValueError:
            continue
        crafts.setdefault(fields[0].lower(), []).append(fields[1].lower())
    return crafts


def match_craft(craft: str, pieces: Sequence[str], stock_root: Path, payload_root: Path):
    directory = payload_root / craft
    if not directory.is_dir():
        return None

    legacy = {}
    for piece in pieces:
        candidate = stock_root / f"{piece}.geo"
        if candidate.exists():
            found = geo_dims(candidate)
            if found:
                legacy[piece] = found
    if not legacy:
        return None

    redux = {}
    for path in sorted(directory.glob("*.mesh")):
        if path.stem.lower() in legacy:
            continue  # already named what the simulation asks for
        if MARKER_STEM_PATTERN.search(path.stem):
            continue  # marker, not body geometry
        found = mesh_dims(path)
        if found:
            redux[path.stem] = found
    if not redux:
        return None

    taken_left, taken_right, results = set(), set(), []

    # Piece names are <3 letters><2 digits><3 letter code>, where the digit pair
    # is a level-of-detail marker: slt21ckp is the same cockpit as slt11ckp.
    # When a payload carries the simulation's own piece code at another LOD it is
    # that piece by construction, so claim it before any shape comparison --
    # otherwise the bounding box can hand it to a different code entirely, which
    # is how slt21ckp was landing on slt11trt while slt11ckp went unmatched.
    for rname in sorted(redux):
        match = re.fullmatch(r"([a-z]{3})(\d{2})([a-z0-9]{3})", rname, re.IGNORECASE)
        if not match:
            continue
        normalized = f"{match.group(1)}11{match.group(3)}".lower()
        if normalized in legacy and normalized not in taken_left:
            taken_left.add(normalized)
            taken_right.add(rname)
            results.append((normalized, rname, cost(legacy[normalized], redux[rname]), None))

    pairs = sorted(
        (
            (cost(left, right), lname, rname)
            for lname, left in legacy.items()
            for rname, right in redux.items()
        ),
        key=lambda item: item[0],
    )

    for value, lname, rname in pairs:
        if lname in taken_left or rname in taken_right:
            continue
        runner_up = next(
            (
                other
                for other, l2, r2 in pairs
                if l2 == lname and r2 != rname and r2 not in taken_right
            ),
            None,
        )
        taken_left.add(lname)
        taken_right.add(rname)
        results.append((lname, rname, value, runner_up))

    return (
        results,
        [name for name in legacy if name not in taken_left],
        sorted(set(redux) - taken_right),
    )


def main(argv: Sequence[str]) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--stock-root",
        type=Path,
        required=True,
        help="Legacy Battlezone stock directory holding per-piece .geo files",
    )
    parser.add_argument("--manifest", type=Path, default=DEFAULT_MANIFEST)
    parser.add_argument("--payload-root", type=Path, default=DEFAULT_PAYLOAD_ROOT)
    parser.add_argument("--craft", action="append", help="Limit to these craft names")
    parser.add_argument(
        "--threshold",
        type=float,
        default=0.12,
        help="Bounding-box delta at or below which a match is treated as confident",
    )
    parser.add_argument(
        "--max-delta",
        type=float,
        default=0.50,
        help="Reject matches worse than this outright; they are noise, not geometry",
    )
    parser.add_argument(
        "--emit-aliases",
        type=Path,
        help="Write an alias table the exporter can consume (craft|bone|piece)",
    )
    args = parser.parse_args(argv)

    if not args.stock_root.is_dir():
        print(f"stock root not found: {args.stock_root}", file=sys.stderr)
        return 2

    crafts = load_manifest(args.manifest)
    wanted = {c.lower() for c in args.craft} if args.craft else None

    confident = weak = 0
    aliases: List[Tuple[str, str, str, float]] = []
    for craft in sorted(crafts):
        if wanted and craft not in wanted:
            continue
        outcome = match_craft(craft, crafts[craft], args.stock_root, args.payload_root)
        if not outcome:
            continue
        results, unmatched, leftover = outcome
        if not results:
            continue

        print(f"\n===== {craft} =====")
        for lname, rname, value, runner_up in sorted(results):
            margin = "" if runner_up is None else f"  (next best {runner_up:.1%})"
            if value > args.max_delta:
                verdict = "DROP"
            elif value <= args.threshold:
                confident += 1
                verdict = "OK  "
            else:
                weak += 1
                verdict = "WEAK"
            if verdict != "DROP":
                aliases.append((craft, rname, lname, value))
            print(f"  {verdict} {lname:<12} <- {rname:<22} delta {value:>6.1%}{margin}")
        if unmatched:
            print(f"  no legacy match: {', '.join(unmatched)}")
        if leftover:
            print(f"  unused payloads: {', '.join(leftover)}")

    print(f"\nconfident (<= {args.threshold:.0%}): {confident}    weak: {weak}")

    if args.emit_aliases:
        header = [
            "# Chunk payload piece aliases: <craft>|<exported bone name>|<simulation piece>",
            "#",
            "# Generated by scripts/match_legacy_chunk_pieces.py and consumed by",
            "# scripts/export_chunk_mesh_payloads.py. Each row says a payload the",
            "# exporter would name after a model bone should instead be named after the",
            "# piece the simulation fragments, recovered by matching the Redux geometry",
            "# against the legacy .geo of the same building.",
            "#",
            "# The trailing percentage is the bounding-box delta between the two. Under",
            "# ~12% is a confident match; larger values are best-effort, kept because a",
            "# roughly right chunk still beats a generic placeholder. Rows are plain data",
            "# -- edit or delete any you disagree with and re-run the exporter.",
            "",
        ]
        rows = [
            f"{craft}|{bone}|{piece}  # {value:.1%}"
            for craft, bone, piece, value in sorted(aliases)
        ]
        args.emit_aliases.write_text("\n".join(header + rows) + "\n", encoding="ascii")
        print(f"wrote {len(rows)} aliases to {args.emit_aliases}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
