from __future__ import annotations

import argparse
import json
import struct
import sys
import time
from datetime import datetime
from pathlib import Path
from typing import Any

from capture_runtime_layout import (
    PROCESS_QUERY_INFORMATION,
    PROCESS_VM_READ,
    ensure_allowed_name,
    enumerate_modules,
    find_module,
    find_process_by_pid,
    kernel32,
    read_process_memory,
    wait_for_process,
)


DISK_IMAGE_BASE = 0x00400000
CHUNK_EFFECT_SINGLETON_VA = 0x00950190
CHUNK_SIMULATE_SINGLETON_VA = 0x00946DD8
CHUNK_EFFECT_ENTRY_BASE_OFFSET = 0x28
CHUNK_EFFECT_ENTRY_SIZE = 0x20
CHUNK_EFFECT_ACTIVE_COUNT_OFFSET = 0x8028
CHUNK_EFFECT_ACTIVE_GATE_OFFSET = 0x802C
CHUNK_EFFECT_TUNING_BASE_OFFSET = 0x8038
CHUNK_EFFECT_TEMPLATE_LIST_OFFSET = 0x8050
OBJ76_FLAGS_OFFSET = 0x14
OBJ76_MATRIX_OFFSET = 0x20
OBJ76_GEOM_REF_OFFSET = 0x64
# Older notes called this a "template ref", but the legacy decompile strongly
# suggests obj+0x64 is the geometry-side identity we need for distinguishing
# stock chunklets from reused fragment GEO objects.
OBJ76_TEMPLATE_REF_OFFSET = OBJ76_GEOM_REF_OFFSET
OBJ76_PARENT_OFFSET = 0x78
OBJ76_SIBLING_OFFSET = 0x7C
OBJ76_CHILD_OFFSET = 0x80
OBJ76_CLASS_ID_OFFSET = 0x84
OBJ76_OWNER_OFFSET = 0x8C
OBJ76_TIMER_OFFSET = 0xAC


def u32(data: bytes, offset: int) -> int:
    if offset + 4 > len(data):
        return 0
    return int.from_bytes(data[offset : offset + 4], "little", signed=False)


def f32(data: bytes, offset: int) -> float:
    if offset + 4 > len(data):
        return 0.0
    return struct.unpack_from("<f", data, offset)[0]


def hex32(value: int) -> str:
    return f"0x{value:08X}"


def decode_entry_words(data: bytes) -> list[int]:
    words: list[int] = []
    for offset in range(0, min(len(data), CHUNK_EFFECT_ENTRY_SIZE), 4):
        words.append(u32(data, offset))
    return words


def classify_chunk_geom_name(name: str | None) -> str | None:
    if not name:
        return None
    lowered = name.lower()
    if lowered in {"chunk1", "chunk2"}:
        return "stock_chunklet_guess"
    return "named_non_chunklet_geom"


def read_c_string(handle: int, address: int, max_len: int = 64) -> str | None:
    if address == 0:
        return None

    raw, _error = read_process_memory(handle, address, max_len)
    if not raw:
        return None

    end = raw.find(b"\x00")
    if end == -1:
        end = len(raw)
    raw = raw[:end]
    if not raw:
        return None

    if any(byte < 0x20 or byte > 0x7E for byte in raw):
        return None

    try:
        return raw.decode("ascii")
    except UnicodeDecodeError:
        return None


def snapshot_block(handle: int, address: int, size: int) -> dict[str, Any]:
    raw, error = read_process_memory(handle, address, size)
    snapshot: dict[str, Any] = {
        "address": address,
        "address_hex": hex32(address),
        "read_error": error,
        "raw_dwords": [],
        "candidate_strings": [],
    }
    if not raw:
        return snapshot

    snapshot["raw_dwords"] = [u32(raw, offset) for offset in range(0, len(raw), 4)]
    seen_strings: set[str] = set()
    for value in snapshot["raw_dwords"][:16]:
        text = read_c_string(handle, value)
        if text and text not in seen_strings:
            seen_strings.add(text)
            snapshot["candidate_strings"].append(
                {
                    "pointer": value,
                    "pointer_hex": hex32(value),
                    "text": text,
                }
            )
    return snapshot


def snapshot_geom_ref_block(handle: int, address: int) -> dict[str, Any]:
    snapshot = snapshot_block(handle, address, 0x80)
    children: list[dict[str, Any]] = []
    raw_dwords = snapshot.get("raw_dwords", [])
    for child_ptr in raw_dwords[3:6]:
        if child_ptr:
            child_snapshot = snapshot_block(handle, child_ptr, 0x40)
            children.append(child_snapshot)
    snapshot["child_blocks"] = children
    return snapshot


