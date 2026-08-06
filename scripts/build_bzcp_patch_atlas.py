from __future__ import annotations

import argparse
import json
import os
import shutil
import struct
import tempfile
import warnings
from collections import Counter, defaultdict
from pathlib import Path
from typing import Any

import pyghidra

from extract_bzcp_catalog import (
    BinaryView,
    PatchWrite,
    collect_patch_names,
    collect_patch_writes,
    disassemble_worker,
    load_slot_map,
    payload_desc,
)


OPEN_SHIM_STATUS = {
    0x0079B85F: (
        "implemented",
        "Clean-room shim models this as Hop-Fix 1/3.",
    ),
    0x00799279: (
        "implemented",
        "Clean-room shim models this as Hop-Fix 2/3.",
    ),
    0x00799377: (
        "implemented",
        "Clean-room shim models this as Hop-Fix 3/3.",
    ),
    0x007680D6: (
        "probe_only",
        "Clean-room shim treats this original patch site as a probe-only refresh hook.",
    ),
    0x00799116: (
        "probe_only",
        "Clean-room shim treats this original patch site as a probe-only refresh hook.",
    ),
    0x0062480B: (
        "deferred",
        "Clean-room shim now leaves this original /help and /ban command intercept disabled until the detour is reimplemented clean-room.",
    ),
    0x007AA5A1: (
        "implemented",
        "Clean-room shim now applies this byte patch under the original vehicle-fix semantics.",
    ),
    0x0078DD4E: (
        "implemented",
        "Clean-room shim now patches this real version-string operand site with its own OpenShim tag.",
    ),
    0x00618C2F: (
        "implemented",
        "Clean-room shim now patches this real version-string operand site with its own OpenShim tag.",
    ),
}

DLL_ADDRESS_NOTES = {
    0x1000CAF0: "save selection helper",
    0x1000CB40: "restore selection helper",
    0x1000CCA0: "restore scroll helper",
    0x1000CD10: "Hop-Fix 1 trampoline",
    0x1000CD40: "Hop-Fix 2 trampoline",
    0x1000CD60: "Hop-Fix 3 trampoline",
}


def classify_category(name: str) -> str:
    if name.startswith(("Map Sorting", "Map Filters", "Map List", "Map Filter UI", "Map Icon Hook", "Map list icon", "Lobby map name")):
        return "Map UI / filters / hop-fix"
    if name.startswith(("Version Notice", "CLI Fix")):
        return "Version / CLI constants"
    if name.startswith("Vehicle List"):
        return "Vehicle list / mod assets"
    if name.startswith(("BZCP BZRNET", "Custom Command", "Ban Button", "Joiner Event Hook")):
        return "Lobby / network / commands"
    if name.startswith("Ogre Resource Loader"):
        return "Ogre / resources"
    return "Other"


def format_hex(value: int | None, width: int = 8) -> str | None:
    if value is None:
        return None
    return f"0x{value:0{width}X}"


def compute_patch_bytes(patch: PatchWrite, instruction_address: int | None, instruction_length: int | None) -> bytes | None:
    if patch.kind == "jmp5" and patch.payload_value is not None:
        rel = patch.payload_value - (patch.dest_va + 5)
        return b"\xE9" + struct.pack("<i", rel)
    if patch.kind == "rel32" and patch.payload_value is not None:
        if instruction_address is None or instruction_length is None:
            return None
        rel = patch.payload_value - (instruction_address + instruction_length)
        return struct.pack("<i", rel)
    if patch.kind == "u32" and patch.payload_value is not None:
        return struct.pack("<I", patch.payload_value)
    if patch.kind == "u8" and patch.payload_value is not None:
        return bytes((patch.payload_value & 0xFF,))
    return None


def summarize_stub(instructions: list[dict[str, Any]]) -> str:
    if not instructions:
        return ""
    parts = [item["text"] for item in instructions[:3]]
    return "; ".join(parts)


def capture_instruction_block(listing: Any, inst: Any, count: int = 6) -> list[dict[str, Any]]:
    out: list[dict[str, Any]] = []
    cur = inst
    for _ in range(count):
        if cur is None:
            break
        out.append(
            {
                "address": str(cur.getAddress()),
                "text": str(cur),
                "bytes": bytes(cur.getBytes()).hex(),
                "length": int(cur.getLength()),
            }
        )
        cur = cur.getNext()
    return out


