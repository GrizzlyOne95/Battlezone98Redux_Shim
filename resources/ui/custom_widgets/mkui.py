#!/usr/bin/env python3
"""Generate the OpenShim options-page tile kit.

Every colour here is sampled from the shipped Battlezone 98 Redux UI art
(``common/ui/newon.png``, ``mp1on.png``, ``mpcron.png`` and
``Options/keyOptions_center.png``), so the injected pages stay inside the
stock palette without copying stock pixels.

The tiles are deliberately flat single-colour fills. The engine stretches a
widget texture to the widget rect, so any border or corner motif baked into
the art is distorted by the stretch -- that is what put a squashed diagonal
highlight underneath the value text on the stock ``mpcron.png`` plates.
Flat fills cannot distort, so separation between a row's label field and its
value button comes from tonal value and from the gaps in the layout instead.
"""

import struct
import zlib

# --- stock palette ---------------------------------------------------------
# keyOptions_center.png frame highlight / mp1on.png accent.
BORDER = (0, 127, 0)
# newon.png + mpcron.png button body.
BUTTON = (0, 84, 0)
# mpcron.png recessed field, also the keyOptions_center frame body.
FIELD = (0, 43, 0)
# mpcrclk.png pressed body.
BUTTON_HOT = (0, 127, 0)

TILES = {
    "uiline.png": BORDER,   # panel border bars
    "uiplate.png": FIELD,   # row label field
    "uibtn.png": BUTTON,    # value button, toolbar button
    "uibtnhv.png": BUTTON_HOT,  # hover + pressed
}

SIZE = 8


def _chunk(tag: bytes, payload: bytes) -> bytes:
    return (struct.pack(">I", len(payload)) + tag + payload +
            struct.pack(">I", zlib.crc32(tag + payload) & 0xFFFFFFFF))


def write_solid(path: str, rgb, size: int = SIZE) -> None:
    """Write a size x size opaque RGBA PNG of one colour."""
    row = bytes((rgb[0], rgb[1], rgb[2], 255)) * size
    raw = b"".join(b"\x00" + row for _ in range(size))
    png = (b"\x89PNG\r\n\x1a\n" +
           _chunk(b"IHDR", struct.pack(">IIBBBBB", size, size, 8, 6, 0, 0, 0)) +
           _chunk(b"IDAT", zlib.compress(raw, 9)) +
           _chunk(b"IEND", b""))
    with open(path, "wb") as handle:
        handle.write(png)


def main() -> None:
    for name, rgb in sorted(TILES.items()):
        write_solid(name, rgb)
        print(f"wrote {name} {SIZE}x{SIZE} rgb{rgb}")


if __name__ == "__main__":
    main()
