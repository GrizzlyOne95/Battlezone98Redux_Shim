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


def reference_fingerprint(zones_x, zones_z, plane, pad=0):
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
                    h = step(h, int(plane[sz, sx]) & 0xFFF if inside else pad)
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
        # Outside the HG2 the engine reads [Size] Height / 0.1 (Titan: 50 -> 500).
        self.assertEqual(auto.terrain_fingerprint(zx, zz, plane, 500), reference_fingerprint(zx, zz, plane, 500))
        trn = self.root / "pad.trn"
        trn.write_text("[Size]\nWidth=5120\nHeight=50\n[TextureType0]\nHeight=7\n")
        self.assertEqual(auto.read_trn_pad(trn), 500)
        self.assertEqual(auto.read_trn_pad(self.root / "m.trn"), 0)
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

    def test_trn_names_parse_from_comments_or_bare_text(self):
        trn = self.root / "names.trn"
        trn.write_text("[TextureType0] // Sulphur Deposits\n[TextureType1] Liquid Sulphur\n[TextureType3]\nSolidA0=c.map\n")
        self.assertEqual(auto.read_trn_types(trn), {0: "Sulphur Deposits", 1: "Liquid Sulphur", 3: ""})

    def test_type_name_alternatives(self):
        files = (self.root / "m.hg2", self.root / "m.mat", self.root / "m.trn")
        self.recipe["typeNames"]["1"] = ["", "Rocky"]
        auto.validate_recipe(self.recipe)
        auto.load_map("m", files, self.recipe, None, 64)
        self.recipe["typeNames"]["1"] = []
        with self.assertRaisesRegex(ValueError, "typeNames"):
            auto.validate_recipe(self.recipe)

    def test_seamless_layer_wraps_continuously(self):
        ramp = np.tile(np.linspace(0, 255, 64, dtype=np.float64), (64, 1))
        image = Image.fromarray(np.stack([ramp] * 3, axis=-1).astype(np.uint8))
        out = np.asarray(auto.make_seamless(image), dtype=np.float64)[..., 0]
        self.assertLess(abs(out[:, 0] - out[:, -1]).mean(), 10)          # was 255 across the wrap
        self.assertAlmostEqual(out[32, 32], ramp[32, 32], delta=1)        # centre unchanged

    def test_match_mean_takes_reference_palette(self):
        art = Image.fromarray(np.stack([np.full((8, 8), v, np.uint8) for v in (100, 100, 100)], axis=-1))
        reference = Image.new("RGB", (4, 4), (50, 80, 120))
        mean = np.asarray(auto.match_mean(art, reference), dtype=np.float64).reshape(-1, 3).mean(axis=0)
        np.testing.assert_allclose(mean, (50, 80, 120), atol=1)

    def test_variation_and_slope_reweight_cells(self):
        cells = np.zeros((32, 32), dtype=np.uint16)                 # one type everywhere
        recipe = dict(self.recipe, variation={"meters": 200, "amount": 1, "types": {"0": [0, 0, 1, 0]}})
        field = auto.cell_field(cells, None, recipe, seed=3)
        self.assertTrue(field[..., 0].max() > 0.99 and field[..., 2].max() > 0.99, "patches reach both layers")
        np.testing.assert_allclose(field.sum(axis=2), 1)
        np.testing.assert_array_equal(field, auto.cell_field(cells, None, recipe, seed=3))
        plane = np.zeros((128, 128), dtype=np.uint16)
        plane[:, 64:] = (np.arange(64) * 100)[None, :]              # 10 m rise per 5 m sample: 63 degrees
        recipe = dict(self.recipe, slope={"weights": [0, 0, 0, 1], "startDegrees": 25, "fullDegrees": 40})
        field = auto.cell_field(cells, plane, recipe, seed=0)
        self.assertEqual(tuple(field[5, 4]), (1, 0, 0, 0))           # flat
        self.assertEqual(tuple(field[5, 24]), (0, 0, 0, 1))          # steep
        recipe["slope"]["fullDegrees"] = 20
        with self.assertRaisesRegex(ValueError, "slope"):
            auto.validate_recipe(recipe)

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
        self.assertEqual(binding["sliceCount"], 9)
        self.assertEqual(sorted(binding["tiles"], key=int), [str(i) for i in range(9)])
        self.assertEqual(binding["paint"]["heightMeters"], [0, 0, 0, 0])
        with Image.open(self.root / "out" / binding["tiles"]["5"]) as normal:
            self.assertEqual((normal.mode, normal.getpixel((3, 3))[:3]), ("RGBA", (128, 128, 255)))
        self.assertNotIn("terrainFingerprint", binding["paint"])
        with Image.open(self.root / "out" / entries[0]["control"]) as control:
            self.assertEqual(control.size, (64, 64))
        self.assertTrue((self.root / "out" / "test_auto_alpha_editor.html").exists())
        self.assertEqual(len(list((self.root / "out").glob("*_control.png"))), 1)

    def test_missions_sharing_a_terrain_get_one_entry(self):
        files = (self.root / "m.hg2", self.root / "m.mat", self.root / "m.trn")
        maps = [auto.load_map(name, files, self.recipe, None, 64) for name in ("alpha", "alpha_b")]
        manifest = auto.build_pack(maps, self.recipe, self.root, self.root / "out", 64, "test_auto", False)
        self.assertEqual(len(manifest["materials"]["TERRAIN"]["paint"]["maps"]), 1)
        maps[1]["weights"] = maps[1]["weights"].transpose(Image.Transpose.FLIP_LEFT_RIGHT)
        with self.assertRaisesRegex(ValueError, "share terrain"):
            auto.build_pack(maps, self.recipe, self.root, self.root / "out2", 64, "test_auto", False)

    def test_full_material_uses_archive_maps_and_orients_normals(self):
        import zipfile
        size, repeat = 64, 16
        x = np.arange(size)
        height = np.tile(0.5 + 0.4 * np.sin(2 * np.pi * x / size), (size, 1))  # varies along columns
        dh = np.gradient(height, axis=1)
        normal = np.dstack((-dh / np.abs(dh).max() * 0.5, np.zeros_like(dh), np.ones_like(dh)))
        normal[..., 1] = -normal[..., 0]  # Y disagrees: must be checked, and flipped, against the height
        height2 = (height + height.T) / 2
        def png(a, mode):
            stream = __import__("io").BytesIO(); Image.fromarray(a, mode).save(stream, format="PNG"); return stream.getvalue()
        enc = lambda a: np.clip(a * 127.5 + 127.5, 0, 255).astype(np.uint8)
        with zipfile.ZipFile(self.root / "rock.zip", "w") as z:
            z.writestr("Rock_BaseColor.png", png(np.full((size, size, 3), 90, np.uint8), "RGB"))
            z.writestr("Rock_Normal.png", png(enc(normal), "RGB"))
            z.writestr("Rock_Displacement.png", png((height * 255).astype(np.uint8), "L"))
            z.writestr("Rock_Roughness.png", png(np.full((size, size), 204, np.uint8), "L"))
        layer = {"name": "Rock", "archive": "rock.zip", "member": "Rock_BaseColor.png", "repeatMeters": repeat}
        self.assertEqual(auto.material_source(self.root.resolve(), layer, "normal")["member"], "Rock_Normal.png")
        diffuse, _ = auto._hd.load_art(self.root.resolve(), layer)
        n, h, spec, identity = auto.material_maps(self.root.resolve(), layer, diffuse, size, repeat)
        self.assertEqual(identity["normalFlipXY"], [False, False])
        self.assertAlmostEqual(float(spec.mean()), 0.2, places=2)
        slope = np.gradient(h, axis=1)
        self.assertGreater(float(np.mean(n[..., 0] * -slope)), 0)
        # A normal whose X points uphill is flipped back.
        flipped, flips = auto.orient_normal(np.dstack((-n[..., 0], n[..., 1], n[..., 2])), h)
        self.assertEqual(flips[0], True)
        recipe = dict(self.recipe, heightBlend=0.75, layers=[dict(layer, heightMeters=2.5)] + self.recipe["layers"][1:])
        auto.validate_recipe(recipe)
        files = (self.root / "m.hg2", self.root / "m.mat", self.root / "m.trn")
        maps = [auto.load_map("alpha", files, recipe, None, 64)]
        binding = auto.build_pack(maps, recipe, self.root, self.root / "out", size, "test_auto", False)["materials"]["TERRAIN"]
        self.assertEqual((binding["paint"]["heightBlend"], binding["paint"]["heightMeters"]), (0.75, [2.5, 0, 0, 0]))
        with Image.open(self.root / "out" / binding["tiles"]["0"]) as d, Image.open(self.root / "out" / binding["tiles"]["5"]) as nh:
            self.assertEqual(d.getpixel((5, 5))[3], 51)                 # specular = 1 - roughness 0.8
            self.assertGreater(np.ptp(np.asarray(nh)[..., 3]), 200)    # height stretched to 0..1
        diffuse_only = auto.build_pack(maps, dict(recipe, diffuseOnly=True), self.root, self.root / "out5", size, "test_auto", False)
        self.assertEqual(diffuse_only["materials"]["TERRAIN"]["sliceCount"], 5)
        self.assertNotIn("heightMeters", diffuse_only["materials"]["TERRAIN"]["paint"])
        with self.assertRaisesRegex(ValueError, "heightMeters"):
            auto.validate_recipe(dict(recipe, layers=[dict(layer, heightMeters=40)] + self.recipe["layers"][1:]))


if __name__ == "__main__":
    unittest.main()
