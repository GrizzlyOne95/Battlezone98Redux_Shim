"""Rebuild a disk-layout PE from a module-sized debugger memory capture.

The capture must begin at the module image base and span SizeOfImage. This is
for analysis copies of packed BzE executables after their loader has restored
the sections in memory. It does not repair imports or guess the original OEP.
"""

from __future__ import annotations

import argparse
import struct
from pathlib import Path

import pefile


def align(value: int, alignment: int) -> int:
    return (value + alignment - 1) & ~(alignment - 1)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--memory", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()

    original = args.original.resolve()
    memory_path = args.memory.resolve()
    output = args.output.resolve()
    pe = pefile.PE(str(original), fast_load=False)
    memory = memory_path.read_bytes()
    expected_size = pe.OPTIONAL_HEADER.SizeOfImage
    if len(memory) != expected_size:
        raise ValueError(
            f"memory capture is {len(memory):#x} bytes; expected SizeOfImage {expected_size:#x}"
        )

    file_alignment = pe.OPTIONAL_HEADER.FileAlignment
    header_size = pe.OPTIONAL_HEADER.SizeOfHeaders
    cursor = align(header_size, file_alignment)
    section_layout: list[tuple[object, int, int]] = []
    for section in pe.sections:
        virtual_size = max(section.Misc_VirtualSize, section.SizeOfRawData)
        raw_size = align(virtual_size, file_alignment)
        section_layout.append((section, cursor, raw_size))
        cursor += raw_size

    rebuilt = bytearray(cursor)
    rebuilt[:header_size] = memory[:header_size]
    for section, raw_offset, raw_size in section_layout:
        section_header = section.get_file_offset()
        struct.pack_into("<I", rebuilt, section_header + 16, raw_size)
        struct.pack_into("<I", rebuilt, section_header + 20, raw_offset)
        source_start = section.VirtualAddress
        source_end = min(source_start + raw_size, len(memory))
        copied = source_end - source_start
        if copied > 0:
            rebuilt[raw_offset : raw_offset + copied] = memory[source_start:source_end]

    security_index = pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_SECURITY"]
    directory_base = pe.OPTIONAL_HEADER.DATA_DIRECTORY[0].get_file_offset()
    struct.pack_into("<II", rebuilt, directory_base + security_index * 8, 0, 0)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_bytes(rebuilt)
    print(output)


if __name__ == "__main__":
    main()
