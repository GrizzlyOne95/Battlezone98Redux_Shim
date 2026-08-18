# Shift+F10 editor object placement — Redux vs BZ 1.5

**Date:** 2026-08-17
**Legacy reference:** `bzone.exe` 1.5 + exact-match `bzint.pdb` (15,070 functions)
**Redux target:** GOG `battlezone98redux.exe`, SHA-256 `8d71f56c…3377413` (matches the repo decomp corpus)
**Status:** RE complete, root cause proven statically. **No patch implemented yet** -- section 7
sets out two designs and the one decision needed before code is written.

---

## 0. Headline, and a correction to the premise

Two things must be said before the call graph, because both change what the bug can be.

**(a) Shift+F10 is not the edit-mode toggle.** The shipped `gamekey.map` binds:

```
OVER_VIEW           SHIFT+F10        <- what the report calls "the Shift-F10 editor"
TOGGLE_EDITMODE     CTRL+E           <- the terrain editor
TOGGLE_ARCADE_MODE  CTRL+A
PAUSE_GAME          PAUSE  (also ALT+P)
```

Shift+F10 selects **`OVER_VIEW`**, the overhead view. Object manipulation in that view is not
unconditional: `OverView::Render` splits on `UserPref_arcadeMode()`, and only the arcade branch
does select / move / rotate / delete. `UserPref_arcadeMode()` is
`!Net_IsNetGame() && (UserProfile->playOption & 1)` — identical in both builds. That bit is set by
`TOGGLE_ARCADE_MODE` (Ctrl+A, itself gated on `TerrainEdit`), and also **automatically** by
`EditTerrain_Enter` (Ctrl+E). So the working editor state is *overhead view + arcade bit*, and the
non-arcade branch of the same function is ordinary RTS unit commanding.

**(b) The root cause is a transposed display-interface render priority for the overhead view.**
`DisplayInterface::AddView(view, priority)` inserts into a per-view list sorted ascending by
priority, so lower priority renders first. For view 3 (`OVER_VIEW`):

| registered by | 1.5 | Redux |
|---|---|---|
| `OverView` ctor | priority **0** | priority **1** |
| `ControlPanel` ctor | priority **1** | priority **0** |

The two constants are swapped. `OverView::Render` *publishes* `reticle.groundPos`;
`ControlPanel::Render` *consumes* it and refuses to build when it is null. In 1.5 the producer runs
first. In Redux the consumer runs first, reads the null that `Reticle::Simulate` wrote earlier in
the same frame, plays `mnu_clik.wav` -- which sits **outside** the null guard -- and skips the
`GameObjectClass::Build`. Full proof in section 6.

Pausing works because `Simulate()` (and therefore `Reticle::Simulate`, and therefore the null-out)
stops running, while Redux's pause path still renders the whole frame; the cursor freezes at the
same moment because `DisplayInterface::SimulateAll` is the sole writer of
`DisplayInterface::mousePos` and it stops too. Both halves of the reported symptom fall out of one
mechanism.

---

## 1. Function map

