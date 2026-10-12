"""Build a guarded linear normal atlas from explicit terrain height artwork.

Uses a live engine tile-to-atlas capture, never TRN/HG2/MAT parsing. Height
art changes lighting only in the current native integration, not geometry.
"""
import argparse
import hashlib
import importlib.util
import json
import math
from pathlib import Path
import re
import struct
from PIL import Image

spec = importlib.util.spec_from_file_location('hd_pack', Path(__file__).with_name('Build-TerrainHdPack.py'))
hd = importlib.util.module_from_spec(spec)
spec.loader.exec_module(hd)


def unit_normal(rgb):
    v = [c / 127.5 - 1 for c in rgb[:3]]
    length = math.sqrt(sum(c * c for c in v))
    if length < .01 or v[2] <= 0:
        return (0., 0., 1.)
    return tuple(c / length for c in v)


def samples(image):
    # Pillow 13 renamed the flattened-data reader; retain older authoring hosts.
    getter = getattr(image, 'get_flattened_data', None)
    return getter() if getter else image.getdata()


def encode_normal(v):
    length = math.sqrt(sum(c * c for c in v))
    return tuple(max(0, min(255, round(127.5 * (c / length + 1)))) for c in v) + (255,)


def renormalize(image):
    result = Image.new('RGBA', image.size)
    result.putdata([encode_normal(unit_normal(p)) for p in samples(image.convert('RGBA'))])
    return result


def height_normals(stock, height, amplitude, tile_meters, edge_pixels):
    """Linear height in [0,1]; quintic envelope gives zero edge height/slope."""
    size = stock.width
    if stock.height != size or height.size != stock.size:
        raise ValueError('normal/height tiles must be matching squares')
    if type(amplitude) not in (int, float) or not math.isfinite(amplitude) or not 0 < amplitude <= 1:
        raise ValueError('heightMeters must be finite and in (0,1]')
    if type(tile_meters) not in (int, float) or not math.isfinite(tile_meters) or not 1 <= tile_meters <= 100:
        raise ValueError('tileMeters must be finite and in 1..100')
    if type(edge_pixels) is not int or not 2 <= edge_pixels <= size // 2:
        raise ValueError('edgePixels must be 2..half the tile size')
    def fade(x):
        t = min(1., min(x, size - 1 - x) / edge_pixels)
        return t**3 * (t * (t * 6 - 15) + 10)
    raw = list(samples(height))
    if any(not math.isfinite(h) or not 0 <= h <= 1 for h in raw):
        raise ValueError('height samples must be finite linear data in [0,1]')
    heights = [(2 * raw[y * size + x] - 1) * amplitude * fade(x) * fade(y)
               for y in range(size) for x in range(size)]
    pixels = list(samples(stock.convert('RGBA')))
    result = []
    spacing = tile_meters / (size - 1)
    for y in range(size):
        for x in range(size):
            if x in (0, size - 1) or y in (0, size - 1):
                result.append(pixels[y * size + x])  # exact original boundary
                continue
            du = (heights[y * size + x + 1] - heights[y * size + x - 1]) / (2 * spacing)
            dv = (heights[(y + 1) * size + x] - heights[(y - 1) * size + x]) / (2 * spacing)
            base = unit_normal(pixels[y * size + x])
            # Gradient perturbation in +U/+V texture coordinates. The native
            # UV-derived tangent frame applies the tile rotation/reflection.
            result.append(encode_normal((base[0] - base[2] * du, base[1] - base[2] * dv, base[2])))
    normal = Image.new('RGBA', stock.size)
    normal.putdata(result)
    return normal, heights


def read_height(root, entry, size):
    path = hd.source_path(root, entry)
    with Image.open(path) as image:
        if image.mode not in ('L', 'I;16', 'I;16L', 'I;16B', 'I', 'F'):
            raise ValueError('height artwork must be a single-channel linear 8/16-bit or float image')
        mode = image.mode
        image.load()
        values = list(samples(image))
        maximum = 255 if mode == 'L' else (1 if mode == 'F' else 65535)
        if any(not math.isfinite(v) or not 0 <= v <= maximum for v in values):
            raise ValueError('invalid height channel range')
        height = Image.new('F', image.size)
        height.putdata([v / maximum for v in values])
        height = height.resize(size, Image.Resampling.BILINEAR)
    return height, {'file': entry, 'sha256': hashlib.sha256(path.read_bytes()).hexdigest(), 'inputMode': mode}


def dds_bytes(levels):
    """Legacy uncompressed RGBA8 DDS, full linear normal-vector mip chain."""
    width, height = levels[0].size
    header = [124, 0x2100f, height, width, width * 4, 0, len(levels)] + [0] * 11
    header += [32, 0x41, 0, 32, 0xff, 0xff00, 0xff0000, 0xff000000]
    header += [0x401008 if len(levels) > 1 else 0x1000, 0, 0, 0, 0]
    assert len(header) == 31
    return b'DDS ' + struct.pack('<31I', *header) + b''.join(level.convert('RGBA').tobytes() for level in levels)


