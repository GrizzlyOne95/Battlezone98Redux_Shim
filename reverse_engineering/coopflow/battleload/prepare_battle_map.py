"""Stage the authored lcbench terrain as a private four-player network map.

The default stages nbattle (battle load). --map mpbugs stages the stock
multiplayer bug pack instead: same terrain and spawns, its own mission script.
"""
import argparse
import re
import shutil
from pathlib import Path

MAPS = {
    "nbattle": ("A Network Battle Load",
                "Private four-player network test: two AI armies, native combat, destruction and scrap."),
    # Sorts above "A Network Battle Load" in the lobby's map list.
    "mpbugs": ("A Multiplayer Bug Pack",
               "Private network test: stock multiplayer bug reproductions (mission end, host leave, weapons)."),
}


def prepare(output: Path, map_name: str = "nbattle") -> None:
    title, description = MAPS[map_name]
    here = Path(__file__).resolve().parent
    fixture = here.parents[1] / "test_missions" / "live_combat_scaling"
    output.mkdir(parents=True, exist_ok=True)
    # Reuse existing authored terrain unchanged; no retail terrain extraction.
    for name in ("lcbench.trn", "lcbench.hg2", "lcbench.mat", "lcbench.lgt",
                 "earthgood.dds", "earthgood.material"):
        shutil.copyfile(fixture / name, output / name.replace("lcbench.", map_name + "."))
    source = (fixture / "lcbench.bzn").read_text()
    header, rest = source.split("[GameObject]", 1)
    player, tail = rest.split("name = LuaMission", 1)
    header = header.replace("lcbench.bzn", map_name + ".bzn")
    header = header.replace("TerrainName = lcbench", "TerrainName = " + map_name)
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
        # Preserve the authored spawn powerup's state, including the native
        # zero-mass inverse sentinel. It is already a spawn, not a craft.
        buoy = re.sub(r"(perceivedTeam \[1\] =\s*)1\b", rf"\g<1>{team}", buoy)
        blocks.append(buoy)
    bzn = header + "".join("[GameObject]" + b for b in blocks)
    # Strategy multiplayer must construct the native multiplayer mission class
    # to initialize its spawn powerup registry before network startup sync.
    bzn += "name = MultSTMission" + tail.replace("00000002", "00000006")
    (output / (map_name + ".bzn")).write_text(bzn, encoding="ascii")
    (output / (map_name + ".ini")).write_text(
        f'[DESCRIPTION]\nmissionName = "{title}"\n'
        '[WORKSHOP]\nmapType = "multiplayer"\ncustomtags = "Coop,Testing"\n'
        '[MULTIPLAYER]\nminPlayers = "2"\nmaxPlayers = "4"\ngameType = "S"\n', encoding="ascii")
    (output / (map_name + ".vxt")).write_text("asuser aspilo.des\tanims\\aspil.avi NSDF Pilot\n", encoding="ascii")
    (output / (map_name + ".des")).write_text(description + "\n", encoding="ascii")
    shutil.copyfile(here / (map_name + ".lua"), output / (map_name + ".lua"))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--map", choices=sorted(MAPS), default="nbattle")
    arguments = parser.parse_args()
    prepare(arguments.output, arguments.map)
