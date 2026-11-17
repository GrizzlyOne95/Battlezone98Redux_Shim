# Scoping: walkers immune to seismic launch (BZR OpenShim)

**Decision (2026-11-16):** per-ODF key on the Thumper's [SeismicWaveClass] (synced with the mod), not a global ini option.

Corpus root D = Battlezone_Source\BZ1\Redux\openshim_re_corpus\bzr_gog_best_effort\ghidrecomp\results\bins\battlezone98redux.exe-6777ca\decomps
(GOG decomp; the Ghidra MCP project binary /battlezone98redux.exe-007c64 = shipping GOG exe; re-decompiled 005cf510, identical to corpus.)
PDB-named reference: Battlezone_Source\BZ1\1.5\functions\0053\00538e78_SeismicWave_Simulate.c (different build, same logic).

## 1. How the effect works
- "Thumper" weapon fires ordnance of class SeismicWaveClass (ODF [SeismicWaveClass]; odf_compat.cpp L68 lists "seismicwaveclass").
  Class ctor FUN_005cea80 (D, L16-35) reads ODF keys into class+0x78.. : waveRadius 0x78, waveHeight 0x84, startOffset 0x88,
  rampUp 0x8c, rampDown 0x94, sweepOmega 0x9c, sweepVeloc 0xa0, shakeFrequency 0xa4, shakeOmega 0xa8, shakeVeloc 0xac,
  walkerScale 0xb0, towerScale 0xb4, dampOmega 0xb8, levelOmega 0xbc, buildingScale 0xc0.
  (field order = 1.5 ctor 005388e7 L~35-70; offsets GOG = 1.5 + 8. Key names UNVERIFIED for hashes except walkerScale/towerScale/dampOmega/levelOmega,
  confirmed by 1.5 changelog.txt L1723-1725 "Added walkerScale and towerScale / dampOmega and levelOmega properties to the ODF".)
- Per-tick Simulate = FUN_005cf510 (GOG exe, ctor FUN_005cef80, Init, UpdateExtents FUN_005cf100). It (a) raises terrain heights (L~268-300),
  then (b) Range-searches objects within radius*1.5+20 (FUN_005b28e0, L~346), loop at LAB_005cfd63.
- Victim selection: any object whose vtbl[+0x18]()->+0x1C (class id; 1.5 enum types.txt L7155-7165: 1 HELICOPTER, 3 POWERUP, 6 VEHICLE, 2 STRUCTURE1,
  10 STRUCTURE2, 7 SCRAP, 5 SIGN) is in distance. Weight local_260 = scale*dt*falloff (L~340-347).
- Class ids 1/3/6 (L355): mobile objects. Hovercraft AND walkers are both CLASS_ID_VEHICLE(6) (UNVERIFIED that walker==6; the code treats them identically
  until the classSig test). Sequence: angular impulse block (sweepOmega 0x9c L385, shakeOmega 0xa8 noise L409-417), then classSig test (obj class +0x14):
  0x54555252 'TURR' -> scale omega by towerScale 0xb4 (L421-431); 0x57414c4b 'WALK' -> scale omega by walkerScale 0xb0 (L432-442).
  Then damp (0xb8) and level (0xbc) torque written to object omega (L444-470, writes into obj+0x24..).
  THEN the LINEAR kick: local_38 = sweepVeloc(0xa0)*weight*dir (+ noise shakeVeloc 0xac) (L496-510) and `FUN_004a75b0(&local_38)` (L511).
  FUN_004a75b0 = GameObject::AddVelocity: adds to obj+0x12c/0x130/0x134 and recomputes speed (cited from decomp of 004a75b0).
  dir = normalize(terrain normal + wave front + (0,1,0)) (L~372-378: local_23c = front + normal; local_238 = front.y + normal.y + 1.0; FUN_004621a0 normalizes). Upward bias.
- Why walkers fly: walkerScale ONLY scales the angular (omega) block. The linear AddVelocity at L511 has no walker/class test at all, so a walker
  receives the same vertical velocity as a hover tank. (Class ids 2/10/7/5 = buildings/scrap take a different branch L513+, with buildingScale 0xc0; they get
  terrain-snapped, no velocity.)
