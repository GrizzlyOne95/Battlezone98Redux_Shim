# Global Decompile Pipeline

This repo now includes an unattended best-effort pipeline for native Battlezone
reverse-engineering.

What it does:

- extracts PE string corpora from the target binary
- exports advisory metadata from a nearby PDB even when the PDB does not match
  the EXE exactly
- runs `ghidrecomp` over the binary to produce a cached Ghidra project and
  per-function decompilation corpus
- exports a machine-readable Ghidra inventory after analysis
- joins Ghidra functions to PDB public symbols by RVA where that still lines up

Important behavior:

- the PDB is only applied directly inside Ghidra when the EXE RSDS GUID and age
  exactly match the PDB, unless you force it
- the PDB reference export still runs even when the pair is mismatched, because
  names, classes, modules, and source paths remain useful as advisory metadata

## Background Run

From the repo root:

```powershell
.\reverse_engineering\start_best_effort_pipeline.ps1
```

Useful switches:

```powershell
.\reverse_engineering\start_best_effort_pipeline.ps1 `
  -BinaryPath "C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe" `
  -PdbPath "C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb" `
  -OutputRoot ".\reverse_engineering\workshop\global_decompile\bzr_gog" `
  -ForceAnalysis `
  -Callgraphs
```

The launcher writes:

- `background_stdout.log`
- `background_stderr.log`
- `background_pid.txt`

## Direct Run

```powershell
python reverse_engineering\run_best_effort_pipeline.py `
  --binary "C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe" `
  --pdb "C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb" `
  --force-analysis
```

Useful flags:

- `--callgraphs` to ask `ghidrecomp` for per-function callgraph markdown
- `--skip-llvm` to disable `llvm-pdbutil` text exports
- `--lightweight-pdb` to skip the heaviest `llvm-pdbutil` dumps
- `--force-pdb-in-ghidra` to force a mismatched PDB into the Ghidra analysis
  step

## Output Layout

The default output root is:

`reverse_engineering\workshop\global_decompile\<binary-stem>_<sha256-prefix>`

Key artifacts:

- `pipeline_manifest.json`
- `SUMMARY.md`
- `binary_strings\ascii_strings.csv`
- `binary_strings\utf16_strings.csv`
- `pdb_reference\reference.json`
- `pdb_reference\public_functions.csv`
- `pdb_reference\modules.csv`
- `pdb_reference\llvm\*.txt`
- `ghidrecomp\results\bins\<project>\decomps\*.c`
- `inventory\functions.csv`
- `inventory\symbols.csv`
- `merged\function_matches_by_rva.csv`

## Notes

- `llvm-pdbutil` is auto-discovered at
  `C:\Program Files\LLVM\bin\llvm-pdbutil.exe`
- `GHIDRA_INSTALL_DIR` is taken from the environment, which is already set in
  this environment
- the pipeline is safe to rerun; `ghidrecomp` uses its cached project unless
  you force re-analysis or skip cache

## Promote And Search

When a run is complete, promote it into a stable pointer/index with:

```powershell
python reverse_engineering\finalize_global_corpus.py `
  --output-root ".\reverse_engineering\workshop\global_decompile\bzr_gog_best_effort"
```

Or let a watcher do that automatically after a background PID exits:

```powershell
.\reverse_engineering\watch_best_effort_pipeline.ps1 `
  -ProcessId 12345 `
  -OutputRoot ".\reverse_engineering\workshop\global_decompile\bzr_gog_best_effort"
```

After promotion, future searches should target the promoted corpus first:

```powershell
.\reverse_engineering\search_global_corpus.ps1 -Pattern "weapon mask"
```

To generate a starting brief for a new agentic RE task:

```powershell
python reverse_engineering\build_re_brief.py --query "weapon mask howitzer"
```

## Dual-Corpus Workflow

The default RE workflow now assumes two promoted corpora:

- `reverse_engineering\current_global_corpus` for current Redux behavior
- `reverse_engineering\current_legacy_global_corpus` for exact-match legacy
  semantics

The stable registry is:

- `reverse_engineering\current_re_corpora.json`

Search both corpora with:

```powershell
.\reverse_engineering\search_re_corpora.ps1 -Pattern "HowitzerClass"
```

That default search hits indexes, strings, and metadata first. Add
`-IncludeDecomps` when you need to grep the full decomp trees.

Limit the search to one corpus when needed:

```powershell
.\reverse_engineering\search_re_corpora.ps1 -Pattern "HowitzerClass" -CorpusLabels legacy
.\reverse_engineering\search_re_corpora.ps1 -Pattern "HowitzerClass" -CorpusLabels redux
```

Build a combined starter brief with:

```powershell
python reverse_engineering\build_re_brief.py --query "weapon mask howitzer minelayer"
```

That brief now pulls from both corpora automatically when both promoted roots
exist.

For moving finished corpora to another PC without rebuilding them, use:

- `reverse_engineering\portable_corpus_workflow.md`
- `reverse_engineering\import_transferred_corpora.ps1`
