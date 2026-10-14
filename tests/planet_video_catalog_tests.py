"""Guard the instruction/operand distinction in the planet native bindings."""
import json
from pathlib import Path
import unittest


class CatalogTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.catalog = json.loads((Path(__file__).resolve().parents[1] / "scripts/patches.json").read_text())

    def test_required_bindings_cannot_fall_back_to_unverified_addresses(self):
        rows = [r for r in self.catalog["resolves"] if r["name"].startswith("PlanetVideo::")]
        self.assertEqual(len(rows), 7)
        for row in rows:
            with self.subTest(binding=row["name"]):
                self.assertTrue(row["require_unique"])
                self.assertEqual(int(row["fallback"], 16), 0)
                self.assertEqual(row["prefer"], "scan")

    def test_call_target_offsets_name_the_instruction(self):
        for row in self.catalog["resolves"]:
            if row["name"].startswith("PlanetVideo::") and row["mode"] == "rel32_target":
                with self.subTest(binding=row["name"]):
                    pattern = row["pattern"].split()
                    self.assertEqual(pattern[row["offset"]], "E8")
                    self.assertEqual(pattern[row["offset"] + 1:row["offset"] + 5], ["??"] * 4)

    def test_only_the_custom_call_operand_is_replaced(self):
        row = next(r for r in self.catalog["patches"] if r["name"] == "Custom Planet Video Playback")
        pattern = row["pattern"].split()
        self.assertEqual(row["platforms"], ["gog"])
        self.assertEqual(row["expected_size"], 4)
        self.assertEqual(pattern[row["offset"] - 1], "E8")
        self.assertEqual(pattern[row["offset"]:row["offset"] + 4], ["??"] * 4)


if __name__ == "__main__":
    unittest.main()
