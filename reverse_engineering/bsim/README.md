# BSim legacy→Redux function matcher

Semantic (decompiler p-code) function matching between **legacy Battlezone 1.5**
(`bzone.exe` build 227, symbolized from the exact-match `bzint.pdb`) and the
**unpacked Battlezone 98 Redux** executable, wired into the existing
`build_legacy_to_redux_symbol_map.py` text-shingle pipeline as an independent,
stronger second signal.

Where the text pipeline matches decompiled-C *tokens*, BSim matches normalized
p-code *feature vectors* (Ghidra's `medium_nosize` LSH template) — far more robust
to compiler/optimization differences between the 1998 build and Rebellion's remaster.

## Pipeline

```
import_programs.ps1      # 1. import bzone.exe (+bzint.pdb) and unpacked redux into ./project
run_bsim_compare.ps1     # 2. in-memory BSim compare -> out/bsim_matches.csv
merge_bsim_into_symbol_map.py   # 3. join into text map -> out/legacy_to_redux_symbol_map.bsim.csv
run_all.ps1              # runs 1→3 end to end
```

### 1. `import_programs.ps1`
Builds a single Ghidra 12.0.4 project `project/bz_bsim` containing both programs.
The legacy import uses `ghidra_scripts/SetPdbFile.java` as a **pre-script** because
`PdbUniversalAnalyzer` will not search next to the binary in headless mode — without
it the 1.5 side imports with no symbols and there is nothing to transfer. Redux is
imported without a PDB (its shipped PDB is a mismatched beta; we only need its
function RVAs).

### 2. `run_bsim_compare.ps1` → `ghidra_scripts/BSimCompareExport.java`
A headless port of Ghidra's stock `LocalBSimQueryScript.getMatchesTwoPrograms()`.
For every **named** legacy function it computes BSim similarity + significance against
every Redux function and writes the top-N (default 5) to `out/bsim_matches.csv`:

```
legacy_va,legacy_name,legacy_namespace,target_rva,target_va,target_name,similarity,significance
```

- `similarity`  0..1 cosine of the LSH vectors (1.0 = identical p-code signature).
- `significance` scaled log-probability the match is not chance; higher = rarer/safer.

Tunables (script args): `MaxMatches`, `MinSim` (default 0.50). Self-significance floor
15.0 drops trivially small functions, matching the stock script.

### 3. `merge_bsim_into_symbol_map.py`
Joins `bsim_matches.csv` onto the text map on `legacy_entry_va` and emits:

- **`out/legacy_to_redux_symbol_map.bsim.csv`** — every original text-map column, plus
  `bsim_redux_rva`, `bsim_similarity`, `bsim_significance`, rank-2 match, a
  `bsim_agreement` cross-check (`exact` / `diff` / `bsim_only` / `text_only`) and a
  fused `combined_confidence`. `exact` = both independent methods point at the same
  Redux RVA → strongest evidence.
- **`out/bsim_only_discoveries.csv`** — functions BSim located that the text pipeline
  missed, ranked by significance. This is the net-new reverse-engineering yield.
- **`out/bsim_merge_summary.json`** — agreement / confidence histograms.

## Caveats
- The RVA cross-check assumes both pipelines target the **same Redux build**. Both use
  the `redux_documents_unpacked` family here; if you re-point either side at a different
  build, `bsim_agreement` degrades to `diff`/`bsim_only` and BSim stands alone as an
  independent signal (still valid, just uncorroborated).
- BSim ranks candidates; it does not prove a match. Treat `very_high`/`exact` as strong
  naming candidates, not automatic hook approval — the existing validation rules in the
  text-map README still apply (validate live RVA + prologue bytes before patching).
- Redux is a remaster, not a recompile: expect strong matches on simulation/gameplay/math
  and few on rewritten renderer/platform/netcode code.

## Object model extraction (for the UE port)
`ghidra_scripts/ExportObjectModel.java` + `render_object_model.py` dump the 1.5 PDB's
reconstructed C++ types to `out/object_model/`:
- `core_object_model.md` — 23 curated game classes (fields + methods + inferred inheritance).
- `object_model.json` — all 1,014 game-relevant types, full field/method detail.
- `all_types_index.csv` — every struct/union + size (6,396). `enums.md` — game enums.

Confirmed hierarchy: `GameObject`(544)→`Craft`(616)→`HoverCraft`/`Walker`, with a parallel
`GameObjectClass`→`CraftClass`→`HoverCraftClass` config tree (every object has a paired
`XClass` holding ODF-driven stats). This is the authoritative schema the port mirrors.

## Gameplay logic export (for the UE port)
`ghidra_scripts/ExportGameplayLogic.java` decompiles a focused 1.5 behavior slice: all
`Misn*Mission` classes plus the core object/combat/AI classes (`GameObject`, `Craft`,
`HoverCraft`, `Weapon`, `Ordnance`, `Team`, `AiMission`, etc.). Run:

```
.\run_gameplay_logic_export.ps1
```

Current output lives in `out/gameplay_logic/`:
- `gameplay_logic.md` — summary report and mission `Execute` file index.
- `index.csv` — machine-readable map of VA, namespace, function, signature, status, line count,
  and relative source path.
- `decompiled/` — one source-like `.cpp` file per exported function.

Verified run: **784** functions, **0** decompile failures, **43,467** decompiled lines across
**48** classes/namespaces. This includes **25** mission `Execute` methods (`Misn01Mission` through
`Misn18Mission`, plus `Misns1Mission` through `Misns8Mission`) and core vehicle logic such as
`HoverCraft::Simulate`.

## Applying names onto Redux (for the DLL shim)
`prep_apply_input.py` filters the merged map to `very_high`/`high` rows → `out/apply_input.tsv`;
`ghidra_scripts/ApplyNamesToRedux.java` (run `-process` on the Redux program, writable) renames
those Redux functions to their namespaced 1.5 names and attaches each function's exact 1.5
prototype + BSim provenance (similarity/significance/agreement) as a plate comment. Log:
`out/redux_named.csv`. First run applied **323** names (0 failures). Verify read-only with
`VerifyReduxNames.java`. Writes go only to the regenerable `bz_bsim` project copy.

## Applying 1.5 signatures onto Redux (for safer hooks)
`prep_signature_apply_input.py` builds `out/signature_apply_input.tsv` from the high-confidence
BSim rows, exact Lua registration-table rows, and supplemental Lua-runtime rows that have a 1.5
source VA. `ghidra_scripts/ApplyReduxSignaturesFromBz15.java` opens the 1.5 program read-only,
clones return/parameter data types into the Redux DataTypeManager, and updates the destination
function using Ghidra dynamic parameter storage. Run:

```
.\run_redux_signature_apply.ps1
```

Verified run: **590** Redux function prototypes applied, **0** missing source functions,
**0** missing Redux functions, **0** failures. This upgrades a large portion of the named hook
surface from "right name + prototype comment" to actual Redux function signatures in the local
Ghidra project copy. Log: `out/redux_signatures_applied.csv`.

`render_redux_hook_catalog.py` joins the named functions, Lua API targets, Lua runtime names,
and signature-transfer log into:
- `out/redux_hook_catalog.md` — prioritized hook target report.
- `out/redux_hook_catalog.csv` — machine-readable hook catalog.

Current catalog: **629** Redux hook/reference entries, with **590** having applied signatures.

## Curated 1.5 port reference
`render_port_reference.py` reorganizes the broad gameplay export into a porting-focused subset:

```
python .\render_port_reference.py
```

Current output lives in `out/port_reference/`:
- `port_reference.md` — subsystem report.
- `index.csv` — machine-readable function index.
- `decompiled/<system>/...` — copied source-like files grouped by subsystem.

Verified run: **458** unique 1.5 functions selected (**523** system-tagged rows):
AI/tasks/orders **78**, damage/explosion/combat **116**, save/load state **124**,
factory/build logic **170**, team/resources **35**.

## Stock FID and Lua runtime cleanup
`ghidra_scripts/ApplyStockFidNames.java` wraps Ghidra's stock Function ID command and logs only
newly-added library labels. Run:

```
.\run_stock_fid.ps1
```

Result on the current Redux project copy: stock VS FID added only **11** ambiguous MFC/STL conflict
labels and did **not** increase the primary named-function count. Treat this as a useful negative
finding: the stock FID databases are not the next big coverage lever for this binary as imported.
The log is `out/stock_fid_battlezone98redux.exe.unpacked.exe.csv`.

The stronger Lua-runtime signal comes from the 1.5 PDB names plus BSim. `prep_lua_runtime_apply.py`
filters the merged BSim map to Lua 5.1.5 runtime/library names with significance >= 30, excluding
known collision/low-conflict classes. `ApplySupplementalBsimNames.java` then applies only to Redux
functions that are still default-named, preserving existing BSim/Lua API names. Run:

```
.\run_lua_runtime_apply.ps1
```

Verified run: **130** Lua/runtime candidates, **65** newly named Redux functions, **65** skipped
because they were already named, **0** missing functions, **0** rename failures. Redux non-default
named functions increased **2,481 → 2,546**. Combined with the earlier high-confidence BSim pass,
there are now **146** named Lua-runtime/library functions in Redux. Logs:
`out/lua_runtime_apply_input.tsv` and `out/lua_runtime_names_applied.csv`.

## Lua script-binding recovery (registration table)
BSim cannot separate the tiny mission-script getters/setters (`GetCurAmmo`, `GetOwner`,
`GetTarget`, …) — they compile to near-identical code and collapse onto one Redux address.
The engine's own `luaL_reg` registration table disambiguates them exactly: each API name
string is paired with its `lua_CFunction` pointer in `.rdata`.

`ghidra_scripts/LuaBindingTableExtractor.java` reads that table in each binary — for every
documented API name (`out/lua_api_names.txt`, scraped from the official BZ script-utilities
reference) it finds the name string, the table slot pointing at it, and the adjacent function
pointer. Run both via `run_lua_bindings.ps1` → `out/lua_bindings_{legacy,redux}.csv`.

Self-validation: on 1.5 **all 203** recovered pointers resolve to a function already named
exactly like the API primitive (0 mismatches) — proving the method. Redux yields **242**
entry points at **242 distinct** RVAs (0 collisions).

`ApplyLuaBindings.java` (via the join in `lua_apply_input.tsv`) renames those 242 Redux
functions and attaches each one's 1.5 prototype + provenance (`out/lua_bindings_applied.csv`).
The formerly-collided cluster is now 10 distinct correct names. Verify with `VerifyLuaBindings.java`.
The readable cross-binary map is `out/lua_api_map.md` / `.csv` (API primitive → 1.5 impl VA →
Redux VA) — the mission-script contract for the UE port and the hook table for the DLL shim.

## Cross-check with BinDiff (optional follow-on)
For a third opinion, export both programs with the Ghidra **BinExport** plugin and diff in
Google BinDiff; its call-graph matching is a good independent tie-breaker on `diff` rows.
