# UI render exception fail-soft (Lua error alert closed the game)

Status: 2026-10-14. Two fixes, one safety net and one root-cause repair.

## Symptom

A Lua runtime error on a multiplayer co-op host closed the whole game and every guest lost the session. Harness run
`cr-misn11-assists-Overridemisn11-coop-4p-20261014-014130`, host `BZLogger.txt`:

```text
01:45:49.934 Lua script Update error: [string "misn11.lua"]:545: bad argument #2 to 'Formation' (number expected, got userdata)
01:45:49.934 Starting alert in game UI wrapper
01:45:49.966 Creating screen of type 29
01:45:49.974 Ogre Rendering Exception Seen from UI: ... without both vertex and fragment shaders ...
01:45:50.003 Closing application due to complete render failure
```

## Root cause

Two independent faults stacked.

1. **The alert path has a fatal exception handler; the gameplay path does not.** The Lua error alert is a UI view run
   by the UI frame function at `0x007C7070`, which wraps `Ogre::Root::renderOneFrame` in a try block. Its catch funclet
   (`0x007C7340`) calls the quality ladder at `0x007AE480`; when the ladder has nothing left to lower it logs
   `Closing application due to complete render failure` and sets the exit state (`0x00434170(9)`). Otherwise it logs
   `Ogre Rendering Exception Seen from UI` and resumes. The ordinary in-game render path only logs
   `Ogre Rendering Exception Seen` and carries on. So an exception the game survives all mission long is terminal the
   frame the alert opens. The alert renders the whole scene, not just its panel, so the exception need not come from the
   alert.
2. **Something in the scene threw on every frame.** The same run logged 8,651 `Ogre Rendering Exception Seen` lines
   (120-185 per second) from the moment the mission loaded. The trigger is OpenShim's own multiplayer flag billboard
   material `OpenShimFlag_<hash>` (`src/patches/multiplayer_vehicle_flags.cpp`). It is written as a plain fixed-function
   `.material` with no `vertex_program_ref` / `fragment_program_ref`. D3D11 has no fixed pipeline, so every draw of it
   throws, and the throw abandons the rest of that frame. The shipped preset has `DX11LegacyMaterialCompat = 0`, which
   makes the compat ladder decline the material (`[DX11COMPAT] skipped shaderless draw material=OpenShimFlag_... vs=<none>
   ps=<none>`), so nothing replaced it. Runs with no flag material (`flags=0` in `openshim.log`) logged zero exceptions.

Any other shaderless draw in a mod has the same effect, which is why fault 1 is fixed independently of fault 2.

## Fix

* **`UI Render Exception Fail-Soft`** (`scripts/patches.json` globals, `include/patches.h`): the `JNE` at `0x007C734C`
  becomes `JMP`, so the exhausted-ladder branch is unreachable. A render exception under a UI view is logged and the
  frame is dropped, exactly as in gameplay. Pattern-checked (`require_unique`) with the original byte `75` verified, so
  it stands down on any other build.
* **OpenShim-owned materials always convert** (`Dx11Compat::EffectiveCompatConfigForMaterial`): materials whose name
  starts with `OpenShim` take the fixed-function conversion even when the user set `DX11LegacyMaterialCompat = 0`.
  That setting gates third-party content; it was never meant to leave OpenShim's own materials shaderless.

## Verification

See the pull request for the harness runs. Unit tests: `dx11_legacy_material_compat_tests` (`TestOpenShimOwnedMaterials`)
and `patch_registration_tests` (the new patch is registered in both files).

## Not changed

The alert is still the stock game UI. With the safety net the worst case for a persistent shaderless draw is a
per-frame log line under a UI view, not an exit.
