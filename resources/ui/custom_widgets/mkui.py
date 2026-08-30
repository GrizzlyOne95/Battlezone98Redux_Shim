from PIL import Image, ImageDraw, ImageFont
from pathlib import Path
import hashlib, json, shutil, zipfile

SRC = Path('/mnt/data/ui_src/ui')
OUT = Path('/mnt/data/openshim_ui_kit')
ASSET = OUT / 'assets'
SRCOUT = OUT / 'src'
TOOLS = OUT / 'tools'
for d in (ASSET, SRCOUT, TOOLS): d.mkdir(parents=True, exist_ok=True)

# All game-facing filenames are <= 8 characters before extension.
FILES = {
    'uibg.png':   ('blackui.png', (0,0,4,4), None),
    'uitl.png':   ('newon.png', (0,0,32,32), 'newon'),
    'uitr.png':   ('newon.png', (153,0,185,32), 'newon'),
    'uibl.png':   ('newon.png', (0,27,32,59), 'newon'),
    'uibr.png':   ('newon.png', (153,27,185,59), 'newon'),
    'uitop.png':  ('newon.png', (32,0,153,8), 'newon'),
    'uibot.png':  ('newon.png', (32,51,153,59), 'newon'),
    'uileft.png': ('newon.png', (0,16,8,43), 'newon'),
    'uiright.png':('newon.png', (177,32,185,43), 'newon'),
    'uitrch.png': ('mp1on.png', (108,0,185,72), 'mp1on'),
    'uiblch.png': ('mp1on.png', (0,36,77,72), 'mp1on'),
}

# Remove only the flat stock fill from border/ornament crops. This does not recolor,
# redraw, antialias, or otherwise invent pixels; visible pixels remain byte-for-byte
# from the supplied Redux UI textures.
FILL_KEYS = {
    'newon': {(0,90,0,255)},
    'mp1on': {(0,84,0,255)},
}

def sha256(p: Path):
    return hashlib.sha256(p.read_bytes()).hexdigest()

def extract(dst_name, src_name, crop, key):
    im = Image.open(SRC/src_name).convert('RGBA').crop(crop)
    if key:
        pix = im.load()
        keys = FILL_KEYS[key]
        for y in range(im.height):
            for x in range(im.width):
                if pix[x,y] in keys:
                    r,g,b,a = pix[x,y]
                    pix[x,y] = (r,g,b,0)
    im.save(ASSET/dst_name, optimize=False)

for dst, (src,crop,key) in FILES.items():
    extract(dst,src,crop,key)

# Offline composer for validation only. Runtime OpenShim code uses the same geometry.
def fit_nearest(im, size):
    return im.resize((max(1,int(size[0])), max(1,int(size[1]))), Image.Resampling.NEAREST)

def paste_rgba(canvas, name, box):
    x,y,w,h = map(int, box)
    im = Image.open(ASSET/name).convert('RGBA')
    if im.size != (w,h): im = fit_nearest(im,(w,h))
    canvas.alpha_composite(im,(x,y))

def panel(canvas, x,y,w,h, tech=True, fill=True):
    # Background is the exact stock 4x4 blackui tile, stretched because that is also
    # how the existing OpenShim backdrop path uses tiny generic UI fills.
    if fill: paste_rgba(canvas,'uibg.png',(x,y,w,h))
    c=32; e=8
    paste_rgba(canvas,'uitl.png',(x,y,c,c))
    paste_rgba(canvas,'uitr.png',(x+w-c,y,c,c))
    paste_rgba(canvas,'uibl.png',(x,y+h-c,c,c))
    paste_rgba(canvas,'uibr.png',(x+w-c,y+h-c,c,c))
    paste_rgba(canvas,'uitop.png',(x+c,y,w-2*c,e))
    paste_rgba(canvas,'uibot.png',(x+c,y+h-e,w-2*c,e))
    paste_rgba(canvas,'uileft.png',(x,y+c,e,h-2*c))
    paste_rgba(canvas,'uiright.png',(x+w-e,y+c,e,h-2*c))
    if tech:
        tr = Image.open(ASSET/'uitrch.png').convert('RGBA')
        bl = Image.open(ASSET/'uiblch.png').convert('RGBA')
        canvas.alpha_composite(tr,(x+w-tr.width,y))
        canvas.alpha_composite(bl,(x,y+h-bl.height))

