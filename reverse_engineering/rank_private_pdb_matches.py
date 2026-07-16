from __future__ import annotations

import argparse
import csv
import json
import math
import re
from collections import Counter, defaultdict
from pathlib import Path


DEFAULT_PDB_INDEX = Path("reverse_engineering/workshop/private_pdb_index")
DEFAULT_BSIM_MAP = Path(
    "reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/bsim/out/legacy_to_redux_symbol_map.bsim.csv"
)
DEFAULT_LUA_MAP = Path("reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/bsim/out/lua_api_map.csv")
DEFAULT_BSIM_APPLIED = Path("reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/bsim/out/redux_named.csv")
DEFAULT_LUA_APPLIED = Path(
    "reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/bsim/out/lua_bindings_applied.csv"
)
DEFAULT_INVENTORY = Path("reverse_engineering/repo_corpora/bzr_gog_best_effort/inventory/functions.csv")
DEFAULT_DECOMP_DIR = Path(
    "reverse_engineering/repo_corpora/bzr_gog_best_effort/ghidrecomp/results/bins/"
    "battlezone98redux.exe-6777ca/decomps"
)

DEFAULT_NAME_PATTERN = re.compile(r"^(?:FUN|LAB|SUB)_[0-9A-Fa-f]+$")
NAME_PART_PATTERN = re.compile(r"[A-Z]+(?=[A-Z][a-z]|\d|$)|[A-Z]?[a-z]+|\d+")
GENERIC_NAME_PARTS = {
    "class",
    "create",
    "delete",
    "destroy",
    "execute",
    "find",
    "get",
    "global",
    "has",
    "init",
    "load",
    "operator",
    "save",
    "set",
    "state",
    "update",
}
CONFIDENCE_ORDER = {
    "rejected": 0,
    "ambiguous": 1,
    "low": 2,
    "medium": 3,
    "high": 4,
    "very_high": 5,
    "registration_exact": 6,
}


def read_csv(path: Path) -> list[dict]:
    if not path.exists():
        return []
    with path.open("r", newline="", encoding="utf-8-sig") as handle:
        return list(csv.DictReader(handle))


def write_csv(path: Path, rows: list[dict], fieldnames: list[str]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=fieldnames, extrasaction="ignore")
        writer.writeheader()
        writer.writerows(rows)


def parse_int(value: str | int | None) -> int | None:
    if value is None or value == "":
        return None
    try:
        return int(str(value), 0)
    except ValueError:
        return None


def parse_float(value: str | float | None) -> float | None:
    if value is None or value == "":
        return None
    try:
        return float(value)
    except ValueError:
        return None


def normalize_symbol(value: str) -> str:
    destructor = re.match(r"^(.*)::`(?:scalar|vector) deleting destructor'$", value)
    if destructor:
        owner = destructor.group(1)
        value = f"{owner}::~{owner.rsplit('::', 1)[-1]}"
    return re.sub(r"[^a-z0-9~]+", "", value.lower())


def legacy_full_name(row: dict) -> str:
    name = row.get("legacy_name", "")
    namespace = row.get("legacy_namespace", "")
    if not namespace or namespace in {"Global", "<global>"}:
        return name
    return f"{namespace}::{name}"


def split_parameters(value: str) -> list[str] | None:
    end = value.rfind(")")
    if end < 0:
        return None
    depth = 0
    start = -1
    for index in range(end, -1, -1):
        char = value[index]
        if char == ")":
            depth += 1
        elif char == "(":
            depth -= 1
            if depth == 0:
                start = index
                break
    if start < 0:
        return None
    payload = value[start + 1 : end].strip()
    if not payload or payload == "void":
        return []
    parts: list[str] = []
    token: list[str] = []
    nesting = 0
    for char in payload:
        if char in "<([":
            nesting += 1
        elif char in ">)]" and nesting:
            nesting -= 1
        if char == "," and nesting == 0:
            parts.append("".join(token).strip())
            token = []
        else:
            token.append(char)
    parts.append("".join(token).strip())
    return parts


def signature_arity(signature: str, remove_this: bool = False) -> int | None:
    parts = split_parameters(signature)
    if parts is None:
        return None
    if remove_this and parts and re.search(r"\bthis\b", parts[0]):
        parts = parts[1:]
    return len(parts)


def name_tokens(value: str) -> list[str]:
    parts: list[str] = []
    for chunk in re.split(r"[^A-Za-z0-9]+", value):
        parts.extend(NAME_PART_PATTERN.findall(chunk))
    return sorted(
        {
            part.lower()
            for part in parts
            if len(part) >= 4 and part.lower() not in GENERIC_NAME_PARTS and not part.isdigit()
        }
    )


