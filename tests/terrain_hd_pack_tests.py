import importlib.util
import json
from pathlib import Path
import tempfile
import unittest
import zipfile

from PIL import Image

spec = importlib.util.spec_from_file_location("terrain_pack", Path(__file__).parents[1] / "scripts/Build-TerrainHdPack.py")
pack = importlib.util.module_from_spec(spec)
spec.loader.exec_module(pack)


class PackTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.atlas = self.root / "atlas.png"
        image = Image.new("RGBA", (128, 64), "red")
        image.paste(Image.new("RGBA", (64, 64), "blue"), (64, 0))
        image.putpixel((64, 0), (0, 255, 0, 255))
        image.save(self.atlas)
        # Native IDs intentionally disagree with CSV order; the second row
        # repeats a tile name at another rectangle, like the actual Mars CSV.
        self.capture = self.root / "capture.json"
        self.write_capture({"schema": "bzr-openshim-terrain-atlas-v1", "material": "TERRAIN",
            "diffuseResource": "atlas.png", "width": 128, "height": 64,
            "tiles": {"9": [0, 0, .5, 1], "2": [.5, 0, .5, 1], "3": [.5, 0, .5, 1]},
            "usedIndices": [2, 9]})
        self.csv = self.root / "atlas.csv"
        self.csv.write_text("DIRT.MAP,0,0,0.5,1\nDIRT.MAP,0.5,0,0.5,1\n")

    def write_capture(self, data):
        self.capture.write_text(json.dumps(data))

    def build(self, **kwargs):
        return pack.build_pack(self.capture, self.atlas, self.root / "out", tile_size=64,
                               atlas_csv=self.csv, **kwargs)

    def test_native_index_and_orientation_not_csv_order(self):
        manifest, report = self.build()
        binding = pack.read_json(manifest)["materials"]["TERRAIN"]
        self.assertEqual(binding["sliceCount"], 10)
        self.assertEqual(binding["diffuseResource"], "atlas.png")
        self.assertEqual(binding["tiles"]["2"], binding["tiles"]["3"])
        with Image.open(manifest.parent / binding["tiles"]["2"]) as image:
            self.assertEqual(image.mode, "RGBA")
            self.assertEqual(image.size, (64, 64))
            self.assertEqual(image.getpixel((0, 0)), (0, 255, 0, 255))
            self.assertEqual(image.getpixel((0, 63)), (0, 0, 255, 255))
        with Image.open(manifest.parent / binding["tiles"]["9"]) as image:
            self.assertEqual(image.getpixel((32, 32)), (255, 0, 0, 255))
        self.assertEqual(report["uniqueImages"], 2)
        self.assertEqual(report["tiles"][0]["names"], ["DIRT.MAP"])

    def test_missing_used_tile_fails_before_writing(self):
        capture = pack.read_json(self.capture)
        capture["usedIndices"].append(255)
        self.write_capture(capture)
        with self.assertRaisesRegex(ValueError, "every used"):
            self.build()
        self.assertFalse((self.root / "out").exists())

    def test_bad_rectangles_rejected(self):
        for rect in ([float("nan"), 0, .5, 1], [0, 0, 1.1, 1], [0, 0, 0, 1], [.001, 0, .5, 1]):
            with self.subTest(rect=rect), self.assertRaises(ValueError):
                pack.pixel_box(rect, 128, 64)

    def test_wrong_atlas_identity_and_dimensions(self):
        capture = pack.read_json(self.capture)
        for key, value in (("diffuseResource", "another.png"), ("width", 256)):
            changed = dict(capture, **{key: value})
            self.write_capture(changed)
            with self.assertRaises(ValueError):
                self.build()

    def test_partial_art_replacement_keeps_edges_alpha_and_transition(self):
        stock = Image.new("RGBA", (64, 64), (10, 20, 30, 123))
        tile = pack.replacement_tile(stock, Image.new("RGB", (64, 64), "white"), 4, False)
        self.assertEqual(tile.getpixel((32, 32)), (255, 255, 255, 123))
        for point in ((0, 32), (63, 32), (32, 0), (32, 63)):
            self.assertEqual(tile.getpixel(point), stock.getpixel(point))
        self.csv.write_text("DIRT.MAP,0,0,0.5,1\nTRANSITION.MAP,0.5,0,0.5,1\n")
        Image.new("RGB", (64, 64), "white").save(self.root / "art.png")
        recipe = self.root / "recipe.json"
        recipe.write_text(json.dumps({"schema": "bzr-openshim-terrain-art-v1", "matchStockColor": False,
            "replacements": {"DIRT.MAP": {"file": "art.png"}}}))
        manifest, report = self.build(recipe_path=recipe, source_root=self.root)
        binding = pack.read_json(manifest)["materials"]["TERRAIN"]
        with Image.open(manifest.parent / binding["tiles"]["2"]) as image:
            self.assertEqual(image.getpixel((32, 32)), (0, 0, 255, 255))
        with Image.open(manifest.parent / binding["tiles"]["9"]) as image:
            self.assertEqual(image.getpixel((32, 32)), (255, 255, 255, 255))
        self.assertIn("sha256", report["artwork"]["DIRT.MAP"])

    def test_zip_member_and_root_boundaries(self):
        art = self.root / "art.png"
        Image.new("RGB", (64, 64), "white").save(art)
        with zipfile.ZipFile(self.root / "art.zip", "w") as archive:
            archive.write(art, "albedo.png")
        image, identity = pack.load_art(self.root, {"archive": "art.zip", "member": "albedo.png"})
        self.assertEqual(image.size, (64, 64))
        self.assertEqual(identity["member"], "albedo.png")
        with self.assertRaises(ValueError):
            pack.source_path(self.root, "../outside.png")
        with self.assertRaises(ValueError):
            pack.load_art(self.root, {"archive": "art.zip", "member": "../albedo.png"})
        with self.assertRaises(ValueError):
            pack.load_art(self.root, {"file": "art.png", "archive": "art.zip"})

    def test_refuses_existing_output_by_default(self):
        self.build()
        with self.assertRaisesRegex(ValueError, "already exist"):
            self.build()


if __name__ == "__main__":
    unittest.main()
