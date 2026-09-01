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
