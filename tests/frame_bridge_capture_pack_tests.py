"""Replay must retain the matched camera's float precision and image orientation."""
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import unittest

from PIL import Image

TOOL = Path(__file__).resolve().parents[1] / 'tools/frame_bridge/Prepare-RT-Capture.py'


class CapturePackTests(unittest.TestCase):
    def test_precision_scene_and_camera_identity(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            width, height = 3, 3
            # Deliberately distinct six-digit scene / nine-digit depth floats.
            exact = struct.unpack('<f', struct.pack('<f', 1.000071168))[0]
            camera = {'cameraIdentity': 31, 'observationQpc': 900,
                      'stage': 1, 'clearOrdinal': 3, 'width': width, 'height': height,
                      'valid': True, 'matrixSource': 'camera-for-shaders',
                      'projection': [exact]*16, 'view': [exact]*16,
                      'nearClip': .08, 'farClip': 1125}
            scene_camera = dict(camera, projection=[1.00007]*16, view=[1.00007]*16)
            scene = {'frameId': 50, 'stage': 1, 'width': width, 'height': height,
                     'cameraObservation': scene_camera}
            depth = {'frameId': 50, 'cameraObservation': camera}
            (root/'game-scene.bmp.json').write_text(json.dumps(scene))
            (root/'game-depth.pfm.json').write_text(json.dumps(depth))
            Image.new('RGB', (width, height), (20, 30, 40)).save(root/'game-scene.bmp')
            Image.new('RGB', (width, height), (100, 110, 120)).save(root/'game-frame.bmp')
            (root/'game-depth.pfm').write_bytes(b'Pf\n3 3\n-1.0\n'+struct.pack('<9f', *range(9)))
            for scene_only in (False, True):
                result = subprocess.run([sys.executable, str(TOOL), str(root)]+(['--scene-only'] if scene_only else []), capture_output=True)
                self.assertEqual(result.returncode, 0, result.stderr)
                payload = (root/('rt-scene-input.bin' if scene_only else 'rt-capture-input.bin')).read_bytes()
                self.assertEqual(payload[:8], b'BZRCAP1\0')
                self.assertEqual(struct.unpack_from('<f', payload, 16)[0], exact)
                self.assertEqual(struct.unpack_from('<9f', payload, 16+34*4), (6,7,8,3,4,5,0,1,2))
                self.assertEqual(payload[-width*height*4:], bytes((20,30,40,255) if scene_only else (100,110,120,255))*9)
            depth['cameraObservation']['observationQpc'] = 901
            (root/'game-depth.pfm.json').write_text(json.dumps(depth))
            result = subprocess.run([sys.executable, str(TOOL), str(root)], capture_output=True)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn(b'Camera observation differs', result.stderr)


if __name__ == '__main__':
    unittest.main()
