# BZCP Patch Atlas

Generated from `_bzcp.dll`, `winmm.bin`, the GOG `battlezone98redux.exe`, and direct Ghidra listing data.

## Summary

- Patch writes recovered: `36`
- Unique `_bzcp.dll` hook targets: `30`
- `_bzcp.dll` PDB: `F:\Battlezone\Janne DLL Shim and Lua\bzpre\Release\_bzcp.pdb`
- `winmm.bin` PDB: `F:\Battlezone\Janne DLL Shim and Lua\bzpre\Release\winmm.pdb`
- Patch kinds:
  - `jmp5`: `29`
  - `rel32`: `2`
  - `u32`: `4`
  - `u8`: `1`
- Patch categories:
  - Lobby / network / commands: `6`
  - Map UI / filters / hop-fix: `22`
  - Ogre / resources: `1`
  - Vehicle list / mod assets: `4`
  - Version / CLI constants: `3`

## Clean-Room Shim Alignment

- Correct alignments:
  - `0x0079B85F`, `0x00799279`, `0x00799377` are correctly identified as the three hop-fix detours.
  - `0x0078DD4E` and `0x00618C2F` are now patched as the real version-string operand sites.
  - `0x007AA5A1` is now named and patched as the original vehicle control branch fix.
- Probe-only alignments:
  - `0x007680D6` and `0x00799116` correspond to real `_bzcp.dll` patch sites, but the clean-room shim only probes them.
- Remaining intentionally deferred hook:
  - `0x0062480B` is the original `/help` and `/ban` command intercept; the clean-room shim no longer mislabels it, but does not port it yet.

## All Patch Writes

