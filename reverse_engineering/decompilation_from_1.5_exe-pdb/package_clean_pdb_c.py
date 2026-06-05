#!/usr/bin/env python3
"""Package the best PDB-backed Ghidra decompilation into a clean source tree."""

from __future__ import annotations

import csv
import json
import re
import shutil
import subprocess
from pathlib import Path


ROOT = Path(__file__).resolve().parent
PRIMARY = ROOT / "ghidra_pdb_skip"
SUPPLEMENT = ROOT / "ghidra_pdb"
OUT = ROOT / "clean_pdb_c"

BLOCK_RE = re.compile(
    r"^/\* =====================================================================\r?\n"
    r" \* (?P<entry>[0-9a-fA-F]{8})  (?P<name>.*?)\r?\n"
    r" \* Signature: (?P<signature>.*?)\r?\n"
    r" \* Symbol source: (?P<source>.*?)\r?\n"
    r" \* ===================================================================== \*/\r?\n"
    r"(?P<body>.*?)(?=^/\* =====================================================================|\Z)",
    re.MULTILINE | re.DOTALL,
)


def read_index(path: Path) -> list[dict[str, str]]:
    with path.open("r", encoding="utf-8", newline="") as f:
        return list(csv.DictReader(f, delimiter="\t"))


def read_failures(path: Path) -> dict[str, str]:
    failures: dict[str, str] = {}
    with path.open("r", encoding="utf-8", newline="") as f:
        for row in csv.DictReader(f, delimiter="\t"):
            failures[row["entry"].lower()] = row["reason"]
    return failures


def read_blocks(path: Path) -> dict[str, dict[str, str]]:
    text = path.read_text(encoding="utf-8", errors="replace")
    blocks: dict[str, dict[str, str]] = {}
    for match in BLOCK_RE.finditer(text):
        item = match.groupdict()
        item["entry"] = item["entry"].lower()
        blocks[item["entry"]] = item
    return blocks


def safe_name(name: str, limit: int = 120) -> str:
    cleaned = re.sub(r"[^A-Za-z0-9_.$@~-]+", "_", name.strip())
    cleaned = cleaned.strip("._") or "function"
    return cleaned[:limit]


def write_function_file(row: dict[str, str], body: str) -> Path:
    entry = row["entry"].lower()
    shard = entry[:4]
    out_dir = OUT / "functions" / shard
    out_dir.mkdir(parents=True, exist_ok=True)
    path = out_dir / f"{entry}_{safe_name(row['name'])}.c"
    content = (
        "/*\n"
        f" * Entry: {row['entry']}\n"
        f" * Name: {row['name']}\n"
        f" * Namespace: {row['parent_namespace']}\n"
        f" * Signature: {row['signature']}\n"
        f" * Symbol source: {row['source']}\n"
        f" * Export status: {row['status']}\n"
        " */\n\n"
        f"{body.strip()}\n"
    )
    path.write_text(content, encoding="utf-8", newline="\n")
    return path


def write_failed_disassembly(index: list[dict[str, str]], failures: list[dict[str, str]]) -> int:
    objdump = shutil.which("llvm-objdump")
    exe = ROOT.parent / "bzone.exe"
    if objdump is None or not exe.exists():
        return 0

    by_entry = {row["entry"].lower(): row for row in index}
    entries = sorted(int(row["entry"], 16) for row in index)
    fail_dir = OUT / "failed_asm"
    fail_dir.mkdir(parents=True, exist_ok=True)

    count = 0
    for failure in failures:
        entry_text = failure["entry"].lower()
        entry = int(entry_text, 16)
        stop = next((candidate for candidate in entries if candidate > entry), None)
        if stop is None:
            continue

        row = by_entry[entry_text]
        path = fail_dir / f"{entry_text}_{safe_name(row['name'])}.asm"
        command = [
            objdump,
            "-d",
            "--no-show-raw-insn",
            f"--start-address=0x{entry:08x}",
            f"--stop-address=0x{stop:08x}",
            str(exe),
        ]
        result = subprocess.run(command, check=False, capture_output=True, text=True)
        header = (
            f"; Entry: {row['entry']}\n"
            f"; Name: {row['name']}\n"
            f"; Signature: {row['signature']}\n"
            f"; Stop: 0x{stop:08x}\n"
            f"; Reason: {failure['reason']}\n"
            f"; Command: {' '.join(command)}\n\n"
        )
        path.write_text(header + result.stdout + result.stderr, encoding="utf-8", newline="\n")
        count += 1

    return count


