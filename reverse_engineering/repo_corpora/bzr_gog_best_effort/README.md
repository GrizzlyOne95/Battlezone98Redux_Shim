# Repo-Tracked Redux Best-Effort Corpus

This is the trimmed portable Battlezone 98 Redux GOG best-effort decompile
bundle tracked in the repo for use on other PCs.

Included:
- ghidrecomp decomp output
- inventory CSVs
- merged RVA name matches
- PDB reference exports
- binary string dumps
- portable current corpus index/manifest

Excluded:
- ghidra_projects
- local background/watcher pid files
- local pipeline logs

Refresh from a local workshop output with:

```powershell
.\reverse_engineering\sync_repo_best_effort_corpus.ps1
```
