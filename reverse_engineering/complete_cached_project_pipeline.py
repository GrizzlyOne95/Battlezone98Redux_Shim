from __future__ import annotations

import argparse
import csv
import json
import subprocess
import sys
from pathlib import Path

from run_best_effort_pipeline import load_reference_json, merge_function_maps, write_summary


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


def count_csv_rows(path: Path) -> int:
    if not path.exists():
        return 0
    with path.open("r", newline="", encoding="utf-8") as handle:
        reader = csv.reader(handle)
        try:
            next(reader)
        except StopIteration:
            return 0
        return sum(1 for _ in reader)


def main() -> None:
    parser = argparse.ArgumentParser(description="Finish a decompile pipeline from an existing analyzed Ghidra project.")
    parser.add_argument("--binary", type=Path, required=True)
    parser.add_argument("--output-root", type=Path, required=True)
    parser.add_argument("--project-path", type=Path, required=True)
    parser.add_argument("--project-name", required=True)
    parser.add_argument("--promoted-root", type=Path)
    parser.add_argument("--max-ram-percent", type=float, default=35.0)
    parser.add_argument("--decompile-timeout-secs", type=int, default=10)
    args = parser.parse_args()

    output_root = args.output_root.resolve()
    project_path = args.project_path.resolve()
    logs_dir = output_root / "logs"
    decomp_dir = output_root / "ghidrecomp" / "results" / "bins" / args.project_name / "decomps"
    inventory_dir = output_root / "inventory"
    pdb_dir = output_root / "pdb_reference"
    strings_dir = output_root / "binary_strings"
    merged_dir = output_root / "merged"

    run_command(
        [
            sys.executable,
            str(Path(__file__).resolve().parent / "export_existing_project_decomp.py"),
            "--binary",
            str(args.binary.resolve()),
            "--project-path",
            str(project_path),
            "--project-name",
            args.project_name,
            "--output-dir",
            str(decomp_dir),
            "--max-ram-percent",
            str(args.max_ram_percent),
            "--decompile-timeout-secs",
            str(args.decompile_timeout_secs),
        ],
        logs_dir / "export_existing_project_decomp.log",
    )

    run_command(
        [
            sys.executable,
            str(Path(__file__).resolve().parent / "export_ghidra_inventory.py"),
            "--binary",
            str(args.binary.resolve()),
            "--project-path",
            str(project_path),
            "--project-name",
            args.project_name,
            "--output-dir",
            str(inventory_dir),
            "--max-ram-percent",
            str(args.max_ram_percent),
        ],
        logs_dir / "export_ghidra_inventory_resume.log",
    )

    merged_count = merge_function_maps(
        inventory_dir / "functions.csv",
        pdb_dir / "public_functions.csv",
        merged_dir / "function_matches_by_rva.csv",
    )

    pdb_reference = load_reference_json(pdb_dir / "reference.json") or {}
    manifest = {
        "binary_path": str(args.binary.resolve()),
        "pdb_path": str(pdb_reference.get("pdb_path")) if pdb_reference else None,
        "output_root": str(output_root),
        "ghidra_project_path": str(project_path),
        "ghidra_project_name": args.project_name,
        "counts": {
            "ascii_strings": count_csv_rows(strings_dir / "ascii_strings.csv"),
            "utf16_strings": count_csv_rows(strings_dir / "utf16_strings.csv"),
            "merged_rva_names": merged_count,
        },
        "pdb_exact_match": bool(pdb_reference.get("match", {}).get("exact_match", False)),
        "decomp_dir": str(decomp_dir),
        "inventory_dir": str(inventory_dir),
        "strings_dir": str(strings_dir),
        "pdb_dir": str(pdb_dir),
        "logs_dir": str(logs_dir),
        "ghidra_pdb_apply": "auto_exact_rsds",
    }
    (output_root / "pipeline_manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")
    write_summary(output_root / "SUMMARY.md", manifest)

    if args.promoted_root:
        run_command(
            [
                sys.executable,
                str(Path(__file__).resolve().parent / "finalize_global_corpus.py"),
                "--output-root",
                str(output_root),
                "--promoted-root",
                str(args.promoted_root.resolve()),
            ],
            logs_dir / "finalize_global_corpus.log",
        )

    print(json.dumps(manifest, indent=2))


if __name__ == "__main__":
    main()