def pick_snapshot_name(snapshot: dict[str, Any] | None) -> str | None:
    if not snapshot:
        return None

    for string_info in snapshot.get("candidate_strings", []):
        text = string_info.get("text")
        if text:
            return text

    for child_snapshot in snapshot.get("child_blocks", []):
        for string_info in child_snapshot.get("candidate_strings", []):
            text = string_info.get("text")
            if text:
                return text

    return None


def snapshot_obj76(handle: int, obj_ptr: int) -> dict[str, Any]:
    raw, error = read_process_memory(handle, obj_ptr, 0xC0)
    snapshot: dict[str, Any] = {
        "address": obj_ptr,
        "address_hex": hex32(obj_ptr),
        "read_error": error,
        "raw_dwords": [],
        "class_id": None,
        "flags": None,
        "geom_ref": None,
        "geom_name": None,
        "geom_kind": None,
        "template_ref": None,
        "parent": None,
        "sibling": None,
        "child": None,
        "owner": None,
        "timer": None,
        "matrix_floats": [],
    }

    if not raw:
        return snapshot

    raw_dwords = [u32(raw, offset) for offset in range(0, len(raw), 4)]
    snapshot["raw_dwords"] = raw_dwords
    snapshot["class_id"] = u32(raw, OBJ76_CLASS_ID_OFFSET)
    snapshot["flags"] = u32(raw, OBJ76_FLAGS_OFFSET)
    snapshot["geom_ref"] = u32(raw, OBJ76_GEOM_REF_OFFSET)
    snapshot["template_ref"] = snapshot["geom_ref"]
    snapshot["parent"] = u32(raw, OBJ76_PARENT_OFFSET)
    snapshot["sibling"] = u32(raw, OBJ76_SIBLING_OFFSET)
    snapshot["child"] = u32(raw, OBJ76_CHILD_OFFSET)
    snapshot["owner"] = u32(raw, OBJ76_OWNER_OFFSET)
    snapshot["timer"] = f32(raw, OBJ76_TIMER_OFFSET)
    snapshot["matrix_floats"] = [f32(raw, OBJ76_MATRIX_OFFSET + (index * 4)) for index in range(12)]
    return snapshot


def snapshot_chunk_effect(handle: int, chunk_effect_va: int, max_entries: int) -> dict[str, Any]:
    header_size = CHUNK_EFFECT_ENTRY_BASE_OFFSET + (max_entries * CHUNK_EFFECT_ENTRY_SIZE)
    tail_end = CHUNK_EFFECT_TEMPLATE_LIST_OFFSET + 8
    read_size = max(header_size, tail_end)
    raw, error = read_process_memory(handle, chunk_effect_va, read_size)

    snapshot: dict[str, Any] = {
        "captured_at": datetime.now().isoformat(timespec="milliseconds"),
        "chunk_effect": chunk_effect_va,
        "chunk_effect_hex": hex32(chunk_effect_va),
        "read_error": error,
        "count": 0,
        "gate": 0,
        "vtable": 0,
        "tuning": {},
        "template_list": 0,
        "template_count": 0,
        "entries": [],
    }

    if not raw:
        return snapshot

    count = u32(raw, CHUNK_EFFECT_ACTIVE_COUNT_OFFSET)
    snapshot["count"] = count
    snapshot["gate"] = u32(raw, CHUNK_EFFECT_ACTIVE_GATE_OFFSET)
    snapshot["vtable"] = u32(raw, 0x0)
    snapshot["tuning"] = {
        "f8038": f32(raw, CHUNK_EFFECT_TUNING_BASE_OFFSET + 0x0),
        "f803C": f32(raw, CHUNK_EFFECT_TUNING_BASE_OFFSET + 0x4),
        "f8040": f32(raw, CHUNK_EFFECT_TUNING_BASE_OFFSET + 0x8),
        "f8044": f32(raw, CHUNK_EFFECT_TUNING_BASE_OFFSET + 0xC),
        "f8048": f32(raw, CHUNK_EFFECT_TUNING_BASE_OFFSET + 0x10),
    }
    snapshot["template_list"] = u32(raw, CHUNK_EFFECT_TEMPLATE_LIST_OFFSET)
    snapshot["template_count"] = u32(raw, CHUNK_EFFECT_TEMPLATE_LIST_OFFSET + 4)

    entry_count = min(count, max_entries)
    entries: list[dict[str, Any]] = []
    for index in range(entry_count):
        entry_offset = CHUNK_EFFECT_ENTRY_BASE_OFFSET + (index * CHUNK_EFFECT_ENTRY_SIZE)
        entry_data = raw[entry_offset : entry_offset + CHUNK_EFFECT_ENTRY_SIZE]
        words = decode_entry_words(entry_data)
        entries.append(
            {
                "index": index,
                "offset": entry_offset,
                "words": words,
                "words_hex": [hex32(word) for word in words],
                "obj_ptr": words[0] if words else 0,
                "obj_ptr_hex": hex32(words[0]) if words else hex32(0),
            }
        )
    snapshot["entries"] = entries
    return snapshot