- Cross-refs to AddVelocity 004a75b0 (Ghidra): 004aa903, 004aacfc (FUN_004aa630), 004c0fbc, 0050ca54, 005cf510@005d08e1, 005d0d80@005d12aa.
  => the seismic call site is 0x005d08e1 (only one inside Simulate). 005d0d80 is another caller (UNVERIFIED which class; probably other ordnance/shockblast).
  The exe-side `FUN_005cf510` label has no PDB symbol; fn entry 0x005cf510.

## 2. Existing hooks
- OpenShim: only src\patches\seismic_wave_extent_clamp.cpp (hooks UpdateExtents 0x005cf100 prologue 55 8B EC 83 EC 24 89 4D FC, 9 bytes; fixes a heap overrun).
  Registered bzr_hooks.cpp L1653, bzr_hooks_internal.h L2232. Nothing on walkers, per-ODF immunity, or thumper velocity. Docs\ has no seismic design doc
  (only MULTIPLAYER_BUG_SOURCE_INVESTIGATION.md / BBCode mentions).
- ExtraUtilities: examples\PhysicsImpact.lua L62 only has a "seismic" knockback table entry (Lua-side impulse, not a stock immunity). No walker immunity.
- Stock ODF workaround today: set walkerScale = 0 in [SeismicWaveClass] (kills walker tumble only, NOT launch) -- per above; sweepVeloc/shakeVeloc are
  class-wide so lowering them affects every unit type (and the Thumper's point). Actual thumper ODF values: UNVERIFIED (ODF not read).
- BZ2/BZCC: bzcc_battlezone2_20190509 decomp has Simulate-00645912.c / SeismicWaveClass-00646d66.c in battlezone2_unpacked (BZ2 1.3-era, not BZCC); no
  walker-immunity flag seen in the file list (not read in detail -> UNVERIFIED). BZ1 changelog L143: "Restored original Turret and Gun Tower reaction to seismic wave".

## 3. Proposal (smallest)
Option A (recommended): detour the call site / wrapper only for the velocity add.
- Hook FUN_005cf510 call to AddVelocity at 0x005d08e1 (5-byte E8 rel32 call; patch to a thunk) OR hook the 004a75b0 entry with a "currently in seismic" TLS flag
  (more fragile: 4 other callers). Call-site patch preferred: thunk(this=ecx obj? -- ecx at call = target GameObject `local_25c`, arg=&local_38) checks whether
  the target's class sig (obj->vtbl[+0x18]()->+0x14) == 0x57414c4b and OpenShim option on; if so skip (or scale arg by factor) else call stock.
  Need to re-read register setup at 0x005d08e1 with disassembly before writing (UNVERIFIED: ecx=target assumption, matches thiscall of FUN_004a75b0).
- Partial effect: easy. Scale arg local_38.y (vertical) by k (0 => no launch, keep horizontal shove) and/or scale whole vector; omega/damage unaffected.
  "Stagger" = keep omega block as is (walkerScale already ODF-tunable) -- no extra work.
- Config: global [Fixes]/[Gameplay] ini toggle `SeismicWalkerImmune` (+ optional `SeismicWalkerVerticalScale`) is simplest. Per-ODF key (`seismicImmune` in
  [WalkerClass]/[CraftClass]) needs an ODF read path at class build time (OpenShim has odf_compat.cpp; extra storage keyed by class ptr) = more work;
  better alternative per-ordnance: new key `walkerVelocityScale` in the thumper's [SeismicWaveClass] read via the same ParameterDB hook as the stock ctor.
- MP determinism: velocity add happens inside sim tick on every peer (same code path), so every client must run the same option value; put the toggle in the
  host-synced options / require it be in lobby-sync or mod-ODF-driven (ODF-driven is inherently synced, ini is not). A mismatched peer will desync (UNVERIFIED how BZR MP validates).
- Effort: S for global ini toggle (call-site patch + 1 option + test); M if per-ODF key; plus live test (thumper vs walker) under the lock protocol.
- Alternative needing zero native work: mod walker ODFs cannot opt out; but a custom Thumper ODF could set sweepVeloc/shakeVeloc low (affects all targets).
