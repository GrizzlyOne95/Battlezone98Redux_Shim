import argparse
import ctypes
import glob
import json
import os
import shutil
import subprocess
import sys
import time
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Any

from mcp.server.fastmcp import FastMCP


kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)

TH32CS_SNAPPROCESS = 0x00000002
PROCESS_QUERY_INFORMATION = 0x0400
PROCESS_VM_READ = 0x0010


class PROCESSENTRY32W(ctypes.Structure):
    _fields_ = [
        ("dwSize", ctypes.c_uint32),
        ("cntUsage", ctypes.c_uint32),
        ("th32ProcessID", ctypes.c_uint32),
        ("th32DefaultHeapID", ctypes.c_size_t),
        ("th32ModuleID", ctypes.c_uint32),
        ("cntThreads", ctypes.c_uint32),
        ("th32ParentProcessID", ctypes.c_uint32),
        ("pcPriClassBase", ctypes.c_long),
        ("dwFlags", ctypes.c_uint32),
        ("szExeFile", ctypes.c_wchar * 260),
    ]


kernel32.CreateToolhelp32Snapshot.argtypes = [ctypes.c_uint32, ctypes.c_uint32]
kernel32.CreateToolhelp32Snapshot.restype = ctypes.c_void_p
kernel32.Process32FirstW.argtypes = [ctypes.c_void_p, ctypes.POINTER(PROCESSENTRY32W)]
kernel32.Process32FirstW.restype = ctypes.c_int
kernel32.Process32NextW.argtypes = [ctypes.c_void_p, ctypes.POINTER(PROCESSENTRY32W)]
kernel32.Process32NextW.restype = ctypes.c_int
kernel32.CloseHandle.argtypes = [ctypes.c_void_p]
kernel32.CloseHandle.restype = ctypes.c_int
kernel32.OpenProcess.argtypes = [ctypes.c_uint32, ctypes.c_int, ctypes.c_uint32]
kernel32.OpenProcess.restype = ctypes.c_void_p
kernel32.ReadProcessMemory.argtypes = [
    ctypes.c_void_p,
    ctypes.c_void_p,
    ctypes.c_void_p,
    ctypes.c_size_t,
    ctypes.POINTER(ctypes.c_size_t),
]
kernel32.ReadProcessMemory.restype = ctypes.c_int


REPO_ROOT = Path(__file__).resolve().parents[1]
DEFAULT_STATE_PATH = Path.home() / ".codex" / "tmp" / "redux_debug_bridge_state.json"
DEFAULT_SETTLE_SECONDS = 15.0


@dataclass
class SessionInfo:
    backend: str
    game_exe: str
    game_dir: str
    game_args: list[str]
    controller_pid: int | None
    target_pid: int
    launch_time: float


def candidate_game_dirs() -> list[Path]:
    user_profile = Path(os.environ.get("USERPROFILE", ""))
    dirs: list[Path] = []
    explicit = os.environ.get("BZR_GAME_DIR") or os.environ.get("BZR_REDUX_GAME_DIR")
    if explicit:
        dirs.append(Path(explicit))
    if user_profile:
        dirs.append(user_profile / "Documents" / "Battlezone 98 Redux")
    dirs.append(Path("C:/GOG Games/Battlezone 98 Redux"))
    return dirs


def resolve_game_dir(path: str | None = None) -> Path:
    if path:
        return Path(path)

    for candidate in candidate_game_dirs():
        if (candidate / "battlezone98redux.exe").exists():
            return candidate

    return candidate_game_dirs()[0]


def resolve_game_exe(path: str | None = None, game_dir: Path | None = None) -> Path:
    if path:
        return Path(path)

    explicit = os.environ.get("BZR_GAME_EXE") or os.environ.get("BZR_REDUX_EXE")
    if explicit:
        return Path(explicit)

    root = game_dir or resolve_game_dir()
    return root / "battlezone98redux.exe"


def parse_address(text: str | int) -> int:
    if isinstance(text, int):
        return text
    return int(str(text), 0)


def split_argline(argline: str | None) -> list[str]:
    if not argline:
        return []
    return [part for part in argline.split(" ") if part]


