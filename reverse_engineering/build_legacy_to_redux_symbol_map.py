from __future__ import annotations

import argparse
import csv
import hashlib
import json
import math
import re
from collections import Counter, defaultdict
from dataclasses import dataclass, field
from datetime import datetime, timezone
from pathlib import Path
from typing import Iterable

import pefile


C_KEYWORDS = {
    "auto",
    "bool",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "false",
    "float",
    "for",
    "goto",
    "if",
    "int",
    "long",
    "register",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "true",
    "typedef",
    "uchar",
    "uint",
    "undefined",
    "undefined1",
    "undefined2",
    "undefined4",
    "undefined8",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while",
}

GENERIC_IDENTIFIER_RE = re.compile(
    r"^(?:"
    r"FUN|DAT|LAB|PTR|UNK|SUB|EXT|s_|u_|local_|param_|extraout_|unaff_|in_|out_|auStack|"
    r"puVar|piVar|pcVar|pbVar|pdVar|pfVar|ppcVar|ppiVar|this|this_|iVar|uVar|cVar|bVar|dVar|fVar|pFVar"
    r")[A-Za-z0-9_]*$"
)
ADDRESS_IDENTIFIER_RE = re.compile(r"^(?:FUN|DAT|LAB|PTR|UNK|SUB)_[0-9A-Fa-f]+$")
STRING_RE = re.compile(r'"(?:\\.|[^"\\])*"')
CHAR_RE = re.compile(r"'(?:\\.|[^'\\])+'")
HEX_RE = re.compile(r"\b0x[0-9A-Fa-f]+\b")
DEC_RE = re.compile(r"\b\d+\b")
IDENT_RE = re.compile(r"[A-Za-z_?@$][A-Za-z0-9_:?@$~<>]*")
DECOMP_SUFFIX_RE = re.compile(r"-([0-9A-Fa-f]{8,16})\.c$")


@dataclass(slots=True)
class Corpus:
    label: str
    promoted_root: Path
    root: Path
    manifest: dict
    functions_path: Path
    decomp_dir: Path


@dataclass(slots=True, eq=False)
class FunctionRecord:
    corpus_label: str
    entry_va: int
    entry_rva: int
    name: str
    namespace: str
    signature: str
    calling_convention: str
    return_type: str
    parameter_count: str
    body_min_va: int
    body_max_va: int
    decomp_path: Path | None = None
    features: "FunctionFeatures | None" = None

    @property
    def body_size(self) -> int:
        if self.body_max_va <= self.body_min_va:
            return 0
        return self.body_max_va - self.body_min_va + 1


@dataclass(slots=True)
class FunctionFeatures:
    text_size: int
    normalized_hash: str
    declaration_shape: str
    strings: set[str] = field(default_factory=set)
    chars: set[str] = field(default_factory=set)
    constants: set[str] = field(default_factory=set)
    identifiers: set[str] = field(default_factory=set)
    shingles: set[str] = field(default_factory=set)


@dataclass(slots=True)
class PeByteReader:
    path: Path
    image_base: int
    data: bytes
    pe: pefile.PE

    @classmethod
    def open(cls, path: Path) -> "PeByteReader | None":
        if not path.exists():
            return None
        pe = pefile.PE(str(path), fast_load=True)
        return cls(path=path, image_base=pe.OPTIONAL_HEADER.ImageBase, data=path.read_bytes(), pe=pe)

    def read_va(self, va: int, length: int) -> bytes:
        try:
            offset = self.pe.get_offset_from_rva(va - self.image_base)
        except Exception:
            return b""
        if offset < 0 or offset >= len(self.data):
            return b""
        return self.data[offset : offset + length]


