import importlib.util
from pathlib import Path
import unittest

spec = importlib.util.spec_from_file_location('layers', Path(__file__).resolve().parents[1] / 'tools/frame_bridge/Inspect-Scene-Layers.py')
layers = importlib.util.module_from_spec(spec)
spec.loader.exec_module(layers)


def draw(program, write=1, identity=False):
    return {'width': 1280, 'height': 720, 'targetDescription': {'width': 1280, 'height': 720, 'format': 28},
            'passObservation': {'material': 'test', 'fragmentProgram': program}, 'depthPolicy': {'enabled': True, 'writeMask': write},
            'blendPolicy': {'enabled': True}, 'policyCandidate': 'identity-overlay' if identity else 'blended',
            'precedingViewportDepthClears': 1, 'calls': 30}


class SceneLayers(unittest.TestCase):
    def test_material_blending_is_not_particle_opacity(self):
        self.assertEqual(layers.classify(draw('TerrainGlow_fragment')), 'depth-writing-material')
        self.assertEqual(layers.classify(draw('Sky_fragment', 0)), 'sky')
        self.assertEqual(layers.classify(draw('Effect_fragment', 0)), 'world-effect-candidate')
        self.assertEqual(layers.classify(draw('Effect_fragment', 0, True)), 'identity-overlay')
        self.assertEqual(layers.classify(draw('Glow_fs', 0, True)), 'compositor')
        self.assertEqual(layers.classify(draw(None, 0)), 'unknown')

    def test_interleaved_effect_rejects_early_opaque_snapshot(self):
        summary = {'boundedTraceClean': True, 'completion': {'stringLayoutChecked': True},
                   'drawGroups': [draw('Effect_fragment', 0), draw('TerrainGlow_fragment'), draw('UI_fragment', 0, True)],
                   'orderedDraws': [{'frame': 1, 'thread': 1, 'ordinal': i + 1, 'group': i, 'width': 1280, 'height': 720} for i in range(3)]}
        result = layers.analyze(summary)
        self.assertTrue(result['worldEffectsInterleavedWithDepthWriters'])
        self.assertFalse(result['firstBlendedDrawIsSafeOpaqueBoundary'])
        self.assertFalse(result['opacityMaskQualified'])
        self.assertEqual(result['observedFrames'][0]['laterDepthWritingDraws'], 1)
        summary['completion']['stringLayoutChecked'] = False
        with self.assertRaises(ValueError):
            layers.analyze(summary)


if __name__ == '__main__':
    unittest.main()
