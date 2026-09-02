# BZ 1.4 legacy AI — implementation summary (2026-09-01 — research only)

**Status:** No runtime patch applied in this pass. Research phase only, per Implementation Policy (research first, narrow hooks, stock untouched by default).

**Proven hook point:** `kGogAttackTaskDoStateEntryAddr = 0x00478A50` (`bzr_hooks.cpp:1029`, `ExpectedBytesMatchAt`). This is `AttackTask::DoState` in Redux (GOG v2.2.301), structurally identical to 1.5 `0x40F25B`.

**What would be changed (when justified):**

* `src/patches/bzr_hooks.cpp` — add `IsLegacyAiProcess(Task*)` helper reading `GameObjectClass aiName` hash or `RtimeClass` name at task/process creation, store `bool isLegacy` in a non-serialized side map keyed by `AiProcess*` or `Task*` (prefer `task+0x104` group-ptr adjacent spare or external hash_map; do not grow serialized struct).
* Gate at `FUN_00478A50` case handlers:
  - D1: `case 2` `AbleToHit` → `if (isLegacy) next=7 else next=10` (1 byte patch + branch)
  - D2: `case 7` replace `IsBuilding || now>start+10` with `ReadEnemyTaskState(+0xAC) in {2,5,7} →10 else SidewaysAndClose(0x488D0) →8` (requires helper to resolve enemy task: `GetHandle at +0x1C` → `FindObject` → `GetTask at vtbl+0x30` → `state at +0xAC` with Redux offset translation)
  - D4: `case 8` `now>start+8.0` → `if (isLegacy) next=7 else next=9`
  - D3: `case 9` suppress `timer+3.0` branch when legacy

* `GameObjectClass` registration in `BZMR` init: call `RtimeClass::RtimeClass(&legacyRtimeClass, "TankLegacyFriend", LegacyCreateObject)` and sibling for Enemy, similar to `0x5CA6CF` sequence. Expose via ODF: duplicate `avtnk.odf` → `avtnklf.odf` (≤8 chars: e.g. `avtnklgf.odf` if needed for file variant) with `aiName="TankLegacyFriend"`.

**Files that would be touched (narrow):**

* `src/patches/bzr_hooks.cpp` — new `LegacyAi` namespace (~100 lines) + 4 branch gates
* `src/patches/trampolines.cpp` — if hook needs trampoline for `FUN_00478A50`
* `include/ai_legacy.h` — new header for `IsLegacy` helper and FNV `0x811C9DC5` hash (reuse existing `ParameterDB` hash routine at `0x4166B8`)

**Configuration semantics (proposed):**

* `openshim.ini [SinglePlayer] Legacy14AI = 0/1` (master, default 0)
* Per-ODF: `aiName = "TankLegacyFriend"` selects legacy regardless of master if master=1? Or master gates registration — unknown aiName then falls back gracefully (TraceError path). Recommend master=1 registers legacy RtimeClass entries; ODF selects per-unit.

**Test ODFs / mission:** see `bz14_legacy_ai_integration_design_20260901.md` §5 harness. ODF variant `avtnk_legacy.odf` (or 8-char `avtnklf.odf`) copies `avtnk.odf` with `aiName="TankLegacyFriend"` / `aiName2="TankLegacyEnemy"`.

**Validation performed this pass:** compile/static checks only (no runtime hook installed). `ai_nonvirtual_method_map.tsv` Proven rows cross-checked against decompiles; `bz14_cross_agent` F1 proven via disasm sites `0x40CFA3` vs `0x40F301`; Redux hook address byte-validated in existing code.

**Known gaps:**  IsStuck `flags &0x20000` clear and `flags&4` exemption need offset sited in Redux (`FUN_006027F0`); DoStuck 7-state needs `00407000` probe sited; UpdateWeapon/AbleToHit split needs second 1.4 address; team-vs-perceivedTeam selector for aiName/aiName2 needs live probe (spawn with known team and log which RtimeClass is instantiated); unknown-aiName behavior needs probe.

**Next step:** run live probe mission logging `RtimeClass::CreateObject` for `TankFriend` vs `TankLegacyFriend` and verify per-unit coexistence in same engagement.

