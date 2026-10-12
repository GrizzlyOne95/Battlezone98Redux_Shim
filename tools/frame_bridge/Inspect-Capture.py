"""Inspect raw bridge depth; contrast is a diagnostic, not linearized depth.

Usage: python tools/frame_bridge/Inspect-Capture.py capture.pfm --color capture.bmp
Requires Pillow for PNG output. Raw PFM/JSON stay authoritative.
"""

import argparse
from array import array
import json
import math
from pathlib import Path
import sys

from PIL import Image, ImageDraw


def inspect(path, color):
    with path.open("rb") as stream:
        if stream.readline() != b"Pf\n":
            raise ValueError("Expected single-channel bridge PFM")
        width, height = map(int, stream.readline().split())
        scale = float(stream.readline())
        if not (0 < width <= 8192 and 0 < height <= 8192) or abs(scale) != 1:
            raise ValueError("Unsupported dimensions/scale")
        payload = stream.read()
    if len(payload) != width * height * 4:
        raise ValueError("Truncated or oversized PFM")
    values = array("f")
    if values.itemsize != 4:
        raise ValueError("Float representation must be 32 bits")
    values.frombytes(payload)
    if (scale < 0) != (sys.byteorder == "little"):
        values.byteswap()
    if any(not math.isfinite(z) or not 0 <= z <= 1 for z in values):
        raise ValueError("Invalid device depth")
    metadata = json.loads(Path(str(path) + ".json").read_text())
    if metadata["width"] != width or metadata["height"] != height or not metadata["candidateOnly"]:
        raise ValueError("Mismatched candidate metadata")
    non_clear_count = sum(0 < z < 1 for z in values)
    # Bounded percentile sampling avoids sorting a full 8K image in Python.
    stride = max(1, len(values) // 1_000_000)
    sample = sorted(z for z in values[::stride] if 0 < z < 1)
    low = sample[len(sample) // 100] if sample else 0
    high = sample[min(len(sample) - 1, len(sample) * 99 // 100)] if sample else 1
    span = high - low
    preview = bytes(
        0 if z == 0 or z == 1 else
        (255 if span <= 1e-10 else int(255 * max(0, min(1, (high - z) / span))))
        for z in values
    )
    depth = Image.frombytes("L", (width, height), preview).transpose(Image.Transpose.FLIP_TOP_BOTTOM)
    depth_path = path.with_suffix(".contrast.png")
    depth.save(depth_path)
    stats = {**metadata, "minimum": min(values), "maximum": max(values),
             "nonClearPixels": non_clear_count, "contrastLow": low, "contrastHigh": high,
             "contrastMeaning": "lower raw device z is brighter; endpoints black; no linearization"}
    path.with_suffix(".stats.json").write_text(json.dumps(stats, indent=2) + "\n")
    if color:
        with Image.open(color) as image:
            if image.size != (width, height):
                raise ValueError("Color/depth dimensions differ")
            panel = Image.new("RGB", (width * 2, height + 28), "black")
            panel.paste(image.convert("RGB"), (0, 28))
        panel.paste(depth.convert("RGB"), (width, 28))
        labels = ImageDraw.Draw(panel)
        labels.text((8, 8), f"Color: frame {metadata['frameId']}", fill="white")
        labels.text((width + 8, 8), "Raw depth candidate: percentile contrast, not linear depth", fill="white")
        panel.save(path.with_suffix(".comparison.png"))
    print(json.dumps(stats, indent=2))
    print(f"Preview: {depth_path}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("pfm", type=Path)
    parser.add_argument("--color", type=Path)
    args = parser.parse_args()
    inspect(args.pfm, args.color)
