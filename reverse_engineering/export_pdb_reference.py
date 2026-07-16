from __future__ import annotations

import argparse
import csv
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Iterable

import pefile
from construct import Array, CString, Int16ul
from pdbparse import parse as parse_pdb
from pdbparse.dbi import DBIExHeader, DBIHeader, DbiDbgHeader, get_parsed_size, sstFileIndex
from pdbparse.gdata import parse_stream as parse_gdata_stream
from pdbparse.pe import Sections


PATH_PATTERN = re.compile(
    r"[A-Za-z]:\\[^\x00\r\n]{1,260}\.(?:c|cc|cpp|cxx|h|hpp|hh|inl|ipp|obj|lib|pdb)",
)
MODULE_HEADER_PATTERN = re.compile(r"^Mod\s+(\d+)\s+\|\s+`(.*)`:.*$")
SYMBOL_RECORD_PATTERN = re.compile(
    r"^\s*(\d+)\s+\|\s+(S_[A-Z0-9_]+)\s+\[size\s*=\s*\d+\](?:\s+`(.*)`)?\s*$"
)
PROC_DETAIL_PATTERN = re.compile(
    r"parent\s*=\s*\d+,\s*end\s*=\s*(\d+),\s*addr\s*=\s*"
    r"([0-9A-Fa-f]+):([0-9A-Fa-f]+),\s*code size\s*=\s*(\d+)"
)
PROC_TYPE_PATTERN = re.compile(
    r"type\s*=\s*`(0x[0-9A-Fa-f]+)\s+\((.*?)\)`(?:,\s*debug start\s*=\s*(\d+),"
    r"\s*debug end\s*=\s*(\d+),\s*flags\s*=\s*(.*))?\s*$"
)
LOCAL_TYPE_PATTERN = re.compile(
    r"type\s*=\s*(0x[0-9A-Fa-f]+)(?:\s+\((.*?)\))?,\s*flags\s*=\s*(.*)\s*$"
)
SOURCE_FILE_PATTERN = re.compile(r"^(.*?)\s+\(([^:()]+):\s*([0-9A-Fa-f]+)\)\s*$")
LINE_RANGE_PATTERN = re.compile(
    r"^\s+([0-9A-Fa-f]+):([0-9A-Fa-f]+)-([0-9A-Fa-f]+),\s*"
    r"line/addr entries\s*=\s*(\d+)\s*$"
)
LINE_ENTRY_PATTERN = re.compile(r"(?:(\d+)|([A-Z][A-Z0-9_]*))\s+([0-9A-Fa-f]{8,})")
TYPE_LAYOUT_PATTERN = re.compile(r"^    (class|struct|union) (.*?) \[sizeof = (\d+)\]\s*$")
BASE_DECLARATION_PATTERN = re.compile(r"^      :\s+(.*?)(?:\s+\{)?\s*$")
DIRECT_MEMBER_PATTERN = re.compile(
    r"^      (data|base|vfptr) \+0x([0-9A-Fa-f]+) \[sizeof=(\d+)\]\s*(.*)$"
)
DIRECT_PADDING_PATTERN = re.compile(r"^      <padding> \((\d+) bytes\)\s*$")
TOTAL_PADDING_PATTERN = re.compile(r"^    Total padding (\d+) bytes")
IMMEDIATE_PADDING_PATTERN = re.compile(r"^    Immediate padding (\d+) bytes")


@dataclass(frozen=True)
class RsdsInfo:
    guid: str | None
    age: int | None
    pdb_path: str | None


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        while True:
            chunk = handle.read(1024 * 1024)
            if not chunk:
                return digest.hexdigest()
            digest.update(chunk)


def guid_to_string(guid) -> str:
    data4 = bytes(guid.Data4)
    return (
        f"{guid.Data1:08X}-{guid.Data2:04X}-{guid.Data3:04X}-"
        f"{data4[:2].hex().upper()}-{data4[2:].hex().upper()}"
    )


