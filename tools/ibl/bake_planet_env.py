#!/usr/bin/env python3
"""Bake per-planet image-based-lighting cubemap pairs for Battlezone 98 Redux.

For each of the 9 worlds this writes
  openshim_env_<code>_prefilter.dds    128px BC1 cube, 8 GGX-prefiltered mips
  openshim_env_<code>_irradiance.dds    32px BC1 cube, full box-filtered mip chain
matching the size of openshim_ibl_neutral_{prefilter,irradiance}.dds. Ogre
loads the neutral cubes with its default mip count (6 levels at 128px and
32px), so the runtime copies the destination's mip count per face and every
file must carry at least that many mips.
Values are LINEAR radiance; sRGB source textures are decoded before baking.

The GGX/Hammersley prefilter, cosine irradiance, BC1 compressor and cube DDS
writer are adapted from Campaign-Reimagined/Tools/Generate-StaticIBL.py. Changes
there: environment() is a per-planet sky sampled from a precomputed equirect
radiance map (with filtered importance sampling through its mip chain), and
the BC1 endpoint quantiser rounds to nearest instead of truncating.

Requires numpy and Pillow. Game data is only read, never written.
"""
from __future__ import annotations

import argparse
import math
import re
import struct
from pathlib import Path

import numpy as np
from PIL import Image, ImageDraw

PI = math.pi

# code -> (display name, trn stem, atlas stem)
WORLDS = {
    'mn': ('Moon', 'moon', 'MOON'),
    'ma': ('Mars', 'mars', 'MARS'),
    've': ('Venus', 'venus', 'VENUS'),
    'io': ('Io', 'io', 'IO'),
    'eu': ('Europa', 'europa', 'EUROPA'),
    'ti': ('Titan', 'titan', 'TITAN'),
    'ga': ('Ganymede', 'ganymede', 'GANYMEDE'),
    'ac': ('Achilles', 'achilles', 'ACHILLES'),
    'el': ('Elysium', 'elysium', 'ELYSIUM'),
}

AIRLESS_SKY = 0.003       # linear radiance of an airless sky
GROUND_DARKEN = 0.6       # ground = mean terrain colour * this
HORIZON_BLEND_DEG = 10.0  # ground/sky smoothing half-width
SKY_TILE_SCALE = 1.0      # tileSize = SkyHeight * this (uv = dir.xz/dir.y * SkyHeight/tileSize)
CLOUD_STRENGTH = 0.35     # light cloud composite
EQ_W, EQ_H = 1024, 512    # source radiance equirect (mip 0)
EQ_SS = 2                 # supersampling per axis when building the equirect
# Io's sky is jupiter.map with SkyType=1; the real placement is unknown, so guess.
IO_JUPITER = dict(az=0.0, el=40.0, radius_deg=18.0)

SKY_DIRS = ['pc/textures/sky', 'pc/textures/TRO/TERRAIN/SKY', 'common/textures/sky']


# ----------------------------------------------------------------- data io
def parse_trn(path: Path) -> dict[str, dict[str, str]]:
    """Minimal ini parse: lower-cased section/key, // comments stripped."""
    out: dict[str, dict[str, str]] = {}
    sec = ''
    for line in path.read_text(errors='replace').splitlines():
        line = line.split('//')[0].strip()
        m = re.match(r'\[([^\]]+)\]', line)
        if m:
            sec = m.group(1).strip().lower()
            out.setdefault(sec, {})
            continue
        if '=' in line and sec:
            k, v = line.split('=', 1)
            out[sec][k.strip().lower()] = v.strip().strip('"')
    return out


def srgb_to_linear(c: np.ndarray) -> np.ndarray:
    return np.where(c <= 0.04045, c / 12.92, ((c + 0.055) / 1.055) ** 2.4)


def linear_to_srgb(c: np.ndarray) -> np.ndarray:
    c = np.clip(c, 0.0, 1.0)
    return np.where(c <= 0.0031308, c * 12.92, 1.055 * c ** (1 / 2.4) - 0.055)


def find_texture(assets: Path, name: str) -> Path | None:
    stem = Path(name.strip()).stem.lower()
    if not stem:
        return None
    for d in SKY_DIRS:
        folder = assets / d
        if not folder.is_dir():
            continue
        for ext in ('.dds', '.tga', '.png'):
            for p in sorted(folder.iterdir()):
                if p.stem.lower() == stem and p.suffix.lower() == ext:
                    return p
    return None