def read_json(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8-sig"))


def resolve_path(base: Path, candidate: str | Path) -> Path:
    path = Path(candidate)
    if path.is_absolute():
        return path
    return (base / path).resolve()


def load_corpora(config_path: Path) -> dict[str, Corpus]:
    config = read_json(config_path)
    output: dict[str, Corpus] = {}
    for item in config.get("corpora", []):
        label = str(item["label"])
        promoted_root = resolve_path(config_path.parent, item["promoted_root"])
        index = read_json(promoted_root / "current_index.json")
        manifest = index["manifest"]
        root = resolve_path(promoted_root, index["current_corpus_root"])
        inventory_dir = resolve_path(promoted_root, manifest["inventory_dir"])
        output[label] = Corpus(
            label=label,
            promoted_root=promoted_root,
            root=root,
            manifest=manifest,
            functions_path=inventory_dir / "functions.csv",
            decomp_dir=resolve_path(promoted_root, manifest["decomp_dir"]),
        )
    return output


def parse_int(value: str | int | None) -> int:
    if value is None:
        return 0
    if isinstance(value, int):
        return value
    text = str(value).strip()
    if not text:
        return 0
    return int(text, 0)


def load_functions(corpus: Corpus) -> dict[int, FunctionRecord]:
    records: dict[int, FunctionRecord] = {}
    with corpus.functions_path.open("r", newline="", encoding="utf-8-sig") as handle:
        for row in csv.DictReader(handle):
            if str(row.get("is_external", "")).lower() == "true":
                continue
            entry_va = parse_int(row.get("entry_va"))
            if not entry_va:
                continue
            records[entry_va] = FunctionRecord(
                corpus_label=corpus.label,
                entry_va=entry_va,
                entry_rva=parse_int(row.get("entry_rva")),
                name=str(row.get("name", "")),
                namespace=str(row.get("namespace", "")),
                signature=str(row.get("signature", "")),
                calling_convention=str(row.get("calling_convention", "")),
                return_type=str(row.get("return_type", "")),
                parameter_count=str(row.get("parameter_count", "")),
                body_min_va=parse_int(row.get("body_min_va")),
                body_max_va=parse_int(row.get("body_max_va")),
            )
    attach_decomp_paths(corpus.decomp_dir, records)
    return records


def attach_decomp_paths(decomp_dir: Path, records: dict[int, FunctionRecord]) -> None:
    if not decomp_dir.exists():
        return
    for path in decomp_dir.rglob("*.c"):
        match = DECOMP_SUFFIX_RE.search(path.name)
        if match:
            entry_va = int(match.group(1), 16)
        else:
            prefix = re.match(r"^([0-9A-Fa-f]{8,16})_", path.name)
            if not prefix:
                continue
            entry_va = int(prefix.group(1), 16)
        record = records.get(entry_va)
        if record is not None:
            record.decomp_path = path


def unquote_c_string(token: str) -> str:
    # Preserve the spelling enough for matching while avoiding full C escape parsing.
    return token[1:-1].replace('\\"', '"').replace("\\\\", "\\")


def canonical_constant(token: str) -> str | None:
    try:
        value = int(token, 16 if token.lower().startswith("0x") else 10)
    except ValueError:
        return None
    if value in {0, 1, 2, 3, 4, 8, 16, 32, 64, 255, 256, 512, 1024}:
        return None
    if value >= 0x400000:
        return None
    return hex(value)


def normalize_identifier(token: str) -> str | None:
    if token in C_KEYWORDS:
        return None
    if ADDRESS_IDENTIFIER_RE.match(token) or GENERIC_IDENTIFIER_RE.match(token):
        return None
    if len(token) <= 1:
        return None
    return token


def normalize_text(text: str) -> tuple[str, str]:
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.DOTALL)
    text = re.sub(r"//.*", " ", text)
    declaration = ""
    for line in text.splitlines():
        stripped = line.strip()
        if stripped and not stripped.startswith("{"):
            declaration = stripped
            break
    text = STRING_RE.sub('"STR"', text)
    text = CHAR_RE.sub("'CHR'", text)
    text = re.sub(r"\b(?:FUN|DAT|LAB|PTR|UNK|SUB)_[0-9A-Fa-f]+\b", "ADDRSYM", text)
    text = re.sub(r"\b(?:local|param|extraout|unaff|in|out)_[A-Za-z0-9_]+\b", "VAR", text)
    text = re.sub(r"\bauStack[0-9A-Fa-f_]+\b", "VAR", text)
    text = HEX_RE.sub("NUM", text)
    text = DEC_RE.sub("NUM", text)
    text = re.sub(r"\s+", " ", text).strip()
    declaration_shape = re.sub(r"\b[A-Za-z_?@$][A-Za-z0-9_:?@$~<>]*\b", "ID", declaration)
    declaration_shape = re.sub(r"\s+", " ", declaration_shape).strip()
    return text, declaration_shape


