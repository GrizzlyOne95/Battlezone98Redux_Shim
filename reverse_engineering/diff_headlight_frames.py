"""Differences two capture frames to isolate the headlight contribution.

Both frames must come from the same fixture and renderer; the player craft
hovers, so frames are paired by minimising difference over an unlit control
band (the sky/ridge region the headlight never reaches).
"""

import sys
from pathlib import Path

import numpy as np
from PIL import Image, ImageOps

LUMA = np.array([0.2126, 0.7152, 0.0722], dtype=np.float64)
CONTROL_BAND = (0, 380)


def luminance(path: Path) -> np.ndarray:
    with Image.open(path) as image:
        return np.asarray(image.convert("RGB"), dtype=np.float64) @ LUMA


def best_pair(on_dir: Path, off_dir: Path, index: int):
    on_frames = sorted(on_dir.glob("frame_*.png"))
    off_frames = sorted(off_dir.glob("frame_*.png"))
    on = luminance(on_frames[index])
    best = None
    for off_path in off_frames:
        off = luminance(off_path)
        if off.shape != on.shape:
            continue
        score = float(np.abs(
            on[CONTROL_BAND[0]:CONTROL_BAND[1]] -
            off[CONTROL_BAND[0]:CONTROL_BAND[1]]).mean())
        if best is None or score < best[2]:
            best = (on_frames[index], off_path, score)
    return best


def main() -> int:
    root = Path(sys.argv[1])
    on_dir = root / "dx11_headlight-on"
    off_dir = root / "dx11_headlight-off"
    index = int(sys.argv[2]) if len(sys.argv) > 2 else 3

    on_path, off_path, score = best_pair(on_dir, off_dir, index)
    print(f"paired {on_path.name} <-> {off_path.name} cameraDelta={score:.2f}")

    diff = np.clip(luminance(on_path) - luminance(off_path), 0.0, None)
    peak = float(np.percentile(diff, 99.5))
    print(f"contribution peak (p99.5) = {peak:.1f}")
    if peak <= 1.0:
        print("no measurable headlight contribution")
        return 1

    visual = np.clip(diff * (255.0 / peak), 0, 255).astype(np.uint8)
    out = Image.fromarray(visual)
    out = ImageOps.autocontrast(out)
    out_path = root / f"headlight_contribution_{index:03d}.png"
    out.save(out_path)
    print(f"wrote {out_path}")

    # Row profile: mean contribution per horizontal band, to locate the pool.
    height = diff.shape[0]
    for band in range(0, height, 120):
        mean = float(diff[band:band + 120].mean())
        print(f"rows {band:4d}-{min(band + 120, height):4d}: mean {mean:6.2f}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