def load_rgba_linear(path: Path) -> np.ndarray:
    a = np.asarray(Image.open(path).convert('RGBA')).astype(np.float64) / 255.0
    a[..., :3] = srgb_to_linear(a[..., :3])
    return a


def mean_linear(path: Path) -> np.ndarray:
    return load_rgba_linear(path)[..., :3].reshape(-1, 3).mean(0)


# --------------------------------------------------- equirect source helpers
def eq_dirs(w: int, h: int, ss: int = 1) -> np.ndarray:
    """Directions for an equirect (u from lon = atan2(x, z), v = acos(y) / pi)."""
    xs = (np.arange(w * ss) + 0.5) / (w * ss)
    ys = (np.arange(h * ss) + 0.5) / (h * ss)
    lon, colat = np.meshgrid(xs * 2 * PI - PI, ys * PI)
    return np.stack((np.sin(colat) * np.sin(lon), np.cos(colat), np.sin(colat) * np.cos(lon)), axis=-1)


def dir_to_eq_uv(d: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
    lon = np.arctan2(d[..., 0], d[..., 2])
    return (lon + PI) / (2 * PI), np.arccos(np.clip(d[..., 1], -1, 1)) / PI


def sample_wrap(img: np.ndarray, u: np.ndarray, v: np.ndarray, wrap_v: bool = True) -> np.ndarray:
    """Bilinear sample; u wraps, v wraps (tiling textures) or clamps (equirect)."""
    h, w = img.shape[:2]
    x = u * w - 0.5
    y = v * h - 0.5
    x0 = np.floor(x).astype(np.int64)
    y0 = np.floor(y).astype(np.int64)
    fx = (x - x0)[..., None]
    fy = (y - y0)[..., None]

    def px(xi, yi):
        xi = xi % w
        yi = yi % h if wrap_v else np.clip(yi, 0, h - 1)
        return img[yi, xi]
    return ((px(x0, y0) * (1 - fx) + px(x0 + 1, y0) * fx) * (1 - fy)
            + (px(x0, y0 + 1) * (1 - fx) + px(x0 + 1, y0 + 1) * fx) * fy)


def smoothstep(a: float, b: float, x: np.ndarray) -> np.ndarray:
    t = np.clip((x - a) / (b - a), 0.0, 1.0)
    return t * t * (3 - 2 * t)


def sprite_info(rgba: np.ndarray) -> tuple[np.ndarray, float]:
    """(mean linear colour of the lit pixels, disc radius as a fraction of the half-quad)."""
    lum = rgba[..., :3] @ np.array([0.2126, 0.7152, 0.0722])
    mask = lum > 0.004
    return rgba[..., :3][mask].mean(0), 2.0 * math.sqrt(mask.mean() / PI)


def az_el_dir(az_deg: float, el_deg: float) -> np.ndarray:
    az, el = math.radians(az_deg), math.radians(el_deg)
    return np.array([math.sin(az) * math.cos(el), math.sin(el), math.cos(az) * math.cos(el)])


# ----------------------------------------------------------- per-planet sky
class PlanetSky:
    """Builds the mip-0 equirect radiance map for one world."""

    def __init__(self, code: str, game: Path):
        self.code = code
        self.name, trn_stem, atlas_stem = WORLDS[code]
        assets = game / 'BZ_ASSETS'
        trn = parse_trn(game / 'Edit' / 'trn' / f'{trn_stem}.trn')
        sky = trn.get('sky', {})
        self.notes: list[str] = []

        atlas = assets / 'pc/textures/TerrainTextures/BZ_TERRAIN_ATLASES_DIFF_DDS' / f'{atlas_stem}_ATLAS_D.dds'
        self.ground_mean = mean_linear(atlas)
        self.ground = self.ground_mean * GROUND_DARKEN

        sky_name = sky.get('skytexture', '')
        sky_type = int(float(sky.get('skytype', '0') or 0))
        self.sky_height = float(sky.get('skyheight', '110') or 110)
        self.sky_tex = None
        self.sky_mean = np.full(3, AIRLESS_SKY)
        self.sprites: list[tuple[np.ndarray, np.ndarray, float]] = []  # (dir, colour, angular radius)
        self.cloud_layers: list[np.ndarray] = []

        if sky_type == 1 and sky_name.strip():
            tex = find_texture(assets, sky_name)
            col, _ = sprite_info(load_rgba_linear(tex))
            self.sprites.append((az_el_dir(IO_JUPITER['az'], IO_JUPITER['el']), col,
                                 math.radians(IO_JUPITER['radius_deg'])))
            self.notes.append(f'SkyType=1 {sky_name}: treated as airless backdrop with a GUESSED '
                              f'disc (az {IO_JUPITER["az"]}, el {IO_JUPITER["el"]}, '
                              f'radius {IO_JUPITER["radius_deg"]} deg)')
        elif sky_name.strip():
            tex = find_texture(assets, sky_name)
            if tex is None:
                raise SystemExit(f'{self.name}: sky texture {sky_name!r} not found')
            self.sky_tex = load_rgba_linear(tex)[..., :3]
            self.sky_mean = self.sky_tex.reshape(-1, 3).mean(0)
            clouds = trn.get('clouds', {})
            for i in range(int(float(clouds.get('count', '0') or 0))):
                ct = find_texture(assets, clouds.get(f'texture{i}', ''))
                if ct is not None:
                    self.cloud_layers.append(load_rgba_linear(ct))
        else:
            # Airless: the largest [Stars] billboard with a Size is the primary planet.
            stars = trn.get('stars', {})
            best = None
            for k, v in stars.items():
                m = re.fullmatch(r'size(\d+)', k)
                if not m:
                    continue
                n = m.group(1)
                tname = stars.get(f'texture{n}', '')
                if Path(tname).stem.lower() in ('stars', 'milkyway', ''):
                    continue
                if best is None or float(v) > best[0]:
                    best = (float(v), n, tname)
            if best:
                size, n, tname = best
                radius = float(stars.get('radius', '1000'))
                col, rf = sprite_info(load_rgba_linear(find_texture(assets, tname)))
                rho = math.atan(math.tan(math.atan(size * 0.5 / radius)) * rf)
                d = az_el_dir(float(stars.get(f'azimuth{n}', '0')), float(stars.get(f'elevation{n}', '0')))
                self.sprites.append((d, col, rho))
                self.notes.append(f'billboard {tname} size {size:g} radius {radius:g}: disc radius '
                                  f'{math.degrees(rho):.1f} deg, colour {np.round(col, 3)}')

    def build(self) -> np.ndarray:
        d = eq_dirs(EQ_W, EQ_H, EQ_SS)
        y = d[..., 1]
        elev = np.degrees(np.arcsin(np.clip(y, -1, 1)))
        if self.sky_tex is not None:
            uv = np.stack((d[..., 0], d[..., 2]), axis=-1) / np.maximum(y, 1e-3)[..., None] \
                * (1.0 / SKY_TILE_SCALE)
            tex = sample_wrap(self.sky_tex, uv[..., 0], uv[..., 1])
            w = smoothstep(0.05, 0.40, y)[..., None]  # in-game fog takes over near the horizon
            sky = self.sky_mean + (tex - self.sky_mean) * w
            for li, clouds in enumerate(self.cloud_layers[:3]):
                cuv = uv * 0.5 + np.array([0.31 * li, 0.17 * li])
                c = sample_wrap(clouds, cuv[..., 0], cuv[..., 1])
                a = c[..., 3:4] * CLOUD_STRENGTH * w
                sky = sky * (1 - a) + c[..., :3] * a
            horizon = self.sky_mean
        else:
            sky = np.full(d.shape, AIRLESS_SKY)
            for sdir, col, rho in self.sprites:
                theta = np.arccos(np.clip(d @ sdir, -1, 1))
                sky = sky + (1.0 - smoothstep(rho * 0.9, rho, theta))[..., None] * col
            horizon = np.full(3, AIRLESS_SKY)
        sky = np.where((y > 0)[..., None], sky, horizon)
        t = smoothstep(-HORIZON_BLEND_DEG, HORIZON_BLEND_DEG, elev)[..., None]
        img = self.ground * (1 - t) + sky * t
        return img.reshape(EQ_H, EQ_SS, EQ_W, EQ_SS, 3).mean(axis=(1, 3))

    @staticmethod
    def mean_sky(img: np.ndarray) -> np.ndarray:
        lat = PI / 2 - (np.arange(EQ_H) + 0.5) / EQ_H * PI
        sa = np.cos(lat)
        up = lat > 0
        return (img[up] * sa[up, None, None]).sum((0, 1)) / (sa[up].sum() * EQ_W)


class RadianceSource:
    """Equirect mip chain with trilinear lookups by direction."""

    def __init__(self, base: np.ndarray):
        self.levels = [base]
        while self.levels[-1].shape[1] > 8:
            b = self.levels[-1]
            self.levels.append(b.reshape(b.shape[0] // 2, 2, b.shape[1] // 2, 2, 3).mean(axis=(1, 3)))
        self.texel_solid_angle = 4 * PI / (base.shape[0] * base.shape[1])

    def lookup(self, d: np.ndarray, lod: np.ndarray | None = None) -> np.ndarray:
        u, v = dir_to_eq_uv(d)
        if lod is None:
            return sample_wrap(self.levels[0], u, v, wrap_v=False)
        top = len(self.levels) - 1
        lod = np.clip(lod, 0, top)
        fl = np.floor(lod).astype(np.int64)
        fr = (lod - fl)[..., None]
        out = np.zeros(d.shape)
        for lv in range(top + 1):
            lo = fl == lv
            hi = np.minimum(fl + 1, top) == lv
            if lo.any():
                out[lo] += (1 - fr[lo]) * sample_wrap(self.levels[lv], u[lo], v[lo], wrap_v=False)
            if hi.any():
                out[hi] += fr[hi] * sample_wrap(self.levels[lv], u[hi], v[hi], wrap_v=False)
        return out


# ------------------------------------- adapted from Generate-StaticIBL.py
def normalize(v: np.ndarray) -> np.ndarray:
    return v / np.maximum(np.linalg.norm(v, axis=-1, keepdims=True), 1e-12)


def radical_inverse_vdc(bits: np.ndarray) -> np.ndarray:
    bits = bits.astype(np.uint32)
    bits = ((bits << 16) | (bits >> 16)) & np.uint32(0xFFFFFFFF)
    bits = (((bits & 0x55555555) << 1) | ((bits & 0xAAAAAAAA) >> 1)) & np.uint32(0xFFFFFFFF)
    bits = (((bits & 0x33333333) << 2) | ((bits & 0xCCCCCCCC) >> 2)) & np.uint32(0xFFFFFFFF)
    bits = (((bits & 0x0F0F0F0F) << 4) | ((bits & 0xF0F0F0F0) >> 4)) & np.uint32(0xFFFFFFFF)
    bits = (((bits & 0x00FF00FF) << 8) | ((bits & 0xFF00FF00) >> 8)) & np.uint32(0xFFFFFFFF)
    return bits.astype(np.float64) * 2.3283064365386963e-10


def hammersley(count: int) -> np.ndarray:
    i = np.arange(count, dtype=np.uint32)
    return np.stack((i.astype(np.float64) / float(count), radical_inverse_vdc(i)), axis=-1)


def cube_directions(face: int, size: int) -> np.ndarray:
    # D3D cubemap convention. v grows downward in texture memory.
    uv = (np.arange(size, dtype=np.float64) + 0.5) / size * 2.0 - 1.0
    u, v = np.meshgrid(uv, uv)
    if face == 0:       # +X
        d = np.stack((np.ones_like(u), -v, -u), axis=-1)
    elif face == 1:     # -X
        d = np.stack((-np.ones_like(u), -v, u), axis=-1)
    elif face == 2:     # +Y
        d = np.stack((u, np.ones_like(u), v), axis=-1)
    elif face == 3:     # -Y
        d = np.stack((u, -np.ones_like(u), -v), axis=-1)
    elif face == 4:     # +Z
        d = np.stack((u, -v, np.ones_like(u)), axis=-1)
    else:               # -Z
        d = np.stack((-u, -v, -np.ones_like(u)), axis=-1)
    return normalize(d)


def tangent_basis(n: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
    up = np.where((np.abs(n[..., 2]) < 0.999)[..., None],
                  np.array([0.0, 0.0, 1.0]),
                  np.array([1.0, 0.0, 0.0]))
    t = normalize(np.cross(up, n))
    b = np.cross(n, t)
    return t, b


def local_to_world(local: np.ndarray, n: np.ndarray) -> np.ndarray:
    t, b = tangent_basis(n)
    return normalize(t[:, None, :] * local[None, :, 0:1]
                     + b[:, None, :] * local[None, :, 1:2]
                     + n[:, None, :] * local[None, :, 2:3])


def cosine_samples(count: int) -> np.ndarray:
    xi = hammersley(count)
    phi = 2.0 * PI * xi[:, 0]
    r = np.sqrt(xi[:, 1])
    return np.stack((r * np.cos(phi), r * np.sin(phi), np.sqrt(np.maximum(1.0 - xi[:, 1], 0.0))), axis=-1)


def ggx_half_vectors(count: int, roughness: float) -> np.ndarray:
    xi = hammersley(count)
    a = max(roughness * roughness, 1e-4)
    a2 = a * a
    phi = 2.0 * PI * xi[:, 0]
    cos_theta = np.sqrt((1.0 - xi[:, 1]) / np.maximum(1.0 + (a2 - 1.0) * xi[:, 1], 1e-8))
    sin_theta = np.sqrt(np.maximum(1.0 - cos_theta * cos_theta, 0.0))
    return np.stack((np.cos(phi) * sin_theta, np.sin(phi) * sin_theta, cos_theta), axis=-1)


def generate_irradiance(src: RadianceSource, size: int, samples: int) -> list[np.ndarray]:
    local = cosine_samples(samples)
    # Filtered importance sampling: pdf = cos/pi, so sample solid angle = pi/(N*cos).
    omega_s = PI / (samples * np.maximum(local[:, 2], 1e-3))
    lod = np.maximum(0.5 * np.log2(omega_s / src.texel_solid_angle) + 1.0, 0.0)
    faces = []
    for face in range(6):
        n = cube_directions(face, size).reshape(-1, 3)
        l = local_to_world(local, n)
        c = src.lookup(l, np.broadcast_to(lod, l.shape[:2])).mean(axis=1)
        faces.append(c.reshape(size, size, 3))
    return faces


def box_mip_chain(face: np.ndarray) -> list[np.ndarray]:
    """Mip 0 plus 2x2 box-filtered levels down to 1px."""
    chain = [face]
    while chain[-1].shape[0] > 1:
        f = chain[-1]
        chain.append(0.25 * (f[0::2, 0::2] + f[1::2, 0::2] + f[0::2, 1::2] + f[1::2, 1::2]))
    return chain


def generate_prefilter(src: RadianceSource, base_size: int, samples: int) -> list[list[np.ndarray]]:
    mip_count = int(math.log2(base_size)) + 1
    all_faces: list[list[np.ndarray]] = [[] for _ in range(6)]
    for mip in range(mip_count):
        size = max(1, base_size >> mip)
        roughness = mip / max(mip_count - 1, 1)
        if roughness > 1e-6:
            h_local = ggx_half_vectors(samples, roughness)
            a2 = max(roughness * roughness, 1e-4) ** 2
            ndoth = h_local[:, 2]
            dist = a2 / (PI * (ndoth * ndoth * (a2 - 1.0) + 1.0) ** 2)
            pdf = dist / 4.0  # D * NdotH / (4 VdotH) with N = V
            omega_s = 1.0 / (samples * np.maximum(pdf, 1e-8))
            lod = np.maximum(0.5 * np.log2(omega_s / src.texel_solid_angle) + 1.0, 0.0)
        for face in range(6):
            r = cube_directions(face, size).reshape(-1, 3)
            if roughness <= 1e-6:
                c = src.lookup(r)
            else:
                h = local_to_world(h_local, r)
                # Prefilter convention uses V=R=N for the lookup integration.
                vdoth = np.sum(r[:, None, :] * h, axis=-1, keepdims=True)
                l = normalize(2.0 * vdoth * h - r[:, None, :])
                ndotl = np.clip(np.sum(r[:, None, :] * l, axis=-1), 0.0, 1.0)
                colors = src.lookup(l, np.broadcast_to(lod, l.shape[:2]))
                weight = ndotl[..., None]
                c = np.sum(colors * weight, axis=1) / np.maximum(np.sum(weight, axis=1), 1e-8)
            all_faces[face].append(c.reshape(size, size, 3))
    return all_faces


def rgb565(c: np.ndarray) -> int:
    # Round to nearest 5/6/5 level (the original truncated 8-bit values).
    c = np.clip(c, 0.0, 1.0)
    return (int(round(c[0] * 31.0)) << 11) | (int(round(c[1] * 63.0)) << 5) | int(round(c[2] * 31.0))


def unpack565(v: int) -> np.ndarray:
    return np.array([((v >> 11) & 31) / 31.0, ((v >> 5) & 63) / 63.0, (v & 31) / 31.0])


def bc1_compress(image: np.ndarray) -> bytes:
    h, w, _ = image.shape
    ph = max(4, ((h + 3) // 4) * 4)
    pw = max(4, ((w + 3) // 4) * 4)
    padded = image[np.minimum(np.arange(ph), h - 1)][:, np.minimum(np.arange(pw), w - 1)]

    out = bytearray()
    lum_w = np.array([0.299, 0.587, 0.114])
    for by in range(0, ph, 4):
        for bx in range(0, pw, 4):
            block = padded[by:by + 4, bx:bx + 4].reshape(16, 3)
            lum = block @ lum_w
            v0 = rgb565(block[int(np.argmax(lum))])
            v1 = rgb565(block[int(np.argmin(lum))])
            if v0 == v1:
                if v0 < 0xFFFF:
                    v0 += 1
                elif v1 > 0:
                    v1 -= 1
            if v0 < v1:
                v0, v1 = v1, v0
            p0, p1 = unpack565(v0), unpack565(v1)
            palette = np.stack((p0, p1, (2.0 * p0 + p1) / 3.0, (p0 + 2.0 * p1) / 3.0))
            dist = np.sum((block[:, None, :] - palette[None, :, :]) ** 2, axis=-1)
            idx = np.argmin(dist, axis=1)
            bits = 0
            for i, code in enumerate(idx):
                bits |= int(code) << (2 * i)
            out += struct.pack('<HHI', v0, v1, bits)
    return bytes(out)


def dds_header_bc1(width: int, height: int, mip_count: int) -> bytes:
    flags = 0x1 | 0x2 | 0x4 | 0x1000 | 0x80000 | 0x20000
    caps = 0x1000 | 0x8 | 0x400000
    linear_size = max(1, (width + 3) // 4) * max(1, (height + 3) // 4) * 8
    fourcc = struct.unpack('<I', b'DXT1')[0]
    header = struct.pack('<I', 124)
    header += struct.pack('<IIIIII', flags, height, width, linear_size, 0, mip_count)
    header += struct.pack('<11I', *([0] * 11))
    header += struct.pack('<8I', 32, 0x4, fourcc, 0, 0, 0, 0, 0)
    header += struct.pack('<IIIII', caps, 0xFE00, 0, 0, 0)
    assert len(header) == 124
    return b'DDS ' + header


def cube_dds_bytes(faces_mips: list[list[np.ndarray]]) -> bytes:
    base = faces_mips[0][0].shape[0]
    mips = len(faces_mips[0])
    out = bytearray(dds_header_bc1(base, base, mips))
    for face in range(6):  # +X -X +Y -Y +Z -Z, all mips per face
        for mip in range(mips):
            out += bc1_compress(np.clip(faces_mips[face][mip], 0.0, 1.0))
    return bytes(out)


# ------------------------------------------------------------ preview / main
def cube_to_equirect(face_imgs: list[np.ndarray], w: int, h: int) -> np.ndarray:
    """Nearest-texel equirect view of a cube (inverse of cube_directions)."""
    d = eq_dirs(w, h)
    size = face_imgs[0].shape[0]
    major = np.argmax(np.abs(d), axis=-1)
    out = np.zeros((h, w, 3))
    for face in range(6):
        axis = face // 2
        sign = 1.0 if face % 2 == 0 else -1.0
        sel = (major == axis) & (np.sign(d[..., axis]) == sign)
        if not sel.any():
            continue
        dd = d[sel]
        m = np.abs(dd[:, axis])
        if face == 0:
            u, v = -dd[:, 2], -dd[:, 1]
        elif face == 1:
            u, v = dd[:, 2], -dd[:, 1]
        elif face == 2:
            u, v = dd[:, 0], dd[:, 2]
        elif face == 3:
            u, v = dd[:, 0], -dd[:, 2]
        elif face == 4:
            u, v = dd[:, 0], -dd[:, 1]
        else:
            u, v = -dd[:, 0], -dd[:, 1]
        ix = np.clip(((u / m) * 0.5 + 0.5) * size, 0, size - 1).astype(int)
        iy = np.clip(((v / m) * 0.5 + 0.5) * size, 0, size - 1).astype(int)
        out[sel] = face_imgs[face][iy, ix]
    return out


def to_png(img: np.ndarray) -> Image.Image:
    return Image.fromarray((linear_to_srgb(img) * 255 + 0.5).astype(np.uint8))


def verify_headers(out_dir: Path, written: list[Path]) -> None:
    for kind in ('prefilter', 'irradiance'):
        ref = (out_dir / f'openshim_ibl_neutral_{kind}.dds').read_bytes()
        for p in written:
            if p.name.endswith(f'_{kind}.dds'):
                data = p.read_bytes()
                # Same size and caps as the neutral file; mip count (offset 28)
                # may be larger, never smaller.
                ref_mips = struct.unpack_from('<I', ref, 28)[0]
                mips = struct.unpack_from('<I', data, 28)[0]
                if data[12:20] != ref[12:20] or data[76:128] != ref[76:128] or mips < ref_mips:
                    raise SystemExit(f'HEADER MISMATCH: {p.name}')
    print(f'verified {len(written)} files: size, format and caps match the neutral references')


def main() -> None:
    root = Path(__file__).resolve().parents[2]
    ap = argparse.ArgumentParser(description='Bake per-planet IBL cubemaps for BZ98 Redux.')
    ap.add_argument('--game-dir', type=Path, required=True, help='Battlezone 98 Redux install (read only)')
    ap.add_argument('--output', type=Path, default=root / 'resources/renderer/enhanced')
    ap.add_argument('--preview-dir', type=Path, default=None, help='optional equirect PNG previews + contact sheet')
    ap.add_argument('--worlds', default=','.join(WORLDS), help='comma list of world codes')
    ap.add_argument('--samples', type=int, default=128)
    args = ap.parse_args()
    args.output.mkdir(parents=True, exist_ok=True)
    if args.preview_dir:
        args.preview_dir.mkdir(parents=True, exist_ok=True)

    written: list[Path] = []
    previews = []
    for code in [c.strip() for c in args.worlds.split(',') if c.strip()]:
        ps = PlanetSky(code, args.game_dir)
        base = ps.build()
        print(f'[{code}] {ps.name}: mean upper sky {np.round(ps.mean_sky(base), 4)}, '
              f'ground {np.round(ps.ground, 4)} (atlas mean {np.round(ps.ground_mean, 4)})')
        for n in ps.notes:
            print(f'    note: {n}')
        src = RadianceSource(base)
        pre = generate_prefilter(src, 128, args.samples)
        irr = generate_irradiance(src, 32, args.samples * 2)
        for kind, data in (('prefilter', cube_dds_bytes(pre)), ('irradiance', cube_dds_bytes([box_mip_chain(f) for f in irr]))):
            p = args.output / f'openshim_env_{code}_{kind}.dds'
            p.write_bytes(data)
            written.append(p)
            print(f'    {p.name}: {len(data)} bytes')
        if args.preview_dir:
            img = to_png(cube_to_equirect([pre[f][0] for f in range(6)], 1024, 512))
            img.save(args.preview_dir / f'env_{code}_{ps.name.lower()}.png')
            previews.append((ps.name, img))
    if (args.output / 'openshim_ibl_neutral_prefilter.dds').exists():
        verify_headers(args.output, written)
    if previews:
        tw, th = 512, 256
        sheet = Image.new('RGB', (3 * tw, 3 * th), (24, 24, 24))
        dr = ImageDraw.Draw(sheet)
        for i, (name, img) in enumerate(previews):
            x, y = (i % 3) * tw, (i // 3) * th
            sheet.paste(img.resize((tw, th), Image.LANCZOS), (x, y))
            dr.text((x + 6, y + 4), name, fill=(255, 255, 0))
        sheet.save(args.preview_dir / 'contact_sheet.png')
    print(f'total bytes: {sum(p.stat().st_size for p in written)}')


if __name__ == '__main__':
    main()
