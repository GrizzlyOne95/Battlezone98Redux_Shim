"""Measures how abruptly the player headlight stops on terrain.

Peak image gradient is useless here: crater rims and silhouettes swamp it. What
separates a hard terminator from a smooth falloff is the *width* of the band
over which the headlight's own contribution dies away.

Two things make that measurable:

  * The contribution is isolated by subtracting a headlight-off capture of the
    same mission on the same renderer, so terrain albedo largely cancels.
  * The player craft hovers, so no two runs stop on the same frame. Frames are
    therefore paired by minimising the difference over an unlit control band
    near the top of the image, which the headlight never reaches -- that band
    depends on the camera and not on the light, so the pair that matches there
    is the pair that shares a camera.

The reported number is the mean run length, in pixels, of the horizontal
transition between 15% and 85% of the peak contribution: the thickness of the
terminator. A hard edge is a few pixels; a smooth skirt is tens.
"""

import sys
from pathlib import Path

import numpy as np
from PIL import Image

LUMA = np.array([0.2126, 0.7152, 0.0722], dtype=np.float64)

# Rows the headlight never reaches in this mission's framing (sky and far
# ridgeline). Used only to pair frames by camera, never measured for falloff.
CONTROL_BAND = (0, 380)
# Rows the lit pool occupies.
MEASURE_BAND = (700, 1430)


def luminance(path: Path) -> np.ndarray:
    with Image.open(path) as image:
        return np.asarray(image.convert("RGB"), dtype=np.float64) @ LUMA


def frames(directory: Path) -> list[Path]:
    return sorted(directory.glob("frame_*.png"))


def best_camera_match(on_dir: Path, off_dir: Path) -> tuple[Path, Path, float]:
    """The (on, off) frame pair whose unlit control band agrees most closely."""
    on_frames = [(path, luminance(path)) for path in frames(on_dir)]
    off_frames = [(path, luminance(path)) for path in frames(off_dir)]
    best = None
    for on_path, on_image in on_frames:
        for off_path, off_image in off_frames:
            if on_image.shape != off_image.shape:
                continue
            band = np.abs(
                on_image[CONTROL_BAND[0]:CONTROL_BAND[1]]
                - off_image[CONTROL_BAND[0]:CONTROL_BAND[1]])
            score = float(band.mean())
            if best is None or score < best[2]:
                best = (on_path, off_path, score)
    return best


def terminator_thickness(contribution: np.ndarray) -> tuple[float, float]:
    """Mean horizontal run length of the 15%-85% transition, in pixels."""
    peak = float(np.percentile(contribution, 99.5))
    if peak <= 1.0:
        return float("nan"), peak

    low, high = 0.15 * peak, 0.85 * peak
    runs: list[int] = []
    for row in contribution:
        inside = (row >= low) & (row < high)
        if not inside.any():
            continue
        # Run lengths of consecutive True values.
        padded = np.concatenate(([False], inside, [False]))
        edges = np.flatnonzero(padded[1:] != padded[:-1])
        lengths = edges[1::2] - edges[0::2]
        # Ignore single-pixel speckle from albedo noise.
        runs.extend(int(length) for length in lengths if length >= 2)
    if not runs:
        return float("nan"), peak
    return float(np.mean(runs)), peak


def analyse(on_dir: Path, off_dir: Path) -> dict:
    match = best_camera_match(on_dir, off_dir)
    if match is None:
        return {"label": on_dir.name, "error": "no comparable frames"}
    on_path, off_path, score = match
    contribution = np.clip(luminance(on_path) - luminance(off_path), 0.0, None)
    thickness, peak = terminator_thickness(
        contribution[MEASURE_BAND[0]:MEASURE_BAND[1]])
    return {
        "label": on_dir.name,
        "on": on_path.name,
        "off": off_path.name,
        "camera_delta": score,
        "peak": peak,
        "thickness_px": thickness,
    }


PAIRS = [
    ("ab_dx11_white-focused_repair-off", "ab_dx11_off_repair-on"),
    ("ab_dx11_white-focused_repair-on", "ab_dx11_off_repair-on"),
    ("ab_dx9_white-focused_repair-off", "ab_dx9_off_repair-on"),
    ("ab_dx9_white-focused_repair-on", "ab_dx9_off_repair-on"),
    ("ab_dx11_white-wide_repair-off", "ab_dx11_off_repair-on"),
    ("ab_dx11_white-wide_repair-on", "ab_dx11_off_repair-on"),
    ("ab_dx9_white-wide_repair-off", "ab_dx9_off_repair-on"),
    ("ab_dx9_white-wide_repair-on", "ab_dx9_off_repair-on"),
]


def main() -> int:
    root = Path(sys.argv[1]) if len(sys.argv) > 1 else Path(
        "reverse_engineering/snapshots/headlight_falloff")
    print(f"{'run':<40}{'cameraDelta':>13}{'peak':>8}{'terminator(px)':>16}")
    for on_name, off_name in PAIRS:
        on_dir, off_dir = root / on_name, root / off_name
        if not on_dir.is_dir() or not off_dir.is_dir():
            print(f"{on_name:<40}{'missing':>13}")
            continue
        result = analyse(on_dir, off_dir)
        if "error" in result:
            print(f"{result['label']:<40}{result['error']:>13}")
            continue
        print(f"{result['label']:<40}{result['camera_delta']:>13.2f}"
              f"{result['peak']:>8.1f}{result['thickness_px']:>16.1f}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
