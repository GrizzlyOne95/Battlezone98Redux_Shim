"""Crops and contrast-enhances shadow-cutoff capture frames for inspection.

Shadow differences on the moon fixture are low-contrast at night ambient.
For each frame this produces:
  - a full-frame autocontrast version, and
  - per-station crops along the tank line (stations every 25 m from the
    player) when the line geometry is known, scaled up with strong local
    contrast enhancement.

Usage: python enhance_shadow_frames.py <arm_dir> [frame_index]
"""

import sys
from pathlib import Path

from PIL import Image, ImageEnhance, ImageOps

# Screen-space anchor: the nearest station trio sits near the frame centre at
# 25 m; stations recede toward the horizon. These fractions were measured on
# the 1280x720 pipeline captures and are only a visual aid, not exact.
STATION_ANCHORS = {
    25:  (0.42, 0.80),
    50:  (0.55, 0.74),
    75:  (0.63, 0.70),
    100: (0.69, 0.67),
    125: (0.74, 0.65),
    150: (0.78, 0.63),
    200: (0.83, 0.61),
    250: (0.86, 0.60),
}


def enhance(image: Image.Image) -> Image.Image:
    grey = ImageOps.autocontrast(image.convert("L"), cutoff=1)
    return ImageEnhance.Contrast(grey).enhance(2.5)


def main() -> int:
    arm_dir = Path(sys.argv[1])
    frame_index = int(sys.argv[2]) if len(sys.argv) > 2 else 2
    frame_path = arm_dir / f"frame_{frame_index:03d}.png"
    if not frame_path.is_file():
        print(f"missing {frame_path}")
        return 1
    image = Image.open(frame_path).convert("RGB")
    width, height = image.size

    out_full = arm_dir / f"enhanced_full_{frame_index:03d}.png"
    enhance(image).save(out_full)
    print(f"wrote {out_full}")

    for station, (fx, fy) in STATION_ANCHORS.items():
        cx, cy = int(width * fx), int(height * fy)
        half_w, half_h = width // 10, height // 8
        box = (max(0, cx - half_w), max(0, cy - half_h),
               min(width, cx + half_w), min(height, cy + half_h))
        crop = image.crop(box)
        crop = crop.resize((crop.width * 2, crop.height * 2), Image.LANCZOS)
        out = arm_dir / f"enhanced_station_{station:03d}m_{frame_index:03d}.png"
        enhance(crop).save(out)
    print(f"wrote station crops to {arm_dir}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
