# Battlezone 98 Redux Lua — Agent Reference

This is the agent-oriented reference for the **stock Battlezone 98 Redux LuaMission API** used by Campaign Reimagined.

Its purpose is not to reproduce the HTML site page-for-page. It is to give coding and review agents the information they actually need to produce correct BZR Lua: signatures, overloads, lifecycle rules, multiplayer locality, stock engine bugs, version differences, and project-validated quirks.

The original HTML reference remains valuable and should be consulted for examples and individual function pages. This file is the compact operational reference.

---

# Evidence hierarchy

When sources disagree, use this order:

1. **Current BZR runtime-validated project findings** in `Text/ScriptingGuide.txt`, dedicated tests, or reproducible mission behavior.
2. **`References/StockLuaAPI-Functions/` and `References/StockLuaAPI-Expressions/`** for definitions, intended behavior, version tags, examples, and known issues.
3. **`Scripts/scriptutils.lua`** for canonical searchable signatures, overloads, LuaLS types, enums, and availability markers.
4. Historical Battlezone 1.5 notes only when the target behavior has not been validated in Redux.

This order is deliberate. The HTML corpus is extremely useful, but it contains at least one incorrect Redux claim: its `ObjectiveObjects()` page says the 1.5 iterator bug was solved in Redux, while current Redux project testing confirms that the stock iterator is **still broken**.

When a runtime finding contradicts the HTML reference, document both rather than silently erasing the discrepancy.

---

# Scope

- Runtime: **Lua 5.1**.
- Target: **Battlezone 98 Redux** (`GameVersion` begins with `"2"`).
- Do not assume external standard libraries such as `io`, `os`, or `debug` are available.
- Do not use Lua 5.2+ syntax such as `goto` / `::label::`.
- EXU, OpenShim, BZFILE, and Campaign Reimagined helper functions are **not stock Lua API** unless explicitly identified as such.
- `Scripts/scriptutils.lua` can contain project-only additions. Entries tagged `[campaignReimagined]`, such as `SetTeamColor`, are not retail BZR functions.

---

# Agent rules

1. **A valid signature does not prove valid engine behavior.** Always check the hazard section for functions involved in multiplayer, iterators, objectives, AI setup, ownership, or producer commands.
2. **Stock BZR `ObjectiveObjects()` is broken. Do not use it unless a known OpenShim/EXU compatibility patch is confirmed active.**
3. **`GetPlayerHandle(team)` is broken for remote-player lookup.** Calling `GetPlayerHandle()` for the local player is valid; passing a team number can return `nil` instead of the remote player's handle.
4. **Prefer capability tests over parsing exact version strings** for optional Redux functions.
5. **Treat network ownership as part of the design.** A local mutation is not proof that the same state exists on peers.
6. **`SetAIControl` is startup configuration.** Calling it after strategic-AI initialization can crash the game.
7. **Never exceed ten simultaneous objective messages.** The stock objective panel uses a fixed buffer and can overflow.
8. **Do not rely on the `duration` argument of `AddObjective` or `UpdateObjective`.** It is ignored; the effective duration is fixed to eight seconds.
9. **Differentiate `BuildObject` from `Build`/`BuildAt`.** `BuildObject` creates immediately; `Build` and `BuildAt` command producers.
10. **Use `TeamSlot`, `AiCommand`, `PathType`, and `ClassId` instead of magic numeric constants.**
11. **Exact capitalization is part of the API.** Do not “correct” names such as `UpdateEarthQuake` or `isPortalActive`.
12. **Project/runtime findings outrank an HTML statement when the conflict is explicit and reproducible.**

---

# High-priority stock bugs and quirks

## `ObjectiveObjects()` — BROKEN IN STOCK REDUX

```text
iterator ObjectiveObjects()
```

Current Redux project testing records that the stock iterator is broken and returns only the first objective object rather than enumerating the full set.

**Agent rule:** do not generate stock Lua that depends on `ObjectiveObjects()`.

```lua
-- Do not assume this enumerates every objective in stock Redux.
for h in ObjectiveObjects() do
    -- unsafe assumption
end
```

If OpenShim or EXU provides a compatibility patch for this iterator, the patched behavior may be usable, but that must be treated as an **environment capability**, not as stock Redux behavior. Do not assume the patch exists merely because EXU/OpenShim is commonly used by this project.

The HTML reference currently claims the old 1.5 bug was fixed in Redux. That statement conflicts with current Redux testing and is therefore treated as inaccurate for this project.

Primary project note: `Text/ScriptingGuide.txt`.

## `GetPlayerHandle(team)` — remote team lookup is broken

