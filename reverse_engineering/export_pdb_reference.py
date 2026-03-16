from __future__ import annotations

import argparse
import csv
import hashlib
import json
import re
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
    parser.add_argument("--llvm-pdbutil", type=Path, default=Path(r"C:\Program Files\LLVM\bin\llvm-pdbutil.exe"))
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
    if not args.skip_llvm and args.llvm_pdbutil.exists():
        llvm_results = run_llvm_pdbutil(args.llvm_pdbutil, args.pdb, output_dir / "llvm", heavy=not args.lightweight)

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
        },
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
