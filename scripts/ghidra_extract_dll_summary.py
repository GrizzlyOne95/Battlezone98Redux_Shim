from __future__ import annotations

import argparse
import shutil
import tempfile
from pathlib import Path

import lief
import pyghidra
from pyghidra_mcp.context import PyGhidraContext
from pyghidra_mcp.tools import GhidraTools


KEY_FUNCTIONS = {
    "winmm.bin": [
        ("DllMain entry", "0x10002E1B"),
        ("Loader / proxy init", "0x10001C20"),
    ],
    "_bzcp.dll": [
        ("patch export", "0x10010280"),
        ("patch worker", "0x1000EB30"),
        ("save selection helper", "0x1000CAF0"),
        ("restore selection helper", "0x1000CB40"),
        ("restore scroll helper", "0x1000CCA0"),
    ],
}
def pdb_filename(path: Path) -> str | None:
    binary = lief.parse(str(path))
    if binary is None or not binary.has_debug:
        return None
    for entry in binary.debug:
        text = str(entry)
        for line in text.splitlines():
            line = line.strip()
            if line.startswith("filename:"):
                return line.split(":", 1)[1].strip()
    return None


def sanitize_excerpt(text: str, limit: int) -> str:
    return text.replace("\r", "").strip()[:limit].rstrip()


def analyze_dlls(bzcp_path: Path, winmm_path: Path) -> str:
    project_root = Path(tempfile.gettempdir()) / "bzr_open_shim_pyghidra"
    if project_root.exists():
        shutil.rmtree(project_root)

    project_name = "BZR_OPEN_SHIM_DLLS"
    pyghidra.start(False)

    ctx = PyGhidraContext(
        project_name=project_name,
        project_path=project_root,
        pyghidra_mcp_dir=project_root / f"{project_name}-pyghidra-mcp",
        threaded=False,
        max_workers=1,
        wait_for_analysis=False,
    )

    try:
        ctx.import_binaries([bzcp_path, winmm_path])
        for domain_file in ctx.list_binary_domain_files():
            ctx.analyze_program(domain_file)

        program_names = {Path(name).name.split("-", 1)[0]: name for name in ctx.list_binaries()}

        lines: list[str] = []
        lines.append("# Ghidra DLL Summary")
        lines.append("")
        lines.append("Headless analysis performed with `pyghidra` / `pyghidra_mcp`.")
        lines.append("")

        for binary_name, src_path in (("_bzcp.dll", bzcp_path), ("winmm.bin", winmm_path)):
            project_key = program_names[f"{binary_name}"]
            program_info = ctx.get_program_info(project_key)
            tools = GhidraTools(program_info)

            lines.append(f"## {binary_name}")
            lines.append("")
            lines.append(f"- Source path: `{src_path}`")
            lines.append(f"- Project name: `{project_key}`")
            lines.append(f"- PDB path in debug record: `{pdb_filename(src_path)}`")
            lines.append("")

            exports = tools.list_exports(limit=16)
            imports = tools.list_imports(limit=16)
            lines.append("- Exports:")
            for export in exports:
                lines.append(f"  - `{export.name}` @ `{export.address}`")
            lines.append("- Imports (first 16):")
            for imp in imports:
                lines.append(f"  - `{imp.library}` :: `{imp.name}`")
            lines.append("")

            for label, addr in KEY_FUNCTIONS[binary_name]:
                decompiled = tools.decompile_function_by_name_or_addr(addr)
                lines.append(f"### {label}")
                lines.append("")
                lines.append(f"- Address: `{addr}`")
                lines.append(f"- Signature: `{decompiled.signature}`")
                lines.append("```c")
                lines.append(sanitize_excerpt(decompiled.code, 2400))
                lines.append("```")
                lines.append("")

        return "\n".join(lines)
    finally:
        ctx.close()


def main() -> None:
    parser = argparse.ArgumentParser(description="Run headless Ghidra analysis for _bzcp.dll and winmm.bin")
    parser.add_argument(
        "--bzcp",
        type=Path,
        default=Path("reverse_engineering/workshop/3362534335/latest/_bzcp.dll"),
        help="Path to _bzcp.dll",
    )
    parser.add_argument(
        "--winmm",
        type=Path,
        default=Path("reverse_engineering/workshop/3362534335/latest/winmm.bin"),
        help="Path to winmm.bin",
    )
    parser.add_argument(
        "--out",
        type=Path,
        default=None,
        help="Optional output markdown path",
    )
    args = parser.parse_args()

    summary = analyze_dlls(args.bzcp, args.winmm)
    if args.out:
        args.out.write_text(summary, encoding="utf-8")
    else:
        print(summary)


if __name__ == "__main__":
    main()
