from __future__ import annotations

import argparse
import csv
import re
import struct
from dataclasses import dataclass
from pathlib import Path

import lief
from capstone import CS_ARCH_X86, CS_MODE_32, Cs


PATCH_HELPER_VA = 0x10004930
LOG_HELPER_VA = 0x100184C0
WORKER_START_VA = 0x1000EF65
WORKER_END_VA = 0x10010156

GENERIC_LOGS = {
    "Game byte test matches expectation.",
    "=========== PATCHING ===========",
    "=========== ACTIVITY ===========",
    "Wrote %d",
}

HEX_RE = re.compile(r"0x[0-9a-fA-F]+")


@dataclass
class PatchWrite:
    index: int
    name: str
    call_va: int
    dest_va: int
    dest_slot_va: int | None
    length: int
    kind: str
    payload_value: int | None


class BinaryView:
    def __init__(self, path: Path) -> None:
        self.path = path
        self.binary = lief.parse(str(path))
        if self.binary is None:
            raise RuntimeError(f"Failed to parse {path}")
        self.imagebase = self.binary.optional_header.imagebase
        self.sections = []
        for section in self.binary.sections:
            raw = bytes(section.content)
            start = self.imagebase + section.virtual_address
            size = max(section.virtual_size, len(raw))
            if len(raw) < size:
                raw = raw.ljust(size, b"\x00")
            self.sections.append((start, start + size, raw, section.name))

    def read_bytes(self, va: int, size: int) -> bytes:
        for start, end, raw, _name in self.sections:
            if start <= va < end:
                offset = va - start
                chunk = raw[offset : offset + size]
                if len(chunk) != size:
                    raise ValueError(f"Short read at 0x{va:08X} from {self.path}")
                return chunk
        raise ValueError(f"VA 0x{va:08X} not found in {self.path}")

    def read_u32(self, va: int) -> int:
        return struct.unpack("<I", self.read_bytes(va, 4))[0]

    def read_utf16(self, va: int, max_bytes: int = 256) -> str:
        data = self.read_bytes(va, max_bytes)
        chars = []
        for idx in range(0, len(data) - 1, 2):
            pair = data[idx : idx + 2]
            if pair == b"\x00\x00":
                break
            chars.append(pair)
        text = b"".join(chars).decode("utf-16le", errors="replace")
        return text.rstrip("\r\n, ")

    def read_ascii(self, va: int, max_bytes: int = 256) -> str:
        data = self.read_bytes(va, max_bytes)
        text = data.split(b"\x00", 1)[0].decode("ascii", errors="replace")
        return text.rstrip("\r\n, ")

    def extract_ascii_strings(self, min_len: int = 4) -> list[str]:
        blob = self.path.read_bytes()
        out = []
        current = bytearray()
        for byte in blob:
            if 0x20 <= byte <= 0x7E:
                current.append(byte)
                continue
            if len(current) >= min_len:
                out.append(current.decode("ascii", errors="replace"))
            current.clear()
        if len(current) >= min_len:
            out.append(current.decode("ascii", errors="replace"))
        return out

    def extract_utf16_strings(self, min_len: int = 4) -> list[str]:
        blob = self.path.read_bytes()
        out = []
        current = bytearray()
        idx = 0
        while idx + 1 < len(blob):
            lo = blob[idx]
            hi = blob[idx + 1]
            if hi == 0 and 0x20 <= lo <= 0x7E:
                current.extend((lo, hi))
                idx += 2
                continue
            if len(current) >= min_len * 2:
                out.append(current.decode("utf-16le", errors="replace"))
            current.clear()
            idx += 2
        if len(current) >= min_len * 2:
            out.append(current.decode("utf-16le", errors="replace"))
        return out

    def pdb_filename(self) -> str | None:
        if not self.binary.has_debug:
            return None
        for entry in self.binary.debug:
            text = str(entry)
            for line in text.splitlines():
                line = line.strip()
                if line.startswith("filename:"):
                    return line.split(":", 1)[1].strip()
        return None


def parse_hex(op_str: str) -> int | None:
    match = HEX_RE.search(op_str)
    return int(match.group(0), 16) if match else None


def parse_hexes(op_str: str) -> list[int]:
    return [int(value, 16) for value in HEX_RE.findall(op_str)]


def first_hex(op_str: str) -> int | None:
    values = parse_hexes(op_str)
    return values[0] if values else None


def last_hex(op_str: str) -> int | None:
    values = parse_hexes(op_str)
    return values[-1] if values else None


def load_slot_map(path: Path) -> dict[int, int]:
    if not path.exists():
        return {}
    mapping: dict[int, int] = {}
    with path.open(newline="", encoding="utf-8") as handle:
        reader = csv.DictReader(handle)
        for row in reader:
            slot = int(row["Ptr"], 16)
            target = int(row["Offset"], 16)
            mapping[slot] = target
    return mapping


def disassemble_worker(view: BinaryView) -> list:
    text = next(section for section in view.binary.sections if section.name == ".text")
    start = WORKER_START_VA
    size = WORKER_END_VA - WORKER_START_VA
    code = bytes(text.content)[start - (view.imagebase + text.virtual_address) : start - (view.imagebase + text.virtual_address) + size]
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    return list(md.disasm(code, start))


