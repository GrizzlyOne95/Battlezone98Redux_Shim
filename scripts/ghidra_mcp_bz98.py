import argparse
import os
import subprocess
import sys
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[1]
DEFAULT_PROJECT_PATH = REPO_ROOT / "pyghidra_mcp_projects"
DEFAULT_PROJECT_NAME = "BZ98_Redux"
DEFAULT_GHIDRA_INSTALL_DIR = Path("C:/ghidra_12.0.4_PUBLIC")


def candidate_binary_paths() -> list[Path]:
    user_profile = Path(os.environ.get("USERPROFILE", ""))
    paths: list[Path] = []
    explicit_binary = os.environ.get("BZR_GAME_EXE") or os.environ.get("BZR_REDUX_EXE")
    explicit_game_dir = os.environ.get("BZR_GAME_DIR") or os.environ.get("BZR_REDUX_GAME_DIR")

    if explicit_binary:
        paths.append(Path(explicit_binary))
    if explicit_game_dir:
        paths.append(Path(explicit_game_dir) / "battlezone98redux.exe")

    if user_profile:
        paths.append(user_profile / "Documents" / "Battlezone 98 Redux" / "battlezone98redux.exe")
        paths.append(user_profile / "Downloads" / "Battlezone 98 Redux" / "battlezone98redux.exe")

    paths.append(Path("C:/GOG Games/Battlezone 98 Redux/battlezone98redux.exe"))
    return paths


def resolve_default_binary() -> Path:
    for path in candidate_binary_paths():
        if path.exists():
            return path
    return candidate_binary_paths()[0]


def build_command(args: argparse.Namespace) -> list[str]:
    command = [sys.executable, "-m", "pyghidra_mcp"]

    command += [
        "--project-path",
        str(args.project_path),
        "--project-name",
        args.project_name,
        "--transport",
        args.transport,
    ]

    if args.host:
        command += ["--host", args.host]
    if args.port is not None:
        command += ["--port", str(args.port)]
    if args.wait_for_analysis:
        command.append("--wait-for-analysis")
    if args.force_analysis:
        command.append("--force-analysis")
    if args.no_symbols:
        command.append("--no-symbols")
    if args.verbose_analysis:
        command.append("--verbose-analysis")
    if args.symbols_path:
        command += ["--symbols-path", str(args.symbols_path)]
    if args.sym_file_path:
        command += ["--sym-file-path", str(args.sym_file_path)]
    if args.gzfs_path:
        command += ["--gzfs-path", str(args.gzfs_path)]

    command.append(str(args.binary))
    command += args.extra_args
    return command


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Battlezone 98 Redux wrapper for pyghidra_mcp."
    )
    parser.add_argument(
        "--binary",
        type=Path,
        default=resolve_default_binary(),
        help="Binary to expose through pyghidra_mcp.",
    )
    parser.add_argument(
        "--project-path",
        type=Path,
        default=DEFAULT_PROJECT_PATH,
        help="Ghidra project directory or .gpr path.",
    )
    parser.add_argument(
        "--project-name",
        default=DEFAULT_PROJECT_NAME,
        help="Project name when creating a project directory.",
    )
    parser.add_argument(
        "--transport",
        choices=("stdio", "streamable-http", "sse", "http"),
        default="stdio",
        help="pyghidra_mcp transport.",
    )
    parser.add_argument("--host", default="127.0.0.1")
    parser.add_argument("--port", type=int, default=8000)
    parser.add_argument("--wait-for-analysis", action="store_true")
    parser.add_argument("--force-analysis", action="store_true")
    parser.add_argument("--no-symbols", action="store_true")
    parser.add_argument("--verbose-analysis", action="store_true")
    parser.add_argument("--symbols-path", type=Path, default=None)
    parser.add_argument("--sym-file-path", type=Path, default=None)
    parser.add_argument("--gzfs-path", type=Path, default=None)
    parser.add_argument(
        "--ghidra-install-dir",
        type=Path,
        default=Path(
            os.environ.get(
                "BZR_GHIDRA_INSTALL_DIR",
                os.environ.get("GHIDRA_INSTALL_DIR", str(DEFAULT_GHIDRA_INSTALL_DIR)),
            )
        ),
        help="Sets GHIDRA_INSTALL_DIR for the launched MCP process.",
    )
    args, unknown = parser.parse_known_args()
    args.extra_args = unknown
    return args


def main() -> int:
    args = parse_args()

    env = os.environ.copy()
    if args.ghidra_install_dir:
        env["GHIDRA_INSTALL_DIR"] = str(args.ghidra_install_dir)

    args.project_path.mkdir(parents=True, exist_ok=True)
    command = build_command(args)
    return subprocess.call(command, env=env)


if __name__ == "__main__":
    raise SystemExit(main())
