"""Show actual captured pixels at useful scale, with an explicitly amplified delta."""
import argparse
import json
from pathlib import Path

import numpy as np
from PIL import Image, ImageDraw, ImageFont

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('before', type=Path)
parser.add_argument('after', type=Path)
parser.add_argument('output', type=Path)
parser.add_argument('--crop', type=int, nargs=4, metavar=('X', 'Y', 'W', 'H'))
parser.add_argument('--after-label', default='DXR AO')
parser.add_argument('--before-label', default='Original raster')
args = parser.parse_args()
before = Image.open(args.before).convert('RGB')
after = Image.open(args.after).convert('RGB')
if before.size != after.size:
    raise ValueError('Capture extents differ')
a, b = np.asarray(before).astype(np.int16), np.asarray(after).astype(np.int16)
delta = np.max(np.abs(a - b), axis=2)
crop = args.crop or [0, 0, *before.size]
x, y, w, h = crop
if min(x, y) < 0 or min(w, h) <= 0 or x+w > before.width or y+h > before.height:
    raise ValueError('Crop outside capture')
box = (x, y, x+w, y+h)
# Heatmap is evidence of changed pixels, never presented as rendered lighting.
heat = np.zeros((*delta.shape, 3), dtype=np.uint8)
heat[:, :, 0] = np.minimum(delta.astype(np.int32)*8, 255)
heat[:, :, 1] = np.minimum(delta.astype(np.int32)*2, 255)
panels = [before.crop(box), after.crop(box), Image.fromarray(heat).crop(box)]
panel_width = 640
panel_height = round(h*panel_width/w)
out = Image.new('RGB', (panel_width*3+40, panel_height+90), '#10171c')
draw = ImageDraw.Draw(out)
font_path = Path('C:/Windows/Fonts/segoeui.ttf')
font = ImageFont.truetype(str(font_path), 23) if font_path.exists() else ImageFont.load_default()
for index, (panel, label) in enumerate(zip(panels, [args.before_label, args.after_label, 'Pixel difference (8x red gain)'])):
    offset = 10+index*(panel_width+10)
    draw.text((offset, 10), label, font=font, fill='#a5e5cc')
    out.paste(panel.resize((panel_width, panel_height), Image.Resampling.NEAREST), (offset, 48))
draw.text((10, panel_height+54), f'Pixel comparison | crop {x},{y} {w}x{h} | before/after colors unchanged', font=font, fill='#c2c9cf')
out.save(args.output)
report = {'before': str(args.before.resolve()), 'after': str(args.after.resolve()),
          'crop': crop, 'changedPixelsOver2': int(np.count_nonzero(delta > 2)),
          'maximumChannelDelta': int(delta.max()), 'differenceRedGain': 8}
report['cropChangedPixelsOver2'] = int(np.count_nonzero(delta[y:y+h, x:x+w] > 2))
args.output.with_suffix('.json').write_text(json.dumps(report, indent=2)+'\n')
print(json.dumps(report))
