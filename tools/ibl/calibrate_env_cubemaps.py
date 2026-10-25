"""Calibrate the per-planet IBL cubemaps against the neutral pair.

The raw bakes from bake_planet_env.py are physically motivated and very dark:
an airless world's irradiance averages about 7/255 against the neutral map's
90/255, so swapping it in drops most of the ambient on every Enhanced
surface. The Enhanced shaders take their ambient from the irradiance cube
(OSE_IBL_LEGACY_AMBIENT_RETAIN keeps only 20% of the scene ambient), so the
raw bake reads as a lighting failure rather than as a planet.

This tool keeps each planet's colour and part of its directionality while
pinning its exposure to the neutral map:

    tint     = meanRGB(planet mip 0) / luminance(meanRGB)     (chroma only)
    planet'  = planet * luminance(neutral) / luminance(planet) (same exposure)
    out      = w * planet' + (1 - w) * neutral * tint          (w = --planet-weight)
    out      = luminance(out) + (out - luminance(out)) * c      (c = --chroma)

Every mip is processed with the same formula against the neutral's matching
mip (the neutral irradiance ships one mip; its chain is box-filtered). The
mean luminance of the result equals the neutral's, so a swap never changes
overall brightness; only the hue and the sky/ground balance move, and the hue
is damped by --chroma because a raw bake can lose a channel entirely (Venus
bakes with no blue at all).

Usage (inputs are the RAW bakes; running on calibrated output would pull the
maps further toward neutral):

    py -3 tools/ibl/calibrate_env_cubemaps.py --input-dir <raw bakes> \
        --output resources/renderer/enhanced [--planet-weight 0.5] [--worlds mn,ma]

Needs numpy. Reads the neutral pair from --output.
"""
from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

import numpy as np

sys.path.insert(0, str(Path(__file__).resolve().parent))
from bake_planet_env import WORLDS, bc1_compress, box_mip_chain, dds_header_bc1  # noqa: E402

KINDS = ('prefilter', 'irradiance')
LUM = np.array([0.2126, 0.7152, 0.0722])


