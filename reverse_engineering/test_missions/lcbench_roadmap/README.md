# lcbench roadmap qualification overlay

This directory is a purpose-specific overlay for the existing `lcbench`
mission. It does not contain or replace the world/terrain assets. The runner
temporarily deploys `rmpilot.lua` as `addon/lcbench/lcbench.lua`, installs the
selected short-named ODF fixtures, launches `lcbench.bzn`, captures evidence,
and restores the exact prior live files.

## Pilot hardpoint ordering matrix

All pilot fixtures are based on the shipped `aspilo.odf` values. Only the
section/key placement described below changes.

| Case | File | Deliberate delta |
|---|---|---|
| control | `pctl.odf` | Stock-valid ordering |
| craft | `pcrft.odf` | A `CraftClass` section captures the hardpoint pair before `PersonClass` |
| after | `paftr.odf` | The hardpoint pair occurs after `PersonClass` begins |
| reverse | `prevs.odf` | `PersonClass` precedes `CraftClass`; hardpoint pair is in the latter |
| partial | `ppart.odf` | Stock section ordering, but only the hardpoint name is present |

Run the matrix from the repository root:

```powershell
pwsh -File reverse_engineering/run_lcroad_pilot.ps1
```

Run one arm or change the repeat count:

```powershell
pwsh -File reverse_engineering/run_lcroad_pilot.ps1 -Cases pcrft -Repeats 3
```

The default evidence directory is outside `addon`, under
`openshim_test_results/lcroad_pilot_<timestamp>` in the GOG install. Every arm
contains a manifest, `BZLogger.txt`, `openshim.log`, `openshim_crash.log` when
present, and any new `openshim_crash_*.dmp`.

## Neutral Attack command matrix

`rmneut.lua` creates a player-team wingman, team-0 neutral fighter, and an
ordinary enemy control at separate `GetPositionNear` locations. It exercises
four directed Lua `Attack` arms (`n2p`, `a2n`, `a2e`, `a2f`) and records command,
target, health, ammo, and `GetWhoShotMe` state every half-second.

```powershell
pwsh -File reverse_engineering/run_lcroad_neutral.ps1
```

This qualifies the Lua/native AI command route. A human-issued UI Attack order
is intentionally documented as a separate manual evidence gate.

## AIP mixed stock/custom producer matrix

`rmaip.lua` builds an AI base for team 2, installs one arm's `.aip`, and counts
what the AI actually produces. `svfigh` is the stock unit; `mxfigh` is a
value-identical clone (`baseName = "svfigh"`, same `scrapCost`, `buildTime`,
`maxHealth`) differing only in ODF identity, so any preference between them
cannot be explained by cost, role, or durability.

Both producers carry an **identical** build menu — the full stock recycler list
plus `mxfigh` — so producer ODF identity is the only variable across arms.

| Case | Producer | Offense account |
|---|---|---|
| `sps` | `svrecy` (override) | stock only |
| `spc` | `svrecy` (override) | custom only |
| `spms` | `svrecy` (override) | mixed, stock first |
| `spmc` | `svrecy` (override) | mixed, custom first |
| `cps` | `mxrecy` | stock only |
| `cpc` | `mxrecy` | custom only |
| `cpms` | `mxrecy` | mixed, stock first |
| `cpmc` | `mxrecy` | mixed, custom first |
| `mp2` | both | mixed, stock first |
| `ccak` | `svrecy` | **CONTROL**: shipped `ccatank.aip` verbatim |

```powershell
pwsh -File reverse_engineering/run_lcroad_aip.ps1 -Cases cpms -Repeats 1
```

Always run `ccak` alongside a negative result. It is the known-good control: it
produced 4 `svfigh` plus 20 other units, which is what proves the harness
itself can drive AI production before any arm's zero is believed.

### Harness requirements discovered the hard way

Each of these independently reduces every arm to a build count of zero, with no
error message anywhere:

1. **`SetAIControl(2, true)` must be called at chunk scope**, not from `Start()`.
   Strategic AI is configured immediately after the chunk runs; a later call is
   too late to start the AI and the reference warns it can crash the game.
2. **Never re-issue `Deploy()` (or any order) every frame.** It restarts the
   5-second `timeDeploy` animation forever, so the producer never finishes
   deploying and freezes. Retries here are throttled to 15s.
3. **A producer only deploys on a geyser.** This applies to the recycler as well
   as the munitions factory. `lcbench` ships **no** geysers, so the fixture
   creates one per producer and spawns the producer directly on it.