def source_component(source_files: str, registration_exact: bool) -> str:
    if registration_exact:
        return "lua_api"
    source = source_files.lower().replace("/", "\\")
    if "\\source\\" in source:
        return source.split("\\source\\", 1)[1].split("\\", 1)[0]
    if "microsoft visual studio" in source:
        return "msvc"
    return "other" if source else "unknown"


def bsim_base_confidence(row: dict) -> tuple[str, int, list[str], list[str]]:
    combined = row.get("combined_confidence", "")
    agreement = row.get("bsim_agreement", "")
    similarity = parse_float(row.get("bsim_similarity"))
    significance = parse_float(row.get("bsim_significance"))
    reasons: list[str] = ["qualified PDB name agrees with exact-symbol legacy name"]
    caveats: list[str] = []

    if agreement == "exact":
        reasons.append("BSim and text-shingle mapping independently agree on the Redux RVA")
        return "very_high", 85, reasons, caveats

    if agreement == "diff" or combined in {"low_conflict", "medium_conflict"}:
        caveats.append("BSim and text-shingle mappings disagree")
        return "ambiguous", 20, reasons, caveats
    if combined == "collision_ambiguous":
        caveats.append("BSim reports a collision-prone function family")
        return "ambiguous", 18, reasons, caveats

    if not row.get("bsim_redux_rva"):
        if combined == "text_very_high":
            reasons.append("very-high text/shingle mapping")
            return "high", 68, reasons, caveats
        if combined == "text_medium":
            reasons.append("medium text/shingle mapping")
            return "medium", 48, reasons, caveats
        caveats.append("text-only mapping without BSim corroboration")
        return "low", 30, reasons, caveats

    if combined == "high":
        reasons.append("high BSim mapping confidence")
        return "high", 70, reasons, caveats
    if combined == "medium":
        if similarity is not None and significance is not None and similarity >= 0.85 and significance >= 30:
            reasons.append("strong BSim similarity and significance")
            return "high", 66, reasons, caveats
        reasons.append("medium BSim mapping confidence")
        return "medium", 52, reasons, caveats

    if similarity is not None and significance is not None:
        if significance >= 100 and similarity >= 0.55:
            reasons.append("rare BSim match with very high significance")
            return "high", 66, reasons, caveats
        if significance >= 40 and similarity >= 0.70:
            reasons.append("strong BSim similarity/significance pair")
            return "high", 64, reasons, caveats
        if significance >= 30 and similarity >= 0.60:
            reasons.append("useful BSim similarity/significance pair")
            return "medium", 50, reasons, caveats

    caveats.append("low-confidence BSim-only mapping")
    return "low", 34, reasons, caveats


def lower_confidence(confidence: str, steps: int = 1) -> str:
    levels = ["rejected", "ambiguous", "low", "medium", "high", "very_high", "registration_exact"]
    index = levels.index(confidence)
    return levels[max(0, index - steps)]


def decomp_file_map(root: Path) -> dict[int, Path]:
    output: dict[int, Path] = {}
    if not root.exists():
        return output
    for path in root.glob("*.c"):
        match = re.search(r"-([0-9A-Fa-f]{8})\.c$", path.name)
        if match:
            output[int(match.group(1), 16)] = path
    return output


