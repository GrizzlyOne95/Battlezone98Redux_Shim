#!/usr/bin/env python3
"""Regenerate the English column of the OpenShim options localization table.

The English text lives in C++ (src/patches/bzr_options_registry.inc,
bzr_options_categories.inc and every one-line ShimText/ShimFormat call under
src/patches). This script rebuilds resources/localization/openshim_localization.csv
from it, keeping every translated cell whose key still exists.

    python scripts/sync_options_localization.py          # rewrite the table
    python scripts/sync_options_localization.py --check  # exit 1 if it is stale

The file is ANSI, like the game's localization_table.csv: cp1252, and cp1251 in
the Russian column. It is read and written as raw bytes (latin-1 round trip) so
no column is ever re-encoded. See Docs/OPTIONS_UI_LOCALIZATION.md.
"""

import argparse
import pathlib
import re
import sys

ROOT = pathlib.Path(__file__).resolve().parents[1]
REGISTRY = ROOT / "src" / "patches" / "bzr_options_registry.inc"
CATEGORIES = ROOT / "src" / "patches" / "bzr_options_categories.inc"
SOURCES = ROOT / "src" / "patches"
TABLE = ROOT / "resources" / "localization" / "openshim_localization.csv"

HEADER = ["Key", "English", "French", "German", "Spanish", "Italian", "Russian", "Portuguese"]
SPACER = "~" * (len(HEADER) - 1)

TOKEN = re.compile(r'''
    (?P<ws>\s+|//[^\n]*|/\*.*?\*/|\#[^\n]*(?:\\\r?\n[^\n]*)*)
  | (?P<str>"(?:[^"\\\n]|\\.)*")
  | (?P<id>[A-Za-z_][A-Za-z0-9_:]*)
  | (?P<num>[0-9][0-9A-Za-z_.]*)
  | (?P<punct>[{}(),;=\[\]*&<>/+\-.:?!|%^~])
''', re.S | re.X)


def unescape(literal):
    body = literal[1:-1]
    return re.sub(r'\\(.)', lambda m: {"n": "\n", "t": "\t"}.get(m.group(1), m.group(1)), body)


def tokens(text):
    out = []
    pos = 0
    while pos < len(text):
        m = TOKEN.match(text, pos)
        if not m:
            raise SystemExit(f"cannot tokenize near: {text[pos:pos + 40]!r}")
        pos = m.end()
        if m.lastgroup == "ws":
            continue
        value = m.group(m.lastgroup)
        if m.lastgroup == "str":
            value = ("str", unescape(value))
            if out and isinstance(out[-1], tuple):  # adjacent literals concatenate
                out[-1] = ("str", out[-1][1] + value[1])
                continue
        out.append(value)
    return out


def string_arrays(toks):
    """name -> [str] for every `const char* const NAME[] = { "a", "b" };`."""
    arrays = {}
    i = 0
    while i < len(toks):
        if toks[i] == "[" and i + 3 < len(toks) and toks[i + 1] == "]" and toks[i + 2] == "=" and toks[i + 3] == "{":
            name = toks[i - 1]
            j = i + 4
            items = []
            while toks[j] != "}":
                if isinstance(toks[j], tuple):
                    items.append(toks[j][1])
                elif toks[j] not in (",",):
                    items.append(toks[j])  # a named constant (kShimRowReticle)
                j += 1
            arrays[name] = items
            i = j
        i += 1
    return arrays


def registry_rows(toks):
    start = toks.index("g_ShimSettingsRegistry")
    i = toks.index("{", start) + 1
    rows = []
    while toks[i] != "}":
        if toks[i] == "{":
            j = i + 1
            fields, current = [], []
            while toks[j] != "}":
                if toks[j] == ",":
                    fields.append(current)
                    current = []
                else:
                    current.append(toks[j])
                j += 1
            if current:
                fields.append(current)
            rows.append(fields)
            i = j
        i += 1
    out = []
    for f in rows:
        def text(field):
            return field[0][1] if isinstance(field[0], tuple) else None
        out.append({
            "label": text(f[0]),
            "key": text(f[2]),
            "values": f[5][0],
            "labels": f[6][0],
            "description": text(f[10]),
        })
    return out


def slug(text):
    return "".join(ch for ch in text if ch.isascii() and ch.isalnum())


def row_id(row):
    return row["key"] if row["key"] else slug(row["label"])