```text
handle GetPlayerHandle([teamnum team])
```

- `GetPlayerHandle()` with no argument: normal local-player lookup.
- `GetPlayerHandle(team)` for another player's team: current project testing says it always returns `nil` instead of the remote player's handle.

Do not write:

```lua
local remotePlayer = GetPlayerHandle(2)
```

For multiplayer, track player identity through `CreatePlayer` / `AddPlayer` / `DeletePlayer` and exchange current player-object handles through `Send` / `Receive` when required.

## `LockAllies()` called from `Start()`

The HTML reference documents that in Redux, calling `LockAllies(...)` from `Start()` has no effect.

If the mission requires locked alliances, issue the one-shot lock after startup has advanced sufficiently and validate the result in-game.

## Objective panel: fixed duration and fixed capacity

```text
AddObjective(name, color?, duration?, text?)
UpdateObjective(name, color?, duration?, text?)
```

Documented hazards:

- `duration` is ignored; effective duration is fixed to **8 seconds**.
- only **10 simultaneous objectives** are safe;
- adding more can overflow the stock buffer and eventually crash the game.

Prefer named reusable slots and `UpdateObjective` instead of endlessly appending entries.

## Multiplayer cockpit timer override

In `MultSTMission` and `MultDMMission`, the stock multiplayer mission logic calls `StartCockpitTimerUp()` every frame.

Consequences:

- a normal `StartCockpitTimer()` countdown cannot be maintained;
- warn/alert thresholds cannot be reliably repurposed;
- show/hide behavior remains possible.

Do not design a multiplayer countdown mechanic around the stock cockpit timer without replacing or bypassing that stock mission-mode behavior.

## `Attack()` against same-team targets

```text
Attack(handle me, handle him, priority? priority)
```

The target is only attacked when it is on the attacker's own team if command priority is `1` (uncommandable).

## Armory `Build` / `BuildAt` cross-team targeting

The HTML reference documents a targeting bug when an Armory belongs to a team other than the local player's team: launched powerups may not properly reach the requested target.

The source page documents Lua/ODF workarounds involving `aiName2`.

Do not assume a cross-team Armory behaves identically to the local player's Armory.

## `Build()` then `Dropoff()` needs a simulation update

For Armories and Construction Rigs, the producer must first process the `Build(...)` command. At least one simulation update is needed before the location supplied through `Dropoff(...)` is reliably accepted.

Unsafe assumption:

```lua
Build(rig, "abtowe")
Dropoff(rig, where) -- same synchronous frame/path
```

Safer pattern:

```lua
Build(rig, "abtowe")
-- issue Dropoff on a later Update
```

## `SetAIControl()` timing

```text
SetAIControl(teamnum team, boolean? enabled)
```

Only configure strategic AI during mission startup/root initialization. The engine sets strategic AI up shortly afterward; later calls can crash the game.

`GetAIControl(team)` can be queried later.

## Exact stock capitalization

```lua
UpdateEarthQuake(magnitude)
isPortalActive(portal)
```

Both spellings are intentional.

## Legacy string-padding/null-byte warning

Project notes also record hidden trailing/null characters from string-returning functions such as:

```text
GetOdf
GetPilotClass
GetWeaponClass
GetClassSig
GetBase
```

The HTML corpus describes the null-character defect as a Battlezone 1.5.2.x issue, while project notes list it as an engine caveat without the same qualification.

**Agent rule:** do not silently normalize strings unless the mission/build actually reproduces the problem. If comparison failures occur despite identical printed text, inspect for `\0` padding before assuming the script logic is wrong.

## `DeleteObject()` properties

Project notes record that once an object is flagged as destroyed, most properties are no longer safe/useful from `DeleteObject()`, with the handle/objective name being the important remaining identifiers.

If destruction logic needs ammo, ODF, team, health, class, or similar properties, cache those while the object is alive instead of querying them only after destruction.

---

# Legacy Battlezone 1.5 compatibility notes

These are historical compatibility issues. Do not automatically apply them to Redux unless current testing reproduces them.

| Function/behavior | Historical issue |
|---|---|
| `SetLabel` | named `SettLabel` in 1.5.2.x |
| `GiveWeapon` | removing currently active weapon could crash 1.5 |
| `GetAIControl` | missing/broken on some 1.5 builds and implemented through a Lua workaround |
| string-returning getters | 1.5 documentation reports unexpected null characters |
| `ObjectiveObjects` | old docs describe a 1.5 loop-counter bug; stock Redux is also broken, but current Redux behavior is documented separately above |

Cross-version compatibility code may use:

```lua
SetLabel = SetLabel or SettLabel
```

---

# Core runtime types

| Type | Meaning |
|---|---|
| `handle` | game-object identifier/light userdata |
| `message` | audio-message userdata |
| `odfhandle` | parsed ODF/INI/TRN handle |
| `vector` | `x`, `y`, `z` position/direction userdata |
| `matrix` | right/up/front/posit transform userdata |
| `teamnum` | integer team 0–15 |
| `weaponslot` | weapon slot 0–4 |
| `weaponmask` | hardpoint bit mask 0–31 |
| `priority` | 0 commandable, 1 uncommandable |

Object handles are safe identifiers, but a non-nil handle does not imply the underlying object still exists. Use `IsValid` / `IsAlive` as appropriate.

---

# Important globals and enums

```text
string GameVersion
number Language              -- Redux 2.0+
string LanguageName          -- Redux 2.0+
string LanguageSuffix        -- Redux 2.0+
string LastGameKey
matrix IdentityMatrix
ClassId ClassId
TeamSlot TeamSlot
PathType PathType
AiCommand AiCommand
```

`GameVersion` starts with `"1"` for Battlezone 1.5 and `"2"` for Redux.

Prefer capability tests when a particular function matters:

```lua
if IsTouching ~= nil then
    -- Redux version that provides IsTouching
end
```

## `PathType`

```text
PathType.ONE_WAY    = 0
PathType.ROUND_TRIP = 1
PathType.LOOP       = 2
```

## Important `TeamSlot` names

```text
PLAYER
RECYCLER
FACTORY
ARMORY
CONSTRUCT
MIN_OFFENSE / MAX_OFFENSE
MIN_DEFENSE / MAX_DEFENSE
MIN_UTILITY / MAX_UTILITY
MIN_BEACON / MAX_BEACON
MIN_POWER / MAX_POWER
MIN_COMM / MAX_COMM
MIN_REPAIR / MAX_REPAIR
MIN_SUPPLY / MAX_SUPPLY
MIN_SILO / MAX_SILO
MIN_BARRACKS / MAX_BARRACKS
MIN_GUNTOWER / MAX_GUNTOWER
```

## Important `AiCommand` names

```text
NONE
SELECT
STOP
GO
ATTACK
FOLLOW
FORMATION
PICKUP
DROPOFF
NO_DROPOFF
GET_REPAIR
GET_RELOAD
GET_WEAPON
GET_CAMERA
GET_BOMB
DEFEND
GO_TO_GEYSER
RESCUE
RECYCLE
SCAVENGE
HUNT
BUILD
PATROL
STAGE
SEND
GET_IN
LAY_MINES
CLOAK
```

---

# LuaMission callbacks

Mission scripts implement these handlers; LuaMission calls them.

```text
Load(...)
... Save()
Start()
GameKey(string key)
Update(number timestep)
CreateObject(handle h)
AddObject(handle h)
DeleteObject(handle h)
CreatePlayer(integer id, string name, teamnum team)
AddPlayer(integer id, string name, teamnum team)
DeletePlayer(integer id, string name, teamnum team)
boolean Receive(integer from, string type, ...)
boolean Command(string command, string arguments)
```

Guidance:

- `Start()` is one-time initialization.
- `Update()` is the main per-frame simulation callback.
- `CreateObject()` receives heavy traffic; keep it cheap.
- `AddObject()` generally covers more important mission objects.
- `Save` / `Load` support serializable primitive/game types, not arbitrary Lua state.
- multiplayer-only missions normally do not rely on save/load.
- `Receive()` is the standard explicit script-level network synchronization hook.

---

# Multiplayer ownership and locality

## Canonical network API

```text
boolean IsNetGame()
boolean IsHosting()
SetLocal(handle h)
boolean IsLocal(handle h)
boolean IsRemote(handle h)
DisplayMessage(string message)
Send(integer? to, string type, ...)
```

`Send(nil, type, ...)` and `Send(0, type, ...)` broadcast.

The stock packet payload is approximately **244 bytes** after network headers, so keep custom messages compact.

`SetLocal` must not be used as a casual synchronization primitive. Only one machine should attempt to claim a specific object at a time.

## Project-validated multiplayer behavior

These observations come from Campaign Reimagined runtime testing and should be treated as practical BZR behavior unless later testing supersedes them.