def bc1_bytes(w: int, h: int) -> int:
    return max(1, (w + 3) // 4) * max(1, (h + 3) // 4) * 8


def read_cube(path: Path) -> list[list[np.ndarray]]:
    """Legacy DXT1 cube DDS -> faces[6][mips] of float RGB in 0..1."""
    data = path.read_bytes()
    if data[:4] != b'DDS ' or data[84:88] != b'DXT1':
        raise SystemExit(f'{path}: not a DXT1 DDS')
    height, width = struct.unpack_from('<II', data, 12)
    mips = max(1, struct.unpack_from('<I', data, 28)[0])
    caps2 = struct.unpack_from('<I', data, 112)[0]
    if not caps2 & 0x200 or width != height:
        raise SystemExit(f'{path}: not a square cubemap')
    faces: list[list[np.ndarray]] = []
    offset = 128
    for _ in range(6):
        chain = []
        for mip in range(mips):
            size = max(1, width >> mip)
            n = bc1_bytes(size, size)
            chain.append(decode_dxt1(data[offset:offset + n], size, size))
            offset += n
        faces.append(chain)
    if offset != len(data):
        raise SystemExit(f'{path}: payload size mismatch')
    return faces


def decode_dxt1(block_bytes: bytes, w: int, h: int) -> np.ndarray:
    bw, bh = max(1, (w + 3) // 4), max(1, (h + 3) // 4)
    blocks = np.frombuffer(block_bytes, dtype='<u2').reshape(bw * bh, 4)
    c0 = blocks[:, 0].astype(np.uint32)
    c1 = blocks[:, 1].astype(np.uint32)
    idx = blocks[:, 2].astype(np.uint32) | (blocks[:, 3].astype(np.uint32) << 16)

    def rgb(c: np.ndarray) -> np.ndarray:
        return np.stack([((c >> 11) & 31) / 31.0, ((c >> 5) & 63) / 63.0, (c & 31) / 31.0], -1)

    p0, p1 = rgb(c0), rgb(c1)
    four = (c0 > c1)[:, None]
    p2 = np.where(four, (2 * p0 + p1) / 3, (p0 + p1) / 2)
    p3 = np.where(four, (p0 + 2 * p1) / 3, 0.0)
    palette = np.stack([p0, p1, p2, p3], 1)
    out = np.zeros((bh * 4, bw * 4, 3), np.float64)
    rows = np.arange(len(idx))
    for i in range(16):
        sel = (idx >> (2 * i)) & 3
        y, x = divmod(i, 4)
        out[y::4, x::4] = palette[rows, sel].reshape(bh, bw, 3)
    return out[:h, :w]


def luminance(img: np.ndarray) -> np.ndarray:
    return img @ LUM


def mean_rgb(faces: list[list[np.ndarray]], mip: int = 0) -> np.ndarray:
    return np.concatenate([f[mip].reshape(-1, 3) for f in faces]).mean(0)


def calibrate(planet: list[list[np.ndarray]], neutral: list[list[np.ndarray]],
              weight: float, chroma: float) -> list[list[np.ndarray]]:
    mips = len(planet[0])
    if len(neutral[0]) < mips:
        neutral = [box_mip_chain(face[0])[:mips] for face in neutral]
    planet_mean = mean_rgb(planet)
    neutral_mean = mean_rgb(neutral)
    planet_l = float(luminance(planet_mean))
    neutral_l = float(luminance(neutral_mean))
    if planet_l <= 1e-6:
        raise SystemExit('planet map is black; nothing to calibrate')
    tint = planet_mean / planet_l
    exposure = neutral_l / planet_l
    out: list[list[np.ndarray]] = []
    for face in range(6):
        chain = []
        for mip in range(mips):
            p = planet[face][mip] * exposure
            n = neutral[face][mip] * tint
            mixed = weight * p + (1.0 - weight) * n
            grey = luminance(mixed)[..., None]
            chain.append(np.clip(grey + (mixed - grey) * chroma, 0.0, 1.0))
        out.append(chain)
    return out


def write_cube(path: Path, faces: list[list[np.ndarray]]) -> None:
    base = faces[0][0].shape[0]
    mips = len(faces[0])
    data = bytearray(dds_header_bc1(base, base, mips))
    for face in range(6):
        for mip in range(mips):
            data += bc1_compress(faces[face][mip])
    path.write_bytes(bytes(data))


def describe(label: str, faces: list[list[np.ndarray]]) -> str:
    names = ('+X', '-X', '+Y', '-Y', '+Z', '-Z')
    mean = mean_rgb(faces) * 255.0
    per = ' '.join(f'{names[i]}={float(luminance(f[0]).mean()) * 255.0:5.1f}' for i, f in enumerate(faces))
    return (f'{label:34s} mean=({mean[0]:5.1f},{mean[1]:5.1f},{mean[2]:5.1f}) '
            f'L={float(luminance(mean_rgb(faces))) * 255.0:5.1f} | {per}')


def main() -> None:
    root = Path(__file__).resolve().parents[2]
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--input-dir', type=Path, required=True, help='directory holding the RAW openshim_env_*.dds bakes')
    ap.add_argument('--output', type=Path, default=root / 'resources/renderer/enhanced',
                    help='destination; also where openshim_ibl_neutral_*.dds are read from')
    ap.add_argument('--planet-weight', type=float, default=0.5,
                    help='share of the exposure-matched planet map in the result (0 = neutral tinted, 1 = planet only)')
    ap.add_argument('--chroma', type=float, default=0.6,
                    help='share of the planet hue kept after mixing (1 = full saturation, 0 = grey)')
    ap.add_argument('--worlds', default=','.join(WORLDS))
    ap.add_argument('--dry-run', action='store_true', help='report only; write nothing')
    args = ap.parse_args()
    if not 0.0 <= args.planet_weight <= 1.0 or not 0.0 <= args.chroma <= 1.0:
        raise SystemExit('--planet-weight and --chroma must be within 0..1')

    for kind in KINDS:
        neutral = read_cube(args.output / f'openshim_ibl_neutral_{kind}.dds')
        print(describe(f'neutral {kind}', neutral))
        for code in args.worlds.split(','):
            src = args.input_dir / f'openshim_env_{code}_{kind}.dds'
            planet = read_cube(src)
            result = calibrate(planet, neutral, args.planet_weight, args.chroma)
            print(describe(f'  {code} raw', planet))
            print(describe(f'  {code} calibrated', result))
            if args.dry_run:
                continue
            dst = args.output / src.name
            write_cube(dst, result)
            if dst.stat().st_size != src.stat().st_size:
                raise SystemExit(f'{dst}: size changed ({dst.stat().st_size} vs {src.stat().st_size})')


if __name__ == '__main__':
    main()
