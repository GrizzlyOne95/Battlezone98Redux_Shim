# Phase 2 — Attribution of the non-render CPU cost of a large battle

Branch: `agent/render-submission-attribution`
Phase 1 head: `91519426` (`reverse_engineering/render_submission_attribution_phase1_20260823.md`)
Date: 2026-08-23
Workload: GOG Battlezone 98 Redux 2.2.301, `lcbench` four-team distant battle,
80 × `avtank`, 400 m, DX11 unless stated.

---

## 0. Summary

Phase 1 measured that roughly 7.9 ms of a 9.2 ms large-battle frame was neither
Ogre submission nor GPU execution, and that firing added about 5.8 ms over the
same scene idle. Phase 2 set out to attribute that time.

It is attributable, and the dominant owner was not a Battlezone subsystem. It
was OpenShim.

`GetHeadlightOgreApi()` in `src/patches/bzr_hooks.cpp` resolved twenty Ogre
entry points with a per-field `if (!field) field = GetProcAddress(...)` pattern
and no completion latch. One of the twenty mangled names was wrong —
`getCastShadows` is virtual on `Ogre::MovableObject`, so its decoration is
`?getCastShadows@MovableObject@Ogre@@UBE_NXZ`, not `...@@QBE_NXZ` — so that
field could never be filled and its lookup ran again on every call. The caller,
`HandleEmissionLightState`, is an inline detour inside the engine's
emission-light renderer loop, which iterates every active emission light once
per frame. A failing `GetProcAddress` therefore ran hundreds of times per frame,
and the loader's name search plus its error-reporting path accounted for
**45.4% of the main thread's CPU** in a firing frame.

Correcting the name and latching the resolution moves the firing frame from
**10.59 ms to 5.56 ms** with idle unchanged, measured with PresentMon and the
profiler disabled over eight interleaved runs per arm. That removes **5.03 ms of
the 7.18 ms firing-minus-idle delta — 70% of it.**

What remains after the repair is mostly rendering, not simulation: of the 1.93 ms
that firing still adds to an idle frame, 1.09 ms is inside
`Ogre::Root::renderOneFrame` and 0.39 ms is the world simulation tick.

A methodological finding of equal importance: **DWM present mode moves the same
scene between 3.4 ms and 9.6 ms at identical GPU-active time.** Captures in
`Composed: Flip` and `Hardware: Independent Flip` are not comparable, and some
Phase 1 frame times were almost certainly taken in the composed mode.

---

## 1. Instrument: a sampling CPU profiler

Phase 1 was instrumented with detours and two of them failed silently — an
isolation arm whose hooks were never installed, and a DX11 draw observer that
was reverted mid-frame. Both produced plausible numbers rather than errors.
Placing timers on native functions whose call hierarchy was not yet known would
have repeated that at a much larger scale, so Phase 2 used sampling instead.

`src/patches/native_cpu_sampler.cpp` (new, dormant unless
`OPENSHIM_PROFILE_NATIVE_CPU` asks for it):

* A dedicated thread wakes on a high-resolution waitable timer, suspends each
  process thread that consumed CPU in the previous enumeration pass, reads
  `Eip` plus a bounded frame-pointer chain, and resumes it.
* Nothing is allocated, locked, or logged inside the suspend window, and the
  frame walk only reads at or above `Esp` — the pages below `Esp` hold the stack
  guard page, and touching one from another thread would clear the guard bit
  without growing the stack.
* The interval is **jittered** ±50%. A fixed 1 ms request lands at the system
  timer granularity of about 1.5 ms, and a 9.2 ms battle frame is almost exactly
  six of those; a periodic sampler would keep landing at the same phase of every
  frame and would report whichever subsystem happens to run there. This was
  found and fixed during calibration, not assumed.
* Every thread's CPU total is recorded from `GetThreadTimes` whether or not it is
  stack-sampled, so "is the work on another thread" stays answerable without
  suspending a dozen parked workers at 700 Hz.

Attribution from raw addresses to functions is entirely offline
(`reverse_engineering/analyze_cpu_samples.py`), so the in-process cost stays
bounded and a capture can be re-analysed as naming improves.

### 1.1 Instrumentation health

Reported with every capture, and every number below comes from a capture that
passed these:

| Health metric | Firing capture, 80 craft |
|---|---|
| ticks requested / serviced | 25,951 / 25,951 |
| achieved sample rate | 741 Hz (1000 requested; the deficit is timer granularity) |
| suspend failures / context failures | 0 / 0 |
| samples | 39,920 across 2 busy threads |
| mean stack depth | 28.4 of a 48 cap |
| stacks truncated by the depth cap | 0.44% |
| leaf outside any known module | 9 of 39,920 |
| suspend window as a share of wall time | 2.42% |

A category reporting 0.00 ms here is a category with zero *leaf samples*, not a
category whose hook failed to fire — there are no per-category hooks to fail.

### 1.2 Symbolization, and how it is kept honest