def enrich_candidate(
    pdb_row: dict,
    mapping_row: dict,
    target_rva: int,
    inventory_by_rva: dict[int, dict],
    decomp_by_va: dict[int, Path],
    pdb_name_count: int,
    registration_exact: bool = False,
) -> dict:
    inventory = inventory_by_rva.get(target_rva, {})
    entry_va = parse_int(inventory.get("entry_va"))
    if entry_va is None:
        entry_va = target_rva + 0x400000
    current_name = inventory.get("name", "")
    current_namespace = inventory.get("namespace", "")
    current_full = current_name if current_namespace in {"", "Global"} else f"{current_namespace}::{current_name}"

    confidence, score, reasons, caveats = bsim_base_confidence(mapping_row)
    if registration_exact:
        confidence = "registration_exact"
        score = 100
        reasons = [
            "PDB global lua_State wrapper agrees with the exact Lua registration-table API name",
            "registration table supplies the current Redux function pointer",
        ]
        caveats = []

    pdb_arity = signature_arity(pdb_row.get("signature", ""))
    legacy_namespace = mapping_row.get("legacy_namespace", "")
    legacy_arity = signature_arity(
        mapping_row.get("legacy_signature", ""),
        remove_this=bool(legacy_namespace and legacy_namespace not in {"Global", "<global>"}),
    )
    arity_agreement = "unknown"
    if pdb_arity is not None and legacy_arity is not None:
        if pdb_arity == legacy_arity:
            arity_agreement = "yes"
            score += 5
            reasons.append(f"PDB and legacy signatures agree on {pdb_arity} explicit parameter(s)")
        else:
            arity_agreement = "no"
            score -= 15
            caveats.append(f"signature arity differs: PDB {pdb_arity}, legacy {legacy_arity}")
            confidence = "rejected" if registration_exact else lower_confidence(confidence)

    current_name_agreement = False
    if current_name and not DEFAULT_NAME_PATTERN.match(current_name):
        current_name_agreement = normalize_symbol(current_full) == normalize_symbol(pdb_row.get("name", ""))
        if current_name_agreement:
            score += 5
            reasons.append("current Ghidra name independently agrees")

    rank2_similarity = parse_float(mapping_row.get("bsim_rank2_similarity"))
    similarity = parse_float(mapping_row.get("bsim_similarity"))
    rank_margin: float | None = None
    if rank2_similarity is not None and similarity is not None:
        rank_margin = similarity - rank2_similarity
        if rank_margin < 0.02:
            score -= 8
            caveats.append("BSim first/second candidate similarity margin is under 0.02")
            if confidence not in {"registration_exact", "very_high"}:
                confidence = "ambiguous"
        elif rank_margin >= 0.10:
            score += 3
            reasons.append("BSim has a clear rank-2 margin")

    pdb_size = parse_int(pdb_row.get("code_size"))
    body_min = parse_int(inventory.get("body_min_va"))
    body_max = parse_int(inventory.get("body_max_va"))
    current_size = body_max - body_min + 1 if body_min is not None and body_max is not None else None
    size_ratio: float | None = None
    if pdb_size and current_size:
        size_ratio = current_size / pdb_size
        if 0.8 <= size_ratio <= 1.25:
            score += 3
            reasons.append("function body sizes agree within 25%")
        elif size_ratio < 0.2 or size_ratio > 5:
            score -= 3
            caveats.append("function body sizes differ by more than 5x")

    decomp_path = decomp_by_va.get(entry_va)
    token_hits: list[str] = []
    if decomp_path and decomp_path.exists():
        decomp_text = decomp_path.read_text(encoding="utf-8", errors="replace").lower()
        token_hits = [token for token in name_tokens(pdb_row.get("name", "")) if token in decomp_text]
        if token_hits:
            score += min(3, len(token_hits))
            reasons.append(f"decompile contains name token(s): {', '.join(token_hits[:4])}")

    same_rva = parse_int(pdb_row.get("rva")) == target_rva
    if same_rva:
        score += 1
        reasons.append("PDB and current Redux RVAs also happen to align")

    if pdb_name_count > 1:
        caveats.append(f"PDB contains {pdb_name_count} records/overloads with this qualified name")

    score = max(0, min(100, score))
    return {
        "score": score,
        "confidence": confidence,
        "pdb_name": pdb_row.get("name", ""),
        "pdb_module_index": pdb_row.get("module_index", ""),
        "pdb_symbol_record_offset": pdb_row.get("symbol_record_offset", ""),
        "pdb_signature": pdb_row.get("signature", ""),
        "pdb_rva": pdb_row.get("rva", ""),
        "pdb_code_size": pdb_row.get("code_size", ""),
        "pdb_module": pdb_row.get("module_name", ""),
        "pdb_object": pdb_row.get("object_name", ""),
        "pdb_source_files": pdb_row.get("source_files", ""),
        "pdb_source_line_min": pdb_row.get("source_line_min", ""),
        "pdb_source_line_max": pdb_row.get("source_line_max", ""),
        "source_component": source_component(pdb_row.get("source_files", ""), registration_exact),
        "pdb_local_count": pdb_row.get("local_count", ""),
        "pdb_parameter_count": pdb_row.get("parameter_count", ""),
        "pdb_name_record_count": pdb_name_count,
        "legacy_name": mapping_row.get("legacy_name", ""),
        "legacy_namespace": mapping_row.get("legacy_namespace", ""),
        "legacy_signature": mapping_row.get("legacy_signature", ""),
        "legacy_entry_va": mapping_row.get("legacy_entry_va", mapping_row.get("legacy_va", "")),
        "redux_rva": target_rva,
        "redux_va": entry_va,
        "redux_current_name": current_name,
        "redux_current_namespace": current_namespace,
        "redux_current_signature": inventory.get("signature", ""),
        "redux_body_size": current_size if current_size is not None else "",
        "mapping_source": "lua_registration" if registration_exact else (
            "bsim" if mapping_row.get("bsim_redux_rva") else "text_map"
        ),
        "registration_exact": registration_exact,
        "bsim_agreement": mapping_row.get("bsim_agreement", ""),
        "bsim_combined_confidence": mapping_row.get("combined_confidence", ""),
        "bsim_similarity": mapping_row.get("bsim_similarity", ""),
        "bsim_significance": mapping_row.get("bsim_significance", ""),
        "bsim_rank2_rva": mapping_row.get("bsim_rank2_rva", ""),
        "bsim_rank2_similarity": mapping_row.get("bsim_rank2_similarity", ""),
        "bsim_rank_margin": f"{rank_margin:.4f}" if rank_margin is not None else "",
        "bsim_target_fanin": mapping_row.get("bsim_target_fanin", ""),
        "signature_arity_agreement": arity_agreement,
        "current_name_agreement": current_name_agreement,
        "same_rva": same_rva,
        "body_size_ratio": f"{size_ratio:.4f}" if size_ratio is not None else "",
        "decomp_token_hits": "|".join(token_hits),
        "decomp_path": str(decomp_path) if decomp_path else "",
        "reasons": "; ".join(reasons),
        "caveats": "; ".join(caveats),
    }


