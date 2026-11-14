# Remote-object movement on a client (Redux 2.2.301 GOG) and a smoothing proposal

Date: 2026-11-07. Build: GOG `battlezone98redux.exe` 2.2.301 (5,425,152 bytes, image base 0x400000).

Trigger: co-op misn02b at ~350 ms ping. A host-owned tank moves jaggedly on the guest. The Steam
BZLogger for 16:07–16:17 shows the host sending every 80–84 ms, plus 794 stale-duplicate
`Dropping Packet` lines with no updates lost. So the updates arrive; the question is how the client
turns them into motion.

Citation key:
- `R:FUN_x:L` is a line in the private Redux GOG decompile corpus (`Battlezone_Source\BZ1\Redux\Raw .C\FUN_x-x.c`).
- `15:file:L` is a line in the BZ 1.5 decompile (`Battlezone_Source\BZ1\1.5\functions\...`).
- `EXE` means bytes read directly from the GOG exe.
- Anything without one of these is marked UNVERIFIED.

No decompiler output or PDB data is reproduced here, only addresses, offsets and constants.

## Summary

1. Stock Redux already has a display-only smoothing layer for remote objects. It is a fixed
   per-frame blend: position 0.3, rotation slerp 0.5. Because the factor is per frame, not per
   second, the smoothing depends on frame rate. At 60 fps each 80 ms packet correction is about
   83 % applied within 5 frames, so the steps show.
2. The client dead-reckons by re-running full physics for the latency (`net_dt`, at most 5 × 0.1 s
   sub-steps) from the received state each frame. The physics state snaps to every packet; only the
   displayed transform is blended.
3. The displayed transform is the world object's matrix at obj+0x20, which UpdatePosition
   (`FUN_004DB100`) then pushes on.
4. No stock tunables were found (one reader and a string scan; UNVERIFIED as an absence). Every constant is hard-coded, and net.ini has no smoothing keys.
5. Proposal: an opt-in shim wrapper around GameObject::Simulate (`0x004DEEC0`). It re-blends the
   displayed transform with a time-based factor `α = 1 − exp(−dt/τ)` and adds a snap threshold.
   Implemented as `[Network] RemoteSmoothingMs` (see "Implementation").

## Q1. Receive path into the GameObject

| Step | Site | Evidence |
|---|---|---|
| P2P receive, kind-0 delivery tail | `0x0075D800` → `0x0075DEEF` case 0 → `0x00758C90` | `p2p_early_unreliable_receive_20261010.md` |
| Net message dispatcher | `FUN_00570500` (thiscall) | message `'_'` (temp-state batch) → `FUN_004B7750` (R:FUN_00570500:79-92); message `0x4F50` → `FUN_004B7710` (R:FUN_00570500:173-176) |
| Thunks | `FUN_004B7750`, `FUN_004B7710` | both forward to `FUN_004B8590`; `4B7710` takes the send time from the first dword (R:FUN_004b7710:4, R:FUN_004b7750:4) |
| DistributedObject::ReceiveTempState | `FUN_004B8590(id, data, len, sendTime)` | see below |

UNVERIFIED: how `0x00758C90` reaches `FUN_00570500`. It is probably an indirect handler call;
neither function is in the other's direct call list in the corpus. The dispatcher is the only
non-thunk caller of the two thunks (corpus grep), so all temp-state traffic goes through it.

What `FUN_004B8590` does. Offsets are DistributedObject-relative; DO sits at GO+0x18 in Redux (GO+0x20 in 1.5).

- Rejects records shorter than 6 bytes (R:FUN_004b8590:65).
- Decodes the op from `& 3` (R:FUN_004b8590:83-99). A record for a deleted id logs `OOP ... DELETED ID`
  (R:FUN_004b8590:105-107); an unknown id creates the object via `FUN_004B9350` (R:FUN_004b8590:112).
- Drops out-of-order records: `sendTime < DO+0x78` (last received time) logs `OOP D=... Last Received` (R:FUN_004b8590:134-139).
- Sets net_user DO+0x60 and the team (R:FUN_004b8590:141-150). Resets iter DO+0x50 = 0 and
  count = last_count, then last_count = 0 (R:FUN_004b8590:152-154).