def shingle_tokens(tokens: list[str], width: int = 5) -> set[str]:
    if len(tokens) < width:
        return {" ".join(tokens)} if tokens else set()
    return {" ".join(tokens[index : index + width]) for index in range(0, len(tokens) - width + 1)}


def extract_features(path: Path) -> FunctionFeatures:
    text = path.read_text(encoding="utf-8", errors="ignore")
    strings = {unquote_c_string(match.group(0)) for match in STRING_RE.finditer(text)}
    strings = {value for value in strings if len(value) >= 3}
    chars = {match.group(0) for match in CHAR_RE.finditer(text)}
    constants = {
        canonical
        for token in [*HEX_RE.findall(text), *DEC_RE.findall(text)]
        if (canonical := canonical_constant(token)) is not None
    }
    identifiers = {
        canonical
        for token in IDENT_RE.findall(text)
        if (canonical := normalize_identifier(token)) is not None
    }
    normalized, declaration_shape = normalize_text(text)
    tokens = re.findall(r"[A-Za-z_]+|NUM|STR|CHR|==|!=|<=|>=|->|&&|\|\||[{}()[\];,=+\-*/%&|^<>!~]", normalized)
    shingles = shingle_tokens(tokens)
    normalized_hash = hashlib.sha256(normalized.encode("utf-8", errors="ignore")).hexdigest()
    return FunctionFeatures(
        text_size=len(text),
        normalized_hash=normalized_hash,
        declaration_shape=declaration_shape,
        strings=strings,
        chars=chars,
        constants=constants,
        identifiers=identifiers,
        shingles=shingles,
    )


def add_features(records: Iterable[FunctionRecord]) -> list[FunctionRecord]:
    ready: list[FunctionRecord] = []
    for record in records:
        if record.decomp_path is None:
            continue
        try:
            record.features = extract_features(record.decomp_path)
        except OSError:
            continue
        ready.append(record)
    return ready


def is_generic_name(name: str) -> bool:
    return bool(re.match(r"^(?:FUN|SUB|thunk_FUN|Ordinal|LAB|DAT)_", name))


def should_offer_legacy_name(record: FunctionRecord) -> bool:
    name = record.name
    if not name or is_generic_name(name):
        return False
    if name.startswith("??_") or name.startswith("?_"):
        return False
    if record.body_size <= 4:
        return False
    return True


def jaccard(left: set[str], right: set[str]) -> float:
    if not left and not right:
        return 0.0
    intersection = len(left & right)
    if intersection == 0:
        return 0.0
    return intersection / len(left | right)


def size_similarity(left: int, right: int) -> float:
    if left <= 0 or right <= 0:
        return 0.0
    smaller = min(left, right)
    larger = max(left, right)
    return smaller / larger


def build_inverted(records: Iterable[FunctionRecord], attr: str, max_bucket: int) -> dict[str, list[FunctionRecord]]:
    buckets: dict[str, list[FunctionRecord]] = defaultdict(list)
    for record in records:
        features = record.features
        if features is None:
            continue
        values = getattr(features, attr)
        for value in values:
            buckets[value].append(record)
    return {key: value for key, value in buckets.items() if 0 < len(value) <= max_bucket}


def build_hash_index(records: Iterable[FunctionRecord]) -> dict[str, list[FunctionRecord]]:
    buckets: dict[str, list[FunctionRecord]] = defaultdict(list)
    for record in records:
        if record.features is not None:
            buckets[record.features.normalized_hash].append(record)
    return buckets


def candidate_records(
    legacy: FunctionRecord,
    exact_hash_index: dict[str, list[FunctionRecord]],
    string_index: dict[str, list[FunctionRecord]],
    shingle_index: dict[str, list[FunctionRecord]],
    constant_index: dict[str, list[FunctionRecord]],
    max_candidates: int,
) -> list[FunctionRecord]:
    features = legacy.features
    if features is None:
        return []

    weighted: Counter[FunctionRecord] = Counter()
    for candidate in exact_hash_index.get(features.normalized_hash, []):
        weighted[candidate] += 100
    for value in features.strings:
        for candidate in string_index.get(value, []):
            weighted[candidate] += 12
    for value in features.shingles:
        for candidate in shingle_index.get(value, []):
            weighted[candidate] += 2
    for value in features.constants:
        for candidate in constant_index.get(value, []):
            weighted[candidate] += 1

    if not weighted:
        return []
    return [candidate for candidate, _ in weighted.most_common(max_candidates)]


