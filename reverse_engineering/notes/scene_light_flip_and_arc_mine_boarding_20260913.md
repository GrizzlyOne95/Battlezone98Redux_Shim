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

### The A/B was run and produced NO MEASUREMENT

`run_lcplight.ps1 -Scenario headlight` was run on 2026-09-13 across three arms.
Both instrumented arms engaged, verified from their own probe lines:

| arm | `[HEADLIGHT-PROBE]` |
|---|---|
| repair | `range=2239.8 falloff=2.000 edgeIntensityAtRange=0.00392 (below 8-bit floor)` |
| stock | `range=600.0 falloff=0.350 edgeIntensityAtRange=0.05181 (VISIBLE STEP AT RANGE)` |

and the analysis found zero light steps in either. **That is not a null result.**
The frames are bit-identical for long stretches — `styling_002` through
`styling_024` all at exactly 60.94, every `board_*` frame at exactly 35.31,
frame-to-frame geometry difference 0.000 — while BZLogger kept growing at the
per-tick rate. `PrintWindow` against the windowed DXGI swapchain hands back the
**last presented surface**, and behind another window that surface stops
changing. The burst photographed a stale buffer, so a single-frame step inside
it was never sampled.

`analyze_lcplight_burst.py` now warns when consecutive frames are bit-identical,
and `run_lcplight.ps1` carries the limitation next to `Save-WindowFrame`.

Two further things the runs did establish:

- the `stock` arm is **not stock**. With `HeadlightFalloffRepair = 0` the shim
  still writes the Wide 63/86-degree cone, diffuse 4.0, and `falloff = 0.35`
  (`kHeadlightPreRepairSpotFalloff`), which `headlight_falloff.h` itself
  describes as "a step, not a gradient". Only `Headlights = 0` is stock, and
  that arm captured no frames at all;
- every transition in the capture lands within one `kHeadlightRefreshMs = 200`
  tick of the shim applying its headlight state (boarding 158 ms and 167 ms;
  hop-out 100 ms and 83 ms). The scene steps when the shim styles a headlight,
  not when the craft is entered.

### Operator A/B: it is ours (2026-09-13)

`[SinglePlayer] Headlights = 0` on `play01.bzn`, run by hand:

> No headlights, it doesn't break anything.

So the flip is caused by the shim's headlight policy, not by stock Redux. With
`Headlights = 0` the policy sets the player's headlight **invisible**
(`g_HeadlightPlayerVisibleConfigured` true, `g_HeadlightPlayerVisible` false),
so there is no shim-styled headlight in the scene and no step.

That confirms ownership but does not yet isolate *which* property. Four
candidates remain, and they are separable with three more manual runs:

| `Headlights` | `HeadlightColor` | `HeadlightBeam` | `HeadlightFalloffRepair` | isolates |
|---|---|---|---|---|
| 1 | Stock | Stock | 0 | the light existing at all, engine-stock 10/20 deg, diffuse 1.0, range 600 |
| 1 | White | Stock | 0 | the x4 intensity alone |
| 1 | Stock | Wide | 0 | the 63/86 degree cone alone |
| 1 | Stock | Stock | 1 | the solved 2239.8 m range alone |

With `HeadlightColor = Stock` and `HeadlightBrightness = 1.00`, `setPlayerColour`
is false; with `HeadlightBeam = Stock`, `setPlayerBeam` is false. Row one
therefore applies visibility only and leaves the engine's own light untouched,
which makes it the row that matters: if the flip returns there, no shim property
is responsible and the mechanism is that a visible headlight exists at all.

The operator also reports the capture was taken in **SHIFT+F4 (`TRACK_VIEW`)**,
not cockpit view. Whether the active view changes the result is untested and
should be held fixed across the table above rather than assumed irrelevant.

Screen capture cannot run this table -- see the frozen-burst limitation above --
so it is either operator-run or it needs the shim instrumented to log the scene
light state each refresh.

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

### Which side of the predicate is broken

The mine in the capture was **team 1, the same team as the player** (reported by
the operator). For a team-1 mine to target a team-1 object, `FriendP` has to
come back false, and the only route to that is the **target's** team reading
something team 1 is not allied with. `Team::FriendP` rejects `n < 1` outright,
so a team that reads **0** for even one tick is hostile to its own side's mines.
That is what "the weapon mine neutral bug" names: the thing being boarded, or
the pilot being destroyed, goes neutral, not the mine.

So the mine's own team is not the defect and no mine-side guard is warranted.