# Preview: several arbitrary dimensions demonstrate that the pieces are composable.
prev = Image.new('RGBA',(1400,850),(0,0,0,255))
panel(prev,90,80,1220,220,True,True)
panel(prev,90,340,580,400,True,True)
panel(prev,730,340,580,400,False,True)
# Stock-only controls placed in preview for visual-language comparison.
newon=Image.open(SRC/'newon.png').convert('RGBA')
mp1on=Image.open(SRC/'mp1on.png').convert('RGBA')
prev.alpha_composite(newon,(130,125))
prev.alpha_composite(mp1on,(1050,120))
# Label preview with neutral font; labels are not game assets.
d=ImageDraw.Draw(prev)
try: font=ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf',22)
except: font=None
for pos,text in [((130,95),'STOCK newon.png'),((1050,90),'STOCK mp1on.png'),((115,315),'TECH PANEL — runtime assembled'),((755,315),'PLAIN PANEL — runtime assembled')]:
    d.text(pos,text,fill=(127,255,127,255),font=font)
prev.save(OUT/'preview.png')

manifest = {
  'purpose': 'OpenShim runtime-constructible decorative UI tile kit',
  'policy': 'Visible pixels are crops from supplied stock Redux UI assets; no generated line art, recoloring, smoothing, or invented UI style.',
  'game_facing_name_rule': 'Every supplied PNG stem is <= 8 characters.',
  'sources': {n: {'sha256': sha256(SRC/n), 'size': Image.open(SRC/n).size} for n in ['blackui.png','newon.png','mp1on.png']},
  'assets': {dst: {'source':src,'crop':crop,'flat_fill_made_transparent':key is not None} for dst,(src,crop,key) in FILES.items()},
  'panel_geometry': {'corner_px':32,'edge_px':8,'tech_top_right_native':[77,72],'tech_bottom_left_native':[77,36]},
}
(OUT/'manifest.json').write_text(json.dumps(manifest,indent=2),encoding='utf-8')

header = r'''#pragma once
// OpenShim decorative UI geometry helper.
//
// WHY: Custom OpenShim option pages currently create individual native Redux UI
// children.  This helper keeps decoration equally dynamic: it computes a set of
// passive image rectangles for the stock-derived UI tile kit instead of baking a
// resolution-specific full-screen background.
//
// This file deliberately knows nothing about Redux cUI pointers or ownership.  The
// existing bzr_options_ui.cpp image/backdrop creation path should consume the
// returned pieces so the proven host/lifetime/input rules remain authoritative.

#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
    struct UiDecorRect
    {
        float x = 0.0f;
        float y = 0.0f;
        float width = 0.0f;
        float height = 0.0f;
    };

    struct UiDecorPiece
    {
        const char* texture = nullptr;
        UiDecorRect rect = {};
    };

    enum UiDecorPanelFlags : uint32_t
    {
        UI_DECOR_FILL = 1u << 0,
        UI_DECOR_TECH = 1u << 1,
        UI_DECOR_DEFAULT = UI_DECOR_FILL | UI_DECOR_TECH,
    };

    struct UiDecorPanelDesc
    {
        UiDecorRect rect = {};
        uint32_t flags = UI_DECOR_DEFAULT;
    };

    // Worst case: fill + 8 frame pieces + 2 stock tech ornaments.
    constexpr size_t kUiDecorMaxPanelPieces = 11;

    // Returns the number of descriptors written. Returns 0 for invalid geometry or
    // insufficient output capacity. The caller owns only its normal cUI children;
    // this helper allocates no Redux objects and stores no pointers.
    size_t BuildUiDecorPanel(const UiDecorPanelDesc& desc,
                             UiDecorPiece* outPieces,
                             size_t outCapacity);
}
'''
(SRCOUT/'uidcor.h').write_text(header,encoding='utf-8')

