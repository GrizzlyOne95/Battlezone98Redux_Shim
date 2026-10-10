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
CAREER_LAYOUT in step with the constants in src/patches/career_screen.cpp, and
PRELOBBY_LAYOUT with src/patches/prelobby_screen.cpp.

    python mkscreens.py            # writes every osh_*_center.png and button skin
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


# Layout contract with src/patches/prelobby_screen.cpp (1440x1080 design space).
# The PLAYER box holds the nickname panel (240x144) and the flag picker (224x170
# preview with the 48px arrows 8 below it) side by side, each centred in a half.
PRELOBBY_LAYOUT = {
    'title': (470, 132, 500, 56),
    'boxes': [
        (244, 238, 952, 330),   # Player
        (244, 596, 952, 200),   # Connection
    ],
}


def prelobby_center():
    img = Image.new('RGBA', (s(W), s(H)), (0, 0, 0, 0))
    d = ImageDraw.Draw(img)
    frame(d)
    title_plate(d, *PRELOBBY_LAYOUT['title'])
    for b in PRELOBBY_LAYOUT['boxes']:
        box(d, *b)
    return img.resize((W, H), Image.LANCZOS)


# Stock option-slot colours, sampled from Options/optionhv.png, optionck.png
# and the painted slots in Options/esc_center.png.
SLOT_RIM = (0, 127, 0, 255)
SLOT_SHADE = (0, 43, 0, 255)
SLOT_SPARK = (96, 255, 96, 255)
SLOT_CUT = (0, 119, 0, 255)
SLOT_HOVER = (0, 84, 0, 255)
SLOT_PRESS = (0, 127, 0, 255)
CONNECT = (0, 23, 2, 255)


def slot(d, x, y, w, h, fill=(0, 0, 0, 255), mark=None):
    """An option slot after the stock ones: a plate with a bright rim along
    the top and right, a shaded rim along the left and bottom, a lit triangle
    in the top-left corner and a cut corner at the bottom right. Painted into
    a panel it is the resting state; the button's hover and press textures
    are the same slot with a filled body, drawn by slot_texture."""
    cut = max(8, min(40, h * 0.32))
    tri = max(10, min(56, h * 0.42))
    body = [(x, y), (x + w, y), (x + w, y + h - cut), (x + w - cut, y + h), (x, y + h)]
    poly(d, body, fill=fill)
    d.line([(s(x), s(y + 1)), (s(x + w), s(y + 1))], fill=SLOT_RIM, width=s(2))
    d.line([(s(x + w - 1), s(y)), (s(x + w - 1), s(y + h - cut))], fill=SLOT_RIM, width=s(2))
    d.line([(s(x + 1), s(y)), (s(x + 1), s(y + h))], fill=SLOT_SHADE, width=s(3))
    d.line([(s(x), s(y + h - 1)), (s(x + w - cut), s(y + h - 1))], fill=SLOT_SHADE, width=s(3))
    poly(d, [(x + w, y + h - cut), (x + w, y + h), (x + w - cut, y + h)], fill=SLOT_CUT)
    poly(d, [(x + 2, y + 2), (x + tri, y + 2), (x + 2, y + tri)], fill=mark or SLOT_RIM)
    poly(d, [(x + 2, y + 2), (x + tri * 0.3, y + 2), (x + 2, y + tri * 0.3)], fill=SLOT_SPARK)
    # The stock slot's twin bevel strokes beside the lit corner.
    for k in (0.55, 0.8):
        d.line([(s(x + tri * k + 4), s(y + 4)), (s(x + 4), s(y + tri * k + 4))],
               fill=SLOT_RIM, width=s(2))


def slot_texture(w, h, fill):
    img = Image.new('RGBA', (s(w), s(h)), (0, 0, 0, 0))
    slot(ImageDraw.Draw(img), 0, 0, w, h, fill=fill)
    return img.resize((w, h), Image.LANCZOS)


