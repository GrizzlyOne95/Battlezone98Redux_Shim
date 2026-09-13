# Constructor double-recycle leaves the losing rig permanently deployed

Reproduced live on 2026-09-13 against the GOG Redux install, with controls,
then fixed. The recycle teardown path cancels the unbuild but omits the
undeploy that the completion path performs, so a Constructor whose target is
removed by somebody else is left deployed for the rest of the mission.

## Reproduction

```powershell
pwsh -File reverse_engineering/run_lcroad_recycle.ps1
```

The runner installs the `lcbench` world assets if they are absent, deploys
`rmrcyc.lua` as `addon/lcbench/lcbench.lua`, runs each arm, captures evidence,
and removes everything it laid down. Single arm, three repeats:

```powershell
pwsh -NoProfile -Command "& './reverse_engineering/run_lcroad_recycle.ps1' -Cases @('same') -Repeats 3"
```

Note the `@(...)` form: `pwsh -File ... -Cases same,stag` passes one string and
fails `ValidateSet`.

`rmrcyc.lua` spawns the rigs at mirrored lateral offsets from the building so
both travel the same distance, issues `SetCommand(rig, AiCommand.RECYCLE, 1,
building)`, polls `IsDeployed` / `GetCurrentCommand` / `GetCurrentWho` every
half second, and then — ten seconds after the building dies — pokes every
surviving rig with a `Goto`. The poke is what separates *wedged* from merely
*idle and deployed*.

## Result

| Arm | Rigs | Buildings | Deployed at end | Moved after poke | Stuck | Target down at |
|---|---|---|---|---|---|---|
| `solo` | 1 | 1 | 0 | 1 | 0 | T+13.01 |
| `pair` | 2 | 2, one each | 0 | 2 | 0 | T+13.02 |
| `same` | 2 | 1, shared | 1 | 1 | **1** | T+13.01 |
| `stag` | 2 | 1, shared, 2nd order +4s | 1 | 1 | **1** | T+13.01 |

`same` reproduced identically on both repeats. The two controls are what make
the reading safe: a lone rig and two rigs on two buildings both finish clean,
so "ends up deployed" is not simply what Constructors do.

The trace from `same_r01`, trimmed to the transition:

```
T+9.501  POLL        rig1{dep=true  cmd=18 who=FFE00002} rig2{dep=true  cmd=18 who=FFE00002} bld1{v=true}
T+13.008 TARGETDOWN  rig1{dep=true  cmd=18 who=FFE00002} rig2{dep=true  cmd=18 who=FFE00002} bld1{v=false}
T+13.502 POLL        rig1{dep=false cmd=18 who=FFE00002} rig2{dep=true  cmd=18 who=FFE00002} bld1{v=false}
T+23.008 POKE rig=1 dep=false cmd=18
T+23.008 POKE rig=2 dep=true  cmd=18
T+35.012 RIGRESULT rig=1 dep=false cmd=0 travelled=63.09
T+35.012 RIGRESULT rig=2 dep=true  cmd=3 travelled=0.00
```

Both rigs hold `cmd=18` (`CMD_RECYCLE`) on the same handle `FFE00002`. When the
building dies, rig1 undeploys within half a second. Rig2 never does. Twelve
seconds after being handed a `Goto` it still reads `dep=true`, and `travelled`
is exactly `0.00` — it **accepted** the order (`cmd=3`, `GO`) and could not act
on it. The loser is not idling deployed, it is wedged.

Two incidental findings fall out of the same table:

- `targetDownAt` is T+13.0 in every arm, `solo` included. The second rig's
  unbuild contributes nothing — each rig runs its own independent countdown and
  the first to reach zero deletes the building. Double-recycling is pure loss:
  no speed-up, one Constructor gone.
- The 4-second stagger in `stag` does not help. This is not a same-frame race;
  any second rig that has reached the unbuild loop before the winner finishes is
  lost.

## Root cause

Addresses below are the shipped GOG Redux 2.2.301 executable, read from its own
decompile corpus and confirmed against the live binary.

The only undeploy anywhere on the recycle path is in `UnBuild::DoNear`
(`0x0049EC50`), in the branch it takes once `ConstructionRig::IsUnbuilding`
goes false:

```c
if (rig->IsDeployed()) {
    if (stage == 0) { ConstructionRig::StartUnbuild(rig, target); stage = 1; }
    if (stage == 1) {
        ConstructionRig::UpdateUnbuild(rig, TimeStep());   /* 0x0049CDF0 */
        if (!ConstructionRig::IsUnbuilding(rig)) {
            stage = 2;
            rig->vtbl[0x64]();          /* Craft::Undeploy  -- 0x004AE330 */
            ...
        }
    }
}
```