cpp = r'''#include "uidcor.h"

namespace BZROpenShim
{
    namespace
    {
        constexpr float kCorner = 32.0f;
        constexpr float kEdge = 8.0f;
        constexpr float kTechRightWidth = 77.0f;
        constexpr float kTechRightHeight = 72.0f;
        constexpr float kTechLeftWidth = 77.0f;
        constexpr float kTechLeftHeight = 36.0f;

        bool Push(UiDecorPiece*& cursor, size_t& remaining,
                  const char* texture, float x, float y, float w, float h)
        {
            if (!cursor || remaining == 0 || !texture || w <= 0.0f || h <= 0.0f)
                return false;
            cursor->texture = texture;
            cursor->rect = { x, y, w, h };
            ++cursor;
            --remaining;
            return true;
        }
    }

    size_t BuildUiDecorPanel(const UiDecorPanelDesc& desc,
                             UiDecorPiece* outPieces,
                             size_t outCapacity)
    {
        // WHY: The stock-derived corners are 32 px. Reject tiny rectangles instead
        // of scaling/overlapping the distinctive Redux corner language into mush.
        if (!outPieces || desc.rect.width < kCorner * 2.0f ||
            desc.rect.height < kCorner * 2.0f)
            return 0;

        const size_t required = 8u +
            ((desc.flags & UI_DECOR_FILL) ? 1u : 0u) +
            ((desc.flags & UI_DECOR_TECH) ? 2u : 0u);
        if (outCapacity < required)
            return 0;

        UiDecorPiece* cursor = outPieces;
        size_t remaining = outCapacity;
        const float x = desc.rect.x;
        const float y = desc.rect.y;
        const float w = desc.rect.width;
        const float h = desc.rect.height;

        if (desc.flags & UI_DECOR_FILL)
            Push(cursor, remaining, "uibg.png", x, y, w, h);

        // Four corners + four stretchable straight runs. The textures are literal
        // crops from stock newon.png, with only its flat green interior keyed to
        // transparency so the underlying stock blackui fill can show through.
        Push(cursor, remaining, "uitl.png", x, y, kCorner, kCorner);
        Push(cursor, remaining, "uitr.png", x + w - kCorner, y, kCorner, kCorner);
        Push(cursor, remaining, "uibl.png", x, y + h - kCorner, kCorner, kCorner);
        Push(cursor, remaining, "uibr.png", x + w - kCorner, y + h - kCorner, kCorner, kCorner);
        Push(cursor, remaining, "uitop.png", x + kCorner, y, w - 2.0f * kCorner, kEdge);
        Push(cursor, remaining, "uibot.png", x + kCorner, y + h - kEdge, w - 2.0f * kCorner, kEdge);
        Push(cursor, remaining, "uileft.png", x, y + kCorner, kEdge, h - 2.0f * kCorner);
        Push(cursor, remaining, "uiright.png", x + w - kEdge, y + kCorner, kEdge, h - 2.0f * kCorner);

        if (desc.flags & UI_DECOR_TECH)
        {
            // WHY: These are the original mp1on.png orientations. Do not mirror or
            // procedurally redraw them; preserving their top-right / bottom-left
            // asymmetry keeps the decoration recognizably Redux rather than a new
            // sci-fi skin merely inspired by it.
            Push(cursor, remaining, "uitrch.png", x + w - kTechRightWidth, y,
                 kTechRightWidth, kTechRightHeight);
            Push(cursor, remaining, "uiblch.png", x, y + h - kTechLeftHeight,
                 kTechLeftWidth, kTechLeftHeight);
        }

        return required;
    }
}
'''
(SRCOUT/'uidcor.cpp').write_text(cpp,encoding='utf-8')

