# MakeSTB (2013-09-07) — Initial Reverse Engineering Notes

Target: `MakeSTB.exe` from `MakeSTB_2013-09-07(1).zip`

SHA-256: `11fbc561c302d593224f58e94230ad3d35648450bb3e12a139277485c2e6f062`

## Binary identity

- PE32 x86 Windows console executable, image base `0x00400000`
- Linker 9.0 / MSVCR90 dependency (Visual C++ 2008 generation)
- Build timestamp: 2013-09-08 03:17:56 UTC; embedded utility version string says Sep 7 2013
- Linked XML implementation is `tinyxml2` (RTTI class names are present)
- PDB path embedded in debug data: `c:\Users\Ken\Documents\Projects\BZ1\debug\MakeSTB.pdb`
- No evidence of executable packing/obfuscation

## STB binary layout

The STB file has **no header, magic, version, count, or index**. The executable repeatedly calls `fread(..., 0x34, 1, file)` until it can no longer read a complete record. Writers similarly call `fwrite(..., 0x34, 1, file)`.

Each record is exactly **52 bytes (`0x34`)**:

| Offset | Size | Type | Field |
|---:|---:|---|---|
| `0x00` | 32 | raw char array | `name[32]` |
| `0x20` | 8 | raw char array | `texture[8]` |
| `0x28` | 2 | little-endian uint16 | `u` |
| `0x2A` | 2 | little-endian uint16 | `v` |
| `0x2C` | 2 | little-endian uint16 | `width` |
| `0x2E` | 2 | little-endian uint16 | `height` |
| `0x30` | 4 | little-endian uint32 | `flags` |

Implications:

- Entry count is `floor(file_size / 52)`.
- A trailing partial record is silently ignored by the reader.
- Name and texture are fixed-width byte arrays; maximum-length values do not need a NUL terminator.
- The reader prints them with precision-limited `%s` formats (`%.32s`, `%.8s`), avoiding overread when full-width.
- Coordinates/dimensions are read as unsigned 16-bit values and printed as decimal.
- Flags are opaque to MakeSTB and are preserved as a 32-bit value.

## CLI surface

Embedded usage:

```text
MakeSTB <command> <stb_file> [<file_name>...]

l   list sprite table entries
rt  read STB and output TXT
rc  read STB and output CSV
rx  read STB and output XML
rj  read STB and output JSON
wt  input TXT and write STB
wc  input CSV and write STB
wx  input XML and write STB
```

Command letters are normalized with `toupper`, so case is effectively ignored.

Read commands open STB input as binary (`rb`). If an output filename is supplied, it is opened in text-write mode (`wt`); otherwise output is stdout.

Write commands open the target STB as binary-write (`wb`). TXT/CSV may be read from stdin when no source file is supplied. XML explicitly refuses stdin. Multiple source files can be supplied and are appended sequentially into one STB.

## Text format (`wt` / `rt`)

Generated header:

```text
# NAME............................ TEXTURE. U.... V.... W.... H.... FLAGS.....
```

Record shape:

```text
"<name up to 32>" <texture up to 8> <u> <v> <w> <h> 0x<8 hex digits>
```

The parser requires seven successful conversions for a normal record. The four geometry values are parsed as signed decimal integers then stored in 16-bit fields, so out-of-range/negative values are truncated/wrapped rather than rejected. Flags are parsed as hex.

Lines whose **first byte** is `#` are skipped. Blank lines are skipped.

### TXT includes

Documented and confirmed:

```text
@include "filename"
```

The filename scanset is capped at 32 characters. Includes are recursive. The include path is passed directly to `fopen`, so relative paths are relative to the process working directory, not necessarily the including file's directory.

## CSV format (`wc` / `rc`)

Output is headerless:

```text
name,texture,u,v,width,height,0xFLAGS
```

Input is more permissive than the name suggests. It tokenizes on any of:

```text
, ; TAB
```

The first two tokens (name and texture) are required. Missing numeric tokens default to zero. Numeric values use `strtoul(..., base=0)`, so decimal, `0x` hexadecimal, and C-style octal are accepted. Geometry values are truncated to 16 bits; flags are retained as 32 bits.

## XML format (`wx` / `rx`)

Generated form:

```xml
<?xml version="1.0" standalone="no"?>
<spritetable>
    <sprite name="..." texture="..." u="0" v="0" width="0" height="0" flags="0x00000000"/>
</spritetable>
```

`name` and `texture` are required for an input `<sprite>` to be emitted. `u`, `v`, `width`, `height`, and `flags` are optional and default to zero. Numeric XML attributes use `strtoul(..., base=0)`.

### Undocumented XML include support

Static analysis found an additional input element not mentioned in the changelog:

```xml
<include file="other.xml"/>
```

It recursively invokes the XML reader and appends included sprites to the same output STB. As with TXT includes, the path is opened directly and therefore resolves against the process working directory.

Unknown child elements are skipped.

## JSON output

JSON is **read/export only**. The executable contains the explicit message:

```text
ERROR: reading JSON not supported yet :(
```

`rj` outputs an array of objects with:

- `name`
- `texture`
- `u`
- `v`
- `width`
- `height`
- `flags` (formatted as a quoted `0x........` string)

No JSON escaping logic was identified around the formatted string writer, so unusual names containing JSON-special characters are a likely edge case.

## Important distinction from Redux `.st` text

The legacy MakeSTB record contains only `U, V, W, H` plus flags. Its changelog explicitly says its tabular format resembles BZ2 `sprite.txt` **minus TW and TH**.

The current `Battlezone98ReduxFontGenerator/tools/dump_bzfont_st.py` parser expects two additional text fields (`ref_w`, `ref_h`) before flags. Therefore the Redux `.st` text consumed by that helper should **not be assumed identical** to MakeSTB's TXT representation or to the 52-byte STB record.

A modern codec should model these as separate dialects until engine/runtime evidence proves a safe conversion relationship.

## Recommended next RE/validation step

1. Obtain one known-good BZ1 `.stb` (ideally `spritea.stb` or equivalent) and parse it with the recovered 52-byte schema.
2. Confirm every file length is divisible by 52 and inspect coordinate/texture/name plausibility.
3. Compare the same table against any available text `.st`/sprite table counterpart to determine exactly how TW/TH/ref dimensions are introduced in later formats.
4. Only then implement the clean-room codec and GUI in TextureManager, with a shared library usable by FontGenerator.
