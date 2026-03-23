import argparse
import csv
import ctypes
import http.client
import json
import os
import re
import runpy
import subprocess
import sys
import time
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[1]
DEFAULT_PROJECT_PATH = REPO_ROOT / "pyghidra_mcp_projects"
DEFAULT_PROJECT_NAME = "BZ98_Redux"
DEFAULT_GHIDRA_INSTALL_DIR = Path("C:/ghidra_12.0.4_PUBLIC")
DEFAULT_SERVICE_HOST = "127.0.0.1"
DEFAULT_SERVICE_PORT = 8765
DEFAULT_SERVICE_PATH = "/mcp"
DEFAULT_SERVICE_LOG_PATH = (
    Path(os.environ.get("LOCALAPPDATA", str(REPO_ROOT)))
    / "BZR-OpenShim"
    / "logs"
    / "ghidra_mcp.log"
)
DEFAULT_ADVISORY_CORPUS_ROOT = REPO_ROOT / "reverse_engineering" / "current_global_corpus"
DEFAULT_ADVISORY_REPO_CORPUS_ROOT = (
    REPO_ROOT / "reverse_engineering" / "repo_corpora" / "bzr_gog_best_effort"
)
DEFAULT_ADVISORY_PIPELINE_ROOT = (
    REPO_ROOT / "reverse_engineering" / "workshop" / "global_decompile" / "bzr_gog_best_effort"
)
ADVISORY_SYMBOL_OPTIONS_NAME = "BZR OpenShim"
ADVISORY_SYMBOL_VERSION_KEY = "redux_advisory_symbols_version"
ADVISORY_SYMBOL_VERSION = "2026-03-23b"
_FRIENDLY_LABEL_RE = re.compile(r"([A-Za-z_~][\w~]*(?:::(?:`[^']+'|[A-Za-z_~][\w~]*))+)")
_SANITIZE_LABEL_RE = re.compile(r"[^0-9A-Za-z_]+")
_UNDNAME_CACHE: dict[str, str] = {}
_ADVISORY_SYMBOL_CACHE: dict[str, dict[str, object] | None] = {}


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


