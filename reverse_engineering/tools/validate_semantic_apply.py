from __future__ import annotations

import argparse
import csv
import hashlib
import json
import os
import re
from collections import Counter
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs


DEFAULT_RANKING_DIR = Path("reverse_engineering/workshop/private_pdb_index/semantic_ranking")
DEFAULT_INVENTORY = Path("reverse_engineering/repo_corpora/bzr_gog_best_effort/inventory/functions.csv")
DEFAULT_MANIFEST = Path("reverse_engineering/repo_corpora/bzr_gog_best_effort/pipeline_manifest.json")

EXECUTE_FLAG = 0x20000000
BAD_FIRST_MNEMONICS = {"hlt", "int3", "ud2"}
SAFE_NAME_PATTERN = re.compile(r"^[A-Za-z_~][A-Za-z0-9_~]*$")
SAFE_NAMESPACE_PATTERN = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")


def read_csv(path: Path) -> list[dict]:
    if not path.exists():
        return []
    with path.open("r", newline="", encoding="utf-8-sig") as handle:
        return list(csv.DictReader(handle))


def write_csv(path: Path, rows: list[dict], fields: list[str]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=fields, extrasaction="ignore")
        writer.writeheader()
        writer.writerows(rows)


def write_tsv(path: Path, rows: list[dict], fields: list[str]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=fields, extrasaction="ignore", delimiter="\t")
        writer.writeheader()
        writer.writerows(rows)


def parse_int(value: str | int | None) -> int | None:
    if value is None or value == "":
        return None
    try:
        return int(str(value), 0)
    except ValueError:
        return None


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        while chunk := handle.read(1024 * 1024):
            digest.update(chunk)
    return digest.hexdigest()


def resolve_default_binary(explicit: Path | None, expected_sha: str) -> Path:
    if explicit is not None:
        path = explicit.expanduser().resolve()
        if not path.is_file():
            raise FileNotFoundError(f"Binary does not exist: {path}")
        return path

    candidates: list[Path] = []
    for variable in ("BZR_GOG_EXE", "BZR_GAME_EXE", "BZR_REDUX_EXE"):
        value = os.environ.get(variable)
        if value:
            candidates.append(Path(value).expanduser())
    program_files_x86 = os.environ.get("ProgramFiles(x86)", r"C:\Program Files (x86)")
    candidates.extend(
        [
            Path(program_files_x86) / "GOG Galaxy" / "Games" / "Battlezone 98 Redux" / "battlezone98redux.exe",
            Path.home() / "Documents" / "Battlezone 98 Redux" / "battlezone98redux.exe",
        ]
    )

    existing: list[Path] = []
    seen: set[str] = set()
    for candidate in candidates:
        resolved = candidate.resolve()
        key = str(resolved).lower()
        if key in seen or not resolved.is_file():
            continue
        seen.add(key)
        existing.append(resolved)
        if sha256_file(resolved).lower() == expected_sha.lower():
            return resolved
    if existing:
        return existing[0]
    raise FileNotFoundError(
        "No Redux executable found. Pass --binary or set BZR_GOG_EXE/BZR_GAME_EXE."
    )


def bool_value(value: str | bool | None) -> bool:
    if isinstance(value, bool):
        return value
    return str(value).lower() == "true"


def split_qualified_name(value: str) -> tuple[str, str]:
    if "::" not in value:
        return "Global", value
    namespace, name = value.rsplit("::", 1)
    return namespace, name


def safe_rename(namespace: str, name: str) -> bool:
    if not SAFE_NAME_PATTERN.fullmatch(name):
        return False
    return namespace == "Global" or all(SAFE_NAMESPACE_PATTERN.fullmatch(part) for part in namespace.split("::"))


def section_for_rva(pe: pefile.PE, rva: int):
    for section in pe.sections:
        start = int(section.VirtualAddress)
        end = start + max(int(section.Misc_VirtualSize), int(section.SizeOfRawData))
        if start <= rva < end:
            return section
    return None


def decode_entry(code: bytes, va: int) -> tuple[list[str], int]:
    disassembler = Cs(CS_ARCH_X86, CS_MODE_32)
    instructions: list[str] = []
    decoded_bytes = 0
    for instruction in disassembler.disasm(code, va):
        instructions.append(f"{instruction.mnemonic} {instruction.op_str}".strip())
        decoded_bytes += instruction.size
        if decoded_bytes >= min(8, len(code)) or len(instructions) >= 5:
            break
    return instructions, decoded_bytes


