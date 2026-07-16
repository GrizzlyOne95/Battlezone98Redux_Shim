# Item 23: Jump-Sniping Crouch-on-Landing — Root Cause + Fix (GOG)

Date: 2026-07-13
Supersedes the open questions in `jump_sniping_player_investigation_20260318.md`.

All addresses/offsets below were derived by **static disassembly of the live
installed GOG binary** (`battlezone98redux.exe`, `.text` VA=0x401000,
Raw=0x400, so `VA = fileOffset + 0x400C00`), not from the advisory beta PDB.
The advisory PDB is drifted for this build (see corrections below).

## The real Person::Simulate

- **GOG `Person::Simulate` = `0x0059D340`** (not the PDB's `0x004F43E0`).
- Prologue bytes: `55 8B EC 6A FF 68 D6 C1 84 00 64 A1 00 00 00 00 50 81 EC E8 06 00 00`
  (`push ebp; mov ebp,esp; push -1; push 0x84C1D6; mov eax,fs:0; push eax; sub esp,0x6E8`).
- `this` (Person*) is spilled to `[ebp-0x340]`.
- `add ecx,0x18; call 0x4B9830` == `DistributedObject::IsRemote(this+0x18)`,
  matching the beta decomp `FUN_0059d340`.

### The existing OpenShim probe hooked the WRONG function (now fixed)

`InstallJumpSnipingProbeIfRequested()` used to target
`kGogPersonSimulateEntryAddr = 0x004F4370` with expected prologue
`55 8B EC B8 44 10 00 00`. That address disassembles as a **version/string
builder** (0x1044-byte frame, compares a global at `0x917B20` against version
constants `0x419/0x7D0/0x7DA/0x7DE`, builds a path string). It contains no SNIP
sig compare and no animation calls. So the March probe never observed Person
state. It also used beta-PDB field offsets that are all wrong for GOG (below).

**Fixed 2026-07-13**: the probe now hooks `0x0059D340` with a 10-byte prologue
patch (`55 8B EC 6A FF 68 D6 C1 84 00`; 10 lands on the instruction boundary
after the `push imm32`), uses the corrected offsets below, and additionally
logs the anim FSM state (`+0x228`) and the grounded flag
(`*(Person+0x230)+0x114 & 0x80`). Log line now reads
`... fsm=%u->%u grounded=%s->%s anim=... animH=... sniper=...`.

## GOG field offsets (verified from the disassembly)

Relative to `Person*`:

| Field | GOG offset | Beta-PDB said | Evidence |
|-------|-----------|---------------|----------|
| `carrier` | **+0x1A0** | 0x198 | `mov ecx,[ecx+0x1A0]` before `Carrier::GetWeapon` (0x417F60) at 0x59D7BD |
| anim FSM state | **+0x228** | (unnamed / "vhcl") | switch index at 0x59DDC0; written 0/1/2/3 |
| `curAnim` | **+0x2A8** | 0x288 | `cmp dword [ecx+0x2A8],0xB` at 0x59DE50 |
| `animHandle` | **+0x2AC** | 0x28C | `cmp dword [eax+0x2AC],-1` at 0x59E079 |
| grounded-flags obj ptr | **+0x230** | (— ) | `mov eax,[edx+0x230]` at 0x59DDEC |

Carrier/weapon path (unchanged shape): `weapon = Carrier::GetWeapon(slot)`,
`weaponClass = *(weapon+0x08)`, `sig = *(weaponClass+0x0C)`; sniper iff
`sig == 0x534E4950` ('SNIP'). Confirmed at `0x59D7D7`
(`cmp dword [eax+0xC], 0x534E4950`).

Grounded/airborne flag: `*( *(Person+0x230) + 0x114 ) & 0x80`. **Bit set =
grounded**, bit clear = airborne. Tested at `0x59DDF8` (`and ecx,0x80;
jne <grounded branch>`).

## The animation state machine (case 0 is where the bug lives)

Switch on FSM state `Person+0x228` (jump table at `0x5A0A98`):

- **case 0** (`0x59DDE6`): read grounded bit `*(Person+0x230)+0x114 & 0x80`.
  - **airborne** (bit clear): choose land/jump anims (`9`, `10`, or hold `11`).
  - **grounded** (bit set, `0x59DEA5`):
    1. `if (jumpHeld)`  → anim `0xB` (jump)              ← **the regression**
    2. `else if (sniperSelected)` → anim `0` (stand2Kneel), `state = 1`
    3. `else` → idle/run anims `2/4/5/6/7`
- case 1 (`0x59E073`): wait for anim to finish (`animHandle==-1`) → anim `3`
  (crouch idle), `state = 2`.
- case 2 (`0x59E0AA`): `if (!sniper)` anim `1` (kneel2stand), `state=3`; else
  stay anim `3` (crouch idle).
- case 3 (`0x59E0DD`): wait → anim `2` (stand idle), `state = 0`.

`jumpHeld` = `[ebp-0x352]` (from the jump control, `!=0` while jump input is
held). `sniperSelected` = `[ebp-0x351]` (set by the slot scan). The two bools
are **adjacent** in the frame (`-0x352`, `-0x351`).

### Root cause

Redux's case-0 grounded branch tests `jumpHeld` **before** `sniperSelected`.
While jump is held, `jumpHeld` stays 1, so the sniper-crouch path (step 2) is
never reached even after touching the ground — you keep getting the jump anim.
Legacy 1.5 checked sniper first in the grounded branch (no jump-held gate), so
landing with a sniper selected always re-entered the crouch pose. This exactly
matches the report: "in redux you can hold jump and even if you touch ground it
doesn't [crouch]."

## Fix: 11-byte inline patch at 0x59DEA5

Change the grounded branch predicate from `if (jumpHeld) → jump` to
`goto sniperCheck iff (jumpHeld <= sniperSelected)`. Since both are 0/1, the
predicate `jumpHeld <= sniper` yields: (0,0)→sniperCheck, (0,1)→sniperCheck,
(1,1)→sniperCheck (crouch!), (1,0)→jump anim. Only the
`jumpHeld && sniper` case changes — it now crouches instead of playing jump.
All non-sniper behavior and the airborne branch are untouched.

- Original (11 bytes @ `0x59DEA5`): `0F B6 85 AE FC FF FF 85 C0 74 26`
  (`movzbl [ebp-0x352],eax; test al,al; je 0x59DED6`)
- Patched: `66 8B 85 AE FC FF FF 38 E0 76 26`
  (`mov ax,[ebp-0x352]; cmp al,ah; jbe 0x59DED6`)

The `jbe` reuses the same rel8 `0x26` because start and target are unchanged.
After a taken `jbe`, execution reaches the original sniper check at `0x59DED6`;
after fall-through it reaches the original jump-anim block at `0x59DEB0`.

### Gating (updated 2026-07-14): INI baseline, off in multiplayer

OpenShim owns the native byte patch, enables it by default for single-player,
and reads `[SinglePlayer] JumpSnipeCrouch=1|0` from `openshim.ini`. The existing
`OpenShimSetJumpSnipeCrouchEnabled(BOOL)` / `exu.SetJumpSnipeCrouch()` bridge can
temporarily override that baseline for scripted content. Three guards keep it
out of multiplayer and off-build:

1. `RefreshJumpSnipeCrouchPatchState()` only applies the patch when the local
   net id (`0x009180D4`) is 0 (not a network game), and reverts otherwise. A
   continuous re-check also runs from the chunk-effect sim tick.
2. `ResetMissionHookOverridesFromBridge()` restores the user's INI baseline on
   mission end, and the continuous gate reverts it if a network game starts.
3. Expected-bytes guard: no-ops on any build (e.g. Steam) whose `0x59DEA5`
   bytes don't match.

Neither INI nor script state can bypass the live network-ID gate.

## Validation still required

This is derived entirely from static analysis; it has NOT been run in a live
match. Enable the env var, confirm: land with sniper while holding jump → crouch
pose returns; non-sniper jump/land visuals unchanged; multiplayer remote persons
still animate (Person::Simulate is shared sim, so remote pilots run the same
patched branch — verify no desync of the crouch state across host/client).