4. **Raise the caps before filling them.** `SetScrap`/`SetPilot` are clamped to
   the team maximum, so without `SetMaxScrap`/`SetMaxPilot` first, scrap pins at
   40 and the team has no pilots to crew anything.
5. **A stripped-down AIP parses but produces nothing.** A single-account file
   with all priorities zeroed is silently inert. The full
   Slush/Defense/Offense shape plus the shipped scheduler values is load-bearing
   and must not be trimmed; these arms copy them from `ccatank.aip`.
6. **`CreateObject` and `AddObject` both fire for the same object.** Counting
   both double-counts every build, so the observer de-duplicates by handle.

### Reading a result

`stock=` / `custom=` in the `COMPLETE` line are the build counts. Note that
`other=` rising and scrap/pilots being consumed is itself proof the AI is
producing, even when both units under test are zero.

A run that does not reach `RESULT` is **not** a result. The simulation stalls
whenever the game window loses focus — the log simply goes silent while the
process keeps rendering — so re-run that arm rather than recording its zero.

### Crash signals

`C:\BZDumps` receives one WER dump per *dead process*, including every normal
harness timeout kill, so a dump there is **not** evidence of a crash. The real
signals are `looksLikeCrash` in the manifest: a shim dump in the game's `logs\`
folder, or an early exit with no `RESULT` marker.

### Same-origin pair controls (`ss2`, `cc2`)

The working hypothesis is that the AI will not build a **mix of stock and
custom** units, rather than that it prefers custom units specifically. The first
completed arm supports this: `spmc` listed the custom unit at the *higher*
priority and the AI still built 3 stock and 0 custom.

The mixed arms alone cannot distinguish "will not mix two origins" from "will
not build two units out of one account". These controls close that gap by
pairing units of the *same* origin, on the same producer as the `sp*` arms:

| Arm | Offense account | Asks |
|---|---|---|
| `ss2` | `svfigh` + `svturr` | do two **stock** units both build? |
| `cc2` | `mxfigh` + `mxturr` | do two **custom** units both build? |

`mxturr` is a value-identical clone of `svturr`, matching `mxfigh`/`svfigh`.

Read it as: if both same-origin pairs build out, but every stock+custom pair
yields one origin and a zero, the defect is precisely the **origin boundary**.
If `ss2` also builds only one, the defect is about accounts rather than origin
and the whole framing changes.

Note the AI already builds `svscav`, `svcnst`, `svturr` and `svfigh` together in
a single run, so it plainly does mix unit *types*. `Defense` was moved off
`svturr` onto `sprepa` so it cannot contaminate the `ss2` count.

## Result: the defect is confined to AIP selection

Three independent facts localize it:

1. **The custom ODF is valid.** `ODFPROBE` spawns each clone directly every run:
   `mxfigh valid=true class=wingman`, `mxturr valid=true class=turrettank`.
2. **The producer builds it on command.** With the Offense account neutered to
   `NUMBER_TO_HAVE 0`, so nothing is attributable to the AIP:

   | Arm | Command | Built |
   |---|---|---|
   | `blds` | `Build(producer, "svfigh")` | 3, at T+50/68/86 |
   | `bldc` | `Build(producer, "mxfigh")` | 3, at T+50/68/86 |

   Symmetric to the frame. The producer has no objection to the custom ODF.
3. **No AIP account ever builds it.** Zero custom units when requested alone
   (`spc`, `cpc`), paired with another custom (`cc2`), mixed with stock in either
   priority order (`spms`, `spmc`, `cpms`, `cpmc`), from either producer
   identity, and at either end of the producer's build menu (`posc`).

So the unit is constructible, the producer will construct it, and the AI will
not ask for it. **Instrument the AIP account-to-ODF resolution step**, not the
producer, the ODF loader, or the build list.

### `Build()` is dropped while the producer is busy

Every arm's first command at T+20 lands with `busy=true` and produces nothing;
every later command lands with `busy=false` and produces a unit 12s later. This
is why the first direct-build pass — which issued the command only once, at
T+20 — wrongly appeared to show the custom unit being refused. Check `IsBusy`
and re-issue, and never conclude a refusal from a single dropped order.

### Correction to the reported bug

The roadmap records this as the AI building *only the custom* units. What
reproduces here is the exact opposite: the AI builds *never the custom* units.
The direction should be re-confirmed against the original report's setup before
any selection routine is patched.