def score_pair(legacy: FunctionRecord, redux: FunctionRecord) -> tuple[float, list[str], dict[str, str]]:
    lf = legacy.features
    rf = redux.features
    if lf is None or rf is None:
        return 0.0, [], {}

    string_score = jaccard(lf.strings, rf.strings)
    constant_score = jaccard(lf.constants, rf.constants)
    identifier_score = jaccard(lf.identifiers, rf.identifiers)
    shingle_score = jaccard(lf.shingles, rf.shingles)
    body_score = size_similarity(legacy.body_size, redux.body_size)
    text_score = size_similarity(lf.text_size, rf.text_size)

    score = (
        0.36 * shingle_score
        + 0.24 * string_score
        + 0.14 * constant_score
        + 0.08 * identifier_score
        + 0.10 * body_score
        + 0.08 * text_score
    )

    methods: list[str] = []
    if lf.normalized_hash == rf.normalized_hash:
        score += 0.35
        methods.append("exact_normalized_decomp")
    shared_strings = lf.strings & rf.strings
    if shared_strings:
        methods.append("shared_strings")
        if lf.strings == rf.strings and len(lf.strings) >= 1:
            score += 0.08
            methods.append("same_string_set")
    if lf.constants & rf.constants:
        methods.append("shared_constants")
    if shingle_score >= 0.35:
        methods.append("decomp_shingles")
    if body_score >= 0.85:
        methods.append("similar_body_size")
    if legacy.calling_convention and legacy.calling_convention == redux.calling_convention:
        score += 0.02
        methods.append("same_calling_convention")
    if legacy.parameter_count and legacy.parameter_count == redux.parameter_count:
        score += 0.02
        methods.append("same_parameter_count")

    score = min(score, 1.0)
    evidence = {
        "string_score": f"{string_score:.4f}",
        "constant_score": f"{constant_score:.4f}",
        "identifier_score": f"{identifier_score:.4f}",
        "shingle_score": f"{shingle_score:.4f}",
        "body_size_score": f"{body_score:.4f}",
        "text_size_score": f"{text_score:.4f}",
        "shared_strings": " | ".join(sorted(shared_strings)[:8]),
        "shared_constants": " | ".join(sorted(lf.constants & rf.constants)[:12]),
    }
    return score, methods, evidence


def confidence_for(score: float, margin: float, methods: list[str]) -> str:
    method_set = set(methods)
    if "exact_normalized_decomp" in method_set and score >= 0.88:
        return "very_high"
    if score >= 0.82 and margin >= 0.10 and ({"shared_strings", "decomp_shingles"} & method_set):
        return "high"
    if score >= 0.70 and margin >= 0.06:
        return "medium"
    if "same_string_set" in method_set and score >= 0.50 and margin >= 0.02:
        return "medium"
    if score >= 0.58 and margin >= 0.04:
        return "low"
    if "same_string_set" in method_set and score >= 0.40 and margin >= 0.02:
        return "low"
    return "reject"


def format_hex(value: int) -> str:
    return f"0x{value:08x}"


def format_bytes(data: bytes) -> str:
    return " ".join(f"{byte:02X}" for byte in data)


def relpath(path: Path | None) -> str:
    if path is None:
        return ""
    try:
        return str(path.resolve().relative_to(Path.cwd().resolve()))
    except ValueError:
        return str(path)