def iter_processes() -> list[dict[str, int | str]]:
    snapshot = kernel32.CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)
    if snapshot == ctypes.c_void_p(-1).value:
        raise OSError(ctypes.get_last_error(), "CreateToolhelp32Snapshot failed")

    try:
        entry = PROCESSENTRY32W()
        entry.dwSize = ctypes.sizeof(PROCESSENTRY32W)
        rows: list[dict[str, int | str]] = []
        if kernel32.Process32FirstW(snapshot, ctypes.byref(entry)):
            while True:
                rows.append(
                    {
                        "pid": int(entry.th32ProcessID),
                        "parent_pid": int(entry.th32ParentProcessID),
                        "exe": entry.szExeFile,
                    }
                )
                if not kernel32.Process32NextW(snapshot, ctypes.byref(entry)):
                    break
        return rows
    finally:
        kernel32.CloseHandle(snapshot)


def process_map() -> dict[int, dict[str, int | str]]:
    return {int(row["pid"]): row for row in iter_processes()}


def ancestor_chain_contains(pid: int, ancestor_pid: int, table: dict[int, dict[str, int | str]]) -> bool:
    visited: set[int] = set()
    current = pid
    while current and current not in visited:
        if current == ancestor_pid:
            return True
        visited.add(current)
        row = table.get(current)
        if not row:
            return False
        current = int(row["parent_pid"])
    return False


def process_alive(pid: int | None) -> bool:
    if not pid:
        return False
    return pid in process_map()


def latest_windbg_root() -> Path | None:
    explicit = os.environ.get("BZR_WINDBG_ROOT")
    if explicit:
        candidate = Path(explicit)
        if candidate.exists():
            return candidate

    try:
        result = subprocess.run(
            [
                "powershell",
                "-NoProfile",
                "-Command",
                "(Get-AppxPackage Microsoft.WinDbg | Select-Object -ExpandProperty InstallLocation)",
            ],
            check=False,
            capture_output=True,
            text=True,
        )
        path = result.stdout.strip()
        if path:
            candidate = Path(path)
            if candidate.exists():
                return candidate
    except OSError:
        pass

    fallback = Path(r"C:\Program Files\WindowsApps\Microsoft.WinDbg_1.2601.12001.0_x64__8wekyb3d8bbwe")
    if fallback.exists():
        return fallback

    return None


def find_cdb_x86() -> Path | None:
    env_value = os.environ.get("BZR_CDB_PATH")
    if env_value and Path(env_value).exists():
        return Path(env_value)

    windbg_root = latest_windbg_root()
    if windbg_root:
        candidate = windbg_root / "x86" / "cdb.exe"
        if candidate.exists():
            return candidate

    for pattern in [
        r"C:\Program Files (x86)\Windows Kits\10\Debuggers\x86\cdb.exe",
        r"C:\Program Files\WindowsApps\Microsoft.WinDbg_*_x64__8wekyb3d8bbwe\x86\cdb.exe",
    ]:
        matches = [Path(path) for path in glob.glob(pattern)]
        if matches:
            return matches[-1]

    return None


def find_x32dbg() -> Path | None:
    env_value = os.environ.get("BZR_X32DBG_PATH")
    if env_value and Path(env_value).exists():
        return Path(env_value)

    direct = shutil.which("x32dbg.exe")
    if direct:
        return Path(direct)

    sibling = shutil.which("x64dbg.exe")
    if sibling:
        sibling_path = Path(sibling)
        candidate = sibling_path.with_name("x32dbg.exe")
        if candidate.exists():
            return candidate

    user_profile = Path(os.environ.get("USERPROFILE", ""))
    local_app_data = Path(os.environ.get("LOCALAPPDATA", ""))
    candidates = []
    if local_app_data:
        candidates.append(
            local_app_data
            / "Microsoft"
            / "WinGet"
            / "Packages"
            / "x64dbg.x64dbg_Microsoft.Winget.Source_8wekyb3d8bbwe"
            / "release"
            / "x32"
            / "x32dbg.exe"
        )

    if user_profile:
        candidates.extend(
            Path(path)
            for path in glob.glob(
                str(
                    user_profile
                    / "AppData"
                    / "Local"
                    / "Microsoft"
                    / "WinGet"
                    / "Packages"
                    / "x64dbg.x64dbg_*"
                    / "release"
                    / "x32"
                    / "x32dbg.exe"
                )
            )
        )

    for candidate in candidates:
        if candidate.exists():
            return candidate

    return None