def enrich_sample(handle: int, sample: dict[str, Any], max_objects: int) -> None:
    geom_refs: dict[int, dict[str, Any]] = {}

    for entry in sample["entries"][:max_objects]:
        if entry["obj_ptr"]:
            obj_snapshot = snapshot_obj76(handle, entry["obj_ptr"])
            entry["obj_snapshot"] = obj_snapshot
            geom_ref = obj_snapshot.get("geom_ref") or 0
            if geom_ref:
                geom_snapshot = geom_refs.get(geom_ref)
                if geom_snapshot is None:
                    geom_snapshot = snapshot_geom_ref_block(handle, geom_ref)
                    geom_refs[geom_ref] = geom_snapshot

                geom_name = pick_snapshot_name(geom_snapshot)
                obj_snapshot["geom_name"] = geom_name
                obj_snapshot["geom_kind"] = classify_chunk_geom_name(geom_name)

    template_list_ptr = sample.get("template_list") or 0
    if template_list_ptr:
        read_size = max(0x20, min(0x100, max(sample.get("template_count", 0), 1) * 0x20))
        sample["template_list_snapshot"] = snapshot_block(handle, template_list_ptr, read_size)
    else:
        sample["template_list_snapshot"] = None

    sample["geom_ref_snapshots"] = list(geom_refs.values())
    sample["template_ref_snapshots"] = sample["geom_ref_snapshots"]


def resolve_runtime_va(main_module_base: int, disk_va: int) -> int:
    return main_module_base + (disk_va - DISK_IMAGE_BASE)


def make_output_dir(root: Path) -> Path:
    stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    output_dir = root / f"chunk_effect_probe_{stamp}"
    output_dir.mkdir(parents=True, exist_ok=False)
    return output_dir


def write_summary(output_dir: Path, report: dict[str, Any]) -> None:
    lines: list[str] = []
    lines.append("# ChunkEffect Live Probe")
    lines.append("")
    lines.append(f"- Timestamp: {report['captured_at']}")
    lines.append(f"- PID: {report['process']['pid']}")
    lines.append(f"- Process: {report['process']['name']}")
    lines.append(f"- EXE: {report['process']['exe']}")
    lines.append(f"- Main module base: {hex32(report['main_module_base'])}")
    lines.append(f"- ChunkEffect singleton: {hex32(report['chunk_effect'])}")
    lines.append(f"- ChunkSimulate singleton: {hex32(report['chunk_simulate'])}")
    lines.append("")
    lines.append("## Capture")
    lines.append("")
    lines.append(f"- Observed nonzero chunk count: {'yes' if report['observed_nonzero'] else 'no'}")
    lines.append(f"- Samples captured: {len(report['samples'])}")
    lines.append("")

    for sample in report["samples"]:
        lines.append(
            f"- {sample['captured_at']}: count={sample['count']} gate={hex32(sample['gate'])} "
            f"templateList={hex32(sample['template_list'])} templateCount={sample['template_count']}"
        )
        for entry in sample.get("entries", []):
            obj = entry.get("obj_snapshot")
            if obj:
                lines.append(
                    f"  entry[{entry['index']}] obj={entry['obj_ptr_hex']} "
                    f"class={obj.get('class_id')} geom={hex32(obj.get('geom_ref') or 0)} "
                    f"geomName={obj.get('geom_name') or '<none>'} "
                    f"geomKind={obj.get('geom_kind') or '<unknown>'} "
                    f"parent={hex32(obj.get('parent') or 0)} sibling={hex32(obj.get('sibling') or 0)} "
                    f"flags={hex32(obj.get('flags') or 0)} "
                    f"owner={hex32(obj.get('owner') or 0)} timer={obj.get('timer')}"
                )
        for geom_snapshot in sample.get("geom_ref_snapshots", []):
            geom_words = geom_snapshot.get("raw_dwords", [])[:8]
            lines.append(
                f"  geomRef {geom_snapshot['address_hex']} "
                f"words={[hex32(word) for word in geom_words]}"
            )
            for string_info in geom_snapshot.get("candidate_strings", [])[:4]:
                lines.append(
                    f"    string {string_info['pointer_hex']} -> {string_info['text']}"
                )
            for child_snapshot in geom_snapshot.get("child_blocks", [])[:3]:
                child_words = child_snapshot.get("raw_dwords", [])[:8]
                lines.append(
                    f"    child {child_snapshot['address_hex']} "
                    f"words={[hex32(word) for word in child_words]}"
                )
                for string_info in child_snapshot.get("candidate_strings", [])[:4]:
                    lines.append(
                        f"      string {string_info['pointer_hex']} -> {string_info['text']}"
                    )
        template_list_snapshot = sample.get("template_list_snapshot")
        if template_list_snapshot:
            list_words = template_list_snapshot.get("raw_dwords", [])[:16]
            lines.append(
                f"  templateListWords {[hex32(word) for word in list_words]}"
            )

    (output_dir / "summary.md").write_text("\n".join(lines) + "\n", encoding="utf-8")


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Poll Redux's live ChunkEffect singleton without breaking into the process."
    )
    parser.add_argument("--process-name", default="battlezone98redux.exe")
    parser.add_argument("--pid", type=int)
    parser.add_argument("--timeout", type=float, default=120.0)
    parser.add_argument("--poll-interval", type=float, default=0.05)
    parser.add_argument("--sample-window", type=float, default=2.0)
    parser.add_argument("--max-entries", type=int, default=16)
    parser.add_argument("--max-objects", type=int, default=8)
    parser.add_argument(
        "--output-root",
        type=Path,
        default=Path("reverse_engineering/snapshots"),
    )
    return parser


