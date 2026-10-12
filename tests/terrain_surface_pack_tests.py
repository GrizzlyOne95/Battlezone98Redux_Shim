import importlib.util
import json
import math
from pathlib import Path
import struct
import tempfile
import unittest
from PIL import Image

spec=importlib.util.spec_from_file_location('surface',Path(__file__).resolve().parents[1]/'scripts/Build-TerrainSurfacePack.py')
surface=importlib.util.module_from_spec(spec)
spec.loader.exec_module(surface)


class SurfacePack(unittest.TestCase):
    def test_height_gradient_and_exact_borders(self):
        normal=Image.new('RGBA',(64,64),(128,128,255,231))
        height=Image.new('F',normal.size)
        height.putdata([x/63 for y in range(64) for x in range(64)])
        result,values=surface.height_normals(normal,height,.5,20,8)
        self.assertLess(result.getpixel((32,32))[0],128)
        self.assertAlmostEqual(result.getpixel((32,32))[1],128,delta=1)
        for y in range(64):
            self.assertEqual(result.getpixel((0,y)),normal.getpixel((0,y)))
            self.assertEqual(values[y*64],0)
            self.assertEqual(result.getpixel((63,y)),normal.getpixel((63,y)))
        self.assertLessEqual(max(abs(v) for v in values),.5)
        # A flat neutral height leaves both normal direction and geometry zero.
        flat,heights=surface.height_normals(normal,Image.new('F',normal.size,.5),.5,20,8)
        self.assertEqual(flat.getpixel((32,32))[:3],normal.getpixel((32,32))[:3])
        self.assertTrue(all(v==0 for v in heights))

    def test_invalid_physical_data_rejects(self):
        normal=Image.new('RGBA',(16,16),(128,128,255,255))
        for amplitude in (True,0,2,float('nan')):
            with self.assertRaises(ValueError):
                surface.height_normals(normal,Image.new('F',normal.size,.5),amplitude,20,2)
        for sample in (float('nan'),-1,2):
            with self.assertRaises(ValueError):
                surface.height_normals(normal,Image.new('F',normal.size,sample),.25,20,2)
        # The normal-only contract permits a taper reaching half the tile.
        surface.height_normals(normal,Image.new('F',normal.size,.5),.25,20,8)
        with self.assertRaises(ValueError):
            surface.height_normals(normal,Image.new('F',normal.size,.5),.25,20,8,1)

    def fixture(self,root):
        capture={'schema':'bzr-openshim-terrain-atlas-v1','material':'MN_DETAIL_ATLAS','diffuseResource':'moon_atlas_d.dds',
                 'tiles':{'7':[0,0,.5,.5],'19':[0,0,.5,.5],'20':[.5,0,.5,.5]},'usedIndices':[7,19,20]}
        recipe={'schema':'bzr-openshim-terrain-surface-art-v1','sourceNormalResource':'normal.png','edgePixels':8,
                'tiles':{'7':{'height':'height.png','heightMeters':.5}}}
        Image.new('RGBA',(128,128),(128,128,255,255)).save(root/'normal.png')
        Image.new('L',(64,64),220).save(root/'height.png')
        (root/'capture.json').write_text(json.dumps(capture))
        (root/'recipe.json').write_text(json.dumps(recipe))
        return capture,recipe

    def test_complete_linear_dds_and_identity(self):
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp); self.fixture(root)
            path,report=surface.build(root/'capture.json',root/'normal.png',root/'recipe.json',root,root/'out')
            manifest=json.loads(path.read_text())
            self.assertFalse(report['heightGeometry'])
            self.assertEqual(report['tiles'][0]['aliasedEngineIndices'],[7,19])
            self.assertEqual(manifest['heightUsage'],'normal-lighting-only')
            self.assertEqual(manifest['sourceDiffuseResource'],'moon_atlas_d.dds')
            data=(root/'out'/manifest['normalAtlas']).read_bytes()
            header=struct.unpack('<31I',data[4:128])
            self.assertEqual(header[6],8)
            self.assertEqual(header[20],0)  # no DX10/sRGB fourCC
            self.assertEqual(len(data),128+sum((128>>i)**2*4 for i in range(8)))
            with Image.open(root/'out'/manifest['normalAtlas']) as image:
                self.assertEqual(image.size,(128,128))
                self.assertEqual(image.getpixel((100,100)),(128,128,255,255))
            with self.assertRaises(ValueError):
                surface.build(root/'capture.json',root/'normal.png',root/'recipe.json',root,root/'out')

    def test_alias_conflict_unknown_tile_and_source_escape_leave_no_output(self):
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp); _,base=self.fixture(root)
            Image.new('L',(64,64),32).save(root/'other.png')
            for edits in ({'7':{'height':'height.png'},'19':{'height':'other.png'}},
                          {'99':{'height':'height.png'}},{'7':{'height':'../outside.png'}}):
                recipe=dict(base); recipe['tiles']=edits
                (root/'recipe.json').write_text(json.dumps(recipe))
                with self.assertRaises(ValueError):
                    surface.build(root/'capture.json',root/'normal.png',root/'recipe.json',root,root/'out')
                self.assertFalse((root/'out').exists())

    def test_16_bit_height_preserves_linear_scale_and_rgb_rejects(self):
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp)
            im=Image.new('I;16',(2,2)); im.putdata([0,32768,65535,32768]); im.save(root/'height.png')
            height,_=surface.read_height(root,'height.png',(2,2))
            self.assertAlmostEqual(height.getpixel((1,0)),32768/65535,places=6)
            self.assertEqual(height.getpixel((0,1)),1)
            Image.new('RGB',(2,2),'gray').save(root/'rgb.png')
            with self.assertRaises(ValueError): surface.read_height(root,'rgb.png',(2,2))

    def test_partial_overlap_declines_before_publication(self):
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp); capture,_=self.fixture(root)
            capture['tiles']['21']=[.25,0,.5,.5]
            (root/'capture.json').write_text(json.dumps(capture))
            with self.assertRaises(ValueError):
                surface.build(root/'capture.json',root/'normal.png',root/'recipe.json',root,root/'out')
            self.assertFalse((root/'out').exists())

    def test_normal_mips_stay_unit_vectors(self):
        normal=Image.new('RGBA',(8,8),(170,90,240,255))
        mip=surface.renormalize(normal.resize((4,4),Image.Resampling.BOX))
        for p in surface.samples(mip):
            length=math.sqrt(sum((v/127.5-1)**2 for v in p[:3]))
            self.assertAlmostEqual(length,1,delta=.01)

    def test_geometry_height_dds_is_signed_linear_with_zero_guard(self):
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp); self.fixture(root)
            # Non-neutral art makes the additional geometry resource observable.
            path,report=surface.build(root/'capture.json',root/'normal.png',root/'recipe.json',root,root/'out',geometry_height=True)
            self.assertTrue(report['geometryHeightGenerated'])
            self.assertFalse(report['heightGeometry'])  # no native integration claim
            manifest=json.loads((path.parent/'openshim_surface_height.json').read_text())
            self.assertEqual(manifest['heightEncoding'],'r32-float-meters')
            self.assertEqual(manifest['samplePolicy'],'bilinear-load-mip-zero')
            self.assertFalse(manifest['nativeIntegrationQualified'])
            data=(path.parent/manifest['heightAtlas']).read_bytes()
            header=struct.unpack('<31I',data[4:128])
            self.assertEqual(header[20],114)  # D3DFMT_R32F, not UNORM or sRGB
            self.assertEqual(header[6],0)
            heights=struct.unpack('<16384f',data[128:])
            self.assertGreater(heights[32*128+32],.3)
            self.assertAlmostEqual(manifest['maximumAbsoluteHeight'],max(abs(v) for v in heights),places=6)
            guard=manifest['zeroGuardPixels']
            for y in range(64):
                for x in range(64):
                    if min(x,y,63-x,63-y)<=guard:
                        self.assertEqual(heights[y*128+x],0)
            self.assertTrue(all(heights[y*128+x]==0 for y in range(128) for x in range(64,128)))

    def test_height_aliases_check_float_values_even_when_normals_quantize_equal(self):
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp); _,recipe=self.fixture(root)
            # Tiny amplitudes collapse to the same 8-bit normal but must not
            # silently alias different signed geometry data.
            recipe['tiles']={'7':{'height':'height.png','heightMeters':1e-8},
                             '19':{'height':'height.png','heightMeters':2e-8}}
            (root/'recipe.json').write_text(json.dumps(recipe))
            with self.assertRaises(ValueError):
                surface.build(root/'capture.json',root/'normal.png',root/'recipe.json',root,root/'out',geometry_height=True)
            self.assertFalse((root/'out').exists())


if __name__=='__main__': unittest.main()