def deduplicate_candidates(rows: list[dict]) -> list[dict]:
    grouped: dict[tuple[str, str, int], list[dict]] = defaultdict(list)
    for row in rows:
        key = (normalize_symbol(row["pdb_name"]), row["pdb_signature"], int(row["redux_rva"]))
        grouped[key].append(row)

    output: list[dict] = []
    for candidates in grouped.values():
        candidates.sort(
            key=lambda row: (
                bool(row["registration_exact"]),
                CONFIDENCE_ORDER[row["confidence"]],
                int(row["score"]),
                parse_float(row.get("bsim_significance")) or -math.inf,
            ),
            reverse=True,
        )
        best = dict(candidates[0])
        best["duplicate_evidence_rows"] = len(candidates)
        best["pdb_source_files"] = "|".join(
            dict.fromkeys(row["pdb_source_files"] for row in candidates if row["pdb_source_files"])
        )
        output.append(best)
    return output


def apply_target_ambiguity(rows: list[dict]) -> None:
    by_target: dict[int, list[dict]] = defaultdict(list)
    for row in rows:
        by_target[int(row["redux_rva"])].append(row)

    for candidates in by_target.values():
        distinct_names = {normalize_symbol(row["pdb_name"]) for row in candidates}
        ranked = sorted(candidates, key=lambda row: int(row["score"]), reverse=True)
        top_score = int(ranked[0]["score"])
        second_score = next(
            (int(row["score"]) for row in ranked[1:] if normalize_symbol(row["pdb_name"]) != normalize_symbol(ranked[0]["pdb_name"])),
            None,
        )
        margin = top_score - second_score if second_score is not None else top_score
        for row in candidates:
            row["target_distinct_name_count"] = len(distinct_names)
            row["target_top_score"] = top_score
            row["target_score_margin"] = margin
            row["is_target_top_candidate"] = int(row["score"]) == top_score
            if (
                len(distinct_names) > 1
                and row["is_target_top_candidate"]
                and margin < 8
                and row["confidence"] != "registration_exact"
            ):
                row["confidence"] = "ambiguous"
                extra = "competing names for this Redux RVA are within 8 score points"
                row["caveats"] = f"{row['caveats']}; {extra}".strip("; ")


def build_applied_name_map(
    bsim_applied: list[dict], lua_applied: list[dict], image_base: int
) -> dict[int, list[str]]:
    output: dict[int, list[str]] = defaultdict(list)
    for row in bsim_applied:
        if row.get("status") != "applied":
            continue
        va = parse_int(row.get("redux_va"))
        if va is None:
            continue
        name = row.get("applied_name", "")
        namespace = row.get("namespace", "")
        output[va - image_base].append(name if not namespace or namespace == "Global" else f"{namespace}::{name}")
    for row in lua_applied:
        if row.get("status") != "applied":
            continue
        va = parse_int(row.get("redux_va"))
        if va is None:
            continue
        output[va - image_base].append(row.get("applied_name", row.get("api_name", "")))
    return output


def apply_prior_name_evidence(rows: list[dict], applied_names: dict[int, list[str]]) -> None:
    for row in rows:
        names = list(dict.fromkeys(applied_names.get(int(row["redux_rva"]), [])))
        row["prior_applied_names"] = "|".join(names)
        row["prior_name_agreement"] = "unknown" if not names else "no"
        row["net_new_name_candidate"] = not names
        if not names:
            continue
        pdb_full = normalize_symbol(row["pdb_name"])
        pdb_leaf = normalize_symbol(row["pdb_name"].rsplit("::", 1)[-1])
        agrees = any(
            normalize_symbol(name) == pdb_full or normalize_symbol(name.rsplit("::", 1)[-1]) == pdb_leaf
            for name in names
        )
        if agrees:
            row["prior_name_agreement"] = "yes"
            row["score"] = min(100, int(row["score"]) + 3)
            row["reasons"] = f"{row['reasons']}; existing BSim/Lua applied-name log agrees".strip("; ")
        else:
            row["score"] = max(0, int(row["score"]) - 10)
            row["caveats"] = (
                f"{row['caveats']}; existing applied-name log uses: {', '.join(names)}"
            ).strip("; ")
            if row["confidence"] != "registration_exact":
                row["confidence"] = "ambiguous"