| Module | Source | Notes |
|---|---|---|
| `battlezone98redux.exe` | Ghidra function bodies from the repo corpus | The shipped `battlezone98redux.pdb` is a 2016 build; its GUID does not match the executable and the analyzer rejects it. |
| `ntdll.dll` | exact-GUID `wntdll.pdb` already in the local symbol cache | 6,757 publics. GUID is checked; age deliberately is not, since a PDB's age counts writes. |
| `winmm.dll` (OpenShim) | its own build PDB, private `S_LPROC32` records | Publics alone are not enough: everything interesting in the shim has internal linkage. |
| `OgreMain.dll`, render systems, CRT | PE export table, **following incremental-link thunks** | Raw export addresses point at a 256 KB block of 5-byte `jmp` thunks 20 bytes apart. Without following them, all 9,194 Ogre exports collapse onto one name. |

Two symbolization traps were hit and fixed, and both would have produced
confident nonsense:

1. A 32-bit process reports its system modules as `C:\Windows\System32\...`, but
   that path is redirected to `SysWOW64` for the process and **not** for a
   64-bit analysis tool. Following it verbatim opens the 64-bit `ntdll`. The
   analyzer now rewrites the path and verifies the file's `SizeOfImage` against
   the loaded size.
2. Nearest-preceding-export naming is not identity. Before the thunk fix, the
   hot leaves resolved to plausible-looking string and heap functions, which
   would have supported an entirely fictitious "the frame is allocation-bound"
   conclusion. The finding that survived was the one confirmed by callers.

---

## 2. The reconstructed native frame

Anchors are Ghidra names; identifications come from string literals in the
decompiled bodies in the repo corpus.

```
battlezone98redux.exe!entry
└─ sub_618b10 / sub_618ff0 / sub_619fc0 / sub_618a40 ("Start of Game Menu Display")
   └─ sub_618270 ("ERROR, Device_Set_ShutDown has been called")
      └─ sub_618130   DoNextFrame   ("DoNextFrame: Quiting Game Due to Net Execute failure")
         ├─ sub_618060 → sub_62bc80 → sub_62bd40   object-class step ("Obj76\Classfnc.c")
         ├─ sub_617fa0
         ├─ sub_6175c0 → sub_6176a0                world simulation tick
         │   ├─ sub_617600 → sub_4b6f10 → sub_4b6db0 → sub_493ec0   ("ping.wav", "cgrowl.wav")
         │   └─ sub_4d4610                          per-object update loop
         │       │                                  (iterates a container, calls vtable+0x20
         │       │                                   on each object whose flag bit 2 is set)
         │       └─ sub_451f80                      per-object update
         │           ├─ sub_44e7f0                  renderer list — calls vtable+0x10 per entry
         │           │   └─ sub_44cb70              emission-light renderer loop
         │           │                              (calls Ogre::Light::setPosition /
         │           │                               setDirection per light)
         │           └─ sub_44e880                  second renderer list
         ├─ sub_682540                              render preparation ("low-noshadow")
         ├─ sub_6192b0                              Win32 message pump (PeekMessage/Dispatch)
         └─ sub_617b20                              frame statistics, then the Ogre render
             └─ OgreMain!Ogre::Root::renderOneFrame
                └─ Root::_updateAllRenderTargets
                   └─ D3D11RenderSystem::_updateAllRenderTargets
                      └─ RenderSystem::_updateAllRenderTargets
                         └─ RenderTarget::updateImpl → RenderTarget::_beginUpdate
```

**Limitation, stated rather than hidden:** the walk is frame-pointer based, so a
function compiled without an EBP frame is invisible and its children appear to
hang off its caller. `Ogre::Root::renderOneFrame` appearing directly under
`DoNextFrame` is an instance of this — `sub_617b20` is its real caller. This
affects the shape of the tree, never the leaf attribution or the totals.

---

## 3. Phase attribution: idle vs firing, before and after the repair

Inclusive share of main-thread samples, converted to ms/frame using the
profiler-disabled PresentMon frame time for the same scenario and present mode.

| Phase | idle before | idle after | firing before | firing after | moving after | native-AI after |
|---|---:|---:|---:|---:|---:|---:|
| frame time (PresentMon) | 3.433 | 3.424 | 10.587 | 5.357 | 3.988 | 8.494 |
| `DoNextFrame` | 3.42 | 3.41 | 10.57 | 5.34 | 3.97 | 8.45 |
| ├ `Ogre::Root::renderOneFrame` | 2.43 | 2.43 | 3.72 | 3.52 | 2.51 | 4.23 |
| ├ world simulation tick | 0.49 | 0.52 | **5.73** | 0.91 | 0.54 | 1.53 |
| │  ├ per-object update loop | 0.00 | 0.01 | **5.24** | 0.38 | 0.01 | 0.87 |
| │  │   └ emission renderer list | 0.00 | 0.00 | **4.91** | 0.06 | 0.00 | 0.07 |
| │  │   └ second renderer list | 0.00 | 0.00 | 0.28 | 0.28 | 0.00 | 0.34 |
| │  └ sub-update `sub_617600` | 0.46 | 0.49 | 0.47 | 0.50 | 0.50 | 0.63 |
| ├ object-class step `sub_618060` | 0.23 | 0.23 | 0.32 | 0.28 | 0.20 | 1.01 |
| ├ `sub_617fa0` | 0.05 | 0.05 | 0.30 | 0.21 | 0.05 | 0.19 |
| └ render preparation `sub_682540` | 0.03 | 0.02 | 0.19 | 0.18 | 0.02 | 0.51 |
| *(of which)* `GetProcAddress` | 0.00 | 0.00 | **4.80** | 0.00 | 0.00 | 0.00 |