def build_rows(
    legacy_records: list[FunctionRecord],
    redux_records: list[FunctionRecord],
    min_score: float,
    max_candidates: int,
    redux_bytes: PeByteReader | None,
    prologue_length: int,
) -> list[dict[str, str]]:
    exact_hash_index = build_hash_index(redux_records)
    string_index = build_inverted(redux_records, "strings", max_bucket=30)
    shingle_index = build_inverted(redux_records, "shingles", max_bucket=12)
    constant_index = build_inverted(redux_records, "constants", max_bucket=80)

    rows: list[dict[str, str]] = []
    for index, legacy in enumerate(legacy_records, start=1):
        candidates = candidate_records(
            legacy,
            exact_hash_index=exact_hash_index,
            string_index=string_index,
            shingle_index=shingle_index,
            constant_index=constant_index,
            max_candidates=max_candidates,
        )
        scored: list[tuple[float, FunctionRecord, list[str], dict[str, str]]] = []
        for redux in candidates:
            score, methods, evidence = score_pair(legacy, redux)
            if score >= min_score:
                scored.append((score, redux, methods, evidence))
        if not scored:
            continue
        scored.sort(key=lambda item: item[0], reverse=True)
        best_score, best_redux, methods, evidence = scored[0]
        next_score = scored[1][0] if len(scored) > 1 else 0.0
        margin = best_score - next_score
        confidence = confidence_for(best_score, margin, methods)
        if confidence == "reject":
            continue

        rows.append(
            {
                "legacy_name": legacy.name,
                "legacy_namespace": legacy.namespace,
                "legacy_entry_va": format_hex(legacy.entry_va),
                "legacy_entry_rva": format_hex(legacy.entry_rva),
                "legacy_signature": legacy.signature,
                "redux_current_name": best_redux.name,
                "redux_entry_va": format_hex(best_redux.entry_va),
                "redux_entry_rva": format_hex(best_redux.entry_rva),
                "redux_signature": best_redux.signature,
                "score": f"{best_score:.4f}",
                "next_score": f"{next_score:.4f}",
                "margin": f"{margin:.4f}",
                "confidence": confidence,
                "methods": ";".join(methods),
                "redux_static_prologue": format_bytes(redux_bytes.read_va(best_redux.entry_va, prologue_length))
                if redux_bytes
                else "",
                "legacy_body_size": str(legacy.body_size),
                "redux_body_size": str(best_redux.body_size),
                "shared_strings": evidence["shared_strings"],
                "shared_constants": evidence["shared_constants"],
                "string_score": evidence["string_score"],
                "constant_score": evidence["constant_score"],
                "identifier_score": evidence["identifier_score"],
                "shingle_score": evidence["shingle_score"],
                "body_size_score": evidence["body_size_score"],
                "text_size_score": evidence["text_size_score"],
                "legacy_decomp": relpath(legacy.decomp_path),
                "redux_decomp": relpath(best_redux.decomp_path),
            }
        )
        if index % 1000 == 0:
            print(f"matched scan progress: {index}/{len(legacy_records)} legacy functions")
    rows.sort(key=lambda row: (row["confidence"], float(row["score"])), reverse=True)
    return rows