def read_pe_rsds(pe_path: Path) -> RsdsInfo:
    pe = pefile.PE(str(pe_path), fast_load=False)
    pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_DEBUG"]])
    if not hasattr(pe, "DIRECTORY_ENTRY_DEBUG"):
        return RsdsInfo(guid=None, age=None, pdb_path=None)

    for entry in pe.DIRECTORY_ENTRY_DEBUG:
        if entry.struct.Type != 2:
            continue
        raw = pe.get_data(entry.struct.AddressOfRawData, entry.struct.SizeOfData)
        if raw[:4] != b"RSDS" or len(raw) < 24:
            continue
        guid_raw = raw[4:20]
        age = int.from_bytes(raw[20:24], "little")
        pdb_path = raw[24:].split(b"\0", 1)[0].decode("utf-8", errors="replace")
        data1 = int.from_bytes(guid_raw[0:4], "little")
        data2 = int.from_bytes(guid_raw[4:6], "little")
        data3 = int.from_bytes(guid_raw[6:8], "little")
        data4 = guid_raw[8:10].hex().upper()
        data5 = guid_raw[10:16].hex().upper()
        guid = f"{data1:08X}-{data2:04X}-{data3:04X}-{data4}-{data5}"
        return RsdsInfo(guid=guid, age=age, pdb_path=pdb_path)

    return RsdsInfo(guid=None, age=None, pdb_path=None)


def parse_dbi_stream(pdb) -> tuple[dict, list[dict], list[list[str]], dict]:
    stream = pdb.STREAM_DBI.stream_file
    stream.seek(0)
    dbi_header = DBIHeader.parse_stream(stream)

    pos = get_parsed_size(DBIHeader, dbi_header)
    stream.seek(pos)
    dbiexhdr_data = stream.read(dbi_header.module_size)

    modules: list[dict] = []
    while dbiexhdr_data:
        header = DBIExHeader.parse(dbiexhdr_data)
        modules.append(
            {
                "module_name": header.modName,
                "object_name": header.objName,
                "stream": int(header.stream),
                "symbol_size": int(header.symSize),
                "source_file_count": int(header.nSrcFiles),
                "range_section": int(header.range.section),
                "range_offset": int(header.range.offset),
                "range_size": int(header.range.size),
                "flags": int(header.flags),
            }
        )
        size = get_parsed_size(DBIExHeader, header)
        if size % 4:
            size += 4 - (size % 4)
        dbiexhdr_data = dbiexhdr_data[size:]

    stream.seek(pos + dbi_header.module_size + dbi_header.secconSize + dbi_header.secmapSize)
    files_end = stream.tell() + dbi_header.filinfSize
    file_index = sstFileIndex.parse_stream(stream)
    mod_start = Array(file_index.cMod, Int16ul).parse_stream(stream)
    ref_counts = Array(file_index.cMod, Int16ul).parse_stream(stream)
    name_refs = Array(file_index.cRef, __import__("construct").Int32ul).parse_stream(stream)
    names_blob = stream.read(files_end - stream.tell())

    module_files: list[list[str]] = []
    for module_index in range(file_index.cMod):
        files: list[str] = []
        for name_index in range(mod_start[module_index], mod_start[module_index] + ref_counts[module_index]):
            files.append(CString(encoding="utf8").parse(names_blob[name_refs[name_index] :]))
        module_files.append(files)

    stream.seek(files_end + dbi_header.tsmapSize + dbi_header.ecinfoSize)
    dbg_header = DbiDbgHeader.parse_stream(stream)

    dbi_meta = {
        "machine": str(dbi_header.Machine),
        "module_count": len(modules),
        "file_count": sum(len(files) for files in module_files),
        "global_symbol_stream": int(dbi_header.symrecStream),
        "section_header_stream": int(dbg_header.snSectionHdr),
        "section_header_orig_stream": int(dbg_header.snSectionHdrOrig),
        "omap_from_source_stream": int(dbg_header.snOmapFromSrc),
    }
    return dbi_meta, modules, module_files, {"dbg_header": dbg_header}


def parse_pdb_sections(pdb, dbg_header) -> list[dict]:
    stream_index = dbg_header.snSectionHdrOrig if dbg_header.snSectionHdrOrig != -1 else dbg_header.snSectionHdr
    if stream_index == -1:
        return []
    sections = Sections.parse(pdb.streams[stream_index].data)
    output: list[dict] = []
    for section in sections:
        output.append(
            {
                "name": section.Name.rstrip("\0"),
                "virtual_address": int(section.VirtualAddress),
                "virtual_size": int(section.Misc.VirtualSize),
                "raw_size": int(section.SizeOfRawData),
            }
        )
    return output


