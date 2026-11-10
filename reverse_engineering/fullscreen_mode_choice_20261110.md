# Full Screen row: Windowed / Fullscreen / Borderless (graphics options screen)

Build: released GOG 2.2.301 (exe SHA-256 8D71F56C...3377413). Decompile lines
are from the ghidrecomp corpus
`Battlezone_Source\BZ1\Redux\openshim_re_corpus\bzr_gog_best_effort\ghidrecomp\results\bins\battlezone98redux.exe-6777ca\decomps\`
(line numbers count blank lines); addresses and bytes were read from the
shipping exe. Code: `src/patches/fullscreen_mode_choice.cpp`; rows: `FsMode*`
in `scripts/patches.json` `engine_addresses`, plus the existing
`ResListAddTarget` (checklist add) and `ResDropChecklistSelectValue`.

## Building the row (`FUN_007af4a0`, options ctor 0x007AF4A0)
- Lines 1013-1049: looks up the Ogre "Full Screen" config option; its
  currentValue is at map entry + 0x18.
- Line 1067: `FUN_007c3150("screenChecklist", ...)` builds the cUI_Checklist;
  line 1077 stores it at `local_1a4[0x54]` = screen+0x150.
- Lines 1081-1093: for each Ogre possibleValues entry, `FUN_007c3ac0(text,
  index)` adds an item whose text is the raw value ("Yes" / "No") and whose
  value is the index, then compares it with currentValue and selects it.
  The order of "Yes"/"No" in possibleValues is UNVERIFIED (the code looks the
  "Yes" item up by text, so it does not depend on it).
- 0x007B07BE (exe bytes `68 30 E8 7A 00 8B 8D 60 FE FF FF 8B 89 50 01 00 00
  E8 1C 35 01 00 6A 00`, unique hit): `push 0x7AE830; mov ecx,[ebp-0x1A0];
  mov ecx,[ecx+0x150]; call 0x007C3CF0` at 0x007B07CF. This is the last call
  on the Full Screen list in the ctor, so the list is complete and selected
  when it runs.
- `0x007C3CF0` (bytes `55 8B EC 51 89 4D FC 8B 45 FC 8B 4D 08 89 88 D8 01 00
  00`): thiscall(this, cb), `ret 4`, stores cb at +0x1D8.
- Change callback `FUN_007ae830` calls `FUN_007af2f0`; line 9 there sets
  screen+0x19E = 1 (Full Screen dirty). No other cUI_OptionsGraphics function
  reads +0x150 (grep of the FUN_007* decomps).

## cUI_Checklist details used
- Items vector begin +0x1E4, end +0x1E8 (`0x004200B0` count = (end-begin)>>2),
  elements are `Item*`, Item = `{char text[0x40]; int value}` (`0x007C3120`
  strncpy 0x40, value at +0x40; `0x006CF300` returns [+0x40]).
- Selected index +0x1DC. `0x007C3C10` selects by value and does not call the
  +0x1D8 callback. `0x007C3D10` returns the selected item's text, or
  0x008A1AD8 when out of range.

## Applying (`FUN_007aebc0`, 0x007AEBC0, fastcall(screen))
- Only caller: the Apply button callback `FUN_007ae810` (installed by the ctor
  at line 1821, `FUN_007c23e0(FUN_007ae810)`): bytes at 0x007AE813
  `8B 0D A4 55 94 00 E8 A2 03 00 00 5D C3` = `mov ecx,[0x009455A4];
  call 0x007AEBC0; pop ebp; ret` (unique hit; the call is at 0x007AE819).
- Line 67: does nothing while +0x178 (the restart alert) is non-zero.
- Lines 85-105: when 0x19E, 0x19C or 0x1A0 is set, sets Ogre "Full Screen"
  to `FUN_007c3d10()` of the +0x150 list, i.e. the selected item's TEXT.
  So a third item must never be selected when this runs, or Ogre is handed
  "Borderless".
- Line 143: `FUN_00683620(1,1)` applies the change live and saves the config.
- Lines 147-211: when 0x19F or 0x19D is set: FSAA (`DAT_00873e08`),
  `Root::saveConfig` (line 203), recolour.
- Lines 223-253: when 0x19F, 0x19D or 0x1A1 is set, builds the "Alert" with
  `FUN_0081cb40("options","restart_required")` and stores it at +0x178.
- Lines 257-267: clears the dirty bytes.

## Design consequences
- Borderless = Ogre "Full Screen" "Yes" + `[Graphics] BorderlessFullscreen=1`.
  dxgi_flip_model.cpp reads that key once at startup, so changing it needs a
  restart; raising +0x19F reuses the stock restart_required alert (side effect:
  FSAA is re-set to the value the screen shows, which is its current one).
- DX11 detection: `RenderProfiles::IdentifyActiveRenderSystem() == 1` (Ogre's
  active render system by pointer identity). Module presence is wrong: a live
  GOG run (2026-11-10, pid 24536) had RenderSystem_Direct3D9.dll,
  RenderSystem_Direct3D11.dll and RenderSystem_GL.dll all loaded. On DX9 no
  item is added.
