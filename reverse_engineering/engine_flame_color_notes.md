# Engine Flame Color Notes

Date: 2026-03-16

## Scope

Goal: determine whether Battlezone 98 Redux supports engine flame color per
team or per handle, and if not, identify what native change would be required.

Primary inputs:

- GOG EXE: `C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe`
- GOG PDB: `C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb`
- Stock ODF: `C:\Users\istuart\Downloads\Battlezone 98 Redux\Edit\stock\engflame.odf`
- Sprite materials: `C:\GOG Games\Battlezone 98 Redux\BZ_ASSETS\pc\materials\sprites.material`

## Result

Stock Redux only supports one global engine flame definition at a time.

The blue default is not just an ODF default that later gets overridden per
object. The native `EngineFlame` feature owns one global texture/index/frame
set and pushes individual flames into a queue that stores only:

- `MAT_3D transform`
- `float scale`

There is no per-flame team, handle, color, texture, or material field in the
queued record. By the time `EngineFlame::Submit` renders the queue, the owner
context is already gone.

Conclusion: per-team or per-handle engine flame color is not present in stock
Redux and cannot be enabled only by editing ODFs. It needs a native patch.

## Asset-Side Findings

Stock `engflame.odf` explicitly points to blue:

```ini
[EngineFlame]
flareTexture = "sun.0"
flareFrames = 1
flareScale = 2.0
flareVariance = 0.2
flameTexture = "exhaust_b.0"
flameFrames = 4
flameWidth = 1.0
flameLength = 3.0
```

The shipped assets do contain separate colored flame materials:

- `sprites.material:398` `material rflame`
- `sprites.material:404` `material gflame`
- `sprites.material:410` `material bflame`

And the matching textures exist:

- `rflame.png`
- `gflame.png`
- `bflame.png`

Important limitation: stock assets expose `rflame`, `gflame`, and `bflame`,
but this investigation did not find stock aliases `exhaust_r.0` or
`exhaust_g.0`. The executable only exposes `exhaust_b.0`.

Practical meaning:

- You can replace global flame behavior with a custom `engflame.odf`.
- You can also add your own material aliasing to point that global ODF at a
  different flame.
- But stock native code still applies that choice globally, not per object.

## Native Findings

`llvm-pdbutil` shows a dedicated global feature compiled from
`fun3d\engineflame.cpp` / `EngineFlame.obj`.

Key symbols:

- `EngineFlame::PreLoad`
- `EngineFlame::AddFlame`
- `EngineFlame::Control`
- `EngineFlame::Submit`
- static `engineFlame`

Class layout from the shipped PDB:

```text
class EngineFlame [sizeof = 4672]
  +0x28   Flame flameList[64]
  +0x1228 Flame* flamePtr
  +0x122c long flameTexture
  +0x1230 long flameIndex
  +0x1234 long flameFrames
  +0x1238 float flameLength
```

Queued flame layout:

```text
struct Flame [sizeof = 72]
  +0x00 MAT_3D transform
  +0x40 float scale
```

That is the core blocker. `Flame` has no room for:

- team
- handle
- texture id
- color enum

So stock behavior is structurally global.

## Function Ranges

Original source file and line ranges recovered from the PDB:

- `fun3d\engineflame.cpp`
  - line 28-49: `EngineFlame::PreLoad`
  - line 57-77: `EngineFlame::AddFlame`
  - line 84-92: `EngineFlame::Control`
  - line 98-210: `EngineFlame::Submit`

Matching public RVAs from the PDB pretty dump:

- `EngineFlame::PreLoad` around `0x0005FC90`
- `EngineFlame::AddFlame` around `0x0005FDC0`
- `EngineFlame::Control` around `0x0005FE40`
- `EngineFlame::Submit` around `0x0005FE70`

The line table dump reports section-relative offsets lower by `0x1000`, which
matches the PE `.text` section base.

Legacy BZ1 RVAs are useful for symbol confirmation, but the live Redux GOG build
uses different VAs. The current validated GOG addresses are:

- `EngineFlame::EngineFlame` `0x004C85F0`
- `EngineFlame::PreLoad` `0x004C8610`
- `EngineFlame::AddFlame` `0x004C8800`
- `EngineFlame::Control` `0x004C88A0`
- `EngineFlame::Submit` `0x004C88C0`

The live `EngineFlame` vtable is at `0x0087918C` with:

- `Control` slot `0x008791A4 -> 0x004C88A0`
- `Submit` slot `0x008791AC -> 0x004C88C0`

The live hovercraft exhaust call path is:

- `HoverCraft::Simulate(float dt)` `0x004EA300`
- `EngineFlame::AddFlame` callsite `0x004EAD77` with manager `0x009B2C88`
- `EngineFlame::AddFlame` callsite `0x004EAFDE` with manager `0x009B3ED8`

At both callsites the current hovercraft `this` pointer is still available at
`[ebp-0x698]`, which makes them the best current hook points for team-aware
routing before stock blue exhaust wins.

## What This Means For Modding

### What ODF can do now

ODF can select one engine flame setup globally through `engflame.odf`.

That is why defining your own `engflame.odf` works but affects everything.

### What ODF cannot do now

ODF cannot assign engine flame color per team or per handle in stock native
code because the renderer queue never stores that information.

## Native Patch Direction