def same_rva_assessment(
    same_rva_rows: list[dict], semantic_rows: list[dict], bsim_rows: list[dict]
) -> list[dict]:
    semantic_by_name: dict[str, list[dict]] = defaultdict(list)
    for row in semantic_rows:
        semantic_by_name[normalize_symbol(row["pdb_name"])].append(row)

    bsim_by_target: dict[int, list[dict]] = defaultdict(list)
    for row in bsim_rows:
        rva = parse_int(row.get("bsim_redux_rva"))
        if rva is not None:
            bsim_by_target[rva].append(row)

    output: list[dict] = []
    for row in same_rva_rows:
        current_rva = int(row["entry_rva"])
        semantic = semantic_by_name.get(normalize_symbol(row.get("pdb_name", "")), [])
        semantic_targets = sorted({int(item["redux_rva"]) for item in semantic})
        same_target = [item for item in semantic if int(item["redux_rva"]) == current_rva]
        bsim_here = sorted(
            bsim_by_target.get(current_rva, []),
            key=lambda item: parse_float(item.get("bsim_significance")) or -math.inf,
            reverse=True,
        )
        if same_target:
            assessment = "semantically_corroborated"
        elif semantic_targets:
            assessment = "contradicted_by_semantic_mapping"
        elif bsim_here:
            assessment = "conflicts_with_bsim_name_at_same_rva"
        else:
            assessment = "unresolved_rva_only"
        enriched = dict(row)
        enriched.update(
            {
                "assessment": assessment,
                "semantic_target_rvas": "|".join(f"0x{value:x}" for value in semantic_targets),
                "semantic_best_confidence": max(
                    (item["confidence"] for item in semantic),
                    key=lambda value: CONFIDENCE_ORDER[value],
                    default="",
                ),
                "same_rva_bsim_name": legacy_full_name(bsim_here[0]) if bsim_here else "",
                "same_rva_bsim_confidence": bsim_here[0].get("combined_confidence", "") if bsim_here else "",
                "same_rva_bsim_similarity": bsim_here[0].get("bsim_similarity", "") if bsim_here else "",
                "same_rva_bsim_significance": bsim_here[0].get("bsim_significance", "") if bsim_here else "",
            }
        )
        output.append(enriched)
    return output