def collect_patch_names(view: BinaryView, insns: list) -> list[str]:
    names: list[str] = []
    for idx, insn in enumerate(insns):
        if insn.mnemonic != "push":
            continue
        imm = parse_hex(insn.op_str)
        if imm is None:
            continue
        lookahead = insns[idx + 1 : idx + 4]
        if not any(item.mnemonic == "call" and item.op_str == f"0x{LOG_HELPER_VA:x}" for item in lookahead):
            continue
        if imm < view.imagebase:
            continue
        text = view.read_utf16(imm)
        if not text or text in GENERIC_LOGS:
            continue
        names.append(text)
    return names


def last_matching(insns: list, predicate) -> tuple[int, object] | tuple[None, None]:
    for idx in range(len(insns) - 1, -1, -1):
        if predicate(insns[idx]):
            return idx, insns[idx]
    return None, None


def classify_payload(window: list, dest_move_index: int, length: int) -> tuple[str, int | None]:
    if length == 5:
        _idx, insn = last_matching(
            window,
            lambda item: item.mnemonic == "mov"
            and (
                item.op_str.startswith("edx, 0x")
                or item.op_str.startswith("ebx, 0x")
            ),
        )
        return "jmp5", parse_hex(insn.op_str) if insn else None

    if length == 4:
        if any(
            item.mnemonic == "sub" and item.op_str in {"edx, ecx", "ebx, ecx"}
            for item in window
        ):
            _idx, insn = last_matching(
                window,
                lambda item: item.mnemonic == "mov"
                and (
                    item.op_str.startswith("edx, 0x")
                    or item.op_str.startswith("ebx, 0x")
                ),
            )
            return "rel32", parse_hex(insn.op_str) if insn else None

        _idx, insn = last_matching(
            window,
            lambda item: item.mnemonic == "mov"
            and item.op_str.startswith("dword ptr [ebp")
            and ", 0x" in item.op_str,
        )
        if insn:
            return "u32", last_hex(insn.op_str)

        _idx, insn = last_matching(
            window,
            lambda item: item.mnemonic == "mov"
            and (
                item.op_str.startswith("eax, 0x")
                or item.op_str.startswith("ecx, 0x")
                or item.op_str.startswith("edx, 0x")
                or item.op_str.startswith("ebx, 0x")
            ),
        )
        return "u32", last_hex(insn.op_str) if insn else None

    if length == 1:
        _idx, insn = last_matching(
            window,
            lambda item: item.mnemonic == "mov"
            and item.op_str.startswith("byte ptr [ebp")
            and ", 0x" in item.op_str,
        )
        return "u8", last_hex(insn.op_str) if insn else None

    return f"bytes{length}", None


def infer_target_reg(window: list) -> str | None:
    for item in reversed(window):
        if item.mnemonic == "sub" and item.op_str == "ebx, ecx":
            return "ebx"
        if item.mnemonic == "sub" and item.op_str == "edx, ecx":
            return "edx"
    return None


def regs_seeded_with_payload(window: list, payload_value: int) -> list[str]:
    regs: list[str] = []
    needle = f"0x{payload_value:x}"
    for item in window:
        if item.mnemonic != "mov":
            continue
        if item.op_str == f"edx, {needle}":
            regs.append("edx")
        elif item.op_str == f"ebx, {needle}":
            regs.append("ebx")
    return regs


def collect_patch_writes(view: BinaryView, insns: list, names: list[str], slot_map: dict[int, int]) -> list[PatchWrite]:
    calls = [idx for idx, insn in enumerate(insns) if insn.mnemonic == "call" and insn.op_str == f"0x{PATCH_HELPER_VA:x}"]
    if len(calls) != len(names):
        raise RuntimeError(f"Expected equal call/name counts, got {len(calls)} calls and {len(names)} names")

    patches: list[PatchWrite] = []
    prev_call_idx = -1
    last_targets: dict[str, int] = {}
    for patch_index, call_idx in enumerate(calls, start=1):
        window = insns[prev_call_idx + 1 : call_idx]
        prev_call_idx = call_idx

        length_idx, length_insn = last_matching(
            window,
            lambda item: item.mnemonic == "push" and item.op_str in {"1", "4", "5"},
        )
        if length_insn is None:
            raise RuntimeError(f"Failed to locate patch length for call {patch_index}")
        length = int(length_insn.op_str, 10)

        dest_move_idx, dest_move = last_matching(
            window,
            lambda item: item.mnemonic == "mov"
            and (item.op_str.startswith("ecx, dword ptr [0x") or item.op_str.startswith("ecx, 0x")),
        )
        if dest_move is None:
            raise RuntimeError(f"Failed to locate destination move for call {patch_index}")

        if "dword ptr [" in dest_move.op_str:
            dest_slot_va = first_hex(dest_move.op_str)
            if dest_slot_va is None:
                raise RuntimeError(f"Failed to parse slot VA for call {patch_index}")
            dest_va = slot_map.get(dest_slot_va, view.read_u32(dest_slot_va))
        else:
            dest_slot_va = None
            dest_va = last_hex(dest_move.op_str)
            if dest_va is None:
                raise RuntimeError(f"Failed to parse direct destination VA for call {patch_index}")

        kind, payload_value = classify_payload(window, dest_move_idx, length)
        target_reg = infer_target_reg(window)
        if payload_value is None and kind in {"jmp5", "rel32"} and target_reg in last_targets:
            payload_value = last_targets[target_reg]
        if payload_value is not None and kind in {"jmp5", "rel32"}:
            for reg in regs_seeded_with_payload(window, payload_value):
                last_targets[reg] = payload_value
            if target_reg is not None:
                last_targets[target_reg] = payload_value
        patches.append(
            PatchWrite(
                index=patch_index,
                name=names[patch_index - 1],
                call_va=insns[call_idx].address,
                dest_va=dest_va,
                dest_slot_va=dest_slot_va,
                length=length,
                kind=kind,
                payload_value=payload_value,
            )
        )
    return patches


