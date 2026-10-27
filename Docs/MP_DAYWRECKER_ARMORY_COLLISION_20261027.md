# Daywrecker phantom at the Armory: [Fixes] DaywreckerArmoryCollision

Date: 2026-10-27. Branch: `agent/mp-bug-scenarios`. GOG Redux 2.2.301.

## Symptom

An Armory-launched Daywrecker sometimes also blows up at the Armory, but only
on the other players' machines. Their own units near the Armory take a full
blast; the launcher sees nothing. The target blast happens normally on every
peer.

Reproduced with `Run-BZRMpBugs -Case Weapons -ScenarioArgs @{ Weapon = 'daywrecker'; Burst = 3 }`
(run `mpbugs-wp-phantom-1`, host launcher, 2 clients): the receiver had one
extra Daywrecker lifetime at the Armory spawn point (2160, 13.2, 2664) that
lasted one frame, and its four Armory witnesses lost 1582-1977 health each.
Both peers saw exactly 3 detonations at the target.

## Cause

| Step | Evidence (GOG exe) |
| --- | --- |
| Only the launching peer runs the Armory's ObjectLobber. It builds the bomb, records the Armory as owner and sets vehicle flags `4\|8` (in flight, launched). | `00582190` calls `0046FC40` (owner handle to bomb+0x224) and ORs `0xC` into `*(bomb+0x228)+0x114`. |
| Every other peer builds its copy from a network create message, with flags 0 and owner 0, and marks it remote. | Create path calls `004B7F00` (id) then `004B7F20` (mode byte at Distributed+0x68 = 2); the trace logs `CREATE ... flags=0x0->0x0 owner=0x00000000 ret=0x004B972F`. |
| The copy's first state, applied through the PowerUp unpack, sets `4\|8`. | `005AACF0` rebuilds the flags word from the packet; trace: `flags=0x0->0xC` on the first unpack, `0xC->0xC` after. |
| DayWrecker::Simulate detonates whenever bit 4 is clear (crater, blast, Remove). | `004B0460`: `test [flags],4 / je` into the blast path, guarded only by the consumed latch at +0x230. |

The world sim can reach a fresh remote copy (call through vtable slot 15 at
`004DF001`) before any state for it has arrived. That Simulate sees flags 0
and blows the copy up where it was created, inside the Armory, on that peer
only. In the receiver trace for run `mpbugs-wp-diag-3`, bomb 0x1000F was
created, simulated with flags 0 before its first unpack, removed, and then
rebuilt from later state (`revived=1`; a remote dynamic ID leaves no
deleted-ID record, see
[the lifetime investigation](DAYWRECKER_RECEIVER_LIFETIME_INVESTIGATION_20261007.md))
and it flew on. Every other copy in the run got its state first and was
fine. It depends on whether the create and the first state land in the same
sim frame, which is why it is intermittent.

A rebuilt copy has the flags but still no owner, so if it is still inside the
Armory, DayWrecker::RegCollision (`004B0610`) no longer skips the Armory as
its owner and can set it off a second time.

Two earlier explanations were ruled out by runs: the owner-less collision
alone (an Armory exemption never fired on a first copy) and state clearing the
flags of a locally built copy (a flag guard on the unpack never fired).

## Fix

`src/patches/mp_daywrecker_armory_collision.cpp`, one switch, two parts:

1. **Hold detonation until first state.** The Simulate entry of the DayWrecker
   class vtable (`00878508`, slot 15) is replaced. For a remote copy (mode
   byte 2) that has not had a state unpack yet, it runs PowerUp::Simulate
   (`005A7D70`, what DayWrecker::Simulate runs while the bomb is in flight)
   instead of the detonation check. A detour on the unpack (`005AACF0`)
   records each DayWrecker that has had state applied, keyed by pointer and
   network id. Local bombs (the launcher's, or a Lua-built one) are never
   remote and keep stock behaviour; a remote Lua-built bomb detonates as soon
   as its first state arrives. The vtable entry is patched rather than the
   function, so it chains with the MPAUTH trace's inline detour on
   `004B0460`.
2. **Owner-less copies skip the Armory.** `004B0610` is detoured: for a bomb
   with flags 4 and 8 set and owner handle 0, a collision with an Armory
   (class signature `ARMR`) is ignored, as the launcher already ignores its
   own Armory. The launcher always has an owner, so it is unaffected.

Trade-off of part 2: on a receiver, a rebuilt bomb that hits a *different*
Armory in flight passes through it, while the launcher would detonate it
there. That is rare.

The fix is local to each patched peer: it changes how this machine simulates
other peers' bombs and sends nothing. An unpatched peer still gets the
phantom. It is inert in single player (no remote objects).

Off switch: `[Fixes] DaywreckerArmoryCollision = 0`, or
`OPENSHIM_DISABLE_MP_DAYWRECKER_ARMORY_COLLISION=1`. The Weapons case's
`-Expect Stock` arm turns it off.

The MPAUTH trace's REMOVE line now reads the identity from the complete object
(the Remove hook receives complete+0x18), so it logs the real ID; its sim and
CREATE lines also log the flags, owner and return address.

## Verification
`Run-BZRMpBugs -Case Weapons -ScenarioArgs @{ Weapon = 'daywrecker'; Burst = 5 }`,
host launcher, 2 clients:

| Run | Expect | Result | Receiver c1 |
| --- | --- | --- | --- |
| `mpbugs-wp-fixed7-1` | Fixed | PASS, 27 checks | 5 creates, 0 removes, 0 Armory ends, Armory witness loss 0; 2 bombs held until first state |
| `mpbugs-wp-fixed7-2` | Fixed | PASS, 27 checks | 5 creates, 0 removes, 0 Armory ends, Armory witness loss 0; 6 hold log lines |
| `mpbugs-wp-stock6-1` | Stock | Armory checks fail as expected | phantom ends at the Armory |
| `mpbugs-wp-stock7-1` | Stock | stopped early (c1 left the match, return code 0) | 7 creates, 2 removes before it stopped: the rebuild pattern |

The Armory exemption (part 2) did not fire in either fixed run; with part 1
no copy is rebuilt at the Armory. It stays as a backstop.
