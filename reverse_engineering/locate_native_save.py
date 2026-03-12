from __future__ import annotations

import argparse
import hashlib
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable

import pefile


SAVE_FIELD_STRINGS = (
    b"binarySave",
    b"msn_filename",
    b"seq_count",
    b"missionSave",
    b"runType",
    b"saveGameDesc",
    b"TerrainName",
    b"Failed to save game",
)

AUTO_SAVE_STRINGS = (
    b"auto.sav",
    b"auto2.sav",
    b"Auto Load Game: Run state set to bookmark",
)

# Unique in the GOG build. Wildcards cover call displacements and absolute globals.
GOG_SAVEGAME_SIGNATURE = (
    "55 8B EC 81 EC 94 00 00 00 C6 45 FF 01 E8 ?? ?? ?? ?? "
    "89 85 78 FF FF FF 68 ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 C4 04 "
    "0F B6 05 ?? ?? ?? ?? 85 C0 0F 84 ?? ?? ?? ?? 6A 2E"
)


@dataclass(frozen=True)
class PeView:
    path: Path
    pe: pefile.PE
    image: bytes
    text_section: pefile.SectionStructure
    text_data: bytes

    @property
    def image_base(self) -> int:
        return self.pe.OPTIONAL_HEADER.ImageBase

    @property
    def entrypoint_rva(self) -> int:
        return self.pe.OPTIONAL_HEADER.AddressOfEntryPoint

    def va(self, rva: int) -> int:
        return self.image_base + rva


def load_pe(path: Path) -> PeView:
    pe = pefile.PE(str(path), fast_load=False)
    image = pe.get_memory_mapped_image()
    text = next(section for section in pe.sections if section.Name.rstrip(b"\0") == b".text")
    return PeView(path=path, pe=pe, image=image, text_section=text, text_data=text.get_data())


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def find_string_rva(view: PeView, needle: bytes) -> int | None:
    raw = view.path.read_bytes()
    offset = raw.find(needle)
    if offset < 0:
        return None
    return view.pe.get_rva_from_offset(offset)


def find_immediate_refs(view: PeView, va: int) -> list[int]:
    pattern = va.to_bytes(4, "little")
    refs: list[int] = []
    start = 0
    while True:
        index = view.text_data.find(pattern, start)
        if index < 0:
            return refs
        refs.append(view.text_section.VirtualAddress + index)
        start = index + 1


def backtrack_prolog(view: PeView, near_rva: int, max_back: int = 0x400) -> int | None:
    start_rva = max(view.text_section.VirtualAddress, near_rva - max_back)
    start_off = start_rva - view.text_section.VirtualAddress
    end_off = near_rva - view.text_section.VirtualAddress
    window = view.text_data[start_off:end_off]

    candidates: list[int] = []
    for prolog in (b"\x55\x8B\xEC", b"\x8B\xFF\x55\x8B\xEC"):
        search = 0
        while True:
            index = window.find(prolog, search)
            if index < 0:
                break
            candidates.append(start_rva + index + (2 if prolog.startswith(b"\x8B\xFF") else 0))
            search = index + 1

    if not candidates:
        return None

    return max(candidates)


def parse_signature(signature: str) -> tuple[bytes, bytes]:
    pattern = bytearray()
    mask = bytearray()
    for token in signature.split():
        if token == "??":
            pattern.append(0)
            mask.append(0)
        else:
            pattern.append(int(token, 16))
            mask.append(1)
    return bytes(pattern), bytes(mask)


def find_signature_hits(data: bytes, signature: str) -> list[int]:
    pattern, mask = parse_signature(signature)
    hits: list[int] = []
    plen = len(pattern)
    for index in range(0, len(data) - plen + 1):
        for pos in range(plen):
            if mask[pos] and data[index + pos] != pattern[pos]:
                break
        else:
            hits.append(index)
    return hits


def section_hashes(view: PeView) -> dict[str, str]:
    out: dict[str, str] = {}
    for section in view.pe.sections:
        out[section.Name.rstrip(b"\0").decode(errors="ignore")] = sha256(section.get_data())
    return out


