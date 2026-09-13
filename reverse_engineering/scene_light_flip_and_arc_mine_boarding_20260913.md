# Scene light flip on boarding, and the Arc Mine boarding discharge (2026-09-13)

Source evidence: a 15.83 s ShadowPlay capture of `play01.bzn` (playground, no
mission script, so engine plus shim only), 3840x2160 at 120 fps, 1900 frames.
Frame numbers below are that capture's.

Two separate defects are in the clip. One is ours, one is stock. Neither is
patched yet; this file records what is proven, what is disproved, and the one
measurement each still needs.

---

## Timeline (both defects)

Player state is read from the weapon panel: the craft loadout (AT-Stabber /
Mini Gun / Arc Mine / MDM Mortar) versus the pilot loadout (Plasma Rifle /
Sniper Rifle). The transition frames are exact.

| frame | t | player | terrain luma | headlight cone | mine |
|---|---|---|---:|---|---|
| 0 | 0.000 | in craft | 70.0 | on | |
| 86 | 0.717 | exit -> pilot | 70.0 | on | |
| 98 | 0.817 | pilot | 70.0 | off | |
| **689** | **5.742** | **board craft** | 70.0 | off | **gmbolt discharge** |
| **708** | **5.900** | in craft | **39.3** | **on** | |
| 990 | 8.250 | exit -> pilot | 39.3 | on | |
| 1000 | 8.333 | pilot | 39.3 | off | |
| 1513 | 12.609 | pilot | 70.0 | off | |
| **1565** | **13.042** | **board craft** | 70.0 | off | **gmbolt discharge** |
| **1585** | **13.208** | in craft | **39.3** | **on** | |

---

## Defect 1 (ours): the scene light level steps 2.4x with the craft headlight

### What is measured

Terrain luma is the mean of a fixed 800x400 patch at (2600,1500) in the 4K
frame, away from the headlight cone. It has exactly two values, 70.0 and 39.3,
and every transition is a single-frame step.

Frames 707 and 708 are consecutive, same camera, player in the craft in both:
one frame apart the scene drops 2.4x and the cone appears. Same at 1584/1585.

### It is a scene light level, not a post-process

- **Sky-dome stars are bit-identical across the step** (individual star pixels
  105 -> 105; region max 125.67 -> 125.67 in both). Unlit geometry is untouched,
  so nothing is happening to the framebuffer.
- Relative contrast (sigma/mu 0.194 -> 0.221) and hue (B/R 1.360 -> 1.329) are
  preserved: an intensity scale, not a light being removed or added with a
  different colour.
- Pure black stays black (input 0-5 maps to output mean 1.06), so nothing
  additive is involved.
- The HUD does not change, so it happens before HUD compositing.

### The shim's headlight is enormous

Live `[HEADLIGHT-PROBE]` from an instrumented run, shipped preset
(`Headlights = 1`, `HeadlightColor = White`, `HeadlightBeam = Wide`,
`HeadlightFalloffRepair` defaulting on):

```text
type=2 diffuse=(4.000,4.000,4.000) specular=(4.000,4.000,4.000) power=1.000
range=2239.8 attenuation=(c=1.0000 l=0.00700 q=0.000200)
inner=63.03deg outer=85.94deg falloff=2.000 visible=yes castShadows=no
```

against stock (`include/headlight_falloff.h`, confirmed by the same probe):

```text
diffuse=(1,1,1) range=600 attenuation=(1, 0.007, 0.0002)
inner=10deg outer=20deg falloff=1.0
```

So the shipped preset turns a 20-degree, 600 m, intensity-1.0 spot into an
**86-degree, 2239.8 m, intensity-4.0** one. `HeadlightBeam = Wide` supplies the
cone (inner 1.1 rad, outer 1.5 rad, colour x0.8) and
`HeadlightFalloff::SolveInvisibleRange` supplies the range: it solves for the
distance at which the curve falls below one 8-bit step so the range clamp stops
being a visible terminator.

`headlight_falloff.h` names the hazard this creates, in its own comment on
`kMaxRange`:

> Never shrink below stock, and never let the solved radius run away: past a few
> kilometres the light is in every renderable's candidate list for no visible gain.

The cap chosen was 3600 m. 2239.8 m is already far inside "in every renderable's
candidate list".

### What is ruled out

- **Not a post-process, colourspace or gamma flip.** Stars are bit-identical;
  the working tree's `dx11_colorspace_diagnostic.cpp` edits are debug-name
  classification only and change no transform.
- **Not `EnhancedLightSelectionV2`.** `BudgetForEnhancedScheme` returns 0 for
  every non-`en-` scheme, and the install runs the stock-compatible Redux
  profile, so that hook is inert.
- **Not the shim mistaking the sun for a headlight.** `RefreshHeadlightState`
  reaches a light only through a GameObject's render bridge at +0xA8; it cannot
  address the scene's directional light.
- **Not the pilot flashlight.** It does not exist in the captured session (no
  `[PILOTLIGHT] created` line in a log from the same install and config), and
  the transitions that matter are the craft light's.

### What is NOT yet established

**Why a bigger light makes the rest of the scene darker.** Adding light should
add light; within 150 m this headlight delivers order-1.0 illumination across an
86-degree cone. The remaining candidate is light-list displacement -- a 2.2 km
range puts the spot in every renderable's candidate list, and whatever Redux's
terrain pass does with a full list then costs the surfaces the spot does not
actually illuminate. That is a hypothesis, not a finding.