def main() -> int:
    parser = build_parser()
    args = parser.parse_args()

    if args.pid is not None:
        proc = find_process_by_pid(args.pid)
    else:
        ensure_allowed_name(args.process_name)
        proc = wait_for_process(args.process_name, timeout=args.timeout, poll_interval=0.25)

    modules = enumerate_modules(proc.pid)
    main_module = find_module(modules, Path(proc.exe()))
    chunk_effect_va = resolve_runtime_va(main_module.base, CHUNK_EFFECT_SINGLETON_VA)
    chunk_simulate_va = resolve_runtime_va(main_module.base, CHUNK_SIMULATE_SINGLETON_VA)

    handle = kernel32.OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, False, proc.pid)
    if not handle:
        raise OSError(f"OpenProcess failed for pid {proc.pid}: {kernel32.GetLastError()}")

    output_dir = make_output_dir(args.output_root)
    report: dict[str, Any] = {
        "captured_at": datetime.now().isoformat(timespec="seconds"),
        "process": {
            "pid": proc.pid,
            "name": proc.name(),
            "exe": proc.exe(),
        },
        "main_module_base": main_module.base,
        "chunk_effect": chunk_effect_va,
        "chunk_simulate": chunk_simulate_va,
        "observed_nonzero": False,
        "samples": [],
    }

    print(
        f"Watching pid {proc.pid} ChunkEffect={hex32(chunk_effect_va)} "
        f"ChunkSimulate={hex32(chunk_simulate_va)}"
    )

    try:
        deadline = time.monotonic() + args.timeout
        capture_deadline = None
        while time.monotonic() < deadline:
            sample = snapshot_chunk_effect(handle, chunk_effect_va, args.max_entries)

            if sample["count"] > 0:
                if not report["observed_nonzero"]:
                    report["observed_nonzero"] = True
                    capture_deadline = time.monotonic() + args.sample_window
                    print(
                        f"[ChunkEffect] count={sample['count']} gate={hex32(sample['gate'])} "
                        f"templateList={hex32(sample['template_list'])} "
                        f"templateCount={sample['template_count']}"
                    )

                enrich_sample(handle, sample, args.max_objects)

                report["samples"].append(sample)

                if capture_deadline is not None and time.monotonic() >= capture_deadline:
                    break

            elif report["observed_nonzero"]:
                report["samples"].append(sample)
                break

            time.sleep(args.poll_interval)
    finally:
        kernel32.CloseHandle(handle)

    output_path = output_dir / "report.json"
    output_path.write_text(json.dumps(report, indent=2), encoding="utf-8")
    write_summary(output_dir, report)
    print(f"OUTPUT_DIR={output_dir}")

    if report["observed_nonzero"]:
        print(f"Captured {len(report['samples'])} chunk samples -> {output_dir}")
        if report["samples"]:
            first = report["samples"][0]
            print(
                f"First nonzero sample: count={first['count']} gate={hex32(first['gate'])} "
                f"templateList={hex32(first['template_list'])}"
            )
    else:
        print(f"No nonzero ChunkEffect samples observed -> {output_dir}")
        return 1

    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except TimeoutError as exc:
        print(str(exc), file=sys.stderr)
        raise SystemExit(1)
