# Portable Corpus Workflow

Use this when you want the RE workflow available on another PC without
re-running the full decompile pipeline there.

## What To Commit

Commit the repo-side automation and docs:

- `reverse_engineering/current_re_corpora.json`
- `reverse_engineering/search_re_corpora.ps1`
- `reverse_engineering/build_re_brief.py`
- `reverse_engineering/import_transferred_corpora.ps1`
- the pipeline and workflow docs
- focused RE notes

Do not normally commit the full generated corpora into the main repo history.
The two current corpora are roughly:

- Redux full corpus: about `345 MB` and `31,997` files
- Legacy full corpus: about `286 MB` and `30,195` files

That is workable for manual storage or release artifacts, but poor for normal
Git history.

## Recommended Transfer Method

1. Copy the finished corpus folders to the target machine.

Recommended names:

- `reverse_engineering\portable_corpora\bzr_gog_best_effort`
- `reverse_engineering\portable_corpora\legacy_bz1_exact_full`

2. Run the importer from the repo root:

```powershell
.\reverse_engineering\import_transferred_corpora.ps1
```

That recreates these local pointer directories:

- `reverse_engineering\current_global_corpus`
- `reverse_engineering\current_legacy_global_corpus`

3. Use the normal dual-corpus workflow:

```powershell
.\reverse_engineering\search_re_corpora.ps1 -Pattern "HowitzerClass"
python reverse_engineering\build_re_brief.py --query "weapon mask howitzer minelayer"
```

## Custom Locations

If you store the transferred corpora somewhere else, pass the paths directly:

```powershell
.\reverse_engineering\import_transferred_corpora.ps1 `
  -ReduxOutputRoot "D:\BZR\Corpora\bzr_gog_best_effort" `
  -LegacyOutputRoot "D:\BZR\Corpora\legacy_bz1_exact_full"
```

## Notes

- `current_global_corpus` and `current_legacy_global_corpus` are local generated
  pointers and are ignored by Git.
- `current_re_corpora.json` now uses repo-relative paths, so it is safe to
  commit and works on different checkout locations.
- If you eventually want to distribute the corpora more formally, use a zipped
  artifact or Git LFS rather than normal Git history.