def parse_global_symbols(pdb, sym_stream_index: int, sections: list[dict]) -> list[dict]:
    if sym_stream_index < 0:
        return []
    symbols = parse_gdata_stream(pdb.streams[sym_stream_index].stream_file)
    rows: list[dict] = []
    for symbol in symbols:
        if not hasattr(symbol, "symtype"):
            continue
        segment = int(getattr(symbol, "segment", 0))
        offset = int(getattr(symbol, "offset", 0))
        rva = None
        if 0 < segment <= len(sections):
            rva = int(sections[segment - 1]["virtual_address"]) + offset
        kind = "other"
        if int(symbol.symtype) == 2:
            kind = "function"
        elif int(symbol.symtype) == 0:
            kind = "data"
        rows.append(
            {
                "kind": kind,
                "symtype": int(symbol.symtype),
                "name": str(symbol.name),
                "segment": segment,
                "offset": offset,
                "rva": rva,
            }
        )
    return rows


def extract_path_hits(path: Path) -> list[str]:
    blob = path.read_bytes()
    ascii_text = blob.decode("latin-1", errors="ignore")
    hits = {match.group(0) for match in PATH_PATTERN.finditer(ascii_text)}
    utf16_text = blob.decode("utf-16le", errors="ignore")
    hits.update(match.group(0) for match in PATH_PATTERN.finditer(utf16_text))
    return sorted(hits)


def write_csv(path: Path, rows: Iterable[dict], fieldnames: list[str]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=fieldnames)
        writer.writeheader()
        for row in rows:
            writer.writerow(row)


def section_offset_to_rva(sections: list[dict], section: int, offset: int) -> int | None:
    if not 0 < section <= len(sections):
        return None
    return int(sections[section - 1]["virtual_address"]) + offset


def module_metadata(modules: list[dict], module_index: int) -> tuple[str, str]:
    if not 0 <= module_index < len(modules):
        return "", ""
    module = modules[module_index]
    return str(module.get("module_name", "")), str(module.get("object_name", ""))


