"""Phase 2 native CPU attribution: read raw sampler output and attribute it.

Input is `cpu_samples.bin` as written by src/patches/native_cpu_sampler.cpp.
The sampler records raw addresses only; every mapping from an address to a
module, a function, or a subsystem happens here so the in-process cost stays
bounded and so the same capture can be re-analysed as naming improves.

Three properties of the data matter and are easy to misread:

* A sample's first address is the leaf (where the CPU actually was). The rest
  are return addresses recovered from the frame-pointer chain, deepest first.
  Self time is a leaf count; inclusive time is an "appears anywhere in the
  stack" count, and the two must never be added together.
* A thread parked in a wait still produces samples, with a leaf inside ntdll.
  Those samples are wall time, not CPU time, and they are labelled as waits
  rather than folded into the busy total.
* A frame-pointer walk stops at the first function that does not keep EBP. The
  fraction of walks that ended early is reported with every table, because a
  hierarchy built from truncated stacks understates its roots.

Naming comes from two sources. The game executable is resolved through a Ghidra
function export (body ranges, so an address inside a function resolves to that
function). Every other module is resolved to the nearest preceding entry in its
own PE export table, which names public functions exactly and attributes
internal ones to the exported function in front of them -- good enough to tell
a heap allocation from a wait, which is what this phase needs from ntdll.

Usage:
    python analyze_cpu_samples.py <cpu_samples.bin> [options]
"""

from __future__ import annotations

import argparse
import bisect
import collections
import csv
import datetime
import os
import re
import struct
import sys

HEADER_SIZE = 64
MAGIC = b"OSCPUSM1"

TAG_MODULE = 0x4C444F4D
TAG_THREAD = 0x44524854
TAG_SAMPLE_BLOCK = 0x4B4C4253
TAG_STATS = 0x54415453
TAG_END = 0x53444E45

FLAG_DEPTH_CAPPED = 1 << 0
FLAG_LEAF_OUTSIDE_MODULES = 1 << 1
FLAG_WALK_REJECTED = 1 << 2

FILETIME_UNIX_DELTA = 116444736000000000

# Leaf symbols that mean "this thread was not running". Everything that reaches
# a kernel wait passes through one of these.
WAIT_SYMBOLS = (
    "NtWaitForSingleObject", "ZwWaitForSingleObject",
    "NtWaitForMultipleObjects", "ZwWaitForMultipleObjects",
    "NtDelayExecution", "ZwDelayExecution",
    "NtRemoveIoCompletion", "ZwRemoveIoCompletion",
    "NtWaitForWorkViaWorkerFactory", "ZwWaitForWorkViaWorkerFactory",
    "NtSignalAndWaitForSingleObject", "ZwSignalAndWaitForSingleObject",
    "NtWaitForAlertByThreadId", "ZwWaitForAlertByThreadId",
    "NtYieldExecution", "ZwYieldExecution",
    "TpWaitForAlpcCompletion",
)


class Capture:
    def __init__(self) -> None:
        self.qpc_frequency = 0
        self.start_qpc = 0
        self.start_filetime = 0
        self.start_local_filetime = 0
        self.requested_hz = 0
        self.max_depth = 0
        self.process_id = 0
        self.modules: list[tuple[int, int, str]] = []
        self.samples: list[tuple[int, int, int, tuple[int, ...]]] = []
        self.thread_passes: list[dict] = []
        self.stats: list[dict] = []
        self.saw_end = False
        self._module_starts: list[int] = []

    def finalize(self) -> None:
        self.modules.sort(key=lambda entry: entry[0])
        self._module_starts = [entry[0] for entry in self.modules]

    def module_for(self, address: int) -> tuple[int, int, str] | None:
        index = bisect.bisect_right(self._module_starts, address) - 1
        if index < 0:
            return None
        entry = self.modules[index]
        return entry if address < entry[1] else None

    def local_time(self, qpc: int) -> datetime.datetime:
        offset_100ns = ((qpc - self.start_qpc) * 10_000_000) // self.qpc_frequency
        unix_100ns = self.start_local_filetime + offset_100ns - FILETIME_UNIX_DELTA
        return datetime.datetime(1970, 1, 1) + datetime.timedelta(
            microseconds=unix_100ns / 10.0)