def summarize_field_cluster(view: PeView, labels: Iterable[bytes]) -> tuple[int | None, dict[str, list[int]]]:
    refs_by_label: dict[str, list[int]] = {}
    earliest: int | None = None
    for label in labels:
        rva = find_string_rva(view, label)
        if rva is None:
            refs_by_label[label.decode()] = []
            continue
        refs = find_immediate_refs(view, view.va(rva))
        refs_by_label[label.decode()] = refs
        if refs:
            candidate = min(refs)
            earliest = candidate if earliest is None else min(earliest, candidate)
    return earliest, refs_by_label


def print_view_header(name: str, view: PeView) -> None:
    print(f"== {name} ==")
    print(f"path: {view.path}")
    print(f"entrypoint_rva: 0x{view.entrypoint_rva:X}")
    print(f"text_sha256: {sha256(view.text_data)}")
    for section_name, digest in section_hashes(view).items():
        print(f"section[{section_name}]: {digest}")
    print()


def main() -> None:
    parser = argparse.ArgumentParser(description="Locate native Battlezone save routines in local executables.")
    parser.add_argument(
        "--gog",
        type=Path,
        default=Path(r"C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe"),
        help="Path to the GOG executable",
    )
    parser.add_argument(
        "--steam",
        type=Path,
        default=Path(r"C:\Users\istuart\Downloads\Battlezone 98 Redux\battlezone98redux.exe"),
        help="Path to the Steam executable",
    )
    args = parser.parse_args()

    gog = load_pe(args.gog)
    steam = load_pe(args.steam)

    print_view_header("gog", gog)
    print_view_header("steam", steam)

    earliest_ref, refs_by_label = summarize_field_cluster(gog, SAVE_FIELD_STRINGS)
    savegame_start = backtrack_prolog(gog, earliest_ref) if earliest_ref is not None else None
    print("GOG save-field refs:")
    for label, refs in refs_by_label.items():
        joined = ", ".join(f"0x{gog.va(rva):08X}" for rva in refs[:4]) or "<none>"
        print(f"  {label}: {joined}")
    print(f"GOG earliest field ref: {f'0x{gog.va(earliest_ref):08X}' if earliest_ref is not None else '<none>'}")
    print(f"GOG candidate SaveGame start: {f'0x{gog.va(savegame_start):08X}' if savegame_start is not None else '<none>'}")
    print("  inferred calling shape: bool __cdecl SaveGame(char* filename, int nType)")
    print()

    auto_ref, auto_refs = summarize_field_cluster(gog, AUTO_SAVE_STRINGS)
    auto_helper_start = backtrack_prolog(gog, auto_ref) if auto_ref is not None else None
    print("GOG auto-save helper refs:")
    for label, refs in auto_refs.items():
        joined = ", ".join(f"0x{gog.va(rva):08X}" for rva in refs[:4]) or "<none>"
        print(f"  {label}: {joined}")
    print(f"GOG first auto-save helper start: {f'0x{gog.va(auto_helper_start):08X}' if auto_helper_start is not None else '<none>'}")
    print()

    gog_hits = find_signature_hits(gog.text_data, GOG_SAVEGAME_SIGNATURE)
    steam_hits = find_signature_hits(steam.text_data, GOG_SAVEGAME_SIGNATURE)
    print(f"GOG SaveGame signature hits: {[hex(gog.text_section.VirtualAddress + hit) for hit in gog_hits]}")
    print(f"Steam SaveGame signature hits: {[hex(steam.text_section.VirtualAddress + hit) for hit in steam_hits]}")
    print()

    same_rdata = section_hashes(gog).get(".rdata") == section_hashes(steam).get(".rdata")
    same_data = section_hashes(gog).get(".data") == section_hashes(steam).get(".data")
    same_text = section_hashes(gog).get(".text") == section_hashes(steam).get(".text")
    print("Cross-build summary:")
    print(f"  .rdata identical: {same_rdata}")
    print(f"  .data identical: {same_data}")
    print(f"  .text identical: {same_text}")
    print("  Steam adds a .bind section and changes the entrypoint into that section, which is consistent with a wrapper/stub build.")
    print("  Expect GOG RVAs to work only on the unwrapped engine image, not on the Steam file-on-disk .text bytes.")


if __name__ == "__main__":
    main()
