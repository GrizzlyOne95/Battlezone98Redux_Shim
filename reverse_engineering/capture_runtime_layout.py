from __future__ import annotations

import argparse
import ctypes
import hashlib
import json
import sys
import time
from dataclasses import dataclass
from datetime import datetime
from pathlib import Path
from typing import Any

import pefile
import psutil
from ctypes import wintypes


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

GOG_SAVEGAME_SIGNATURE = (
    "55 8B EC 81 EC 94 00 00 00 C6 45 FF 01 E8 ?? ?? ?? ?? "
    "89 85 78 FF FF FF 68 ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 C4 04 "
    "0F B6 05 ?? ?? ?? ?? 85 C0 0F 84 ?? ?? ?? ?? 6A 2E"
)

ALLOWED_PROCESS_NAMES = {"battlezone98redux.exe", "bzr.exe"}

PROCESS_QUERY_INFORMATION = 0x0400
PROCESS_VM_READ = 0x0010
TH32CS_SNAPMODULE = 0x00000008
TH32CS_SNAPMODULE32 = 0x00000010
INVALID_HANDLE_VALUE = ctypes.c_void_p(-1).value

kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)


class MODULEENTRY32W(ctypes.Structure):
    _fields_ = [
        ("dwSize", wintypes.DWORD),
        ("th32ModuleID", wintypes.DWORD),
        ("th32ProcessID", wintypes.DWORD),
        ("GlblcntUsage", wintypes.DWORD),
        ("ProccntUsage", wintypes.DWORD),
        ("modBaseAddr", ctypes.c_void_p),
        ("modBaseSize", wintypes.DWORD),
        ("hModule", wintypes.HMODULE),
        ("szModule", wintypes.WCHAR * 256),
        ("szExePath", wintypes.WCHAR * 260),
    ]


kernel32.OpenProcess.argtypes = [wintypes.DWORD, wintypes.BOOL, wintypes.DWORD]
kernel32.OpenProcess.restype = wintypes.HANDLE
kernel32.ReadProcessMemory.argtypes = [
    wintypes.HANDLE,
    wintypes.LPCVOID,
    wintypes.LPVOID,
    ctypes.c_size_t,
    ctypes.POINTER(ctypes.c_size_t),
]
kernel32.ReadProcessMemory.restype = wintypes.BOOL
kernel32.CloseHandle.argtypes = [wintypes.HANDLE]
kernel32.CloseHandle.restype = wintypes.BOOL
kernel32.CreateToolhelp32Snapshot.argtypes = [wintypes.DWORD, wintypes.DWORD]
kernel32.CreateToolhelp32Snapshot.restype = wintypes.HANDLE
kernel32.Module32FirstW.argtypes = [wintypes.HANDLE, ctypes.POINTER(MODULEENTRY32W)]
kernel32.Module32FirstW.restype = wintypes.BOOL
kernel32.Module32NextW.argtypes = [wintypes.HANDLE, ctypes.POINTER(MODULEENTRY32W)]
kernel32.Module32NextW.restype = wintypes.BOOL


@dataclass(frozen=True)
class ModuleInfo:
    name: str
    path: str
    base: int
    size: int


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


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
    if plen == 0 or len(data) < plen:
        return hits

    for index in range(0, len(data) - plen + 1):
        for pos in range(plen):
            if mask[pos] and data[index + pos] != pattern[pos]:
                break
        else:
            hits.append(index)
    return hits


def read_process_memory(handle: int, address: int, size: int) -> tuple[bytes, str | None]:
    if size <= 0:
        return b"", None

    buffer = ctypes.create_string_buffer(size)
    bytes_read = ctypes.c_size_t(0)
    ok = kernel32.ReadProcessMemory(
        handle,
        ctypes.c_void_p(address),
        buffer,
        size,
        ctypes.byref(bytes_read),
    )
    read = bytes_read.value
    if not ok and read == 0:
        err = ctypes.get_last_error()
        return b"", f"ReadProcessMemory failed at 0x{address:08X} (error {err})"
    if not ok and read > 0:
        err = ctypes.get_last_error()
        return buffer.raw[:read], f"ReadProcessMemory returned partial data at 0x{address:08X} (error {err})"
    return buffer.raw[:read], None


