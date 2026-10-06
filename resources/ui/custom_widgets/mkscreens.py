"""Paint the centre panels of OpenShim's own shell screens.

A stock Redux screen is a cUI_View "Top Screen" (stock background plus the
four border views) with one 1440x1080 overlay whose texture is a painted
panel: the frame, header and boxes are art, and the widgets sit on top of the
painted boxes. These panels are drawn the same way, at the exact size they are
shown, so nothing is stretched.

Everything is drawn from geometry in the stock palette (sampled from
Options/goptions_center.png and Multiplayer/multi2_center.png); no stock
pixels are copied. Transparent outside the frame, like the stock panels, so
the stock background shows through.

The box rectangles here are the layout contract with the screen code: keep
CAREER_LAYOUT in step with the constants in src/patches/career_screen.cpp.

    python mkscreens.py            # writes osh_career_center.png
    python mkscreens.py --preview  # also writes *_preview.png over black
"""
import sys
from pathlib import Path

from PIL import Image, ImageDraw

HERE = Path(__file__).resolve().parent
SS = 2  # supersampling factor; drawn at 2x and reduced for clean diagonals

# Stock palette.
FILL = (0, 44, 1, 255)        # frame body
LINE = (0, 84, 0, 255)        # frame outline and trace lines
HILITE = (0, 127, 0, 255)     # header underline, box rims
ACCENT = (18, 165, 28, 255)   # corner notches
BOX = (0, 0, 0, 236)          # box interior; near-opaque black like the stock boxes
HEADER = (0, 30, 1, 255)      # box header band

W, H = 1440, 1080


def s(v):
    return int(round(v * SS))


def chamfer_poly(x, y, w, h, c):
    """Rectangle with all four corners cut at 45 degrees by c."""
    return [(x + c, y), (x + w - c, y), (x + w, y + c), (x + w, y + h - c),
            (x + w - c, y + h), (x + c, y + h), (x, y + h - c), (x, y + c)]


def poly(d, pts, fill=None, outline=None, width=1):
    pts = [(s(px), s(py)) for px, py in pts]
    if fill:
        d.polygon(pts, fill=fill)
    if outline:
        d.line(pts + [pts[0]], fill=outline, width=s(width), joint='curve')


def frame(d):
    """Outer frame after the Options panels: a stadium-shaped body whose
    middle is cut out as a chamfered black field, leaving two side brackets
    with half-round outer edges and short arms along the top and bottom,
    plus a trace band above and below."""
    top, bot = 120, 960
    # Trace bands across the full width: a dark strip of five lines with a
    # connector block at the centre, after the stock bands.
    for band_y in (top - 44, bot + 4):
        d.rectangle([s(0), s(band_y), s(W), s(band_y + 40)], fill=(0, 0, 0, 255))
        for k in range(5):
            y = band_y + 6 + k * 7
            colour = LINE if k % 2 == 0 else FILL
            d.rectangle([s(0), s(y), s(W), s(y + 2)], fill=colour)
        poly(d, chamfer_poly(670, band_y - 2, 100, 44, 8), fill=FILL, outline=LINE, width=2)
        for k in range(7):
            x = 688 + k * 11
            d.rectangle([s(x), s(band_y + 8), s(x + 3), s(band_y + 34)], fill=ACCENT if k == 3 else LINE)
    # Body.
    d.rounded_rectangle([s(0), s(top), s(W), s(bot)], radius=s((bot - top) / 2),
                        fill=FILL, outline=LINE, width=s(2))
    # Inner field: open between the arms, chamfered where the arms turn.
    inner = [(372, top), (W - 372, top), (W - 372, 195), (W - 265, 195), (W - 208, 252),
             (W - 208, bot - 132), (W - 265, bot - 75), (W - 372, bot - 75), (W - 372, bot),
             (372, bot), (372, bot - 75), (265, bot - 75), (208, bot - 132), (208, 252),
             (265, 195), (372, 195)]
    poly(d, inner, fill=(0, 0, 0, 255), outline=LINE, width=2)
    # The field runs into the bands, so the outline must not close across them.
    d.rectangle([s(374), s(top - 1), s(W - 374), s(top + 2)], fill=(0, 0, 0, 255))
    d.rectangle([s(374), s(bot - 2), s(W - 374), s(bot + 1)], fill=(0, 0, 0, 255))
    # A recessed slot across each bracket's waist, the way the stock pods
    # break their brackets at mid height.
    for x0, x1 in ((0, 208), (W - 208, W)):
        d.rectangle([s(x0), s(H / 2 - 40), s(x1), s(H / 2 + 40)], fill=(0, 0, 0, 255))
        d.rectangle([s(x0), s(H / 2 - 40), s(x1), s(H / 2 - 38)], fill=LINE)
        d.rectangle([s(x0), s(H / 2 + 38), s(x1), s(H / 2 + 40)], fill=LINE)
        for k in range(6):
            gy = H / 2 - 26 + k * 10
            d.rectangle([s(x0 + 14), s(gy), s(x1 - 14), s(gy + 2)], fill=FILL if k % 2 else LINE)


def box(d, x, y, w, h, header_h=44):
    """A content box: chamfered black plate, rim, header band, corner notches."""
    c = 14
    poly(d, chamfer_poly(x, y, w, h, c), fill=BOX, outline=HILITE, width=2)
    # Header band under the top rim.
    hb = [(x + c, y + 3), (x + w - c, y + 3), (x + w - 3, y + c), (x + w - 3, y + header_h),
          (x + 3, y + header_h), (x + 3, y + c)]
    poly(d, hb, fill=HEADER)
    d.rectangle([s(x + 3), s(y + header_h), s(x + w - 3), s(y + header_h + 2)], fill=HILITE)
    # Corner notches on the two bottom chamfers.
    for nx, ny, dx in ((x + 2, y + h - c - 2, 1), (x + w - 2, y + h - c - 2, -1)):
        tri = [(nx, ny), (nx + dx * 12, ny + 12), (nx, ny + 12)]
        poly(d, tri, fill=ACCENT)


def title_plate(d, x, y, w, h):
    """The screen title plate: a wide chamfered bar with a bright underline."""
    poly(d, chamfer_poly(x, y, w, h, 18), fill=FILL, outline=LINE, width=2)
    d.rectangle([s(x + 40), s(y + h - 8), s(x + w - 40), s(y + h - 6)], fill=HILITE)


# Layout contract with src/patches/career_screen.cpp (1440x1080 design space).
CAREER_LAYOUT = {
    'title': (470, 132, 500, 56),
    'boxes': [
        (244, 238, 464, 300),   # Overall
        (732, 238, 464, 300),   # Single player
        (244, 566, 464, 300),   # Multiplayer
        (732, 566, 464, 300),   # Record
    ],
}


def career_center():
    img = Image.new('RGBA', (s(W), s(H)), (0, 0, 0, 0))
    d = ImageDraw.Draw(img)
    frame(d)
    title_plate(d, *CAREER_LAYOUT['title'])
    for b in CAREER_LAYOUT['boxes']:
        box(d, *b)
    return img.resize((W, H), Image.LANCZOS)


def main():
    out = HERE / 'osh_career_center.png'
    img = career_center()
    img.save(out, optimize=True)
    print('wrote', out.name, img.size)
    if '--preview' in sys.argv:
        bg = Image.new('RGBA', img.size, (0, 0, 0, 255))
        bg.alpha_composite(img)
        prev = HERE / 'osh_career_center_preview.png'
        bg.convert('RGB').save(prev)
        print('wrote', prev.name)


if __name__ == '__main__':
    main()
