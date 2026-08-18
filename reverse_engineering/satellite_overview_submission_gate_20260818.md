# Satellite overview submission gate: located, not yet implementable (2026-08-18)

Status: **analysis complete, patch NOT applied.** The submission path is
identified and the regression is structurally proven, but the last link needed
for a safe patch is not yet derived. Reasons and the exact remaining step are in
§5.

## 1. The corrected SATVIS capture confirms the split

From `logs/openshim.log`, view=3, 54 objects, 6 rejected by the new arena filter:

```
user   obj=0x02A0D720 team=1 illumRaw=0x3F800000 illumFlt=1  detected=1 legacyVisible=1
hidden obj=0x02A03720 team=2 illumRaw=0x00000000 illumFlt=0  detected=0 legacyVisible=0
hidden obj=0x02A0BF20 team=2 illumRaw=0x00000000 illumFlt=0  detected=0 legacyVisible=0
```

`illumRaw=0x3F800000` is exactly `1.0f`, so the field is confirmed float at the
corrected `+0xE8` and the producer is working. Enemy mobiles sit at
`illumination=0 / detected=0 / legacyVisible=0` and still render in satellite.
The defect is therefore purely on the **consumer** side, as reported.

## 2. The legacy predicate, exactly

`GameObject_IsVisibleToUser` (1.5 `0x00496888`), disassembled:

```
gameObj = obj76 ? obj76->[+0xB4] : NULL      ; _OBJ76::gameObj
if (!gameObj) return 0
fldz ; fcomp [gameObj+0xDC]                  ; illumination
return (0.0 < illumination) ? 1 : 0          ; STRICTLY greater
```

`+0xDC` is 1.5's illumination — which independently corroborates the Redux
value, since Redux is the 1.5 layout shifted by +0xC (`0xDC + 0xC = 0xE8`).

It has exactly **one** caller in the whole 1.5 image:
`Submit_Overview_Entities+0x41` (`0x004EA846`). It is an overview-only gate and
is applied at submission, before any transform or culling work.

## 3. 1.5 uses a separate submitter for the overview

`Render_Hardware_Next_Frame` (`0x004783FF`):

```c
if (view != TWO_D_VIEW) {
    if (view != OVER_VIEW && view != EDIT_VIEW && !TerrainExposeMode) Draw_Sky(...);
    if (view != TWO_D_VIEW && (Submit_Terrain_Mesh(cam), view != TWO_D_VIEW) && view != EDIT_VIEW) {
        if (view == OVER_VIEW) Submit_Overview_Entities(cam);   // gated
        else                   ...Submit_All_Entities...        // ungated
    }
}
```

The submitter family, all sharing a `Get_Visible_Lights(cam)` prologue
(`0x004F8B1E`): `Submit_All_Entities` (`0x004EB693`), `Submit_Overview_Entities`
(`0x004EA805`), `Submit_Rear_View_Entities`, `Submit_Single_Entity`,
`Render_Entity_Cockpit`. Only the overview member carries the illumination gate.

## 4. Redux collapsed the branch — this is the regression

Redux frame body `FUN_006176A0` (reached via `FUN_006175C0`,
`Render_Next_Frame`) is the same shape, view id in `DAT_008EAAD8`:

| 1.5 | Redux |
| --- | --- |
| `BlitFill` when OVER/EDIT/expose | `FUN_0067CB10(0,0,0)` when view==3 \|\| 9 \|\| 10 \|\| `DAT_009454BC` |
| `Draw_Sky` unless OVER/EDIT/expose | `FUN_00616500` unless view==3 \|\| 9 \|\| 10 \|\| `DAT_009454BC` |
| `Submit_Terrain_Mesh(cam)` | `FUN_00780C70(cam)` |
| `if (view==OVER) Submit_Overview_Entities else Submit_All_Entities` | `if (view != 9 && view != 10) { FUN_00584D30(cam); FUN_0062EAB0(cam); FUN_004D4610(cam); }` |

**Redux has no overview-specific submitter.** Its submission block excludes only
views 9 and 10; view 3 falls through to the same ungated path used by first
person. That is precisely where the 1.5 gate went, and it explains the capture
in §1 with no other mechanism required.

`FUN_004D4610` is the entity submitter and matches the 1.5 shape:

```
FUN_004D4610(camera):
    FUN_0046E7F0(camera)              ; Get_Visible_Lights analogue (iterates a
                                      ; container at 0x0094E2C4 with the camera)
    for obj in container [0x00917A68]:
        if ((obj[0x25] >> 2) & 1)
            obj->vtbl[8](camera)      ; slot +0x20 = submit
```

## 5. Why no patch was applied

The objects in `[0x00917A68]` are **not GameObjects**. All 17 references to that
container live in one module (`0x004D41xx`–`0x004D4Bxx`), and the siblings show
a renderer-side registry:

* `+0x1C` sort key — `FUN_004D4150` is the comparator (`b->[0x1C] < a->[0x1C]`)
* `+0x24` low byte, a pass/layer id
* `+0x25` flag bits — bit 2 selects the `FUN_004D4610` pass, bit 3 selects the
  `FUN_004D46B0` pass (which dispatches vtable slot 9, `+0x24`)
* virtual submit methods at `+0x20` and `+0x24`

The GameObject arena is a separate 0x400-stride region (the shim's own
`CollectLiveGameObjectsFromArena`, and the `0x02A0xxxx` pointers in §1 confirm
the stride). 1.5 could reach illumination because its loop object was a
`tagENTITY` holding `obj76`, and `_OBJ76::gameObj` sits at `+0xB4`. Redux's
registry object is a different, vtable-bearing type whose back-reference to the
owning GameObject **has not been derived**.

Applying the gate requires that back-reference. Guessing it would mean reading
an unverified offset inside the render loop — the same failure mode that
produced both defects repaired earlier in this session (the WeaponMine guard
built on a misread vtable slot, and the SATVIS field block shifted by 0xC). A
wrong offset here does not fail loudly; it silently hides or shows the wrong
objects every frame.

## 6. The remaining step

Identify the render-registry class and its GameObject back-pointer. Cheapest
route, in order:

1. Find the registration site — the constructor that inserts into
   `[0x00917A68]`. All 17 xrefs found are iteration sites, so registration is in
   the class constructor; locate it via the vtables whose slot 8 (`+0x20`) points
   into the submit family, then read the ctor's stored parameters.
2. Confirm the back-pointer by cross-checking one object against the arena: the
   candidate field must land on a 0x400-aligned pointer inside the arena range.
3. Only then gate: `view == 3 && !(gameObj->[+0xE8] > 0)` → skip, leaving the
   stock flag test intact for every other view.

That preserves the §2 semantics exactly (strict `>`, applied at submission,
overview only), touches no producer, no radar/`seen`/`isVisible`/team state, and
no Ogre entity ownership — and leaves first person on the stock path because the
added term is conditioned on view 3.

## 7. Confidence

| Claim | Confidence |
| --- | --- |
| 1.5 gate is `illumination > 0`, overview-only, at submission | **Very high** — disassembled; single caller |
| Redux has no overview-specific submitter and view 3 uses the ungated path | **High** — frame body read in full; branch excludes only views 9/10 |
| `FUN_004D4610` is the entity submitter | **High** — Get_Visible_Lights prologue + per-object virtual submit |
| `[0x00917A68]` holds renderer-registry objects, not GameObjects | **High** — comparator, pass id, flag bits, two dispatch slots |
| Back-pointer to GameObject | **Not established** — the blocker |