Internal consistency checks that the table passes: idle `renderOneFrame` is
2.43 ms in both arms (the repair does not touch rendering); firing
`renderOneFrame` is 3.72 ms before and 3.52 ms after, i.e. unchanged within the
noise of two different capture sessions; and the removed `GetProcAddress` term
(4.80 ms) accounts for essentially all of the measured 5.03 ms frame-time
reduction.

### 3.1 Answering B — what caused the firing-minus-idle delta

| | before repair | after repair |
|---|---:|---:|
| firing − idle | **7.18 ms** | **1.93 ms** |
| owned by the shim's failing `GetProcAddress` | 4.80 ms (67%) | 0.00 ms |
| owned by `Ogre::Root::renderOneFrame` | 1.29 ms (18%) | 1.09 ms (56%) |
| owned by the world simulation tick | 5.24 ms* | 0.39 ms (20%) |
| remainder | — | ~0.45 ms |

\* the simulation tick figure before the repair *contains* the `GetProcAddress`
cost, because the detour sits inside it; the rows are nested, not additive.

After the repair the firing delta is majority **render** work, not simulation.

---

## 4. The defect, in detail

`src/patches/bzr_hooks.cpp`, `GetHeadlightOgreApi()`:

```cpp
static HeadlightOgreApi& GetHeadlightOgreApi()
{
    static HeadlightOgreApi api;
    if (!api.getDiffuse)
        api.getDiffuse = ResolveOgreProc<...>("?getDiffuseColour@Light@Ogre@@QBEABVColourValue@2@XZ");
    ...  // eighteen more
    if (!api.getCastShadows)
        api.getCastShadows = ResolveOgreProc<...>("?getCastShadows@MovableObject@Ogre@@QBE_NXZ");
    return api;                               //  ^^^ Q, but the method is virtual
}
```

Checked against the export table of the shipped `OgreMain.dll`: **19 of the 20
names resolve, one does not.** The missing one is `getCastShadows`, whose real
decoration is `?getCastShadows@MovableObject@Ogre@@UBE_NXZ`.

Call site: `HandleEmissionLightState`, invoked from an inline detour at
`0x0044CBD0`, inside `FUN_0044cb70` — the loop that walks every active
emission-light renderer once per frame calling `Ogre::Light::setPosition` and
`setDirection`. The feature is on by default; only
`OPENSHIM_DISABLE_EMISSION_LIGHT_FIX` turns it off.

That call frequency is why the cost is a *firing* cost. Parked craft have almost
no active emission lights, so idle frames barely enter the loop — which is
exactly what the measurements show (idle 3.433 ms before, 3.424 ms after).

Where the time went inside the loader, from the sampled call tree:

```
KERNEL32!GetProcAddress                                     42.95%
└─ KERNELBASE!GetProcAddressForCaller                       42.23%
   ├─ ntdll!LdrGetProcedureAddressForCaller+0x449           25.35%
   │  └─ ntdll!LdrpReportError → LdrpLogInternal            24.13%
   │     └─ LdrpWriteToSnapsBuffer → vsnprintf/vsnwprintf   23.18%
   └─ ntdll!LdrGetProcedureAddressForCaller+0x37c           16.34%
      └─ LdrpResolveProcedureAddress → LdrpGetProcedureAddress
         └─ LdrpLogInternal                                 15.13%
```

More than half the cost is the loader's **failure** path. `GlobalFlag` is 0 on
this machine and there is no Image File Execution Options entry for
`battlezone98redux.exe`, so the magnitude of the logging component may differ on
other machines. The defect — an unbounded retry of a lookup that can never
succeed, in a per-light-per-frame loop — does not.

### 4.1 The repair

1. Correct the mangled name to `?getCastShadows@MovableObject@Ogre@@UBE_NXZ`.
2. Latch resolution with a `static bool resolved`, so the block runs exactly once
   regardless of whether every name succeeds.
3. Audit and log the outcome once, naming any entry point that did not resolve.

Point 3 matters as much as points 1 and 2. The mis-mangled name survived because
nothing ever reported that it had failed; a null function pointer degraded a
headlight behaviour in silence. The log line now reads
`[HEADLIGHT] Ogre entry points resolved once: 20 of 20`, appears exactly once
per process, and would name any future regression.

Behaviour is otherwise unchanged: the other nineteen pointers already resolved
on the first call, and `api.getCastShadows` is read at exactly one site — a
diagnostic trace line gated behind the headlight light-trace flag.

