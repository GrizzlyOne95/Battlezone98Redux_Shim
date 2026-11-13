#!/usr/bin/env python3
"""Audit OpenShim vtable-slot hooks for unhooked copies of the same function.

For each hooked function this finds every 4-byte copy of its address in the
exe's read-only data, decides whether the copy is a slot in an MSVC vtable
(RTTI class name, vtable VA, slot index), and marks whether OpenShim hooks that
slot. Reads the exe at runtime only; nothing from it is stored.

Run:  python -I scripts/audit_vtable_hooks.py [exe]
Hook table: HOOKS below. Function and vtable addresses come from
scripts/patches.json (engine_addresses + the fallback of each "VTable Hook"
patch row); only slot indexes live here.
"""
import json
import struct
import sys
from pathlib import Path

DEFAULT_EXE = r"C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\battlezone98redux.exe"
PATCHES = Path(__file__).with_name("patches.json")

# Hooked-slot specs: ("patch", row) = fallback address of a DWORD patch row;
# ("vt", vtable row, index) = vtable row address + 4 * index.
# fn is an engine_addresses name, or ("slot", vtable row, index) when the
# original is whatever the stock slot holds. An optional 4th item is the
# reason the hook is meant to cover only some copies; those are not counted.
def P(name):
    return ("patch", name)


def VT(row, idx):
    return ("vt", row, idx)


# Classes whose slot 38 is the inherited HoverCraft::UpdateWeaponAim.
HOVERCRAFT = ["Wingman", "HoverCraft", "APC", "Minelayer", "SAV", "Scavenger", "Tug",
              "Armory", "Producer", "Recycler", "Factory", "ConstructionRig"]
AI = ["Artillery", "Bomber", "Gech", "Offensive", "Person", "RocketTank", "Scout", "Soldier", "Tank", "Wingman"]
AI_SUB = ["RocketTank", "Scout", "Person", "Soldier", "Artillery", "Gech", "Bomber", "Tank"]
PRODUCERS = ["Producer", "Recycler", "Factory"]