def analyze_exe_sites(exe_path: Path, patches: list[PatchWrite], ghidra_install: Path | None) -> dict[int, dict[str, Any]]:
    project_dir = Path(tempfile.gettempdir()) / "bzr_bzcp_patch_atlas_exe"
    if project_dir.exists():
        shutil.rmtree(project_dir)

    result: dict[int, dict[str, Any]] = {}
    with pyghidra.open_program(
        exe_path,
        project_location=project_dir,
        project_name="bzr_bzcp_patch_atlas_exe",
        analyze=True,
        nested_project_location=True,
    ) as api:
        program = api.getCurrentProgram()
        listing = program.getListing()
        fm = program.getFunctionManager()
        for patch in patches:
            addr = api.toAddr(format_hex(patch.dest_va))
            inst = listing.getInstructionContaining(addr)
            func = fm.getFunctionContaining(addr)
            info: dict[str, Any] = {
                "function": None,
                "instruction": None,
            }
            if func is not None:
                info["function"] = {
                    "entry": str(func.getEntryPoint()),
                    "name": str(func.getName()),
                    "signature": str(func.getSignature()),
                }
            if inst is not None:
                inst_address = int(str(inst.getAddress()), 16)
                inst_length = int(inst.getLength())
                field_offset = patch.dest_va - inst_address
                info["instruction"] = {
                    "address": str(inst.getAddress()),
                    "text": str(inst),
                    "bytes": bytes(inst.getBytes()).hex(),
                    "length": inst_length,
                    "field_offset": field_offset,
                    "preview": capture_instruction_block(listing, inst, count=4),
                }
                patch_bytes = compute_patch_bytes(patch, inst_address, inst_length)
                info["patch_bytes"] = patch_bytes.hex() if patch_bytes is not None else None
            else:
                info["patch_bytes"] = None
            result[patch.dest_va] = info
    shutil.rmtree(project_dir, ignore_errors=True)
    return result


def analyze_dll_stubs(dll_path: Path, target_addrs: set[int]) -> dict[int, dict[str, Any]]:
    project_dir = Path(tempfile.gettempdir()) / "bzr_bzcp_patch_atlas_dll"
    if project_dir.exists():
        shutil.rmtree(project_dir)

    result: dict[int, dict[str, Any]] = {}
    with pyghidra.open_program(
        dll_path,
        project_location=project_dir,
        project_name="bzr_bzcp_patch_atlas_dll",
        analyze=True,
        nested_project_location=True,
    ) as api:
        program = api.getCurrentProgram()
        listing = program.getListing()
        for target in sorted(target_addrs):
            addr = api.toAddr(format_hex(target))
            inst = listing.getInstructionAt(addr) or listing.getInstructionContaining(addr)
            if inst is None:
                result[target] = {
                    "address": format_hex(target),
                    "note": DLL_ADDRESS_NOTES.get(target),
                    "instructions": [],
                }
                continue
            instructions = capture_instruction_block(listing, inst, count=6)
            callouts = [
                item["text"]
                for item in instructions
                if item["text"].startswith("CALL ")
            ]
            result[target] = {
                "address": format_hex(target),
                "note": DLL_ADDRESS_NOTES.get(target),
                "instructions": instructions,
                "summary": summarize_stub(instructions),
                "callouts": callouts,
            }
    shutil.rmtree(project_dir, ignore_errors=True)
    return result


