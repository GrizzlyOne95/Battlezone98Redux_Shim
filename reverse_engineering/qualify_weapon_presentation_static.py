"""Reproduce static qualification; never represents a live-runtime capture.

Requires pefile/capstone and the private stock GOG executable. Reports belong
with private RE evidence, not in this public checkout. No binary is downloaded.
"""
from pathlib import Path
import argparse
import hashlib
import json

import capstone
import pefile


def qualify(executable, catalog):
    data = executable.read_bytes()
    digest = hashlib.sha256(data).hexdigest()
    if digest != "8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413":
        raise ValueError("Not the qualified stock GOG executable")
    pe = pefile.PE(data=data)
    if pe.FILE_HEADER.Machine != 0x14C or pe.OPTIONAL_HEADER.ImageBase != 0x400000:
        raise ValueError("Unexpected PE architecture/base")
    rows = [r for r in json.loads(catalog.read_text())["resolves"]
            if r["name"].startswith("WeaponPresentation::")]
    if len(rows) != 14:
        raise ValueError("Native qualification catalog is incomplete")
    image = pe.get_memory_mapped_image()
    sites = {}
    for row in rows:
        pattern = bytes.fromhex(row["pattern"])
        hits = []
        cursor = 0
        while True:
            cursor = image.find(pattern, cursor)
            if cursor < 0:
                break
            hits.append(cursor)
            cursor += 1
        if len(hits) != 1 or not row["require_unique"]:
            raise ValueError(f"{row['name']}: non-unique or ungated pattern")
        address = pe.OPTIONAL_HEADER.ImageBase + hits[0] + row["offset"]
        if address != int(row["fallback"], 0):
            raise ValueError(f"{row['name']}: signature/fallback disagreement")
        sites[row["name"].split("::")[1]] = address

    call_targets = {}
    for name, target in [("CannonShotCall", "OrdnanceFactory"),
                         ("WeaponClassPopCall", "PopScope"),
                         ("CraftClassPopCall", "PopScope")]:
        va = sites[name]
        code = pe.get_data(va - pe.OPTIONAL_HEADER.ImageBase, 5)
        if code[0] != 0xE8:
            raise ValueError(f"{name}: not CALL rel32")
        destination = va + 5 + int.from_bytes(code[1:], "little", signed=True)
        if destination != sites[target]:
            raise ValueError(f"{name}: wrong native callee")
        call_targets[name] = {"site": hex(va), "bytes": code.hex(" "), "target": hex(destination)}

    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    steals = {}
    for name, size in [("WeaponCtor", 9), ("WeaponDtor", 6), ("SimulationPass", 6),
                       ("SetWeapon", 7), ("ModelPose", 6)]:
        va = sites[name]
        code = pe.get_data(va - pe.OPTIONAL_HEADER.ImageBase, size)
        instructions = list(decoder.disasm(code, va))
        if sum(i.size for i in instructions) != size:
            raise ValueError(f"{name}: steal splits an instruction")
        if any(i.mnemonic.startswith(("call", "j", "ret")) for i in instructions):
            raise ValueError(f"{name}: steal needs relocation")
        steals[name] = {"site": hex(va), "size": size, "bytes": code.hex(" "),
                        "instructions": [f"{i.mnemonic} {i.op_str}" for i in instructions]}

    returns = {}
    for name, expected in [("WeaponCtor", 8), ("WeaponDtor", 0), ("SimulationPass", 0),
                           ("SetWeapon", 8), ("ModelPose", 0), ("RawGet", 8),
                           ("PopScope", 0), ("OrdnanceFactory", 8), ("RenderFind", 0),
                           ("RenderUpdate", 4), ("RenderDetach", 8)]:
        va = sites[name]
        for instruction in decoder.disasm(pe.get_data(va - pe.OPTIONAL_HEADER.ImageBase, 4096), va):
            if instruction.mnemonic == "ret":
                popped = int(instruction.op_str, 0) if instruction.op_str else 0
                if popped != expected:
                    raise ValueError(f"{name}: wrong callee stack cleanup")
                returns[name] = {"site": hex(instruction.address), "popped_bytes": popped}
                break
        else:
            raise ValueError(f"{name}: no bounded return found")
    return {"evidence_kind": "static_only", "sha256": digest, "size": len(data),
            "image_base": hex(pe.OPTIONAL_HEADER.ImageBase),
            "coff_timestamp": pe.FILE_HEADER.TimeDateStamp,
            "sites": {k: hex(v) for k, v in sites.items()}, "call_targets": call_targets,
            "steals": steals, "returns": returns,
            "live_pid": None, "activation_qualified": False}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--catalog", type=Path,
                        default=Path(__file__).resolve().parents[1] / "scripts/patches.json")
    parser.add_argument("--report", type=Path, required=True,
                        help="Output in private evidence storage; includes instruction bytes")
    args = parser.parse_args()
    report = qualify(args.executable, args.catalog)
    args.report.parent.mkdir(parents=True, exist_ok=True)
    args.report.write_text(json.dumps(report, indent=2) + "\n")
    print(f"Static qualification passed: {len(report['sites'])} resolves, "
          f"{len(report['call_targets'])} calls, {len(report['steals'])} steals; live qualification pending")