def parse_private_symbols(
    path: Path, sections: list[dict], modules: list[dict]
) -> tuple[list[dict], list[dict], list[dict]]:
    functions: list[dict] = []
    locals_rows: list[dict] = []
    local_ranges: list[dict] = []
    current_module = -1
    current_function: dict | None = None
    current_local: dict | None = None
    current_range: dict | None = None
    inline_end_offsets: list[int] = []
    pending_inline_site = False

    def flush_range() -> None:
        nonlocal current_range
        if current_range is None:
            return
        current_range["description"] = " ".join(current_range.pop("description_parts")).strip()
        local_ranges.append(current_range)
        current_range = None

    with path.open("r", encoding="utf-8", errors="replace") as handle:
        for raw_line in handle:
            line = raw_line.rstrip("\r\n")
            module_match = MODULE_HEADER_PATTERN.match(line)
            if module_match:
                flush_range()
                current_module = int(module_match.group(1))
                current_function = None
                current_local = None
                inline_end_offsets.clear()
                pending_inline_site = False
                continue

            record_match = SYMBOL_RECORD_PATTERN.match(line)
            if record_match:
                flush_range()
                record_offset = int(record_match.group(1))
                record_kind = record_match.group(2)
                record_name = record_match.group(3) or ""

                while inline_end_offsets and record_offset >= inline_end_offsets[-1]:
                    inline_end_offsets.pop()

                function_end = current_function.get("end_record_offset") if current_function else ""
                if current_function and function_end != "" and record_offset >= int(function_end):
                    current_function = None
                    current_local = None
                    inline_end_offsets.clear()

                if re.fullmatch(r"S_[GL]PROC32(?:_ID)?", record_kind):
                    module_name, object_name = module_metadata(modules, current_module)
                    current_function = {
                        "module_index": current_module,
                        "module_name": module_name,
                        "object_name": object_name,
                        "record_kind": record_kind,
                        "symbol_record_offset": record_offset,
                        "end_record_offset": "",
                        "name": record_name,
                        "signature": "",
                        "type_index": "",
                        "section": "",
                        "offset": "",
                        "rva": "",
                        "code_size": "",
                        "debug_start": "",
                        "debug_end": "",
                        "flags": "",
                        "local_count": 0,
                        "inline_local_count": 0,
                        "parameter_count": 0,
                        "source_files": "",
                        "source_line_min": "",
                        "source_line_max": "",
                        "line_entry_count": 0,
                    }
                    functions.append(current_function)
                    current_local = None
                    inline_end_offsets.clear()
                    pending_inline_site = False
                    continue

                if record_kind == "S_INLINESITE" and current_function is not None:
                    current_local = None
                    pending_inline_site = True
                    continue

                if record_kind == "S_LOCAL" and current_function is not None:
                    inline_depth = len(inline_end_offsets)
                    current_local = {
                        "module_index": current_module,
                        "module_name": current_function["module_name"],
                        "function_symbol_record_offset": current_function["symbol_record_offset"],
                        "function_name": current_function["name"],
                        "function_rva": current_function["rva"],
                        "symbol_record_offset": record_offset,
                        "name": record_name,
                        "type_index": "",
                        "type_name": "",
                        "flags": "",
                        "is_parameter": False,
                        "is_function_parameter": False,
                        "inline_depth": inline_depth,
                        "location_record_count": 0,
                    }
                    locals_rows.append(current_local)
                    current_function["local_count"] = int(current_function["local_count"]) + 1
                    if inline_depth:
                        current_function["inline_local_count"] = int(current_function["inline_local_count"]) + 1
                    continue

                if record_kind.startswith("S_DEFRANGE") and current_function is not None and current_local is not None:
                    current_local["location_record_count"] = int(current_local["location_record_count"]) + 1
                    current_range = {
                        "module_index": current_module,
                        "function_symbol_record_offset": current_function["symbol_record_offset"],
                        "function_name": current_function["name"],
                        "function_rva": current_function["rva"],
                        "local_symbol_record_offset": current_local["symbol_record_offset"],
                        "local_name": current_local["name"],
                        "range_record_offset": record_offset,
                        "range_kind": record_kind,
                        "description_parts": [],
                    }
                    continue

                if record_kind == "S_END" and current_function is not None:
                    if record_offset >= int(current_function.get("end_record_offset") or record_offset):
                        current_function = None
                        current_local = None
                        inline_end_offsets.clear()
                    continue

                continue

            if current_range is not None and line.strip():
                current_range["description_parts"].append(line.strip())
                continue

            if pending_inline_site and current_function is not None:
                inline_end_match = re.search(r"\bend\s*=\s*(\d+)", line)
                if inline_end_match:
                    inline_end_offsets.append(int(inline_end_match.group(1)))
                    pending_inline_site = False
                    continue

            if current_function is not None:
                detail_match = PROC_DETAIL_PATTERN.search(line)
                if detail_match:
                    # llvm-pdbutil's symbol dump renders section:offset values in
                    # decimal, unlike its line-table dump (which uses hexadecimal).
                    section = int(detail_match.group(2), 10)
                    offset = int(detail_match.group(3), 10)
                    rva = section_offset_to_rva(sections, section, offset)
                    current_function.update(
                        {
                            "end_record_offset": int(detail_match.group(1)),
                            "section": section,
                            "offset": offset,
                            "rva": rva if rva is not None else "",
                            "code_size": int(detail_match.group(4)),
                        }
                    )
                    continue

                type_match = PROC_TYPE_PATTERN.search(line)
                if type_match:
                    current_function.update(
                        {
                            "type_index": type_match.group(1),
                            "signature": type_match.group(2),
                            "debug_start": type_match.group(3) or "",
                            "debug_end": type_match.group(4) or "",
                            "flags": type_match.group(5) or "",
                        }
                    )
                    continue

            if current_local is not None:
                local_type_match = LOCAL_TYPE_PATTERN.search(line)
                if local_type_match:
                    flags = local_type_match.group(3).strip()
                    is_parameter = "param" in {part.strip() for part in flags.split("|")}
                    is_function_parameter = is_parameter and int(current_local["inline_depth"]) == 0
                    current_local.update(
                        {
                            "function_rva": current_function["rva"] if current_function else "",
                            "type_index": local_type_match.group(1),
                            "type_name": local_type_match.group(2) or "",
                            "flags": flags,
                            "is_parameter": is_parameter,
                            "is_function_parameter": is_function_parameter,
                        }
                    )
                    if is_function_parameter and current_function is not None:
                        current_function["parameter_count"] = int(current_function["parameter_count"]) + 1

    flush_range()
    return functions, locals_rows, local_ranges