The winner reaches it: its countdown expires, `UpdateUnbuild` calls
`FinishUnbuild` (`0x0049CEE0`), the unbuild handle is cleared, and the same
frame asks for the undeploy.

The loser never reaches it. On the next AI tick its task reports itself done,
`RigProcess` leaves the unbuild state, and `RigProcess::CleanUState2`
(`0x0049EE10`) destroys the `UnBuild` task before `DoNear` is ticked again:

```c
void RigProcess::CleanUState2(RigProcess *this) {
    ConstructionRig::CancelUnbuild(this->craft);   /* 0x0049CDB0 */
    if (this->task) this->task->vtbl[0]( /*deleting*/ 1 );
    this->task = 0;
}
```

`CancelUnbuild` zeroes the unbuild handle and timer, so the unbuild state is
torn down correctly. **Nothing undeploys the craft.** The rig is left in deploy
state 2 with no task, no unbuild, and no remaining code path that will ever ask
it to stand up again.

That is the whole defect: **the recycle teardown path cancels the unbuild but
omits the undeploy that the completion path performs.**

### What the live trace showed, and what it ruled out

An earlier reading of the BZ 1.5 decompile pointed at `UpdateUnbuild`'s
vanished-target branch, which calls `Producer::CancelBuild` (`0x005AED80` in
Redux) — the build-side cancel, which never touches `unbuildHandle`. A detour
that cleared the handle there was built, shipped and measured, and **released
nothing**: `staleHandlesReleased = 0` on every arm while the bug still
reproduced. Redux's `CleanUState2` already calls `CancelUnbuild`, so the stale
handle that theory depends on never exists.

Instrumenting `DoNear` settled it. Both tasks tick in lockstep through deploy
state 0 → 1 → 2 and stage 0 → 1, and then, on the frame the building dies:

```
[DONEAR] beat task=0x29811828 rig=0x02A0CF20 calls=3200 stage=1 deployState=2
[DONEAR] beat task=0x29812BD8 rig=0x02A0CB20 calls=3200 stage=1 deployState=2
[TRACE]  terminal rig=0x02A0CF20 handleBefore=0xFFE00002 handleAfter=0x00000000
```

and nothing afterwards, for either task. `DoNear` stops being called for **both**
rigs at once. The winner got its undeploy inside that terminal frame; the loser's
task was gone before its next tick. No stale handle is ever observed, on either
rig, at any point.

This is why an arm has to report what the fix actually did and not just the
mission outcome — see [[ab-arm-that-never-engaged-looks-like-a-null-result]].
The first fix was installed, active, and running on every frame, and a summary
that only showed `stuck=1` would have read as "the fix does not work" rather
than "the fix never applied to anything".

## The fix

`[Fixes] ConstructorRecycleStaleTarget`, default ON, MP-gated with the other
simulation-affecting corrections.

A detour on `RigProcess::CleanUState2` asks for the undeploy the completion
branch would have asked for, through the same virtual (`Craft::Undeploy`, rig
vtable +0x64, confirmed live as `0x004AE330`):

```c
rig    = process->craft;              /* +0x34 */
target = process->unbuildTarget;      /* +0x3C */
if (rig && target && GameObjectHandle::GetObj(target) == nullptr &&
    (rig->deployState == 2 || rig->deployState == 1))
{
    rig->vtbl[0x64](rig);             /* Craft::Undeploy */
}
/* then delegate to the original */
```

Two guards keep it to the defect and nothing else:

- **The target must no longer resolve.** Finishing an unbuild normally, or the
  player replacing the order, leaves this state with a live or absent target
  handle and is untouched.
- **The rig must be deployed (2) or still deploying (1).** A rig already
  undeploying (3) is skipped, so the winner — which asked for its undeploy one
  tick earlier — is never touched. `Craft::Undeploy` only sets the control
  block's deploy request under the same two states, so even if the winner were
  still at 2 the call would be the idempotent re-assert it already made.

Byte-guarded on three instructions inside `CleanUState2` — the entry prologue,
the load of the craft at `+0x34` feeding the `CancelUnbuild` call, and the load
of the task pointer at `+0x38` — plus `GetObj`'s own prologue, since the fix
calls it. A mismatch stands the fix down and logs one line.

The same defect covers a rig whose recycle target is destroyed by enemy fire
mid-recycle; that is the identical teardown path.