### 4.2 Preventing a recurrence, not just fixing the instance

Repairing the call site leaves the shape that produced it intact. A survey found
the retry shape (`if (!field) field = ResolveOgreProc<T>(...)`) at exactly 20
sites, all inside `GetHeadlightOgreApi`, so no other call site currently has the
bug — but the next one written would.

Two changes push the guarantee down to where it cannot drift:

**The resolver caches failure.** `ResolveOgreProcRaw` memoises both outcomes, so
a name that does not resolve is looked up once for the lifetime of the process
no matter how the caller is written, and logs one warning naming it. A miss is
only cached once `OgreMain.dll` is actually loaded — a lookup made before the
module exists is an answer about timing, not about the name, and must not be
recorded as one.

**A startup sweep runs before any frame.** `VerifyExpectedOgreExportsIfPossible`
resolves thirteen hot-path exports plus the twenty light entry points as soon as
OgreMain is present, from the existing deferred-hook retry pass. A bad
decoration is now one clear line in the log at startup rather than a runtime tax
discovered by a profiler. Verified live:

```
[HEADLIGHT] Ogre entry points resolved once: 20 of 20
[OGRE-EXPORTS] Startup verification: 13 of 13 hot-path exports resolved
```

Each appears exactly once per process, on the patch thread, with no warnings.

The sweep's list is deliberately short and can drift from the full set of names
the shim uses; when it does, the consequence is only that those names are
reported later by the resolver rather than at startup. The resolver's warning is
the drift-proof half.

Cost, measured the same way as the repair itself (DX11 firing, interleaved,
profiler and sampler off): **5.303 → 5.267 ms, −0.7%, inside the run-to-run
noise** (sd 0.025–0.036). The added mutex is taken once per distinct name, not
per call.

---

## 5. Frame-time result (profiler disabled, external PresentMon)

Method: `reverse_engineering/run_shim_ab_presentmon.ps1` swaps only `winmm.dll`
between arms, verifies the deployed SHA-256 against the arm before each run, and
**interleaves** arms (A B A B …) so machine drift cannot land entirely in one of
them. Frame times come from PresentMon v1 ETW with the Ogre profiler and the CPU
sampler both off.

Two sessions, 4 interleaved repeats each, `Hardware: Independent Flip` only:

| scenario | arm | runs | mean ms | sd | drift over 15 s | fps |
|---|---|---:|---:|---:|---:|---:|
| idle | before | 8 | 3.42 | 0.08 | +0.03 | 292 |
| idle | after | 7 | 3.42 | 0.06 | +0.05 | 293 |
| firing | before | 6 | 10.60 | 0.15 | **+6.21** | 94 |
| firing | after | 7 | 5.51 | 0.12 | **+0.31** | 181 |

**firing: −5.03 ms, −47.5%. idle: no change.** The drift column is discussed in
§8 — it is not noise, it is the mechanism.

Raw per-run values and per-run present mode are in
`reverse_engineering/phase2_nonrender/presentmon_shim_ab3.csv`.

### 5.1 Present mode is a confound and must be reported

The first A/B session produced a 36% improvement that was partly an artifact.
Three runs landed in `Hardware: Independent Flip` and the rest in
`Composed: Flip`, and the same scene measures:

| present mode | idle | firing (before) | GPU active |
|---|---:|---:|---:|
| Hardware: Independent Flip | 3.39 ms | 10.18 ms | 1.82 ms |
| Composed: Flip | 9.62 ms | 12.32 ms | 1.94 ms |

Identical GPU-active time, identical spawn count, 6 ms of difference. The
benchmark runner now asserts the game window's foreground at `warmup-begin`, and
`reverse_engineering/analyze_presentmon_runs.py` reports present mode per run and
**refuses to average across modes**.

This applies retroactively: Phase 1's 9.23 ms firing frame is consistent with a
composed-mode capture, and its absolute frame times should be treated as
mode-unqualified.

---

## 6. Scenario decomposition (post-repair, 80 craft, DX11)

PresentMon, profiler and sampler off, `Hardware: Independent Flip` only.
`fourteam_move` is new in this phase: the same four-team layout ordered to
advance across its own front but never given a target, so movement cost is
separable from weapon cost.

| scenario | ms/frame | sd | − idle | what it adds |
|---|---:|---:|---:|---|
| `fourteam` (idle) | 3.424 | 0.073 | — | 80 craft rendered, parked, no orders |
| `fourteam_move` | 3.988 | 0.105 | +0.564 | movement, physics, terrain following |
| `fourteam_fire` | 5.357 | 0.122 | +1.933 | + weapon discharge, ordnance, impacts |
| `fourteam_ai` | 8.494 | 1.913 | +5.070 | + native target search, fire control, damage, destruction |

Two things follow. Movement is cheap — 0.56 ms for 80 craft, 7 µs each.
And the realistic case is the expensive one: letting the native AI fight costs
2.6× what the harness's scripted `FireAt` loop costs, because the harness only
discharges weapons while the AI also searches for targets, manoeuvres, takes
damage and destroys craft. `fourteam_ai` is also the only scenario with high
run-to-run variance (sd 1.9 ms), which is expected — it is the only one whose
outcome is not deterministic.