def parse_source_line_ranges(path: Path, sections: list[dict], modules: list[dict]) -> list[dict]:
    rows: list[dict] = []
    current_module = -1
    current_source = ""
    checksum_kind = ""
    checksum = ""
    current_range: dict | None = None

    def flush_range() -> None:
        nonlocal current_range
        if current_range is None:
            return
        lines = current_range.pop("lines")
        current_range["line_min"] = min(lines) if lines else ""
        current_range["line_max"] = max(lines) if lines else ""
        current_range["parsed_line_entry_count"] = current_range.pop("parsed_line_entry_count")
        current_range["special_line_entry_count"] = current_range.pop("special_line_entry_count")
        rows.append(current_range)
        current_range = None

    with path.open("r", encoding="utf-8", errors="replace") as handle:
        for raw_line in handle:
            line = raw_line.rstrip("\r\n")
            module_match = MODULE_HEADER_PATTERN.match(line)
            if module_match:
                flush_range()
                current_module = int(module_match.group(1))
                current_source = ""
                continue

            source_match = SOURCE_FILE_PATTERN.match(line)
            if source_match and not line.startswith(" "):
                flush_range()
                current_source = source_match.group(1)
                checksum_kind = source_match.group(2)
                checksum = source_match.group(3)
                continue

            range_match = LINE_RANGE_PATTERN.match(line)
            if range_match:
                flush_range()
                section = int(range_match.group(1), 16)
                offset_start = int(range_match.group(2), 16)
                offset_end = int(range_match.group(3), 16)
                rva_start = section_offset_to_rva(sections, section, offset_start)
                rva_end = section_offset_to_rva(sections, section, offset_end)
                module_name, _ = module_metadata(modules, current_module)
                current_range = {
                    "module_index": current_module,
                    "module_name": module_name,
                    "source_path": current_source,
                    "checksum_kind": checksum_kind,
                    "checksum": checksum,
                    "section": section,
                    "offset_start": offset_start,
                    "offset_end": offset_end,
                    "rva_start": rva_start if rva_start is not None else "",
                    "rva_end": rva_end if rva_end is not None else "",
                    "line_entry_count": int(range_match.group(4)),
                    "lines": [],
                    "parsed_line_entry_count": 0,
                    "special_line_entry_count": 0,
                }
                continue

            if current_range is not None:
                for entry_match in LINE_ENTRY_PATTERN.finditer(line):
                    current_range["parsed_line_entry_count"] += 1
                    if entry_match.group(1):
                        current_range["lines"].append(int(entry_match.group(1)))
                    else:
                        current_range["special_line_entry_count"] += 1

    flush_range()
    return rows


def add_source_context(functions: list[dict], line_ranges: list[dict]) -> None:
    ranges_by_module: dict[int, list[dict]] = {}
    for row in line_ranges:
        ranges_by_module.setdefault(int(row["module_index"]), []).append(row)

    for function in functions:
        if function["section"] == "" or function["offset"] == "" or function["code_size"] == "":
            continue
        start = int(function["offset"])
        end = start + int(function["code_size"])
        overlaps = [
            row
            for row in ranges_by_module.get(int(function["module_index"]), [])
            if int(row["section"]) == int(function["section"])
            and int(row["offset_start"]) < end
            and int(row["offset_end"]) > start
        ]
        if not overlaps:
            continue
        function["source_files"] = "|".join(dict.fromkeys(str(row["source_path"]) for row in overlaps if row["source_path"]))
        line_mins = [int(row["line_min"]) for row in overlaps if row["line_min"] != ""]
        line_maxs = [int(row["line_max"]) for row in overlaps if row["line_max"] != ""]
        function["source_line_min"] = min(line_mins) if line_mins else ""
        function["source_line_max"] = max(line_maxs) if line_maxs else ""
        function["line_entry_count"] = sum(int(row["line_entry_count"]) for row in overlaps)