- Saves the old true_transform (R:FUN_004b8590:155-161). ExpandMatrix (`FUN_006253C0`, R:FUN_004b8590:162)
  writes the received matrix to true_transform DO+0x10 (R:FUN_004b8590:172-178).
- Calls the UnPackTempState chain `FUN_004B7E30` for velocity and other class state (R:FUN_004b8590:181).
- Sets `net_dt` DO+0x5C = `Get_Time() − sendTime − TimeStep()` (R:FUN_004b8590:183-188).
  `Get_Time` = `FUN_00822D80` reads `DAT_02CC1B2C`; `TimeStep` = `FUN_00822D60` reads `DAT_00946790`
  (R:FUN_00822d80:3, R:FUN_00822d60:3).
- New in Redux: logs `Possible Large Warp: Distributed Object Updated Position By (%f,%f,%f) with TS %f`
  when any axis |Δpos| > 2.5 or |net_dt| > 0.32 (R:FUN_004b8590:189-201). Δ = received position − previous physics position.

The same structure exists in 1.5 at `15:0048f8c1_DistributedObject_ReceiveTempState.c`:
out-of-order drop at 160-161, ExpandMatrix at 183, iter reset at 191-193, true_transform at 194-200,
UnPack at 201-203 and net_dt at 205-208. The warp log does not exist in 1.5.

IsRemote = `FUN_004B9830(DO*)`: `object_type` DO+0x68 == 2 (R:FUN_004b9830). 1.5:
`15:0048a23e_DistributedObject_IsRemote.c`.

## Q2. Dead reckoning and correction

GameObject::Simulate is `FUN_004DEEC0(obj76*)` (R:FUN_004deec0). `obj` is the world/render object;
`go` comes from `FUN_00479F30` (R:FUN_004deec0:63).

- Non-network games take a plain simulate path (R:FUN_004deec0:65-73; `FUN_00572A70` = Net_IsNetGame).
- Remote object (`FUN_004B9830`, R:FUN_004deec0:76):
  1. Save the displayed transform obj+0x20 as D0 (R:FUN_004deec0:78-84).
  2. If true_transform.posit_y (GO+0x58) != −1.0, a validity sentinel, copy true_transform (GO+0x28)
     into obj+0x20. Physics now starts from the last received state (R:FUN_004deec0:85-92).
  3. `net_dt` (GO+0x74) += TimeStep (R:FUN_004deec0:95-97).
  4. Sub-step loop: `step = clamp(net_dt, 0.001, 0.1)` (`FUN_00447ED0`, constants 0x3A83126F and
     0x3DCCCCCD); `net_dt −= step`; vtable+0x3C Simulate(step). It stops if obj+0x14 & 0x200
     (deleted) or after 5 iterations (R:FUN_004deec0:99-106). This is dead reckoning by full physics
     over at most 0.5 s. Right after a packet it simulates about one latency forward; on later
     frames it advances about one TimeStep.
  5. Store the new physics state P back into true_transform (R:FUN_004deec0:142-148).
  6. Display rotation = slerp(D0, P, 0.5) (`FUN_0081F1E0` matrix→quat, `FUN_004DEAD0` normalize,
     `FUN_004DEBE0(..., 0x3F000000)`; R:FUN_004deec0:107-137), written back by `FUN_0081EFE0`
     quat→matrix (R:FUN_004deec0:152-168).
  7. Display position = D0 + (P − D0) × 0.30000001 per axis on obj+0x48/0x50/0x58 (R:FUN_004deec0:169-174).
  8. `FUN_004DB100` UpdatePosition (R:FUN_004deec0:175).
- 1.5 is identical: `15:004964d3_GameObject_Simulate.c`, save and restore at 60-78, loop at 79-92,
  slerp 0.5 / true_transform / 0.3 lerp / UpdatePosition at 93-139.

So obj+0x20 is in effect a display-only transform for remote objects: at the start of every frame it is
overwritten with the physics state (step 2), and only the blended value survives to rendering.

Why it looks jagged at 80 ms / 350 ms ping:

- Blend factors are per frame. With α = 0.3 per frame, τ = −dt / ln(0.7) ≈ 2.8 frames: 47 ms at 60 fps,
  23 ms at 120 fps. At the original 30 fps it was about 93 ms. A high-fps client therefore shows nearly the
  raw per-packet correction as a step every 80 ms.