The emission-light defect tracked exactly this ordering. Its share of main-thread
samples before the repair:

| scenario | `GetProcAddress` inclusive, before | after |
|---|---:|---:|
| idle | 0.07% | 0.04% |
| moving | 0.04% | 0.05% |
| firing | 45.36% | 0.02% |
| native AI | 29.59% | 0.03% |

Moving craft do not enter the emission-light loop at all. **Weapon discharge is
what creates the active emission lights**, which is why this was a combat-only
cost and why it never showed up in a quiet scene.

## 7. Unit-count scaling

Post-repair, DX11, 400 m, independent flip. "− idle" subtracts the idle frame
time at the *same* population, so it isolates the cost of the activity rather
than the cost of drawing more craft.

| scenario | 20 craft | 40 craft | 80 craft | shape |
|---|---:|---:|---:|---|
| idle, absolute | 2.214 | 2.343 | 3.424 | superlinear above 40 |
| firing − idle | 0.304 | 0.938 | 1.933 | ~linear above 40 (2.06× for 2× units) |
| native AI − idle | 1.878 | 2.820 | 5.070 | ~linear, slightly sublinear (1.80× for 2× units) |
| firing, µs per craft | 15.2 | 23.5 | 24.2 | flat above 40 |
| native AI, µs per craft | 93.9 | 70.5 | 63.4 | falling |

**No pathological scaling remains in combat.** Per-craft combat cost is flat or
falling as the battle grows, which rules out an O(N²) target-search or
collision-broadphase term at these populations — the shape that would have
explained a "CPU wall" algorithmically.

The wall was not algorithmic. It was a fixed per-call cost multiplied by a
quantity that is linear in the number of *shooting* craft, which is why it felt
like a scaling problem.

The one nonlinearity left is on the idle side: the second 40 craft cost 1.08 ms
where the first 20 cost 0.13 ms. That is render-side (idle frames are 71%
`renderOneFrame`) and belongs to the Phase 1 shadow-caster/submission material,
not to this phase.

## 8. The cost is not stationary — it grows during a battle

The A/B analyzer now reports **drift**: the mean of the capture's last whole
second minus the mean of its first. Over a 15 s firing window:

| scenario | arm | first second | last second | drift |
|---|---|---:|---:|---:|
| idle | before | 3.4 | 3.4 | +0.03 |
| idle | after | 3.4 | 3.4 | +0.05 |
| firing | before | 7.6 – 9.0 | 13.9 – 17.8 | **+6.21** |
| firing | after | 5.3 – 5.5 | 5.5 – 6.0 | **+0.31** |

Before the repair the firing frame nearly doubles over fifteen seconds of
sustained combat. After it, the frame is flat.

This is the mechanism showing itself. The cost was one failing lookup per
*active emission light*, and active emission lights accumulate while a battle is
being fought — ordnance in flight and impact lights build up faster than they
expire. So the penalty was proportional to how long the fight had been going,
which is exactly what "large missions hit a CPU wall" feels like from inside the
game, and it is why a short capture understates it.

It also means the headline number depends on window length. All figures here use
a 15 s measurement window, stated so they can be reproduced.

## 9. DX9 confirmation

The repaired code resolves Ogre entry points and is invoked from the engine's
emission-light loop, not from a render system, so the mechanism should be
backend-independent. It is.

DX9, `fourteam_fire`, 80 craft, 400 m, two sessions, independent flip only:

| arm | runs | mean ms | sd | median | drift |
|---|---:|---:|---:|---:|---:|
| before | 5 | 11.59 | 0.83 | 10.76 | **+7.34** |
| after | 4 | 7.67 | 2.96 | 6.19 | **+0.59** |
| after, excluding one anomalous run | 3 | 6.20 | 0.47 | 6.19 | +0.44 |

**DX9: −5.4 ms, −46% (excluding the anomaly), against −5.03 ms and −47.5% on
DX11.** The drift signature separates the arms as cleanly as it does on DX11.

The excluded run is `phase2_dx9_ab/after_r1` at 12.06 ms. It is excluded on an
objective marker rather than because it is inconvenient: every other `after` run
in either backend is flat *and* fast, and every `before` run climbs steeply; that
run is flat *and* slow (drift +1.4, level ~12 ms throughout), which is the
signature of a machine disturbance during the run rather than of the workload.
It is reported here and retained in the raw CSV. One further DX9 `after` run
(`phase2_dx9_ab2/after_r1`) did not reach `benchmark-end` at all
(`completed: false`, exit code 1) and was dropped automatically by the
minimum-frame rule.

## 10. Profiler perturbation, regression and visual validation

### Sampler perturbation

The brief requires final frame-time claims to come from an external,
profiler-disabled measurement. They do — every number in §5 through §9 is
PresentMon with both the Ogre profiler and the CPU sampler off.

Measured perturbation, same scenario and build:

| configuration | ms/frame |
|---|---:|
| sampler off (§5, n=4) | 5.559 |
| sampler off (§6, n=3) | 5.357 |
| sampler on, 1 kHz requested / 741 Hz achieved | 5.803 |

**The sampler costs roughly +0.34 ms, about 6% of the frame** — larger than the
2.42% suspend window it reports for itself, the remainder being scheduling
disturbance. Sampled percentages are therefore used for attribution only, never
as a performance result, and the ms/frame figures in §3 are percentages
multiplied by *profiler-disabled* frame times.

### Regression checks

* Shim logs across the post-repair captures: no errors, no exceptions, no access
  violations, no stale-object diagnostics. The only error-level line in either
  arm is the pre-existing `cGogInterface::preinitGoGInterface ... Could not
  retrieve GalaxyPeer library location`, present identically before and after
  and unrelated to this work.
* The new one-shot log line reads
  `[HEADLIGHT] Ogre entry points resolved once: 20 of 20` and appears exactly
  once per process, confirming both that the latch works and that the corrected
  mangled name resolves.
* Both backends, all four scenarios, and populations 20/40/80 reached
  `benchmark-end` except the one DX9 run noted in §9.
* The pre-existing `OPENSHIM_DISABLE_EMISSION_LIGHT_FIX` opt-out still disables
  the feature this code belongs to.

### Visual validation

`reverse_engineering/snapshots/phase2_visuals_near/` holds four frames per arm of
the same firing scenario at 100 m, captured windowed with the profiler disabled
and with the deployed binary's SHA-256 verified for each arm. The frames are
equivalent: same terrain, same craft formation, same weapon effects, same HUD,
same lighting.

**This visual check is weak and should be read as such.** The benchmark camera is
partly occluded by terrain at both 100 m and 400 m, so only part of the battle is
in frame. The stronger argument is structural: nineteen of the twenty entry
points already resolved on the first call before the repair, so their values are
unchanged; the twentieth, `getCastShadows`, is read at exactly one site —
`LogHeadlightLightParameters`, a diagnostic gated behind
`[Diagnostics] HeadlightLightTrace`. Correcting it changes what that trace line
prints and nothing else.

A first attempt at this validation produced two directories that both silently
used the *pre-fix* binary, because the `Copy-Item` for the second arm failed
while the game still held `winmm.dll` open and the loop continued anyway. The
invalid capture was deleted and the harness now retries the swap and verifies the
deployed hash before each arm. Recording it here because a silently-wrong A/B
arm is the exact failure this programme has now hit three times.

## 11. Rejected hypotheses and instrumentation defects

### Hypotheses tested and rejected

**"The frame is heap-allocation bound."** The first symbolized pass put 50% of
main-thread self time in `ntdll`, with leaves naming `RtlAllocateHeap`,
`RtlRbRemoveNode` and `RtlDeleteElementGenericTableAvlEx` — a textbook
malloc/free-bound game loop, and three independent-looking corroborations of it.
All of it was an artifact of nearest-preceding-export naming: the export table
addresses were incremental-link thunks, so every hot address resolved against
whatever export happened to precede a 6.8 MB gap. Following the thunks and then
resolving the callers showed the real path was `GetProcAddress`. **No conclusion
was drawn from a leaf name until its callers agreed with it**, and none should
be.

**"The winmm proxy resolves its forwards per call."** Inspected: the `FORWARD`
macro caches in a zero-initialized function-local static, and the legacy naked
exports jump through slots filled once in `LoadRealWinmm`. Not the cause.

**"`ResolveOgreProc` in the chunk-proxy render path is the storm."**
Those call sites are dynamic initializers of function-local statics, so MSVC
runs them once behind a guard. Not the cause.

**"Loader Snaps are enabled on this machine, so the magnitude is local."**
`GlobalFlag` is 0 machine-wide and there is no Image File Execution Options entry
for `battlezone98redux.exe`, yet `LdrpLogInternal` and its string formatting are
demonstrably on the sampled stacks. The mechanism for that logging being active
is **unresolved**, and it is recorded here as a caveat on the *magnitude*, not on
the defect. A machine where that path is cheaper would see a smaller win from
the same repair.

### Instrumentation defects found and corrected during this phase

1. **A periodic sampler aliases against the frame.** A 1 ms request lands at
   ~1.5 ms of timer granularity, and a 9.2 ms frame is almost exactly six of
   those. Fixed with ±50% interval jitter before any attribution was taken.
2. **The stack-depth cap silently truncates the root, not the leaf.** At depth 24
   it capped 44% of stacks, destroying the top of the hierarchy this phase
   exists to reconstruct. Raised to 48.
3. **A thread-tracking cap of 128 was being pinned**, which would have excluded
   any thread that became busy after the cap was reached. Raised to 512.
4. **The 64-bit analysis tool read the 64-bit `ntdll`** for a 32-bit capture,
   because `System32` is only redirected to `SysWOW64` for the process. Now
   rewritten and verified against the loaded `SizeOfImage`.
