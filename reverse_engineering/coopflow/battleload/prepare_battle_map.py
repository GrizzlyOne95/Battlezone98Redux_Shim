"""Stage the authored lcbench terrain as a private four-player combat map."""
import argparse
import re
import shutil
from pathlib import Path


def prepare(output: Path) -> None:
    here = Path(__file__).resolve().parent
    fixture = here.parents[1] / "test_missions" / "live_combat_scaling"
    output.mkdir(parents=True, exist_ok=True)
    # Reuse existing authored terrain unchanged; no retail terrain extraction.
    for name in ("lcbench.trn", "lcbench.hg2", "lcbench.mat", "lcbench.lgt",
                 "earthgood.dds", "earthgood.material"):
        shutil.copyfile(fixture / name, output / name.replace("lcbench.", "nbattle."))
    source = (fixture / "lcbench.bzn").read_text()
    header, rest = source.split("[GameObject]", 1)
    player, tail = rest.split("name = LuaMission", 1)
    header = header.replace("lcbench.bzn", "nbattle.bzn")
    header = header.replace("TerrainName = lcbench", "TerrainName = nbattle")
    header = re.sub(r"seq_count \[1\] =\s*2", "seq_count [1] =\n6", header)
    header = re.sub(r"size \[1\] =\s*1", "size [1] =\n5", header)
    blocks = [player]
    spawn = (here / "spawn_template.bzn.txt").read_text()
    for team in range(1, 5):
        buoy = spawn.replace("label = coop_spawn1", f"label = battle_spawn{team}")
        buoy = re.sub(r"(seqno? \[1\] =\s*)\d+", rf"\g<1>{team + 1}", buoy, flags=re.I)
        buoy = re.sub(r"(team \[1\] =\s*)\d+", rf"\g<1>{team}", buoy)
        buoy = re.sub(r"obj_addr = \w+", f"obj_addr = {team + 1:08x}", buoy)
        # Keep all four observer positions nearby and outside the combat arena.
        position = ("pos [1] =\n  x [1] =\n" + str(2490 + team * 35)
                    + "\n  y [1] =\n1\n  z [1] =\n2560")
        buoy = re.sub(r"(?m)^pos \[1\] =\n  x \[1\] =\n[^\n]+\n  y \[1\] =\n[^\n]+\n  z \[1\] =\n[^\n]+", position, buoy)
        fields = {"posit_x": 2490 + team * 35, "posit_y": 1, "posit_z": 2560,
                  "right_x": 1, "right_y": 0, "right_z": 0,
                  "up_x": 0, "up_y": 1, "up_z": 0,
                  "front_x": 0, "front_y": 0, "front_z": 1}
        for field, value in fields.items():
            buoy = re.sub(rf"(?m)^([ \t]*{field} \[1\] =\n)[^\n]+", rf"\g<1>{value}", buoy)
        # A start marker is not a craft; don't carry serialized player state.
        for field in ("healthRatio", "curHealth", "maxHealth", "ammoRatio", "curAmmo", "maxAmmo", "mass", "mass_inv", "k_i"):
            buoy = re.sub(rf"({field} \[1\] =\s*)[-\d.e+]+", r"\g<1>0", buoy)
        buoy = buoy.replace("aiProcess [1] =\ntrue", "aiProcess [1] =\nfalse")
        buoy = buoy.replace("curPilot [1] =\nasuser", "curPilot [1] =\n")
        buoy = re.sub(r"(perceivedTeam \[1\] =\s*)1\b", rf"\g<1>{team}", buoy)
        blocks.append(buoy)
    bzn = header + "".join("[GameObject]" + b for b in blocks)
    bzn += "name = LuaMission" + tail.replace("00000002", "00000006")
    (output / "nbattle.bzn").write_text(bzn, encoding="ascii")
    (output / "nbattle.ini").write_text(
        '[DESCRIPTION]\nmissionName = "A Network Battle Load"\n'
        '[WORKSHOP]\nmapType = "multiplayer"\ncustomtags = "Coop,Testing"\n'
        '[MULTIPLAYER]\nminPlayers = "2"\nmaxPlayers = "4"\ngameType = "S"\n', encoding="ascii")
    (output / "nbattle.vxt").write_text("asuser aspilo.des\tanims\\aspil.avi NSDF Pilot\n", encoding="ascii")
    (output / "nbattle.des").write_text(
        "Private four-player network test: two AI armies, native combat, destruction and scrap.\n", encoding="ascii")
    shutil.copyfile(here / "nbattle.lua", output / "nbattle.lua")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, required=True)
    prepare(parser.parse_args().output)