def parse_class_layouts(path: Path) -> tuple[list[dict], list[dict]]:
    """Parse top-level type layouts while excluding recursively expanded base/member layouts."""
    layouts: list[dict] = []
    members: list[dict] = []
    current: dict | None = None

    with path.open("r", encoding="utf-8", errors="replace") as handle:
        for raw_line in handle:
            line = raw_line.rstrip("\r\n")
            type_match = TYPE_LAYOUT_PATTERN.match(line)
            if type_match:
                current = {
                    "type_ordinal": len(layouts),
                    "kind": type_match.group(1),
                    "name": type_match.group(2),
                    "size": int(type_match.group(3)),
                    "base_classes": "",
                    "direct_member_count": 0,
                    "direct_data_count": 0,
                    "direct_base_count": 0,
                    "vfptr_count": 0,
                    "direct_padding_bytes": 0,
                    "total_padding_bytes": "",
                    "immediate_padding_bytes": "",
                }
                layouts.append(current)
                continue

            if current is None:
                continue

            base_match = BASE_DECLARATION_PATTERN.match(line)
            if base_match:
                current["base_classes"] = base_match.group(1)
                continue

            member_match = DIRECT_MEMBER_PATTERN.match(line)
            if member_match:
                member_kind = member_match.group(1)
                members.append(
                    {
                        "type_ordinal": current["type_ordinal"],
                        "owner_kind": current["kind"],
                        "owner_name": current["name"],
                        "owner_size": current["size"],
                        "member_kind": member_kind,
                        "offset": int(member_match.group(2), 16),
                        "offset_hex": f"0x{int(member_match.group(2), 16):x}",
                        "size": int(member_match.group(3)),
                        "declaration": member_match.group(4).strip(),
                    }
                )
                current["direct_member_count"] += 1
                if member_kind == "data":
                    current["direct_data_count"] += 1
                elif member_kind == "base":
                    current["direct_base_count"] += 1
                elif member_kind == "vfptr":
                    current["vfptr_count"] += 1
                continue

            padding_match = DIRECT_PADDING_PATTERN.match(line)
            if padding_match:
                current["direct_padding_bytes"] += int(padding_match.group(1))
                continue

            total_padding_match = TOTAL_PADDING_PATTERN.match(line)
            if total_padding_match:
                current["total_padding_bytes"] = int(total_padding_match.group(1))
                continue

            immediate_padding_match = IMMEDIATE_PADDING_PATTERN.match(line)
            if immediate_padding_match:
                current["immediate_padding_bytes"] = int(immediate_padding_match.group(1))

    return layouts, members


def resolve_llvm_pdbutil(candidate: Path | None) -> Path | None:
    candidates: list[Path] = []
    if candidate and "<LLVM_ROOT>" not in str(candidate):
        candidates.append(candidate)
    command = shutil.which("llvm-pdbutil") or shutil.which("llvm-pdbutil.exe")
    if command:
        candidates.append(Path(command))
    llvm_root = os.environ.get("LLVM_ROOT")
    if llvm_root:
        candidates.append(Path(llvm_root) / "bin" / "llvm-pdbutil.exe")
    candidates.extend(
        [
            Path(r"C:\Program Files\LLVM\bin\llvm-pdbutil.exe"),
            Path(r"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\x64\bin\llvm-pdbutil.exe"),
        ]
    )
    for path in candidates:
        if path.exists():
            return path.resolve()
    return None


def run_llvm_pdbutil(llvm_pdbutil: Path, pdb_path: Path, output_dir: Path, heavy: bool) -> list[dict]:
    jobs = [
        (
            "dump_summary.txt",
            [
                str(llvm_pdbutil),
                "dump",
                "--summary",
                "--streams",
                "--named-streams",
                "--section-headers",
                "--modules",
                str(pdb_path),
            ],
        ),
        (
            "pretty_funcs.txt",
            [
                str(llvm_pdbutil),
                "pretty",
                "--globals",
                "--sym-types=funcs",
                "--symbol-order=name",
                "--no-system-libs",
                str(pdb_path),
            ],
        ),
        (
            "compiland_files.txt",
            [
                str(llvm_pdbutil),
                "dump",
                "--files",
                str(pdb_path),
            ],
        ),
    ]
    if heavy:
        jobs.extend(
            [
                (
                    "pretty_classes.txt",
                    [
                        str(llvm_pdbutil),
                        "pretty",
                        "--classes",
                        "--class-order=name",
                        "--class-definitions=layout",
                        "--no-system-libs",
                        str(pdb_path),
                    ],
                ),
                (
                    "publics.txt",
                    [
                        str(llvm_pdbutil),
                        "dump",
                        "--publics",
                        "--globals",
                        str(pdb_path),
                    ],
                ),
                (
                    "private_symbols.txt",
                    [
                        str(llvm_pdbutil),
                        "dump",
                        "--symbols",
                        "--jmc",
                        str(pdb_path),
                    ],
                ),
                (
                    "source_lines.txt",
                    [
                        str(llvm_pdbutil),
                        "dump",
                        "-l",
                        "--jmc",
                        str(pdb_path),
                    ],
                ),
                (
                    "type_stats.txt",
                    [
                        str(llvm_pdbutil),
                        "dump",
                        "--type-stats",
                        "--id-stats",
                        str(pdb_path),
                    ],
                ),
            ]
        )

    results: list[dict] = []
    for file_name, command in jobs:
        target = output_dir / file_name
        target.parent.mkdir(parents=True, exist_ok=True)
        with target.open("w", encoding="utf-8", errors="replace") as handle:
            completed = subprocess.run(command, stdout=handle, stderr=subprocess.STDOUT, text=True, check=False)
        results.append({"file": str(target), "exit_code": completed.returncode, "command": command})
    return results