5. **A PDB's age is not part of its identity for matching purposes** — it counts
   writes and runs ahead of the age recorded in the module. Matching on GUID+age
   silently rejected the correct symbols; GUID only is correct.
6. **DWM present mode was uncontrolled**, and it moves the same scene by 6 ms.
   The runner now asserts the game window's foreground before the measurement
   window and the analyzer refuses to average across modes.

Every one of these produced a plausible number rather than an error, which is
the same failure class Phase 1 hit twice.

## 12. Remaining unattributed time and ranked next candidates

Post-repair firing frame, 5.357 ms, DX11, 80 craft:

| | ms | share |
|---|---:|---:|
| `Ogre::Root::renderOneFrame` | 3.52 | 65.7% |
| world simulation tick | 0.91 | 16.9% |
| object-class step `sub_618060` | 0.28 | 5.2% |
| `sub_617fa0` | 0.21 | 4.0% |
| render preparation `sub_682540` | 0.18 | 3.3% |
| named total | 5.10 | 95.2% |
| unnamed children of `DoNextFrame` + outside it | 0.26 | 4.8% |

The 4.8% remainder is spread across children below the 2.5% pruning threshold
(message pump, frame statistics, audio); none of it is a single hidden term.

### Ranked candidates, by measured ceiling

| # | Candidate | Measured ceiling | % of frame | % of firing delta | Risk |
|---|---|---:|---:|---:|---|
| 1 | Native AI engagement cost | 5.07 ms over idle at 80 craft | 60% of an AI frame | n/a (own workload) | High — it is gameplay behaviour |
| 2 | `Ogre::Root::renderOneFrame`, idle floor | 2.43 ms | 71% of an idle frame | — | Phase 1 territory; submissions are only ~1.3 ms of it |
| 3 | Idle 40→80 nonlinearity | 1.08 ms for the second 40 craft | 32% of an 80-craft idle frame | — | Render-side; shadow casters |
| 4 | World simulation tick under fire | 0.39 ms over idle | 7% | 20% | Medium |
| 5 | Second renderer list `sub_44e880` | 0.28 ms | 5% | 15% | Low, but small |

**Recommendation.** Candidate 1 is the only remaining multi-millisecond term and
it is the one a player actually experiences, since real missions are fought by
the native AI rather than by a scripted `FireAt` loop. Its post-repair
composition is already visible in §3: of the 5.07 ms it adds to an idle frame,
1.80 ms is inside `renderOneFrame`, 1.01 ms is the world simulation tick, 0.78 ms
is the object-class step and 0.49 ms is render preparation. That spread means it
is *not* one hot loop, and a Phase 3 aimed at it should expect to attribute
several moderate terms rather than find another single defect.

Candidates 2 and 3 are render-side and belong with the Phase 1 material.

---

## 13. The four questions, answered

**A. Where does the ~7.9 ms of non-submission, non-GPU frame time go?**

It was never one thing, and the largest single piece was not Battlezone. In a
firing frame measured at 10.59 ms:

* 4.80 ms — OpenShim's `GetHeadlightOgreApi()` retrying a `GetProcAddress` that
  could never succeed, once per active emission light per frame, plus the
  loader's error-reporting path for it.
* 3.72 ms — `Ogre::Root::renderOneFrame`, of which Phase 1 attributed ~1.3 ms to
  Ogre submissions and the rest to culling, queue building and present.
* ~0.9 ms — the world simulation tick excluding the defect.
* ~1.1 ms — object-class processing, render preparation, message pump, audio,
  frame statistics.

After the repair the same frame is 5.56 ms and is 66% `renderOneFrame`.

**B. What caused the ~5.79 ms firing-minus-idle delta?**

Measured here as 7.18 ms (Phase 1's 5.79 ms was taken over a shorter window and
in an unqualified present mode). **67% of it was the shim defect.** It presented
as a combat cost because weapon discharge is what creates active emission
lights: idle and *moving* craft do not enter that loop at all. After the repair
the delta is 1.93 ms, of which 56% is `renderOneFrame` and 20% is the world
simulation tick.

**C. Is the dominant remaining cost legacy simulation, Redux render
preparation, or a combination?**

Neither of the two the question anticipated — the dominant cost was shim
overhead. What remains is **predominantly rendering**: 2.43 ms of a 3.42 ms idle
frame and 3.52 ms of a 5.36 ms firing frame are inside
`Ogre::Root::renderOneFrame`. Legacy simulation is 0.52 ms idle and 0.91 ms
firing. Redux render preparation outside Ogre (`sub_682540`, the "low-noshadow"
scheme step) is 0.02–0.18 ms and is not a significant term at these populations.

The exception is the native-AI workload, where the extra 5.07 ms over idle
divides roughly 35% rendering, 20% simulation, 15% object-class processing and
10% render preparation — genuinely a combination, and no single hot loop.

**D. Which subsystem offers the largest realistic optimization opportunity?**

Now that the defect is repaired: **native AI engagement**, at 5.07 ms over idle
for 80 craft and roughly linear in population. It is the only remaining
multi-millisecond term and it is the one real missions actually incur.

