"""Author a local stock-avtank recoil clip using the shared Toolbox codecs.

Writes a new output directory only; never installs or distributes game assets.
The stock mesh/weights and existing bones/clips are retained. Skeleton-only
parents carry animation while stock code continues aiming the original bones.
"""
from __future__ import annotations

import argparse
import copy
import hashlib
import json
import math
from pathlib import Path
import re
import sys


def prepare(game: Path, output: Path, toolbox: Path, distance: float, duration: float):
    if not math.isfinite(distance) or not 0 < distance <= 2:
        raise ValueError("Distance must be finite and in (0, 2] metres")
    if not math.isfinite(duration) or not 0.02 <= duration <= 2:
        raise ValueError("Duration must be finite and in [0.02, 2] seconds")
    sys.path.insert(0, str(toolbox.resolve()))
    from battlezone.meshes.ogre_skeleton import (
        Animation, Bone, Keyframe, Track, read_skeleton, write_skeleton,
    )

    models = game / "BZ_ASSETS/common/models"
    source = models / "avtank.skeleton"
    original = source.read_bytes()
    skeleton = read_skeleton(original)
    if write_skeleton(skeleton) != original:
        raise ValueError("Stock skeleton must round-trip byte-for-byte before editing")
    old = copy.deepcopy(skeleton)
    clip = "osh_recoil"
    if any(a.name == clip for a in skeleton.animations):
        raise ValueError("Source already contains the trial clip")
    tracks = []
    parents = []
    for barrel_name, helper_name in (("AGR11BGA", "osh_recoil_world"),
                                     ("AGR21bga", "osh_recoil_cockpit")):
        barrel = skeleton.bone(barrel_name)
        if barrel is None or barrel.parent is None or skeleton.bone(helper_name):
            raise ValueError(f"Unexpected stock barrel hierarchy: {barrel_name}")
        handle = max(b.handle for b in skeleton.bones) + 1
        skeleton.bones.append(Bone(helper_name, handle, parent=barrel.parent))
        barrel.parent = handle
        # Smoothstep return: maximum kick at t=0, zero offset at the end.
        keys = []
        for n in range(13):
            fraction = n / 12
            offset = -distance * (1 - (3 * fraction**2 - 2 * fraction**3))
            keys.append(Keyframe(duration * fraction, translation=(0, 0, offset)))
        tracks.append(Track(handle, keys))
        parents.append({"barrel": barrel_name, "helper": helper_name, "handle": handle})
    skeleton.animations.append(Animation(clip, duration, tracks))
    encoded = write_skeleton(skeleton)
    decoded = read_skeleton(encoded)
    if decoded.animations[:-1] != old.animations or len(decoded.bones) != len(old.bones) + 2:
        raise ValueError("Existing clips or bone count changed unexpectedly")
    reparented = {item["barrel"]: item["handle"] for item in parents}
    for original_bone in old.bones:
        actual = copy.deepcopy(decoded.bone(original_bone.name))
        if actual.parent != reparented.get(original_bone.name, original_bone.parent):
            raise ValueError(f"Unexpected parent change: {original_bone.name}")
        actual.parent = original_bone.parent  # only the two barrel parents may change
        if actual != original_bone:
            raise ValueError(f"Original bone transform changed: {original_bone.name}")
    for track in decoded.animations[-1].tracks:
        if abs(track.keyframes[0].translation[2] + distance) > 1e-6 or any(track.keyframes[-1].translation):
            raise ValueError("Recoil endpoints failed validation")

    odf = game / "addon/avtank.odf"
    if not odf.is_file():
        odf = game / "StockODFFiles/avtank.odf"
    text = odf.read_bytes().decode("latin1")
    if not re.search(r'(?im)^weaponName1\s*=\s*"gatstab"', text):
        raise ValueError("Expected gatstab in avtank slot one")
    text = re.sub(r"(?im)^recoil(?:Name|Distance|Return|Animation|PlaybackRate|Cockpit)1\s*=.*\r?\n?", "", text)
    text = re.sub(r"(?im)^// OpenShim opt-in avtank/gatstab recoil trial \(slot 1\)\.[\r\n]*", "", text)
    settings = ('\r\n// OpenShim authored stock-model animation trial.\r\n'
                'recoilAnimation1 = "osh_recoil"\r\n'
                'recoilPlaybackRate1 = 1.0\r\nrecoilCockpit1 = true\r\n')
    text, count = re.subn(r"(?im)^\[CraftClass\][ \t\r]*$", lambda m: m.group(0).rstrip("\r") + settings, text)
    if count != 1:
        raise ValueError("Expected one CraftClass section")
    output.mkdir(parents=True, exist_ok=False)
    (output / "avtank.skeleton").write_bytes(encoded)
    (output / "avtank.mesh").write_bytes((models / "avtank.mesh").read_bytes())
    (output / "avtank.odf").write_bytes(text.encode("latin1"))
    manifest = {"clip": clip, "distance_metres": distance, "duration_seconds": duration,
                "parents": parents, "source_skeleton_sha256": hashlib.sha256(original).hexdigest(),
                "files": {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in output.iterdir()}}
    (output / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    print(json.dumps({"output": str(output.resolve()), **manifest}, indent=2))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--game-root", type=Path, default=Path(r"C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux"))
    parser.add_argument("--output", type=Path, required=True, help="New directory for locally generated game assets")
    parser.add_argument("--toolbox", type=Path, default=Path(__file__).resolve().parents[2] / "Battlezone98_Modding_Toolbox")
    parser.add_argument("--distance", type=float, default=0.30)
    parser.add_argument("--duration", type=float, default=0.12)
    args = parser.parse_args()
    prepare(args.game_root, args.output, args.toolbox, args.distance, args.duration)