| Role | 1.5 | Redux |
|---|---|---|
| `DoFrame` / `DoNextFrame(paused)` | `0x0047A39D` | `0x00618270` |
| frame body (split out in Redux) | — | `0x00618130` |
| `NextInputs` | `0x004BAF9E` | `0x006210A0` |
| `ProcessInput` | `0x004B9EE8` | `0x0061DBA0` |
| `ProcessGK` | `0x004B9B98` | `0x0061DC10` |
| `Simulate` | `0x004789C5` | `0x00618060` |
| `ControlWeapons` | `0x0047894D` | `0x00617FA0` |
| `Render_Next_Frame` | `0x004786E9` | `0x006175C0` |
| `HandleGamePauses` | `0x0047A355` | `0x00617F50` |
| **`Render_Pause_Message`** | `0x00477FB2` | **`0x00617800`** |
| `PauseKeyToggle` | `0x0054F32D` | `0x00821050` |
| `SetScreenMode` | `0x0054F2E2` | `0x00820FE0` |
| `HandlePauseInput` | `0x0054F4FA` | `0x00821020` |
| LockMouse / UnlockMouse | — | `0x00623EB0` / `0x00623FF0` |
| `UserPref_arcadeMode` | `0x00478729` | `0x00451DE0` |
| `DisplayInterface_SimulateAll` | `0x004C86F7` | `0x004B6EF0` |
| `DisplayInterface::SimulateAll` | `0x004C8584` | `0x004B6C80` |
| `DisplayInterface::RenderAll` | `0x004C8633` | (not resolved) |
| `Set_View` | `0x0047A6DB` | `0x0061D120` |
| view fn table (10 × `{code,fn}`) | `Int_View_Fnction_Table` | `0x008EAD18` |
| `Toggle_Edit_View` (GK `0x2A`) | `0x0047B46B` | `0x0061C110` |
| `Apply_Edit_View` | `0x0047B3A9` | `0x0061BF60` |
| `Exit_Edit_View` | `0x0047A6CA` | `0x0061C0F0` |
| `Apply_2D_View` | `0x0047B48E` | `0x0061C150` |
| Apply over-view (GK code 7) | — | `0x0061BD20` |
| `EditTerrain_Enter` / `_Exit` | `0x004CD00D` / `0x004CA3A7` | `0x004C82D0` / `0x004C8310` |
| `SetControlMode` / `SetEditMode` | `0x004ACCF7` / `0x004ACD0E` | `0x005B0900` / `0x005B0920` |
| **`OverView::Render`** | `0x004D37B2` | **`0x00587EF0`** |
| **`ControlPanel::Render`** | `0x004C4998` | **`0x004A08E0`** |
| `GameObjectClass::Build` | `0x00498D9C` | `0x004E1190` |
| `GameObject::SetOrigin` / `SetTransform` | — | `0x005873A0` / `0x0056D6A0` |
| `PathDisplay::Render` | `0x004D873B` | `0x00594CA0` |
| `PathDisplay::HandleControlMode` | `0x004D86AD` | `0x005981A0` |
| `PathDisplay::DrawMenuBar` | `0x004D7289` | `0x00595250` |
| `PathDisplay::DrawBuildMenu` | `0x004D6BB9` | `0x0059B550` |
| `PathDisplay::DoControlObject` | `0x004D8280` | `0x0059ADD0` |

Identification method: structural fingerprint, not PDB address. `PathDisplay::Render` was anchored
on its `sprintf` cursor/zoom status line and its five-call body; `DrawMenuBar` on the exact
`mode_select[1..6]` → `menuMode` ladder; `OverView::Render` on the
`TerrainEditMode` early-out + radar-rect early-out + `MoveCamera` + `arcadeMode` split;
`ControlPanel::Render` on the editor build-menu `Build` call site. Each was cross-checked against
at least one independent caller.

## 2. Verified globals and offsets (Redux)

| Field | Address / offset |
|---|---|
| `WeAreActive` | `0x008EAAA4` |
| `ScreenMode` (dword) | `0x008FE240` — `SIM = 1`, `PAUSE = 2` |
| `LastMode` | `0x008FE23C` |
| `View_Record` | `0x008EAAD0`; `Update_Camera +0`, `Intenal_View +4`, `Current_View +8`, `Camera_Owner +0x1E8` |
| `useDisplayInterface` | `0x008EAAB0` |
| `Cockpit_Visible` | `0x008EAD0C` |
| `hudFlags` | `0x008EAAAC` |
| `TerrainEdit` | `0x009454B8` |
| `TerrainEditMode` | `0x009454A4` |
| `UserProfilePtr` | `0x0094672C`; `playOption` at `+0x30`, bit 0 = arcade/freeze |
| `command_controls.cmd_x` / `cmd_y` | `0x00919868` / `0x0091986C` |
| `cmd_click[0..1]` | `0x00919870`, `0x00919871` |
| `cmd_hold[0..1]` | `0x00919872`, `0x00919873` |
| `cmd_delete` / `cmd_multi` | `0x00919874` / `0x00919875` |
| `center_player` / `center_recycler` | `0x00919876` / `0x00919877` |
| `mode_select[0..9]` | `0x00919878` … `0x00919881` |
| `menu_back` | `0x0091988B` |
| `DisplayInterface::mousePos.x` / `.y` | `0x009175A0` / `0x009175A4` |
| `DisplayInterface::currentBuffer` / `currentCamera` | `0x00917580` / `0x00917594` |
| `reticle.groundPos` / `reticle.targetObject` | `0x025CE778` / `0x025CE77C` |
| `OverView::select` / staging matrix | `0x02CC2BD4` / `0x02CC3110` |
| discrete-control name table | `0x008EB1EC`, stride `0x20`, **`0x6F` (111) entries** (1.5: 106) |
| view fn table | `0x008EAD18`, stride 8, codes `1,2,3,4,5,6,7,0x2A,8,9` |

