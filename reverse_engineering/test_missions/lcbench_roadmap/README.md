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