- Each packet resets physics to the received state and re-extrapolates about net_dt (≈ 0.12 s in the log, see below) through full
  physics with the received velocities. Any host-side input change in that window, such as steering,
  thrust or collision, becomes a position jump of the order Δv × net_dt on arrival. The display
  blend then absorbs it in about 50 ms.
- A pure exponential blend also lags a moving target by about v·dt·(1−α)/α in steady state:
  ≈ 0.8 m at 20 m/s and 60 fps. The constant lag is mostly invisible; the step response is what shows.

Not found: consumers of iter/count/last_count (DO+0x50/0x54/0x58). They may be unused in Redux (UNVERIFIED).

## Q3. Where the per-frame render transform comes from

- The displayed matrix is obj76+0x20 (rotation, then double posit at +0x48/+0x50/+0x58), written by
  step 7 above, then `FUN_004DB100` (R:FUN_004deec0:175).
- UNVERIFIED: the path from obj+0x20 / UpdatePosition to the Ogre scene node. Memory notes put the
  chunk render around `FUN_006802B0`; it was not traced here.
- Caveat: obj+0x20 is not render-only. Collision, targeting and AI read the same matrix (UNVERIFIED in
  detail, but there is no separate render matrix in the GO/obj76 layout). Any extra smoothing therefore
  also moves what the guest aims and collides against.

## Q4. Stock tunables

None found (UNVERIFIED as an absence: one reader plus a string scan, and exe string scans can miss keys). `FUN_0056FD20` reads net.ini `MaxPing` (700), `MaxPingsLost` (0x14), `UpCount` (10),
`DownCount` (5), `MinBandwidth`, `MaxBandwidth`, `AutoKickStart/Ping/Loss/Time`, `LimitLowNPPI`,
`LimitHiNPPI`, `DivisorMPPI2NPPI` and `DivisorPing2NPPI` (R:FUN_0056fd20:87-100). None relates to
interpolation. A string scan of the exe found no interp/smooth/predict keys. The constants 0.3, 0.5,
0.001, 0.1 and 5 are immediates in `FUN_004DEEC0` (R:FUN_004deec0:99-106, 128, 169-174).

## Evidence from the user's log

Source: Steam `BZLogger.txt`, mtime 2026-11-07 16:19, window 16:07–16:18. Read-only; the file is not committed.

- 1396 `Possible Large Warp` lines. |Δ| histogram (m): 0: 5, 1: 14, 2: 316, 3: 731, 4: 327, 5: 3.
  192 lines are > 4.3 m. TS (net_dt) is mostly 0.10–0.15 (1323) or about 0.05 (33). 38 lines with
  TS > 0.32 ramp 0.4 → 4.3 s (a stall). 2 lines have TS < −0.32. 505 `OOP D=` lines across the whole file.
- How to read it: Δ is the received (old) state minus the already-extrapolated previous physics state, so
  it includes about v × latency (20 m/s × 0.12 s ≈ 2.4 m). It overstates the visible correction. The true
  post-extrapolation error was not measured (UNVERIFIED). Still, 2–4 m deltas every 80 ms fit the
  stepping the user saw.
- Note: TS ≈ 0.12 s while the ping is about 350 ms suggests sendTime is clock-synced, so one-way latency
  is about 0.12 s plus TimeStep (UNVERIFIED).

## Design proposal

Goal: make remote motion smooth independent of frame rate, without touching authority or physics.

