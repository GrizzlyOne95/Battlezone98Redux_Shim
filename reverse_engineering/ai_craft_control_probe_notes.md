# AI Craft Control Probe Notes

## Scope

This note captures a live Steam-process probe run on `2026-03-17` against the currently running `battlezone98redux.exe`.

The goal was to learn more about the missing "advanced AI control" gap for:

- craft-side movement control beyond EXU's current `UnitTask` fields
- `jump`
- broader special/action flags like `eject`, `deploy`, and `abandon`

## New Probe Helper

Use:

- `reverse_engineering/probe_ai_craft_controls.py`

What it does:

- reads the live `.text` section from the running Steam process
- scans for machine-code accesses to likely craft-control offsets
- annotates each hit with the nearest advisory Redux PDB public symbol
- separately looks for the more promising pattern:
  - load pointer from `obj + 0xF4`
  - then access nearby control-style offsets on that same register

This is intentionally a live-process probe rather than a pure on-disk scan because the Steam executable on disk does not cleanly match the executing code bytes.

## Current Findings

### 1. The naive `+0xD0/+0xD4/+0xD8/+0xDC` scan is noisy

The live Steam image does contain direct accesses at those displacements, but most of the obvious hits land near unrelated or misleading symbol neighborhoods:

- `GameObject::PostLoad / Load / Save`
- `DayWrecker::*`
- `EditTerrain::*`

This means the simple "find everything touching `+0xD0` and assume it is `jump`" approach is not safe.

Observed direct-hit buckets from the live process included:

- `0x0046CFEA`, `0x0046D00A`, `0x0046D537`, `0x0046D54A`, `0x0046D55D`, `0x0046D603`, `0x0046D62F`, `0x0046D65C`, `0x0046D9AE`, `0x0046DAE0`, `0x0046DCA5`
  - nearest advisory neighborhood: `GameObject::PostLoad / Load / Save`
- `0x00450E7C`, `0x00450E9C`, `0x00450F8D`, `0x004515D2`, `0x004515F0`, `0x004515FB`, `0x00451612`, `0x0045161D`
  - nearest advisory neighborhood: `DayWrecker::*`
- `0x0045CC91`, `0x0045CCA5`
  - nearest advisory neighborhood: `EditTerrain::*`

These are worth keeping on record specifically so later agents do not waste time treating them as clean AI-control ownership.

### 2. The confirmed live AI-ish control consumer found so far is still the lower movement pair

The strongest control-style hits in the running Steam image are:

- `0x004706C7`
  - `mov ecx, dword ptr [eax + 0xF4]`
- `0x004706D3`
  - `mov eax, dword ptr [edx + 0xF4]`
- `0x004706E1`
  - `addss xmm0, dword ptr [eax + 0xBC]`
- `0x00470716`
  - `addss xmm0, dword ptr [ecx + 0xC0]`

Nearest advisory symbol neighborhood:

- `GechProcess::*`

Interpretation:

- this supports the current EXU model that AI movement ultimately feeds a second craft/vehicle-side state block
- at least two live fields from that block are still being consumed in the Steam build
- the pair looks consistent with `steer` and `braccel`
- the pointer load through `obj + 0xF4` is the strongest current candidate for the handoff from higher-level AI object to lower craft/vehicle control state

### 3. We do not yet have a trustworthy live `jump` producer/consumer site

The direct `+0xD0` hits found in this pass did **not** land in a clear `UnitTask` / `UnitProcess` / craft-simulation neighborhood.

So the current evidence does **not** justify shipping a blind EXU `jump` setter that just pokes a guessed field.

The live pass did find `+0xD0` accesses, but they were inside the noisy buckets above rather than a trustworthy `UnitTask`, `UnitProcess`, or craft simulation site.

## Cross-Repo Breadcrumbs

Relevant repo locations recorded for later agent work:

- Shim-side probe helper:
  - `C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\probe_ai_craft_controls.py`
- Captured live-process report from the successful rerun after the EXE was relaunched:
  - `C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\ai_craft_control_probe_report_20260317.md`
- This summary note:
  - `C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\ai_craft_control_probe_notes.md`
- Current EXU task-state implementation:
  - `C:\Users\iestu\Documents\ExtraUtilities\src\GameObject.cpp`
- Shared high-level feature tracker entry:
  - `C:\Users\iestu\Documents\ExtraUtilities\FeaturesToLookInto.txt`

## Practical Conclusion

This probe strengthens the current split:

- EXU's existing `UnitTask` state exposure is a real foothold for movement shaping
- the missing "emulate a player" coverage likely requires a second layer:
  - resolve the true live craft/control packet for the active unit
  - then instrument or patch the handoff between task logic and craft simulation

For now, the safest statement is:

- `steer` and `braccel` have live craft-side consumers confirmed in the Steam process
- `jump` remains unresolved in the live AI path
- the obvious `+0xD0` scan space contains too many false positives to expose it cleanly yet

## Recommended Next Probe

The next high-value pass should be dynamic rather than static:

1. pick a known AI-controlled craft live in mission
2. resolve its actual craft/vehicle pointer from EXU-side handle data
3. watch the small control block in memory over time while forcing behavior transitions
4. correlate the changing bytes with:
   - `exu.GetAiTaskState()`
   - task type changes
   - actual observed jump/deploy/eject behavior

That would turn the current address/offset hints into a real per-field mapping instead of another blind offset guess.