| Operation | Observed behavior |
|---|---|
| `MakeExplosion` | local-only; remote peers do not automatically receive explosion/damage |
| `SetVelocity` | synchronizes correctly in project testing |
| `BuildObject` | globally usable vehicle creation is safest from the machine that should own/control it |
| non-host/client-built vehicles | can be invisible/nonfunctional to others unless ownership is corrected |
| `RemoveObject` on remote/non-local object | remote state can restore it; synchronized removal should be explicitly messaged |
| `SetPosition` on remote/non-local object | same class of locality problem as removal |
| `SetLocal` on remote AI | can break that AI's control/behavior |
| `SetName` | observed local-only |
| objective markers | not synchronized automatically |
| `Hide` / `UnHide` | peers can diverge unless state is applied consistently |
| team mutations on another player's units | require correct locality/ownership |
| `GiveWeapon` | use `Send`/`Receive` when weapon state must match on all peers |
| `DisplayMessage` | local chat-window output; stringify non-string values |

### Recommended synchronization shape

```lua
local MSG_REMOVE = "R"

function RemoveSynced(h)
    if IsNetGame() then
        Send(0, MSG_REMOVE, h)
    else
        RemoveObject(h)
    end
end

function Receive(from, kind, ...)
    if kind == MSG_REMOVE then
        local h = ...
        if IsValid(h) then
            RemoveObject(h)
        end
        return true
    end

    return false
end
```

Mission-specific authority still matters; this only illustrates the principle that every peer should receive an explicit state transition when stock replication does not provide it.

---

# Function reference

Notation:

- `T?` means optional.
- `A|B` means overload/union.
- `pos` means the function supports the documented `handle`, `path[, point]`, `vector`, or `matrix` location forms.
- `[2.0+]` / `[2.1+]` are Redux availability markers.

## Audio messages

```text
RepeatAudioMessage()
message AudioMessage(string filename)
boolean IsAudioMessageDone(message msg)
StopAudioMessage(message msg)
boolean IsAudioMessagePlaying()
```

Audio messages are 2D voice/narration playback and use the Voice Volume option.

## Sound effects

```text
StartSound(string filename, handle? h, integer? priority,
           boolean? loop, integer? volume, integer? rate)
StopSound(string filename, handle? h)
```

With a handle, sound is positional and follows the object. Without a handle it is global 2D sound.

## Game objects

```text
handle GetHandle(string label)
handle BuildObject(string odfname, teamnum team, handle h)
handle BuildObject(string odfname, teamnum team, string path, integer? point)
handle BuildObject(string odfname, teamnum team, vector position)
handle BuildObject(string odfname, teamnum team, matrix transform)
RemoveObject(handle h)
boolean IsOdf(handle h, string odfname)
string GetOdf(handle h)
string GetBase(handle h)
string GetLabel(handle h)
SetLabel(handle h, string label)
string GetClassSig(handle h)
string GetClassLabel(handle h)
ClassId GetClassId(handle h)
string GetNation(handle h)
boolean IsValid(handle h)
boolean IsAlive(handle h)
boolean IsAliveAndPilot(handle h)
boolean IsCraft(handle h)
boolean IsBuilding(handle h)
boolean IsPerson(handle h)
boolean IsDamaged(handle h, number? threshold)
[2.1+] boolean IsRecycledByTeam(handle h, teamnum team)
```

## Team / perceived team

```text
teamnum GetTeamNum(handle h)
SetTeamNum(handle h, teamnum team)
teamnum GetPerceivedTeam(handle h)
SetPerceivedTeam(handle h, teamnum team)
```

The perceived team can differ from the real team during disguise/empty-enemy-vehicle behavior.

## Target

```text
SetUserTarget(handle? target)
handle GetUserTarget()
SetTarget(handle h, handle target)
handle GetTarget(handle h)
```

The user-target functions operate on the local player's UI target.

## Owner

```text
SetOwner(handle h, handle owner)
handle GetOwner(handle h)
```

## Pilot class

```text
SetPilotClass(handle h, string? odfname)
string GetPilotClass(handle h)
```

Nil resets the pilot class to the normal nation/default assignment.

## Position / transform

```text
SetPosition(handle h, string path, integer? point)
SetPosition(handle h, vector position)
SetPosition(handle h, matrix transform)
vector GetPosition(handle h)
vector GetPosition(string path, integer? point)
vector GetFront(handle h)
SetTransform(handle h, matrix transform)
matrix GetTransform(handle h)
```

Use `SetTransform` when orientation matters. The matrix overload of `SetPosition` is still position-oriented rather than a general transform replacement.

## Velocity

```text
vector GetVelocity(handle h)
SetVelocity(handle h, vector velocity)
vector GetOmega(handle h)
SetOmega(handle h, vector omega)
```

## Position helpers

