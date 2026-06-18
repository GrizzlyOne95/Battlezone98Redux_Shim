# Legacy To Redux Symbol Transfer

This repo now has a repeatable sidecar symbol-transfer pass for mapping reliable
Battlezone 1.5 PDB names onto likely Battlezone 98 Redux functions.

The current generated map is:

`reverse_engineering\workshop\symbol_transfer\legacy_to_redux\legacy_to_redux_symbol_map.csv`

Current run summary:

- Legacy functions fingerprinted: `14263`
- Redux functions fingerprinted: `25168`
- Accepted candidate transfers: `713`
- Confidence counts: `8 very_high`, `1 high`, `278 medium`, `426 low`

## Generate

From the repo root:

```powershell
python reverse_engineering\build_legacy_to_redux_symbol_map.py
```

Useful debug run:

```powershell
python reverse_engineering\build_legacy_to_redux_symbol_map.py `
  --max-legacy 200 `
  --output-dir reverse_engineering\workshop\symbol_transfer\legacy_to_redux_test
```

The script reads:

- `reverse_engineering\current_re_corpora.json`
- `reverse_engineering\current_legacy_global_corpus`
- `reverse_engineering\current_global_corpus`

It uses the exact-match legacy names as the source of truth and treats the
Redux corpus as unnamed behavior to match. It does not apply names directly into
Ghidra.

## Search

```powershell
.\reverse_engineering\search_legacy_to_redux_symbol_map.ps1 -Pattern "StartMusic"
.\reverse_engineering\search_legacy_to_redux_symbol_map.ps1 -Pattern "luaB_" -Confidence medium,high,very_high
```

Important CSV columns:

- `legacy_name`: exact-match 1.5 PDB name.
- `redux_entry_rva`: candidate Redux RVA for patch work.
- `redux_static_prologue`: first bytes from the Steamless-unpacked Redux file
  at the candidate entry VA.
- `confidence`: `very_high`, `high`, `medium`, or `low`.
- `score` and `margin`: match strength and separation from the next candidate.
- `methods`: evidence used, such as shared strings or exact normalized decomp.
- `redux_decomp`: current Redux decompiler file to inspect.

## Trust Model

- `very_high`: usually CRT/helper functions where normalized decomp matched
  exactly. Still validate before patching.
- `high`: strong decomp/string evidence with a clear margin.
- `medium`: good manual-review candidate.
- `low`: breadcrumb only; use it to start RE, not to approve a hook.

Rows with `same_string_set` are useful for locating subsystems but can be
ambiguous when several functions share the same format string. For example, the
current map places:

- `StartMusic` at Redux RVA `0x000378f0`, low confidence, shared `%02d.ogg`.
- `StopMusic` at Redux RVA `0x00037a70`, medium confidence, shared `%02d.ogg`.

Those are good starting points, but the final hook decision must come from
manual decomp inspection plus runtime byte validation.

This pass is static-only. It was generated from the unpacked Redux corpus and
the exact-match legacy corpus; it does not prove that a candidate RVA is already
safe to patch in a packed Steam launch. If the app cannot be launched in the
current environment, stop at candidate identification and carry the RVA,
`redux_static_prologue`, and decomp evidence into a later runtime validation
pass.

## Patch-Site Workflow

For a candidate row:

1. Open the legacy decomp to recover semantics and original names.
2. Open `redux_decomp` from the map and confirm behavior against strings,
   globals, callers, and nearby functions.
3. Probe `moduleBase + redux_entry_rva` after the Redux SteamStub settle delay.
4. Record expected prologue bytes or a masked byte signature before patching.
5. Compute the trampoline length from decoded x86 instructions, not from a
   fixed byte count.
6. Keep the task note explicit about whether the symbol-map row was sufficient
   or only a starting breadcrumb.

The mismatched Redux beta PDB should remain advisory. Do not force-apply it as a
bulk Ghidra rename source unless each affected function is independently
validated.

When launch/debugging is unavailable, compare the candidate against the
Steamless-unpacked file bytes and defer live prologue validation. Do not treat a
packed-image byte read as a failed match unless the process is known to have
settled into the same layout as the static unpacked corpus.