def build_pyghidra_args(args: argparse.Namespace) -> list[str]:
    command = [
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
        "--ensure-service",
        action="store_true",
        help="Start or reuse a persistent localhost streamable-http MCP service.",
    )
    parser.add_argument(
        "--service-host",
        default=DEFAULT_SERVICE_HOST,
        help="Host for the persistent streamable-http MCP service.",
    )
    parser.add_argument(
        "--service-port",
        type=int,
        default=DEFAULT_SERVICE_PORT,
        help="Port for the persistent streamable-http MCP service.",
    )
    parser.add_argument(
        "--service-log-path",
        type=Path,
        default=DEFAULT_SERVICE_LOG_PATH,
        help="Log file used when background-launching the persistent MCP service.",
    )
    parser.add_argument(
        "--service-startup-timeout",
        type=float,
        default=90.0,
        help="Seconds to wait for the persistent MCP service to accept connections.",
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
    parser.add_argument(
        "--no-advisory-symbols",
        action="store_true",
        help="Skip applying advisory Redux labels from the local promoted corpus.",
    )
    parser.add_argument(
        "--advisory-corpus-root",
        type=Path,
        default=None,
        help="Optional promoted corpus root or pipeline output root for advisory Redux labels.",
    )
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


def normalize_exit_code(value: object) -> int:
    if value is None:
        return 0
    if isinstance(value, int):
        return value
    return 1


def _load_json_file(path: Path) -> dict | None:
    if not path.exists():
        return None
    with path.open("r", encoding="utf-8") as handle:
        return json.load(handle)


def _resolve_advisory_symbol_root(root_override: Path | None) -> Path | None:
    candidates: list[Path] = []
    if root_override:
        candidates.append(root_override)
    candidates.append(DEFAULT_ADVISORY_CORPUS_ROOT)
    candidates.append(DEFAULT_ADVISORY_REPO_CORPUS_ROOT)
    candidates.append(DEFAULT_ADVISORY_PIPELINE_ROOT)

    for candidate in candidates:
        candidate = candidate.resolve()
        manifest = None
        if candidate.is_file():
            manifest = _load_json_file(candidate)
            if manifest:
                output_root = manifest.get("output_root")
                if output_root:
                    resolved = Path(output_root)
                    if not resolved.is_absolute():
                        resolved = (candidate.parent / resolved).resolve()
                    if resolved.exists():
                        return resolved
            continue

        current_manifest = candidate / "current_manifest.json"
        if current_manifest.exists():
            manifest = _load_json_file(current_manifest)
        else:
            pipeline_manifest = candidate / "pipeline_manifest.json"
            if pipeline_manifest.exists():
                manifest = _load_json_file(pipeline_manifest)

        if manifest:
            output_root = manifest.get("output_root")
            if output_root:
                resolved = Path(output_root)
                if not resolved.is_absolute():
                    resolved = (candidate / resolved).resolve()
                if resolved.exists():
                    return resolved

        if (
            (candidate / "pdb_reference" / "public_functions.csv").exists()
            or (candidate / "merged" / "function_matches_by_rva.csv").exists()
        ):
            return candidate

    return None


def _undecorate_symbol_name(raw_name: str) -> str:
    cached = _UNDNAME_CACHE.get(raw_name)
    if cached is not None:
        return cached

    result = raw_name
    try:
        buffer = ctypes.create_string_buffer(4096)
        converted = ctypes.windll.dbghelp.UnDecorateSymbolName(  # type: ignore[attr-defined]
            raw_name.encode("utf-8"),
            buffer,
            len(buffer),
            0,
        )
        if converted:
            result = buffer.value.decode("utf-8", errors="replace")
    except Exception:
        result = raw_name

    _UNDNAME_CACHE[raw_name] = result
    return result


def _sanitize_label_name(text: str) -> str:
    cleaned = (
        text.replace("::", "__")
        .replace("`vftable'", "vftable")
        .replace("`vbtable'", "vbtable")
        .replace("`scalar deleting destructor'", "scalar_deleting_destructor")
        .replace("`vector deleting destructor'", "vector_deleting_destructor")
        .replace("`RTTI Complete Object Locator'", "RTTI_Complete_Object_Locator")
        .replace("`RTTI Type Descriptor'", "RTTI_Type_Descriptor")
    )
    cleaned = _SANITIZE_LABEL_RE.sub("_", cleaned).strip("_")
    cleaned = re.sub(r"_+", "_", cleaned)
    if not cleaned:
        cleaned = "symbol"
    if cleaned[0].isdigit():
        cleaned = f"sym_{cleaned}"
    return cleaned


def _friendly_label_from_symbol(raw_name: str) -> tuple[str, str]:
    demangled = _undecorate_symbol_name(raw_name)
    match = _FRIENDLY_LABEL_RE.search(demangled)
    if match:
        label = _sanitize_label_name(match.group(1))
    else:
        label = _sanitize_label_name(raw_name)

    if raw_name.startswith("??0"):
        class_name = _sanitize_label_name(demangled.split("::", 1)[0].split()[-1])
        label = f"{class_name}__ctor"
    elif raw_name.startswith("??1"):
        class_name = _sanitize_label_name(demangled.split("::", 1)[0].split()[-1])
        label = f"{class_name}__dtor"

    return label, demangled


def _append_label_suffixes(rows: list[dict[str, object]]) -> None:
    counts: dict[str, int] = {}
    for row in rows:
        label = str(row["label"])
        counts[label] = counts.get(label, 0) + 1

    for row in rows:
        label = str(row["label"])
        if counts.get(label, 0) > 1:
            row["label"] = f"{label}__rva_{int(row['rva']):06X}"


def _should_import_global_symbol(raw_name: str) -> bool:
    return raw_name.startswith(("??_7", "??_R0", "??_R4", "?class"))


def _load_advisory_symbol_bundle(root_override: Path | None) -> dict[str, object] | None:
    root = _resolve_advisory_symbol_root(root_override)
    if root is None:
        return None

    cache_key = str(root.resolve())
    cached = _ADVISORY_SYMBOL_CACHE.get(cache_key)
    if cached is not None:
        return cached

    public_functions_path = root / "pdb_reference" / "public_functions.csv"
    global_data_path = root / "pdb_reference" / "global_data.csv"
    merged_function_matches_path = root / "merged" / "function_matches_by_rva.csv"
    if not public_functions_path.exists() and not merged_function_matches_path.exists():
        _ADVISORY_SYMBOL_CACHE[cache_key] = None
        return None

    exact_function_rows: list[dict[str, object]] = []
    exact_rvas: set[int] = set()
    if merged_function_matches_path.exists():
        with merged_function_matches_path.open("r", encoding="utf-8", newline="") as handle:
            for row in csv.DictReader(handle):
                raw_name = row.get("pdb_name") or ""
                rva_text = row.get("entry_rva") or ""
                if not raw_name or not rva_text:
                    continue
                try:
                    rva = int(rva_text)
                except ValueError:
                    continue

                label, demangled = _friendly_label_from_symbol(raw_name)
                exact_function_rows.append(
                    {
                        "rva": rva,
                        "label": label,
                        "raw_name": raw_name,
                        "demangled": demangled,
                        "exact_match": True,
                    }
                )
                exact_rvas.add(rva)

    advisory_function_rows: list[dict[str, object]] = []
    if public_functions_path.exists():
        with public_functions_path.open("r", encoding="utf-8", newline="") as handle:
            for row in csv.DictReader(handle):
                raw_name = row.get("name") or ""
                rva_text = row.get("rva") or ""
                if not raw_name or not rva_text:
                    continue
                try:
                    rva = int(rva_text)
                except ValueError:
                    continue

                if rva in exact_rvas:
                    continue

                label, demangled = _friendly_label_from_symbol(raw_name)
                advisory_function_rows.append(
                    {
                        "rva": rva,
                        "label": label,
                        "raw_name": raw_name,
                        "demangled": demangled,
                        "exact_match": False,
                    }
                )

    global_rows: list[dict[str, object]] = []
    if global_data_path.exists():
        with global_data_path.open("r", encoding="utf-8", newline="") as handle:
            for row in csv.DictReader(handle):
                raw_name = row.get("name") or ""
                rva_text = row.get("rva") or ""
                if not raw_name or not rva_text or not _should_import_global_symbol(raw_name):
                    continue
                try:
                    rva = int(rva_text)
                except ValueError:
                    continue

                label, demangled = _friendly_label_from_symbol(raw_name)
                global_rows.append(
                    {
                        "rva": rva,
                        "label": label,
                        "raw_name": raw_name,
                        "demangled": demangled,
                    }
                )

    _append_label_suffixes(exact_function_rows)
    _append_label_suffixes(advisory_function_rows)
    _append_label_suffixes(global_rows)

    function_rows = [*exact_function_rows, *advisory_function_rows]
    generated_labels_by_rva: dict[int, set[str]] = {}
    for row in function_rows:
        generated_labels_by_rva.setdefault(int(row["rva"]), set()).add(str(row["label"]))

    bundle = {
        "root": root,
        "version": ADVISORY_SYMBOL_VERSION,
        "functions": function_rows,
        "globals": global_rows,
        "generated_labels_by_rva": generated_labels_by_rva,
    }
    _ADVISORY_SYMBOL_CACHE[cache_key] = bundle
    return bundle


def _is_default_like_symbol_name(name: str) -> bool:
    return name.startswith(("FUN_", "LAB_", "DAT_", "PTR_", "UNK_", "thunk_"))


def _program_looks_like_redux(program) -> bool:
    try:
        name = program.getDomainFile().getName().lower()
    except Exception:
        name = str(program).lower()
    return "battlezone98redux.exe" in name


def _apply_advisory_symbols_to_program(context, program, root_override: Path | None) -> None:
    if not _program_looks_like_redux(program):
        return

    bundle = _load_advisory_symbol_bundle(root_override)
    if not bundle:
        return

    options = program.getOptions(ADVISORY_SYMBOL_OPTIONS_NAME)
    if options.getString(ADVISORY_SYMBOL_VERSION_KEY, "") == bundle["version"]:
        return

    from ghidra.program.model.symbol import SourceType

    address_space = program.getAddressFactory().getDefaultAddressSpace()
    function_manager = program.getFunctionManager()
    symbol_table = program.getSymbolTable()
    image_base = int(program.getImageBase().getOffset())
    generated_labels_by_rva = bundle.get("generated_labels_by_rva", {})

    transaction = program.startTransaction("Apply OpenShim advisory Redux symbols")
    changed = False
    try:
        for row in bundle["functions"]:
            address = address_space.getAddress(image_base + int(row["rva"]))
            function = function_manager.getFunctionAt(address)
            label = str(row["label"])
            demangled = str(row["demangled"])
            generated_labels = set(generated_labels_by_rva.get(int(row["rva"]), set()))
            exact_match = bool(row.get("exact_match"))

            if function is not None:
                current_name = function.getName()
                current_source = function.getSymbol().getSource()
                if current_name != label and (
                    current_source != SourceType.USER_DEFINED
                    or _is_default_like_symbol_name(current_name)
                    or (exact_match and current_name in generated_labels)
                ):
                    function.setName(label, SourceType.USER_DEFINED)
                    changed = True
                if demangled and function.getComment() != demangled:
                    function.setComment(demangled)
                    changed = True
                continue

            existing = symbol_table.getPrimarySymbol(address)
            if existing is None:
                symbol_table.createLabel(address, label, SourceType.USER_DEFINED)
                changed = True
            elif (
                existing.getName() != label
                and (
                    existing.getSource() != SourceType.USER_DEFINED
                    or _is_default_like_symbol_name(existing.getName())
                    or (exact_match and existing.getName() in generated_labels)
                )
            ):
                existing.setName(label, SourceType.USER_DEFINED)
                changed = True

        for row in bundle["globals"]:
            address = address_space.getAddress(image_base + int(row["rva"]))
            label = str(row["label"])
            existing = symbol_table.getPrimarySymbol(address)
            if existing is None:
                symbol_table.createLabel(address, label, SourceType.USER_DEFINED)
                changed = True
            elif (
                existing.getName() != label
                and existing.getSource() != SourceType.USER_DEFINED
                and _is_default_like_symbol_name(existing.getName())
            ):
                existing.setName(label, SourceType.USER_DEFINED)
                changed = True

        options.setString(ADVISORY_SYMBOL_VERSION_KEY, str(bundle["version"]))
        changed = True
    finally:
        program.endTransaction(transaction, True)

    if changed:
        context.project.save(program)


def apply_pyghidra_context_patch(args: argparse.Namespace) -> None:
    import pyghidra_mcp.context as pyghidra_context

    advisory_root = args.advisory_corpus_root
    advisory_enabled = not args.no_advisory_symbols
    original_analyze_program = pyghidra_context.PyGhidraContext.analyze_program

    def _init_project_programs(self):
        from ghidra.framework.model import DomainFile
        from ghidra.program.model.listing import Program

        for domain_file in self.list_binary_domain_files():
            assert isinstance(domain_file, DomainFile)
            program: Program = self.project.openProgram(
                domain_file.getParent().pathname, domain_file.getName(), False
            )
            program_info = self._init_program_info(program)
            self.programs[domain_file.pathname] = program_info
            if advisory_enabled:
                _apply_advisory_symbols_to_program(self, program, advisory_root)

    def analyze_program(self, df_or_prog, require_symbols=True, force_analysis=False, verbose_analysis=False):
        result = original_analyze_program(
            self,
            df_or_prog,
            require_symbols=require_symbols,
            force_analysis=force_analysis,
            verbose_analysis=verbose_analysis,
        )
        if advisory_enabled:
            from ghidra.framework.model import DomainFile
            from ghidra.program.model.listing import Program

            if isinstance(df_or_prog, Program):
                program = df_or_prog
            elif isinstance(df_or_prog, DomainFile):
                program_info = self.programs.get(df_or_prog.pathname)
                program = program_info.program if program_info else None
            else:
                program = None

            if program is not None:
                _apply_advisory_symbols_to_program(self, program, advisory_root)
        return result

    pyghidra_context.PyGhidraContext._init_project_programs = _init_project_programs
    pyghidra_context.PyGhidraContext.analyze_program = analyze_program


def run_patched_pyghidra_mcp(args: argparse.Namespace) -> int:
    if args.ghidra_install_dir:
        os.environ["GHIDRA_INSTALL_DIR"] = str(args.ghidra_install_dir)

    args.project_path.mkdir(parents=True, exist_ok=True)
    apply_pyghidra_context_patch(args)

    pyghidra_args = build_pyghidra_args(args)
    old_argv = sys.argv[:]
    sys.argv = ["pyghidra_mcp", *pyghidra_args]
    try:
        runpy.run_module("pyghidra_mcp", run_name="__main__")
    except SystemExit as exc:
        return normalize_exit_code(exc.code)
    finally:
        sys.argv = old_argv
    return 0


def service_ready(host: str, port: int, timeout_seconds: float = 2.0) -> bool:
    try:
        connection = http.client.HTTPConnection(host, port, timeout=timeout_seconds)
        connection.request("GET", DEFAULT_SERVICE_PATH)
        response = connection.getresponse()
        response.read()
        connection.close()
        return response.status in (200, 400, 405, 406)
    except OSError:
        return False


def build_background_command(args: argparse.Namespace) -> list[str]:
    command = [
        sys.executable,
        str(Path(__file__).resolve()),
        "--binary",
        str(args.binary),
        "--project-path",
        str(args.project_path),
        "--project-name",
        args.project_name,
        "--transport",
        "streamable-http",
        "--host",
        args.service_host,
        "--port",
        str(args.service_port),
        "--ghidra-install-dir",
        str(args.ghidra_install_dir),
    ]

    if args.wait_for_analysis:
        command.append("--wait-for-analysis")
    if args.force_analysis:
        command.append("--force-analysis")
    if args.no_symbols:
        command.append("--no-symbols")
    if args.verbose_analysis:
        command.append("--verbose-analysis")
    if args.no_advisory_symbols:
        command.append("--no-advisory-symbols")
    if args.advisory_corpus_root:
        command += ["--advisory-corpus-root", str(args.advisory_corpus_root)]
    if args.symbols_path:
        command += ["--symbols-path", str(args.symbols_path)]
    if args.sym_file_path:
        command += ["--sym-file-path", str(args.sym_file_path)]
    if args.gzfs_path:
        command += ["--gzfs-path", str(args.gzfs_path)]

    command += args.extra_args
    return command


def ensure_service(args: argparse.Namespace) -> int:
    if service_ready(args.service_host, args.service_port):
        return 0

    args.service_log_path.parent.mkdir(parents=True, exist_ok=True)
    command = build_background_command(args)
    creationflags = 0
    for flag_name in ("CREATE_NO_WINDOW", "DETACHED_PROCESS", "CREATE_NEW_PROCESS_GROUP"):
        creationflags |= getattr(subprocess, flag_name, 0)

    with args.service_log_path.open("a", encoding="utf-8") as log_file:
        process = subprocess.Popen(
            command,
            cwd=str(REPO_ROOT),
            env=os.environ.copy(),
            stdin=subprocess.DEVNULL,
            stdout=log_file,
            stderr=log_file,
            creationflags=creationflags,
        )

    deadline = time.monotonic() + max(args.service_startup_timeout, 1.0)
    while time.monotonic() < deadline:
        if service_ready(args.service_host, args.service_port):
            return 0

        return_code = process.poll()
        if return_code is not None:
            return return_code

        time.sleep(1.0)

    return 1


def main() -> int:
    args = parse_args()
    if args.ensure_service:
        return ensure_service(args)
    return run_patched_pyghidra_mcp(args)


if __name__ == "__main__":
    raise SystemExit(main())
