"""Inspect RGB float PFM camera-motion diagnostics; never qualify DLSS inputs."""
import argparse
from array import array
import json
import math
from pathlib import Path
import sys
from PIL import Image, ImageDraw


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('motion', type=Path)
    parser.add_argument('--color', type=Path)
    parser.add_argument('--scale-pixels', type=float, default=1.0)
    args = parser.parse_args()
    if not math.isfinite(args.scale_pixels) or args.scale_pixels <= 0:
        raise ValueError('Color scale must be finite and positive')
    with args.motion.open('rb') as source:
        if source.readline() != b'PF\n':
            raise ValueError('Expected RGB float PFM')
        width, height = map(int, source.readline().split())
        if not 0 < width <= 8192 or not 0 < height <= 8192 or source.readline() != b'-1.0\n':
            raise ValueError('Unsupported dimensions or endian/scale')
        payload = source.read(width * height * 12 + 1)
    if len(payload) != width * height * 12:
        raise ValueError('Truncated/oversized motion payload')
    values = array('f')
    values.frombytes(payload)
    if sys.byteorder != 'little':
        values.byteswap()
    metadata = json.loads(Path(str(args.motion) + '.json').read_text(encoding='utf-8-sig'))
    if metadata.get('diagnosticOnly') is not True or metadata.get('dlssReady') is not False or \
            metadata.get('width') != width or metadata.get('height') != height or \
            metadata['currentFrameId'] - metadata['previousFrameId'] != 1:
        raise ValueError('Invalid diagnostic pair metadata')
    pixels = bytearray(width * height * 3)
    valid_count = 0
    maximum = 0.0
    squared = 0.0
    for y in range(height):
        for x in range(width):
            at = ((height - 1 - y) * width + x) * 3
            dx, dy, valid = values[at:at + 3]
            if not all(math.isfinite(v) for v in (dx, dy, valid)) or valid not in (0, 1):
                raise ValueError('Invalid float or validity mask')
            if not valid:
                if dx != 0 or dy != 0:
                    raise ValueError('Absent vectors must have zero channels')
                continue
            valid_count += 1
            length = math.hypot(dx, dy)
            maximum = max(maximum, length)
            squared += length * length
            dst = (y * width + x) * 3
            pixels[dst] = round(128 + max(-1, min(1, dx / args.scale_pixels)) * 127)
            pixels[dst + 1] = round(128 + max(-1, min(1, -dy / args.scale_pixels)) * 127)
            pixels[dst + 2] = 64
    if valid_count != metadata['validPixels'] or abs(maximum - metadata['maximumPixels']) > max(1e-6, maximum * 1e-6):
        raise ValueError('Motion payload does not match metadata stats')
    preview = Image.frombytes('RGB', (width, height), bytes(pixels))
    path = args.motion.with_suffix('.motion.png')
    preview.save(path)
    stats = {
        'diagnosticOnly': True, 'validPixels': valid_count,
        'maximumPixels': maximum, 'rmsPixels': math.sqrt(squared / valid_count) if valid_count else 0,
        'visualizationScalePixels': args.scale_pixels,
        'meaning': 'R=positive X, G=negative Y, neutral olive=zero, black=absent; static-scene camera reprojection only',
    }
    args.motion.with_suffix('.stats.json').write_text(json.dumps(stats, indent=2) + '\n', encoding='utf-8')
    if args.color:
        color = Image.open(args.color).convert('RGB')
        if color.size != preview.size:
            raise ValueError('Color/motion extent mismatch')
        comparison = Image.new('RGB', (width * 2, height + 28))
        comparison.paste(color, (0, 28)); comparison.paste(preview, (width, 28))
        draw = ImageDraw.Draw(comparison)
        draw.text((8, 8), f"Captured color frame {metadata['currentFrameId']}", fill='white')
        draw.text((width + 8, 8), f"Camera motion diagnostic: {metadata['previousFrameId']} -> {metadata['currentFrameId']} (objects/HUD omitted)", fill='white')
        comparison.save(args.motion.with_suffix('.comparison.png'))
    print(json.dumps(stats, indent=2))
    print(path)


if __name__ == '__main__':
    main()