**The measurement that would settle it** is `run_lcplight.ps1 -Scenario headlight`,
which holds everything else constant and varies only `HeadlightFalloffRepair`
(2239.8 m vs stock 600 m) and `Headlights` (policy off entirely), reporting the
largest within-run luma step across the boarding transition in each arm. If the
step survives at 600 m, the range is not the mechanism and the beam width or the
intensity is. **This run has not been made: the game install is a single shared
resource and another agent's session has been running it continuously.**

Do not patch `kMaxRange` on the strength of the hypothesis alone. The range
inflation exists to remove a visible cone terminator, and trading a real fix for
a guessed one is how the first WeaponMine guard happened (see below).

---

## Defect 2 (stock): the Arc Mine discharges at the boarding point

### What is measured

A single-frame white-pixel spike in the scene region, baseline 94 px:

- frame **689** (t=5.742): 1275 px
- frame **1565** (t=13.042): 1368 px

Both are the exact frames the weapon panel switches to the craft loadout, i.e.
the frames the player boards. Neither *exit* produces one. The second is fully
visible: a vertical arc bolt near the mine field and a white impact star with a
pink halo on the ground at the boarding point, frames 1566-1584 (~0.16 s).

The craft takes no damage: the hull bar is flat across the whole capture (all
apparent variation tracks the light step changing the background behind it).

The mine field is four green dots and **one red**, persistent for the whole
capture, with the player's reticle on one of them.

### The object

`boltmine.odf` -- `classLabel = "weaponmine"`, `unitName = "Arc Mine"`,
`weaponName = "gmbolt"`, `searchRadius = 100.0`, `heightScale = 2.0`,
`maxAmmo = 100`, `lifeSpan = 1e30`. That is what the player's own slot-3
"Arc Mine" lays, and `gmbolt` is the vertical lightning the capture shows.
The ODF fields map onto the decompiled reads: `+0x168` searchRadius (compared
squared), `+0x16c` heightScale (the z weight in the distance term), `+0x174`
the terrain-LOS flag.

### The predicate, read end to end

1.5 `WeaponMine::Simulate` `0x0053F9CF` (named PDB decompilation) and Redux
`0x00612950` are semantically identical:

```text
if IsRemote(this): return
if not weapon->vtbl[1]():  this->+0x238 = 0        # weapon not ready
else:
    best = null; bestDist2 = searchRadius^2
    for craft in Craft::craftList:
        if GameObject::FriendP(this, craft):  continue
        d2 = |craft->vtbl[0xc]() - minePos|^2 with heightScale on z
        if d2 < bestDist2:
            aim = weapon->vtbl[0x2c](craft)
            if losFlag and Terrain_GetIntersection(minePos, aim): continue
            bestDist2 = d2; bestAim = aim; best = craft
    GameObject::SetTarget(this, best)
    if best:
        ...write the aim matrix into weapon->obj->transform...
        if not losFlag or not MayHitFriends(this, bestDist2, 0.3, 1.0):
            weapon->vtbl[8]()                        # FIRE
Mine::Simulate(this, dt)
```

and the hostility test bottoms out at:

```text
GameObject::FriendP(GameObject* o)  ->  o->vtbl[1]()  == ACTUAL team
GameObject::FriendP(int n)          ->  teamList and n >= 0 and Team::FriendP(teamList, n)
Team::FriendP(int n)                ->  n >= 1 and (dwAllies & (1 << n))
```

Two facts follow directly, and both are load-bearing:

1. **`Team::FriendP` rejects team 0 outright** (`n < 1` returns false). Any
   object whose actual team reads 0 is a valid target for every weapon mine,
   including its own side's.
2. **`Person` is a `Craft` subclass** -- `Craft::BuildPilot` is declared
   `Craft * BuildPilot(Craft *this, GameObjectClass *)` and returns the object
   it builds. So pilots on foot are in `Craft::craftList` and are themselves
   candidate mine targets.

### Relationship to the 2026-08-17 report

`weaponmine_hop_friendly_fire_root_cause_20260817.md` proved the **hop-out**
direction: `Craft::AbandonPilot` writes `SetPerceivedTeam(craft, 0)` and nothing
else, WeaponMine reads actual team not perceived team, so hopping out does not
change the mine relation. That stands, and the guard removed then was correctly
removed.

This is the **boarding** direction, which that report did not examine. Nothing
in it is contradicted.

### What is NOT yet established

Which object reads team 0 during the boarding transition -- the pilot being
destroyed, or the craft being taken over -- and whether the red mine in the
field is a team-0 mine that is hostile to everything by construction.

`reverse_engineering/test_missions/lcbench_wmine/rmwmine.lua` +
`run_lcwmine.ps1` answer exactly that: they lay a friendly (team 1) and a
team-0 Arc Mine inside `searchRadius`, hop out, board again through
`exu.SetAsUser`, and log every team per tick together with each mine's ammo.
`maxAmmo = 100` and the discharge is a weapon shot, so a drop in `GetAmmo`
names which mine fired on which tick -- a number, not a sprite in a screenshot.
**This run has not been made, for the same shared-install reason.**

No patch should be written before it is. The previous WeaponMine patch in this
repository was premised on a mechanism that turned out to be wrong, shipped, and
had to be removed.

---

## Provenance

- Capture: `Battlezone 98 Redux 2026.09.13 - 08.51.44.01.mp4`, h264 3840x2160,
  120 fps, 15.833 s, 1900 frames.
- Game: GOG Redux 2.2.301, `battlezone98redux.exe`.
- Shim under test: installed `winmm.dll` SHA-256
  `55C4D20FF0D597602BFA988D0840C0CFA39E48DED90A05E59763EB55B9FA9BAB`
  (not the repo's `bin/Release` build).
- 1.5 reference: `reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/functions`,
  named from the shipped `bzint.pdb`.
- Redux decompilation: `repo_corpora/bzr_gog_best_effort` (31,948 functions).
