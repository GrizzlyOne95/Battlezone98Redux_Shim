# Walker cockpit jitter — native closure attempt, 2026-09-02

Status: **ONE NARROW BLOCKER.** The walker-root → cockpit link is definitively
excluded as the source of divergence, the real cockpit hierarchy is pinned for
all four walkers, and the sole camera-position writer is attributed. What is
*not* proven is that the remaining camera-vs-cockpit cadence difference is the
visible jitter — the symptom was never visually confirmed in these runs.

All measurements below are from **stock** runs. See "Mod contamination" — the
first three capture sessions were invalid because Campaign: Reimagined was
loaded.

---

## 1. Corrections to the previous pass

| Previous claim | Status |
|---|---|
| "avwalk-only asset-specific excluded" | Now actually supported, by per-frame capture on all four walkers under real motion — not by stationary world-transform sampling. |
| "preliminary shared — all four behave identically at world layer" | Superseded. The correct statement is stronger and narrower: the cockpit node carries a **bit-identical** transform to the walker node on every frame, in all four walkers, moving or not. |
| `fwd` / `slope` exercised motion | Confirmed false. `Goto()` does not drive a `SetAsUser()` vehicle. Motion here comes from real keyboard input (`run_lcwalk_drive.ps1`). |
| The native tracer "already exists" | It did not function. It included a header that did not exist, was not in the `.vcxproj`, and never resolved its Ogre exports, so its entity enumeration could never return anything. It has been rewritten. |

---

## 2. Resolved cockpit entities (directive 1)

Resolution is by pointer, not by name: `userObject` (main+0x00517AFC) →
`GameObject+0xF0` → `renderOwner+0x94` → `Ogre::Entity`, the chain verified in
`bzr_hooks.cpp:2484` against ExtraUtilities' `GetOgreEntity`. RTTI on the user
object confirms class identity.

| ODF | RTTI class | world mesh | cockpit mesh | bones | POV bone | veh node parent | ckp node parent |
|---|---|---|---|---|---|---|---|
| `avwalk` | `Walker` | `avwalk.mesh` | `avwalk_c.mesh` | 28 | `AGe11POV` | `Ogre/SceneRoot` | `Ogre/SceneRoot` |
| `svwalk` | `Walker` | `svwalk.mesh` | `svwalk_c.mesh` | 15 | `svw11POV` | `Ogre/SceneRoot` | `Ogre/SceneRoot` |
| `bvwalk` | `Walker` | `bvwalk.mesh` | `bvwalk_c.mesh` | — | `BGe11POV` | `Ogre/SceneRoot` | `Ogre/SceneRoot` |
| `cvwalk` | `Walker` | `cvwalk.mesh` | `cvwalk_c.mesh` | — | `cvw11POV` | `Ogre/SceneRoot` | `Ogre/SceneRoot` |
| `avtank` | `Wingman` | `avtank.mesh` | **none** | 19 | `AGR11POV` | `Ogre/SceneRoot` | — |

The runtime mapping, established by enumeration rather than assumed:

- Every walker's `_c` cockpit entity exists for the whole mission. All of them
  sit **detached** (`getParentSceneNode() == null`) except the possessed one.
- The cockpit node is **not a child of the vehicle node**. Both are children of
  `Ogre/SceneRoot` — the cockpit is a *sibling*. This is why the previous
  subtree-based search found nothing.
- `avtank` has no cockpit entity at all, so the separate-cockpit mechanism is
  specific to vehicles that ship a `_c` mesh.
- Redux imports nothing from `Ogre::Node`/`SceneNode` except `getName` and
  `getCreator` (per `dumpbin /IMPORTS`). It never moves scene nodes through
  Ogre's API — it writes node memory directly.

---

## 3. The walker-root → cockpit link is not the defect

Per-frame capture inside `SceneManager::_renderScene`, ~13,200 frames per
vehicle, under real driven motion (forward / turn / forward+turn / reverse):

| vehicle | frames | body moved | `\|vehD − ckpD\|` mean | max |
|---|---|---|---|---|
| `avwalk` | 13187 | 14.62% | **0.000000** | **0.000000** |
| `svwalk` | 13103 | 12.01% | **0.000000** | **0.000000** |
| `bvwalk` | 13343 | 12.07% | **0.000000** | **0.000000** |
| `cvwalk` | 13247 | 12.96% | **0.000000** | **0.000000** |

Position *and* orientation match exactly: `ckpQ` equals `vehQ` on every frame,
with the same change cadence and the same step sizes. The POV bone never moves
at all (0.00% of frames, local and derived).

**There is no stale parent, no double-applied transform, and no ordering defect
between the walker root and the cockpit.** They are the same transform.

This is the answer to "fix the jitter between walker root and cockpit": at the
Ogre transform level there is nothing between them to fix.

---

## 4. Where the streams do diverge

Rendering runs at ~355 fps while the simulation updates transforms on ~14.7% of
rendered frames (a ~52 Hz tick). Vehicle and cockpit share that cadence exactly.
The camera does not:

- camera position changes on **16.30%** of frames vs the cockpit's **14.67%**
- **frames where the camera moved but the vehicle *and* cockpit did not:**

| vehicle | cam-only frames | % of frames | mean magnitude | max |
|---|---|---|---|---|
| `avwalk` | 139 | 1.05% | 0.005690 | 0.072400 |
| `svwalk` | 26 | 0.20% | 0.002919 | 0.010916 |
| `bvwalk` | 6 | 0.04% | 0.010865 | 0.064689 |
| `cvwalk` | 273 | 2.06% | 0.004013 | 0.079531 |
| `avtank` (control) | 2 | 0.01% | 1.359841 | 2.719144 |