`View_Record` layout is confirmed by the `0x8E`-dword save/restore loop in both
`Apply_Edit_View` and `Apply_2D_View`, matching 1.5's `PRESET_VIEW` copy of the same length.

## 3. The 1.5 baseline (what "works while running" actually means)

`DoFrame` (`0x0047A39D`), instruction-verified:

```
call Get_Frame_Count ... ; respawn ; Device.ShutDownReq check
call SetLoopTimes                       ; 0x582074
call NextInputs                         ; 0x4BAF9E   <- clears then refills every discrete control
mov  eax, [WeAreActive]
test eax, eax        -> je  skip
test byte [0x633A88], 0x3E              ; ScreenMode & (MOVIE|MENU|NOTEPAD|MAP|PAUSE)
jne  skip
   ... CheckEntityCollisions / ProcessInput / GameFeature_ControlAll / Manage_AI
   call Simulate                        ; 0x4789C5 -> ... -> DisplayInterface_SimulateAll
   call ControlWeapons
   ... if (ScreenMode == SCREENMODE_SIM) Render_Next_Frame(&MainCam)
skip:
call HandleGamePauses(WeAreActive)
```

Two structural facts follow.

**The editor is render-path code, not simulation code.** `Render_Next_Frame` →
`RenderHUD` → `DisplayInterface_RenderAll()` → the per-view display list → `OverView::Render`,
`ControlPanel::Render`, `PathDisplay::Render`. Those functions *are* the editor's input handling:
they read `command_controls`, hit-test `DisplayInterface::mousePos`, and call
`GameObject::SetOrigin`, `GameObject::SetTransform`, the object destructor and
`GameObjectClass::Build`. Nothing about placement lives in `Simulate()`.