| # | Name | Category | BZR VA | Function | Containing Instruction | Kind | Payload | Open Shim |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 1 | Map Sorting | Map UI / filters / hop-fix | `0x007680D6` | `007680d0` | `007680d6` `MOV dword ptr [EBP + -0x8],ECX` | `jmp5` | `jmp5 -> _bzcp+0x0A1E0` | `probe_only` |
| 2 | Map Filters 1/8 | Map UI / filters / hop-fix | `0x007A31D9` | `007a3160` | `007a31d9` `PUSH 0x89b3e0` | `jmp5` | `jmp5 -> _bzcp+0x0BF50` | `unmodeled` |
| 3 | Map Filters 2/8 | Map UI / filters / hop-fix | `0x00752A82` | `00752a50` | `00752a82` `CALL 0x00752ed0` | `jmp5` | `jmp5 -> _bzcp+0x0C9D0` | `unmodeled` |
| 4 | Map Filters 3/8 | Map UI / filters / hop-fix | `0x0079D6B1` | `0079d6b0` | `0079d6b1` `MOV EBP,ESP` | `jmp5` | `jmp5 -> _bzcp+0x0A040` | `unmodeled` |
| 5 | Map Filters 4/8 | Map UI / filters / hop-fix | `0x0079D691` | `0079d690` | `0079d691` `MOV EBP,ESP` | `jmp5` | `jmp5 -> _bzcp+0x0A060` | `unmodeled` |
| 6 | Map Filters 5/8 | Map UI / filters / hop-fix | `0x00799116` | `00796880` | `00799116` `PUSH EDX` | `jmp5` | `jmp5 -> _bzcp+0x0C9F0` | `probe_only` |
| 7 | Map Filters 6/8 | Map UI / filters / hop-fix | `0x0079920A` | `00796880` | `00799209` `CALL 0x007cb5a0` [+1] | `rel32` | `rel32 -> _bzcp+0x0CAD0` | `unmodeled` |
| 8 | Map Filters 7/8 | Map UI / filters / hop-fix | `0x007998AB` | `00799880` | `007998ab` `MOV EAX,dword ptr [EBP + -0x44]` | `jmp5` | `jmp5 -> _bzcp+0x0CA60` | `unmodeled` |
| 9 | Map Filters 8/8 | Map UI / filters / hop-fix | `0x007997A9` | `007997a0` | `007997a9` `MOV EAX,dword ptr [EBP + -0x8]` | `jmp5` | `jmp5 -> _bzcp+0x0CA80` | `unmodeled` |
| 10 | Map List Rewrite for Hop-Fix 1/3 | Map UI / filters / hop-fix | `0x0079B85F` | `0079b850` | `0079b85f` `MOV EAX,dword ptr [EBP + -0x4]` | `jmp5` | `jmp5 -> _bzcp+0x0CD10` | `implemented` |
| 11 | Map List Rewrite for Hop-Fix 2/3 | Map UI / filters / hop-fix | `0x00799279` | `00796880` | `00799279` `PUSH 0x0` | `jmp5` | `jmp5 -> _bzcp+0x0CD40` | `implemented` |
| 12 | Map List Rewrite for Hop-Fix 3/3 | Map UI / filters / hop-fix | `0x00799377` | `00796880` | `00799377` `CALL EDX` | `jmp5` | `jmp5 -> _bzcp+0x0CD60` | `implemented` |
| 13 | Map List Filter Scrolling | Map UI / filters / hop-fix | `0x00799774` | `00799770` | `00799774` `MOV dword ptr [EBP + -0x4],ECX` | `jmp5` | `jmp5 -> _bzcp+0x0CE20` | `unmodeled` |
| 14 | Map List Coloring | Map UI / filters / hop-fix | `0x007A4440` | `007a4400` | `007a4440` `ADD EAX,0x20` | `jmp5` | `jmp5 -> _bzcp+0x0CEF0` | `unmodeled` |
| 15 | Map List Fix Support 1/3 | Map UI / filters / hop-fix | `0x007A311E` | `007a3110` | `007a311e` `MOV ECX,dword ptr [0x00945574]` | `jmp5` | `jmp5 -> _bzcp+0x0D090` | `unmodeled` |
| 16 | Map List Fix Support 2/3 | Map UI / filters / hop-fix | `0x007A313E` | `007a3130` | `007a313e` `MOV ECX,dword ptr [0x00945574]` | `jmp5` | `jmp5 -> _bzcp+0x0D090` | `unmodeled` |
| 17 | Map List Fix Support 3/3 | Map UI / filters / hop-fix | `0x007A3D63` | `007a3d20` | `007a3d63` `MOV ECX,dword ptr [EBP + -0x8]` | `jmp5` | `jmp5 -> _bzcp+0x0D0B0` | `unmodeled` |
| 18 | Map Filter UI Height | Map UI / filters / hop-fix | `0x00798EAC` | `00796880` | `00798ea8` `MOVSS XMM0,dword ptr [0x008a2abc]` [+4] | `u32` | `u32 0x1002A1D0` | `unmodeled` |
| 19 | Version Notice 1/2 | Version / CLI constants | `0x0078DD4E` | `0078d000` | `0078dd4d` `PUSH 0x8784e4` [+1] | `u32` | `u32 0x100244D0 ("2.2.301CP (Community Patch 0.2)")` | `implemented` |
| 20 | Version Notice 2/2 | Version / CLI constants | `0x00618C2F` | `00618c10` | `00618c2e` `PUSH 0x8784e4` [+1] | `u32` | `u32 0x100244D0 ("2.2.301CP (Community Patch 0.2)")` | `implemented` |
| 21 | CLI Fix | Version / CLI constants | `0x008F068C` | `n/a` | n/a | `u32` | `u32 0x00000920` | `unmodeled` |
| 22 | Vehicle List Mod Fix 1/4 (Force Mod-Scoped Assets 1/3) | Vehicle list / mod assets | `0x00766C4A` | `00766900` | `00766c4a` `CALL 0x00481af0` | `jmp5` | `jmp5 -> _bzcp+0x0D460` | `unmodeled` |
| 23 | Vehicle List Mod Fix 2/4 (Force Mod-Scoped Assets 2/3) | Vehicle list / mod assets | `0x0079A4F4` | `00799d70` | `0079a4f3` `CALL 0x007a3e60` [+1] | `rel32` | `rel32 -> _bzcp+0x0D330` | `unmodeled` |
| 24 | Vehicle List Mod Fix 3/4 (Always Update Vehicle Control) | Vehicle list / mod assets | `0x007AA5A1` | `007aa560` | `007aa5a1` `JNZ 0x007aa60a` | `u8` | `u8 0xEB` | `implemented` |
| 25 | Vehicle List Mod Fix 4/4 (Force Mod-Scoped Assets 3/3) | Vehicle list / mod assets | `0x00798BD9` | `00796880` | `00798bd9` `PUSH ECX` | `jmp5` | `jmp5 -> _bzcp+0x0D440` | `unmodeled` |
| 26 | BZCP BZRNET Integration HOST | Lobby / network / commands | `0x00743C05` | `007436c0` | `00743c05` `LEA EAX,[EBP + 0xffffff00]` | `jmp5` | `jmp5 -> _bzcp+0x0D7B0` | `unmodeled` |
| 27 | BZCP BZRNET Integration CLIENT | Lobby / network / commands | `0x0073E71C` | `0073e240` | `0073e71c` `MOV byte ptr [EBP + -0x4],0x7` | `jmp5` | `jmp5 -> _bzcp+0x0D850` | `unmodeled` |
| 28 | Custom Command /help Handler | Lobby / network / commands | `0x0062480B` | `006247a0` | `0062480b` `PUSH 0x88d53c` | `jmp5` | `jmp5 -> _bzcp+0x0D770` | `deferred` |
| 29 | Ban Button Hook 1/2 | Lobby / network / commands | `0x007D0A2F` | `007d0770` | `007d0a2f` `MOVZX EAX,byte ptr [EBP + 0x20]` | `jmp5` | `jmp5 -> _bzcp+0x0E110` | `unmodeled` |
| 30 | Ban Button Hook 2/2 | Lobby / network / commands | `0x007A6913` | `007a4b60` | `007a6913` `MOV dword ptr [EBP + -0x4],0xffffffff` | `jmp5` | `jmp5 -> _bzcp+0x0E360` | `unmodeled` |
| 31 | Joiner Event Hook | Lobby / network / commands | `0x0073F430` | `0073eeb0` | `0073f430` `CALL 0x00742560` | `jmp5` | `jmp5 -> _bzcp+0x0DD80` | `unmodeled` |
| 32 | Map Icon Hook (Map Select) | Map UI / filters / hop-fix | `0x007A42F5` | `007a4260` | `007a42f5` `MOV AL,byte ptr [EAX + 0x38]` | `jmp5` | `jmp5 -> _bzcp+0x0E560` | `unmodeled` |
| 33 | Map Icon Hook (Lobby) | Map UI / filters / hop-fix | `0x007A1FAD` | `007a1e20` | `007a1fad` `CALL 0x007527e0` | `jmp5` | `jmp5 -> _bzcp+0x0E5A0` | `unmodeled` |
| 34 | Ogre Resource Loader | Ogre / resources | `0x00664865` | `00664110` | `00664865` `JMP 0x00664755` | `jmp5` | `jmp5 -> _bzcp+0x0E950` | `unmodeled` |
| 35 | Map list icon draw coordinate adjustments | Map UI / filters / hop-fix | `0x007A39DF` | `007a3160` | `007a39df` `MOV ECX,dword ptr [EAX + 0x2c]` | `jmp5` | `jmp5 -> _bzcp+0x0E9C0` | `unmodeled` |
| 36 | Lobby map name for unknown map | Map UI / filters / hop-fix | `0x007A18F8` | `007a11e0` | `007a18f8` `LEA ECX,[EBP + 0xfffffee4]` | `jmp5` | `jmp5 -> _bzcp+0x0EAF0` | `unmodeled` |