def enumerate_modules(pid: int) -> list[ModuleInfo]:
    snapshot = kernel32.CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid)
    if snapshot == INVALID_HANDLE_VALUE:
        raise OSError(f"CreateToolhelp32Snapshot failed for pid {pid}: {ctypes.get_last_error()}")

    try:
        entry = MODULEENTRY32W()
        entry.dwSize = ctypes.sizeof(MODULEENTRY32W)
        modules: list[ModuleInfo] = []

        success = kernel32.Module32FirstW(snapshot, ctypes.byref(entry))
        if not success:
            raise OSError(f"Module32FirstW failed for pid {pid}: {ctypes.get_last_error()}")

        while success:
            modules.append(
                ModuleInfo(
                    name=entry.szModule,
                    path=entry.szExePath,
                    base=int(entry.modBaseAddr),
                    size=int(entry.modBaseSize),
                )
            )
            success = kernel32.Module32NextW(snapshot, ctypes.byref(entry))

        return modules
    finally:
        kernel32.CloseHandle(snapshot)


def wait_for_process(process_name: str, timeout: float, poll_interval: float) -> psutil.Process:
    deadline = time.monotonic() + timeout
    target = process_name.lower()
    while True:
        candidates: list[tuple[float, psutil.Process]] = []
        for proc in psutil.process_iter(["pid", "name", "create_time"]):
            try:
                name = (proc.info.get("name") or "").lower()
            except (psutil.NoSuchProcess, psutil.AccessDenied):
                continue
            if name == target:
                created = float(proc.info.get("create_time") or 0.0)
                candidates.append((created, proc))

        if candidates:
            candidates.sort(key=lambda item: item[0], reverse=True)
            return candidates[0][1]

        if time.monotonic() >= deadline:
            raise TimeoutError(f"Timed out waiting for {process_name}")
        time.sleep(poll_interval)


def find_process_by_pid(pid: int) -> psutil.Process:
    proc = psutil.Process(pid)
    if not proc.is_running():
        raise RuntimeError(f"Process {pid} is not running")
    return proc


def find_module(modules: list[ModuleInfo], exe_path: Path) -> ModuleInfo:
    exe_str = str(exe_path).lower()
    for module in modules:
        if module.path.lower() == exe_str:
            return module
    for module in modules:
        if module.name.lower() == exe_path.name.lower():
            return module
    return modules[0]


def find_string_hits(section_name: str, base_rva: int, base_va: int, data: bytes, needle: bytes) -> list[dict[str, Any]]:
    hits: list[dict[str, Any]] = []
    start = 0
    while True:
        index = data.find(needle, start)
        if index < 0:
            return hits
        hits.append(
            {
                "section": section_name,
                "rva": base_rva + index,
                "va": base_va + index,
            }
        )
        start = index + 1


def collect_string_hits(section_payloads: list[dict[str, Any]], labels: tuple[bytes, ...]) -> dict[str, list[dict[str, Any]]]:
    results: dict[str, list[dict[str, Any]]] = {}
    for label in labels:
        decoded = label.decode("ascii", errors="ignore")
        hits: list[dict[str, Any]] = []
        for section in section_payloads:
            hits.extend(
                find_string_hits(
                    section_name=section["name"],
                    base_rva=section["rva"],
                    base_va=section["va"],
                    data=section["runtime_data"],
                    needle=label,
                )
            )
        results[decoded] = hits
    return results


def ensure_allowed_name(name: str) -> None:
    if name.lower() not in ALLOWED_PROCESS_NAMES:
        joined = ", ".join(sorted(ALLOWED_PROCESS_NAMES))
        raise SystemExit(f"Refusing to attach to {name}. Allowed names: {joined}")


def make_output_dir(root: Path) -> Path:
    stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    output_dir = root / f"runtime_capture_{stamp}"
    output_dir.mkdir(parents=True, exist_ok=False)
    return output_dir


def section_display_name(section: pefile.SectionStructure) -> str:
    name = section.Name.rstrip(b"\0").decode("ascii", errors="ignore")
    return name or f"section_{section.VirtualAddress:08X}"