def render_summary(
    path: Path,
    payload: dict,
    best_rows: list[dict],
    gameplay_rows: list[dict],
    net_new_rows: list[dict],
    same_rva_rows: list[dict],
) -> None:
    lines = [
        "# Private-PDB Semantic Match Ranking",
        "",
        "The leaked PDB is joined by qualified symbol name to the exact-symbol legacy 1.5 corpus,",
        "then carried to current Redux by BSim/text evidence or by the exact Lua registration table.",
        "Raw leaked-PDB RVA equality is assessed separately and is never a primary confidence signal.",
        "",
        "## Counts",
        "",
    ]
    for key, value in payload["counts"].items():
        lines.append(f"- {key.replace('_', ' ').title()}: `{value}`")
    lines.extend(["", "## Confidence Distribution", ""])
    for key, value in payload["confidence_counts"].items():
        lines.append(f"- {key}: `{value}`")
    lines.extend(
        [
            "",
            "## Highest-Priority Current Functions",
            "",
            "| Confidence | Score | Redux RVA | PDB name | BSim | Source |",
            "|---|---:|---:|---|---:|---|",
        ]
    )
    for row in best_rows[:40]:
        source = row["pdb_source_files"].split("|")[0] if row["pdb_source_files"] else ""
        bsim = row["bsim_similarity"] or "registration"
        lines.append(
            f"| {row['confidence']} | {row['score']} | 0x{int(row['redux_rva']):x} | "
            f"{row['pdb_name'].replace('|', '/')} | {bsim} | {source.replace('|', '/')} |"
        )
    lines.extend(
        [
            "",
            "## Battlezone Gameplay/Engine Review Queue",
            "",
            "| Confidence | Score | Component | Redux RVA | PDB name | Source |",
            "|---|---:|---|---:|---|---|",
        ]
    )
    for row in gameplay_rows[:50]:
        source = row["pdb_source_files"].split("|")[0] if row["pdb_source_files"] else ""
        lines.append(
            f"| {row['confidence']} | {row['score']} | {row['source_component']} | "
            f"0x{int(row['redux_rva']):x} | {row['pdb_name'].replace('|', '/')} | {source.replace('|', '/')} |"
        )
    lines.extend(
        [
            "",
            "## Net-New Medium-Or-Better Name Candidates",
            "",
            "| Confidence | Score | Component | Redux RVA | PDB name | BSim similarity/significance |",
            "|---|---:|---|---:|---|---|",
        ]
    )
    for row in net_new_rows[:50]:
        bsim = (
            f"{row['bsim_similarity']}/{row['bsim_significance']}"
            if row["bsim_similarity"] or row["bsim_significance"]
            else row["mapping_source"]
        )
        lines.append(
            f"| {row['confidence']} | {row['score']} | {row['source_component']} | "
            f"0x{int(row['redux_rva']):x} | {row['pdb_name'].replace('|', '/')} | {bsim} |"
        )
    lines.extend(["", "## Same-RVA Reassessment", ""])
    assessment_counts = Counter(row["assessment"] for row in same_rva_rows)
    for key, value in sorted(assessment_counts.items()):
        lines.append(f"- {key}: `{value}`")
    lines.extend(
        [
            "",
            "Use `current_function_best_matches.csv` as the review queue and",
            "`semantic_function_matches_ranked.csv` when competing overloads or aliases matter.",
            "Do not patch from these results without validating the live RVA and prologue bytes.",
        ]
    )
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def build_local_hints(best_rows: list[dict], pdb_locals: list[dict]) -> list[dict]:
    locals_by_function: dict[tuple[str, str], list[dict]] = defaultdict(list)
    for row in pdb_locals:
        locals_by_function[(row.get("module_index", ""), row.get("function_symbol_record_offset", ""))].append(row)

    output: list[dict] = []
    seen: set[tuple[int, str, str, str]] = set()
    for match in best_rows:
        if CONFIDENCE_ORDER[match["confidence"]] < CONFIDENCE_ORDER["medium"]:
            continue
        key = (match.get("pdb_module_index", ""), match.get("pdb_symbol_record_offset", ""))
        for local in locals_by_function.get(key, []):
            unique = (
                int(match["redux_rva"]),
                local.get("module_index", ""),
                local.get("function_symbol_record_offset", ""),
                local.get("symbol_record_offset", ""),
            )
            if unique in seen:
                continue
            seen.add(unique)
            output.append(
                {
                    "confidence": match["confidence"],
                    "score": match["score"],
                    "redux_rva": match["redux_rva"],
                    "redux_va": match["redux_va"],
                    "redux_current_name": match["redux_current_name"],
                    "pdb_function_name": match["pdb_name"],
                    "pdb_function_signature": match["pdb_signature"],
                    "pdb_source_files": match["pdb_source_files"],
                    "pdb_source_line_min": match["pdb_source_line_min"],
                    "pdb_source_line_max": match["pdb_source_line_max"],
                    "local_name": local.get("name", ""),
                    "local_type": local.get("type_name", ""),
                    "local_flags": local.get("flags", ""),
                    "is_parameter": local.get("is_parameter", ""),
                    "is_function_parameter": local.get("is_function_parameter", ""),
                    "inline_depth": local.get("inline_depth", ""),
                    "pdb_location_record_count": local.get("location_record_count", ""),
                    "pdb_local_record_count": 1,
                    "storage_transferable": False,
                    "mapping_reasons": match["reasons"],
                    "mapping_caveats": match["caveats"],
                }
            )
    collapsed: dict[tuple[int, str, str, str, str, str], dict] = {}
    for row in output:
        key = (
            int(row["redux_rva"]),
            row["pdb_function_name"],
            row["local_name"],
            row["local_type"],
            row["is_function_parameter"],
            row["inline_depth"],
        )
        if key not in collapsed:
            collapsed[key] = row
            continue
        existing = collapsed[key]
        existing["pdb_local_record_count"] = int(existing["pdb_local_record_count"]) + 1
        existing["pdb_location_record_count"] = int(existing["pdb_location_record_count"] or 0) + int(
            row["pdb_location_record_count"] or 0
        )

    output = list(collapsed.values())
    output.sort(
        key=lambda row: (
            -CONFIDENCE_ORDER[row["confidence"]],
            -int(row["score"]),
            int(row["redux_rva"]),
            int(row["inline_depth"] or 0),
            row["local_name"],
        )
    )
    return output


