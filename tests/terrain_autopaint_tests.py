"""Automatic terrain paint: synthetic maps only, no game files or artwork."""
import importlib.util
import json
from pathlib import Path
import struct
import tempfile
import unittest

import numpy as np
from PIL import Image

spec = importlib.util.spec_from_file_location("autopaint", Path(__file__).parents[1] / "scripts/Build-TerrainAutoPaint.py")
auto = importlib.util.module_from_spec(spec)
spec.loader.exec_module(auto)


def reference_fingerprint(zones_x, zones_z, plane):
    """Straight transcription of the runtime hash for a (zones+1) grid, one sample at a time."""
    def step(h, value):
        for shift in (0, 8, 16, 24):
            h = ((h ^ ((value >> shift) & 255)) * 1099511628211) % (1 << 64)
        return h
    nx, nz = zones_x + 1, zones_z + 1
    h = step(14695981039346656037, nx * nz)
    for i in range(nx):
        for j in range(nz):
            h = step(step(h, i), j)
            for z in range(256):
                for x in range(256):
                    sx, sz = i * 256 - 128 + x, j * 256 - 128 + z
                    inside = 0 <= sx < plane.shape[1] and 0 <= sz < plane.shape[0]
                    h = step(h, int(plane[sz, sx]) if inside else 0)
    return f"{h:016x}"


class AutoPaintTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(); self.addCleanup(temp.cleanup); self.root = Path(temp.name)
        rng = np.random.default_rng(7)
        self.plane = rng.integers(0, 3000, size=(256, 512), dtype=np.uint16)  # 2x1 zones
        zones = np.stack([self.plane[:, :256], self.plane[:, 256:]])           # zone-major
        (self.root / "m.hg2").write_bytes(struct.pack("<HHHHI", 1, 8, 2, 1, 10) + zones.astype("<u2").tobytes())
        cells = np.zeros((64, 128), dtype=np.uint16)
        cells[:, 64:] = (1 << 12) | (1 << 8)           # right zone: solid type 1
        cells[0, 0] = (0 << 12) | (1 << 8) | (1 << 7) # one diagonal 0 -> 1
        mat_zones = np.stack([cells[:, :64], cells[:, 64:]])
        (self.root / "m.mat").write_bytes(mat_zones.astype("<u2").tobytes())
        (self.root / "m.trn").write_text("[TextureType0] // Sandy\nSolidA0=a.map\n[TextureType1] // Rocky\nSolidA0=b.map\n")
        for i, color in enumerate(("red", "green", "blue", "white")):
            Image.new("RGB", (8, 8), color).save(self.root / f"art{i}.png")
        self.recipe = {"schema": "bzr-openshim-terrain-autopaint-v1", "material": "TERRAIN", "diffuseResource": "atlas.dds",
                       "typeNames": {"0": "Sandy", "1": "Rocky"}, "typeWeights": {"0": [1, 0, 0, 0], "1": [0, 1, 0, 0]},
                       "transition": {"cap": 0.3, "diagonal": 0.5}, "blurMeters": 0,
                       "layers": [{"name": f"L{i}", "file": f"art{i}.png", "repeatMeters": 16} for i in range(4)]}

    def test_fingerprint_matches_reference_and_ignores_high_bits(self):
        zx, zz, plane = auto.read_hg2(self.root / "m.hg2")
        self.assertEqual((zx, zz), (2, 1))
        self.assertEqual(auto.terrain_fingerprint(zx, zz, plane), reference_fingerprint(zx, zz, plane))
        # Stock misn04 (4x3 zones): bounds measured in game on a (zones+1) grid.
        self.assertEqual(auto.terrain_bounds(4, 3), [-3190.0, -2570.0, 3210.0, 2550.0])

    def test_weights_follow_mat_cells_and_normalize(self):
        files = (self.root / "m.hg2", self.root / "m.mat", self.root / "m.trn")
        info = auto.load_map("m", files, self.recipe, None, 512)
        weights, bounds = info["weights"], info["bounds"]
        def at(x_world, z_world):
            px = int((x_world - bounds[0]) / (bounds[2] - bounds[0]) * weights.width)
            pz = int((z_world - bounds[1]) / (bounds[3] - bounds[1]) * weights.height)
            return weights.getpixel((px, pz))
        # Native frame for a 2x1 zone file: X = 5 * (sx - 256), Z = -5 * (sz - 128); MAT cell c
        # spans mesh samples 4c + 2 .. 4c + 6, so cell (0, 0) covers X -1270..-1250, Z 610..630.
        self.assertEqual(at(5 * (400 - 256), -5 * (100 - 128)), (0, 255, 0, 0))   # right zone: rocky soil
        self.assertEqual(at(5 * (100 - 256), -5 * (100 - 128)), (255, 0, 0, 0))   # left zone: sand
        diagonal = at(-1260, 620)                                                    # the one 0 -> 1 diagonal cell
        self.assertTrue(diagonal[0] > 100 and diagonal[1] > 100 and diagonal[2] == diagonal[3] == 0, diagonal)
        self.assertEqual(at(-1260, 590), (255, 0, 0, 0))                             # +Z end is row 0; row 1 is solid
        self.assertEqual(at(-1230, 620), (255, 0, 0, 0))                             # next cell along +X is solid
        self.assertTrue(all(sum(p) == 255 for p in weights.getdata()))

    def test_unknown_texture_layout_is_declined(self):
        self.recipe["typeNames"]["1"] = "Basalt"
        with self.assertRaisesRegex(ValueError, "recipe expects"):
            auto.load_map("m", (self.root / "m.hg2", self.root / "m.mat", self.root / "m.trn"), self.recipe, None, 64)

    def test_multi_map_manifest_shares_identical_controls(self):
        files = (self.root / "m.hg2", self.root / "m.mat", self.root / "m.trn")
        maps = [auto.load_map(name, files, self.recipe, None, 64) for name in ("alpha", "beta")]
        maps[1]["fingerprint"] = "0123456789abcdef"  # the same layout under another terrain shape
        recipe_path = self.root / "recipe.json"; recipe_path.write_text(json.dumps(self.recipe))
        manifest = auto.build_pack(maps, self.recipe, self.root, self.root / "out", 64, "test_auto", False)
        binding = manifest["materials"]["TERRAIN"]
        entries = binding["paint"]["maps"]
        self.assertEqual([e["terrainFingerprint"] for e in entries], [maps[0]["fingerprint"], "0123456789abcdef"])
        self.assertEqual(entries[0]["control"], entries[1]["control"])
        self.assertEqual(binding["tiles"]["4"], entries[0]["control"])
        self.assertEqual(binding["sliceCount"], 5)
        self.assertNotIn("terrainFingerprint", binding["paint"])
        with Image.open(self.root / "out" / entries[0]["control"]) as control:
            self.assertEqual(control.size, (64, 64))
        self.assertTrue((self.root / "out" / "test_auto_alpha_editor.html").exists())
        self.assertEqual(len(list((self.root / "out").glob("*_control.png"))), 1)


if __name__ == "__main__":
    unittest.main()