HOOKS = [
    ("EngineFlameControl", "EngineFlameControl", [P("Engine Flame Control VTable Hook")]),
    ("EngineFlameSubmit", "EngineFlameSubmit", [P("Engine Flame Submit VTable Hook")]),
    ("ChunkEffectSimulate", "ChunkEffectSimulate", [P("Chunk Effect Simulate VTable Hook")]),
    ("LegacyWorldUpdateRenderQueue", "LegacyWorldUpdateRenderQueue",
     [P("Legacy World Update RenderQueue VTable Hook"), VT("DynamicGeometryVtable", 32)]),
    ("ProducerUpdateModeList", "ProducerUpdateModeList", [P(f"{c} UpdateModeList VTable Hook") for c in PRODUCERS]),
    ("ProducerSetActiveMode", "ProducerSetActiveMode", [P(f"{c} SetActiveMode VTable Hook") for c in PRODUCERS]),
    ("GameObjectDeselect (shared empty fn)", "GameObjectDeselect", [P(f"{c} Deselect VTable Hook") for c in PRODUCERS],
     "only the producer classes replace the shared empty Deselect"),
    ("ConstructionRigUpdateModeList", "ConstructionRigUpdateModeList", [P("ConstructionRig UpdateModeList VTable Hook")]),
    ("ConstructionRigSetActiveMode", "ConstructionRigSetActiveMode", [P("ConstructionRig SetActiveMode VTable Hook")]),
    ("ConstructionRigDeselect", "ConstructionRigDeselect", [P("ConstructionRig Deselect VTable Hook")]),
    ("ControlPanelPostLoad", "ControlPanelPostLoad", [P("ControlPanel PostLoad VTable Hook")]),
    ("ControlPanelCleanup", "ControlPanelCleanup", [P("ControlPanel Cleanup VTable Hook")]),
    ("WingmanUpdateWeaponAim", "WingmanUpdateWeaponAim", [VT(f"{c}Vtable", 38) for c in HOVERCRAFT]),
    ("TurretCraftUpdateWeaponAim", "TurretCraftUpdateWeaponAim", [VT("TurretCraftVtable", 38)]),
    ("TurretTankUpdateWeaponAim", "TurretTankUpdateWeaponAim", [VT("HowitzerVtable", 38), VT("TurretTankVtable", 38)]),
    ("ShieldTowerSimulate", "ShieldTowerSimulate", [VT("ShieldTowerVtable", 15)]),
    ("MagnetMineSimulate", "MagnetMineSimulate", [VT("MagnetMineVtable", 15)]),
    ("ProximityMineSimulate", "ProximityMineSimulate", [VT("ProximityMineVtable", 15)]),
    ("SprayBuildingSimulate", "SprayBuildingSimulate", [VT("SprayBuildingVtable", 15)]),
    ("TugPostLoad", "TugPostLoad", [VT("TugVtable", 22)]),
    ("FlagDisplaySubmit", "FlagDisplaySubmit", [VT("FlagDisplayVtable", 8)]),
    ("MultiCreateUpdate", ("slot", "MultiplayerCreateVtable", 13), [VT("MultiplayerCreateVtable", 13)]),
    ("OffensiveProcessDoSubTask", "OffensiveProcessDoSubTask",
     [VT(f"{c}ProcessVtable", 11) for c in AI] +
     [VT(f"{c}{s}Vtable", 11) for c in AI_SUB for s in ("Friend", "Enemy")]),
    ("GunTowerProcessDoSubTask", "GunTowerProcessDoSubTask",
     [VT(f"GunTower{s}Vtable", 11) for s in ("Process", "Friend", "Enemy")]),
    ("DefendTaskDoState", "DefendTaskDoState", [VT("DefendTaskVtable", 12)]),
    ("SitTaskDoState", "SitTaskDoState", [VT("SitTaskVtable", 12)]),
    ("TurretTankProcessDoSubTask", "TurretTankProcessDoSubTask",
     [VT(f"TurretTank{s}Vtable", 11) for s in ("Process", "Friend", "Enemy")]),
    ("TurretTankGetCommand", "TurretTankGetCommand", [VT("TurretTankVtable", 13)]),
    ("TurretTankUpdateModeList", "TurretTankUpdateModeList", [VT("TurretTankVtable", 23)]),
    ("TurretTankProcessInitAttack", "TurretTankProcessInitAttack",
     [VT(f"TurretTank{s}Vtable", 24) for s in ("Process", "Friend", "Enemy")]),
    ("ProducerFinishBuild", "ProducerFinishBuild",
     [VT("RecyclerVtable", 42), VT("FactoryVtable", 42)],
     "ProducerRallyPoints covers Recycler and Factory only; the Producer base and ConstructionRig copies stay stock"),
    ("TurretTankProcessDoAttack", "TurretTankProcessDoAttack",
     [VT(f"TurretTank{s}Vtable", 26) for s in ("Process", "Friend", "Enemy")],
     "shared AiProcess DoAttack; TurretAttackOrders manages turret deploy only"),
]


class Pe:
    def __init__(self, path):
        self.data = Path(path).read_bytes()
        d = self.data
        pe = struct.unpack_from("<I", d, 0x3C)[0]
        nsec = struct.unpack_from("<H", d, pe + 6)[0]
        opt = struct.unpack_from("<H", d, pe + 20)[0]
        self.base = struct.unpack_from("<I", d, pe + 24 + 28)[0]
        self.secs = []  # (va, vsize, raw, rawsize, flags)
        off = pe + 24 + opt
        for i in range(nsec):
            vs, va, rs, ro = struct.unpack_from("<IIII", d, off + 8)
            fl = struct.unpack_from("<I", d, off + 36)[0]
            self.secs.append((self.base + va, vs, ro, rs, fl))
            off += 40

    def sec(self, va):
        for s in self.secs:
            if s[0] <= va < s[0] + max(s[1], s[3]):
                return s
        return None

    def is_code(self, va):
        s = self.sec(va)
        return bool(s and s[4] & 0x20000000)

    def u32(self, va):
        s = self.sec(va)
        if not s or va - s[0] + 4 > s[3]:
            return None
        return struct.unpack_from("<I", self.data, s[2] + va - s[0])[0]

    def cstr(self, va, n=96):
        s = self.sec(va)
        if not s:
            return ""
        o = s[2] + va - s[0]
        return self.data[o:o + n].split(b"\0")[0].decode("latin1")

    def find(self, value):
        pat = struct.pack("<I", value)
        for va, vs, ro, rs, fl in self.secs:
            if fl & 0x20000000 or not rs:  # skip code and empty sections
                continue
            o = ro
            end = ro + rs
            while True:
                o = self.data.find(pat, o, end)
                if o < 0:
                    break
                yield va + (o - ro)
                o += 1

    def vtable_of(self, hit):
        """Walk back over code pointers to the vtable start; return
        (class name, vtable VA, slot index, COL offset) or None."""
        start = hit
        while self.u32(start - 4) is not None and self.is_code(self.u32(start - 4)) and hit - start < 0x800:
            start -= 4
        col = self.u32(start - 4)
        if not col or self.u32(col) != 0:
            return None
        td = self.u32(col + 12)
        name = self.cstr(td + 8) if td else ""
        if not name.startswith(".?A"):
            return None
        return name, start, (hit - start) // 4, self.u32(col + 4)


