#!/usr/bin/env python3
"""Inventory released Redux backend seams without assigning unknown ABI semantics.

Outputs go under the ignored workshop directory. This reads the released GOG
image and its existing private Ghidra corpus; it does not run or patch a game,
import leaked-PDB layouts, or copy decompiler bodies into public source.
Requires the existing RE environment's pefile and capstone packages.
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import json
from pathlib import Path
import re
import struct

import capstone
import pefile

BASELINE_SHA256 = "8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413"
# Research labels for this exact image, not shipping patch sites.
TABLES = {"BZRNetLobby": (0x0089ADDC, 32), "BZRNetP2P": (0x0089BE78, 4)}
BOUNDARIES = {
    "network_readiness": 0x00764870,
    "platform_steam_readiness": 0x007647F0,
    "platform_galaxy_readiness": 0x00764810,
    "bzrnet_readiness": 0x00764840,
    "provider_initialization": 0x00764D80,
    "backend_construction": 0x00764F50,
    "lobby_accessor": 0x00764760,
    "lobby_constructor": 0x0074B3D0,
    "p2p_constructor": 0x0075A2B0,
    "peer_connect_selection": 0x0075EEA0,
    "peer_receive": 0x0075D800,
    "ui_multiplayer_click": 0x0078C6C0,
    "id_copy_used_by_lobby_get_my_id": 0x0073A740,
    "id_construct_kind_1": 0x0073A6E0,
    "id_construct_kind_2": 0x0073A710,
    "id_validity_low_byte": 0x0073A900,
    "id_format": 0x0073AAB0,
    "id_parse": 0x0073ABD0,
    "id_convert_kind_1": 0x0073A970,
    "id_convert_kind_2": 0x0073A9B0,
}


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--exe", type=Path, required=True)
    parser.add_argument("--corpus", type=Path, required=True)
    parser.add_argument("--output", type=Path, default=Path(__file__).resolve().parent /
                        "workshop/direct_lan_backend")
    args = parser.parse_args()
    digest = hashlib.sha256(args.exe.read_bytes()).hexdigest()
    if digest != BASELINE_SHA256:
        parser.error("Executable differs from the qualified static GOG 2.2.301 baseline")
    pe = pefile.PE(str(args.exe))
    image = pe.OPTIONAL_HEADER.ImageBase
    with (args.corpus / "inventory/functions.csv").open(encoding="utf-8", newline="") as f:
        functions = {int(row["entry_va"]): row for row in csv.DictReader(f)}
    files = {}
    for path in (args.corpus / "ghidrecomp/results/bins").glob("*/decomps/*.c"):
        match = re.search(r"-([0-9a-fA-F]{8})$", path.stem)
        if match:
            files[int(match[1], 16)] = path
    disassembler = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    def executable(address: int) -> bool:
        section = pe.get_section_by_rva(address - image)
        return bool(section and section.Characteristics & 0x20000000)

    def inspect(address: int) -> dict:
        row = functions.get(address)
        if not row or not executable(address):
            raise ValueError(f"Missing executable function boundary: {address:#010x}")
        end = int(row["body_max_va"])
        body = pe.get_data(address - image, end - address + 1)
        instructions = list(disassembler.disasm(body, address))
        path = files.get(address)
        source = path.read_text(encoding="utf-8", errors="replace") if path else ""
        return {
            "address": f"0x{address:08X}",
            "body_end": f"0x{end:08X}",
            "entry_bytes": body[:16].hex(" "),
            "disassembly_kind": "bounded linear sweep; trailing data can decode as instructions",
            "instructions": [f"0x{i.address:08X}: {i.mnemonic} {i.op_str}" for i in instructions],
            "returns": [{"address": f"0x{i.address:08X}", "operand": i.op_str}
                        for i in instructions if i.mnemonic == "ret"],
            "decomp_path": str(path.relative_to(args.corpus)) if path else None,
            "decomp_sha256": hashlib.sha256(path.read_bytes()).hexdigest() if path else None,
            "unqualified_signature_hint": row["signature"],
            "direct_call_addresses": sorted(set(re.findall(r"\bFUN_([0-9a-f]{8})\(", source))),
            "abi_status": "UNKNOWN until caller/register/sret/ownership qualification",
        }

    tables = {}
    for name, (address, expected) in TABLES.items():
        entries = []
        for slot in range(64):
            target = struct.unpack("<I", pe.get_data(address - image + slot * 4, 4))[0]
            if not executable(target):
                break
            entries.append({"slot": slot, "byte_offset": f"0x{slot * 4:02X}", **inspect(target)})
        if len(entries) != expected:
            raise ValueError(f"{name}: expected {expected} contiguous code pointers, got {len(entries)}")
        tables[name] = {"address": f"0x{address:08X}", "slots": entries}
    output = {
        "build": "Battlezone 98 Redux 2.2.301 GOG",
        "sha256": digest,
        "image_base": f"0x{image:08X}",
        "binary_path": str(args.exe.resolve()),
        "corpus_path": str(args.corpus.resolve()),
        "evidence_class": "static image/corpus inventory; not a runtime qualification",
        "vtable_pointer_evidence": "PROVEN for this exact image; method semantics remain individually qualified",
        "tables": tables,
        "boundaries": {name: inspect(address) for name, address in BOUNDARIES.items()},
    }
    args.output.mkdir(parents=True, exist_ok=True)
    (args.output / "backend_inventory.json").write_text(json.dumps(output, indent=2) + "\n", encoding="utf-8")
    print(f"Inventoried {sum(len(t['slots']) for t in tables.values())} vtable pointers and "
          f"{len(BOUNDARIES)} backend boundaries; inferred signatures remain unqualified")
    print(args.output / "backend_inventory.json")


if __name__ == "__main__":
    main()
