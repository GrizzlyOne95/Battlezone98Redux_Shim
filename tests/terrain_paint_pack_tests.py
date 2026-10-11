import importlib.util
import json
from pathlib import Path
import tempfile
import unittest

from PIL import Image

spec=importlib.util.spec_from_file_location("paint_pack",Path(__file__).parents[1]/"scripts/Build-TerrainPaintPack.py")
paint=importlib.util.module_from_spec(spec)
spec.loader.exec_module(paint)


class PaintPackTests(unittest.TestCase):
    def setUp(self):
        temp=tempfile.TemporaryDirectory();self.addCleanup(temp.cleanup);self.root=Path(temp.name)
        self.capture=self.root/"capture.json";self.recipe=self.root/"recipe.json"
        self.mapping={"terrainFingerprint":"0123456789abcdef","boundsMeters":[-100,-200,300,400],"rowZero":"minZ"}
        self.capture.write_text(json.dumps({"schema":"bzr-openshim-terrain-atlas-v1","material":"TERRAIN","diffuseResource":"mars.dds","paintMap":self.mapping}))
        colors=["red","green","blue","white"]
        layers=[]
        for i,color in enumerate(colors):
            Image.new("RGB",(8,8),color).save(self.root/f"art{i}.png")
            layers.append({"name":f"Layer {i}","file":f"art{i}.png","repeatMeters":16})
        self.art={"schema":"bzr-openshim-terrain-paint-art-v1","layers":layers}
        self.recipe.write_text(json.dumps(self.art))

    def build(self,**kwargs):
        return paint.build_pack(self.capture,self.recipe,self.root,self.root/"out",size=64,weight_size=64,**kwargs)["materials"]["TERRAIN"]

    def test_array_and_map_contract(self):
        binding=self.build()
        self.assertEqual(binding["sliceCount"],5)
        self.assertEqual(binding["diffuseResource"],"mars.dds")
        self.assertEqual(binding["paint"]["terrainFingerprint"],self.mapping["terrainFingerprint"])
        for name in binding["tiles"].values():
            with Image.open(self.root/"out"/name) as im:
                self.assertEqual(im.size,(64,64));self.assertEqual(im.mode,"RGBA")
        with Image.open(self.root/"out"/binding["tiles"]["4"]) as im:
            # RGB survives even though the fourth weight is zero (PNG alpha 0).
            self.assertEqual(im.getpixel((0,0)),(255,0,0,0))
        html=(self.root/"out"/"openshim_mars_paint_editor.html").read_text()
        self.assertNotIn("__PAINT_",html)
        self.assertIn("TerrainPaintCodec.encode",html)

    def test_soft_brush_world_coordinates_and_undo_source(self):
        image=Image.new("RGBA",(64,64),(255,0,0,0));before=image.copy()
        paint.paint_stroke(image,[-32,-32,32,32],3,.5,.5,12,1)
        self.assertEqual(before.getpixel((32,32)),(255,0,0,0))
        self.assertEqual(image.getpixel((32,32)),(0,0,0,255))
        self.assertEqual(image.getpixel((44,32)),(255,0,0,0))
        edge=image.getpixel((39,32));self.assertGreater(edge[0],0);self.assertGreater(edge[3],0)
        self.assertTrue(all(sum(p)==255 for p in image.getdata()))
        # Repainting replaces rather than accumulating invalid weight sums.
        paint.paint_stroke(image,[-32,-32,32,32],1,.5,.5,12,1)
        self.assertEqual(image.getpixel((32,32)),(0,255,0,0))

    def test_import_preserves_all_four_channels_and_normalizes(self):
        weights=Image.new("RGBA",(64,64),(255,255,0,0));weights.putpixel((0,0),(0,0,0,0))
        path=self.root/"weights.png";weights.save(path)
        binding=self.build(weights_path=path)
        with Image.open(self.root/"out"/binding["tiles"]["4"]) as im:
            self.assertEqual(im.getpixel((0,0)),(255,0,0,0))
            self.assertEqual(im.getpixel((32,32)),(128,127,0,0))

    def test_no_outputs_for_invalid_map_or_material(self):
        self.mapping["terrainFingerprint"]="bad"
        self.capture.write_text(json.dumps({"schema":"bzr-openshim-terrain-atlas-v1","material":"TERRAIN","diffuseResource":"mars.dds","paintMap":self.mapping}))
        with self.assertRaises(ValueError):self.build()
        self.assertFalse((self.root/"out").exists())

    def test_independent_control_resolution_does_not_premultiply_weights(self):
        weights=Image.new("RGBA",(64,64),(0,255,0,0))
        path=self.root/"weights.png";weights.save(path)
        result=paint.build_pack(self.capture,self.recipe,self.root,self.root/"out",
                               size=128,weight_size=64,weights_path=path)
        name=result["materials"]["TERRAIN"]["tiles"]["4"]
        with Image.open(self.root/"out"/name) as im:
            self.assertEqual(im.size,(128,128))
            self.assertEqual(im.getpixel((40,40)),(0,255,0,0))

    def test_wrong_format_missing_layers_and_source_escape(self):
        self.art["layers"][0]["repeatMeters"]=float("nan");self.recipe.write_text(json.dumps(self.art))
        with self.assertRaises(ValueError):self.build()
        self.art["layers"][0]["repeatMeters"]=16;self.art["layers"][0]["file"]="../outside.png";self.recipe.write_text(json.dumps(self.art))
        with self.assertRaises(ValueError):self.build()
        self.art["layers"].pop();self.recipe.write_text(json.dumps(self.art))
        with self.assertRaises(ValueError):self.build()

    def test_output_requires_explicit_overwrite(self):
        self.build()
        with self.assertRaises(ValueError):self.build()
        self.build(force=True)


if __name__=="__main__":unittest.main()
