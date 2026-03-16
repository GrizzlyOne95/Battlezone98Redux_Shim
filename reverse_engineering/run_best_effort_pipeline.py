from __future__ import annotations

import argparse
import csv
import hashlib
import json
import os
import re
import subprocess
import sys
from pathlib import Path

import pefile
from ghidrecomp.decompile import gen_proj_bin_name_from_path


ASCII_PATTERN = re.compile(rb"[\x20-\x7e]{4,}")
UTF16_PATTERN = re.compile(rb"(?:[\x20-\x7e]\x00){4,}")


def run_command(command: list[str], log_path: Path | None = None) -> None:
    print("$", subprocess.list2cmdline(command))
    if log_path is None:
        completed = subprocess.run(command, check=False)
    else:
        log_path.parent.mkdir(parents=True, exist_ok=True)
        with log_path.open("w", encoding="utf-8", errors="replace") as handle:
            completed = subprocess.run(command, stdout=handle, stderr=subprocess.STDOUT, text=True, check=False)
    if completed.returncode != 0:
        raise RuntimeError(f"Command failed with exit code {completed.returncode}: {command}")


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        while True:
            chunk = handle.read(1024 * 1024)
            if not chunk:
                return digest.hexdigest()
            digest.update(chunk)


def detect_default_pdb(binary: Path) -> Path | None:
    candidate = binary.with_suffix(".pdb")
    return candidate if candidate.exists() else None


def extract_binary_strings(binary: Path, output_dir: Path) -> dict[str, int]:
    pe = pefile.PE(str(binary), fast_load=False)
    data = binary.read_bytes()
    output_dir.mkdir(parents=True, exist_ok=True)

    def offset_to_rva(offset: int) -> int | None:
        try:
            return int(pe.get_rva_from_offset(offset))
        except Exception:
            return None

    def section_name_for_rva(rva: int | None) -> str:
        if rva is None:
            return ""
        for section in pe.sections:
            start = int(section.VirtualAddress)
            end = start + max(int(section.Misc_VirtualSize), int(section.SizeOfRawData))
            if start <= rva < end:
                return section.Name.rstrip(b"\0").decode(errors="ignore")
        return ""

    def write_rows(file_name: str, rows: list[dict]) -> None:
        with (output_dir / file_name).open("w", newline="", encoding="utf-8") as handle:
            writer = csv.DictWriter(handle, fieldnames=["offset", "rva", "section", "text"])
            writer.writeheader()
            writer.writerows(rows)

    ascii_rows: list[dict] = []
    for match in ASCII_PATTERN.finditer(data):
        offset = match.start()
        rva = offset_to_rva(offset)
        ascii_rows.append(
            {
                "offset": offset,
                "rva": rva if rva is not None else "",
                "section": section_name_for_rva(rva),
                "text": match.group(0).decode("ascii", errors="ignore"),
            }
        )

    utf16_rows: list[dict] = []
    for match in UTF16_PATTERN.finditer(data):
        offset = match.start()
        rva = offset_to_rva(offset)
        utf16_rows.append(
            {
                "offset": offset,
                "rva": rva if rva is not None else "",
                "section": section_name_for_rva(rva),
                "text": match.group(0).decode("utf-16le", errors="ignore"),
            }
        )

    write_rows("ascii_strings.csv", ascii_rows)
    write_rows("utf16_strings.csv", utf16_rows)
    return {"ascii_strings": len(ascii_rows), "utf16_strings": len(utf16_rows)}


def load_reference_json(path: Path) -> dict | None:
    if not path.exists():
        return None
    return json.loads(path.read_text(encoding="utf-8"))


