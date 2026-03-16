# Agentic RE Workflow

Use this workflow for future reverse-engineering tasks against Battlezone.

## Default Rule

Search both promoted corpora first. Do not open Ghidra immediately unless the
combined corpus stops narrowing the problem.

Primary entry points:

- `reverse_engineering\current_re_corpora.json`
- `reverse_engineering\current_global_corpus\README.md`
- `reverse_engineering\current_legacy_global_corpus\README.md`
- `reverse_engineering\search_re_corpora.ps1`
- `reverse_engineering\build_re_brief.py`
- `reverse_engineering\portable_corpus_workflow.md`

## Standard Loop

1. Build a brief for the user request.

```powershell
python reverse_engineering\build_re_brief.py --query "weapon mask howitzer minelayer"
```

2. Search both corpora directly for exact names, class labels, strings, ODF
   fields, UI text, and known RVAs.

```powershell
.\reverse_engineering\search_re_corpora.ps1 -Pattern "ArtilleryFriend"
```

Add `-IncludeDecomps` only after metadata and symbol searches have already
narrowed the target.

3. Use `inventory\functions.csv`, `inventory\symbols.csv`, and
   `merged\function_matches_by_rva.csv` to narrow likely native targets.

4. Prefer the legacy exact-match corpus for:
   - original gameplay semantics
   - class names
   - process/module ownership
   - source tree breadcrumbs

5. Prefer the Redux corpus for:
   - current patch points
   - current RVAs
   - current decomp behavior
   - anything touching Ogre or Redux-only systems

6. Only if needed, grep the decomp trees directly:

```powershell
.\reverse_engineering\search_re_corpora.ps1 -Pattern "GetWeaponMask" -IncludeDecomps
```

7. Open only the most relevant decomp files under the promoted `decomp_dir`.

8. Validate candidate functions against:
   - nearby strings
   - caller/callee relationships
   - globals touched
   - class/vtable context
   - known patch-safe addresses from your existing notes

9. If the corpus is not enough, move to Ghidra for targeted confirmation, not
   broad exploration.

10. Write findings back into a note under `reverse_engineering\` with:
   - exact addresses or RVAs
   - confidence level
   - what was validated from corpus only
   - what was validated in live Ghidra
   - whether a mismatched PDB name was trusted or rejected

## Good Query Shapes

Search by:

- exact strings from the game UI or logs
- class labels, ODF field names, enum-like tokens
- internal names from the PDB
- nearby helper or friend names
- native function RVAs

Avoid starting with:

- vague gameplay descriptions only
- broad subsystem names like `AI` or `render`

Translate vague requests into concrete search tokens first.

## Trust Model

- Ghidra decomp and disassembly are the behavioral source of truth.
- The Redux GOG PDB is advisory only unless a specific match is independently
  confirmed.
- The legacy `bzone.exe` and `bzint.pdb` pair is exact-match and should be the
  first place to recover original semantic names for core gameplay code.
- RVA joins in `function_matches_by_rva.csv` are useful clues, not proof.

## Deliverables For Each RE Task

Aim to leave behind:

- one focused note with validated addresses and behavior
- one or more search terms that worked
- any newly discovered safe patch points
- whether the corpus was sufficient or Ghidra was required
