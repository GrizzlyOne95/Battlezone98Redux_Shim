from __future__ import annotations

import argparse
import csv
import json
import re
from collections import Counter
from pathlib import Path


def slugify(text: str) -> str:
    slug = re.sub(r"[^A-Za-z0-9]+", "_", text.strip()).strip("_").lower()
    return slug or "re_query"


def load_index(promoted_root: Path) -> dict:
    return json.loads((promoted_root / "current_index.json").read_text(encoding="utf-8-sig"))


def load_corpora_config(config_path: Path) -> list[dict]:
    payload = json.loads(config_path.read_text(encoding="utf-8-sig"))
    corpora = payload.get("corpora", [])
    if not corpora:
        raise ValueError(f"No corpora defined in config: {config_path}")
    return corpora


def resolve_config_path(config_path: Path, candidate: str) -> Path:
    root = Path(candidate)
    if root.is_absolute():
        return root
    return (config_path.parent / root).resolve()


def resolve_index_path(promoted_root: Path, candidate: str) -> Path:
    path = Path(candidate)
    if path.is_absolute():
        return path
    return (promoted_root / path).resolve()


def read_csv_rows(path: Path) -> list[dict]:
    if not path.exists():
        return []
    with path.open("r", newline="", encoding="utf-8") as handle:
        return list(csv.DictReader(handle))


def contains_any(text: str, patterns: list[re.Pattern[str]]) -> bool:
    return any(pattern.search(text) for pattern in patterns)


def select_rows(rows: list[dict], patterns: list[re.Pattern[str]], fields: list[str], limit: int) -> list[dict]:
    matches: list[dict] = []
    for row in rows:
        haystack = " ".join(str(row.get(field, "")) for field in fields)
        if contains_any(haystack, patterns):
            matches.append(row)
            if len(matches) >= limit:
                break
    return matches


def rg_hits(root: Path, query: str, globs: list[str], limit: int) -> list[str]:
    import subprocess

    hits: list[str] = []
    seen: set[str] = set()
    terms = [term for term in query.split() if term.strip()]
    for term in terms:
        args = ["rg", "--line-number", "--smart-case", "--max-count", str(limit)]
        for glob in globs:
            args.extend(["-g", glob])
        args.extend([term, str(root)])
        try:
            completed = subprocess.run(args, capture_output=True, text=True, check=False, timeout=3)
        except subprocess.TimeoutExpired:
            continue
        if completed.returncode not in (0, 1):
            continue
        for line in completed.stdout.splitlines():
            if not line.strip() or line in seen:
                continue
            seen.add(line)
            hits.append(line)
            if len(hits) >= limit:
                return hits
    return hits


def format_table(rows: list[dict], fields: list[str]) -> list[str]:
    lines: list[str] = []
    for row in rows:
        parts = [f"{field}={row.get(field, '')}" for field in fields]
        lines.append(f"- {' | '.join(parts)}")
    return lines or ["- <none>"]


def prefix_rows(rows: list[dict], corpus_label: str) -> list[dict]:
    prefixed: list[dict] = []
    for row in rows:
        current = dict(row)
        current["corpus"] = corpus_label
        prefixed.append(current)
    return prefixed


def default_promoted_roots() -> list[Path]:
    roots = [
        Path("reverse_engineering/current_global_corpus"),
        Path("reverse_engineering/repo_corpora/bzr_gog_best_effort"),
        Path("reverse_engineering/current_legacy_global_corpus"),
    ]
    return [root for root in roots if (root / "current_index.json").exists()]


def dedupe_hits(hits: list[str], limit: int) -> list[str]:
    seen: set[str] = set()
    output: list[str] = []
    for hit in hits:
        if hit in seen:
            continue
        seen.add(hit)
        output.append(hit)
        if len(output) >= limit:
            break
    return output