```text
vector GetCircularPos(vector center, number? radius, number? angle)
vector GetPositionNear(vector center, number? minradius, number? maxradius)
```

`GetPositionNear` is useful when spawning multiple units around one reference point so they do not overlap.

## Shot information

```text
handle GetWhoShotMe(handle h)
number GetLastEnemyShot(handle h)
number GetLastFriendShot(handle h)
```

## Alliances

```text
DefaultAllies()
LockAllies(boolean lock)
Ally(teamnum team1, teamnum team2)
UnAlly(teamnum team1, teamnum team2)
boolean IsTeamAllied(teamnum team1, teamnum team2)
boolean IsAlly(handle me, handle him)
```

Player actions can create half-allied states, so `IsTeamAllied(a,b)` need not equal `IsTeamAllied(b,a)`.

## Objective markers / visible names

```text
SetObjectiveOn(handle h)
SetObjectiveOff(handle h)
string GetObjectiveName(handle h)
SetObjectiveName(handle h, string name)
[2.1+] SetName(handle h, string name)
```

`SetName` is effectively an alias of `SetObjectiveName` in the stock API.

Project multiplayer testing says visible-name and objective-marker changes are not automatically synchronized.

## Distance

```text
number GetDistance(handle h, handle target)
number GetDistance(handle h, string path, integer? point)
number GetDistance(handle h, vector position)
number GetDistance(handle h, matrix transform)
boolean IsWithin(handle h1, handle h2, number distance)
[2.1+] boolean IsTouching(handle h1, handle h2, number? tolerance)
```

Default `IsTouching` tolerance is approximately 1.3 m.

## Nearest queries

Applicable overload families accept handle, path/point, vector, or matrix reference positions:

```text
handle GetNearestObject(pos)
handle GetNearestVehicle(pos)
handle GetNearestBuilding(pos)
handle GetNearestEnemy(pos)
[2.0+] handle GetNearestFriend(pos)
[2.1+] handle GetNearestUnitOnTeam(pos, teamnum team)
integer CountUnitsNearObject(handle h, number distance, teamnum team, string odfname)
```

## Iterators

```text
iterator ObjectsInRange(number distance, pos)
iterator AllObjects()
iterator AllCraft()
iterator SelectedObjects()
iterator ObjectiveObjects()   -- BROKEN IN STOCK REDUX
```

Use:

```lua
for h in AllCraft() do
    -- ...
end
```

Prefer `AllCraft()` over `AllObjects()` when only craft are needed; `AllObjects()` includes incidental objects such as scrap.

Do **not** use stock `ObjectiveObjects()` to enumerate all objective objects. Current Redux project testing says it returns only the first result.

## Scrap management

```text
GetRidOfSomeScrap(integer? limit) -- default 300
ClearScrapAround(number distance, pos)
```

## Team slots

```text
handle GetTeamSlot(TeamSlot slot, teamnum? team)
handle GetPlayerHandle(teamnum? team)       -- remote-team overload broken
handle GetRecyclerHandle(teamnum? team)
handle GetFactoryHandle(teamnum? team)
handle GetArmoryHandle(teamnum? team)
handle GetConstructorHandle(teamnum? team)
```

No team argument means the local player's team.

## Team pilots

```text
integer AddPilot(teamnum team, integer count)
integer SetPilot(teamnum team, integer count)
integer GetPilot(teamnum team)
integer AddMaxPilot(teamnum team, integer count)
integer SetMaxPilot(teamnum team, integer count)
integer GetMaxPilot(teamnum team)
```

## Team scrap

```text
integer AddScrap(teamnum team, integer count)
integer SetScrap(teamnum team, integer count)
integer GetScrap(teamnum team)
integer AddMaxScrap(teamnum team, integer count)
integer SetMaxScrap(teamnum team, integer count)
integer GetMaxScrap(teamnum team)
```

## Deploy / selection / critical

```text
boolean IsDeployed(handle h)
Deploy(handle h)
boolean IsSelected(handle h)
[2.0+] boolean IsCritical(handle h)
[2.0+] SetCritical(handle h, boolean? critical)
```

Mission-critical status disables player actions that would remove/recycle the object.

## Weapons and damage

```text
SetWeaponMask(handle h, weaponmask mask)
boolean GiveWeapon(handle h, string? weaponname, weaponslot? slot)
string GetWeaponClass(handle h, weaponslot slot)
FireAt(handle me, handle him)
Damage(handle h, number amount)
```

Weapon-mask bits correspond to hardpoints 1, 2, 4, 8, and 16.

A nil/blank weapon name with an explicit slot removes that slot's weapon.

## Time

