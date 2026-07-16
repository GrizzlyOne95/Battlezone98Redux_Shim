from __future__ import annotations

import argparse
import json
import shutil
from pathlib import Path


def load_json(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def copy_if_exists(src: Path, dst: Path) -> bool:
    if not src.exists():
        return False
    dst.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(src, dst)
    return True


def write_json(path: Path, payload: dict) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(payload, indent=2), encoding="utf-8")


def write_readme(path: Path, state: dict) -> None:
    lines = [
        "# Current Global Decompile Corpus",
        "",
        f"- Current corpus root: `{state['current_corpus_root']}`",
        f"- Promoted on: `{state['promoted_from']}`",
        "",
        "## Primary Search Targets",
        "",
    ]
    for item in state["search_targets"]:
        lines.append(f"- `{item['label']}`: `{item['path']}`")
    lines.extend(
        [
            "",
            "## Usage",
            "",
            "Search the promoted corpus with:",
            "",
            "```powershell",
            ".\\reverse_engineering\\search_global_corpus.ps1 -Pattern \"Producer::StartBuild\"",
            "```",
            "",
            "Use the pointer files here instead of hardcoding one-off output paths.",
        ]
    )
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def main() -> None:
    parser = argparse.ArgumentParser(description="Promote a finished decompile corpus into a stable current-corpus index.")
    parser.add_argument("--output-root", type=Path, required=True)
    parser.add_argument("--promoted-root", type=Path, default=Path("reverse_engineering/current_global_corpus"))
    args = parser.parse_args()

    output_root = args.output_root.resolve()
    promoted_root = args.promoted_root.resolve()
    manifest_path = output_root / "pipeline_manifest.json"
    summary_path = output_root / "SUMMARY.md"

    if not manifest_path.exists():
        raise FileNotFoundError(f"Missing pipeline manifest: {manifest_path}")

    manifest = load_json(manifest_path)
    promoted_root.mkdir(parents=True, exist_ok=True)

    pointers = {
        "manifest": manifest,
        "current_corpus_root": str(output_root),
        "promoted_from": str(output_root),
        "search_targets": [
            {"label": "Summary", "path": str(summary_path)},
            {"label": "Pipeline Manifest", "path": str(manifest_path)},
            {"label": "Inventory Functions", "path": str(output_root / "inventory" / "functions.csv")},
            {"label": "Inventory Symbols", "path": str(output_root / "inventory" / "symbols.csv")},
            {"label": "Merged RVA Matches", "path": str(output_root / "merged" / "function_matches_by_rva.csv")},
            {"label": "Advisory Private RVA Matches", "path": str(output_root / "merged" / "private_function_matches_by_rva.csv")},
            {"label": "Legacy Symbol Enriched Functions", "path": str(output_root / "merged" / "legacy_symbol_enriched_functions.csv")},
            {"label": "PDB Public Functions", "path": str(output_root / "pdb_reference" / "public_functions.csv")},
            {"label": "PDB Private Functions", "path": str(output_root / "pdb_reference" / "private_functions.csv")},
            {"label": "PDB Private Locals", "path": str(output_root / "pdb_reference" / "private_locals.csv")},
            {"label": "PDB Local Location Ranges", "path": str(output_root / "pdb_reference" / "private_local_ranges.csv")},
            {"label": "PDB Source Line Ranges", "path": str(output_root / "pdb_reference" / "source_line_ranges.csv")},
            {"label": "PDB Class Layouts", "path": str(output_root / "pdb_reference" / "class_layouts.csv")},
            {"label": "PDB Class Members", "path": str(output_root / "pdb_reference" / "class_members.csv")},
            {"label": "Semantic PDB Function Matches", "path": str(output_root / "pdb_reference" / "semantic_ranking" / "current_function_best_matches.csv")},
            {"label": "Semantic PDB Gameplay Review Queue", "path": str(output_root / "pdb_reference" / "semantic_ranking" / "gameplay_engine_review_queue.csv")},
            {"label": "Semantic PDB Net-New Name Queue", "path": str(output_root / "pdb_reference" / "semantic_ranking" / "net_new_name_review_queue.csv")},
            {"label": "Semantic PDB Binary Validation", "path": str(output_root / "pdb_reference" / "semantic_ranking" / "binary_validation" / "prologue_boundary_validation.csv")},
            {"label": "Semantic PDB Safe Apply Queue", "path": str(output_root / "pdb_reference" / "semantic_ranking" / "binary_validation" / "safe_new_apply.tsv")},
            {"label": "Semantic PDB High Review Queue", "path": str(output_root / "pdb_reference" / "semantic_ranking" / "binary_validation" / "high_confidence_review.tsv")},
            {"label": "Semantic PDB Medium Hold Queue", "path": str(output_root / "pdb_reference" / "semantic_ranking" / "binary_validation" / "medium_hold.tsv")},
            {"label": "Semantic PDB Local Hints", "path": str(output_root / "pdb_reference" / "semantic_ranking" / "current_function_local_hints.csv")},
            {"label": "Same-RVA PDB Reassessment", "path": str(output_root / "pdb_reference" / "semantic_ranking" / "same_rva_candidates_reassessed.csv")},
            {"label": "PDB Modules", "path": str(output_root / "pdb_reference" / "modules.csv")},
            {"label": "ASCII Strings", "path": str(output_root / "binary_strings" / "ascii_strings.csv")},
            {"label": "UTF16 Strings", "path": str(output_root / "binary_strings" / "utf16_strings.csv")},
            {"label": "Decomp Root", "path": manifest["decomp_dir"]},
        ],
    }

    write_json(promoted_root / "current_manifest.json", manifest)
    write_json(promoted_root / "current_index.json", pointers)
    (promoted_root / "CURRENT_ROOT.txt").write_text(str(output_root) + "\n", encoding="utf-8")
    copy_if_exists(summary_path, promoted_root / "CURRENT_SUMMARY.md")
    copy_if_exists(output_root / "pdb_reference" / "reference.json", promoted_root / "CURRENT_PDB_REFERENCE.json")
    write_readme(promoted_root / "README.md", pointers)

    print(json.dumps({"promoted_root": str(promoted_root), "corpus_root": str(output_root)}, indent=2))


if __name__ == "__main__":
    main()