def main():
    exe = sys.argv[1] if len(sys.argv) > 1 else DEFAULT_EXE
    cfg = json.loads(PATCHES.read_text(encoding="utf-8"))
    rows = {e["name"]: int(e["address"], 16) for e in cfg["engine_addresses"]}
    fallback = {p["name"]: int(p["fallback"], 16) for p in cfg["patches"] + cfg["resolves"] + cfg["globals"] if p.get("fallback")}
    def slot_va(spec):
        if spec[0] == "patch":
            return fallback.get(spec[1])
        return rows[spec[1]] + 4 * spec[2] if spec[1] in rows else None

    unresolved = [(label, s) for label, fn, specs, *_ in HOOKS for s in specs if slot_va(s) is None]
    unresolved += [(label, fn) for label, fn, *_ in HOOKS
                   if (fn[1] if isinstance(fn, tuple) else fn) not in rows]
    for label, what in unresolved:
        print(f"UNRESOLVED {label}: {what} is not in patches.json")
    if unresolved:
        return 1
    if not Path(exe).is_file():
        print(f"SKIP: no exe at {exe}; patches.json rows resolve, slot scan not run")
        return 77
    pe = Pe(exe)

    print(f"exe={exe} base=0x{pe.base:08X} hooks={len(HOOKS)}")
    total = 0
    for label, fn, specs, *partial in HOOKS:
        va = pe.u32(rows[fn[1]] + 4 * fn[2]) if isinstance(fn, tuple) else rows.get(fn)
        hooked = {slot_va(s) for s in specs} - {None}
        missing = [s for s in specs if slot_va(s) is None]
        print(f"\n# {label} fn=0x{va:08X} hooked_slots={len(hooked)}" + (f" UNRESOLVED={missing}" if missing else ""))
        hits = [(h, pe.vtable_of(h)) for h in pe.find(va)]
        # The same function in a different slot is a different virtual (e.g.
        # the shared empty Deselect); only the hooked slot index matters.
        want = {i[2] for h, i in hits if i and h in hooked}
        unhooked = other = 0
        for hit, info in hits:
            if not info:
                print(f"  NOT-VTABLE hit=0x{hit:08X}")
                continue
            name, vt, idx, coff = info
            if idx not in want:
                other += 1
                continue
            mark = "HOOKED  " if hit in hooked else "UNHOOKED"
            unhooked += hit not in hooked
            print(f"  {mark} {name[4:-2]:<28} vtable=0x{vt:08X} slot={idx} (+0x{idx * 4:02X}){f' col_off={coff}' if coff else ''}")
        for h in hooked:
            if not any(h == x for x, _ in hits):
                print(f"  NOTE hooked slot 0x{h:08X} does not hold fn (wrong slot/row?)")
        if other:
            print(f"  (+{other} copies of the fn in other slot indexes; different virtuals, ignored)")
        if partial:
            print(f"  -> unhooked copies: {unhooked} (expected: {partial[0]})")
        else:
            print(f"  -> unhooked copies: {unhooked}")
            total += unhooked
    print(f"\nunexpected unhooked copies: {total}")
    return 1 if total else 0


if __name__ == "__main__":
    sys.exit(main())