```text
number GetTime()
number GetTimeStep()
number GetTimeNow()
```

`GetTimeNow()` is system milliseconds and is mainly useful for profiling. Mission logic should normally use simulation time/timestep.

## Mission / strategic AI

```text
SetAIControl(teamnum team, boolean? enabled) -- startup-only
boolean GetAIControl(teamnum team)
string GetAIP(teamnum? team)                 -- default team 2
SetAIP(string aipname, teamnum? team)        -- default team 2
FailMission(number time, string? filename)
SucceedMission(number time, string? filename)
```

## Objective messages

```text
ClearObjectives()
AddObjective(string name, string? color, number? duration, string? text)
UpdateObjective(string name, string? color, number? duration, string? text)
RemoveObjective(string name)
```

Supported colors include white/black/grey/blue/green/yellow/red plus dark variants.

Remember:

- duration is effectively fixed to eight seconds;
- keep simultaneous entries <= 10.

## Cockpit timer

```text
StartCockpitTimer(integer time, integer? warn, integer? alert)
StartCockpitTimerUp(integer time, integer? warn, integer? alert)
StopCockpitTimer()
HideCockpitTimer()
integer GetCockpitTimer()
```

`StartCockpitTimer` tops out at `35999` seconds (`9:59:59`).

`StartCockpitTimerUp` has a display malfunction after ten hours.

See the stock multiplayer-mode override warning earlier.

## Earthquake

```text
StartEarthquake(number magnitude)
UpdateEarthQuake(number magnitude)
StopEarthquake()
```

## Path type / area

```text
[2.0+] SetPathType(string path, PathType type)
[2.0+] PathType GetPathType(string path)
SetPathOneWay(string path)
SetPathRoundTrip(string path)
SetPathLoop(string path)
[2.0+] integer GetPathPointCount(string path)
[2.0+] integer GetWindingNumber(string path, handle|vector|matrix target)
[2.0+] boolean IsInsideArea(string path, handle|vector|matrix target)
```

A non-zero winding number means the target point is inside the path-defined polygonal area.

## Unit command inspection

```text
boolean CanCommand(handle me)
boolean CanBuild(handle me)
boolean IsBusy(handle me)
AiCommand GetCurrentCommand(handle me)
handle GetCurrentWho(handle me)
integer GetIndependence(handle me)
SetIndependence(handle me, integer independence)
```

Independence `1` lets a unit take initiative; `0` suppresses autonomous initiative.

## Generic command

```text
SetCommand(handle me,
           AiCommand command,
           priority? priority,
           handle? who,
           matrix|vector|string? where,
           number? when,
           string? param)
```

Not every command is valid for every unit. Use the named wrapper functions when possible.

## Unit command wrappers

```text
Attack(handle me, handle him, priority? priority)
Goto(handle me, string|handle|vector|matrix destination, priority? priority)
Mine(handle me, string|vector|matrix destination, priority? priority)
Follow(handle me, handle him, priority? priority)
[2.1+] boolean IsFollowing(handle me, handle him)
Defend(handle me, priority? priority)
Defend2(handle me, handle him, priority? priority)
Stop(handle me, priority? priority)
Patrol(handle me, string path, priority? priority)
Retreat(handle me, string|handle destination, priority? priority)
GetIn(handle me, handle him, priority? priority)
Pickup(handle me, handle him, priority? priority)
Dropoff(handle me, string|vector|matrix destination, priority? priority)
Build(handle me, string odfname, priority? priority)
BuildAt(handle me, string odfname, handle|string|vector|matrix destination, priority? priority)
[2.1+] Formation(handle me, handle him, priority? priority)
[2.1+] Hunt(handle me, priority? priority)
```

Priority `0` leaves a unit player-commandable. Default priority `1` makes the issued command uncommandable by the player.

### Project behavior notes

- `Defend2`: defensive follow behavior; can chase enemies and may fail to re-follow if the defended object moves too far away.
- `Follow`: looser follow behavior; tends to re-follow after exceeding distance thresholds.
- `Formation`: tightest follow pattern; units cluster near the target and frequently retarget nearby threats.

Treat these descriptions as observed AI behavior rather than a stable formal contract.

## Tug cargo

```text
boolean HasCargo(handle tug)
[2.1+] handle GetCargo(handle tug)
handle GetTug(handle cargo)
```

## Pilot actions

```text
EjectPilot(handle h)
HopOut(handle h)
KillPilot(handle h)
RemovePilot(handle h)
handle HoppedOutOf(handle h)
```

## Health