It should **not** be optimized on that basis alone. It is an aggregate, not a
subsystem: the 5.07 ms divides roughly 1.80 ms rendering, 1.01 ms world
simulation, 0.78 ms object-class processing and 0.49 ms render preparation, so
there is no single hot loop to attack and no evidence yet that any of the four
is pathological rather than simply necessary.

The next phase should therefore attribute those four terms separately and ask,
of each: is this genuinely necessary tactical simulation, is it repeated or
redundant work, and does it scale with active combatants, with weapons and
projectiles in flight, or with candidate targets? The scaling data here says the
aggregate is roughly linear in craft count, which is consistent with necessary
per-combatant work and inconsistent with a combinatorial blow-up — but it does
not separate "linear in combatants" from "linear in projectiles", because in
this benchmark those two move together.

That is the Phase 3 question. Nothing in it has been started.

---

## 14. Reproducing this

```bash
# Build and deploy
MSBuild BZROpenShim.vcxproj /p:Configuration=Release /p:Platform=Win32
```

```powershell
# Attribution capture (sampler on; frame times from these runs are NOT evidence)
.\reverse_engineering\run_live_combat_benchmark.ps1 -Renderer DX11 `
  -Scenario fourteam,fourteam_move,fourteam_fire,fourteam_ai -Count 80 `
  -Distance 400 -WarmupSeconds 6 -MeasureSeconds 20 -ProfilerDisabled `
  -SampleCpu -KillExisting -OutputRoot .\reverse_engineering\snapshots\phase2
```

```bash
python reverse_engineering/analyze_cpu_samples.py <run>/cpu_samples.bin \
  --bzlogger <run>/BZLogger.slice.txt \
  --functions reverse_engineering/repo_corpora/bzr_gog_best_effort/inventory/functions.csv \
  --tree 2.5
```

```powershell
# Frame-time A/B between two shim builds (profiler and sampler off)
.\reverse_engineering\run_shim_ab_presentmon.ps1 `
  -Arm "before=<path>\winmm.dll","after=<path>\winmm.dll" -Repeats 4
```

```bash
python reverse_engineering/analyze_presentmon_runs.py <output-root>
```

### Artifacts

Raw data preserved under `reverse_engineering/phase2_nonrender/`:

| File | Contents |
|---|---|
| `presentmon_shim_ab3.csv` | the headline DX11 A/B, per run, with present mode and drift |
| `presentmon_scenarios_postfix.csv` | idle / moving / firing / native AI at 80 craft |
| `presentmon_scaling_postfix.csv` | 20 / 40 craft for the scaling table |
| `presentmon_dx9_ab.csv`, `presentmon_ai_ab.csv` | DX9 and native-AI A/B arms |
| `presentmon_perturbation.csv` | the sampler-on control |
| `samples_<scenario>_<arm>_self.csv` | per-symbol self time, 8 captures |
| `samples_<scenario>_<arm>_inclusive.csv` | per-symbol inclusive time, 8 captures |

The two `samples_*` families are trimmed to symbols with at least three samples
(77,209 rows to 23,318). The discarded tail is one- and two-sample singletons,
which are below the resolution of a 741 Hz capture; re-running the analyzer on
the preserved `cpu_samples.bin` reproduces them in full.
| `near_{prefix,postfix}_{0..3}.jpg` | visual regression frames, both arms |

Full captures, including the raw `cpu_samples.bin` files, remain under
`reverse_engineering/snapshots/phase2_*/` and are not committed.

---

## 15. Ownership summary

| Category | before, firing ms/frame | after, firing ms/frame | % of the 7.18 ms firing delta (before) | Opportunity | Risk |
|---|---:|---:|---:|---|---|
| OpenShim emission-light `GetProcAddress` | 4.80 | 0.00 | 67% | **taken** | none — defect repair |
| `Ogre::Root::renderOneFrame` | 3.72 | 3.52 | 18% | Phase 1 material; submissions ~1.3 ms of it | medium |
| World simulation tick (excl. defect) | ~0.9 | 0.91 | 5% | small | medium |
| Object-class step `sub_618060` | 0.32 | 0.28 | 1% | small | medium |
| `sub_617fa0` | 0.30 | 0.21 | 1% | small | unknown |
| Redux render preparation `sub_682540` | 0.19 | 0.18 | <1% | not significant at these populations | low |
| Second renderer list `sub_44e880` | 0.28 | 0.28 | 4% | small | low |
| Unnamed remainder | ~0.3 | 0.26 | 3% | none identified | — |
| **Native AI engagement** *(separate workload)* | — | **+5.07 over idle** | — | largest remaining term | high — gameplay behaviour |

No further optimization is proposed in this phase. The one change made here was
a defect repair whose target was quantitatively identified (45.4% of the main
thread), whose payoff is substantial (−5.03 ms, −47.5% on the firing workload),
whose visual and gameplay semantics are unchanged, and which is covered by the
pre-existing `OPENSHIM_DISABLE_EMISSION_LIGHT_FIX` opt-out for the feature it
belongs to.