def validate_row(
    candidate: dict,
    inventory_by_rva: dict[int, dict],
    pe: pefile.PE,
    exact_binary_match: bool,
) -> dict:
    rva = int(candidate["redux_rva"])
    image_base = int(pe.OPTIONAL_HEADER.ImageBase)
    expected_va = image_base + rva
    inventory = inventory_by_rva.get(rva)
    failures: list[str] = []
    warnings: list[str] = []

    if not exact_binary_match:
        failures.append("binary SHA-256 does not match the analyzed corpus")
    if inventory is None:
        failures.append("no exact function-start row in the Ghidra inventory")
        inventory = {}

    inventory_va = parse_int(inventory.get("entry_va"))
    body_min = parse_int(inventory.get("body_min_va"))
    body_max = parse_int(inventory.get("body_max_va"))
    is_external = bool_value(inventory.get("is_external"))
    is_thunk = bool_value(inventory.get("is_thunk"))
    if inventory_va is not None and inventory_va != expected_va:
        failures.append("inventory VA does not equal PE image base plus candidate RVA")
    if body_min is None or body_max is None:
        failures.append("inventory body bounds are missing")
    else:
        if not body_min <= expected_va <= body_max:
            failures.append("function entry lies outside inventory body bounds")
        if body_min != expected_va:
            failures.append("function entry is not the minimum inventory body address")
    if is_external:
        failures.append("inventory function is external")
    if is_thunk:
        warnings.append("inventory function is a thunk; rename application is held")

    section = section_for_rva(pe, rva)
    section_name = ""
    section_executable = False
    code = b""
    if section is None:
        failures.append("candidate RVA does not map to a PE section")
    else:
        section_name = section.Name.rstrip(b"\0").decode("ascii", errors="replace")
        section_executable = bool(int(section.Characteristics) & EXECUTE_FLAG)
        if not section_executable:
            failures.append("candidate RVA is not in an executable PE section")
        body_size = body_max - body_min + 1 if body_min is not None and body_max is not None else 16
        read_size = max(1, min(16, body_size))
        try:
            code = pe.get_data(rva, read_size)
        except Exception:
            code = b""
        if not code:
            failures.append("entry bytes could not be read from the PE")

    instructions: list[str] = []
    decoded_bytes = 0
    if code:
        if all(byte in {0x00, 0xCC} for byte in code):
            failures.append("entry bytes are only zero/int3 padding")
        instructions, decoded_bytes = decode_entry(code, expected_va)
        if not instructions:
            failures.append("Capstone could not decode the function entry")
        else:
            first_mnemonic = instructions[0].split(" ", 1)[0]
            if first_mnemonic in BAD_FIRST_MNEMONICS:
                failures.append(f"entry begins with disallowed instruction {first_mnemonic}")
            if first_mnemonic == "ret":
                warnings.append("entry is a one-instruction return stub")
        required_decode = min(5, len(code))
        if decoded_bytes < required_decode:
            failures.append(f"decoded only {decoded_bytes} of required {required_decode} entry bytes")

    namespace, name = split_qualified_name(candidate["pdb_name"])
    rename_safe = safe_rename(namespace, name)
    if not rename_safe:
        warnings.append("qualified name requires comment-only handling or sanitization")

    boundary_valid = not failures
    prior_agreement = candidate.get("prior_name_agreement", "unknown")
    confidence = candidate.get("confidence", "")
    identity_apply_grade = confidence in {"registration_exact", "very_high"}
    semantic_review_grade = confidence == "high"
    net_new = bool_value(candidate.get("net_new_name_candidate"))

    if failures:
        disposition = "blocked_boundary_or_binary"
    elif prior_agreement == "no":
        disposition = "blocked_name_conflict"
    elif is_thunk:
        disposition = "comment_only_thunk"
    elif identity_apply_grade and prior_agreement == "yes":
        disposition = "verified_existing"
    elif identity_apply_grade and net_new and rename_safe:
        disposition = "safe_new_apply"
    elif identity_apply_grade:
        disposition = "comment_only_identity"
    elif semantic_review_grade and net_new and rename_safe:
        disposition = "high_review_ready"
    elif confidence == "medium" and net_new:
        disposition = "medium_hold"
    else:
        disposition = "not_apply_grade"

    result = dict(candidate)
    result.update(
        {
            "binary_exact_match": exact_binary_match,
            "boundary_valid": boundary_valid,
            "disposition": disposition,
            "qualified_name": candidate["pdb_name"],
            "apply_namespace": namespace,
            "apply_name": name,
            "rename_safe": rename_safe,
            "entry_va_expected": expected_va,
            "inventory_entry_va": inventory_va if inventory_va is not None else "",
            "inventory_body_min_va": body_min if body_min is not None else "",
            "inventory_body_max_va": body_max if body_max is not None else "",
            "inventory_is_thunk": is_thunk,
            "inventory_is_external": is_external,
            "pe_section": section_name,
            "pe_section_executable": section_executable,
            "prologue_hex": code.hex(" "),
            "prologue_sha256": hashlib.sha256(code).hexdigest() if code else "",
            "decoded_bytes": decoded_bytes,
            "entry_instructions": " | ".join(instructions),
            "validation_failures": "; ".join(failures),
            "validation_warnings": "; ".join(warnings),
        }
    )
    return result