def main() -> None:
    parser = argparse.ArgumentParser(description="Export best-effort metadata from a reference PDB.")
    parser.add_argument("--pe", type=Path, required=True, help="Path to the executable or DLL that the PDB approximates.")
    parser.add_argument("--pdb", type=Path, required=True, help="Path to the PDB file.")
    parser.add_argument("--output-dir", type=Path, required=True, help="Directory for exported metadata.")
    parser.add_argument("--llvm-pdbutil", type=Path, help="Optional llvm-pdbutil path; auto-discovered when omitted.")
    parser.add_argument("--skip-llvm", action="store_true", help="Skip llvm-pdbutil exports.")
    parser.add_argument("--lightweight", action="store_true", help="Skip the heaviest llvm-pdbutil dumps.")
    args = parser.parse_args()

    output_dir = args.output_dir
    output_dir.mkdir(parents=True, exist_ok=True)

    pe_rsds = read_pe_rsds(args.pe)
    pdb = parse_pdb(str(args.pdb), fast_load=True)
    pdb.STREAM_PDB.load()
    pdb_meta = {
        "guid": guid_to_string(pdb.STREAM_PDB.GUID),
        "age": int(pdb.STREAM_PDB.Age),
        "named_streams": list(pdb.STREAM_PDB.names),
    }

    dbi_meta, modules, module_files, internals = parse_dbi_stream(pdb)
    sections = parse_pdb_sections(pdb, internals["dbg_header"])
    globals_rows = parse_global_symbols(pdb, dbi_meta["global_symbol_stream"], sections)

    function_rows = [row for row in globals_rows if row["kind"] == "function"]
    data_rows = [row for row in globals_rows if row["kind"] == "data"]
    module_file_rows: list[dict] = []
    for module_index, files in enumerate(module_files):
        module_name = modules[module_index]["module_name"] if module_index < len(modules) else ""
        for source_path in files:
            module_file_rows.append({"module_index": module_index, "module_name": module_name, "source_path": source_path})

    raw_path_hits = extract_path_hits(args.pdb)

    write_csv(
        output_dir / "modules.csv",
        modules,
        [
            "module_name",
            "object_name",
            "stream",
            "symbol_size",
            "source_file_count",
            "range_section",
            "range_offset",
            "range_size",
            "flags",
        ],
    )
    write_csv(output_dir / "module_files.csv", module_file_rows, ["module_index", "module_name", "source_path"])
    write_csv(output_dir / "sections.csv", sections, ["name", "virtual_address", "virtual_size", "raw_size"])
    write_csv(output_dir / "public_functions.csv", function_rows, ["kind", "symtype", "name", "segment", "offset", "rva"])
    write_csv(output_dir / "global_data.csv", data_rows, ["kind", "symtype", "name", "segment", "offset", "rva"])

    (output_dir / "source_path_hits.txt").write_text("\n".join(raw_path_hits) + ("\n" if raw_path_hits else ""), encoding="utf-8")

    llvm_results: list[dict] = []
    private_functions: list[dict] = []
    private_locals: list[dict] = []
    private_local_ranges: list[dict] = []
    source_line_ranges: list[dict] = []
    class_layouts: list[dict] = []
    class_members: list[dict] = []
    llvm_pdbutil = resolve_llvm_pdbutil(args.llvm_pdbutil)
    if not args.skip_llvm and llvm_pdbutil:
        llvm_results = run_llvm_pdbutil(llvm_pdbutil, args.pdb, output_dir / "llvm", heavy=not args.lightweight)
        private_symbols_path = output_dir / "llvm" / "private_symbols.txt"
        source_lines_path = output_dir / "llvm" / "source_lines.txt"
        pretty_classes_path = output_dir / "llvm" / "pretty_classes.txt"
        if not args.lightweight and private_symbols_path.exists():
            private_functions, private_locals, private_local_ranges = parse_private_symbols(
                private_symbols_path, sections, modules
            )
        if not args.lightweight and source_lines_path.exists():
            source_line_ranges = parse_source_line_ranges(source_lines_path, sections, modules)
        if not args.lightweight and pretty_classes_path.exists():
            class_layouts, class_members = parse_class_layouts(pretty_classes_path)
        add_source_context(private_functions, source_line_ranges)

    write_csv(
        output_dir / "private_functions.csv",
        private_functions,
        [
            "module_index",
            "module_name",
            "object_name",
            "record_kind",
            "symbol_record_offset",
            "end_record_offset",
            "name",
            "signature",
            "type_index",
            "section",
            "offset",
            "rva",
            "code_size",
            "debug_start",
            "debug_end",
            "flags",
            "local_count",
            "inline_local_count",
            "parameter_count",
            "source_files",
            "source_line_min",
            "source_line_max",
            "line_entry_count",
        ],
    )
    write_csv(
        output_dir / "private_locals.csv",
        private_locals,
        [
            "module_index",
            "module_name",
            "function_symbol_record_offset",
            "function_name",
            "function_rva",
            "symbol_record_offset",
            "name",
            "type_index",
            "type_name",
            "flags",
            "is_parameter",
            "is_function_parameter",
            "inline_depth",
            "location_record_count",
        ],
    )
    write_csv(
        output_dir / "private_local_ranges.csv",
        private_local_ranges,
        [
            "module_index",
            "function_symbol_record_offset",
            "function_name",
            "function_rva",
            "local_symbol_record_offset",
            "local_name",
            "range_record_offset",
            "range_kind",
            "description",
        ],
    )
    write_csv(
        output_dir / "source_line_ranges.csv",
        source_line_ranges,
        [
            "module_index",
            "module_name",
            "source_path",
            "checksum_kind",
            "checksum",
            "section",
            "offset_start",
            "offset_end",
            "rva_start",
            "rva_end",
            "line_entry_count",
            "parsed_line_entry_count",
            "special_line_entry_count",
            "line_min",
            "line_max",
        ],
    )
    write_csv(
        output_dir / "class_layouts.csv",
        class_layouts,
        [
            "type_ordinal",
            "kind",
            "name",
            "size",
            "base_classes",
            "direct_member_count",
            "direct_data_count",
            "direct_base_count",
            "vfptr_count",
            "direct_padding_bytes",
            "total_padding_bytes",
            "immediate_padding_bytes",
        ],
    )
    write_csv(
        output_dir / "class_members.csv",
        class_members,
        [
            "type_ordinal",
            "owner_kind",
            "owner_name",
            "owner_size",
            "member_kind",
            "offset",
            "offset_hex",
            "size",
            "declaration",
        ],
    )

    summary = {
        "pe_path": str(args.pe),
        "pdb_path": str(args.pdb),
        "pe_sha256": sha256_file(args.pe),
        "pdb_sha256": sha256_file(args.pdb),
        "pe_rsds": asdict(pe_rsds),
        "pdb_info": pdb_meta,
        "dbi": dbi_meta,
        "match": {
            "guid_matches": pe_rsds.guid == pdb_meta["guid"],
            "age_matches": pe_rsds.age == pdb_meta["age"],
            "exact_match": pe_rsds.guid == pdb_meta["guid"] and pe_rsds.age == pdb_meta["age"],
        },
        "counts": {
            "modules": len(modules),
            "module_files": len(module_file_rows),
            "sections": len(sections),
            "public_functions": len(function_rows),
            "global_data": len(data_rows),
            "raw_path_hits": len(raw_path_hits),
            "private_functions": len(private_functions),
            "private_locals": len(private_locals),
            "private_local_ranges": len(private_local_ranges),
            "source_line_ranges": len(source_line_ranges),
            "class_layouts": len(class_layouts),
            "class_members": len(class_members),
        },
        "llvm_pdbutil": str(llvm_pdbutil) if llvm_pdbutil else None,
        "llvm_exports": llvm_results,
    }
    (output_dir / "reference.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")

    print(json.dumps(summary, indent=2))


if __name__ == "__main__":
    try:
        main()
    except Exception as exc:
        print(f"export_pdb_reference.py failed: {exc}", file=sys.stderr)
        raise