def connector(d, x, y, w, h):
    """The dark band with a centre block that links stacked stock slots."""
    d.rectangle([s(x), s(y), s(x + w), s(y + h)], fill=CONNECT)
    bw = min(130, w * 0.4)
    poly(d, chamfer_poly(x + (w - bw) / 2, y + 2, bw, h - 4, 4), fill=FILL, outline=LINE, width=2)
    for k in range(7):
        gx = x + w / 2 - 33 + k * 11
        d.rectangle([s(gx), s(y + 6), s(gx + 3), s(y + h - 6)], fill=ACCENT if k == 3 else LINE)


def text_well(d, x, y, w, h):
    """A recessed strip for a row caption."""
    d.rectangle([s(x), s(y), s(x + w), s(y + h)], fill=(0, 14, 1, 255))
    d.rectangle([s(x), s(y + h - 2), s(x + w), s(y + h)], fill=LINE)


def new_panel():
    img = Image.new('RGBA', (s(W), s(H)), (0, 0, 0, 0))
    d = ImageDraw.Draw(img)
    frame(d)
    return img, d


# Layout contract with src/patches/bzr_options_ui.cpp (OpenShim options).
# The stock Options screen with a fifth slot: the four stock buttons and the
# OpenShim button are re-placed on these rects, so the column is even.
OPTIONS_LAYOUT = {
    'slot': (508, 180, 422, 120),
    'pitch': 150,
    'count': 5,
}
HUB_LAYOUT = {
    'title': (470, 132, 500, 56),
    'tile': (240, 252, 300, 100),
    'tile_pitch': (330, 124),
    'grid': (3, 3),
    'info': (240, 640, 960, 170),
}
CATEGORY_LAYOUT = {
    'title': (470, 132, 500, 56),
    'columns': [(228, 236, 476, 438), (736, 236, 476, 438)],
    'row_top': 14, 'row_pitch': 52, 'row_h': 42, 'rows': 8,
    'pad': 16, 'value_w': 196,
    'info': (228, 690, 984, 120),
}
# The key-binding editor on the stock Input screen (painted mode). Toolbar
# widths and grouping mirror kInputBindingUiToolbarWidths / RightGroup, and
# the rest mirrors BuildKeysPanelLayout, both in bzr_options_ui.cpp.
KEYS_LAYOUT = {
    'title': (470, 132, 500, 56),
    'toolbar': {'y': 264, 'h': 40, 'left': 228, 'right': 1212, 'gap': 10,
                'widths': [120, 190, 150, 160, 90, 90, 120], 'right_from': 4},
    'columns': [(228, 316, 476, 374), (736, 316, 476, 374)],
    'row_top': 10, 'row_pitch': 36, 'row_h': 30, 'rows': 10,
    'pad': 16, 'value_w': 196,
    'info': (228, 702, 984, 116),
}
VALUE_SIZE = (CATEGORY_LAYOUT['value_w'], CATEGORY_LAYOUT['row_h'])
KEY_SIZE = (KEYS_LAYOUT['value_w'], KEYS_LAYOUT['row_h'])
TOOL_SIZE = (150, KEYS_LAYOUT['toolbar']['h'])
TILE_SIZE = HUB_LAYOUT['tile'][2:]


def options_center():
    img, d = new_panel()
    x, y0, w, h = OPTIONS_LAYOUT['slot']
    pitch, n = OPTIONS_LAYOUT['pitch'], OPTIONS_LAYOUT['count']
    # Connectors from the trace bands to the column, and between slots.
    connector(d, x + w / 2 - 65, 116, 130, y0 - 116)
    for k in range(n):
        y = y0 + k * pitch
        if k:
            connector(d, x, y - (pitch - h), w, pitch - h)
        slot(d, x, y, w, h)
    last = y0 + (n - 1) * pitch + h
    connector(d, x + w / 2 - 65, last, 130, 964 - last)
    return img.resize((W, H), Image.LANCZOS)


def info_box(d, x, y, w, h):
    c = 14
    poly(d, chamfer_poly(x, y, w, h, c), fill=BOX, outline=HILITE, width=2)
    d.rectangle([s(x + 24), s(y + h - 46), s(x + w - 24), s(y + h - 45)], fill=LINE)
    for nx, ny, dx in ((x + 2, y + h - c - 2, 1), (x + w - 2, y + h - c - 2, -1)):
        poly(d, [(nx, ny), (nx + dx * 12, ny + 12), (nx, ny + 12)], fill=ACCENT)