def merge_function_maps(inventory_csv: Path, pdb_csv: Path, output_csv: Path) -> int:
    if not inventory_csv.exists() or not pdb_csv.exists():
        return 0

    by_rva: dict[str, dict] = {}
    with pdb_csv.open("r", newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            rva = row.get("rva")
            if not rva:
                continue
            by_rva[rva] = row

    merged_count = 0
    output_csv.parent.mkdir(parents=True, exist_ok=True)
    with inventory_csv.open("r", newline="", encoding="utf-8") as source, output_csv.open(
        "w", newline="", encoding="utf-8"
    ) as destination:
        reader = csv.DictReader(source)
        writer = csv.DictWriter(
            destination,
            fieldnames=[
                "entry_rva",
                "ghidra_name",
                "ghidra_signature",
                "pdb_name",
                "pdb_segment",
                "pdb_offset",
            ],
        )
        writer.writeheader()
        for row in reader:
            match = by_rva.get(row["entry_rva"])
            if not match:
                continue
            writer.writerow(
                {
                    "entry_rva": row["entry_rva"],
                    "ghidra_name": row["name"],
                    "ghidra_signature": row["signature"],
                    "pdb_name": match["name"],
                    "pdb_segment": match["segment"],
                    "pdb_offset": match["offset"],
                }
            )
            merged_count += 1
    return merged_count


def write_summary(summary_path: Path, summary: dict) -> None:
    lines = [
        "# Best-Effort Global Decompile Summary",
        "",
        f"- Binary: `{summary['binary_path']}`",
        f"- Output root: `{summary['output_root']}`",
        f"- Ghidra project: `{summary['ghidra_project_name']}`",
        f"- PDB used as advisory reference: `{summary['pdb_path'] or '<none>'}`",
        f"- Exact PE/PDB match: `{summary['pdb_exact_match']}`",
        "",
        "## Outputs",
        "",
        f"- Decompiled functions: `{summary['decomp_dir']}`",
        f"- Ghidra inventory: `{summary['inventory_dir']}`",
        f"- Binary strings: `{summary['strings_dir']}`",
    ]
    if summary["pdb_dir"]:
        lines.append(f"- PDB reference exports: `{summary['pdb_dir']}`")
    lines.extend(
        [
            "",
            "## Counts",
            "",
            f"- ASCII strings: `{summary['counts'].get('ascii_strings', 0)}`",
            f"- UTF-16 strings: `{summary['counts'].get('utf16_strings', 0)}`",
            f"- Matched RVA names: `{summary['counts'].get('merged_rva_names', 0)}`",
        ]
    )
    summary_path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def main() -> None:
    parser = argparse.ArgumentParser(description="Run a best-effort Battlezone global decompile pipeline.")
    parser.add_argument("--binary", type=Path, default=Path(r"C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe"))
    parser.add_argument("--pdb", type=Path, help="Optional PDB path. Defaults to <binary>.pdb if present.")
    parser.add_argument("--output-root", type=Path, help="Root directory for all generated artifacts.")
    parser.add_argument("--project-path", type=Path, help="Ghidra project storage root.")
    parser.add_argument("--thread-count", type=int, default=max(1, (os.cpu_count() or 8) // 2))
    parser.add_argument("--max-ram-percent", type=float, default=50.0)
    parser.add_argument("--skip-cache", action="store_true")
    parser.add_argument("--force-analysis", action="store_true")
    parser.add_argument("--callgraphs", action="store_true")
    parser.add_argument("--skip-pdb", action="store_true")
    parser.add_argument("--skip-strings", action="store_true")
    parser.add_argument("--skip-inventory", action="store_true")
    parser.add_argument("--skip-llvm", action="store_true")
    parser.add_argument("--lightweight-pdb", action="store_true")
    parser.add_argument("--force-pdb-in-ghidra", action="store_true")
    args = parser.parse_args()

    binary = args.binary.resolve()
    pdb_path = args.pdb.resolve() if args.pdb else detect_default_pdb(binary)
    script_root = Path(__file__).resolve().parent

    if args.output_root:
        output_root = args.output_root.resolve()
    else:
        slug = f"{binary.stem}_{sha256_file(binary)[:12]}"
        output_root = (script_root / "workshop" / "global_decompile" / slug).resolve()
    output_root.mkdir(parents=True, exist_ok=True)

    project_path = args.project_path.resolve() if args.project_path else (output_root / "ghidra_projects")
    project_path.mkdir(parents=True, exist_ok=True)

    ghidra_project_name = gen_proj_bin_name_from_path(binary)
    logs_dir = output_root / "logs"
    strings_dir = output_root / "binary_strings"
    pdb_dir = output_root / "pdb_reference"
    ghidrecomp_dir = output_root / "ghidrecomp"
    inventory_dir = output_root / "inventory"
    merged_dir = output_root / "merged"

    manifest = {
        "binary_path": str(binary),
        "binary_sha256": sha256_file(binary),
        "pdb_path": str(pdb_path) if pdb_path else None,
        "output_root": str(output_root),
        "ghidra_project_path": str(project_path),
        "ghidra_project_name": ghidra_project_name,
        "counts": {},
    }

    if not args.skip_strings:
        manifest["counts"].update(extract_binary_strings(binary, strings_dir))

    pdb_reference = None
    if pdb_path and not args.skip_pdb:
        command = [
            sys.executable,
            str(script_root / "export_pdb_reference.py"),
            "--pe",
            str(binary),
            "--pdb",
            str(pdb_path),
            "--output-dir",
            str(pdb_dir),
        ]
        if args.skip_llvm:
            command.append("--skip-llvm")
        if args.lightweight_pdb:
            command.append("--lightweight")
        run_command(command, logs_dir / "export_pdb_reference.log")
        pdb_reference = load_reference_json(pdb_dir / "reference.json")

    apply_pdb_in_ghidra = False
    if pdb_reference:
        apply_pdb_in_ghidra = bool(pdb_reference["match"]["exact_match"]) or args.force_pdb_in_ghidra
        manifest["pdb_exact_match"] = bool(pdb_reference["match"]["exact_match"])
    else:
        manifest["pdb_exact_match"] = False

    ghidrecomp_command = [
        sys.executable,
        "-m",
        "ghidrecomp",
        str(binary),
        "-o",
        str(ghidrecomp_dir),
        "--project-path",
        str(project_path),
        "-t",
        str(args.thread_count),
        "--max-ram-percent",
        str(args.max_ram_percent),
    ]
    if args.skip_cache:
        ghidrecomp_command.append("--skip-cache")
    if args.force_analysis:
        ghidrecomp_command.append("--fa")
    if args.callgraphs:
        ghidrecomp_command.extend(["--callgraphs", "--cg-direction", "both"])
    ghidra_pdb_apply = "skipped"
    if pdb_path and apply_pdb_in_ghidra:
        ghidrecomp_command.extend(["--sym-file-path", str(pdb_path)])
        ghidra_pdb_apply = "direct"
    else:
        ghidrecomp_command.append("--skip-symbols")

    try:
        run_command(ghidrecomp_command, logs_dir / "ghidrecomp.log")
    except RuntimeError:
        if pdb_path and apply_pdb_in_ghidra:
            fallback_command = [arg for arg in ghidrecomp_command if arg not in ("--sym-file-path", str(pdb_path))]
            if "--skip-symbols" not in fallback_command:
                fallback_command.append("--skip-symbols")
            run_command(fallback_command, logs_dir / "ghidrecomp_fallback.log")
            ghidra_pdb_apply = "fallback_skip_symbols"
        else:
            raise

    if not args.skip_inventory:
        run_command(
            [
                sys.executable,
                str(script_root / "export_ghidra_inventory.py"),
                "--binary",
                str(binary),
                "--project-path",
                str(project_path),
                "--project-name",
                ghidra_project_name,
                "--output-dir",
                str(inventory_dir),
                "--max-ram-percent",
                str(args.max_ram_percent),
            ],
            logs_dir / "export_ghidra_inventory.log",
        )

    merged_count = merge_function_maps(
        inventory_dir / "functions.csv",
        pdb_dir / "public_functions.csv",
        merged_dir / "function_matches_by_rva.csv",
    )
    manifest["counts"]["merged_rva_names"] = merged_count

    decomp_dir = ghidrecomp_dir / "results" / "bins" / ghidra_project_name / "decomps"
    manifest.update(
        {
            "decomp_dir": str(decomp_dir),
            "inventory_dir": str(inventory_dir),
            "strings_dir": str(strings_dir),
            "pdb_dir": str(pdb_dir) if pdb_path and not args.skip_pdb else None,
            "logs_dir": str(logs_dir),
            "ghidra_pdb_apply": ghidra_pdb_apply,
        }
    )

    (output_root / "pipeline_manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")
    write_summary(output_root / "SUMMARY.md", manifest)

    print(json.dumps(manifest, indent=2))


if __name__ == "__main__":
    try:
        main()
    except Exception as exc:
        print(f"run_best_effort_pipeline.py failed: {exc}", file=sys.stderr)
        raise