def main() -> None:
    parser = argparse.ArgumentParser(description="Build a starter reverse-engineering brief from the promoted corpus.")
    parser.add_argument("--query", required=True, help="Free-form query text.")
    parser.add_argument("--promoted-root", dest="promoted_roots", action="append", type=Path, help="Promoted corpus root. May be passed more than once.")
    parser.add_argument("--config", type=Path, help="Optional corpora config JSON. Uses all configured corpora unless --corpus-label is set.")
    parser.add_argument("--corpus-label", dest="corpus_labels", action="append", help="Corpus label from the config file. May be passed more than once.")
    parser.add_argument("--output-dir", type=Path, default=Path("reverse_engineering/workshop/re_briefs"))
    parser.add_argument("--limit", type=int, default=20)
    args = parser.parse_args()

    query = args.query.strip()
    patterns = [re.compile(re.escape(part), re.IGNORECASE) for part in query.split() if part.strip()]
    if not patterns:
        raise ValueError("Query must contain at least one non-space token.")

    selected_corpora: list[dict] = []
    if args.config:
        config_path = args.config.resolve()
        configured = load_corpora_config(config_path)
        selected_labels = {label.lower() for label in (args.corpus_labels or [])}
        for corpus in configured:
            label = str(corpus.get("label", "")).strip()
            if selected_labels and label.lower() not in selected_labels:
                continue
            promoted_root = resolve_config_path(config_path, str(corpus["promoted_root"]))
            selected_corpora.append({"label": label or promoted_root.name, "promoted_root": promoted_root})
    elif args.promoted_roots:
        for index, promoted_root in enumerate(args.promoted_roots, start=1):
            selected_corpora.append({"label": f"corpus{index}", "promoted_root": promoted_root.resolve()})
    else:
        for promoted_root in default_promoted_roots():
            label = "legacy" if promoted_root.name == "current_legacy_global_corpus" else "redux"
            selected_corpora.append({"label": label, "promoted_root": promoted_root.resolve()})

    if not selected_corpora:
        raise ValueError("No promoted corpora selected. Pass --config, --promoted-root, or ensure default promoted corpora exist.")

    function_hits: list[dict] = []
    symbol_hits: list[dict] = []
    merged_hits: list[dict] = []
    pdb_hits: list[dict] = []
    module_hits: list[dict] = []
    decomp_hits_all: list[str] = []
    corpus_summaries: list[dict] = []
    trust_counter: Counter[str] = Counter()

    for corpus in selected_corpora:
        promoted_root = Path(corpus["promoted_root"])
        label = str(corpus["label"])
        index = load_index(promoted_root)
        manifest = index["manifest"]
        corpus_root = resolve_index_path(promoted_root, str(index["current_corpus_root"]))
        trust = "exact" if manifest.get("pdb_exact_match") else "advisory"
        trust_counter[trust] += 1
        corpus_summaries.append(
            {
                "label": label,
                "binary_path": manifest.get("binary_path", ""),
                "corpus_root": str(corpus_root),
                "decomp_dir": manifest.get("decomp_dir", ""),
                "pdb_exact_match": str(manifest.get("pdb_exact_match", False)).lower(),
                "merged_rva_names": str(manifest.get("counts", {}).get("merged_rva_names", "")),
            }
        )

        inventory_dir = resolve_index_path(promoted_root, str(manifest["inventory_dir"]))
        pdb_dir = resolve_index_path(promoted_root, str(manifest["pdb_dir"])) if manifest.get("pdb_dir") else None
        decomp_dir = resolve_index_path(promoted_root, str(manifest["decomp_dir"]))

        inventory_functions = read_csv_rows(inventory_dir / "functions.csv")
        inventory_symbols = read_csv_rows(inventory_dir / "symbols.csv")
        merged_matches = read_csv_rows(corpus_root / "merged" / "function_matches_by_rva.csv")
        pdb_publics = read_csv_rows(pdb_dir / "public_functions.csv") if pdb_dir else []
        pdb_modules = read_csv_rows(pdb_dir / "modules.csv") if pdb_dir else []

        function_hits.extend(prefix_rows(select_rows(inventory_functions, patterns, ["name", "signature", "namespace"], args.limit), label))
        symbol_hits.extend(prefix_rows(select_rows(inventory_symbols, patterns, ["name", "namespace", "symbol_type"], args.limit), label))
        merged_hits.extend(prefix_rows(select_rows(merged_matches, patterns, ["ghidra_name", "pdb_name", "ghidra_signature"], args.limit), label))
        pdb_hits.extend(prefix_rows(select_rows(pdb_publics, patterns, ["name"], args.limit), label))
        module_hits.extend(prefix_rows(select_rows(pdb_modules, patterns, ["module_name", "object_name"], args.limit), label))
        decomp_hits_all.extend([f"[{label}] {line}" for line in rg_hits(decomp_dir, query, ["*.c"], args.limit)])

    function_hits = function_hits[: args.limit]
    symbol_hits = symbol_hits[: args.limit]
    merged_hits = merged_hits[: args.limit]
    pdb_hits = pdb_hits[: args.limit]
    module_hits = module_hits[: args.limit]
    note_hits = rg_hits(Path("reverse_engineering"), query, ["*.md", "*.txt"], args.limit)
    decomp_hits = dedupe_hits(decomp_hits_all, args.limit)

    output_dir = args.output_dir.resolve()
    output_dir.mkdir(parents=True, exist_ok=True)
    slug = slugify(query)
    brief_path = output_dir / f"{slug}.md"

    query_tokens = ", ".join(pattern.pattern for pattern in patterns)
    trust_summary = ", ".join(f"{count} {name}" for name, count in sorted(trust_counter.items()))
    lines = [
        f"# RE Brief: {query}",
        "",
        f"- Query tokens: `{query_tokens}`",
        f"- Corpora searched: `{', '.join(summary['label'] for summary in corpus_summaries)}`",
        f"- Corpus trust mix: `{trust_summary}`",
        "",
        "## Corpora",
        "",
        *format_table(corpus_summaries, ["label", "pdb_exact_match", "merged_rva_names", "binary_path", "corpus_root", "decomp_dir"]),
        "",
        "## Inventory Functions",
        "",
        *format_table(function_hits, ["corpus", "entry_rva", "name", "namespace", "signature"]),
        "",
        "## Inventory Symbols",
        "",
        *format_table(symbol_hits, ["corpus", "address_rva", "name", "namespace", "symbol_type"]),
        "",
        "## Ghidra/PDB RVA Matches",
        "",
        *format_table(merged_hits, ["corpus", "entry_rva", "ghidra_name", "pdb_name"]),
        "",
        "## PDB Public Functions",
        "",
        *format_table(pdb_hits, ["corpus", "rva", "name"]),
        "",
        "## PDB Modules",
        "",
        *format_table(module_hits, ["corpus", "module_name", "object_name"]),
        "",
        "## Existing Notes Hits",
        "",
    ]
    lines.extend([f"- `{line}`" for line in note_hits] or ["- <none>"])
    lines.extend(
        [
            "",
            "## Decompiled Code Hits",
            "",
        ]
    )
    lines.extend([f"- `{line}`" for line in decomp_hits] or ["- <none>"])
    lines.extend(
        [
            "",
            "## Recommended Next Steps",
            "",
            "- Start with legacy exact-match hits for semantics and class names, then compare equivalent Redux hits for current patch targets.",
            "- Treat Redux PDB-derived names as advisory until strings, callers, globals, or decomp structure confirm them.",
            "- Open the matching decomp files under the listed decomp dirs and confirm behavior against nearby strings and call patterns.",
            "- Only move to interactive Ghidra after the combined corpus search stops narrowing the target meaningfully.",
            "- Record validated findings in a dedicated note under `reverse_engineering/` or `reverse_engineering/workshop/`.",
        ]
    )
    brief_path.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(brief_path)


if __name__ == "__main__":
    main()