def generated_entries():
    """Ordered (key, english) groups, separated by None (a spacer line)."""
    reg_toks = tokens(REGISTRY.read_text(encoding="utf-8"))
    arrays = string_arrays(reg_toks)
    rows = registry_rows(reg_toks)

    entries = []
    for row in rows:
        entries.append((f"openshim_opt:{row_id(row)}:label", row["label"]))
        entries.append((f"openshim_opt:{row_id(row)}:desc", row["description"]))
    entries.append(None)

    common = []
    for row in rows:
        for label in arrays[row["labels"]]:
            if label not in common:
                common.append(label)
    entries.extend((f"openshim_value:{label}", label) for label in common)
    entries.append(None)

    cat_text = CATEGORIES.read_text(encoding="utf-8")
    for m in re.finditer(r'constexpr const char\* kShimRow\w+ = "([^"]*)";', cat_text):
        entries.append((f"openshim_ui:row:{slug(m.group(1))}:label", m.group(1)))
    cat_toks = tokens(cat_text)
    i = 0
    while i < len(cat_toks):
        if cat_toks[i] == "BZR_SHIM_CATEGORY" and cat_toks[i + 1] == "(" and isinstance(cat_toks[i + 2], tuple):
            name, title, blurb = (cat_toks[i + 2][1], cat_toks[i + 4][1], cat_toks[i + 6][1])
            entries.append((f"openshim_cat:{slug(name)}:name", name))
            entries.append((f"openshim_cat:{slug(name)}:title", title))
            entries.append((f"openshim_cat:{slug(name)}:blurb", blurb))
        i += 1
    entries.append(None)

    call = re.compile(r'Shim(?:Text|Format)\(\s*"(openshim_ui:[^"]+)",\s*((?:"(?:[^"\\\n]|\\.)*"\s*)+)')
    seen = {}
    for path in sorted(SOURCES.glob("*.cpp")):
        for m in call.finditer(path.read_text(encoding="utf-8")):
            english = "".join(unescape(s) for s in re.findall(r'"(?:[^"\\\n]|\\.)*"', m.group(2)))
            key = m.group(1)
            if key in seen and seen[key] != english:
                raise SystemExit(f"{key} has two English texts: {seen[key]!r} / {english!r}")
            if key not in seen:
                seen[key] = english
                entries.append((key, english))
    return entries, rows, arrays


def read_table(path):
    """key -> list of 7 language cells (raw latin-1 strings)."""
    if not path.exists():
        return {}
    cells = {}
    for line in path.read_bytes().decode("latin-1").splitlines():
        if not line or line.startswith("~"):
            continue
        fields = line.split("~")
        if fields[0] == "Key":
            continue
        cells[fields[0]] = (fields[1:] + [""] * len(HEADER))[: len(HEADER) - 1]
    return cells


def render(entries, rows, arrays, existing):
    valid_value_keys = {
        f"openshim_opt:{row_id(row)}:value:{value}"
        for row in rows for value in arrays[row["values"]]
    }
    lines = ["~".join(HEADER), SPACER]
    generated = set()
    for entry in entries:
        if entry is None:
            lines.append(SPACER)
            continue
        key, english = entry
        if english is None or "~" in english or "\n" in english:
            raise SystemExit(f"{key}: English must be one line without '~': {english!r}")
        try:
            english.encode("cp1252")
        except UnicodeEncodeError:
            raise SystemExit(f"{key}: English must be cp1252: {english!r}")
        generated.add(key)
        old = existing.get(key, [""] * (len(HEADER) - 1))
        lines.append("~".join([key, english.encode("cp1252").decode("latin-1")] + old[1:]))

    # Per-row value overrides are optional and only ever added by hand.
    overrides = sorted(k for k in existing if k in valid_value_keys and k not in generated)
    for key in overrides:
        lines.append("~".join([key] + existing[key]))
    if overrides:
        lines.append(SPACER)

    dropped = sorted(k for k in existing if k not in generated and k not in valid_value_keys)
    return "\r\n".join(lines) + "\r\n", dropped


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--check", action="store_true", help="fail if the table is out of date")
    args = parser.parse_args()

    entries, rows, arrays = generated_entries()
    existing = read_table(TABLE)
    text, dropped = render(entries, rows, arrays, existing)
    data = text.encode("latin-1")

    if args.check:
        if not TABLE.exists() or TABLE.read_bytes() != data:
            print(f"{TABLE.relative_to(ROOT)} is stale; run python scripts/sync_options_localization.py",
                  file=sys.stderr)
            for key in dropped:
                print(f"  unknown key would be dropped: {key}", file=sys.stderr)
            return 1
        print(f"{TABLE.relative_to(ROOT)} is current ({sum(e is not None for e in entries)} keys)")
        return 0

    for key in dropped:
        print(f"dropping unknown key: {key}")
    TABLE.parent.mkdir(parents=True, exist_ok=True)
    TABLE.write_bytes(data)
    print(f"wrote {TABLE.relative_to(ROOT)} ({sum(e is not None for e in entries)} keys)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