def payload_desc(view: BinaryView, patch: PatchWrite) -> str:
    if patch.kind == "jmp5" and patch.payload_value is not None:
        return f"jmp5 -> _bzcp+0x{patch.payload_value - view.imagebase:05X}"
    if patch.kind == "rel32" and patch.payload_value is not None:
        return f"rel32 -> _bzcp+0x{patch.payload_value - view.imagebase:05X}"
    if patch.kind == "u8" and patch.payload_value is not None:
        return f"u8 0x{patch.payload_value:02X}"
    if patch.kind == "u32" and patch.payload_value is not None:
        desc = f"u32 0x{patch.payload_value:08X}"
        if view.imagebase <= patch.payload_value < view.imagebase + view.binary.optional_header.sizeof_image:
            try:
                text = view.read_ascii(patch.payload_value, 96)
                if text and text.isprintable():
                    desc += f' ("{text}")'
            except ValueError:
                pass
        return desc
    return patch.kind


def print_markdown(bzcp: BinaryView, winmm: BinaryView, patches: list[PatchWrite]) -> None:
    bzcp_export = bzcp.binary.get_export()
    winmm_export = winmm.binary.get_export()
    winmm_strings = winmm.extract_ascii_strings() + winmm.extract_utf16_strings()
    loader_paths = sorted({s for s in winmm_strings if "_bzcp.dll" in s})
    has_patch_symbol = any(s == "patch" for s in winmm_strings)

    print("# BZCP Reverse-Engineering Catalog")
    print()
    print("## Binary Metadata")
    print()
    print(f"- `_bzcp.dll` PDB: `{bzcp.pdb_filename()}`")
    print(f"- `_bzcp.dll` exports: {', '.join(f'`{entry.name}`@0x{entry.address:05X}' for entry in bzcp_export.entries)}")
    print(f"- `winmm.bin` PDB: `{winmm.pdb_filename()}`")
    print(f"- `winmm.bin` export count: {len(list(winmm_export.entries))}")
    print(f"- `winmm.bin` contains `patch` symbol lookup string: {'yes' if has_patch_symbol else 'no'}")
    if loader_paths:
        print("- `winmm.bin` hardcoded `_bzcp.dll` paths:")
        for path in loader_paths:
            print(f"  - `{path}`")
    print()
    print("## _bzcp.dll Worker Patch Sequence")
    print()
    print(f"- Worker range analyzed: `0x{WORKER_START_VA:08X}` -> `0x{WORKER_END_VA:08X}`")
    print(f"- Patch helper: `0x{PATCH_HELPER_VA:08X}`")
    print(f"- Recovered patch writes: `{len(patches)}`")
    print()
    print("| # | Name | BZR VA | Slot VA | Len | Payload | Call VA |")
    print("| --- | --- | --- | --- | --- | --- | --- |")
    for patch in patches:
        slot = f"`0x{patch.dest_slot_va:08X}`" if patch.dest_slot_va is not None else "`direct`"
        print(
            f"| {patch.index} | {patch.name} | `0x{patch.dest_va:08X}` | {slot} | `{patch.length}` | {payload_desc(bzcp, patch)} | `0x{patch.call_va:08X}` |"
        )


def main() -> None:
    parser = argparse.ArgumentParser(description="Extract a reproducible _bzcp.dll patch catalog")
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
        "--addr-table",
        type=Path,
        default=Path("reverse_engineering/workshop/3362534335/bzcp_addr_table.csv"),
        help="Optional slot-to-BZR address CSV extracted from decompilation",
    )
    args = parser.parse_args()

    bzcp = BinaryView(args.bzcp)
    winmm = BinaryView(args.winmm)
    slot_map = load_slot_map(args.addr_table)
    insns = disassemble_worker(bzcp)
    names = collect_patch_names(bzcp, insns)
    patches = collect_patch_writes(bzcp, insns, names, slot_map)
    print_markdown(bzcp, winmm, patches)


if __name__ == "__main__":
    main()
