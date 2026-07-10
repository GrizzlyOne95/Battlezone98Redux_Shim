# Live Process Scan Findings — 2026-07-06 (GOG battlezone98redux.exe v2.2.301)

Session goal: close the FeaturesToLookInto items gated on **live process scanning** —
AI cluster (#7, #43) and Discovery cluster (#17, #27). Method: launched GOG into
`misn06.bzn /edit`, skipped VO with SendInput space, then scanned the live process
(PID varies) with `probe_ai_craft_controls.py` and static RTTI re-derivation against
the on-disk exe. Advisory PDB = `battlezone98redux.pdb` (2016 build — **advisory only**).

## CRITICAL cross-cutting finding: advisory PDB addresses have DRIFTED

The shipped `battlezone98redux.pdb` is from the **2016** build; the live GOG exe is the
**Jan 2026** 2.2.301 build. Function VAs have drifted **non-uniformly** (different deltas
per function), so raw PDB addresses must NOT be used for hooks. Verified by disassembling
advisory VAs on the live exe:

| Advisory symbol | Advisory VA | Live bytes | Verdict |
|---|---|---|---|
| `_StartMusic` | 0x00406670 | `push ebp;mov ebp,esp` | still matches (but see #17 — it's a dead stub) |
| `_StopMusic` | 0x004068E0 | `push ebp;mov ebp,esp` | still matches |
| `OffensiveProcess::DoSubTask` | 0x004DFE70 | `push ebp;mov ebp,esp;call` | still matches |
| `NetPlayer::GetPlayerName` | 0x004D9570 | `push ebp;mov ebp,esp;mov eax,[ebp+8]` | still matches |
| `RecycleTask::IsStuck` | 0x00507570 | `les ecx,[eax]` (garbage) | **DRIFTED** |
| `RecycleTask::DoStuck` | 0x00507640 | garbage | **DRIFTED** |
| `RecycleTask::InitLookingForScrap` | 0x00506CC0 | garbage | **DRIFTED** |
| `UnitTask::IsStuck` | 0x005427B0 | mid-function | **DRIFTED** |
| `GoodScrapPosition(f,f)` | 0x004E9E60 | garbage | **DRIFTED** |
| `CSteamLobby::GetCurrentUser` | 0x004D8320 | garbage | **DRIFTED** |

**Rule going forward:** re-derive every hook site on the live exe via RTTI (for virtuals)
or pattern/xref (for `__cdecl`/non-virtual). Do not trust PDB VAs. This is the same failure
that broke #46 splinter (advisory 0x005242F0 had drifted; re-derived via RTTI slot).

## #7 — AI craft control block (live scan) — LOCATED, jump field NOT yet confirmed

Live probe (`probe_ai_craft_controls.py`) against the running mission confirms the RE note's
model: the **craft-side control block is a pointer at `[obj + 0xF4]`**, and the movement
consumer reads control fields from it. Confirmed live consumer sites in the GechProcess /
movement neighborhood `0x004706C7`–`0x0047073F`:

- `mov ecx,[eax+0xF4]` then `addss xmm0,[ecx+0xC0]`  → **braccel @ control+0xC0**
- `mov eax,[edx+0xF4]` then `addss xmm0,[eax+0xBC]`  → **steer   @ control+0xBC**
- adjacent reads at `+0xB4`, `+0xB8` (more control/velocity fields)

Advisory control-block layout (from probe, **only steer/braccel verified live**):
`+0xBC steer, +0xC0 braccel, +0xC4 turbo, +0xC8 pitch, +0xCC strafe, +0xD0 jump,
+0xD4 eject, +0xD8 deploy, +0xDC abandon`.

**Caveat (verified):** a blind scan for `+0xD0..+0xDC` (jump/eject/deploy/abandon) is
noise-dominated — hits land almost entirely in `GameObject::Load/Save/PostLoad` (field
serialization), `DayWrecker::*`, `DayWreckerClass::Build`, and `EditTerrain::CmdBlur`, NOT
in a control producer/consumer. So `+0xD0 = jump` is still UNCONFIRMED. To close it, read a
live player craft's `[obj+0xF4]` block and diff the bytes across a jump keypress (needs
interactive driving; not done this session). Do NOT ship a jump setter on the advisory
offset alone.

## #43 — AI process vtables re-derived via RTTI (current build) — VERIFIED addresses

RTTI walk (type-descriptor → COL → vftable) on the live exe. Current vftable VAs:

| Class | vftable VA |
|---|---|
| RecycleTask | **0x008868BC** |
| UnitTask | **0x00889F14** |
| OffensiveProcess | **0x00884C28** |
| TurretTankProcess | **0x00889710** |
| ScavengerProcess | **0x008871D8** |
| GechProcess | **0x0087A13C** |

All 28 slots dumped are valid function prologues. Offensive / TurretTank / Gech share the
inherited UnitProcess base slots (e.g. 0x005FA6E0, 0x005FB1E0, 0x005FB720, 0x00471860) and
differ only on overridden slots — use the diff to pin per-class overrides (e.g. `DoSubTask`).
Non-virtual targets (`RecycleTask::IsStuck/DoStuck/InitLookingForScrap`, `UnitTask::IsStuck`,
`GoodScrapPosition`) are NOT in a vtable and still need pattern/xref re-derivation before use.
The #43 ODF parser fields are already cached in the shim; wiring is what remains, per hook.

## #17 — Music / soundtrack — legacy wrappers are DEAD STUBS (verified)

On the live GOG build the legacy music wrappers do nothing:

- `_StartMusic` @0x00406670 → `mov ecx,0x992361; call 0x416820; ret` where 0x416820 is an
  identity stub (`mov eax,ecx; ret`). Returns a constant, no playback.
- `_StopMusic` @0x004068E0 → same shape, stub.
- `_PauseMusic` @0x00406820 / `_UnPauseMusic` @0x00406880 → `xor eax,eax; ret` (empty).

So **do not hook the legacy `*Music` wrappers** — Redux's real soundtrack is the native OGG
path (`OggManager::Play/Stop/Pause/Resume/Release(int)`, `CStreamingOggSound`, `%02d.ogg`,
`libvorbisfile`). Advisory `OggManager::Play` @0x004E0AF0 has DRIFTED (landed mid-function),
so re-derive `OggManager::*` on the live exe (anchor via `_MusicOggIdx`/`_MusicStarted`
globals or the `%02d.ogg` format-string xref) before exposing to Lua. This confirms the
note's recommendation to expose the OggManager soundtrack manager rather than generic .ogg
through StartSound.

## #27 — Nickname live-update — Steam-only path, limited on GOG (verified)

The nickname/user machinery found in the PDB is Steam-centric: `cUser` (vftable 0x00655254
advisory), `CSteamLobby::GetCurrentUser`/`GetUserBySteamID`, `NetPlayer` keyed by `CSteamID`,
`NetPlayerMgr::OnP2PReceived`. `CSteamLobby::GetCurrentUser` advisory VA has drifted. On GOG
(no Steam lobby) the live post-startup nickname update path is not exercised the same way;
`NetPlayer::GetPlayerName` @0x004D9570 still matches and is a safe read anchor. Full nickname
live-update remains largely a Steam-build feature — GOG coverage will be partial, as the note
already flagged.

## Environment notes for future live sessions

- x86 crash/debug: WinDbg cdb at
  `C:\Program Files\WindowsApps\Microsoft.WinDbg_<ver>_x64__8wekyb3d8bbwe\amd64\cdb.exe`
  (resolve version via `Get-AppxPackage Microsoft.WinDbg`). The bundled `cdb.cmd` wrapper
  path goes stale when WinDbg auto-updates.
- Launch into a live mission: `battlezone98redux.exe misn06.bzn /edit`, then SendInput VK_SPACE
  a few times once BZLogger shows `Sim Startup: Waiting For VO`.
- Live scan tooling: `reverse_engineering/probe_ai_craft_controls.py` (OpenProcess +
  ReadProcessMemory + capstone). RTTI re-derivation script pattern is in this session's log.
- `battlezone98redux.pdb` is ADVISORY (2016). Names good, addresses drifted — always verify.
