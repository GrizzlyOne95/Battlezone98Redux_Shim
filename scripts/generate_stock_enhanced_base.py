#!/usr/bin/env python3
"""Generate OpenShim's Enhanced stock base imports.

Stock Redux materials inherit their techniques with
`import * from "BZBase.material"` (213 files) or
`import * from "BZTerrainBase.material"` (the detail atlases). Stock bases only
carry Classic schemes, so under the Enhanced viewport scheme those materials
fall back to stock shaders. OpenShim redirects those two imports, while its
Enhanced resources are ready, to the files written here
(src/patches/ogre_script_import_cache.cpp).

Each output is the stock base verbatim plus:
  - the `en-*` techniques of Campaign Reimagined's CR_BZBase /
    CR_BZBaseCockpit / CR_BZTerrainBase, which are already qualified against
    OpenShim's OSE_* programs;
  - the abstract passes those techniques use, renamed BZPassScheme* ->
    OSEPassScheme* (BZTerrainPassScheme* -> OSETerrainPassScheme*) so they do
    not collide with the stock passes of the same file.
CR's image-based-lighting fragment overrides are CR programs. Object ones
(CR_BaseIBL*) become OpenShim's OSE_BaseIBL* twins and keep their IBL texture
units, so stock objects get the static and per-planet IBL without CR. Terrain
ones (CR_TerrainIBL*) become the plain OSE_TerrainEN* fragment of the same
tier and their IBL texture units are dropped. Non-`en-*` techniques stay stock, so Classic,
Redux, Retro and glow rendering are unchanged.

The outputs use a `.import` extension so no resource group parses them as
scripts: they are only ever read through the redirected import, which keeps the
redefined BZBase/BZTerrainBase objects out of the material manager.

Usage:
  python scripts/generate_stock_enhanced_base.py \
      --stock-dir "<Redux>/BZ_ASSETS_CORE/common/BZ_MATERIALS" \
      --cr-dir "<Campaign-Reimagined>/Materials" [--check]
"""

import argparse
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
PAYLOAD = REPO / "resources" / "renderer" / "enhanced"

TARGETS = [
    {
        "stock": "BZBase.material",
        "cr": "CR_BZBase.material",
        "out": "openshim_stock_bzbase.import",
        "pass_from": "BZPassScheme",
        "pass_to": "OSEPassScheme",
        "materials": {"BZBase": "CR_BZBase", "BZBaseCockpit": "CR_BZBaseCockpit"},
        "keep_ibl": True,
    },
    {
        "stock": "BZTerrainBase.material",
        "cr": "CR_BZTerrainBase.material",
        "out": "openshim_stock_bzterrainbase.import",
        "pass_from": "BZTerrainPassScheme",
        "pass_to": "OSETerrainPassScheme",
        "materials": {"BZTerrainBase": "CR_BZTerrainBase"},
    },
]

IBL_FRAGMENTS = [
    (re.compile(r"\bCR_BaseIBLHigh(PSSM|Shadow|NoShadow)_fragment\b"), r"OSE_BaseIBLHigh\1_fragment"),
    (re.compile(r"\bCR_TerrainIBLHigh(PSSM|Shadow|NoShadow)_fragment\b"), r"OSE_TerrainENHigh\1_fragment"),
]
IBL_UNITS = ("irradianceMap", "prefilteredEnvMap", "brdfLut")


def load(path):
    return path.read_text(encoding="latin-1").replace("\r\n", "\n")


def strip_comments(text):
    return re.sub(r"//[^\n]*", "", text)


def blocks(text):
    """Top-level `{}` blocks as (header line, start, end); `//` comments skipped."""
    out = []
    depth = 0
    pos = 0
    header_start = 0
    header = ""
    n = len(text)
    while pos < n:
        if text.startswith("//", pos):
            nl = text.find("\n", pos)
            pos = n if nl < 0 else nl
            continue
        c = text[pos]
        if c == "{":
            if depth == 0:
                lines = [l.strip() for l in strip_comments(text[header_start:pos]).split("\n") if l.strip()]
                header = lines[-1] if lines else ""
                # The block starts at its header line, comments above it excluded.
                line_start = text.rfind("\n", 0, text.rfind(header, header_start, pos)) + 1
                block_start = line_start
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                out.append((header, block_start, pos + 1))
                header_start = pos + 1
        pos += 1
    if depth != 0:
        raise ValueError("unbalanced braces")
    return out


def find_block(text, header):
    for h, s, e in blocks(text):
        if h == header:
            return s, e
    raise KeyError(header)


def drop_ibl_units(technique):
    for unit in IBL_UNITS:
        while True:
            m = re.search(r"\n[ \t]*texture_unit\s+" + unit + r"\s*\{", technique)
            if not m:
                break
            depth = 0
            pos = technique.index("{", m.start())
            while True:
                if technique[pos] == "{":
                    depth += 1
                elif technique[pos] == "}":
                    depth -= 1
                    if depth == 0:
                        break
                pos += 1
            end = pos + 1
            technique = technique[:m.start()] + technique[end:]
    technique = re.sub(r"\n[ \t]*\n([ \t]*\n)+", "\n\n", technique)
    return re.sub(r"\n[ \t]*\n([ \t]*\})", r"\n\1", technique)