def build_atlas_data(
    bzcp_path: Path,
    winmm_path: Path,
    exe_path: Path,
    addr_table_path: Path,
    ghidra_install: Path | None,
) -> dict[str, Any]:
    if ghidra_install is not None:
        pyghidra.start(False, install_dir=ghidra_install)
    else:
        pyghidra.start(False)

    bzcp = BinaryView(bzcp_path)
    winmm = BinaryView(winmm_path)
    exe = BinaryView(exe_path)
    slot_map = load_slot_map(addr_table_path)
    insns = disassemble_worker(bzcp)
    names = collect_patch_names(bzcp, insns)
    patches = collect_patch_writes(bzcp, insns, names, slot_map)

    exe_site_info = analyze_exe_sites(exe_path, patches, ghidra_install)
    dll_target_addrs = {
        patch.payload_value
        for patch in patches
        if patch.kind in {"jmp5", "rel32"}
        and patch.payload_value is not None
        and bzcp.imagebase <= patch.payload_value < bzcp.imagebase + bzcp.binary.optional_header.sizeof_image
    }
    dll_stub_info = analyze_dll_stubs(bzcp_path, dll_target_addrs)

    category_counts: Counter[str] = Counter()
    kind_counts: Counter[str] = Counter()
    patches_out: list[dict[str, Any]] = []
    hook_usage: dict[int, list[int]] = defaultdict(list)

    for patch in patches:
        category = classify_category(patch.name)
        category_counts[category] += 1
        kind_counts[patch.kind] += 1

        exe_info = exe_site_info.get(patch.dest_va, {})
        instruction = exe_info.get("instruction")
        function = exe_info.get("function")
        original_bytes = exe.read_bytes(patch.dest_va, patch.length).hex()
        open_shim_status, open_shim_note = OPEN_SHIM_STATUS.get(
            patch.dest_va,
            ("unmodeled", "Clean-room shim does not currently model this original _bzcp.dll patch site."),
        )

        patch_record = {
            "index": patch.index,
            "name": patch.name,
            "category": category,
            "dest_va": format_hex(patch.dest_va),
            "dest_slot_va": format_hex(patch.dest_slot_va),
            "length": patch.length,
            "kind": patch.kind,
            "payload_value": format_hex(patch.payload_value) if patch.payload_value is not None else None,
            "payload_desc": payload_desc(bzcp, patch),
            "call_va": format_hex(patch.call_va),
            "original_bytes": original_bytes,
            "instruction": instruction,
            "function": function,
            "patch_bytes": exe_info.get("patch_bytes"),
            "open_shim_status": open_shim_status,
            "open_shim_note": open_shim_note,
        }
        patches_out.append(patch_record)
        if patch.payload_value is not None:
            hook_usage[patch.payload_value].append(patch.index)

    hook_stubs: list[dict[str, Any]] = []
    for target in sorted(dll_target_addrs):
        hook_info = dict(dll_stub_info.get(target, {}))
        hook_info["used_by_patches"] = hook_usage.get(target, [])
        hook_stubs.append(hook_info)

    return {
        "inputs": {
            "bzcp_dll": str(bzcp_path),
            "winmm_bin": str(winmm_path),
            "gog_exe": str(exe_path),
            "addr_table": str(addr_table_path),
        },
        "metadata": {
            "bzcp_pdb": bzcp.pdb_filename(),
            "winmm_pdb": winmm.pdb_filename(),
            "patch_count": len(patches_out),
            "kind_counts": dict(sorted(kind_counts.items())),
            "category_counts": dict(sorted(category_counts.items())),
            "dll_hook_target_count": len(dll_target_addrs),
        },
        "patches": patches_out,
        "dll_hook_stubs": hook_stubs,
    }