def write_summary(output_dir: Path, report: dict[str, Any]) -> None:
    lines: list[str] = []
    process = report["process"]
    main_module = report["main_module"]
    disk_pe = report["disk_pe"]

    lines.append("# Runtime Capture")
    lines.append("")
    lines.append(f"- Timestamp: {report['captured_at']}")
    lines.append(f"- PID: {process['pid']}")
    lines.append(f"- Process: {process['name']}")
    lines.append(f"- EXE: {process['exe']}")
    lines.append(f"- Main module base: 0x{main_module['base']:08X}")
    lines.append(f"- Main module size: 0x{main_module['size']:X}")
    lines.append(f"- Disk image base: 0x{disk_pe['image_base']:08X}")
    lines.append(f"- Base delta: 0x{disk_pe['base_delta']:X}")
    lines.append(f"- Runtime entrypoint VA: 0x{disk_pe['entrypoint_va']:08X}")
    lines.append("")

    lines.append("## Signature Hits")
    lines.append("")
    hits = report["signatures"].get("gog_savegame_signature", [])
    if hits:
        for hit in hits:
            lines.append(f"- RVA 0x{hit['rva']:08X} VA 0x{hit['va']:08X}")
    else:
        lines.append("- No hits")
    lines.append("")

    lines.append("## Sections")
    lines.append("")
    for section in report["sections"]:
        same = section.get("disk_matches_runtime")
        same_label = "yes" if same else "no"
        lines.append(
            f"- {section['name']}: RVA 0x{section['rva']:08X}, size 0x{section['read_size']:X}, "
            f"disk/runtime match={same_label}"
        )
    lines.append("")

    lines.append("## Save Strings")
    lines.append("")
    for label, label_hits in report["strings"]["save_fields"].items():
        if label_hits:
            first = label_hits[0]
            lines.append(f"- {label}: {first['section']} RVA 0x{first['rva']:08X} VA 0x{first['va']:08X}")
        else:
            lines.append(f"- {label}: not found")
    lines.append("")

    lines.append("## Auto-save Strings")
    lines.append("")
    for label, label_hits in report["strings"]["auto_save"].items():
        if label_hits:
            first = label_hits[0]
            lines.append(f"- {label}: {first['section']} RVA 0x{first['rva']:08X} VA 0x{first['va']:08X}")
        else:
            lines.append(f"- {label}: not found")
    lines.append("")

    (output_dir / "summary.md").write_text("\n".join(lines) + "\n", encoding="utf-8")


