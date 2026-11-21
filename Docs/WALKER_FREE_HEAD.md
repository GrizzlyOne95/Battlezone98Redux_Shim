# Walker free-turning head (`[WalkerClass] torsoName`)

Status: **M1 (functional twist) implemented, not yet run live.** The legs mesh is not re-posed yet (M2), so on an opted-in walker the whole model still turns with the head; only the locomotion heading is separate. Do not ship an ODF that opts in until M2.
Design, RE and milestones: `Docs/WALKER_FREE_HEAD_RESEARCH.md`. Code: `src/patches/walker_free_head.cpp`, pure math `include/walker_free_head_math.h` (tests `tests/walker_free_head_math_tests.cpp`).

## What it does
- MechWarrior-style twist: the mouse (analog steer axis) turns the head; the steer arrow keys and A/D turn the legs; throttle drives along the legs heading.
- Camera, reticle, weapons and ordnance follow the head, because the walker's root transform is the head (same approach as the tracked turret, `Docs/TRACKED_VEHICLES.md`).
- The head is world-stabilised: turning the legs does not drag the aim, except against a `yawMin`/`yawMax` limit.

## Who gets it
- Off unless the walker's ODF sets `[WalkerClass] torsoName`. No stock ODF does; there is no `openshim.ini` option (the ODF is the opt-in, as for `classLabel = "tracked"`).
- Only the walker the player is driving (obj76 flag 0x10). AI walkers and empty walkers stay stock.
- Single player only: the gate is `IsSinglePlayerSession()`. In a network game every walker is stock.
- The torso node must be a direct child of the model root, else the walker stays stock (one log line).

## ODF
```ini
[WalkerClass]
torsoName = "AGE11TY1"  ; node that stays with the head; 8 chars max, case-insensitive. Required: the feature is off without it.
yawRate   = 2.5         ; head slew rate, rad/s (default 2.5; clamped to 0.05..20)
yawAlpha  = 8.0         ; head slew acceleration, rad/s^2 (default 8.0; clamped to 0.1..200)
yawMin    = -1.6        ; optional: head yaw relative to the legs, radians; unlimited unless set
yawMax    =  1.6        ; a pair that does not satisfy yawMin <= 0 <= yawMax inside +-pi is dropped with a log line
```
Leg turn speed is the stock `omegaTurn`/`alphaSteer`. The keys are read once per ODF name, on the first Simulate of a walker of that class.

## Known losses (accepted for v1)
- **Sidestep:** A/D turn the legs instead of strafing. `ctrl.strafe` is zeroed during the stock call.
- **Steer assist:** the head reads the raw mouse axis, so the stock steer-assist term (UserProcess::Execute, taken when the assist action and a target are set) does not reach the head. The legs ignore it too.
- **delta is not saved:** a loaded game starts with the head over the legs.
- **Leaving the walker** (or death, or a network game) snaps the twist to 0 at once. M2 relaxes it at `yawRate`.

## How it works (M1)
The Walker vtable (0x0088A0BC) slots 15 (Simulate) and 16 (PostSimulate) are replaced in place. For a twisting walker each Simulate call:
1. reads the head command from the analog steer axis global (`UserInput::SteerAxis`, mouse only) and the legs command from the steer arrow bytes (`UserInput::SteerLeft`/`SteerRight`) plus `-ctrl.strafe`;
2. slews the head with the tracked turret's `SlewRate` (trapezoid step);
3. writes `ctrl.steer = legs command`, `ctrl.strafe = 0`;
4. turns the root's right/front to the legs frame (head yawed by `-delta` about its up);
5. calls the stock Walker::Simulate;
6. measures the legs' yaw change about the root's up, sets `delta = delta + headStep - legsTurn` (clamped or wrapped), turns the root back to the head frame, restores `ctrl.steer`/`ctrl.strafe` and calls slot 38 UpdateWeaponAim again (the stock tail ran it with the root in the legs frame).

PostSimulate only logs that it was reached; M2 poses the leg nodes there. Every memory access is under SEH; a fault puts the walker back to stock for that call (logged).

Install fails closed (one `[WALKHEAD]` warning, feature off) when a resolve or engine row is missing, the vtable is not `.?AVWalker@@`, or slot 15/16 holds something other than the stock function or this hook.

## Log lines (`[WALKHEAD]`, all change-only or once)
- `ODF <name>: free head on ...` / `no [WalkerClass] torsoName; stock walker`: once per ODF name.
- `walker <p>: <old gate> -> <new gate>`: the per-object decision (twist, not single player, not the user's craft, dead, torso missing, fault).
- `inputs raw axis ... ctrl.steer=... -> head .. legs ..; mouse-only tracks|DOES NOT TRACK (mouse-only frames N, tracked M)`: whenever the quantised inputs change. With mouse-only input the raw axis read in Simulate must track `ctrl.steer`.
- `walker <p> swap: delta ... root/head yaw a -> b legs yaw c; veloc legs fwd/right, head fwd`: whenever the 5-degree delta bucket, the legs' turn direction or moving/still changes.
- `UpdateWeaponAim (slot 38) re-run after swap-back` and `PostSimulate (slot 16) reached while twisting`: once per object.

## Verification (M1, live, still to do)
Test copy of `avwalk.odf` with `[WalkerClass] torsoName = "AGE11TY1"` (and a faster `omegaTurn` if wanted), single player, player in the walker. UNVERIFIED until run:
1. Install line `installed (M1)` and `ODF avwalk: free head on` appear; a stock walker ODF logs `no [WalkerClass] torsoName`.
2. Gate line `unseen -> twist` on entering the walker; `-> stock (not the user's craft)` on leaving.
3. Mouse only: `inputs` lines say `mouse-only tracks`, and the tracked count stays close to the mouse-only count (the 0x009198B0 read in Simulate tracks `ctrl.steer`).
4. Mouse only: the view turns, `swap` lines show delta changing and `legs yaw` constant.
5. Arrow keys or A/D only: the legs turn (`legs turn` non-zero), `root/head yaw` stays put (world-stabilised), delta changes by the opposite amount.
6. Throttle with delta near 90 degrees: `veloc legs fwd` carries the speed, `head fwd` near 0; the walk clip plays (forward walk, not a sidestep clip).
7. Fire: shots leave along the head (reticle), not along the legs; `UpdateWeaponAim (slot 38) re-run` logged once.
8. `PostSimulate (slot 16) reached while twisting` logged once (confirms the M2 hook point for Walker's class).
9. Camera and cockpit follow the head with no new jitter; the legs mesh turning with the head is expected in M1.
10. With `yawMin`/`yawMax` set: the head stops at the limit and is dragged by the legs past it.
11. A network game: gate `not single player`, walker behaves stock.