def detect_backend(preferred: str) -> str:
    if preferred != "auto":
        return preferred
    if find_cdb_x86():
        return "cdb"
    if find_x32dbg():
        return "x64dbg"
    return "native"


def load_state(state_path: Path) -> dict[str, Any]:
    if not state_path.exists():
        return {}
    return json.loads(state_path.read_text(encoding="utf-8"))


def save_state(state_path: Path, payload: dict[str, Any]) -> None:
    state_path.parent.mkdir(parents=True, exist_ok=True)
    state_path.write_text(json.dumps(payload, indent=2), encoding="utf-8")


def launch_process(command: list[str], cwd: Path) -> subprocess.Popen[Any]:
    return subprocess.Popen(command, cwd=str(cwd))


def wait_for_descendant_process(root_pid: int, exe_name: str, timeout_seconds: float) -> int:
    deadline = time.time() + timeout_seconds
    exe_name = exe_name.lower()

    while time.time() < deadline:
        table = process_map()
        for row in table.values():
            pid = int(row["pid"])
            name = str(row["exe"]).lower()
            if name != exe_name:
                continue
            if ancestor_chain_contains(pid, root_pid, table):
                return pid
        time.sleep(0.25)

    raise RuntimeError(f"Timed out waiting for descendant process '{exe_name}' under PID {root_pid}")


def launch_session(
    backend: str = "auto",
    exe_path: str | None = None,
    game_dir: str | None = None,
    argline: str | None = "/nointro",
    wait_seconds: float = DEFAULT_SETTLE_SECONDS,
    state_path: Path = DEFAULT_STATE_PATH,
) -> dict[str, Any]:
    resolved_game_dir = resolve_game_dir(game_dir)
    resolved_game_exe = resolve_game_exe(exe_path, resolved_game_dir)
    resolved_backend = detect_backend(backend)
    game_args = split_argline(argline)
    launch_time = time.time()

    if resolved_backend == "native":
        controller = launch_process([str(resolved_game_exe), *game_args], resolved_game_dir)
        target_pid = controller.pid
        controller_pid: int | None = None
    elif resolved_backend in ("cdb", "windbg"):
        cdb = find_cdb_x86()
        if not cdb:
            raise FileNotFoundError("Could not locate x86 cdb.exe from the installed WinDbg package")
        controller = launch_process(
            [str(cdb), "-o", "-G", "-g", str(resolved_game_exe), *game_args],
            resolved_game_dir,
        )
        controller_pid = controller.pid
        target_pid = wait_for_descendant_process(controller.pid, resolved_game_exe.name.lower(), wait_seconds)
    elif resolved_backend == "x64dbg":
        x32dbg = find_x32dbg()
        if not x32dbg:
            raise FileNotFoundError("Could not locate x32dbg.exe")
        controller = launch_process([str(x32dbg), str(resolved_game_exe), *game_args], resolved_game_dir)
        controller_pid = controller.pid
        target_pid = wait_for_descendant_process(controller.pid, resolved_game_exe.name.lower(), wait_seconds)
    else:
        raise ValueError(f"Unsupported backend: {resolved_backend}")

    remaining = launch_time + wait_seconds - time.time()
    if remaining > 0:
        time.sleep(remaining)

    session = SessionInfo(
        backend=resolved_backend,
        game_exe=str(resolved_game_exe),
        game_dir=str(resolved_game_dir),
        game_args=game_args,
        controller_pid=controller_pid,
        target_pid=target_pid,
        launch_time=launch_time,
    )
    payload = asdict(session)
    save_state(state_path, payload)
    return payload


def read_process_memory(pid: int, address: int, length: int) -> bytes:
    handle = kernel32.OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 0, pid)
    if not handle:
        raise OSError(ctypes.get_last_error(), f"OpenProcess failed for PID {pid}")

    try:
        buffer = ctypes.create_string_buffer(length)
        bytes_read = ctypes.c_size_t(0)
        ok = kernel32.ReadProcessMemory(
            handle,
            ctypes.c_void_p(address),
            buffer,
            length,
            ctypes.byref(bytes_read),
        )
        if not ok:
            raise OSError(ctypes.get_last_error(), f"ReadProcessMemory failed at 0x{address:08X}")
        return buffer.raw[: bytes_read.value]
    finally:
        kernel32.CloseHandle(handle)