def main() -> None:
    parser = argparse.ArgumentParser(description="Rank leaked private-PDB mappings using independent semantic evidence.")
    parser.add_argument("--pdb-index", type=Path, default=DEFAULT_PDB_INDEX)
    parser.add_argument("--bsim-map", type=Path, default=DEFAULT_BSIM_MAP)
    parser.add_argument("--lua-map", type=Path, default=DEFAULT_LUA_MAP)
    parser.add_argument("--bsim-applied", type=Path, default=DEFAULT_BSIM_APPLIED)
    parser.add_argument("--lua-applied", type=Path, default=DEFAULT_LUA_APPLIED)
    parser.add_argument("--inventory", type=Path, default=DEFAULT_INVENTORY)
    parser.add_argument("--decomp-dir", type=Path, default=DEFAULT_DECOMP_DIR)
    parser.add_argument("--output-dir", type=Path, help="Defaults to <pdb-index>/semantic_ranking")
    args = parser.parse_args()

    pdb_index = args.pdb_index.resolve()
    output_dir = args.output_dir.resolve() if args.output_dir else pdb_index / "semantic_ranking"
    output_dir.mkdir(parents=True, exist_ok=True)

    pdb_functions = read_csv(pdb_index / "private_functions.csv")
    pdb_locals = read_csv(pdb_index / "private_locals.csv")
    bsim_rows = read_csv(args.bsim_map.resolve())
    lua_rows = read_csv(args.lua_map.resolve())
    bsim_applied_rows = read_csv(args.bsim_applied.resolve())
    lua_applied_rows = read_csv(args.lua_applied.resolve())
    inventory_rows = read_csv(args.inventory.resolve())
    same_rva_rows = read_csv(pdb_index / "private_function_matches_by_rva.csv")
    inventory_by_rva = {int(row["entry_rva"]): row for row in inventory_rows if row.get("entry_rva")}
    decomp_by_va = decomp_file_map(args.decomp_dir.resolve())

    pdb_by_name: dict[str, list[dict]] = defaultdict(list)
    for row in pdb_functions:
        pdb_by_name[normalize_symbol(row.get("name", ""))].append(row)

    raw_candidates: list[dict] = []
    for mapping in bsim_rows:
        target_rva = parse_int(mapping.get("bsim_redux_rva"))
        if target_rva is None:
            target_rva = parse_int(mapping.get("redux_entry_rva"))
        if target_rva is None:
            continue
        name_key = normalize_symbol(legacy_full_name(mapping))
        for pdb_row in pdb_by_name.get(name_key, []):
            raw_candidates.append(
                enrich_candidate(
                    pdb_row,
                    mapping,
                    target_rva,
                    inventory_by_rva,
                    decomp_by_va,
                    len(pdb_by_name[name_key]),
                )
            )

    bsim_by_legacy_va: dict[int, list[dict]] = defaultdict(list)
    for row in bsim_rows:
        legacy_va = parse_int(row.get("legacy_entry_va"))
        if legacy_va is not None:
            bsim_by_legacy_va[legacy_va].append(row)

    image_base = 0x400000
    if inventory_rows:
        first_va = parse_int(inventory_rows[0].get("entry_va"))
        first_rva = parse_int(inventory_rows[0].get("entry_rva"))
        if first_va is not None and first_rva is not None:
            image_base = first_va - first_rva

    for lua_row in lua_rows:
        redux_va = parse_int(lua_row.get("redux_va"))
        legacy_va = parse_int(lua_row.get("legacy_va"))
        if redux_va is None:
            continue
        target_rva = redux_va - image_base
        name_key = normalize_symbol(lua_row.get("api_name", ""))
        legacy_matches = bsim_by_legacy_va.get(legacy_va, []) if legacy_va is not None else []
        if legacy_matches:
            mapping = dict(legacy_matches[0])
        else:
            mapping = {
                "legacy_name": lua_row.get("legacy_name", lua_row.get("api_name", "")),
                "legacy_namespace": "Global",
                "legacy_entry_va": lua_row.get("legacy_va", ""),
                "legacy_signature": "",
            }
        mapping["bsim_redux_rva"] = f"0x{target_rva:x}"
        for pdb_row in pdb_by_name.get(name_key, []):
            if "::" in pdb_row.get("name", "") or "lua_State*" not in pdb_row.get("signature", ""):
                continue
            raw_candidates.append(
                enrich_candidate(
                    pdb_row,
                    mapping,
                    target_rva,
                    inventory_by_rva,
                    decomp_by_va,
                    len(pdb_by_name[name_key]),
                    registration_exact=True,
                )
            )

    semantic_rows = deduplicate_candidates(raw_candidates)
    applied_names = build_applied_name_map(bsim_applied_rows, lua_applied_rows, image_base)
    apply_prior_name_evidence(semantic_rows, applied_names)
    apply_target_ambiguity(semantic_rows)
    semantic_rows.sort(
        key=lambda row: (
            CONFIDENCE_ORDER[row["confidence"]],
            int(row["score"]),
            parse_float(row.get("bsim_significance")) or -math.inf,
        ),
        reverse=True,
    )

    best_by_target: list[dict] = []
    seen_targets: set[int] = set()
    for row in semantic_rows:
        target = int(row["redux_rva"])
        if target in seen_targets or not row["is_target_top_candidate"]:
            continue
        seen_targets.add(target)
        best_by_target.append(row)

    gameplay_components = {
        "audio",
        "d3drend",
        "dynamics",
        "fun3d",
        "gamelgc",
        "input",
        "network",
        "obj76",
        "renderer",
        "schedule",
        "terrain",
        "utility",
        "weapons",
        "worldldr",
    }
    gameplay_rows = [
        row
        for row in best_by_target
        if row["source_component"] in gameplay_components
        and CONFIDENCE_ORDER[row["confidence"]] >= CONFIDENCE_ORDER["medium"]
        and row["confidence"] != "registration_exact"
    ]
    net_new_rows = [
        row
        for row in best_by_target
        if row["net_new_name_candidate"]
        and CONFIDENCE_ORDER[row["confidence"]] >= CONFIDENCE_ORDER["medium"]
    ]
    local_hints = build_local_hints(best_by_target, pdb_locals)

    reassessed = same_rva_assessment(same_rva_rows, semantic_rows, bsim_rows)
    confidence_counts = Counter(row["confidence"] for row in best_by_target)
    assessment_counts = Counter(row["assessment"] for row in reassessed)
    payload = {
        "inputs": {
            "pdb_index": str(pdb_index),
            "bsim_map": str(args.bsim_map.resolve()),
            "lua_map": str(args.lua_map.resolve()),
            "inventory": str(args.inventory.resolve()),
            "decomp_dir": str(args.decomp_dir.resolve()),
        },
        "counts": {
            "pdb_private_functions": len(pdb_functions),
            "raw_semantic_evidence_rows": len(raw_candidates),
            "deduplicated_semantic_candidates": len(semantic_rows),
            "current_redux_functions_with_candidates": len(best_by_target),
            "registration_exact_current_functions": sum(
                row["confidence"] == "registration_exact" for row in best_by_target
            ),
            "medium_or_better_gameplay_engine_functions": len(gameplay_rows),
            "medium_or_better_net_new_name_candidates": len(net_new_rows),
            "current_function_local_variable_hints": len(local_hints),
            "same_rva_candidates_reassessed": len(reassessed),
            "same_rva_semantically_corroborated": assessment_counts.get("semantically_corroborated", 0),
        },
        "confidence_counts": dict(sorted(confidence_counts.items(), key=lambda item: -CONFIDENCE_ORDER[item[0]])),
        "same_rva_assessment_counts": dict(sorted(assessment_counts.items())),
    }

    semantic_fields = [
        "score", "confidence", "pdb_name", "pdb_module_index", "pdb_symbol_record_offset",
        "pdb_signature", "pdb_rva", "pdb_code_size",
        "pdb_module", "pdb_object", "pdb_source_files", "pdb_source_line_min", "pdb_source_line_max",
        "source_component",
        "pdb_local_count", "pdb_parameter_count", "pdb_name_record_count", "legacy_name",
        "legacy_namespace", "legacy_signature", "legacy_entry_va", "redux_rva", "redux_va",
        "redux_current_name", "redux_current_namespace", "redux_current_signature", "redux_body_size",
        "mapping_source", "registration_exact", "bsim_agreement", "bsim_combined_confidence",
        "bsim_similarity", "bsim_significance", "bsim_rank2_rva", "bsim_rank2_similarity",
        "bsim_rank_margin", "bsim_target_fanin", "signature_arity_agreement", "current_name_agreement",
        "same_rva", "body_size_ratio", "decomp_token_hits", "decomp_path", "duplicate_evidence_rows",
        "target_distinct_name_count", "target_top_score", "target_score_margin", "is_target_top_candidate",
        "prior_applied_names", "prior_name_agreement", "net_new_name_candidate",
        "reasons", "caveats",
    ]
    write_csv(output_dir / "semantic_function_matches_ranked.csv", semantic_rows, semantic_fields)
    write_csv(output_dir / "current_function_best_matches.csv", best_by_target, semantic_fields)
    write_csv(output_dir / "gameplay_engine_review_queue.csv", gameplay_rows, semantic_fields)
    write_csv(output_dir / "net_new_name_review_queue.csv", net_new_rows, semantic_fields)
    local_fields = [
        "confidence", "score", "redux_rva", "redux_va", "redux_current_name", "pdb_function_name",
        "pdb_function_signature", "pdb_source_files", "pdb_source_line_min", "pdb_source_line_max",
        "local_name", "local_type", "local_flags", "is_parameter", "is_function_parameter",
        "inline_depth", "pdb_location_record_count", "pdb_local_record_count", "storage_transferable", "mapping_reasons",
        "mapping_caveats",
    ]
    write_csv(output_dir / "current_function_local_hints.csv", local_hints, local_fields)
    same_fields = list(same_rva_rows[0].keys()) if same_rva_rows else []
    same_fields.extend(
        [
            "assessment", "semantic_target_rvas", "semantic_best_confidence", "same_rva_bsim_name",
            "same_rva_bsim_confidence", "same_rva_bsim_similarity", "same_rva_bsim_significance",
        ]
    )
    write_csv(output_dir / "same_rva_candidates_reassessed.csv", reassessed, same_fields)
    (output_dir / "summary.json").write_text(json.dumps(payload, indent=2), encoding="utf-8")
    render_summary(output_dir / "SUMMARY.md", payload, best_by_target, gameplay_rows, net_new_rows, reassessed)
    print(json.dumps(payload, indent=2))


if __name__ == "__main__":
    main()