def en_techniques(material_body):
    inner = material_body[material_body.index("{") + 1:material_body.rindex("}")]
    out = []
    for header, s, e in blocks(inner):
        block = inner[s:e]
        scheme = re.search(r"^\s*scheme\s+(\S+)", strip_comments(block), re.M)
        if header == "technique" and scheme and scheme.group(1).startswith("en-"):
            out.append(block)
    return out


def declared_programs():
    names = set()
    for program in PAYLOAD.glob("*.program"):
        for m in re.finditer(r"^\s*(?:vertex|fragment)_program\s+(\S+)", strip_comments(load(program)), re.M):
            names.add(m.group(1))
    return names


def generate(target, stock_dir, cr_dir, programs):
    stock_path = stock_dir / target["stock"]
    cr_path = cr_dir / target["cr"]
    stock = load(stock_path)
    cr = load(cr_path)
    pass_re = re.compile(r"\b" + target["pass_from"] + r"(\w+)")

    # en-* techniques per stock material, retargeted.
    additions = {}
    used_passes = set()
    for stock_material, cr_material in target["materials"].items():
        s, e = find_block(cr, "material " + cr_material)
        techniques = []
        for technique in en_techniques(cr[s:e]):
            technique = re.sub(r"//[^\n]*\n", "", technique)
            for pattern, replacement in IBL_FRAGMENTS:
                technique = pattern.sub(replacement, technique)
            if not target.get("keep_ibl"):
                technique = drop_ibl_units(technique)
            used_passes.update(m.group(0) for m in pass_re.finditer(technique))
            technique = pass_re.sub(target["pass_to"] + r"\1", technique)
            techniques.append(technique)
        if not techniques:
            raise ValueError(f"{cr_path.name}: material {cr_material} has no en-* techniques")
        additions[stock_material] = techniques

    # The abstract passes those techniques use, renamed.
    passes = []
    for name in sorted(used_passes):
        s, e = find_block(cr, "abstract pass " + name)
        block = re.sub(r"//[^\n]*\n", "", cr[s:e])
        # The OSE PSSM v2 shaders compare depth by hand through an ordinary
        # SamplerState, so CR's hardware-comparison sampler state is dropped.
        block = re.sub(r"^[ \t]*compare_(?:test|func)\b[^\n]*\n", "", block, flags=re.M)
        passes.append(pass_re.sub(target["pass_to"] + r"\1", block, count=1))

    out = stock.rstrip("\n") + "\n"
    # Insert techniques at the end of each stock material, last first so
    # earlier offsets stay valid.
    spans = sorted(((find_block(out, "material " + m), m) for m in additions), reverse=True)
    for (s, e), material in spans:
        close = out.rindex("}", s, e)
        insert = "\n\t// ---- OpenShim Enhanced (en-*) techniques ----\n\n\t" + "\n\n\t".join(
            t.strip("\n").lstrip() for t in additions[material]) + "\n"
        out = out[:close] + insert + out[close:]
    first_material = min(s for (s, _), _ in spans)
    out = (out[:first_material]
           + "// ---- OpenShim Enhanced abstract passes ----\n\n"
           + "\n\n".join(passes) + "\n\n"
           + out[first_material:])

    header = (
        "// GENERATED by scripts/generate_stock_enhanced_base.py -- do not edit.\n"
        f"// Stock Redux {target['stock']} with the en-* techniques of Campaign\n"
        f"// Reimagined's {target['cr']}, retargeted to OpenShim OSE_* programs.\n"
        f"// Loaded only through the redirected `import * from \"{target['stock']}\"`.\n\n"
    )
    out = header + out

    # Validation: no CR program or pass survived, every program is ours or stock.
    code = strip_comments(out)
    leftovers = sorted(set(re.findall(r"\bCR_\w+", code)))
    if leftovers:
        raise ValueError(f"{target['out']}: CR names survived: {leftovers}")
    stock_programs = set(re.findall(r"_program_ref\s+(\S+)", strip_comments(stock)))
    for ref in sorted(set(re.findall(r"_program_ref\s+(\S+)", code))):
        if ref not in programs and ref not in stock_programs:
            raise ValueError(f"{target['out']}: undeclared program {ref}")
    for ref in sorted(set(re.findall(r"pass\s*:\s*(\w+)", code))):
        if not re.search(r"abstract pass\s+" + ref + r"\b", code):
            raise ValueError(f"{target['out']}: undefined pass {ref}")
    blocks(out)  # balanced
    return out


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--stock-dir", required=True, type=Path)
    parser.add_argument("--cr-dir", required=True, type=Path)
    parser.add_argument("--check", action="store_true", help="fail if the checked-in outputs differ")
    args = parser.parse_args()

    programs = declared_programs()
    stale = []
    for target in TARGETS:
        text = generate(target, args.stock_dir, args.cr_dir, programs)
        path = PAYLOAD / target["out"]
        if args.check:
            if not path.exists() or load(path) != text:
                stale.append(path.name)
        else:
            path.write_bytes(text.replace("\n", "\r\n").encode("latin-1"))
            print(f"wrote {path.relative_to(REPO)} ({text.count(chr(10))} lines)")
    if stale:
        print("stale: " + ", ".join(stale), file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
