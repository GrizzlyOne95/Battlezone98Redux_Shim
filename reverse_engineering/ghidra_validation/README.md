# Ghidra validation of `scripts/patches.json`

Headless-Ghidra scripts that check every patch, resolve, global, engine address
and static pointer in `scripts/patches.json` against the **GOG Redux 2.2.301**
executable loaded in Ghidra (analysis done, image base `0x400000`). They read
the repo's `patches.json`, so rerun them after editing it or after any new hook.

| Script | Checks |
|---|---|
| `ValidatePatches.java` | Patch/resolve patterns match (uniquely when `require_unique`), the scanned site equals the `fallback`, `rel32_target` anchors are `E8` CALLs landing on function starts, `abs32_operand` operands are in-image, `globals.expected_original` bytes match, hook sites end on instruction boundaries, engine addresses and static pointers exist (data rows have xrefs). Mirrors the runtime semantics in `hook_engine.cpp` / `resolve_table.cpp`. |
| `ValidatePatches2.java` | The entries the first script cannot judge alone: `prefer: fallback` pins, the UnitVo call-site pair, vtable slots point at function starts, `RetAddr_*` / LensFlare sites are instruction starts. |
| `scan_hardcoded.py` + `ValidateHardcoded.java` | Engine addresses written as literals in `src/` and `include/` that `patches.json` does not mention, classified as function start / instruction / mid-instruction / data / undefined. Finds addresses that are not guarded by anything. |

## Running

Scripts take `patches.json` path and an output directory as script arguments
(or `OPENSHIM_PATCHES_JSON` / `OPENSHIM_VALIDATE_OUT`); defaults are the repo's
`scripts/patches.json` and the system temp dir.

    python reverse_engineering/ghidra_validation/scan_hardcoded.py <out_dir>   # only for ValidateHardcoded
    # then run each .java from Ghidra's Script Manager, or through the Ghidra MCP
    # server (run_ghidra_script; needs GHIDRA_MCP_ALLOW_SCRIPTS=1).

Reports (`validate_report.txt`, `hardcoded_report.txt`) land in the output
directory: `OK` / `WARN` / `FAIL` per entry plus a summary.

## Reading the results

* `FAIL` is a real mismatch (pattern not found, fallback disagrees with the
  scan, bytes differ). `WARN` needs a human look.
* A clean `ValidatePatches.java` run still prints ~29 `WARN`s: the vtable `globals` slots (data, not code), the `RetAddr_*` / LensFlare static pointers (code addresses with no data xrefs) and the two UnitVo call-site resolves (no fallback, runtime-settled). `ValidatePatches2.java` checks each of those properly; all should be `OK` there.
* `ValidatePatches.java` is GOG-only. Entries tagged `"platforms": ["steam"]`
  are only shown to still match the GOG image, not validated for Steam.
* This proves addresses, bytes and instruction structure. It does not prove a
  hook's behaviour. Struct field offsets used by hooks (for example the
  voice-cap offset in `patcher.cpp`) are not in `patches.json` at all; guard
  them with an `engine_addresses` row whose `expected` bytes include the
  displacement (see `GAS_SetMaxVoices`).