**`ScreenMode` is a bitmask and pause is inside the skip mask.** `test byte [0x633A88], 0x3E`
with `SIM=1, MOVIE=2, MENU=4, NOTEPAD=8, MAP=0x10, PAUSE=0x20`. When 1.5 is paused the entire
block — including `Render_Next_Frame` — is skipped, and `HandleGamePauses` draws only the overlay.
**In 1.5 the editor does not run while paused at all.** The reported 1.5 behaviour ("works while
the simulation is running") is therefore the *only* behaviour 1.5 has.

Placement itself, 1.5 `ControlPanel::Render` editor branch (entered on `UserPref_arcadeMode()`):

```c
if (*BUTTON_MAP[i] && (StartGASEvent("mnu_clik.wav",...), reticle.groundPos != NULL)) {
    Terrain_GetHeightAndNormal(groundPos->x, groundPos->z, &h, &n);
    ... front = userObject->obj->transform.front ...
    Build_Orthogonal_Matrix(...);
    pGVar12 = GameObjectClass::Build(class, matrix, buildItem->team, 0, -1, NULL);
    AiMission::GetCurrent()->vtbl[0x18](pGVar12);
}
```

`reticle.groundPos` is a pointer to `overView.where`, published by `OverView::Render` earlier in
the same display list. It is the hand-off between the two display interfaces, and it is the only
non-trivial precondition on placement.

## 4. The proven Redux divergence

`Render_Pause_Message`, Redux `0x00617800`, tail:

```
006179a4  e8b724e2ff   call 0x00439E60      ; &View_Record.MainCam
006179a9  50           push eax
006179aa  e811fcffff   call 0x006175C0      ; Render_Next_Frame
006179af  83c404       add  esp, 4
006179b2  e889ab0600   call 0x00682540
006179b7  8be5         mov  esp, ebp
```

1.5's `Render_Pause_Message` (`0x00477FB2`) has no such call; it ends with
`DrawSprite` → `Device.Refresh.Blit`. The `call 0x6175C0 / call 0x682540` pair in the pause path is
byte-identical to the pair in the normal frame body at `FUN_00618130`, which is what makes the
identification airtight rather than inferential.

This is almost certainly deliberate and not a mistake: Ogre must present every frame, so Redux
reuses the whole render path to draw the paused frame. The side effect is that everything hosted on
the render path — the display-interface layer, i.e. the editor — keeps running while paused.

Supporting Redux frame-loop facts, all instruction-verified at `0x00618270`:

```
if (!WeAreActive || DAT_009183B0) paused = 1;
...
if (paused == 0) NextInputs();                       ; input IS still polled while ScreenMode==PAUSE
if ((WeAreActive || netgame) && (ScreenMode & 0x0E) == 0)  FUN_00618130(paused, 1);
else if (netgame) { FUN_00618130(1, 0); Sleep(0x14); }
else HandleGamePauses(WeAreActive);
```

and inside `FUN_00618130`:

```
if (!arcadeMode) CheckEntityCollisions();
if (param_1 == 0) ProcessInput();
... GameFeature_ControlAll / Manage_AI / Simulate / ControlWeapons / NextGAS ...
if (param_2 && ScreenMode == 1) { Render_Next_Frame(&MainCam); FUN_00682540(); }
```

Note the mask shrank from `0x3E` to `0x0E`. With Redux's `PAUSE == 2` the pause bit is still
inside the mask, so pause still diverts to `HandleGamePauses` — the mask change is not the
mechanism here, but it is a second unexplained delta worth recording.

**Net state while paused in Redux:** `NextInputs` runs (controls are live), `ProcessInput` does
not (no `ProcessGK`), `Simulate` does not (so **`DisplayInterface::SimulateAll` does not**, so
`DisplayInterface::mousePos`, `currentBuffer` and `currentCamera` are frozen), and the full render
path *does* run (so all editor interaction code executes). No 1.5 frame can ever be in that state.

## 5. Placement-path predicates: everything else matches

Checked and found equivalent — these are the hypotheses I can rule out:

| Predicate | Verdict |
|---|---|
| explicit paused/`timeScale` requirement around placement | **Absent.** No `ScreenMode`, `runningSS` or pause read anywhere in `OverView::Render`, `ControlPanel::Render`, `PathDisplay::DrawBuildMenu`, or `GameObjectClass::Build` in either build. |
| `UserPref_arcadeMode` semantics | Identical: `!netgame && (playOption & 1)`. Redux `0x00451DE0`. |
| `TerrainEditMode` early-out in `OverView::Render` | Identical (Redux wraps the body in `if (TerrainEditMode == 0)`). |
| radar-rect early-out | Identical (`hudFlags == 0 && InsideRect(mousePos, mapRadar.viewRect)`). |
| editor select / move / rotate / delete ladder | Identical; `SetOrigin` `0x005873A0` and `SetTransform` `0x0056D6A0` are bare writes + `FUN_004DB100`, no guards. |
| `reticle.groundPos` publish/consume | Same producer (`OverView::Render`, both branches) and same consumer (`ControlPanel::Render`). Never cleared per frame in either build. |
| `GameObjectClass::Build` | No pause/simulation guard added. |
| `PathDisplay` build menu → `Build` | Structurally identical; only the `AiMission` vtable slot moved `+0x18` → `+0x1C`. |
| editor entry state bits | Redux `Apply_Edit_View` (`0x0061BF60`) still sets `Cockpit_Visible=0`, `useDisplayInterface=1`, `Current_View=EDIT_VIEW`, calls `SetControlMode(0)` and `EditTerrain_Enter`. `EditTerrain_Enter` still sets `TerrainEditMode`, `SetEditMode(1)`, `SelectTerrainView(10)` and `playOption |= 1`. |
| input handling moved between update paths | `NextInputs` → `ProcessInput` → `Simulate` → render ordering is preserved; `NextInputs` still clears every discrete control at the top of each call. |

The GK table did shift in Redux (`0x19` became "quit", `0x26/0x27/0x28/0x29` slid up one,
`0x2B` is new, arcade toggle moved `0x2A` → `0x2C`, `GK_TOGGLE_EDITMODE` moved `0x29` → `0x2A`).
That is a renumbering with a matching `gamekey.map`, not a defect, but it means any patch keying on
a GK code must use the Redux numbers.

## 6. Root cause -- proven

### The producer / consumer pair

`ControlPanel::Render` editor branch, **1.5 `0x004C4FC5` / Redux `0x004A185F`**. The sound call sits
inside the `&&` but the build is gated on the pointer:

```c
if (mode_select[i]) {
    StartGASEvent("mnu_clik.wav", ...);          // <- always plays
    if (reticle.groundPos != NULL) {             // <- Redux: NULL, so no build
        Terrain_GetHeightAndNormal(groundPos->x, groundPos->z, ...);
        Build_Orthogonal_Matrix(...);
        GameObjectClass::Build(class, matrix, buildItem->team, 0, -1, NULL);
        AiMission::GetCurrent()->vtbl[+0x18 / Redux +0x1C](obj);
    }
}
```

That is exactly the reported symptom: **keystroke makes a sound, no object appears.**

`reticle.groundPos` absolute addresses: **1.5 `0x00B8B3A8`**, **Redux `0x025CE778`**. Xref scans give
the same shape in both -- two absolute writes, both inside `OverView::Render`, everything else a
read. The Redux writes are at `0x00588275` and `0x0058854E` (`a3 78 e7 5c 02`).

### The per-frame null-out

`Reticle_Simulate` is called from `Simulate()` **only in the arcade branch** -- that is, only in
editor mode -- in both builds (1.5 `0x004D9BE6`; Redux `0x005BA150`, which loads `ecx = 0x025CE6D0`,
the global `reticle`, and tail-calls `Reticle::Simulate` at `0x005BA560`).

`Reticle::Simulate` gates on the current view:

- 1.5: `if (view != COCKPIT && view != BINOCULAR && view != FIX_EXTERN && view != CHASE) { selectObj = NULL; groundPos = NULL; }`
- Redux: `if (view == 0 || view == 2 || view == 1 || view == 7) { ...targeting... } else { this[+0xAC] = 0; this[+0xA8] = 0; }`

`reticle + 0xA8 = 0x025CE6D0 + 0xA8 = 0x025CE778` = `groundPos`; `+0xAC = 0x025CE77C` = `selectObj`.
View 3 (`OVER_VIEW`) is in neither positive set, so **both builds null `reticle.groundPos` on every
simulated frame in overhead view.** This is not the regression -- 1.5 does it too.

### The ordering that saves 1.5 and breaks Redux

`DisplayInterface::AddViewRender` (1.5 `0x004C89A6`) walks the list and inserts before the first
entry whose `priority` is strictly greater -- an ascending sort, lowest priority rendered first.
Redux `DisplayInterface::AddView` = **`0x004B6940`**, forwarding the same pair to
`AddViewSimulate` `0x004B6970` and `AddViewRender` `0x004B6A60`.

Registration constants, read as raw bytes out of both images:

```
1.5  OverView::OverView      0x004D3079 :  push 0     ; priority
                             0x004D3083 :  push 3     ; view
                             0x004D308D :  call AddView            -> AddView(3, 0)

1.5  ControlPanel ctor       0x004C495F :  xor edi,edi ; inc edi   ; priority = 1
                             ... push edi ; push {0,2,edi,7,3}     -> AddView({0,2,1,7,3}, 1)

Redux OverView::OverView     0x0058755E :  6A 01      push 1       ; priority
                             0x00587560 :  6A 03      push 3       ; view
                             0x00587565 :  call 0x4B6940           -> AddView(3, 1)

Redux ControlPanel ctor      0x0049F95C :  6A 00      push 0       ; priority
                             0x0049F95E :  6A 03      push 3       ; view
                             0x0049F963 :  call 0x4B6940           -> AddView(3, 0)
```

Redux `ControlPanel` registers the same five views as 1.5 in the same order -- `{0, 2, 1, 7, 3}` --
so this is the same source line with one constant changed, not a restructure.

Identity is nailed down independently of the priorities: the Redux `OverView` ctor at `0x00587520`
stores vtable `0x00884F34`, whose slot `+0x18` is `0x00587EF0` = `OverView::Render`. Cross-check:
`PathDisplay`'s vtable `0x00885540` holds `0x00594CA0` = `PathDisplay::Render` at the same slot, and
1.5's `DisplayInterface::RenderAll` dispatches through `+0x18`.

### The two frames, side by side

**Overhead + arcade, simulation running:**

| | 1.5 | Redux |
|---|---|---|
| `Simulate` -> `Reticle::Simulate` | `groundPos = NULL` | `groundPos = NULL` |
| render list, entry 1 | `OverView::Render` -- publishes `groundPos = &overView.where` | `ControlPanel::Render` -- **reads NULL**, plays the sound, skips `Build` |
| render list, entry 2 | `ControlPanel::Render` -- reads non-null -> **builds** | `OverView::Render` -- publishes, too late |

**Pause held** (Redux only -- 1.5 skips the frame entirely): `ScreenMode == 2` diverts
`DoNextFrame` to `HandleGamePauses`, so `Simulate` never runs and nothing nulls `groundPos`; but
Redux's `Render_Pause_Message` still calls `Render_Next_Frame` (section 4), so `ControlPanel::Render`
sees the pointer the *previous* running frame's `OverView::Render` published, and **builds**. The
cursor is frozen at that same position because `DisplayInterface::SimulateAll` -- sole writer of
`DisplayInterface::mousePos` -- is also skipped. Exactly the reported workaround, including its
limitation.

## 7. Patch design -- and the one wrinkle

The faithful fix restores 1.5's two constants:

| site | current | patched |
|---|---|---|
| `0x0058755E` (OverView, view 3) | `6A 01` | `6A 00` |
| `0x0049F95C` (ControlPanel, view 3) | `6A 00` | `6A 01` |

Both must change together. Changing only one produces a **tie** (`0 == 0` or `1 == 1`), and
`AddViewRender` appends on ties, so the order would then depend on global-constructor order --
non-deterministic, and not what 1.5 does. Guards should cover the whole
`push imm8 ; push 3 ; mov ecx,[ebp-0x10] ; call rel32` sequence (12 bytes each, including the `call`
displacement to `AddView`), not the immediate alone, so a moved build fails closed.

**The wrinkle: these are global-constructor sites.** `OverView::OverView` is reached only from
`0x00409C90` -- `mov ecx, 0x009C9170 ; call 0x00587520 ; push <dtor> ; call atexit` -- a textbook
MSVC dynamic initializer. `ControlPanel` has the same shape via `0x004054E8`. Those run from
`_initterm` during CRT startup, **before `main`**. OpenShim's `RunPatcher` runs after
`WaitForSignature` on a worker thread, long after. Patched there, the write lands after the lists
are already built and does nothing.

Two ways out. This is the decision I want confirmed before writing code:

- **(A) Early apply.** Write these two patches synchronously from `DllMain`. The Windows loader runs
  `DllMain` for statically-imported DLLs before the EXE entry point, and global ctors run from that
  entry point, so the ordering is guaranteed by the loader rather than being a race. Cost: it
  bypasses the normal version-check / config-load / MP-gating flow, because none of that has
  happened yet. The 12-byte guard would be the entire verification, and the feature could not be
  INI-gated at the point of application without a bespoke early config read. Partial precedent
  exists -- `ApplyD3DStartupHooks` and `ApplyTrnSaveNormalizeHooks` already run before the version
  check.
- **(B) Consumer-side redirect.** Leave the lists alone; hook `ControlPanel::Render`'s
  `reticle.groundPos` test so that, **only** when `View_Record.Current_View == 3` and
  `UserPref_arcadeMode()`, a null `groundPos` falls back to `&overView.where` (`0x009C9194`). Fits
  OpenShim's normal patch flow and gating exactly, is INI-gateable and SP-gateable, and costs one
  frame of cursor lag in the editor -- the same lag the Pause workaround already has, and invisible
  in practice.

I lean **(B)**: same observable result, no startup-order special case, default-off and
single-player-gated like every other OpenShim gameplay feature. (A) is the more "correct" fix in the
abstract, but it forces a permanent exception to the loader safety flow for what is a two-byte
constant swap.

There is no `RemoveView` entry point in either build -- only `~DisplayInterface` unregisters -- so
"re-register at runtime with the right priority" is not available as a third option.

**Regression surface.** Under (B) the only behaviour change is inside a branch that already requires
`TerrainEdit`, arcade mode, overhead view and a build-menu keypress. Under (A) the render *and
simulate* order of `ControlPanel` vs `OverView` changes for view 3 in every session including
multiplayer. That is a return to stock 1.5 ordering rather than novel behaviour, but
`ControlPanel::Render` issues `BroadcastCommand`, so it moves when a command is emitted within the
frame -- which argues for (B), or for (A) plus a hard MP gate that (A)'s timing makes awkward.

## 8. Validation

With `/edit`, overhead view (Shift+F10), arcade mode on (Ctrl+A):

1. build-menu key with the simulation running -> object appears at the cursor (the bug)
2. same while paused -> still works (the workaround must not regress)
3. cursor moves freely while running; placement tracks it
4. repeated placement without re-pausing
5. move / rotate / delete of an existing object -- unchanged (all in `OverView::Render`, untouched)
6. leave arcade mode -> number keys drive the normal build menu, not editor placement
7. leave overhead view -> cockpit reticle targeting still works (`Reticle::Simulate` positive branch)
8. non-editor session: number keys, unit commanding and selection boxes unaffected
9. `TerrainEdit` off entirely -> no behaviour change at all
10. multiplayer -> no change (feature must be SP-gated)

## 9. Second-session editor corruption -- what this turned up

Not chased, and on current evidence **not** the same defect. Two observations worth keeping:

- `EditTerrain_Enter` (Redux `0x004C82D0`) calls `EditTerrain::CreateWorldMap` on **every** entry
  against the file-scope `editTerrain` object, which outlives the mission. An empty minimap on the
  second mission is consistent with that reusing state bound to the first mission's terrain.
- Neither `EditTerrain_Enter` nor `EditTerrain_Exit` releases the world-map allocation, in either
  build. So if this is the crash, it is Redux's mission-teardown lifetime rather than a code
  difference in `EditTerrain` -- consistent with the known "process lifetime is not mission lifetime"
  pattern.

The placement path never touches `editTerrain`, so fixing this bug will not affect that one.

## 10. Confidence

| Claim | Confidence |
|---|---|
| Shift+F10 = `OVER_VIEW`; editor object ops gated on the arcade bit | **High** -- shipped `gamekey.map` plus both decompiles |
| Sound plays outside the `groundPos` guard | **High** -- same structure in both builds; matches the reported symptom exactly |
| `Reticle::Simulate` nulls `groundPos` in view 3, in both builds | **High** -- `reticle = 0x025CE6D0`, `+0xA8 = 0x025CE778` confirmed by address arithmetic and by the 1.5 typed decompile |
| `AddView` priorities are transposed for view 3 | **Very high** -- read as raw `push imm8` bytes from both images; `AddView` identified by 57 call sites and by `OverView`'s vtable |
| `AddViewRender` sorts ascending | **High** -- 1.5 typed decompile; Redux `AddView` forwards the same pair |
| The ctors are global dynamic initializers | **High** -- `mov ecx, imm32` + `atexit(dtor)` shape, single caller each |
| Redux pause path renders a full frame | **Very high** -- byte-level `call 0x6175C0 / call 0x682540` |
| Offsets in section 2 | **Medium-high** -- statically derived, none runtime-validated |
| Steam build shares these VAs | **Assumed**, per existing OpenShim convention; not verified |