def collect_capture(proc: psutil.Process, output_dir: Path, dump_sections: bool) -> dict[str, Any]:
    exe_path = Path(proc.exe())
    ensure_allowed_name(exe_path.name)

    modules = enumerate_modules(proc.pid)
    main_module = find_module(modules, exe_path)

    handle = kernel32.OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, False, proc.pid)
    if not handle:
        raise OSError(f"OpenProcess failed for pid {proc.pid}: {ctypes.get_last_error()}")

    try:
        pe = pefile.PE(str(exe_path), fast_load=False)
        section_payloads: list[dict[str, Any]] = []
        section_reports: list[dict[str, Any]] = []

        for section in pe.sections:
            name = section_display_name(section)
            disk_data = section.get_data()
            read_size = len(disk_data)
            va = main_module.base + section.VirtualAddress
            runtime_data, read_error = read_process_memory(handle, va, read_size)
            runtime_hash = sha256(runtime_data) if runtime_data else None
            disk_hash = sha256(disk_data)

            payload = {
                "name": name,
                "rva": int(section.VirtualAddress),
                "va": int(va),
                "runtime_data": runtime_data,
            }
            section_payloads.append(payload)

            dumped_path = None
            if dump_sections and runtime_data:
                dumped_path = f"sections/{name.strip('.') or name}.bin"
                dump_file = output_dir / dumped_path
                dump_file.parent.mkdir(parents=True, exist_ok=True)
                dump_file.write_bytes(runtime_data)

            section_reports.append(
                {
                    "name": name,
                    "rva": int(section.VirtualAddress),
                    "va": int(va),
                    "disk_raw_size": int(len(disk_data)),
                    "virtual_size": int(section.Misc_VirtualSize),
                    "read_size": int(len(runtime_data)),
                    "disk_sha256": disk_hash,
                    "runtime_sha256": runtime_hash,
                    "disk_matches_runtime": runtime_hash == disk_hash if runtime_hash is not None else None,
                    "read_error": read_error,
                    "dump_path": dumped_path,
                }
            )

        runtime_text = next((section for section in section_payloads if section["name"] == ".text"), None)
        savegame_hits: list[dict[str, int]] = []
        if runtime_text:
            for hit in find_signature_hits(runtime_text["runtime_data"], GOG_SAVEGAME_SIGNATURE):
                savegame_hits.append(
                    {
                        "rva": runtime_text["rva"] + hit,
                        "va": runtime_text["va"] + hit,
                    }
                )

        report = {
            "captured_at": datetime.now().isoformat(timespec="seconds"),
            "process": {
                "pid": proc.pid,
                "name": proc.name(),
                "exe": str(exe_path),
                "cmdline": proc.cmdline(),
                "create_time": datetime.fromtimestamp(proc.create_time()).isoformat(timespec="seconds"),
            },
            "main_module": {
                "name": main_module.name,
                "path": main_module.path,
                "base": main_module.base,
                "size": main_module.size,
            },
            "disk_pe": {
                "image_base": int(pe.OPTIONAL_HEADER.ImageBase),
                "entrypoint_rva": int(pe.OPTIONAL_HEADER.AddressOfEntryPoint),
                "entrypoint_va": int(main_module.base + pe.OPTIONAL_HEADER.AddressOfEntryPoint),
                "size_of_image": int(pe.OPTIONAL_HEADER.SizeOfImage),
                "base_delta": int(main_module.base - pe.OPTIONAL_HEADER.ImageBase),
            },
            "modules": [
                {
                    "name": module.name,
                    "path": module.path,
                    "base": module.base,
                    "size": module.size,
                }
                for module in sorted(modules, key=lambda item: item.base)
            ],
            "sections": section_reports,
            "signatures": {
                "gog_savegame_signature": savegame_hits,
            },
            "strings": {
                "save_fields": collect_string_hits(section_payloads, SAVE_FIELD_STRINGS),
                "auto_save": collect_string_hits(section_payloads, AUTO_SAVE_STRINGS),
            },
        }

        (output_dir / "report.json").write_text(json.dumps(report, indent=2), encoding="utf-8")
        write_summary(output_dir, report)
        return report
    finally:
        kernel32.CloseHandle(handle)


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Capture Battlezone runtime module layout and scan the live image for known reverse-engineering anchors."
    )
    parser.add_argument(
        "--process-name",
        default="battlezone98redux.exe",
        help="Process name to wait for. Allowed names are battlezone98redux.exe and BZR.exe.",
    )
    parser.add_argument("--pid", type=int, help="Attach to an already running process id instead of waiting by name.")
    parser.add_argument(
        "--timeout",
        type=float,
        default=120.0,
        help="How long to wait for the target process, in seconds.",
    )
    parser.add_argument(
        "--poll-interval",
        type=float,
        default=1.0,
        help="How often to poll for the target process while waiting.",
    )
    parser.add_argument(
        "--output-root",
        type=Path,
        default=Path("reverse_engineering/snapshots"),
        help="Directory that will receive the timestamped runtime capture folder.",
    )
    parser.add_argument(
        "--no-dump-sections",
        action="store_true",
        help="Skip writing raw runtime section dumps to disk.",
    )
    return parser


def main() -> int:
    parser = build_parser()
    args = parser.parse_args()

    if args.pid is not None:
        proc = find_process_by_pid(args.pid)
    else:
        ensure_allowed_name(args.process_name)
        proc = wait_for_process(args.process_name, timeout=args.timeout, poll_interval=args.poll_interval)

    output_dir = make_output_dir(args.output_root)
    report = collect_capture(proc, output_dir=output_dir, dump_sections=not args.no_dump_sections)

    print(f"Captured runtime layout for pid {report['process']['pid']} -> {output_dir}")
    print(f"Main module base: 0x{report['main_module']['base']:08X}")
    hits = report["signatures"]["gog_savegame_signature"]
    if hits:
        for hit in hits:
            print(f"GOG SaveGame signature hit at RVA 0x{hit['rva']:08X} VA 0x{hit['va']:08X}")
    else:
        print("GOG SaveGame signature: no hits")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except TimeoutError as exc:
        print(str(exc), file=sys.stderr)
        raise SystemExit(1)