def build(capture_path, normal_atlas_path, recipe_path, source_root, output, prefix='openshim_surface'):
    if not re.fullmatch(r'[a-z][a-z0-9_]{0,63}', prefix):
        raise ValueError('prefix must be a lowercase resource name')
    capture = hd.read_json(capture_path)
    recipe = hd.read_json(recipe_path)
    if capture.get('schema') != 'bzr-openshim-terrain-atlas-v1' or recipe.get('schema') != 'bzr-openshim-terrain-surface-art-v1':
        raise ValueError('requires live tile capture and surface artwork recipe')
    source_normal = recipe.get('sourceNormalResource')
    if not isinstance(source_normal, str) or not source_normal or Path(normal_atlas_path).name.lower() != source_normal.lower():
        raise ValueError('normal source filename does not match recipe identity')
    with Image.open(normal_atlas_path) as image:
        atlas = image.convert('RGBA')
    if atlas.width != atlas.height or atlas.width < 64 or atlas.width > 8192 or atlas.width & (atlas.width - 1):
        raise ValueError('source normal atlas must be a square power of two, 64..8192')
    tiles = capture.get('tiles', {})
    used = capture.get('usedIndices', [])
    if not used or any(type(i) is not int or str(i) not in tiles for i in used):
        raise ValueError('capture does not cover used engine tiles')
    edits = recipe.get('tiles', {})
    if not isinstance(edits, dict) or not edits:
        raise ValueError('recipe needs explicit engine tile heights')
    root = Path(source_root).resolve()
    boxes, rows = {}, []
    for key, entry in edits.items():
        if not re.fullmatch(r'0|[1-9][0-9]*', key) or key not in tiles or not isinstance(entry, dict):
            raise ValueError('unknown/invalid engine tile override')
        box = hd.pixel_box(tiles[key], atlas.width, atlas.height)
        aliases = []
        for other_key, rect in tiles.items():
            other = hd.pixel_box(rect, atlas.width, atlas.height)
            if other == box:
                aliases.append(int(other_key))
            elif min(box[2], other[2]) > max(box[0], other[0]) and min(box[3], other[3]) > max(box[1], other[1]):
                raise ValueError('selected height overlaps another non-identical atlas rectangle')
        size = (box[2] - box[0], box[3] - box[1])
        height, identity = read_height(root, entry['height'], size)
        normal, values = height_normals(atlas.crop(box), height, entry.get('heightMeters', .25),
                                       recipe.get('tileMeters', 20), recipe.get('edgePixels', max(2, size[0] // 8)))
        digest = hashlib.sha256(normal.tobytes()).hexdigest()
        if box in boxes and boxes[box][0] != digest:
            raise ValueError('different heights target aliased engine tile rectangles')
        boxes[box] = (digest, normal)
        rows.append({'engineIndex': int(key), 'aliasedEngineIndices': sorted(aliases), 'box': box, 'source': identity,
                     'heightMeters': entry.get('heightMeters', .25), 'heightMinimum': min(values), 'heightMaximum': max(values)})
    for box, (_, normal) in boxes.items():
        atlas.paste(normal, box[:2])
    levels = [atlas]
    while levels[-1].width > 1:
        last = levels[-1]
        levels.append(renormalize(last.resize((last.width // 2, last.height // 2), Image.Resampling.BOX)))
    resource = prefix + '_normal.dds'
    manifest = {'schema': 'bzr-openshim-terrain-surface-v1', 'material': capture['material'],
                'sourceDiffuseResource': capture['diffuseResource'], 'sourceNormalResource': source_normal,
                'normalAtlas': resource, 'width': atlas.width, 'height': atlas.height,
                'normalEncoding': 'rgb-xyz-linear', 'heightUsage': 'normal-lighting-only'}
    report = {'schema': 'bzr-openshim-terrain-surface-report-v1', 'heightGeometry': False,
              'normalSourceSha256': hashlib.sha256(Path(normal_atlas_path).read_bytes()).hexdigest(),
              'mipLevels': len(levels), 'tiles': rows, 'normalAtlasSha256': hashlib.sha256(dds_bytes(levels)).hexdigest()}
    output = Path(output)
    targets = [output / resource, output / (prefix + '.json'), output / (prefix + '_report.json')]
    if any(p.exists() for p in targets):
        raise ValueError('output exists; choose a new directory/prefix')
    output.mkdir(parents=True, exist_ok=True)
    targets[0].write_bytes(dds_bytes(levels))
    targets[2].write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    targets[1].write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
    return targets[1], report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('capture', 'normal-atlas', 'recipe', 'source-root', 'output'):
        parser.add_argument('--' + name, required=True, type=Path)
    parser.add_argument('--prefix', default='openshim_surface')
    args = parser.parse_args()
    path, report = build(args.capture, args.normal_atlas, args.recipe, args.source_root, args.output, args.prefix)
    print(f'BUILT {path}: {len(report["tiles"])} authored height tiles, {report["mipLevels"]} linear normal mips; geometry unchanged')


if __name__ == '__main__':
    main()
