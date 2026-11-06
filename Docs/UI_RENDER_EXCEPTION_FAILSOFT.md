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

* **`UI Render Exception Fail-Soft`** (`scripts/patches.json` globals, `include/patches.h`): the funclet entry at
  `0x007C7340` becomes `JMP 0x007C737B`, its log-and-continue branch, so the ladder is never called from here. A render
  exception under a UI view is logged and the frame is dropped, exactly as in gameplay. Pattern-checked
  (`require_unique`) with the original bytes `6A 01` verified, so it stands down on any other build. See the 2026-11-05
  section for why the original `JNE`->`JMP` at `0x007C734C` was not enough.
* **OpenShim-owned materials always convert** (`Dx11Compat::EffectiveCompatConfigForMaterial`): materials whose name
  starts with `OpenShim` take the fixed-function conversion even when the user set `DX11LegacyMaterialCompat = 0`.
  That setting gates third-party content; it was never meant to leave OpenShim's own materials shaderless.

## 2026-11-05: crash in the ladder itself, from a GPU skinning clone

Dump `battlezone98redux.exe.26912.dmp`: access violation reading `0x3C` at `0x007C3B6F`, opening the pause menu.

* **Stock fault.** Stack is catch `0x007C7340` -> ladder `0x007AE480` -> `0x007AE5B0` -> `0x007C3AC0`. The ladder
  repopulates the options dropdowns when `DAT_009455A4` is non-null (`FUN_007ae480-007ae480.c`, lines ~21 and ~39);
  `FUN_007af4a0-007af4a0.c:205` is that global's only writer and it is never cleared, so it dangles once options has been
  closed. The first fix kept this call. The funclet now skips it. This also ends stock's automatic quality drop on a UI
  exception (it forced low-noshadow); the other two render catches (`0x0068326E`, `0x00684D9B`) never called the ladder.
* **Exception source, OpenShim.** About 1,587 `Unable to set D3D11 vertex declaration ... getILayoutByShader` exceptions
  in the six seconds before the pause menu. A mission started under `en-high-noshadow`, then the scheme became
  `en-high-pssm`. The miss on the GPU skinning clone `OpenShim/GpuSkin/1/w1/__bz_material_default` reached the DX11 compat
  ladder, which added a technique with the unskinned `OSE_Compat_Untextured_vertex`. Ogre then cached hardware animation
  false for that scheme (entity cache in the dump: 14 true, 15 false) and bound blend-stripped vertices, while the shadow
  caster stayed the skinned twin that needs BLENDINDICES/BLENDWEIGHT. That the caster program was inherited by copying the
  technique is inferred; the bound program and declaration are observed.
* **Fix.** `ProbeDx11LegacyCompat` declines a miss on a clone (`Dx11Compat::IsGpuSkinningClone`), so Ogre falls back to
  the clone's skinned Default technique.
* **Known limit.** The decline skips the ladder's vertex-input fit. A clone whose Default program needs an input the mesh
  lacks (stock Untextured requires COLOR0) still throws after a scheme switch. It no longer kills the game.

## Verification

See the pull request for the harness runs. Unit tests: `dx11_legacy_material_compat_tests` (`TestOpenShimOwnedMaterials`)
and `patch_registration_tests` (the new patch is registered in both files).

## Not changed

The alert is still the stock game UI. With the safety net the worst case for a persistent shaderless draw is a
per-frame log line under a UI view, not an exit.