```text
number GetHealth(handle h)       -- fractional 0..1
number GetCurHealth(handle h)
number GetMaxHealth(handle h)
SetCurHealth(handle h, number health)
SetMaxHealth(handle h, number health)
AddHealth(handle h, number health)
[2.1+] GiveMaxHealth(handle h)
```

## Ammo

```text
number GetAmmo(handle h)         -- fractional 0..1
number GetCurAmmo(handle h)
number GetMaxAmmo(handle h)
SetCurAmmo(handle h, number ammo)
SetMaxAmmo(handle h, number ammo)
AddAmmo(handle h, number ammo)
[2.1+] GiveMaxAmmo(handle h)
```

## Cinematic camera

```text
boolean CameraReady()
boolean CameraPath(string path, integer height, integer speed, handle target)
boolean CameraPathDir(string path, integer height, integer speed)
boolean PanDone()
boolean CameraObject(handle base, integer right, integer up, integer forward, handle target)
boolean CameraFinish()
boolean CameraCancelled()
```

`CameraObject` offsets are in centimeters.

## Info display

```text
boolean IsInfo(string odfname)
```

## ODF / INI / TRN reads

```text
odfhandle OpenODF(string filename)
boolean value, boolean found = GetODFBool(odfhandle odf, string? section,
                                          string label, boolean? default)
integer value, boolean found = GetODFInt(odfhandle odf, string? section,
                                         string label, integer? default)
number value, boolean found = GetODFFloat(odfhandle odf, string? section,
                                          string label, number? default)
string value, boolean found = GetODFString(odfhandle odf, string? section,
                                           string label, string? default)
```

If no extension is supplied, `OpenODF` appends `.odf`.

Cache frequently reused `odfhandle` values rather than repeatedly reopening the same file.

## Terrain / floor

Applicable overloads accept handle, path/point, vector, or matrix positions:

```text
number height, vector normal = GetTerrainHeightAndNormal(pos)
number height, vector normal = GetFloorHeightAndNormal(pos)
```

Floor queries include upward-facing polygons on floor-owner entities; terrain queries use the terrain height field.

## Map / files / effects

```text
[2.0+] string GetMissionFilename()
string GetMapTRNFilename()
[2.0+] string UseItem(string filename)
[2.0+] ColorFade(number ratio, number rate, integer r, integer g, integer b)
```

## Vector construction and math

```text
vector SetVector(number? x, number? y, number? z)
number DotProduct(vector a, vector b)
vector CrossProduct(vector a, vector b)
vector Normalize(vector v)
number Length(vector v)
number LengthSquared(vector v)
number Distance2D(vector a, vector b)
number Distance2DSquared(vector a, vector b)
number Distance3D(vector a, vector b)
number Distance3DSquared(vector a, vector b)
```

Vector userdata also supports arithmetic operators. Vector-by-vector multiplication/division is component-wise, not a dot/cross product.

## Matrix construction

```text
matrix SetMatrix(...12 numeric components...)
matrix BuildAxisRotationMatrix(number? angle, number? x, number? y, number? z)
matrix BuildAxisRotationMatrix(number? angle, vector axis)
matrix BuildPositionRotationMatrix(number? pitch, number? yaw, number? roll,
                                   number? x, number? y, number? z)
matrix BuildPositionRotationMatrix(number? pitch, number? yaw, number? roll,
                                   vector position)
matrix BuildOrthogonalMatrix(vector? up, vector? heading)
matrix BuildDirectionalMatrix(vector? position, vector? direction)
```

Angles are radians. Axis-rotation axes must be normalized. Bad/non-orthonormal transforms can violate engine assumptions.

## Portal — Redux 2.1+

```text
PortalOut(handle portal)
PortalIn(handle portal)
DeactivatePortal(handle portal)
ActivatePortal(handle portal)
boolean IsIn(handle portal)
boolean isPortalActive(handle portal)
handle BuildObjectAtPortal(string odfname, teamnum team, handle portal)
```

`BuildObjectAtPortal` creates the object at the portal effect with an initial 50 m/s velocity.

## Cloak — Redux 2.1+

```text
Cloak(handle h)
Decloak(handle h)
SetCloaked(handle h)
SetDecloaked(handle h)
boolean IsCloaked(handle h)
EnableCloaking(handle h, boolean enable)
EnableAllCloaking(boolean enable)
```

Direct cloak calls do not replace the unit's current AI command.

## Hide — Redux 2.1+

```text
Hide(handle h)
UnHide(handle h)
```

Hidden state affects rendering and radar but does not mean AI universally treats the object as nonexistent.

Multiplayer state can diverge between peers; see locality notes.