Two realistic patch strategies emerged from this investigation.

### Option 1: intercept before `AddFlame`

Hook a caller that still knows the owning object, then choose a color there.

Example flow:

1. determine team or handle from the owner
2. map that to red, green, blue, or custom flame material
3. enqueue into a color-specific manager instead of the stock singleton

This is the least invasive design if the stock submit logic can be reused.

### Option 2: replace the queue format

Patch `EngineFlame::AddFlame` and `EngineFlame::Submit` together so each queued
entry carries a texture/material selector.

Example extended record:

```cpp
struct FlameEx {
    MAT_3D transform;
    float scale;
    uint8_t flameColor;
};
```

This is cleaner architecturally, but it is a bigger native patch because both
enqueue and submit paths must change.

## Recommended Implementation Shape

For OpenShim, the best first experiment is:

1. identify the call site that invokes `EngineFlame::AddFlame`
2. hook there, while the owner object is still known
3. route the flame into one of several parallel flame managers:
   - blue
   - green
   - red
   - optional custom

Why this looks best:

- the stock queue already only needs `transform` and `scale`
- the per-color choice can stay outside the queued record
- the existing submit pattern is already organized around one texture set per
  manager

In other words, stock code already behaves like "one queue per texture". It
just only ships with one global queue instance.

## Implemented Status

As of 2026-03-16, the first full Shim + EXU implementation is in the repos.

EXU now provides the script-facing API:

- `exu.GetTeamEngineFlameColor(team)`
- `exu.SetTeamEngineFlameColor(team, color)`
- `exu.ClearTeamEngineFlameColor(team)`

Valid colors:

- `default`
- `blue`
- `red`
- `green`

EXU also exports `EXU_GetTeamEngineFlameColor(int team)` for Shim.

Shim now does the native routing:

- patches the two live `HoverCraft::Simulate` `AddFlame` callsites
- reads the current hovercraft pointer from the stack frame
- resolves `handle` via `GetHandle` at `0x00462380`
- resolves `team` via live `GetTeamNum` helper `0x005C8800`
- asks EXU for the requested color
- redirects the exhaust into cloned red/green `EngineFlame` managers when needed
- patches the live `EngineFlame` vtable `Control` and `Submit` slots so cloned
  managers advance and render each frame

Current texture resolution candidates are:

- red: `exhaust_r.0`, `rflame.0`, `rflame`
- green: `exhaust_g.0`, `gflame.0`, `gflame`

The cloned manager objects currently preserve stock frame, width, and length
behavior and only swap the flame texture handle.

## Build Status

Build verification completed on 2026-03-16:

- OpenShim Debug|Win32: passed
- OpenShim Release|Win32: passed
- EXU Debug|x86: passed
- EXU Release|x86: passed

EXU needed a few unrelated cleanup fixes during this chain:

- `LuaExport.cpp` local `EXPORT` identifier renamed to avoid macro collision
- `UnitVo` files wired into the project and umbrella patch header
- `Overlay.cpp` SEH block split so MSVC accepts the function
- Ogre include path corrected from `..\GIT\ogre-1.10.0` to `..\ogre-1.10.0`

These are build-chain fixes, not engine-flame design changes.

## Runtime Test Chain

Build verification is done. In-game validation is still the next step.

Recommended runtime test:

1. Install the new `winmm.dll` from OpenShim and `exu.dll` from EXU.
2. Ensure assets expose working red and green flame aliases if stock material
   lookup does not resolve `exhaust_r.0` / `exhaust_g.0`.
3. Run a mission script with mappings such as:

```lua
exu.SetTeamEngineFlameColor(1, "blue")
exu.SetTeamEngineFlameColor(2, "red")
exu.SetTeamEngineFlameColor(3, "green")
```

4. Spawn hovercraft-style exhaust users on multiple teams.
5. Verify team-specific exhaust colors in live gameplay.

Current runtime limitation:

- this first pass only hooks the two confirmed hovercraft exhaust callsites
- units that emit exhaust through a different path may still stay stock blue

5. mission spawns hovercraft or other exhaust-using craft on multiple teams
6. in-game verification confirms the teams render different flame colors

Current blockers for the complete chain:

- native exhaust routing is not finished
- red or green exhaust alias exposure still needs to be verified in the live
  addon asset path
- EXU full Debug build is currently blocked by an unrelated compile error in
  `ExtraUtilities-G1\src\Overlay.cpp`

## Commands Used

```powershell
rg -n "rflame|gflame|bflame|exhaust_[rgb]\.0" `
  "C:\GOG Games\Battlezone 98 Redux\BZ_ASSETS\pc\materials\sprites.material" `
  "C:\Users\istuart\Downloads\Battlezone 98 Redux\Edit\stock\engflame.odf"

C:\Program Files\LLVM\bin\llvm-pdbutil.exe pretty --classes `
  --class-definitions=all --with-name=EngineFlame `
  "C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb"

C:\Program Files\LLVM\bin\llvm-pdbutil.exe pretty --classes `
  --class-definitions=all --with-name=Flame `
  "C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb"

C:\Program Files\LLVM\bin\llvm-pdbutil.exe pretty --globals `
  --with-name=engineFlame `
  "C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb"

C:\Program Files\LLVM\bin\llvm-pdbutil.exe dump --files --modi=120 -l `
  "C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb"
```