Approach A (recommended first step): a time-based blend.
- Wrap `FUN_004DEEC0`. Before calling the original, record `remote = IsRemote(go)` and copy D0 = obj+0x20 (64 bytes).
- After the original, if remote, `!(obj+0x14 & 0x200)`, and the patch is enabled, recompute the
  display from D0 and P = true_transform (GO+0x28, which the original just set at step 5):
  - `α = 1 − exp(−dt / τ)`, where dt = TimeStep (`DAT_00946790` via `FUN_00822D60`) and τ comes from settings.
  - position = D0 + (P − D0)·α; rotation = slerp(D0, P, α_rot). Stock rotation uses 0.5/frame, a
    shorter time constant than position, so use a separate rotation τ (τ/1.94, stock's ln 0.5 / ln 0.7 ratio) using the same helpers (`FUN_0081F1E0`,
    `FUN_004DEAD0`, `FUN_004DEBE0`, `FUN_0081EFE0`) or a local quaternion slerp.
  - Snap when |P − D0| > `SnapDistance` (respawn or teleport) or when the posit_y sentinel was −1.0.
    The sentinel must be read before calling the original, which overwrites true_transform at step 5.
  - Call `FUN_004DB100` again so the final transform propagates. Calling it twice per frame is assumed
    harmless (UNVERIFIED).
- Overwriting the stock result is safe because the original sets obj+0x20 again from true_transform
  at the start of the next frame (step 2); the blend output is never fed back into physics. Exception: on a sentinel frame (posit_y == −1.0) step 2
  is skipped, so the wrapper must snap there rather than blend.

Approach B (later, needs RE): velocity-compensated blending, using D0 + v·dt as the start point to remove
the steady-state lag. This needs the Redux velocity offset in the physics struct. In 1.5, HoverCraft
UnPackTempState writes velocity to phys+0x1C; this is not confirmed for Redux.

Approach C (optional): only adjust the stock factor for high fps by re-deriving α to match the 30 fps
behaviour (τ ≈ 93 ms). This is the same code as A with a fixed τ.

Settings: `[Network] RemoteSmoothing` (0 = stock, default; otherwise τ in ms, suggested 100) and
`RemoteSnapDistance` (m, default 15) in openshim.ini, following the env/INI mapping in
`openshim-settings` conventions. The blend is client-local and purely cosmetic, so it should not need the
MP gate. Confirm with the settings owner (UNVERIFIED).

### Hook site

- `FUN_004DEEC0` has one direct call, at `0x00618090` (`E8 2B 6E EC FF`) inside `FUN_00618060`, which
  probably simulates only the current user object (R:FUN_00618060:29-35; EXE; UNVERIFIED).
- Seven absolute pointers to `0x004DEEC0` sit in a per-class callback table of 0x34-byte records starting
  near VA `0x008EC814` (EXE). So other objects are probably simulated through the table (UNVERIFIED), and a call-site retarget
  would miss them.
- Therefore use an entry detour (alternative: retarget all seven table pointers). The prologue `55 8B EC 81 EC A8 01 00 00` (push ebp; mov ebp,esp;
  sub esp,0x1A8) is 9 bytes with no relative operands, so it is clean for a trampoline (EXE). It needs a
  `scripts/patches.json` entry with that signature and a fail-closed check.
- Calling convention: the decompile shows a single obj76* argument (R:FUN_004deec0). Confirm stdcall
  versus cdecl (the `ret` form) before writing the wrapper (UNVERIFIED).

### Implementation (`src/patches/remote_object_smoothing.cpp`)

- Entry detour on `0x004DEEC0` with the 9-byte prologue above; patches.json rows `GameObjectSimulate`,
  `GameObjectSimulateRemoteCopy` (`0x004DEF02`) and `DistributedObjectIsRemote` (`0x004B9830`) pin the
  sites, and the patch stands down if any row, `GameObject::FromObj76` or `TimeStep` fails to resolve.
- Net-game gate: the wrapper reads byte `DAT_00917F7B` (patches.json `IsNetGameFlag`), the same byte
  stock's check reads: `FUN_00572A70` returns `FUN_00571C40()` (R:FUN_00572a70:6), which returns
  `DAT_00917f7b` (R:FUN_00571c40:4).
- Remote test: DO+0x68 == 2 on GO+0x18, as `FUN_004B9830` (R:FUN_004b9830).
- Sentinel frame (posit_y == −1.0): the wrapper keeps the stock result rather than snapping. Stock skips
  the true_transform copy there, so physics starts from the display and the stock 0.3 blend is benign.
- Rotation τ = τ/1.94: stock's per-frame time constants are −1/ln 0.7 = 2.80 frames (position) and
  −1/ln 0.5 = 1.44 frames (rotation).