## Explosion — Redux 2.1+

```text
MakeExplosion(string odfname, handle|string|vector|matrix location)
```

Explosions are not game objects and do not return handles.

Project multiplayer testing says `MakeExplosion` is local-only.

---

# Common safe patterns

## Feature gating

```lua
if GetCargo ~= nil then
    local cargo = GetCargo(tug)
end
```

## Remote-player tracking

Do not use the broken remote `GetPlayerHandle(team)` overload as the source of truth.

```lua
local players = {}

function CreatePlayer(id, name, team)
    players[id] = {
        name = name,
        team = team,
    }
end

function DeletePlayer(id, name, team)
    players[id] = nil
end
```

The current controlled object must still be synchronized separately because respawns, ejects, vehicle changes, and hop-outs can replace it.

## Delayed producer dropoff

```lua
local pending = nil

function QueueBuild(rig, odf, where)
    Build(rig, odf)
    pending = {
        rig = rig,
        where = where,
        frames = 1,
    }
end

function Update(dt)
    if pending then
        if pending.frames > 0 then
            pending.frames = pending.frames - 1
        else
            Dropoff(pending.rig, pending.where)
            pending = nil
        end
    end
end
```

## Bounded objective slots

```lua
local objectives = {}

local function SetObjectiveSlot(key, text, color)
    if objectives[key] then
        UpdateObjective(key, color or "white", 8, text)
        return
    end

    local count = 0
    for _ in pairs(objectives) do
        count = count + 1
    end

    if count >= 10 then
        error("stock objective-message limit reached")
    end

    AddObjective(key, color or "white", 8, text)
    objectives[key] = true
end
```

The `8` does not actually configure duration; it documents the stock effective duration.

## Objective-object enumeration without stock `ObjectiveObjects()`

If the mission needs its own objective set, maintain it explicitly when calling `SetObjectiveOn` / `SetObjectiveOff` instead of attempting to rediscover every objective through the broken stock iterator.

```lua
local objectiveHandles = {}

local function MarkObjective(h)
    if IsValid(h) then
        SetObjectiveOn(h)
        objectiveHandles[h] = true
    end
end

local function UnmarkObjective(h)
    SetObjectiveOff(h)
    objectiveHandles[h] = nil
end
```

If a shim/EXU compatibility patch later provides a proven full iterator, code that intentionally depends on that patched environment should document the dependency explicitly.

---

# Project content constraints relevant to Lua

Campaign Reimagined uses the game's legacy short-name conventions. ODF basenames and files directly referenced from Lua should remain **8 characters or fewer where applicable**.

This is a content/integration constraint rather than a Lua language rule, but agents editing mission scripts must preserve it.

---

# Known source conflicts

## `ObjectiveObjects()`

**HTML claim:** the old Battlezone 1.5 iterator bug was solved in Redux.

**Current BZR project finding:** stock Redux `ObjectiveObjects()` is still broken as an iterator and only returns the first result.

**Decision:** treat it as broken in stock Redux. A shim/EXU patch may make it usable, but that is an optional runtime capability and must be verified separately.

## Null-padded string getters

**HTML claim:** the null-character defect is a 1.5.2.x issue.

**Project note:** several getters are listed as susceptible to hidden characters.

**Decision:** do not add compatibility stripping everywhere by default, but keep the issue in mind when equality/composition behaves differently from printed output.

---

# Maintenance rules

When updating this reference:

1. Check the relevant HTML leaf page, including `Known Issues`.
2. Check `Scripts/scriptutils.lua` for the canonical signature/availability marker.
3. Check current BZR runtime notes/tests before declaring a historical bug fixed.
4. Runtime-validated Redux behavior overrides an inaccurate historical/reference statement, but preserve the disagreement in `Known source conflicts`.
5. Separate **stock BZR**, **Battlezone 1.5 compatibility**, **Campaign Reimagined helpers**, and **OpenShim/EXU-patched behavior**.
6. Never describe a shim/EXU fix as stock behavior.
7. For multiplayer findings, identify whether behavior is local-only, host-sensitive, ownership-sensitive, replicated, or explicitly synchronized.
8. Preserve odd stock capitalization exactly.
9. Keep project-only functions out of the stock function index.
10. If a stock bug is fixed by OpenShim or EXU, document the required component/version/feature gate once confirmed.

## Primary repository sources

- `Text/ScriptingGuide.txt`
- `References/StockLuaAPI-Functions/`
- `References/StockLuaAPI-Expressions/`
- `Scripts/scriptutils.lua`

For runtime conflicts, current validated BZR findings take precedence over the static HTML statement.
