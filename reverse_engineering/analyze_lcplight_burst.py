#!/usr/bin/env python3
"""Find light steps in an lcplight burst, and tell them apart from camera moves.

run_lcplight.ps1 captures a 4 Hz burst of window frames across each transition
and writes luma.csv beside them. A raw luma series cannot distinguish "the scene
light level changed" from "the camera turned and the rectangle now sees
different geometry" -- that confusion already cost one retracted finding.

So score each consecutive pair two ways:

  ratio     mean luma of frame N over frame N-1, over the whole 3D area
  geometry  how much the frame changed once the global scale is divided out

A lighting step scales everything and leaves the normalised difference small.
A camera move leaves a large normalised difference whatever the scale. Only
pairs with a big ratio AND a small normalised difference are reported as light
steps; the rest are listed separately so nothing is hidden.

Usage:
    python analyze_lcplight_burst.py <output-root> [--min-ratio 1.15]
"""

import argparse
import csv
import os
import sys
from collections import defaultdict

try:
    import numpy as np
    from PIL import Image
except ImportError as exc:  # pragma: no cover - environment problem, not logic
    sys.exit(f"needs numpy and pillow: {exc}")


# The captured PNG is the whole game window: title bar at the top, and HUD
# panels in three corners. Crop to the area that is 3D scene in every frame.
SCENE_BOX = (0.30, 0.98, 0.10, 0.58)  # x0, x1, y0, y1 as fractions


def load_scene(path):
    image = np.asarray(Image.open(path).convert("RGB")).astype(np.float32)
    height, width, _ = image.shape
    x0, x1, y0, y1 = SCENE_BOX
    return image[int(y0 * height):int(y1 * height), int(x0 * width):int(x1 * width)]


def score_pair(previous, current):
    """Return (ratio, normalised difference) for one consecutive pair."""
    previous_mean = float(previous.mean())
    current_mean = float(current.mean())
    if previous_mean < 0.5:
        return 0.0, 1.0
    ratio = current_mean / previous_mean
    # Divide the global scale out, then ask how much of the image still moved.
    rescaled = previous * ratio
    denominator = max(current_mean, 1.0)
    normalised = float(np.abs(current - rescaled).mean()) / denominator
    return ratio, normalised


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("output_root")
    parser.add_argument("--min-ratio", type=float, default=1.15,
                        help="report a step when the luma ratio is at least this "
                             "far from 1.0 in either direction")
    parser.add_argument("--max-geometry", type=float, default=0.10,
                        help="above this normalised difference the pair is a "
                             "camera move, not a light step")
    args = parser.parse_args()

    csv_path = os.path.join(args.output_root, "luma.csv")
    if not os.path.isfile(csv_path):
        sys.exit(f"no luma.csv in {args.output_root}")

    series = defaultdict(list)
    with open(csv_path, newline="", encoding="utf-8-sig") as handle:
        for row in csv.DictReader(handle):
            series[(row["Arm"], row["Window"])].append(
                (int(row["Index"]), float(row["At"]), row["Path"]))

    for key in sorted(series):
        arm, window = key
        frames = sorted(series[key])
        print(f"\n=== arm={arm} burst={window} ({len(frames)} frames) ===")
        if len(frames) < 2:
            print("  too few frames to measure a step")
            continue

        previous_image = None
        steps = []
        moves = []
        for index, at, path in frames:
            if not os.path.isfile(path):
                continue
            image = load_scene(path)
            if previous_image is not None:
                ratio, geometry = score_pair(previous_image, image)
                record = (at, ratio, geometry, previous_image.mean(), image.mean())
                if abs(ratio - 1.0) >= (args.min_ratio - 1.0):
                    if geometry <= args.max_geometry:
                        steps.append(record)
                    else:
                        moves.append(record)
            previous_image = image

        if steps:
            print("  LIGHT STEPS (scene scaled, geometry unchanged):")
            for at, ratio, geometry, before, after in steps:
                print(f"    t+{at:<7.2f} {before:7.2f} -> {after:7.2f}  "
                      f"x{ratio:5.3f}  geometry={geometry:.3f}")
        else:
            print("  no light step found")

        if moves:
            print("  brightness changes that came with a camera move "
                  "(NOT evidence of a light step):")
            for at, ratio, geometry, before, after in moves:
                print(f"    t+{at:<7.2f} {before:7.2f} -> {after:7.2f}  "
                      f"x{ratio:5.3f}  geometry={geometry:.3f}")


if __name__ == "__main__":
    main()