readme = r'''# OpenShim stock-derived dynamic UI decoration kit

This pack is deliberately **not** a replacement screen background. It is a set of small passive image pieces for OpenShim to compose at runtime around its existing native controls.

## Art-direction contract

The visible pixels come only from the supplied Redux `common/ui` textures:

- `blackui.png` — panel fill
- `newon.png` — frame corners and straight borders
- `mp1on.png` — the distinctive diagonal technical ornaments

The extraction script does not redraw, recolor, blur, anti-alias, or synthesize decoration. On border/ornament crops it only makes the original flat button-fill color transparent so the stock `blackui` backing can show through. This keeps the line weights, green values, corner treatment and diagonal motif identical to shipped UI artwork.

## Runtime assets

All game-facing filename stems are 8 characters or fewer.

| Asset | Purpose |
|---|---|
| `uibg.png` | exact 4x4 stock black UI fill |
| `uitl.png` / `uitr.png` | upper corners |
| `uibl.png` / `uibr.png` | lower corners |
| `uitop.png` / `uibot.png` | stretchable horizontal runs |
| `uileft.png` / `uiright.png` | stretchable vertical runs |
| `uitrch.png` | stock `mp1on` upper-right technical ornament |
| `uiblch.png` | stock `mp1on` lower-left technical ornament |

## OpenShim integration

`src/uidcor.*` only calculates texture + rectangle descriptors. This is intentional: the current OpenShim Options/Input code already has the proven Redux cUI allocation, parent, ownership and lifetime path. Do **not** introduce a second cUI object creator here.

A screen integrates it approximately as follows, using its existing passive backdrop/image creation helper:

```cpp
UiDecorPiece pieces[kUiDecorMaxPanelPieces] = {};
UiDecorPanelDesc panel = {};
panel.rect = { 420.0f, 255.0f, 820.0f, 290.0f };
panel.flags = UI_DECOR_DEFAULT;

const size_t count = BuildUiDecorPanel(panel, pieces, kUiDecorMaxPanelPieces);
for (size_t i = 0; i < count; ++i)
{
    // Use the SAME passive cUI image/backdrop constructor and validated
    // Middle_Overlay parent already used by bzr_options_ui.cpp.
    CreateExistingOpenShimPassiveImage(pieces[i].texture, pieces[i].rect);
}
```

The placeholder function above is intentionally not compiled into the kit; wire the descriptors into the existing proven helper in `bzr_options_ui.cpp` rather than guessing another Redux ABI path.

### Recommended screen structure

For the current two-column pages, build three panels dynamically:

1. header/status panel — derived from actual header label/status bounds;
2. navigation strip panel — derived from first/last navigation button bounds;
3. content panel — derived from the visible row bounds, with the technical ornament flag enabled.

The content panel height should be computed from `visibleRows * rowPitch + padding`, so pages with fewer rows shrink naturally. Keybindings can use one outer panel or two column panels without new textures.

## Input safety

Decoration must remain passive. Do not create a new full-bleed active `cUI_View` surface over stock controls. Mount decorative children beneath the interactive OpenShim buttons/labels on the already validated `Middle_Overlay` host, following the current OpenShim Native UI lifetime rules.

## Validation

`preview.png` deliberately composes the same pieces at three unrelated sizes. The stock `newon.png` and `mp1on.png` controls are embedded alongside them for direct visual-language comparison.
'''
(OUT/'README.md').write_text(readme,encoding='utf-8')

# Copy the generator into the bundle for exact reproducibility.
shutil.copy2('/mnt/data/build_ui_kit.py', TOOLS/'mkui.py')

zip_path=Path('/mnt/data/openshim_ui_kit.zip')
if zip_path.exists(): zip_path.unlink()
with zipfile.ZipFile(zip_path,'w',zipfile.ZIP_DEFLATED) as z:
    for p in OUT.rglob('*'):
        if p.is_file(): z.write(p,p.relative_to(OUT))
print(zip_path)