### The fixture ran and did not reproduce

`run_lcwmine.ps1`, 2026-09-13. Everything spawned and the transition happened:

```text
T+2.00  SPAWN_AICRAFT    odf=avtank   askedTeam=1 actualTeam=1 dist=40.0
T+5.00  SPAWN_MINE_TEAM1 odf=boltmine askedTeam=1 actualTeam=1 dist=26.0
T+5.00  SPAWN_MINE_TEAM0 odf=boltmine askedTeam=0 actualTeam=0 dist=32.0
T+9.00  AI_HOP_OUT ok=true craftTeam=1
T+9.00  AI_PILOT_SEEN team=1
T+14.00 BOARD_DETECTED the AI pilot object is gone -- it boarded
```

The AI pilot boarded on its own about a second after the hop-out, so no
`GetIn` order was even needed. Across 15,563 logged ticks:

- **zero ammo drops** on either mine;
- **zero ticks** where the pilot's or the craft's team read 0;
- the pilot read team 1 for all 303 ticks it existed.

Two readings, and the second is more likely:

1. the defect needs the player's own `userObject` swap, which an AI boarding
   does not perform; or
2. **the ammo witness is blind.** The team-0 mine also never fired, and by the
   predicate a team-0 mine should be hostile to everything and fire without any
   transition at all. A control that fails to fire indicts the instrument
   before it indicts the theory. `GetAmmo` reported 1 on a freshly built mine
   whose ODF says `maxAmmo = 100`, so it is returning something other than the
   shot count the weapon consumes.

A Lua-visible team is also not the same thing as the team the predicate reads:
`FriendP` resolves through `o->vtbl[1]()`, and if a class overrides that slot
the Lua accessor and the engine can disagree for exactly the tick that matters.

### Operator repro (2026-09-13)

> Team 1 Arc Mine near your tank. Hop out, re-enter the tank. The mine will
> fire briefly.

So it is the **player's** boarding, not an AI pilot's, and the mine is on the
player's own team. The AI fixture above exercised the wrong actor.

### The line that resets the team on boarding

Boarding runs `GameObject::SetAsUser` on the craft (1.5 `0x00495468`):

```c
pAVar1 = this->aiProcess;
if (pAVar1) { destroy(pAVar1); this->aiProcess = 0; }
(**(code **)(this->_padding_ + 8))();             // detach from current team
pGVar2 = userObject;
Set_User_Entity(this->ent);
userObject = this;
if (pGVar2) { (**(code **)(pGVar2->_padding_ + 0x10))(); }   // SetAsNotUser(old user)
(**(code **)(this->_padding_ + 4))(userTeamNumber);          // attach craft to userTeamNumber
UserProcess::UserProcess(...);
```

The old user object is **your pilot**, and `GameObject::SetAsNotUser`
(`0x004954D7`) ends with:

```c
(**(code **)(this->_padding_ + 4))(*(ushort *)((int)&this->obj->flags + 2) & 0xf);
```

which is `SetTeam( (obj->flags >> 16) & 0xF )` -- the pilot's team is **reset
from a 4-bit field packed in the low-level object's flags**, the same field
`get_obj_team` (`0x00482BD4`) reads and that `Craft::Init` / `Person::Init` use
to seed a BZN-loaded object's team.

The slot pairing is confirmed by `GameObject::SetTeam` (`0x004952FA`), which is
exactly `[slot +8, no args]` then `[slot +4, team]` -- so +8 detaches from the
current team list and +4 attaches to team n.

`GameObjectClass::Build` (`0x00498D9C`) is where that nibble is written:

```c
(local_a8.entObj)->flags = param_2 << 0x10;      // param_2 is the team
if (param_3 != 0) { flags |= 0x10; }             // 0x10 marks the user object
```

and the constructor seeds the user globals from the same nibble, gated on that
flag:

```c
if ((this->obj->flags & 0x10) != 0) {
    userTeamNumber = (obj->flags >> 16) & 0xf;
    userObject = this;
    userTeamList = Team::GetTeam(userTeamNumber);
}
```

`Craft::BuildPilot` builds the pilot with `param_3 = 0`, so a runtime-built
pilot is correctly *not* flagged as the user object -- `SetAsUser` is called on
it separately, and that call sets its live team to `userTeamNumber`.

**Hypothesis, sharp enough to test:** the pilot's live team comes from
`userTeamNumber` while you control it, but boarding restores it from the packed
nibble. For a pilot built at runtime those two can disagree, and `Team::FriendP`
rejects team 0 outright, so a pilot whose nibble reads 0 is hostile to its own
side's mines for as long as the Person survives -- which is exactly where the
bolt lands.

