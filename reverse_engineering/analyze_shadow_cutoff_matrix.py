"""Aggregates [OgreProfile][RenderContributorTop] rows from shadow-cutoff matrix logs.

For each arm directory under the matrix root, takes the last fully-sampled
second of contributor rows and groups them by
(camera, technique, scheme, lod, pass, mesh, material), reporting per-frame
submission counts. Output is one CSV per matrix root plus a compact console
summary focused on the avtank and terrain rows under main vs shadow cameras.
"""

import csv
import re
import sys
from collections import defaultdict
from pathlib import Path

ROW = re.compile(r"\[OgreProfile\]\[RenderContributorTop\]\s+(.*)$")
FIELD = re.compile(r"(\w+)=([^\s]+)")


def parse_rows(path: Path) -> list[dict]:
    rows = []
    for line in path.read_text(errors="replace").splitlines():
        match = ROW.search(line)
        if not match:
            continue
        fields = dict(FIELD.findall(match.group(1)))
        rows.append(fields)
    return rows


def last_tick_rows(rows: list[dict]) -> list[dict]:
    # Rows are emitted per second; the log line's own timestamp groups them.
    # Group by the enclosing log timestamp prefix is not available here, so
    # use rank: a full second is rank 0..N contiguous. Take the rows after the
    # last rank-0 occurrence.
    last_start = 0
    for index, row in enumerate(rows):
        if row.get("rank") == "0":
            last_start = index
    return rows[last_start:]


def aggregate(rows: list[dict]) -> dict:
    grouped = defaultdict(float)
    for row in rows:
        key = (
            row.get("camera", "?"),
            row.get("technique", "?"),
            row.get("scheme", "?"),
            row.get("lod", "?"),
            row.get("mesh", "?"),
            row.get("material", "?"),
        )
        try:
            submissions = float(row.get("OgreSubmit", "0").rstrip("/f"))
        except ValueError:
            submissions = 0.0
        grouped[key] += submissions
    return grouped


def summarise(arm: Path) -> dict:
    log = arm / "openshim.log"
    if not log.is_file():
        return {}
    rows = last_tick_rows(parse_rows(log))
    return aggregate(rows)


def main() -> int:
    root = Path(sys.argv[1])
    arms = sorted(path for path in root.iterdir() if path.is_dir())
    all_keys = set()
    per_arm = {}
    for arm in arms:
        per_arm[arm.name] = summarise(arm)
        all_keys.update(per_arm[arm.name])

    def relevant(key):
        camera, technique, scheme, lod, mesh, material = key
        mesh_l = mesh.lower()
        return (
            "avtank" in mesh_l
            or "terrain" in material.lower()
            or "tilecluster" in mesh_l
        )

    out_path = root / "contributor_summary.csv"
    with out_path.open("w", newline="") as handle:
        writer = csv.writer(handle)
        writer.writerow(["camera", "technique", "scheme", "lod", "mesh",
                         "material"] + [arm.name for arm in arms])
        for key in sorted(all_keys):
            if not relevant(key):
                continue
            writer.writerow(list(key) + [
                f"{per_arm[arm.name].get(key, 0.0):.1f}" for arm in arms])
    print(f"wrote {out_path}")

    # Console summary: avtank rows only, compact.
    for arm in arms:
        print(f"\n== {arm.name} ==")
        grouped = per_arm[arm.name]
        for key in sorted(grouped):
            camera, technique, scheme, lod, mesh, material = key
            if "avtank" not in mesh.lower():
                continue
            print(f"  {camera:<28} tech={technique:<24} scheme={scheme:<12} "
                  f"lod={lod:<3} mesh={mesh:<12} sub/f={grouped[key]:.1f}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
