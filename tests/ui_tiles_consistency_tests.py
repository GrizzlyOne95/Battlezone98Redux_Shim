"""Keeps the custom UI image list identical everywhere it is written down.

The same 18 images are listed by the installer, the uninstaller, the shipped
resources folder and the C++ that loads them. A tile added to only some of those
is deployed but never removed, or shipped but never installed, so this compares
all four and names the files that differ.
"""
import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

# Only the tiles OpenShim ships; stock images (blackui, optionck, topcorner,
# tomn*, mpcron, ...) are referenced by the code but belong to the game.
TILE_PATTERN = re.compile(r"\bosh_[a-z0-9_]+\.png\b|\b(?:uiline|uiplate|uibtnhv|uibtn)\.png\b")
SOURCE_LITERAL = re.compile(r'"((?:osh_[a-z0-9_]+|uiline|uiplate|uibtnhv|uibtn)\.png)"')


def script_tiles(path):
    text = path.read_text(encoding="utf-8", errors="replace")
    match = re.search(r"\$uiTiles\s*=\s*@\((.*?)\)", text, re.S)
    if not match:
        raise AssertionError("no $uiTiles array in %s" % path)
    return set(re.findall(r'"([^"]+)"', match.group(1)))


def source_tiles():
    found = set()
    for folder in ("src", "include"):
        for path in (ROOT / folder).rglob("*"):
            if path.suffix.lower() not in (".cpp", ".h", ".hpp", ".c", ".inl"):
                continue
            text = path.read_text(encoding="utf-8", errors="replace")
            found.update(SOURCE_LITERAL.findall(text))
    return found


class UiTilesConsistency(unittest.TestCase):
    def test_all_sources_list_the_same_tiles(self):
        sources = {
            "install_windows.ps1 $uiTiles": script_tiles(ROOT / "scripts" / "install_windows.ps1"),
            "uninstall_windows.ps1 $uiTiles": script_tiles(ROOT / "scripts" / "uninstall_windows.ps1"),
            "resources/ui/custom_widgets/*.png": {
                p.name for p in (ROOT / "resources" / "ui" / "custom_widgets").glob("*.png")},
            "string literals in src/ and include/": source_tiles(),
        }
        for name, tiles in sources.items():
            self.assertTrue(tiles, "%s lists no tiles" % name)

        union = set().union(*sources.values())
        problems = []
        for name, tiles in sources.items():
            missing = sorted(union - tiles)
            if missing:
                problems.append("%s is missing: %s" % (name, ", ".join(missing)))
        self.assertFalse(problems, "UI tile lists disagree:\n  " + "\n  ".join(problems))

    def test_every_tile_name_matches_the_tile_pattern(self):
        # Guards the pattern itself: a renamed tile family would otherwise drop
        # out of the comparison silently.
        for tile in script_tiles(ROOT / "scripts" / "install_windows.ps1"):
            self.assertTrue(TILE_PATTERN.fullmatch(tile), "%s is not covered by TILE_PATTERN" % tile)


if __name__ == "__main__":
    unittest.main()