def render_markdown(data: dict[str, Any]) -> str:
    lines: list[str] = []
    lines.append("# BZCP Patch Atlas")
    lines.append("")
    lines.append("Generated from `_bzcp.dll`, `winmm.bin`, the GOG `battlezone98redux.exe`, and direct Ghidra listing data.")
    lines.append("")
    lines.append("## Summary")
    lines.append("")
    lines.append(f"- Patch writes recovered: `{data['metadata']['patch_count']}`")
    lines.append(f"- Unique `_bzcp.dll` hook targets: `{data['metadata']['dll_hook_target_count']}`")
    lines.append(f"- `_bzcp.dll` PDB: `{data['metadata']['bzcp_pdb']}`")
    lines.append(f"- `winmm.bin` PDB: `{data['metadata']['winmm_pdb']}`")
    lines.append("- Patch kinds:")
    for kind, count in data["metadata"]["kind_counts"].items():
        lines.append(f"  - `{kind}`: `{count}`")
    lines.append("- Patch categories:")
    for category, count in data["metadata"]["category_counts"].items():
        lines.append(f"  - {category}: `{count}`")
    lines.append("")
    lines.append("## Clean-Room Shim Alignment")
    lines.append("")
    lines.append("- Correct alignments:")
    lines.append("  - `0x0079B85F`, `0x00799279`, `0x00799377` are correctly identified as the three hop-fix detours.")
    lines.append("  - `0x0078DD4E` and `0x00618C2F` are now patched as the real version-string operand sites.")
    lines.append("  - `0x007AA5A1` is now named and patched as the original vehicle control branch fix.")
    lines.append("- Probe-only alignments:")
    lines.append("  - `0x007680D6` and `0x00799116` correspond to real `_bzcp.dll` patch sites, but the clean-room shim only probes them.")
    lines.append("- Remaining intentionally deferred hook:")
    lines.append("  - `0x0062480B` is the original `/help` and `/ban` command intercept; the clean-room shim no longer mislabels it, but does not port it yet.")
    lines.append("")
    lines.append("## All Patch Writes")
    lines.append("")
    lines.append("| # | Name | Category | BZR VA | Function | Containing Instruction | Kind | Payload | Open Shim |")
    lines.append("| --- | --- | --- | --- | --- | --- | --- | --- | --- |")
    for patch in data["patches"]:
        function = patch["function"]["entry"] if patch["function"] else "n/a"
        inst = "n/a"
        if patch["instruction"]:
            field = patch["instruction"]["field_offset"]
            suffix = "" if field == 0 else f" [+{field}]"
            inst = f"`{patch['instruction']['address']}` `{patch['instruction']['text']}`{suffix}"
        lines.append(
            f"| {patch['index']} | {patch['name']} | {patch['category']} | `{patch['dest_va']}` | "
            f"`{function}` | {inst} | `{patch['kind']}` | `{patch['payload_desc']}` | "
            f"`{patch['open_shim_status']}` |"
        )
    lines.append("")
    lines.append("## Unique `_bzcp.dll` Hook Targets")
    lines.append("")
    lines.append("| Target | Note | Used By | Preview |")
    lines.append("| --- | --- | --- | --- |")
    for stub in data["dll_hook_stubs"]:
        target = stub["address"]
        note = stub.get("note") or ""
        used_by = ", ".join(str(index) for index in stub.get("used_by_patches", []))
        preview = stub.get("summary", "")
        lines.append(f"| `{target}` | {note} | `{used_by}` | `{preview}` |")
    lines.append("")
    lines.append("## Notes")
    lines.append("")
    lines.append("- `jmp5` entries replace the full 5-byte site with `E9 rel32` into `_bzcp.dll`.")
    lines.append("- `rel32` entries rewrite only the 4-byte relative operand of an existing `CALL` or `JMP`-style instruction.")
    lines.append("- `u32` entries rewrite immediate values or absolute data references inside existing instructions.")
    lines.append("- `u8` entries are single-byte branch or flag flips.")
    return "\n".join(lines)


def main() -> None:
    parser = argparse.ArgumentParser(description="Build a detailed _bzcp.dll patch atlas against the GOG BZR executable.")
    parser.add_argument(
        "--bzcp",
        type=Path,
        default=Path("reverse_engineering/workshop/3362534335/latest/_bzcp.dll"),
        help="Path to _bzcp.dll",
    )
    parser.add_argument(
        "--winmm",
        type=Path,
        default=Path("reverse_engineering/workshop/3362534335/latest/winmm.bin"),
        help="Path to winmm.bin",
    )
    parser.add_argument(
        "--exe",
        type=Path,
        default=Path(r"C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe"),
        help="Path to the GOG battlezone98redux.exe",
    )
    parser.add_argument(
        "--addr-table",
        type=Path,
        default=Path("reverse_engineering/workshop/3362534335/bzcp_addr_table.csv"),
        help="Path to the extracted _bzcp.dll slot address table",
    )
    parser.add_argument(
        "--json-out",
        type=Path,
        default=Path("reverse_engineering/workshop/3362534335/bzcp_patch_atlas.json"),
        help="JSON output path",
    )
    parser.add_argument(
        "--md-out",
        type=Path,
        default=Path("reverse_engineering/workshop/3362534335/bzcp_patch_atlas.md"),
        help="Markdown output path",
    )
    parser.add_argument(
        "--ghidra-install",
        type=Path,
        default=Path(os.environ["GHIDRA_INSTALL_DIR"]) if "GHIDRA_INSTALL_DIR" in os.environ else None,
        help="Optional Ghidra install directory. Defaults to GHIDRA_INSTALL_DIR if set.",
    )
    args = parser.parse_args()

    warnings.filterwarnings("ignore", category=DeprecationWarning, message=r"open_program\(\) is deprecated.*")

    atlas = build_atlas_data(args.bzcp, args.winmm, args.exe, args.addr_table, args.ghidra_install)
    args.json_out.write_text(json.dumps(atlas, indent=2), encoding="utf-8")
    args.md_out.write_text(render_markdown(atlas), encoding="utf-8")


if __name__ == "__main__":
    main()
