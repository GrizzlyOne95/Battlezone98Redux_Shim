# Private-PDB Semantic Ranking

The leaked Redux PDB does not match the released executable, so equal RVAs are
not sufficient evidence for transferring a symbol. This workflow instead uses
three independent build lineages:

1. The leaked PDB supplies private qualified names, signatures, source context,
   locals, and type layouts.
2. The exact `bzint.pdb` identifies functions in the legacy 1.5 executable.
3. BSim and the text-shingle map carry those exact legacy identities to the
   current unpacked Redux corpus. The Lua registration table supplies an exact
   current pointer for script API wrappers.

An exact qualified-name agreement between steps 1 and 2 connects the leaked
PDB metadata to the semantic mapping in step 3 without assuming address-layout
stability.

## Run

Generate the private-PDB index first, then rank it:

```powershell
python reverse_engineering\rank_private_pdb_matches.py
python reverse_engineering\validate_semantic_apply.py
```

The default output is:

`reverse_engineering\workshop\private_pdb_index\semantic_ranking`

Important artifacts:

- `current_function_best_matches.csv`: best explainable candidate for each
  current Redux RVA.
- `gameplay_engine_review_queue.csv`: medium-or-better Battlezone gameplay and
  engine targets, excluding Lua runtime/library noise.
- `net_new_name_review_queue.csv`: medium-or-better targets not already present
  in the existing BSim or exact Lua applied-name logs.
- `semantic_function_matches_ranked.csv`: every candidate, including overloads
  and competing identities.
- `current_function_local_hints.csv`: private parameter/local names and types
  attached to ranked current functions. Storage/register locations are marked
  non-transferable because they belong to the leaked build.
- `same_rva_candidates_reassessed.csv`: the old raw same-RVA results, explicitly
  classified as corroborated, contradicted, conflicting, or unresolved.
- `SUMMARY.md` and `summary.json`: counts, confidence distribution, and the top
  review queue.
- `binary_validation\prologue_boundary_validation.csv`: every semantic
  candidate joined to the exact Ghidra function start and exact PE entry bytes.
- `binary_validation\safe_new_apply.tsv`: the only automatic-rename queue.
- `binary_validation\high_confidence_review.tsv`: exact-boundary, net-new
  `high` candidates that still require semantic review.
- `binary_validation\verified_existing.tsv`: apply-grade candidates whose
  names already agree with the existing applied-name logs.
- `binary_validation\medium_hold.tsv`: useful candidates that are deliberately
  held from application.

## Confidence Semantics

- `registration_exact`: a global `lua_State*` PDB wrapper agrees with the Lua
  registration API name, whose table entry supplies the current function
  pointer. Legacy signature arity is used to reject same-name overloads.
- `very_high`: qualified leaked-PDB and exact legacy names agree, and BSim plus
  the independent text/shingle matcher agree on the current RVA.
- `high`: qualified names agree and BSim has a strong confidence classification
  or a sufficiently strong similarity/significance pair.
- `medium`: useful semantic evidence that still needs closer decompile review.
- `low`: name lineage exists, but the current-build mapping is weak.
- `ambiguous`: BSim/text conflict, collision family, weak rank margin, or close
  competing names at the same current RVA.
- `rejected`: an apparently exact registration-name candidate has a conflicting
  legacy signature arity.

The numeric score only sorts candidates within these explainable evidence
classes. It combines signature arity, BSim rank margin, body-size similarity,
existing current names, and weak decompile-token support. It is not a
probability.

## Validated July 2026 Result

- Current Redux functions with semantic candidates: `2045`
- Exact Lua registration mappings with leaked-PDB signatures: `213`
- Best candidates rated `very_high`: `223`
- Best candidates rated `high`: `325`
- Medium-or-better gameplay/engine review targets: `521`
- Medium-or-better net-new name candidates: `611`
- Collapsed private local/parameter hints: `3776`
- Raw same-RVA candidates reassessed: `1254`
- Raw same-RVA candidates semantically corroborated: `0`

## Exact-Binary Application Gate

`validate_semantic_apply.py` pins the ranking to the exact analyzed GOG
baseline (`SHA-256 8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`).
For each candidate it requires:

- an exact function-start row in the Ghidra inventory
- a non-external function in an executable PE section
- readable, non-padding entry bytes that Capstone can decode
- a stored prologue fingerprint for a second check at import or runtime
- a safe namespace/name shape before automatic rename can be considered

The July 2026 run validated all `2045` candidate boundaries. Its dispositions
are:

- `436` already-named apply-grade candidates (`verified_existing`)
- `244` net-new `high` candidates ready for manual review
- `363` net-new `medium` candidates held from application
- `2` thunks restricted to comments
- `1` existing-name conflict blocked
- `999` candidates below application grade
- `0` new automatic renames

The empty automatic queue is a useful result: the evidence supports retaining
the 436 names already applied, but does not justify silently promoting the next
244 identities. Static boundary agreement proves where a function begins, not
what it does.

The persistent Ghidra service independently reproduced the stored 16-byte
fingerprints for sampled GOG candidates. A clean Ghidra 12.0.4 headless import
and full analysis then ran the importer in `verify` mode over all `244` high
review rows; all `244` had a function at the queued VA and exact prologue-byte
agreement. The packed Steam image did not match those bytes on disk, as
expected; compare Steam addresses only after SteamStub has settled in process.

## Ghidra Import

Use `reverse_engineering\ghidra_scripts\ApplySemanticPdbHints.java` as a Ghidra
post-script. It accepts:

```text
ApplySemanticPdbHints.java <queue.tsv> <verify|comment|rename> <results.csv>
```

- `verify` only rechecks function starts and prologue bytes.
- `comment` adds idempotent provenance comments, preserving existing comments.
- `rename` refuses every input except a file named `safe_new_apply.tsv`, checks
  the bytes again, and will not replace a non-default Ghidra name.

Use `comment` for `high_confidence_review.tsv` only when retaining the candidate
inside Ghidra is useful; a comment is not identity confirmation.

The zero corroborations are the critical negative result: the original
same-RVA table should not be used as a naming or hook-placement map for the
released build. Use the semantic ranking and still validate live prologue bytes
before patching.

## Brief Integration

```powershell
python reverse_engineering\build_re_brief.py `
  --query "Misn13Mission Execute team" `
  --supplemental-pdb reverse_engineering\workshop\private_pdb_index
```

The generated brief shows semantic current-RVA matches, transferred local/type
hints, exact-binary validation dispositions, raw-RVA reassessments, and
class-layout results in separate sections.