def read_capture(path: str) -> Capture:
    with open(path, "rb") as handle:
        data = handle.read()
    if len(data) < HEADER_SIZE or data[:8] != MAGIC:
        raise SystemExit(f"{path}: not a sampler capture")

    capture = Capture()
    (header_size, pointer_bits, capture.qpc_frequency, capture.start_qpc,
     capture.start_filetime, capture.requested_hz, capture.max_depth,
     capture.process_id, _reserved,
     capture.start_local_filetime) = struct.unpack_from("<IIQQQIIIIQ", data, 8)
    if pointer_bits != 32:
        raise SystemExit(f"{path}: unexpected pointer width {pointer_bits}")

    seen_modules: set[tuple[int, int, str]] = set()
    offset = header_size
    total = len(data)
    while offset + 8 <= total:
        tag, payload = struct.unpack_from("<II", data, offset)
        offset += 8
        if offset + payload > total:
            # A capture whose process was killed mid-flush ends in a partial
            # chunk. Everything before it is still valid.
            break
        body = offset
        if tag == TAG_MODULE:
            base, size = struct.unpack_from("<QQ", data, body)
            name_bytes = struct.unpack_from("<H", data, body + 16)[0]
            name = data[body + 18:body + 18 + name_bytes].decode("ascii", "replace")
            entry = (base, base + size, name)
            if entry not in seen_modules:
                seen_modules.add(entry)
                capture.modules.append(entry)
        elif tag == TAG_THREAD:
            (tid, creation, cpu_total, cpu_delta, qpc, sampled) = struct.unpack_from(
                "<IQQQQB", data, body)
            capture.thread_passes.append({
                "tid": tid, "creation": creation, "cpu_total_100ns": cpu_total,
                "cpu_delta_100ns": cpu_delta, "qpc": qpc, "sampled": bool(sampled)})
        elif tag == TAG_SAMPLE_BLOCK:
            cursor = body
            end = body + payload
            while cursor + 16 <= end:
                tid, qpc, depth, flags, _pad = struct.unpack_from("<IQBBH", data, cursor)
                cursor += 16
                if cursor + depth * 4 > end:
                    break
                frames = struct.unpack_from("<%dI" % depth, data, cursor)
                cursor += depth * 4
                capture.samples.append((tid, qpc, flags, frames))
        elif tag == TAG_STATS:
            values = struct.unpack_from("<10Q", data, body)
            capture.stats.append(dict(zip(
                ("elapsed_qpc", "ticks_requested", "ticks_serviced", "samples",
                 "frames", "suspend_failures", "context_failures",
                 "leaf_outside_modules", "depth_capped", "suspend_qpc"), values)))
        elif tag == TAG_END:
            capture.saw_end = True
        offset += payload
    capture.finalize()
    return capture


class FunctionTable:
    """Address -> function, from a Ghidra inventory/functions.csv export."""

    def __init__(self, path: str) -> None:
        starts: list[int] = []
        records: dict[int, tuple[int, str]] = {}
        with open(path, newline="", encoding="utf-8-sig") as handle:
            for row in csv.DictReader(handle):
                try:
                    low = int(row["body_min_va"])
                    high = int(row["body_max_va"])
                except (KeyError, ValueError, TypeError):
                    continue
                entry = int(row.get("entry_va") or low)
                name = row.get("name") or ""
                if not name or name.startswith("FUN_"):
                    name = "sub_%06x" % entry
                records[low] = (high, name)
                starts.append(low)
        starts.sort()
        self.starts = starts
        self.records = records

    def lookup(self, address: int) -> str | None:
        index = bisect.bisect_right(self.starts, address) - 1
        if index < 0:
            return None
        low = self.starts[index]
        high, name = self.records[low]
        return name if address <= high else None


def pe_sections(data: bytes) -> tuple[int, list[tuple[int, int, int, int]]]:
    """Return (optional-header offset, [(virtual_addr, extent, raw_ptr, raw_size)])."""
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    if data[pe:pe + 4] != b"PE\0\0":
        raise ValueError("not a PE")
    section_count = struct.unpack_from("<H", data, pe + 6)[0]
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    optional = pe + 24
    sections = []
    base = pe + 24 + optional_size
    for index in range(section_count):
        header = base + index * 40
        virtual_size = struct.unpack_from("<I", data, header + 8)[0]
        virtual_address = struct.unpack_from("<I", data, header + 12)[0]
        raw_size = struct.unpack_from("<I", data, header + 16)[0]
        raw_pointer = struct.unpack_from("<I", data, header + 20)[0]
        sections.append((virtual_address, max(virtual_size, raw_size),
                         raw_pointer, raw_size))
    return optional, sections


