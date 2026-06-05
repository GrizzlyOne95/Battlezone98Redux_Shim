# Legacy 1.5.2.27 Clean PDB Reference

This repo has a local exact-match Battlezone 1.5.2.27 EXE/PDB reference at:

`reverse_engineering\decompilation_from_1.5_exe-pdb\clean_pdb_c`

For Git sync, the extracted folder is ignored and restored from a Git LFS
archive:

`reverse_engineering\corpus_artifacts\legacy_15227_clean_pdb_c.zip`

Use it as a semantic reference when implementing or validating DLL shim behavior
against the Redux binary. It is Ghidra C-like output, not buildable original
source.

## Coverage

- Function records: `15070`
- Decompiled C-like functions: `15045`
- Remaining Ghidra decompiler timeouts: `25`
- Assembly fallbacks for remaining failures: `25`
- Exact input pair: `bzone.exe` 1.5.2.27 Update 1 + `bzint.pdb`

The remaining C gaps are mostly large software rasterizer and terrain polygon
routines, plus `NetGameDlgProc`, `ShellDlgProc`, and `DXGetErrorStringA`.

## Search

On a fresh machine:

```powershell
git lfs install
git lfs pull
.\reverse_engineering\restore_legacy_15227_clean_corpus.ps1
```

Search the clean exact-match function index and decompiled C:

```powershell
.\reverse_engineering\search_legacy_15227_clean.ps1 -Pattern "Producer"
```

Include assembly fallback files for the 25 functions Ghidra cannot decompile:

```powershell
.\reverse_engineering\search_legacy_15227_clean.ps1 -Pattern "Terrain128Poly" -IncludeFailedAsm
```

For broader Redux-vs-legacy work, keep using:

```powershell
.\reverse_engineering\search_re_corpora.ps1 -Pattern "weapon mask" -IncludeDecomps
python reverse_engineering\build_re_brief.py --query "weapon mask howitzer"
```

## Key Files

- `all_decompiled.c`: merged reference dump.
- `functions\`: one `.c` file per decompiled function, sharded by address prefix.
- `function_index.tsv`: full PDB-named function list and decompile status.
- `decompile_failures.tsv`: remaining C gaps.
- `failed_asm\`: assembly fallback files for those gaps.
- `manifest.json`: machine-readable coverage summary.

## Shim Usage

When adding or validating a hook:

1. Search by PDB function name, nearby string, or address.
2. Read the clean legacy body to understand expected game semantics.
3. Compare against the Redux corpus or live probes before hardcoding Redux
   addresses.
4. Keep shim code clean-room: cite observations and behavior in RE notes, then
   implement equivalent logic in `src\`.
