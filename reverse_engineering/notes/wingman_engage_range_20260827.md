# Wingman engage-range runtime qualification (2026-08-27)

## Scope

This qualification covers the `CalcRange(Craft)` extension for authored
`engageRangeAI` and `weaponRangeMinAI`. It does not change or hook
`OffensiveProcess::FriendFollowVsAttack`, `OffensiveProcess::WaitVsAttack`,
target-reacquisition cadence, scanner range, or player weapon behavior.

The tested executable was the GOG 2.2.301 baseline with SHA-256
`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`.
The candidate was built as Release|Win32 and deployed by
`scripts/Deploy-OpenShim.ps1`.

## Safe harness

The local-only driver dot-sourced `reverse_engineering/BZRHarness.ps1`, set
`BZR_FORCE_WINDOWED=1`, refused pre-existing game processes, and closed every
launched process through `Stop-BZRGame -Id`. It never used forced process
termination. `OPENSHIM_TRACE_AI_RANGE=1` captured the stock outputs and applied
policy.

The final evidence directories are:

- turret regression: `%TEMP%\openshim-wingman-range-20260827-035326`
- 15-second range/standoff and state-gate matrix:
  `%TEMP%\openshim-wingman-range-20260827-035844`
- aimed 15-second range/standoff matrix:
  `%TEMP%\openshim-wingman-range-20260827-040126`
- extended 30-second stock/authored pair:
  `%TEMP%\openshim-wingman-range-20260827-040313`

All completed cases reached `benchmark-end`, produced no `WINGRANGE ERROR`, and
the game exited normally through the harness.

## Resolver and hook identity

Every run emitted the same resolver result:

```text
[RESOLVE] name="CalcRange(Craft)" matches=1 scan=0x00466BE0
fallback=0x00466BE0 used=0x00466BE0 source=scan agree=yes
```

The installed detour retained the independent nine-byte entry-prologue check.
The declarative identity note ties the target to the five-output call from
`UnitTask::Execute` at `0x006002A0`, not merely to the unique signature.

## Live native outputs

The same live hook recorded the stock weapon-aware values and the final policy:

| Case | ODF | Stock close/range | Authored policy | Final close/range |
| --- | --- | --- | --- | --- |
| stock turret | `avturr` | `0 / 155` | none | `0 / 155` |
| authored turret | `wrturr` | `0 / 155` | `engageRangeAI=240` | `0 / 240` |
| stock wingman | `wrbase` | `5 / 149` | none | `5 / 149` |
| authored wingman | `wreng` | `5 / 149` | `engageRangeAI=240` | `5 / 240` |
| authored standoff | `wrmin` | `5 / 149` | `engageRangeAI=240`, `weaponRangeMinAI=100` | `100 / 240` |

`wrbase` caused no tuning load or range-policy row. This is the stock
pass-through control. `wrturr`, `wreng`, and `wrmin` were resolved from the
addon's normal `ODF` directory and logged their authored fields before the live
consumer logged the applied result.

## Controlled behavior

The wingman fixture first received a real hit from an enemy `svtank`. The
activation rows recorded `lastEnemyShot` at about `0.835` seconds, after which
the enemy was moved to the configured distance.

For native Attack-task threshold isolation, Lua issued the Attack command but
did not script weapon fire. Both the stock and authored 220 m cases acquired the
same target (`command=4`, `targetEnemy=true`) while the hook recorded their
different `149` and `240` ranges. Neither craft discharged during the extended
30-second observation. Their trajectories were also effectively identical.
Therefore this run proves that the live wingman `CalcRange` consumer receives
the authored outer value, but it does **not** prove an earlier projectile or a
distinct outer-distance maneuver. No stronger firing-threshold claim should be
made from these logs.

The minimum-range case began at `79.18` m with the target acquired. With the
native close threshold changed from `5` to `100`, the craft initially opened
distance to a measured maximum of `100.59` m before turning back. That is live
behavior consistent with UnitTask's too-close/standoff use of the value. The
craft did not fire during the 15-second window, so the qualification is limited
to native close-range consumption and movement response.

## State-machine regression controls

The authored `wreng` Follow case received a real recent enemy hit and logged the
live `149 -> 240` policy, but remained in Follow (`command=5`), never selected
the enemy, and never fired. The otherwise identical no-damage control also
remained in Follow without a target or shot. This demonstrates that the range
policy does not itself bypass the existing offensive state gates. The patch
contains no writes or hooks in the FriendFollow/Wait transition functions, and
does not change their persistence or reacquisition timing.

## Fixture corrections and qualification boundary

Initial exploratory runs exposed three fixture problems, not game crashes:

1. the custom ODFs lacked `baseName`; they now inherit `avtank` or `avturr`;
2. the shim correctly searched the normal addon `ODF` directory while the local
   driver initially copied files only beside the mission;
3. the hostile trigger craft originally faced away and scripted `FireAt` did
   not register a hit; the final fixture faces it toward the wingman and issues
   one native Attack command to the hostile craft.

The remaining limitation is behavioral proof for the authored outer range:
the live native value is proven, but a distinct firing-distance outcome was not
observed. Any future claim about projectile timing should use a separately
qualified weapon-fire fixture rather than broadening this range-policy patch.