def format_bytes(data: bytes, render_as: str) -> str:
    if render_as == "ascii":
        return "".join(chr(byte) if 32 <= byte <= 126 else "." for byte in data)
    return " ".join(f"{byte:02X}" for byte in data)


def read_memory_command(
    address: str,
    length: int = 16,
    pid: int | None = None,
    render_as: str = "hex",
    state_path: Path = DEFAULT_STATE_PATH,
) -> dict[str, Any]:
    session = load_state(state_path)
    target_pid = pid or int(session.get("target_pid", 0))
    if not target_pid:
        raise RuntimeError("No target PID supplied and no saved session is available")

    parsed_address = parse_address(address)
    data = read_process_memory(target_pid, parsed_address, length)
    return {
        "pid": target_pid,
        "address": f"0x{parsed_address:08X}",
        "length": len(data),
        "bytes": format_bytes(data, render_as),
        "render_as": render_as,
    }


def terminate_session(state_path: Path = DEFAULT_STATE_PATH) -> dict[str, Any]:
    state = load_state(state_path)
    controller_pid = int(state.get("controller_pid") or 0)
    target_pid = int(state.get("target_pid") or 0)

    killed: list[int] = []
    for pid in [controller_pid, target_pid]:
        if not pid or pid in killed:
            continue
        if process_alive(pid):
            subprocess.run(
                ["taskkill", "/PID", str(pid), "/T", "/F"],
                check=False,
                capture_output=True,
                text=True,
            )
            killed.append(pid)

    save_state(state_path, {})
    return {"killed_pids": killed}


def doctor() -> dict[str, Any]:
    game_dir = resolve_game_dir()
    game_exe = resolve_game_exe(None, game_dir)
    windbg_root = latest_windbg_root()
    cdb_x86 = find_cdb_x86()
    x32dbg = find_x32dbg()
    return {
        "repo_root": str(REPO_ROOT),
        "game_dir": str(game_dir),
        "game_exe": str(game_exe),
        "game_exe_exists": game_exe.exists(),
        "windbg_root": str(windbg_root) if windbg_root else "",
        "cdb_x86": str(cdb_x86) if cdb_x86 else "",
        "x32dbg": str(x32dbg) if x32dbg else "",
        "state_path": str(DEFAULT_STATE_PATH),
    }


def probe_addresses(
    addresses: list[str],
    backend: str = "auto",
    exe_path: str | None = None,
    game_dir: str | None = None,
    argline: str | None = "/nointro",
    wait_seconds: float = DEFAULT_SETTLE_SECONDS,
    length: int = 16,
    state_path: Path = DEFAULT_STATE_PATH,
) -> dict[str, Any]:
    session = launch_session(
        backend=backend,
        exe_path=exe_path,
        game_dir=game_dir,
        argline=argline,
        wait_seconds=wait_seconds,
        state_path=state_path,
    )

    results = []
    try:
        for address in addresses:
            results.append(read_memory_command(address, length, int(session["target_pid"]), "hex", state_path))
    finally:
        terminate_session(state_path)

    return {"session": session, "reads": results}


def build_mcp_server() -> FastMCP:
    mcp = FastMCP("redux-debug-bridge")

    @mcp.tool()
    def doctor_tool() -> dict[str, Any]:
        return doctor()

    @mcp.tool()
    def launch_session_tool(
        backend: str = "auto",
        exe_path: str = "",
        game_dir: str = "",
        argline: str = "/nointro",
        wait_seconds: float = DEFAULT_SETTLE_SECONDS,
    ) -> dict[str, Any]:
        return launch_session(
            backend=backend,
            exe_path=exe_path or None,
            game_dir=game_dir or None,
            argline=argline,
            wait_seconds=wait_seconds,
        )

    @mcp.tool()
    def read_memory_tool(
        address: str,
        length: int = 16,
        pid: int = 0,
        render_as: str = "hex",
    ) -> dict[str, Any]:
        return read_memory_command(
            address=address,
            length=length,
            pid=pid or None,
            render_as=render_as,
        )

    @mcp.tool()
    def terminate_session_tool() -> dict[str, Any]:
        return terminate_session()

    @mcp.tool()
    def probe_addresses_tool(
        addresses_csv: str,
        backend: str = "auto",
        argline: str = "/nointro",
        wait_seconds: float = DEFAULT_SETTLE_SECONDS,
        length: int = 16,
    ) -> dict[str, Any]:
        addresses = [item.strip() for item in addresses_csv.split(",") if item.strip()]
        return probe_addresses(
            addresses=addresses,
            backend=backend,
            argline=argline,
            wait_seconds=wait_seconds,
            length=length,
        )

    return mcp