def main() -> None:
    if OUT.exists():
        shutil.rmtree(OUT)
    (OUT / "functions").mkdir(parents=True)

    primary_index = read_index(PRIMARY / "ghidra_function_index.tsv")
    primary_failures = read_failures(PRIMARY / "ghidra_decompile_failures.tsv")
    primary_blocks = read_blocks(PRIMARY / "ghidra_decompiled_all.c")
    supplement_blocks = read_blocks(SUPPLEMENT / "ghidra_decompiled_all.c")

    clean_index: list[dict[str, str]] = []
    failures: list[dict[str, str]] = []
    emitted: list[dict[str, str]] = []

    with (OUT / "all_decompiled.c").open("w", encoding="utf-8", newline="\n") as combined:
        combined.write(
            "/*\n"
            " * Clean merged Ghidra decompilation for bzone.exe 1.5.2.27 Update 1.\n"
            " * Base: ghidra_pdb_skip; supplement: ghidra_pdb for recovered Show_Light_Source.\n"
            " * This is C-like decompiler output for reference, not directly buildable source.\n"
            " */\n\n"
        )

        for row in primary_index:
            entry = row["entry"].lower()
            body = None
            source_run = ""

            if row["status"] == "ok" and entry in primary_blocks:
                body = primary_blocks[entry]["body"]
                source_run = "ghidra_pdb_skip"
            elif entry in supplement_blocks:
                body = supplement_blocks[entry]["body"]
                source_run = "ghidra_pdb"
                row = dict(row)
                row["status"] = "ok_supplemented"
                row["body_size"] = str(len(body))

            clean_index.append(row)

            if body is None:
                failures.append(
                    {
                        "entry": row["entry"],
                        "name": row["name"],
                        "reason": primary_failures.get(entry, row["status"] or "missing body"),
                    }
                )
                continue

            file_path = write_function_file(row, body)
            emitted.append(
                {
                    "entry": row["entry"],
                    "name": row["name"],
                    "status": row["status"],
                    "source_run": source_run,
                    "file": str(file_path.relative_to(OUT)).replace("\\", "/"),
                }
            )

            combined.write("/* =====================================================================\n")
            combined.write(f" * {row['entry']}  {row['name']}\n")
            combined.write(f" * Signature: {row['signature']}\n")
            combined.write(f" * Symbol source: {row['source']}\n")
            combined.write(f" * Export status: {row['status']} ({source_run})\n")
            combined.write(" * ===================================================================== */\n")
            combined.write(body.strip())
            combined.write("\n\n")

    fieldnames = [
        "entry",
        "name",
        "parent_namespace",
        "signature",
        "source",
        "body_size",
        "status",
    ]
    with (OUT / "function_index.tsv").open("w", encoding="utf-8", newline="") as f:
        writer = csv.DictWriter(f, delimiter="\t", fieldnames=fieldnames, extrasaction="ignore")
        writer.writeheader()
        writer.writerows(clean_index)

    with (OUT / "decompile_failures.tsv").open("w", encoding="utf-8", newline="") as f:
        writer = csv.DictWriter(f, delimiter="\t", fieldnames=["entry", "name", "reason"])
        writer.writeheader()
        writer.writerows(failures)

    failed_disassembly_count = write_failed_disassembly(clean_index, failures)

    manifest = {
        "program": "bzone.exe",
        "pdb": "bzint.pdb",
        "primary_source": str(PRIMARY.relative_to(ROOT)).replace("\\", "/"),
        "supplement_source": str(SUPPLEMENT.relative_to(ROOT)).replace("\\", "/"),
        "function_count": len(primary_index),
        "decompiled_count": len(emitted),
        "failed_count": len(failures),
        "supplemented_count": sum(1 for item in emitted if item["status"] == "ok_supplemented"),
        "failed_disassembly_count": failed_disassembly_count,
    }
    (OUT / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")

    readme = f"""# Clean PDB Ghidra C Export

This folder packages the best available Ghidra decompilation for `bzone.exe` with `bzint.pdb` applied.

- Function records: {manifest["function_count"]}
- Decompiled C-like functions: {manifest["decompiled_count"]}
- Remaining failed decompilations: {manifest["failed_count"]}
- Supplemented functions recovered from earlier run: {manifest["supplemented_count"]}

Files:

- `all_decompiled.c`: merged C-like decompiler output.
- `functions/`: one `.c` file per decompiled function, sharded by address prefix.
- `function_index.tsv`: full function index and status.
- `decompile_failures.tsv`: functions still not represented as C.
- `failed_asm/`: assembly fallbacks for the remaining failed decompilations.
- `manifest.json`: machine-readable package summary.

Notes:

- This is reference-grade Ghidra output, not directly buildable original source.
- The remaining failures are Ghidra decompiler timeouts, mostly large software rasterizer/terrain polygon routines.
- `Show_Light_Source` was skipped in the complete run but recovered from the earlier PDB run.
"""
    (OUT / "README.md").write_text(readme, encoding="utf-8", newline="\n")

    print(json.dumps(manifest, indent=2))


if __name__ == "__main__":
    main()
