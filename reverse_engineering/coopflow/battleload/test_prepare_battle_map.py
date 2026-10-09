import re
import tempfile
import unittest
from pathlib import Path
from prepare_battle_map import prepare


class MapFixture(unittest.TestCase):
    def test_native_markers_preserve_basis_and_velocity(self):
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary)
            prepare(output)
            text = (output / "nbattle.bzn").read_text()
            blocks = text.split("[GameObject]")[1:]
            self.assertEqual(len(blocks), 5)
            self.assertIn("TerrainName = nbattle", text)
            self.assertIn("sObject = 00000006", text)
            for team, block in enumerate(blocks[1:], 1):
                value = lambda name: float(re.search(rf"(?m)^\s*{name} \[1\] =\n([^\n]+)", block)[1])
                self.assertEqual(value("seqno"), team + 1)
                self.assertEqual(value("team"), team)
                self.assertEqual(value("perceivedTeam"), team)
                for prefix, basis in (("right", (1,0,0)), ("up", (0,1,0)), ("front", (0,0,1))):
                    self.assertEqual(tuple(value(prefix + "_" + axis) for axis in "xyz"), basis)
                self.assertEqual(value("posit_x"), 2490 + team * 35)
                self.assertEqual(value("posit_z"), 2560)
                self.assertIn("aiProcess [1] =\nfalse", block)
                self.assertNotIn("asuser", block)
                for vector in ("v", "omega", "Accel"):
                    section = re.search(rf"(?m)^ {vector} \[1\] =\n  x \[1\] =\n([^\n]+)\n  y \[1\] =\n([^\n]+)\n  z \[1\] =\n([^\n]+)", block)
                    self.assertEqual([float(v) for v in section.groups()], [0,0,0])
            fixture = Path(__file__).resolve().parents[2] / "test_missions" / "live_combat_scaling"
            for extension in ("trn","hg2","mat","lgt"):
                self.assertEqual((fixture / ("lcbench." + extension)).read_bytes(), (output / ("nbattle." + extension)).read_bytes())


if __name__ == "__main__":
    unittest.main()