## Unique `_bzcp.dll` Hook Targets

| Target | Note | Used By | Preview |
| --- | --- | --- | --- |
| `0x1000A040` |  | `4` | `MOV EBP,ESP; MOV ECX,dword ptr DS:[0x945564]; MOV byte ptr [0x1002ab12],0x1` |
| `0x1000A060` |  | `5` | `MOV EBP,ESP; MOV ECX,dword ptr DS:[0x945564]; MOV byte ptr [0x1002ab12],0x0` |
| `0x1000A1E0` |  | `1` | `MOV EAX,dword ptr [EBP + 0x8]; MOV dword ptr [EBP + -0x4],EAX; MOV ECX,dword ptr [EBP + -0x4]` |
| `0x1000BF50` |  | `2` | `MOV ECX,dword ptr [EBP + 0xfffffe3c]; MOV dword ptr [EBP + -0x4],ECX; MOV ECX,dword ptr [EBP + -0x4]` |
| `0x1000C9D0` |  | `3` | `MOV dword ptr [EBP + -0x8],ECX; MOV ECX,EBP; ADD ECX,0x8` |
| `0x1000C9F0` |  | `6` | `PUSH EDX; PUSH 0x20; PUSH 0x1000a0a0` |
| `0x1000CA60` |  | `8` | `MOV byte ptr [0x1002ab11],0x1; MOV EAX,dword ptr [EBP + -0x44]; MOV ECX,dword ptr [EAX + 0x17c]` |
| `0x1000CA80` |  | `9` | `MOVZX EAX,byte ptr [0x1002ab11]; TEST EAX,EAX; JZ 0x1000caa3` |
| `0x1000CAD0` |  | `7` | `PUSH EBP; MOV EBP,ESP; PUSH ECX` |
| `0x1000CD10` | Hop-Fix 1 trampoline | `10` | `MOV EAX,dword ptr [EBP + -0x4]; MOV dword ptr [EBP + -0x4],EAX; MOV ECX,dword ptr [EBP + -0x4]` |
| `0x1000CD40` | Hop-Fix 2 trampoline | `11` | `MOV EAX,[0x1002ad84]; MOV ECX,dword ptr [EAX]; CALL 0x1000cb40` |
| `0x1000CD60` | Hop-Fix 3 trampoline | `12` | `CALL EDX; MOV EAX,dword ptr [EBP + 0xffffff5c]; MOV dword ptr [EBP + -0x4],EAX` |
| `0x1000CE20` |  | `13` | `MOV dword ptr [EBP + -0x4],ECX; MOV EAX,dword ptr [EBP + 0x8]; MOV dword ptr [EBP + -0x4],EAX` |
| `0x1000CEF0` |  | `14` | `MOV [0x1002af84],EAX; MOV EDX,dword ptr [EBP + -0x4]; MOV dword ptr [0x1002af88],EDX` |
| `0x1000D090` |  | `15, 16` | `MOV ECX,dword ptr [0x1002adc4]; MOV ECX,dword ptr [ECX]; CALL dword ptr [0x1002adc0]` |
| `0x1000D0B0` |  | `17` | `MOV ECX,dword ptr [0x1002adc4]; MOV ECX,dword ptr [ECX]; CALL dword ptr [0x1002adc0]` |
| `0x1000D330` |  | `23` | `MOV dword ptr [0x1002ac30],ECX; JMP 0x1000d0d0; PUSH EBP` |
| `0x1000D440` |  | `25` | `MOV dword ptr [0x1002af20],ECX; MOV ECX,dword ptr [0x1002af20]; CALL 0x1000d340` |
| `0x1000D460` |  | `22` | `POP dword ptr [EBP + -0x4]; PUSH dword ptr [EBP + -0x4]; CALL dword ptr [0x1002adfc]` |
| `0x1000D770` |  | `28` | `MOV EDX,dword ptr [EBP + 0xc]; MOV dword ptr [0x1002af24],EDX; MOVZX EDX,byte ptr [EBP + 0x8]` |
| `0x1000D7B0` |  | `26` | `MOV byte ptr [EBP + -0x4],0xc; LEA EAX,[EBP + 0xffffff00]; PUSH EAX` |
| `0x1000D850` |  | `27` | `MOV byte ptr [EBP + -0x4],0x7; LEA ECX,[EBP + -0x40]; PUSH ECX` |
| `0x1000DD80` |  | `31` | `MOV EAX,dword ptr [EBP + 0xc]; MOV [0x1002af34],EAX; MOV dword ptr [0x1002af38],ECX` |
| `0x1000E110` |  | `29` | `MOVZX EAX,byte ptr [EBP + 0x20]; MOV [0x1002af58],EAX; MOV ECX,dword ptr [EBP + 0x8]` |
| `0x1000E360` |  | `30` | `MOV ECX,dword ptr [EBP + 0xffffff28]; MOV dword ptr [0x1002af5c],ECX; MOV ECX,dword ptr [0x1002af5c]` |
| `0x1000E560` |  | `32` | `MOV [0x1002af60],EAX; MOV AL,byte ptr [EAX + 0x38]; MOVZX ECX,AL` |
| `0x1000E5A0` |  | `33` | `MOV EAX,EBP; ADD EAX,0xffffff44; ADD EAX,-0x38` |
| `0x1000E950` |  | `34` | `CALL 0x1000e5d0; JMP dword ptr [0x1002aec4]; MOVSS XMM1,dword ptr [0x1002af68]` |
| `0x1000E9C0` |  | `35` | `MOVSS XMM0,dword ptr [EBP + 0xfffffde8]; MOVSS dword ptr [0x1002af68],XMM0; MOVSS XMM0,dword ptr [EBP + 0xfffffe04]` |
| `0x1000EAF0` |  | `36` | `LEA EAX,[EBP + -0x28]; MOV [0x1002ac28],EAX; LEA EAX,[EBP + 0xfffffec4]` |

## Notes

- `jmp5` entries replace the full 5-byte site with `E9 rel32` into `_bzcp.dll`.
- `rel32` entries rewrite only the 4-byte relative operand of an existing `CALL` or `JMP`-style instruction.
- `u32` entries rewrite immediate values or absolute data references inside existing instructions.
- `u8` entries are single-byte branch or flag flips.