def write_csv(path: Path, rows: list[dict[str, str]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    if not rows:
        path.write_text("", encoding="utf-8")
        return
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(rows[0].keys()))
        writer.writeheader()
        writer.writerows(rows)


def summarize_rows(rows: list[dict[str, str]]) -> dict:
    counts = Counter(row["confidence"] for row in rows)
    method_counts: Counter[str] = Counter()
    for row in rows:
        method_counts.update(method for method in row["methods"].split(";") if method)
    return {
        "total_matches": len(rows),
        "confidence_counts": dict(sorted(counts.items())),
        "method_counts": dict(method_counts.most_common()),
    }


def write_markdown(path: Path, summary: dict, rows: list[dict[str, str]], output_csv: Path) -> None:
    preview = rows[:30]
    lines = [
        "# Legacy To Redux Symbol Map",
        "",
        f"- Generated: `{summary['generated_at']}`",
        f"- Legacy corpus: `{summary['legacy_corpus_root']}`",
        f"- Redux corpus: `{summary['redux_corpus_root']}`",
        f"- Redux static binary: `{summary['redux_static_binary']}`",
        f"- CSV: `{output_csv}`",
        f"- Total accepted matches: `{summary['matches']['total_matches']}`",
        "",
        "## Confidence Counts",
        "",
    ]
    for key, value in summary["matches"]["confidence_counts"].items():
        lines.append(f"- `{key}`: `{value}`")
    lines.extend(["", "## Method Counts", ""])
    for key, value in summary["matches"]["method_counts"].items():
        lines.append(f"- `{key}`: `{value}`")
    lines.extend(
        [
            "",
            "## Use For Patch Work",
            "",
            "- Treat `very_high` and `high` rows as naming candidates, not final hook approval.",
            "- Use `redux_static_prologue` as the unpacked-file byte baseline for offline review.",
            "- Before patching, validate the Redux RVA against live runtime bytes after the SteamStub settle delay.",
            "- Prefer rows with `shared_strings`, `decomp_shingles`, and a healthy `margin` over rows that only match size/constants.",
            "- Record the validated RVA, expected prologue bytes, and trampoline length in the task-specific RE note.",
            "",
            "## Top Matches",
            "",
        ]
    )
    if preview:
        lines.append("| Confidence | Score | Legacy Name | Redux RVA | Methods |")
        lines.append("|---|---:|---|---:|---|")
        for row in preview:
            lines.append(
                f"| {row['confidence']} | {row['score']} | `{row['legacy_name']}` | `{row['redux_entry_rva']}` | `{row['methods']}` |"
            )
    else:
        lines.append("- <none>")
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Build a best-effort legacy Battlezone 1.5 to Redux function-name transfer map."
    )
    parser.add_argument("--config", type=Path, default=Path("reverse_engineering/current_re_corpora.json"))
    parser.add_argument("--legacy-label", default="legacy")
    parser.add_argument("--redux-label", default="redux")
    parser.add_argument("--output-dir", type=Path, default=Path("reverse_engineering/workshop/symbol_transfer/legacy_to_redux"))
    parser.add_argument("--min-score", type=float, default=0.35)
    parser.add_argument("--max-candidates", type=int, default=500)
    parser.add_argument("--prologue-length", type=int, default=16)
    parser.add_argument("--max-legacy", type=int, default=0, help="Debug/testing limit. 0 means all.")
    args = parser.parse_args()

    config_path = args.config.resolve()
    corpora = load_corpora(config_path)
    legacy_corpus = corpora[args.legacy_label]
    redux_corpus = corpora[args.redux_label]

    print("loading inventories")
    legacy_by_va = load_functions(legacy_corpus)
    redux_by_va = load_functions(redux_corpus)

    print("extracting decompiler fingerprints")
    legacy_candidates = [record for record in legacy_by_va.values() if should_offer_legacy_name(record) and record.decomp_path]
    if args.max_legacy > 0:
        legacy_candidates = legacy_candidates[: args.max_legacy]
    legacy_records = add_features(legacy_candidates)
    redux_records = add_features(redux_by_va.values())

    print(f"legacy functions with features: {len(legacy_records)}")
    print(f"redux functions with features: {len(redux_records)}")
    redux_bytes = PeByteReader.open(Path(redux_corpus.manifest["binary_path"]))
    rows = build_rows(
        legacy_records=legacy_records,
        redux_records=redux_records,
        min_score=args.min_score,
        max_candidates=args.max_candidates,
        redux_bytes=redux_bytes,
        prologue_length=args.prologue_length,
    )

    output_dir = args.output_dir.resolve()
    output_dir.mkdir(parents=True, exist_ok=True)
    csv_path = output_dir / "legacy_to_redux_symbol_map.csv"
    summary_path = output_dir / "summary.json"
    markdown_path = output_dir / "README.md"

    write_csv(csv_path, rows)
    summary = {
        "generated_at": datetime.now(timezone.utc).isoformat(),
        "config": str(config_path),
        "legacy_corpus_root": str(legacy_corpus.root),
        "redux_corpus_root": str(redux_corpus.root),
        "legacy_functions_with_features": len(legacy_records),
        "redux_functions_with_features": len(redux_records),
        "min_score": args.min_score,
        "max_candidates": args.max_candidates,
        "prologue_length": args.prologue_length,
        "redux_static_binary": str(redux_bytes.path) if redux_bytes else "",
        "output_csv": str(csv_path),
        "matches": summarize_rows(rows),
    }
    summary_path.write_text(json.dumps(summary, indent=2), encoding="utf-8")
    write_markdown(markdown_path, summary, rows, csv_path)
    print(json.dumps(summary, indent=2))


if __name__ == "__main__":
    main()