def render_summary(path: Path, summary: dict, review_rows: list[dict]) -> None:
    lines = [
        "# Semantic PDB Binary/Boundary Validation",
        "",
        f"- Binary: `{summary['binary_path']}`",
        f"- SHA-256: `{summary['binary_sha256']}`",
        f"- Expected corpus SHA-256: `{summary['expected_binary_sha256']}`",
        f"- Exact analyzed-binary match: `{summary['binary_exact_match']}`",
        "",
        "## Dispositions",
        "",
    ]
    for name, count in summary["disposition_counts"].items():
        lines.append(f"- {name}: `{count}`")
    lines.extend(
        [
            "",
            "## Net-New High-Confidence Review Queue",
            "",
            "| Score | RVA | Name | Prologue | First instructions |",
            "|---:|---:|---|---|---|",
        ]
    )
    for row in review_rows[:60]:
        lines.append(
            f"| {row['score']} | 0x{int(row['redux_rva']):x} | {row['qualified_name'].replace('|', '/')} | "
            f"`{row['prologue_hex']}` | {row['entry_instructions'].replace('|', '/')} |"
        )
    lines.extend(
        [
            "",
            "`safe_new_apply.tsv` is the only rename-ready queue. High-confidence rows remain",
            "review-only because static boundary validation proves the address, not the semantic identity.",
            "Steam runtime use still requires comparing these fingerprints after SteamStub settles.",
        ]
    )
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def main() -> None:
    parser = argparse.ArgumentParser(description="Validate semantic PDB candidates against the exact analyzed PE.")
    parser.add_argument("--ranking-dir", type=Path, default=DEFAULT_RANKING_DIR)
    parser.add_argument("--binary", type=Path, help="Exact analyzed PE; auto-discovers an SHA-matching local baseline when omitted")
    parser.add_argument("--inventory", type=Path, default=DEFAULT_INVENTORY)
    parser.add_argument("--manifest", type=Path, default=DEFAULT_MANIFEST)
    parser.add_argument("--output-dir", type=Path, help="Defaults to <ranking-dir>/binary_validation")
    args = parser.parse_args()

    ranking_dir = args.ranking_dir.resolve()
    output_dir = args.output_dir.resolve() if args.output_dir else ranking_dir / "binary_validation"
    manifest = json.loads(args.manifest.resolve().read_text(encoding="utf-8-sig"))
    expected_sha = str(manifest["binary_sha256"]).lower()
    binary = resolve_default_binary(args.binary, expected_sha)
    actual_sha = sha256_file(binary).lower()
    exact_binary_match = actual_sha == expected_sha

    candidates = read_csv(ranking_dir / "current_function_best_matches.csv")
    inventory_rows = read_csv(args.inventory.resolve())
    inventory_by_rva = {int(row["entry_rva"]): row for row in inventory_rows if row.get("entry_rva")}
    pe = pefile.PE(str(binary), fast_load=False)

    validated = [validate_row(row, inventory_by_rva, pe, exact_binary_match) for row in candidates]
    validated.sort(key=lambda row: (-int(row["score"]), int(row["redux_rva"])))
    dispositions: dict[str, list[dict]] = {}
    for row in validated:
        dispositions.setdefault(row["disposition"], []).append(row)

    output_fields = list(validated[0].keys()) if validated else []
    write_csv(output_dir / "prologue_boundary_validation.csv", validated, output_fields)
    write_csv(
        output_dir / "blocked_candidates.csv",
        [row for row in validated if row["disposition"].startswith("blocked")],
        output_fields,
    )

    apply_fields = [
        "redux_va",
        "redux_rva",
        "apply_namespace",
        "apply_name",
        "qualified_name",
        "confidence",
        "score",
        "pdb_signature",
        "pdb_source_files",
        "pdb_source_line_min",
        "pdb_source_line_max",
        "prologue_hex",
        "prologue_sha256",
        "inventory_body_min_va",
        "inventory_body_max_va",
        "bsim_similarity",
        "bsim_significance",
        "reasons",
        "caveats",
    ]
    queue_files = {
        "verified_existing.tsv": {"verified_existing"},
        "safe_new_apply.tsv": {"safe_new_apply"},
        "high_confidence_review.tsv": {"high_review_ready"},
        "medium_hold.tsv": {"medium_hold"},
        "comment_only_hints.tsv": {"comment_only_identity", "comment_only_thunk"},
    }
    for file_name, included_dispositions in queue_files.items():
        queue_rows = [row for row in validated if row["disposition"] in included_dispositions]
        write_tsv(output_dir / file_name, queue_rows, apply_fields)

    disposition_counts = Counter(row["disposition"] for row in validated)
    summary = {
        "binary_path": str(binary),
        "binary_sha256": actual_sha,
        "expected_binary_sha256": expected_sha,
        "binary_exact_match": exact_binary_match,
        "image_base": int(pe.OPTIONAL_HEADER.ImageBase),
        "candidate_count": len(validated),
        "boundary_valid_count": sum(bool_value(row["boundary_valid"]) for row in validated),
        "disposition_counts": dict(sorted(disposition_counts.items())),
    }
    (output_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")
    render_summary(output_dir / "SUMMARY.md", summary, dispositions.get("high_review_ready", []))
    print(json.dumps(summary, indent=2))


if __name__ == "__main__":
    main()
