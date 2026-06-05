# Redux Unpacked Beta-PDB Reference

The `Documents\Battlezone 98 Redux` executable is SteamStub packed. A direct
Ghidra pass against the original EXE only found `4` functions. Steamless
successfully identified SteamStub Variant 3.1 x86, removed `.bind`, decrypted
`.text`, and produced an unpacked static PE.

## Inputs

- Packed EXE: `C:\Users\istuart\Documents\Battlezone 98 Redux\battlezone98redux.exe`
- Packed EXE SHA-256: `d298782fc9a13edb0665db934110440c45461031db5f7fe1a76c8784b61cc90d`
- Beta PDB: `C:\Users\istuart\Documents\Battlezone 98 Redux\battlezone98redux.pdb`
- PDB trust: advisory only; GUID mismatch, age match

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
`merged\function_matches_by_rva.csv`, verify behavior against decompiled code,
strings, call sites, and runtime probes before using it in shim code.