- Snap at 15 m is new behaviour: stock has no snap (R:FUN_004deec0:107-175 has only the two blends).
- dt is clamped to 0.1 s, so a hitch blends at most 1 − exp(−0.1/τ).
- Non-rotation or non-finite input is skipped (stock result kept). Any SEH fault latches the patch off
  for the session and logs one Warn line.
- Freed-object writes: stock itself writes obj+0x20 after its 0x200 check (R:FUN_004deec0:142-175),
  and the wrapper re-checks that flag and the remote byte before writing, so it touches the object only
  where stock already does.
- Settings: one key, `RemoteSmoothingMs` (0 = stock, default; clamped 0..300; suggested 100), ini-only,
  restart required. There is no separate snap-distance key and no options-UI row yet.
- A 30 s Info line reports blended/snapped/skipped counts.

### Risks

- Hitbox mismatch: aiming, collision and lock-on on the guest use obj+0x20. A larger τ means more lag
  between what the guest sees and shoots and the predicted position. Keep τ at or below about 150 ms.
  Host-authoritative damage limits the gameplay effect but can feel like "missed shots".
- Scope: every remote DistributedObject goes through this path: craft, buildings, possibly ordnance and
  pilots. Consider limiting it to craft by class, or skipping objects whose |P − D0| is 0.
- Stalls: after a long hitch, dt is large and α → 1, a hard snap. Stock would still blend at 0.3, so this
  is a behaviour change; clamp dt (for example to 0.1 s) if a hitch snap looks worse. The posit_y −1.0 sentinel
  frame must snap.
- Detour coexistence: no current `scripts/`, `src/` or `include/` reference to `0x004DEEC0` on this
  base (grep, 2026-11-07). Recheck open PRs before implementing.
- Testing: a localhost co-op harness has about 0 ms latency and will not show the benefit. A real test
  needs added latency (for example clumsy or netem) or two machines. Measure the frame-to-frame
  displacement variance of a remote tank with the patch on and off.
- Out of scope: the reliable-retry timer (`src/patches/p2p_reliable_send_fix.cpp`), which a parallel
  session owns.

## Live check

This is an impaired 4-client A/B on 2026-11-07. Each arm ran `Run-BZRBattleLoad.ps1 -Mode Strategy -Units 40 -Seconds 60` through the private relay with `-Impair delay=150,jitter=40,loss=5,seed=1`. The run dirs are `C:\BZRCoop\runs\smooth-tau0-190325` and `smooth-tau100-190813`.

| arm | clients with the hook | flow checks | remoteWarps | remoteJumpsOver25m | remote unit-frames per client |
|---|---|---|---|---|---|
| τ = 0 (stock) | none | 48/48 pass | 0 on all 4 | 0 | 230k-284k |
| τ = 100 ms | 0 and 1 | 48/48 pass | 0 on all 4 | 0 | 233k-277k |

- **Clients 2 and 3 are not a τ=100 sample.** In this co-op install, Instance2 and Instance3's `plugins\` folders are junctions to the GOG install's `plugins\`. During the run, another session deployed 1.0.0.73 there. So those two clients ran without the hook.
- **Hook counters, clients 0 and 1:**
  - The detour logged `enabled: tau=100 ms (rotation 52 ms), snap 15 m, detour 0x004DEEC0`.
  - Each 30 s window logged 120k-130k `blended`, with `snapped=0`, `skipped=0` and no fault latch.
  - That is about 4,000 blends per second, which matches the about 4,000 remote unit-frames per second the harness counted on the same client. So the blend runs once per remote object per rendered frame. This settles the reviewer's dt-cadence question for this build.
- **Combat:** the hit-registration numbers (damage per enemy shot 0.42-0.83 per team) stay in the stock arm's range.

What this shows:
- The hook installs, runs on every remote object, never faults, never snaps at 150 ± 40 ms with 5 % loss, and changes no flow or combat check.
- The harness's warp metric is 0 in **both** arms at this impairment. It counts large discontinuities, so it cannot see the per-frame display-error smoothing this patch changes.

UNVERIFIED:
- Visual smoothness. Nothing measured the displayed-versus-true error curve; that needs a frame capture, or a probe that logs the display error per frame.
- Behaviour at real internet latency, and the 350 ms jitter case from the report that started this.
- Steam or Proton builds.