In a first-person cockpit view the cockpit is meant to be rigidly locked to the
eye, so any frame where the eye moves and the cockpit does not is a visible
cockpit slide. Every walker shows more of these than the tank control, but the
rate varies ~50× between walkers (`bvwalk` 0.04% vs `cvwalk` 2.06%) at
comparable amounts of body motion, so **this is a lead, not a proven cause**.
The tank's 2 frames are possession teleports (magnitude 1.4–2.7), not jitter.

---

## 5. Camera writer attribution

One call site writes the camera position, identical across all five vehicles:

```
caller RVA 0x00283026   (VA 0x00683026)
```

Reached via the import table, not a direct call — `Camera::setPosition` has zero
E8 call sites in the executable and one IAT slot, at `[0x869d24]`.

Disassembly of the site:

```
0x00682FCE  mov      edx, dword ptr [ebp - 0x22c]
0x00682FD4  movsd    xmm1, qword ptr [edx + ecx + 0x168]   ; double world coord
0x00682FDD  subsd    xmm1, xmm0                            ; minus rebase origin
0x00682FE1  cvtsd2ss xmm0, xmm1                            ; -> float
0x00682FE5  push     ecx
0x00682FE6  movss    dword ptr [esp], xmm0
...                                                        ; same for +0x160
0x00683018  mov      eax, dword ptr [0x920ea0]
0x0068301D  mov      ecx, dword ptr [eax + 0x10]           ; Camera* (this)
0x00683020  call     dword ptr [0x869d24]                  ; Camera::setPosition(f,f,f)
0x00683026                                                 ; <- observed return address
```

New facts worth keeping:

- `0x00920EA0 + 0x10` is the `Ogre::Camera*`, in the same global structure whose
  `+0x08` is the `Ogre::SceneManager*` (already used elsewhere in the shim).
- The camera world position is held as **doubles** at `+0x160`/`+0x168` of the
  structure at `[ebp-0x22c]`, and the scene is **origin-rebased**: Ogre receives
  `double(world) − origin` narrowed to float. Vehicle/cockpit node positions are
  small numbers near the viewer for the same reason, not world coordinates.

The Redux PDB is useless here — the nearest function public is 336 KB away,
confirming it is a different build.

---

## 6. Mod contamination (important)

`mods\3686673790` is Campaign: Reimagined + Enhanced Shaders, and it overrides
walker meshes including swapped `_c` cockpit meshes. Its cockpit fix parents to
world, so measuring with it loaded measures the fix, not the defect.

**Renaming the folder inside `mods\` does not disable it** — the game enumerates
every subdirectory of `mods\` regardless of name and logged
`MOD FOUND ... 3686673790.disabled_claude`. The folder must be moved out of
`mods\` entirely. `run_lcwalk_drive.ps1 -DisableMods` does this and restores it
in a `finally` block; runs are verified stock by asserting zero `3686673790`
lines in `BZLogger.txt`.

---

## 7. Instrument

`src/patches/walker_cockpit_trace.cpp`, rewritten. Fail-closed, off unless
`[Diagnostics] WalkerCockpitTrace=1` or `OPENSHIM_WALKER_TRACE=1`.

Design points that are load-bearing:

- **Capture runs inside `SceneManager::_renderScene`**, hooked by locating the
  exported implementation in the live SceneManager's vtable and replacing that
  slot. This gives frame coherence and hands us the rendering camera. Cameras
  are *not* in the movable-object collections in Ogre 1.x, so enumerating
  `"Camera"` movables returns nothing.
- **Ogre accessors are called through resolved export addresses, never through
  the headers' vtables.** The pinned 1.10 headers do not share vtable indices
  with the shipped `OgreMain.dll`: dispatching `Node::getParent` through the
  header returned the *Entity* pointer, and walking that fabricated chain
  corrupted the stack into a `STATUS_STACK_BUFFER_OVERRUN` fail-fast.
- Deriving from `Ogre::FrameListener` does not link — it is `_OgreExport`, so
  the base's inherited virtuals become unresolved imports. A layout-compatible
  standalone class is used instead.
- Every pointer reached by walking a chain is validated (`vptr` inside
  OgreMain) before any dispatch through it.

### Harness

- `reverse_engineering/run_lcwalk_drive.ps1` — drives a held, possessed walker
  with real scan-code keyboard input through timed phases, writes `phases.csv`.
  `INPUT` must be pinned to 40 bytes; a 32-byte marshalled struct gets
  `ERROR_INVALID_PARAMETER`.
- `rmwlk.lua` gained only `hold_<odf>` (possess one walker, never advance).
  No capture logic was added.
- `analyze_walker_jitter.py`, `analyze_walker_cadence.py`,
  `analyze_walker_matrix.py`.

---

## 8. What is still open

1. **The symptom was never visually confirmed.** These runs measured transforms;
   nobody watched the screen. If the jitter does not reproduce in the lcbench
   flat-terrain drive, the camera-only frames may be unrelated.
2. **The camera-only frames are not proven to be the jitter.** The 50× spread
   across walkers at comparable motion needs explaining before this is a cause.
3. **The function containing `0x00683026` is unnamed.** It needs a Ghidra pass;
   the PDB cannot help.
4. **Vehicle/cockpit node writers are unattributable by hooking** — Redux writes
   node memory directly rather than through Ogre. Attributing those needs a
   hardware write breakpoint on the node's position field. This only matters if
   the investigation returns to the node layer, which section 3 argues it
   should not.

No smoothing was added. No behavioural patch was made.
