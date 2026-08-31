#!/usr/bin/env python3
"""Minimal read-only parser for Steam depot manifest payload file mappings."""

from __future__ import annotations

import argparse
import struct
from pathlib import Path


PAYLOAD_MAGIC = 0x71F617D0
SYMLINK_FLAG = 0x200


def read_varint(data: bytes, offset: int) -> tuple[int, int]:
    value = 0
    shift = 0
    while True:
        byte = data[offset]
        offset += 1
        value |= (byte & 0x7F) << shift
        if not byte & 0x80:
            return value, offset
        shift += 7
        if shift >= 70:
            raise ValueError("invalid protobuf varint")


def parse_message(data: bytes) -> list[tuple[int, int, object]]:
    fields: list[tuple[int, int, object]] = []
    offset = 0
    while offset < len(data):
        key, offset = read_varint(data, offset)
        field = key >> 3
        wire = key & 7
        if wire == 0:
            value, offset = read_varint(data, offset)
        elif wire == 1:
            value = data[offset : offset + 8]
            offset += 8
        elif wire == 2:
            size, offset = read_varint(data, offset)
            value = data[offset : offset + size]
            offset += size
        elif wire == 5:
            value = data[offset : offset + 4]
            offset += 4
        else:
            raise ValueError(f"unsupported protobuf wire type {wire}")
        fields.append((field, wire, value))
    return fields


def decode_text(value: bytes) -> str | None:
    try:
        text = value.decode("utf-8")
    except UnicodeDecodeError:
        return None
    return text if all(ch.isprintable() or ch in "\t\r\n" for ch in text) else None


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("manifest", type=Path)
    args = parser.parse_args()

    raw = args.manifest.read_bytes()
    magic, payload_size = struct.unpack_from("<II", raw)
    if magic != PAYLOAD_MAGIC:
        raise SystemExit(f"unexpected payload magic 0x{magic:08x}")
    payload = raw[8 : 8 + payload_size]
    mappings = [value for field, wire, value in parse_message(payload) if field == 1 and wire == 2]

    flag_counts: dict[int, int] = {}
    symlinks: list[tuple[str, int, list[tuple[int, str]]]] = []
    for mapping in mappings:
        fields = parse_message(mapping)
        filename = next(
            decode_text(value)
            for field, wire, value in fields
            if field == 1 and wire == 2
        )
        flags = next((value for field, wire, value in fields if field == 3 and wire == 0), 0)
        flag_counts[flags] = flag_counts.get(flags, 0) + 1
        if flags & SYMLINK_FLAG:
            texts = [
                (field, text)
                for field, wire, value in fields
                if wire == 2 and (text := decode_text(value)) is not None
            ]
            symlinks.append((filename, flags, texts))

    print(f"payload_magic=0x{magic:08x}")
    print(f"payload_size={payload_size}")
    print(f"mapping_count={len(mappings)}")
    print("flag_counts=" + ", ".join(f"0x{k:x}:{v}" for k, v in sorted(flag_counts.items())))
    print(f"symlink_count={len(symlinks)}")
    for filename, flags, texts in symlinks:
        print(f"symlink flags=0x{flags:x} path={filename!r} text_fields={texts!r}")


if __name__ == "__main__":
    main()