def hub_center():
    img, d = new_panel()
    title_plate(d, *HUB_LAYOUT['title'])
    tx, ty, tw, th = HUB_LAYOUT['tile']
    px, py = HUB_LAYOUT['tile_pitch']
    cols, rows = HUB_LAYOUT['grid']
    for r in range(rows):
        for c in range(cols):
            slot(d, tx + c * px, ty + r * py, tw, th)
    info_box(d, *HUB_LAYOUT['info'])
    return img.resize((W, H), Image.LANCZOS)


def category_center():
    img, d = new_panel()
    title_plate(d, *CATEGORY_LAYOUT['title'])
    L = CATEGORY_LAYOUT
    for (bx, by, bw, bh) in L['columns']:
        poly(d, chamfer_poly(bx, by, bw, bh, 14), fill=BOX, outline=HILITE, width=2)
        for r in range(L['rows']):
            y = by + L['row_top'] + r * L['row_pitch']
            vx = bx + bw - L['pad'] - L['value_w']
            text_well(d, bx + L['pad'], y, vx - bx - L['pad'] - 10, L['row_h'])
            slot(d, vx, y, L['value_w'], L['row_h'])
    info_box(d, *L['info'])
    return img.resize((W, H), Image.LANCZOS)


def toolbar_rects(t):
    rects = []
    x = t['left']
    for w in t['widths'][:t['right_from']]:
        rects.append((x, t['y'], w, t['h']))
        x += w + t['gap']
    x = t['right']
    right = []
    for w in reversed(t['widths'][t['right_from']:]):
        x -= w
        right.append((x, t['y'], w, t['h']))
        x -= t['gap']
    return rects + list(reversed(right))


def keys_center():
    img, d = new_panel()
    L = KEYS_LAYOUT
    title_plate(d, *L['title'])
    for r in toolbar_rects(L['toolbar']):
        slot(d, *r)
    for (bx, by, bw, bh) in L['columns']:
        poly(d, chamfer_poly(bx, by, bw, bh, 14), fill=BOX, outline=HILITE, width=2)
        for r in range(L['rows']):
            y = by + L['row_top'] + r * L['row_pitch']
            vx = bx + bw - L['pad'] - L['value_w']
            text_well(d, bx + L['pad'], y, vx - bx - L['pad'] - 10, L['row_h'])
            slot(d, vx, y, L['value_w'], L['row_h'])
    info_box(d, *L['info'])
    return img.resize((W, H), Image.LANCZOS)


def main():
    outputs = {
        'osh_career_center.png': career_center(),
        'osh_prelobby_center.png': prelobby_center(),
        'osh_options_center.png': options_center(),
        'osh_hub_center.png': hub_center(),
        'osh_category_center.png': category_center(),
        'osh_tile_hv.png': slot_texture(*TILE_SIZE, SLOT_HOVER),
        'osh_tile_ck.png': slot_texture(*TILE_SIZE, SLOT_PRESS),
        'osh_value_hv.png': slot_texture(*VALUE_SIZE, SLOT_HOVER),
        'osh_value_ck.png': slot_texture(*VALUE_SIZE, SLOT_PRESS),
        'osh_keys_center.png': keys_center(),
        'osh_key_hv.png': slot_texture(*KEY_SIZE, SLOT_HOVER),
        'osh_key_ck.png': slot_texture(*KEY_SIZE, SLOT_PRESS),
        'osh_tool_hv.png': slot_texture(*TOOL_SIZE, SLOT_HOVER),
        'osh_tool_ck.png': slot_texture(*TOOL_SIZE, SLOT_PRESS),
    }
    for name, img in outputs.items():
        img.save(HERE / name, optimize=True)
        print('wrote', name, img.size)
        if '--preview' in sys.argv and img.size == (W, H):
            bg = Image.new('RGBA', img.size, (0, 0, 0, 255))
            bg.alpha_composite(img)
            prev = HERE / name.replace('.png', '_preview.png')
            bg.convert('RGB').save(prev)
            print('wrote', prev.name)


if __name__ == '__main__':
    main()
