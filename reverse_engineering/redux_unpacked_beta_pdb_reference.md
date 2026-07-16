# Redux Unpacked Beta-PDB Reference

The `Documents\Battlezone 98 Redux` executable is SteamStub packed. A direct
Ghidra pass against the original EXE only found `4` functions. Steamless
successfully identified SteamStub Variant 3.1 x86, removed `.bind`, decrypted
`.text`, and produced an unpacked static PE.

## Inputs

- Packed EXE: `<USER_HOME>\Documents\Battlezone 98 Redux\battlezone98redux.exe`
- Packed EXE SHA-256: `d298782fc9a13edb0665db934110440c45461031db5f7fe1a76c8784b61cc90d`
- Beta PDB: `<USER_HOME>\Documents\Battlezone 98 Redux\battlezone98redux.pdb`
- PDB trust: advisory only; GUID mismatch, age match

## Matching-Executable Search

The public Steam history was checked again in July 2026 through both SteamDB
and authenticated SteamCMD metadata for app `301650`, Windows depot `301652`.
The public depot exposes ten historical manifests, all from March 16-28, 2017.
The current public manifest is `7411172603041703474` (build ID `1718871`).
SteamCMD reports that private branches exist, but it does not expose their
manifests to this account. An exact public-web search for the PDB GUID also
returned no matching executable or symbol-server entry.

This cannot prove that no matching EXE ever existed, but it strongly supports
the PDB being from an internal or unreleased build rather than a recoverable
public Steam revision. References:

- <https://steamdb.info/depot/301652/>
- <https://steamdb.info/app/301650/depots/>

## Static Unpack

- Tool: Steamless `v3.1.0.5`
- Detected packer: SteamStub Variant 3.1 x86
- Unpacked EXE SHA-256: `3eabfe97d5c296c36cdbcefc27e16e4bd3866808cc7fd40c0928ba03cce8f237`
- DIE result after unpack: not packed

## Corpus

Local promoted root:

`reverse_engineering\current_global_corpus`

Generated corpus root:

`reverse_engineering\workshop\global_decompile\redux_documents_unpacked_beta_pdb_best_effort`

Git LFS artifact:

`reverse_engineering\corpus_artifacts\redux_documents_unpacked_beta_pdb_best_effort.zip`

Coverage:

- Ghidra functions: `27525`
- Decompiled `.c` files in portable artifact: `25168`
- Binary strings: `15245` ASCII, `77` UTF-16
- Beta-PDB public functions: `8078`
- Direct advisory RVA matches: `497`

## Structured Private-PDB Index

The PDB contains substantially more than its public-symbol table. The current
exporter also recovers:

- Private procedures with signatures and RVAs: `8904`
- Private local-variable records: `41186`
- Optimized local-variable location records: `69497`
- Source-line address ranges: `8027`
- Concrete class/struct/union layouts: `9451`
- Direct base, field, and vtable-pointer layout records: `43304`
- Private procedures with source-file/line context: `8009`
- Raw private procedures represented in the current Ghidra inventory at the
  same numeric RVA: `1254` rows across `876` Ghidra function RVAs

The generated local index is at:

`reverse_engineering\workshop\private_pdb_index`

Useful files are `private_functions.csv`, `private_locals.csv`,
`private_local_ranges.csv`, `source_line_ranges.csv`, `class_layouts.csv`,
`class_members.csv`, and `private_function_matches_by_rva.csv`. Treat same-RVA results as candidates:
the merge labels a single PDB candidate separately from RVAs shared by several
PDB procedures (for example, linker-folded implementations).

The subsequent semantic audit found that none of those `1254` raw same-RVA
rows were corroborated by the independent legacy-name/BSim map. Do not use that
table for released-build naming or hook placement.

## Cross-Build Semantic Ranking

`rank_private_pdb_matches.py` joins leaked-PDB qualified names to the
exact-symbol legacy 1.5 build, then uses BSim/text agreement or the Lua
registration table to locate current Redux functions. The validated result is:

- Current Redux functions with semantic candidates: `2045`
- Exact Lua registration mappings with leaked-PDB signatures: `213`
- `very_high` best candidates: `223`
- `high` best candidates: `325`
- Medium-or-better gameplay/engine review targets: `521`
- Medium-or-better net-new name candidates after existing applied-name logs:
  `611`
- Collapsed current-function local/parameter hints: `3776`
- Same-RVA rows semantically corroborated: `0`

The exact-binary gate subsequently verified all `2045` semantic candidate
addresses against the current GOG PE, executable sections, Ghidra function
boundaries, and decodable prologue bytes. It classified `436` apply-grade names
as already present, `244` net-new high-confidence identities as review-only,
`363` medium identities as held, `2` thunks as comment-only, and `1` conflicting
existing name as blocked. No net-new row met the automatic-rename policy.
A clean Ghidra 12.0.4 headless analysis also verified the function object and
stored entry fingerprint for all `244` rows in the high-review queue.

Outputs live under `semantic_ranking` inside the generated private PDB index.
See `reverse_engineering\private_pdb_semantic_ranking.md` for the evidence model
and file descriptions.

Refresh the gate after regenerating rankings:

```powershell
python reverse_engineering\validate_semantic_apply.py
```

Validated queues are under `semantic_ranking\binary_validation`. Use
`safe_new_apply.tsv` only for automatic names; use the byte-verifying
`reverse_engineering\ghidra_scripts\ApplySemanticPdbHints.java` importer rather
than applying a ranking CSV directly.

Use it immediately in a generated brief with:

```powershell
python reverse_engineering\build_re_brief.py `
  --query "HoverCraft Simulate dt" `
  --supplemental-pdb reverse_engineering\workshop\private_pdb_index
```

## Restore On Another Machine

```powershell
git lfs install
git lfs pull
.\reverse_engineering\restore_redux_unpacked_beta_corpus.ps1
.\reverse_engineering\restore_legacy_15227_clean_corpus.ps1
```

## Search

```powershell
.\reverse_engineering\search_re_corpora.ps1 -CorpusLabels redux -Pattern "Producer" -IncludeDecomps
.\reverse_engineering\search_re_corpora.ps1 -Pattern "weapon mask" -IncludeDecomps
python reverse_engineering\build_re_brief.py --query "weapon mask howitzer"
```

Use beta-PDB names as hints, not facts. When a PDB name appears only through
an RVA merge, verify behavior against the signature, source module, decompiled
code, strings, call sites, and runtime probes before using it in shim code.