def print_payload(payload: dict[str, Any]) -> int:
    print(json.dumps(payload, indent=2))
    return 0


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="CLI and MCP bridge for Battlezone Redux debug sessions.")
    subparsers = parser.add_subparsers(dest="command", required=True)

    doctor_parser = subparsers.add_parser("doctor", help="Report discovered debugger and game paths.")
    doctor_parser.set_defaults(func=lambda _args: print_payload(doctor()))

    launch_parser = subparsers.add_parser("launch", help="Launch Redux through the chosen backend.")
    launch_parser.add_argument("--backend", default="auto", choices=("auto", "native", "cdb", "windbg", "x64dbg"))
    launch_parser.add_argument("--exe-path", default="")
    launch_parser.add_argument("--game-dir", default="")
    launch_parser.add_argument("--argline", default="/nointro")
    launch_parser.add_argument("--wait-seconds", type=float, default=DEFAULT_SETTLE_SECONDS)
    launch_parser.set_defaults(
        func=lambda args: print_payload(
            launch_session(
                backend=args.backend,
                exe_path=args.exe_path or None,
                game_dir=args.game_dir or None,
                argline=args.argline,
                wait_seconds=args.wait_seconds,
            )
        )
    )

    read_parser = subparsers.add_parser("read", help="Read memory from the active or supplied PID.")
    read_parser.add_argument("address")
    read_parser.add_argument("--length", type=int, default=16)
    read_parser.add_argument("--pid", type=int, default=0)
    read_parser.add_argument("--render-as", choices=("hex", "ascii"), default="hex")
    read_parser.set_defaults(
        func=lambda args: print_payload(
            read_memory_command(
                address=args.address,
                length=args.length,
                pid=args.pid or None,
                render_as=args.render_as,
            )
        )
    )

    probe_parser = subparsers.add_parser("probe", help="Launch, read one or more addresses, then terminate.")
    probe_parser.add_argument("addresses", nargs="+")
    probe_parser.add_argument("--backend", default="auto", choices=("auto", "native", "cdb", "windbg", "x64dbg"))
    probe_parser.add_argument("--exe-path", default="")
    probe_parser.add_argument("--game-dir", default="")
    probe_parser.add_argument("--argline", default="/nointro")
    probe_parser.add_argument("--wait-seconds", type=float, default=DEFAULT_SETTLE_SECONDS)
    probe_parser.add_argument("--length", type=int, default=16)
    probe_parser.set_defaults(
        func=lambda args: print_payload(
            probe_addresses(
                addresses=args.addresses,
                backend=args.backend,
                exe_path=args.exe_path or None,
                game_dir=args.game_dir or None,
                argline=args.argline,
                wait_seconds=args.wait_seconds,
                length=args.length,
            )
        )
    )

    status_parser = subparsers.add_parser("status", help="Print the saved session state.")
    status_parser.set_defaults(func=lambda _args: print_payload(load_state(DEFAULT_STATE_PATH)))

    terminate_parser = subparsers.add_parser("terminate", help="Terminate the active session.")
    terminate_parser.set_defaults(func=lambda _args: print_payload(terminate_session()))

    mcp_parser = subparsers.add_parser("mcp", help="Run the bridge as a FastMCP server.")
    mcp_parser.add_argument("--transport", choices=("stdio", "sse", "streamable-http"), default="stdio")
    mcp_parser.set_defaults(func=None)
    return parser


def main() -> int:
    parser = build_parser()
    args = parser.parse_args()
    if args.command == "mcp":
        build_mcp_server().run(transport=args.transport)
        return 0
    return int(args.func(args))


if __name__ == "__main__":
    raise SystemExit(main())