This is not yet proven. The decompilation cannot settle what `BuildPilot`
actually passes as `param_2`: Ghidra collapses several distinct `Craft` members
into one `_padding_` in that function, and `GameObject::GetTeam` decompiles to
a nonsense field read, so the live team's storage is unresolved in this corpus.

### The check was run only half way: the pilot never boarded

`[SinglePlayer] PilotTeamRestore` was implemented as that probe (see
`src/patches/bzr_hooks.cpp`, "Pilot team restore on boarding"). On lcbench with
a scripted `HopOut`:

```text
[PILOTTEAM] Layout verified on a craft: packed=1 live=1 (obj=0x25BF95A8 flags=0x00010010)
[PILOTTEAM] Pilot on foot player=0x02A0D320 packed=1 live=1 verified=yes (agree -- nothing to repair)
```

sampled 15 ms after `[PLIGHT] T+8.00 HOP_OUT attempt=1 ok=true`, i.e. on the
real freshly built pilot.

The self-check passing proves both field offsets on this image: `flags` reads
`0x00010010`, which is the team nibble at bits 16-19 holding 1 plus `0x10`
marking the user object -- exactly what `GameObjectClass::Build` writes.

**THE LIMIT, and it matters: the pilot never boarded in that run.** The
fixture's boarding leg logged `BOARD ok=false via=no-exu` twenty times and every
heartbeat through T+55 still read `onFoot=true`. The sample above is the pilot
standing around *before* boarding, and the probe only logs on the on-foot
branch, which stops the instant boarding completes. The transition this bug
lives on was never observed.

What is ruled out is therefore narrow: the **"pilot's packed nibble reads 0"**
variant, at the endpoint, supported by that sample plus the static argument that
nothing in `SetAsUser` touches the person's nibble before `SetAsNotUser` reads
it (destroy craft aiProcess -> craft `vtbl+8` detach -> `Set_User_Entity` ->
`userObject = craft`). On that reading `SetAsNotUser` would restore team 1.

Anything that goes wrong *during* the transition -- the live team, a null
`teamList`, or the craft rather than the pilot -- this probe cannot see.

The feature is kept, OFF, as the instrument rather than as a fix. Its
`[PILOTTEAM]` lines report both teams for every pilot and say `DISAGREE` if some
other route ever produces the disagreement it was built for.

### What is still open

* **The boarding transition itself, which is the whole event.** Two ways to
  reach it. (a) Make the probe keep sampling the previous pilot object for a few
  frames after it stops being the user object, so a team that flips to 0 inside
  `SetAsNotUser` is caught while the `Person` is still alive -- a small change to
  the existing feature and it needs no input injection. (b) Drive the boarding
  for real: `input.map` has no enter-vehicle action, so the pilot boards by
  walking into the craft, which means throttle-forward via `SendInput` using the
  scan-code harness already proven in `run_lcwalk_drive.ps1`. (a) is cheaper and
  strictly more informative; (b) is what reproduces the operator's own route.
* The mine's target may not be the pilot at all. `GameObject::SetAsUser` detaches
  the craft from its team list (`vtbl+8`) near the start and only re-attaches it
  to `userTeamNumber` (`vtbl+4`) at the end, so the **craft** is teamless across
  the middle of that call. Whether a simulation tick can observe that window is
  not established and cannot be, from a decompilation alone.
* `GameObject::FriendP(int)` also requires a non-null `teamList`; a detached
  object failing that test reaches the same "not a friend" answer without its
  team ever reading 0.

Any of those needs a hook on `WeaponMine::Simulate` itself, logging the chosen
target, its class, and both team readings at the fire call. That is the next
instrument, and it answers the question regardless of which object is at fault.

### The original runtime check, for the record

Log, for the player's pilot across the boarding frame:

* `get_obj_team(person)` -- the packed nibble at `obj->flags + 2` masked 0xF;
* the live team the predicate actually reads, i.e. `person->vtbl[1]()`.

If they disagree at the boarding frame, the patch site is
`GameObject::SetAsNotUser`'s team restore and the fix is to leave a live team
alone rather than re-derive it from the nibble. A Lua `GetTeamNum` probe cannot
do this: `FriendP` resolves through the vtable and a class override would make
the two disagree for exactly the tick in question.

No patch until that check exists. The previous WeaponMine patch in this
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