def rva_to_offset(sections, rva: int) -> int | None:
    for virtual_address, extent, raw_pointer, _raw_size in sections:
        if virtual_address <= rva < virtual_address + extent:
            return raw_pointer + (rva - virtual_address)
    return None


def read_codeview(path: str) -> tuple[str, str] | None:
    """Return (pdb key as symbol-server GUID+age, pdb base name) for a module."""
    try:
        with open(path, "rb") as handle:
            data = handle.read()
        optional, sections = pe_sections(data)
        magic = struct.unpack_from("<H", data, optional)[0]
        directories = optional + (96 if magic == 0x10B else 112)
        debug_rva, debug_size = struct.unpack_from("<II", data, directories + 6 * 8)
        if debug_rva == 0:
            return None
        base = rva_to_offset(sections, debug_rva)
        if base is None:
            return None
        for index in range(debug_size // 28):
            entry = base + index * 28
            kind = struct.unpack_from("<I", data, entry + 12)[0]
            raw = struct.unpack_from("<I", data, entry + 24)[0]
            if kind != 2 or data[raw:raw + 4] != b"RSDS":
                continue
            a, b, c = struct.unpack_from("<IHH", data, raw + 4)
            tail = data[raw + 12:raw + 20]
            age = struct.unpack_from("<I", data, raw + 20)[0]
            name = data[raw + 24:data.index(b"\0", raw + 24)].decode("ascii", "replace")
            key = "%08X%04X%04X%s%X" % (a, b, c, tail.hex().upper(), age)
            return key, name
    except Exception:
        return None
    return None


def find_pdbutil() -> str | None:
    candidates = [
        r"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\x64\bin\llvm-pdbutil.exe",
        r"C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Tools\Llvm\x64\bin\llvm-pdbutil.exe",
        r"C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Tools\Llvm\x64\bin\llvm-pdbutil.exe",
        r"C:\Program Files\LLVM\bin\llvm-pdbutil.exe",
    ]
    for candidate in candidates:
        if os.path.exists(candidate):
            return candidate
    from shutil import which
    return which("llvm-pdbutil")


SYMBOL_CACHE_ROOTS = (r"C:\Symbols", r"C:\ProgramData\dbg\sym")

# MSVC names an anonymous-namespace function `NS::`anonymous namespace'::Fn`,
# so the closing backtick is the LAST one on the line, not the next one.
PUBLIC_RECORD = re.compile(r"`(.+)`")
PUBLIC_ADDRESS = re.compile(r"addr = ([0-9A-Fa-f]{4}):(\d+)")
PROC_RECORD = re.compile(r"S_[GL]PROC32(?:_ID)? \[size = \d+\] `(.+)`")


class PdbTable:
    """Address -> nearest preceding public symbol, from an exact-match PDB.

    Only a PDB whose GUID and age match the loaded module is used. The shipped
    battlezone98redux.pdb is from a 2016 build and is rejected here by that
    check, which is the intended outcome: naming the current executable from a
    different build's symbols is exactly the kind of plausible-but-wrong
    attribution this phase has to avoid.
    """

    _cache: dict[str, "PdbTable | None"] = {}

    def __init__(self, module_path: str, pdb_path: str) -> None:
        self.rvas: list[int] = []
        self.names: list[str] = []
        with open(module_path, "rb") as handle:
            data = handle.read()
        _optional, sections = pe_sections(data)
        section_rvas = [entry[0] for entry in sections]

        # llvm-pdbutil takes several seconds on a large PDB, so its output is
        # cached. The cache lives under the user temp directory rather than
        # beside the PDB: the symbol caches are shared machine state and this
        # analysis has no business writing into them.
        cache_root = os.path.join(
            os.environ.get("LOCALAPPDATA", os.environ.get("TEMP", ".")),
            "Temp", "openshim_symcache")
        os.makedirs(cache_root, exist_ok=True)
        stem = "%s.%s" % (os.path.basename(pdb_path),
                          os.path.basename(os.path.dirname(pdb_path)))

        def dump(kind: str) -> str:
            cached = os.path.join(cache_root, "%s.%s.txt" % (stem, kind))
            if os.path.exists(cached):
                with open(cached, encoding="utf-8", errors="replace") as handle:
                    return handle.read()
            tool = find_pdbutil()
            if not tool:
                return ""
            import subprocess
            result = subprocess.run([tool, "dump", "--" + kind, pdb_path],
                                    capture_output=True, text=True,
                                    errors="replace")
            try:
                with open(cached, "w", encoding="utf-8") as handle:
                    handle.write(result.stdout)
            except OSError:
                pass
            return result.stdout

        def collect(text: str, header: "re.Pattern[str]") -> list[tuple[int, str]]:
            pending: str | None = None
            found: list[tuple[int, str]] = []
            for line in text.splitlines():
                match = header.search(line)
                if match:
                    pending = match.group(1)
                    continue
                if pending is None:
                    continue
                match = PUBLIC_ADDRESS.search(line)
                if match:
                    segment = int(match.group(1), 16)
                    offset = int(match.group(2))
                    if 1 <= segment <= len(section_rvas):
                        found.append((section_rvas[segment - 1] + offset, pending))
                    pending = None
            return found

        # Private procedure records name static functions, which publics do
        # not. That distinction decides whether a shim frame can be named at
        # all: everything interesting inside OpenShim has internal linkage.
        pairs = collect(dump("symbols"), PROC_RECORD)
        publics = collect(dump("publics"),
                          re.compile(r"S_PUB32 \[size = \d+\] `(.+)`"))
        seen = {rva for rva, _name in pairs}
        pairs.extend(pair for pair in publics if pair[0] not in seen)
        pairs.sort()
        self.rvas = [pair[0] for pair in pairs]
        self.names = [pair[1] for pair in pairs]

    @classmethod
    def get(cls, module_path: str) -> "PdbTable | None":
        key = module_path.lower()
        if key in cls._cache:
            return cls._cache[key]
        cls._cache[key] = None
        codeview = read_codeview(module_path)
        if codeview:
            pdb_key, pdb_path = codeview
            pdb_name = os.path.basename(pdb_path)
            candidates = [os.path.join(root, pdb_name, pdb_key, pdb_name)
                          for root in SYMBOL_CACHE_ROOTS]
            candidates.append(os.path.join(os.path.dirname(module_path), pdb_name))
            # The build path recorded in the module itself. This is what names
            # the shim exactly: winmm.dll is built here, so its own PDB is the
            # only way to tell "OpenShim is on the stack" from "OpenShim is the
            # cost". The GUID check below still rejects a stale local PDB.
            candidates.append(pdb_path)
            for candidate in candidates:
                if not os.path.exists(candidate):
                    continue
                # Only the GUID is compared. A PDB's own age counts writes and
                # legitimately runs ahead of the age recorded in the module,
                # so requiring both to match rejects correct symbols.
                found_key = read_pdb_key(candidate)
                if not found_key or found_key[:32] != pdb_key[:32]:
                    continue
                try:
                    table = PdbTable(module_path, candidate)
                except Exception:
                    continue
                if table.rvas:
                    cls._cache[key] = table
                break
        return cls._cache[key]

    def lookup(self, rva: int) -> tuple[str, int] | None:
        index = bisect.bisect_right(self.rvas, rva) - 1
        if index < 0:
            return None
        return self.names[index], rva - self.rvas[index]


def read_pdb_key(path: str) -> str | None:
    """GUID+age of a PDB, so a mismatched build's symbols are never used."""
    try:
        with open(path, "rb") as handle:
            data = handle.read(64 * 1024)
        if not data.startswith(b"Microsoft C/C++ MSF 7.00"):
            return None
        block_size, _free, _blocks, directory_bytes, _reserved, block_map_addr = \
            struct.unpack_from("<IIIIII", data, 32)
        directory_blocks = (directory_bytes + block_size - 1) // block_size
        with open(path, "rb") as handle:
            handle.seek(block_map_addr * block_size)
            block_map = handle.read(directory_blocks * 4)
            indices = struct.unpack_from("<%dI" % directory_blocks, block_map, 0)
            # The stream directory itself is fragmented across blocks. Reading
            # only its first block truncates the stream table on any PDB large
            # enough to need a second one, which silently rejects valid symbols.
            directory = b"".join(
                (handle.seek(index * block_size), handle.read(block_size))[1]
                for index in indices)
            stream_count = struct.unpack_from("<I", directory, 0)[0]
            sizes = struct.unpack_from("<%dI" % stream_count, directory, 4)
            cursor = 4 + stream_count * 4
            blocks: list[list[int]] = []
            for size in sizes:
                count = 0 if size in (0, 0xFFFFFFFF) else (size + block_size - 1) // block_size
                blocks.append(list(struct.unpack_from("<%dI" % count, directory, cursor)))
                cursor += count * 4
            if len(blocks) < 2 or not blocks[1]:
                return None
            handle.seek(blocks[1][0] * block_size)
            head = handle.read(28)
        # PDB Info stream: version, signature, age, then the 16-byte GUID.
        _version, _signature, age, a, b, c = struct.unpack_from("<IIIIHH", head, 0)
        tail = head[20:28]
        return "%08X%04X%04X%s%X" % (a, b, c, tail.hex().upper(), age)
    except Exception:
        return None


class ExportTable:
    """Address -> nearest preceding PE export, read from the module on disk.

    Export addresses in these builds point at incremental-link thunks -- five
    bytes of `jmp target`, twenty bytes apart -- rather than at function bodies,
    so the raw table names a 256 KB thunk block and nothing else. Each thunk is
    followed to its target, which is what makes OgreMain and the CRT resolvable
    at all.
    """

    _cache: dict[str, "ExportTable | None"] = {}

    def __init__(self, path: str) -> None:
        self.rvas: list[int] = []
        self.names: list[str] = []
        with open(path, "rb") as handle:
            data = handle.read()
        pe = struct.unpack_from("<I", data, 0x3C)[0]
        if data[pe:pe + 4] != b"PE\0\0":
            raise ValueError("not a PE")
        section_count = struct.unpack_from("<H", data, pe + 6)[0]
        optional_size = struct.unpack_from("<H", data, pe + 20)[0]
        optional = pe + 24
        magic = struct.unpack_from("<H", data, optional)[0]
        directories = optional + (96 if magic == 0x10B else 112)
        export_rva, export_size = struct.unpack_from("<II", data, directories)
        if export_rva == 0 or export_size == 0:
            return
        sections = pe + 24 + optional_size

        def to_offset(rva: int) -> int | None:
            for index in range(section_count):
                header = sections + index * 40
                virtual_address = struct.unpack_from("<I", data, header + 12)[0]
                virtual_size = struct.unpack_from("<I", data, header + 8)[0]
                raw_size = struct.unpack_from("<I", data, header + 16)[0]
                raw_pointer = struct.unpack_from("<I", data, header + 20)[0]
                extent = max(virtual_size, raw_size)
                if virtual_address <= rva < virtual_address + extent:
                    return raw_pointer + (rva - virtual_address)
            return None

        directory = to_offset(export_rva)
        if directory is None:
            return
        name_count = struct.unpack_from("<I", data, directory + 24)[0]
        functions_rva = struct.unpack_from("<I", data, directory + 28)[0]
        names_rva = struct.unpack_from("<I", data, directory + 32)[0]
        ordinals_rva = struct.unpack_from("<I", data, directory + 36)[0]
        functions = to_offset(functions_rva)
        names = to_offset(names_rva)
        ordinals = to_offset(ordinals_rva)
        if None in (functions, names, ordinals):
            return
        pairs: list[tuple[int, str]] = []
        for index in range(name_count):
            name_pointer = struct.unpack_from("<I", data, names + index * 4)[0]
            ordinal = struct.unpack_from("<H", data, ordinals + index * 2)[0]
            function_rva = struct.unpack_from("<I", data, functions + ordinal * 4)[0]
            offset = to_offset(name_pointer)
            if offset is None:
                continue
            end = data.index(b"\0", offset)
            name = data[offset:end].decode("ascii", "replace")
            target = to_offset(function_rva)
            if target is not None and data[target:target + 1] == b"\xe9":
                relative = struct.unpack_from("<i", data, target + 1)[0]
                function_rva = (function_rva + 5 + relative) & 0xFFFFFFFF
            pairs.append((function_rva, name))
        pairs.sort()
        self.rvas = [pair[0] for pair in pairs]
        self.names = [pair[1] for pair in pairs]

    @classmethod
    def get(cls, path: str) -> "ExportTable | None":
        key = path.lower()
        if key not in cls._cache:
            try:
                cls._cache[key] = cls(path)
            except Exception:
                cls._cache[key] = None
        return cls._cache[key]

    def lookup(self, rva: int) -> tuple[str, int] | None:
        index = bisect.bisect_right(self.rvas, rva) - 1
        if index < 0:
            return None
        return self.names[index], rva - self.rvas[index]


def image_size(path: str) -> int | None:
    try:
        with open(path, "rb") as handle:
            data = handle.read(4096)
        pe = struct.unpack_from("<I", data, 0x3C)[0]
        magic = struct.unpack_from("<H", data, pe + 24)[0]
        return struct.unpack_from("<I", data, pe + 24 + 56)[0] if magic in (0x10B, 0x20B) else None
    except Exception:
        return None


def resolve_module_path(path: str, pointer_bits: int, size: int) -> str | None:
    """Map a recorded module path to the file this 64-bit analysis can read.

    A 32-bit process reports its system modules as C:\\Windows\\System32\\...,
    but that path is redirected to SysWOW64 for the process and NOT for a
    64-bit reader. Following the recorded path verbatim silently opens the
    64-bit ntdll, whose sections and GUID have nothing to do with the capture.
    The loaded size is checked afterwards so a wrong file is rejected rather
    than quietly producing confident nonsense.
    """
    candidates = [path]
    lowered = path.lower()
    if pointer_bits == 32 and "\\system32\\" in lowered:
        candidates.insert(0, re.sub(r"(?i)\\system32\\", r"\\SysWOW64\\", path))
    for candidate in candidates:
        if not os.path.exists(candidate):
            continue
        found = image_size(candidate)
        if found is not None and size and found != size:
            continue
        return candidate
    return None


class Symbolizer:
    def __init__(self, capture: Capture, functions: str | None,
                 game_module: str, no_exports: bool) -> None:
        self.capture = capture
        self.game_module = game_module.lower()
        self.no_exports = no_exports
        self.table = FunctionTable(functions) if functions else None
        self.cache: dict[int, str] = {}
        # Two modules can share a base name (the shim and the system winmm),
        # so disambiguate by appending the load base when that happens.
        counts = collections.Counter(
            os.path.basename(entry[2]).lower() for entry in capture.modules)
        self.short: dict[int, str] = {}
        self.file: dict[int, str | None] = {}
        self.unresolved: list[str] = []
        for base, end, path in capture.modules:
            name = os.path.basename(path)
            if counts[name.lower()] > 1:
                name = "%s@%08x" % (name, base)
            self.short[base] = name
            resolved = resolve_module_path(path, 32, end - base)
            self.file[base] = resolved
            if resolved is None:
                self.unresolved.append(path)

    def module_name(self, address: int) -> str:
        entry = self.capture.module_for(address)
        return self.short[entry[0]] if entry else "<unmapped>"

    def symbol(self, address: int) -> str:
        cached = self.cache.get(address)
        if cached is not None:
            return cached
        entry = self.capture.module_for(address)
        if entry is None:
            result = "<unmapped>+0x%x" % address
            self.cache[address] = result
            return result
        base, _end, _recorded = entry
        short = self.short[base]
        path = self.file[base] or ""
        if short.split("@")[0].lower() == self.game_module and self.table:
            found = self.table.lookup(address)
            if found:
                self.cache[address] = "%s!%s" % (short, found)
                return self.cache[address]
        if not self.no_exports and os.path.exists(path):
            # An exact-GUID PDB beats the export table: ntdll exports 2,517
            # symbols but its PDB carries 204,404 publics, and the heap
            # internals this phase cares about are in the second set only.
            pdb = PdbTable.get(path)
            if pdb:
                found = pdb.lookup(address - base)
                if found:
                    name, delta = found
                    self.cache[address] = (
                        "%s!%s" % (short, name) if delta == 0
                        else "%s!%s+0x%x" % (short, name, delta))
                    return self.cache[address]
            exports = ExportTable.get(path)
            if exports:
                found = exports.lookup(address - base)
                if found:
                    name, delta = found
                    self.cache[address] = (
                        "%s!%s" % (short, name) if delta == 0
                        else "%s!%s+0x%x" % (short, name, delta))
                    return self.cache[address]
        self.cache[address] = "%s+0x%x" % (short, address - base)
        return self.cache[address]


def parse_local(text: str) -> datetime.datetime:
    return datetime.datetime.fromisoformat(text.replace("Z", ""))


def window_from_bzlogger(path: str) -> tuple[datetime.datetime, datetime.datetime]:
    begin = end = None
    with open(path, encoding="utf-8", errors="replace") as handle:
        for line in handle:
            if "[LIVE_COMBAT_BENCH]" not in line:
                continue
            parts = line.split(" ", 2)
            if len(parts) < 2:
                continue
            try:
                stamp = parse_local(" ".join(parts[:2]))
            except ValueError:
                continue
            if "measure-begin" in line and begin is None:
                begin = stamp
            if "benchmark-end" in line:
                end = stamp
    if begin is None or end is None:
        raise SystemExit(f"{path}: could not find measure-begin/benchmark-end markers")
    return begin, end


class TreeNode:
    __slots__ = ("count", "children")

    def __init__(self) -> None:
        self.count = 0
        self.children: dict[str, "TreeNode"] = {}


def build_tree(stacks: list[tuple[str, ...]]) -> TreeNode:
    root = TreeNode()
    for stack in stacks:
        node = root
        node.count += 1
        for name in stack:
            child = node.children.get(name)
            if child is None:
                child = TreeNode()
                node.children[name] = child
            child.count += 1
            node = child
    return root


def print_tree(node: TreeNode, total: int, threshold: float,
               depth: int = 0, max_depth: int = 40) -> None:
    if depth >= max_depth:
        return
    ordered = sorted(node.children.items(), key=lambda kv: -kv[1].count)
    for name, child in ordered:
        share = 100.0 * child.count / total
        if share < threshold:
            continue
        print("%s%6.2f%%  %s" % ("  " * depth, share, name))
        print_tree(child, total, threshold, depth + 1, max_depth)


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("capture")
    parser.add_argument("--functions", default=None,
                        help="Ghidra inventory/functions.csv for the game module")
    parser.add_argument("--module", default="battlezone98redux.exe")
    parser.add_argument("--no-exports", action="store_true",
                        help="skip PE export-table naming for non-game modules")
    parser.add_argument("--window", nargs=2, default=None, metavar=("BEGIN", "END"))
    parser.add_argument("--bzlogger", default=None)
    parser.add_argument("--thread", type=int, default=None)
    parser.add_argument("--top", type=int, default=30)
    parser.add_argument("--tree", type=float, default=0.0,
                        help="print the call tree, pruned below this percent")
    parser.add_argument("--tree-depth", type=int, default=40)
    parser.add_argument("--csv", default=None)
    parser.add_argument("--label", default=None)
    parser.add_argument("--quiet", action="store_true",
                        help="print only the summary block")
    args = parser.parse_args(argv)

    capture = read_capture(args.capture)
    label = args.label or os.path.basename(os.path.dirname(
        os.path.normpath(args.capture))) or os.path.basename(args.capture)
    symbolizer = Symbolizer(capture, args.functions, args.module, args.no_exports)

    window = None
    if args.bzlogger:
        window = window_from_bzlogger(args.bzlogger)
    elif args.window:
        window = (parse_local(args.window[0]), parse_local(args.window[1]))

    samples = capture.samples
    if window:
        begin, end = window
        samples = [s for s in samples if begin <= capture.local_time(s[1]) <= end]
    if not samples:
        print("no samples in the selected window", file=sys.stderr)
        return 1

    per_thread = collections.Counter(s[0] for s in samples)
    target = args.thread if args.thread is not None else per_thread.most_common(1)[0][0]
    thread_samples = [s for s in samples if s[0] == target]
    total = len(thread_samples)

    self_counts: collections.Counter[str] = collections.Counter()
    inclusive_counts: collections.Counter[str] = collections.Counter()
    module_self: collections.Counter[str] = collections.Counter()
    stacks: list[tuple[str, ...]] = []
    depth_total = 0
    rejected = 0
    capped = 0
    waiting = 0

    for _tid, _qpc, flags, frames in thread_samples:
        depth_total += len(frames)
        if flags & FLAG_WALK_REJECTED:
            rejected += 1
        if flags & FLAG_DEPTH_CAPPED:
            capped += 1
        names = tuple(symbolizer.symbol(address) for address in frames)
        leaf = names[0]
        self_counts[leaf] += 1
        module_self[symbolizer.module_name(frames[0])] += 1
        if any(token in leaf for token in WAIT_SYMBOLS):
            waiting += 1
        for name in set(names):
            inclusive_counts[name] += 1
        stacks.append(tuple(reversed(names)))

    duration = ((window[1] - window[0]).total_seconds() if window else
                (capture.local_time(thread_samples[-1][1]) -
                 capture.local_time(thread_samples[0][1])).total_seconds())
    busy = total - waiting

    print("=== %s ===" % label)
    print("capture           : %s" % args.capture)
    print("process id        : %d   requestedHz=%d  maxDepth=%d  cleanShutdown=%s" % (
        capture.process_id, capture.requested_hz, capture.max_depth, capture.saw_end))
    print("window            : %s" % (
        "%s .. %s" % (window[0], window[1]) if window else "whole capture"))
    print("window duration   : %.3f s" % duration)
    print("threads in window : %s" % ", ".join(
        "%d(%d)" % (tid, count) for tid, count in per_thread.most_common()))
    print("analysed thread   : %d  samples=%d  effectiveHz=%.1f" % (
        target, total, total / duration if duration else 0.0))
    print("stack quality     : meanDepth=%.2f walkTruncated=%.1f%% depthCapped=%.1f%%" % (
        depth_total / total, 100.0 * rejected / total, 100.0 * capped / total))
    print("thread state      : busy=%.2f%%  waiting=%.2f%%  (leaf in a kernel wait)" % (
        100.0 * busy / total, 100.0 * waiting / total))
    if capture.stats:
        final = capture.stats[-1]
        print("sampler health    : ticksRequested=%d ticksServiced=%d "
              "suspendFailures=%d contextFailures=%d suspendOverhead=%.2f%%" % (
                  final["ticks_requested"], final["ticks_serviced"],
                  final["suspend_failures"], final["context_failures"],
                  100.0 * final["suspend_qpc"] / (final["elapsed_qpc"] or 1)))

    if not args.quiet:
        print("\n-- module self time (analysed thread) --")
        for module, count in module_self.most_common():
            print("  %-40s %8d  %6.2f%%" % (module, count, 100.0 * count / total))

        print("\n-- top self time --")
        for name, count in self_counts.most_common(args.top):
            print("  %-64s %8d  %6.2f%%" % (name[:64], count, 100.0 * count / total))

        print("\n-- top inclusive time --")
        for name, count in inclusive_counts.most_common(args.top):
            print("  %-64s %8d  %6.2f%%" % (name[:64], count, 100.0 * count / total))

        print("\n-- per-thread CPU from GetThreadTimes (whole capture) --")
        totals: dict[int, int] = {}
        sampled: dict[int, bool] = {}
        for entry in capture.thread_passes:
            totals[entry["tid"]] = max(totals.get(entry["tid"], 0),
                                       entry["cpu_total_100ns"])
            sampled[entry["tid"]] = sampled.get(entry["tid"], False) or entry["sampled"]
        for tid, cpu in sorted(totals.items(), key=lambda kv: -kv[1])[:20]:
            print("  tid=%-6d cpuTotal=%9.1f ms   everSampled=%s" % (
                tid, cpu / 10000.0, sampled[tid]))

    if args.tree > 0.0:
        print("\n-- call tree (root first, pruned below %.2f%%) --" % args.tree)
        print_tree(build_tree(stacks), total, args.tree, 0, args.tree_depth)

    if args.csv:
        with open(args.csv + "_self.csv", "w", newline="", encoding="utf-8") as handle:
            writer = csv.writer(handle)
            writer.writerow(["label", "thread", "symbol", "module", "self_samples",
                             "self_percent", "total_samples", "window_seconds"])
            for name, count in self_counts.most_common():
                writer.writerow([label, target, name, name.split("!")[0].split("+")[0],
                                 count, round(100.0 * count / total, 4), total,
                                 round(duration, 3)])
        with open(args.csv + "_inclusive.csv", "w", newline="", encoding="utf-8") as handle:
            writer = csv.writer(handle)
            writer.writerow(["label", "thread", "symbol", "inclusive_samples",
                             "inclusive_percent", "total_samples", "window_seconds"])
            for name, count in inclusive_counts.most_common():
                writer.writerow([label, target, name, count,
                                 round(100.0 * count / total, 4), total,
                                 round(duration, 3)])
        print("\nwrote %s_self.csv and %s_inclusive.csv" % (args.csv, args.csv))
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
