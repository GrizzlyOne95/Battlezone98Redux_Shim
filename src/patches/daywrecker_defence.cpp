// daywrecker_defence.cpp
// BZR Open Shim - [SinglePlayer] DaywreckerDefence (default 0): AI defence
// against an enemy Daywrecker in flight and an enemy Comet (radarmsl, class
// Torpedo). Single player only; kill switch OPENSHIM_DISABLE_DAYWRECKER_DEFENCE.
//
// Stock (GOG 2.2.301): both are PowerUp subclasses (class category 3), so
// Craft::GetCommand (0x004AE110) answers CMD_GO before it tests for an enemy,
// GetClosestEnemyWithin (0x00463240) never picks them, and EvadeOrdnanceForce
// (0x005FD5F0) only walks Ordnance::ordnanceList, so nobody dodges them.
//
// Hooks (Docs/DAYWRECKER_AI_DEFENCE_RESEARCH.md section 4):
//  1. GetCommand, vtable slot 13: every copy of Craft::GetCommand (Craft,
//     HoverCraft, Minelayer, Person, SAV, Walker, Wingman) and TurretTank's
//     slot (chained after TurretAttackOrders). GO on an enemy bomb becomes
//     ATTACK for an armed craft. The bomb keeps its yellow PowerUp colour
//     (decision 8).
//  2. DayWrecker and Torpedo Simulate, vtable slot 15: each live bomb
//     refreshes a handle registry and, every 0.5 s, scans the object list for
//     enemy craft within 150 m that have detected it the way stock AI detects
//     a Person (decision 9: XZ <= 70 m and in the front half-space). Up to 4
//     idle or defending armed units per bomb get SetCommand(ATTACK, bomb);
//     3 s per-unit cooldown.
//  3. EvadeOrdnanceForce, inline detour: after the stock force, adds a force
//     computed with the stock maths for each registry bomb the unit has
//     detected and is not attacking or aiming at, then re-applies the stock
//     normalise-to-20 rule.
//
// Rules: include/daywrecker_defence_policy.h (unit-tested).
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "com_vtable_patch.h"
#include "daywrecker_defence_policy.h"
#include "hook_engine.h"
#include "patcher.h"
#include "shim_log.h"

#include <windows.h>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            namespace Policy = DaywreckerDefencePolicy;

            using FnGetCommand = int(__thiscall*)(void* craft, void* target);
            using FnSimulate = void(__thiscall*)(void* self, float dt);
            using FnEnemyP = bool(__thiscall*)(void* self, void* other);
            using FnSetCommandObj = void(__thiscall*)(void* obj, int what, void* target);
            using FnGetObj = void*(__cdecl*)(uint32_t handle);
            using FnGetTime = float(__cdecl*)();
            // cdecl, hidden VECTOR_3D return; callers push (ret, unit, current
            // threat, out threat) and `add esp,0x10` (e.g. 0x00602166).
            using FnEvade = float*(__cdecl*)(float* ret, void* unit, void* threat, void** outThreat);

            constexpr size_t kGetCommandSlot = 13;
            constexpr size_t kSimulateSlot = 15;

            // GameObject (complete object) fields, GOG 2.2.301.
            constexpr size_t kIsCargoOffset = 0x9C;    // FUN_00463240: skip when [obj+0x9C] != 0
            constexpr size_t kCurCmdWhatOffset = 0xAC; // Lua GetCurrentCommand 0x005CB5C0
            constexpr size_t kCurCmdWhoOffset = 0xB0;  // Lua GetCurrentWho 0x005CB5F0
            constexpr size_t kNextCmdWhatOffset = 0xCC; // SetCommand 0x004DBD60 writes what
            constexpr size_t kNextCmdWhoOffset = 0xD0;  // ... and who (a handle)
            constexpr size_t kSphereOverrideOffset = 0xF0; // FUN_00462400: sphere at [obj+0xF0]+8
            constexpr size_t kCraftWeaponOffset = 0x1A0;   // Craft::GetCommand armed test
            constexpr size_t kPowerUpStateOffset = 0x228;  // DayWrecker state block
            constexpr size_t kPowerUpFlagsOffset = 0x114;
            constexpr uint32_t kPowerUpAirborne = 0x4;
            // obj76 fields.
            constexpr size_t kObj76FlagsOffset = 0x14;
            constexpr uint32_t kObj76DeadFlag = 0x200;
            constexpr size_t kObj76FrontOffset = 0x38;  // MAT_3D at +0x20, front row at +0x18 (FUN_00462490)
            constexpr size_t kObj76ClassIdOffset = 0x84; // IsCraft FUN_00417e20: 1 or 6
            constexpr size_t kObj76SphereOffset = 0xA0;  // FUN_00462400
            constexpr size_t kSphereRadiusOffset = 0xC;
            constexpr int kClassIdHelicopter = 1;
            constexpr int kClassIdVehicle = 6;

            constexpr size_t kMaxObjects = 4096;

            enum class BombKind
            {
                None,
                DayWrecker,
                Comet,
            };

            bool g_ConfigInitialized = false;
            bool g_Enabled = false;
            bool g_Active = false;
            bool g_GetCommandInstalled = false;
            bool g_DwSimulateInstalled = false;
            bool g_TorpedoSimulateInstalled = false;
            bool g_EvadeInstalled = false;

            uint32_t g_CraftGetCommandAddr = 0;
            uint32_t g_TurretTankGetCommandAddr = 0;
            uint32_t g_DayWreckerVtable = 0;
            uint32_t g_DayWreckerSimulateAddr = 0;
            uint32_t g_TorpedoVtable = 0;
            uint32_t g_TorpedoSimulateAddr = 0;
            uint32_t g_EvadeAddr = 0;
            uint32_t g_EnemyPAddr = 0;
            uint32_t g_SetCommandObjAddr = 0;
            uint32_t g_GetObjAddr = 0;
            uint32_t g_GetTimeAddr = 0;
            uint32_t g_ObjectListGlobal = 0;

            FnGetCommand g_StockCraftGetCommand = nullptr;
            void* g_TurretGetCommandNext = nullptr;
            void* g_DwSimulateNext = nullptr;
            void* g_TorpedoSimulateNext = nullptr;
            InlineDetour32 g_EvadeDetour = {};
            void* volatile g_EvadeTrampoline = nullptr;

            Policy::BombRegistry<> g_Registry;
            Policy::CooldownTable<> g_Cooldowns;
            volatile long g_LogBudget = 400;

            // Change-only decision logs.
            int g_LastOffer = -1;
            uint32_t g_LastScanSummary[Policy::kRegistryCapacity] = {};
            uint32_t g_LastEvadeUnit = 0;
            uint32_t g_LastEvadeBomb = 0;
            bool g_LastEvadeOn = false;

            void LogBudgeted(const wchar_t* fmt, ...)
            {
                if (InterlockedDecrement(&g_LogBudget) < 0)
                    return;
                wchar_t buffer[320];
                va_list args;
                va_start(args, fmt);
                _vsnwprintf_s(buffer, _TRUNCATE, fmt, args);
                va_end(args);
                Log(L"%ls", buffer);
            }

            // ---- fault-safe reads (no C++ objects, so __try is legal) ----

            bool ReadU32(const void* base, size_t offset, uint32_t& out)
            {
                if (reinterpret_cast<uintptr_t>(base) < 0x10000)
                    return false;
                __try
                {
                    out = *reinterpret_cast<const uint32_t*>(static_cast<const uint8_t*>(base) + offset);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            void* ReadPtr(const void* base, size_t offset)
            {
                uint32_t v = 0;
                return ReadU32(base, offset, v) ? reinterpret_cast<void*>(static_cast<uintptr_t>(v)) : nullptr;
            }

            bool ReadVec(const void* base, size_t offset, Policy::Vec3& out)
            {
                if (reinterpret_cast<uintptr_t>(base) < 0x10000)
                    return false;
                __try
                {
                    const float* f = reinterpret_cast<const float*>(static_cast<const uint8_t*>(base) + offset);
                    out = Policy::Make(f[0], f[1], f[2]);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            float NowSeconds()
            {
                if (!g_GetTimeAddr)
                    return 0.0f;
                __try
                {
                    return reinterpret_cast<FnGetTime>(static_cast<uintptr_t>(g_GetTimeAddr))();
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return 0.0f;
                }
            }

            void* SafeGetObj(uint32_t handle)
            {
                if (!g_GetObjAddr || handle == 0)
                    return nullptr;
                __try
                {
                    return reinterpret_cast<FnGetObj>(static_cast<uintptr_t>(g_GetObjAddr))(handle);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return nullptr;
                }
            }

            bool SafeEnemyP(void* self, void* other)
            {
                if (!g_EnemyPAddr || !self || !other)
                    return false;
                __try
                {
                    return reinterpret_cast<FnEnemyP>(static_cast<uintptr_t>(g_EnemyPAddr))(self, other);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool SafeSetAttack(void* unit, void* bomb)
            {
                if (!g_SetCommandObjAddr || !unit || !bomb)
                    return false;
                __try
                {
                    reinterpret_cast<FnSetCommandObj>(static_cast<uintptr_t>(g_SetCommandObjAddr))(
                        unit, Policy::kCmdAttack, bomb);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            uint32_t HandleOf(void* obj)
            {
                int handle = 0;
                return TryGetGameObjectHandleValue(obj, handle) ? static_cast<uint32_t>(handle) : 0;
            }

            void* Obj76Of(void* obj)
            {
                return ReadPtr(obj, kGameObjectObjOffset);
            }

            // An enemy-or-not bomb: a Daywrecker with the airborne bit, or a
            // live Torpedo (Comet). Identified by the primary vtable.
            BombKind BombKindOf(void* obj)
            {
                uint32_t vtable = 0;
                if (!ReadU32(obj, 0, vtable) || vtable == 0)
                    return BombKind::None;
                if (vtable == g_DayWreckerVtable)
                {
                    void* state = ReadPtr(obj, kPowerUpStateOffset);
                    uint32_t flags = 0;
                    return state && ReadU32(state, kPowerUpFlagsOffset, flags) && (flags & kPowerUpAirborne)
                               ? BombKind::DayWrecker
                               : BombKind::None;
                }
                if (vtable == g_TorpedoVtable && g_TorpedoVtable != 0)
                {
                    uint32_t flags = 0;
                    void* obj76 = Obj76Of(obj);
                    return obj76 && ReadU32(obj76, kObj76FlagsOffset, flags) && !(flags & kObj76DeadFlag)
                               ? BombKind::Comet
                               : BombKind::None;
                }
                return BombKind::None;
            }

            bool PositionOf(void* obj, Policy::Vec3& out)
            {
                float p[3] = {};
                if (!TryGetGameObjectWorldPosition(obj, p))
                    return false;
                out = Policy::Make(p[0], p[1], p[2]);
                return true;
            }

            // GameObject::GetSphere (FUN_00462400) radius.
            float RadiusOf(void* obj)
            {
                void* sphere = ReadPtr(obj, kSphereOverrideOffset);
                const uint8_t* base = nullptr;
                if (sphere)
                    base = static_cast<const uint8_t*>(sphere) + 8;
                else if (void* obj76 = Obj76Of(obj))
                    base = static_cast<const uint8_t*>(obj76) + kObj76SphereOffset;
                uint32_t raw = 0;
                if (!base || !ReadU32(base, kSphereRadiusOffset, raw))
                    return 0.0f;
                float r = 0.0f;
                memcpy(&r, &raw, sizeof(r));
                return r > 0.0f && r < 1000.0f ? r : 0.0f;
            }

            bool FrameOf(void* obj76, Policy::Frame& out)
            {
                const size_t rows = kObj76TransformOffset;
                return ReadVec(obj76, rows, out.right) && ReadVec(obj76, rows + 0xC, out.up) &&
                       ReadVec(obj76, kObj76FrontOffset, out.front);
            }

            bool IsCraftObj76(void* obj76)
            {
                uint32_t classId = 0;
                if (!ReadU32(obj76, kObj76ClassIdOffset, classId))
                    return false;
                return static_cast<int>(classId) == kClassIdHelicopter || static_cast<int>(classId) == kClassIdVehicle;
            }

            bool IsDeadObj76(void* obj76)
            {
                uint32_t flags = 0;
                return !ReadU32(obj76, kObj76FlagsOffset, flags) || (flags & kObj76DeadFlag);
            }

            // Fills the command/target fields the policy reads.
            void ReadOrders(void* unit, Policy::UnitView& u)
            {
                uint32_t v = 0;
                u.curWhat = ReadU32(unit, kCurCmdWhatOffset, v) ? static_cast<int>(v) : -1;
                u.curWho = ReadU32(unit, kCurCmdWhoOffset, v) ? v : 0;
                u.nextWhat = ReadU32(unit, kNextCmdWhatOffset, v) ? static_cast<int>(v) : -1;
                u.nextWho = ReadU32(unit, kNextCmdWhoOffset, v) ? v : 0;
                u.target = ReadU32(unit, kGameObjectTargetHandleOffset, v) ? v : 0;
            }

            bool SinglePlayerNow()
            {
                return IsSinglePlayerSession();
            }

            // ---- 1. GetCommand ------------------------------------------

            int OfferFor(void* self, void* target, int stock)
            {
                if (stock != Policy::kCmdGo || !g_Active || !target)
                    return stock;
                const BombKind kind = BombKindOf(target);
                if (kind == BombKind::None)
                    return stock;
                const bool enemy = SafeEnemyP(self, target);
                const bool armed = ReadPtr(self, kCraftWeaponOffset) != nullptr;
                const int out = Policy::OfferedCommand(stock, true, enemy, armed, g_Enabled, SinglePlayerNow());
                const int key = (out << 4) | (enemy ? 2 : 0) | (armed ? 1 : 0) | (kind == BombKind::Comet ? 8 : 0);
                if (key != g_LastOffer)
                {
                    g_LastOffer = key;
                    LogBudgeted(L"[DWDEF] offer %ls: enemy=%d armed=%d -> cmd %d\n",
                                kind == BombKind::Comet ? L"comet" : L"daywrecker", enemy ? 1 : 0, armed ? 1 : 0, out);
                }
                return out;
            }

            int __fastcall CraftGetCommandHook(void* self, void* /*edx*/, void* target)
            {
                return OfferFor(self, target, g_StockCraftGetCommand(self, target));
            }

            int __fastcall TurretGetCommandHook(void* self, void* /*edx*/, void* target)
            {
                return OfferFor(self, target, reinterpret_cast<FnGetCommand>(g_TurretGetCommandNext)(self, target));
            }

            // ---- 2. Registry and radius scan ----------------------------

            size_t SnapshotObjects(void** out, size_t capacity)
            {
                if (!g_ObjectListGlobal)
                    return 0;
                size_t count = 0;
                __try
                {
                    const uint8_t* vec = *reinterpret_cast<uint8_t* const*>(static_cast<uintptr_t>(g_ObjectListGlobal));
                    if (!vec)
                        return 0;
                    void* const* first = *reinterpret_cast<void* const* const*>(vec);
                    void* const* last = *reinterpret_cast<void* const* const*>(vec + 4);
                    if (!first || last < first || static_cast<size_t>(last - first) > kMaxObjects)
                        return 0;
                    const size_t available = static_cast<size_t>(last - first);
                    for (size_t i = 0; i < available && count < capacity; ++i)
                        if (reinterpret_cast<uintptr_t>(first[i]) >= 0x10000)
                            out[count++] = first[i];
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return 0;
                }
                return count;
            }

            struct ScanCounts
            {
                uint32_t inRadius = 0;
                uint32_t detected = 0;
                uint32_t ordered = 0;
                uint32_t busy = 0;     // detected, but an order or target it keeps
                uint32_t unarmed = 0;  // detected, armed test failed (evades instead)
                uint32_t capped = 0;   // cap or cooldown
            };

            void Scan(void* bomb, uint32_t bombHandle, Policy::BombEntry& entry, size_t slot)
            {
                Policy::Vec3 bombPos;
                if (!PositionOf(bomb, bombPos))
                    return;
                static void* objects[kMaxObjects];
                const size_t n = SnapshotObjects(objects, kMaxObjects);
                void* const player = TryGetHeadlightPlayerObject();
                // Player-team craft are never ordered: their orders are the
                // player's (Defend, Follow) and an ATTACK would replace them.
                uint32_t playerTeam = 0;
                const bool havePlayerTeam =
                    player && ReadU32(player, kGameObjectActualTeamOffset, playerTeam) && playerTeam > 0;
                const bool sp = SinglePlayerNow();
                const float now = NowSeconds();
                ScanCounts c;
                for (size_t i = 0; i < n; ++i)
                {
                    void* const unit = objects[i];
                    if (unit == bomb)
                        continue;
                    void* const obj76 = Obj76Of(unit);
                    if (!obj76 || !IsCraftObj76(obj76) || IsDeadObj76(obj76))
                        continue;
                    Policy::Vec3 pos;
                    Policy::Frame frame;
                    if (!PositionOf(unit, pos) || !FrameOf(obj76, frame))
                        continue;
                    if (!Policy::InRadius(bombPos.x - pos.x, bombPos.z - pos.z, Policy::kScanRadius))
                        continue;
                    ++c.inRadius;
                    if (!Policy::Detects(pos, frame.front, bombPos))
                        continue;
                    ++c.detected;
                    Policy::UnitView u;
                    u.isCraft = true;
                    uint32_t unitTeam = 0;
                    u.isPlayer = unit == player || (havePlayerTeam &&
                                                    ReadU32(unit, kGameObjectActualTeamOffset, unitTeam) &&
                                                    unitTeam == playerTeam);
                    u.hasWeapon = ReadPtr(unit, kCraftWeaponOffset) != nullptr;
                    u.enemy = SafeEnemyP(unit, bomb);
                    uint32_t cargo = 0;
                    u.isCargo = ReadU32(unit, kIsCargoOffset, cargo) && (cargo & 0xFF) != 0;
                    ReadOrders(unit, u);
                    if (u.isPlayer || !u.enemy)
                        continue;
                    const uint32_t unitHandle = HandleOf(unit);
                    const bool ready = g_Cooldowns.Ready(unitHandle, now, Policy::kUnitCooldown);
                    if (Policy::ShouldTargetBomb(u, bombHandle, entry.assigned, ready, g_Enabled, sp))
                    {
                        if (SafeSetAttack(unit, bomb))
                        {
                            ++entry.assigned;
                            ++c.ordered;
                            g_Cooldowns.Mark(unitHandle, now);
                            LogBudgeted(L"[DWDEF] target unit=0x%08X bomb=0x%08X assigned=%d\n", unitHandle,
                                        bombHandle, entry.assigned);
                        }
                    }
                    else if (!u.hasWeapon || u.isCargo)
                        ++c.unarmed;
                    else if (!Policy::IsInterruptible(u) || Policy::TargetsBomb(u, bombHandle))
                        ++c.busy;
                    else
                        ++c.capped;
                }
                // Change-only summary per registry slot: shows why a scan
                // that sees units orders none.
                const uint32_t summary = (c.inRadius & 0xF) | ((c.detected & 0xF) << 4) | ((c.ordered & 0xF) << 8) |
                                         ((c.busy & 0xF) << 12) | ((c.unarmed & 0xF) << 16) |
                                         ((c.capped & 0xF) << 20) | 0x80000000u;
                if (slot < Policy::kRegistryCapacity && g_LastScanSummary[slot] != summary)
                {
                    g_LastScanSummary[slot] = summary;
                    LogBudgeted(L"[DWDEF] scan bomb=0x%08X inRadius=%u detected=%u ordered=%u busy=%u unarmed=%u "
                                L"capOrCooldown=%u\n",
                                bombHandle, c.inRadius, c.detected, c.ordered, c.busy, c.unarmed, c.capped);
                }
            }

            size_t SlotOf(const Policy::BombEntry* e)
            {
                for (size_t i = 0; i < g_Registry.Capacity(); ++i)
                    if (&g_Registry.At(i) == e)
                        return i;
                return Policy::kRegistryCapacity;
            }

            // Runs before the stock Simulate: only reads, plus the scan's
            // SetCommand on other units. A grounded Daywrecker detonates in
            // this tick, so it leaves the registry here.
            void OnBombTick(void* self)
            {
                const uint32_t handle = HandleOf(self);
                if (handle == 0)
                    return;
                if (BombKindOf(self) == BombKind::None)
                {
                    if (g_Registry.Remove(handle))
                        LogBudgeted(L"[DWDEF] bomb=0x%08X left (landed or dead)\n", handle);
                    return;
                }
                const float now = NowSeconds();
                const size_t before = g_Registry.Count();
                g_Registry.Prune(now);
                Policy::BombEntry* entry = g_Registry.Refresh(handle, now);
                if (!entry)
                    return;
                if (g_Registry.Count() > before)
                {
                    g_LastScanSummary[SlotOf(entry) % Policy::kRegistryCapacity] = 0;
                    LogBudgeted(L"[DWDEF] bomb=0x%08X tracked\n", handle);
                }
                if (!entry->scanned || Policy::ScanDue(now, entry->lastScan, Policy::kScanInterval))
                {
                    entry->scanned = true;
                    entry->lastScan = now;
                    Scan(self, handle, *entry, SlotOf(entry));
                }
            }

            // Vtable slot 15 (thiscall this, float dt; RET 4).
            void __fastcall DwSimulateHook(void* self, void* /*edx*/, float dt)
            {
                if (g_Active)
                    OnBombTick(self);
                reinterpret_cast<FnSimulate>(g_DwSimulateNext)(self, dt);
            }

            void __fastcall TorpedoSimulateHook(void* self, void* /*edx*/, float dt)
            {
                if (g_Active)
                    OnBombTick(self);
                reinterpret_cast<FnSimulate>(g_TorpedoSimulateNext)(self, dt);
            }

            // ---- 3. Evasion ---------------------------------------------

            void AddBombForces(float* ret, void* unit, bool stockThreat)
            {
                if (!ret || !unit)
                    return;
                if (unit == TryGetHeadlightPlayerObject())
                    return;
                void* const obj76 = Obj76Of(unit);
                Policy::Vec3 pos;
                Policy::Vec3 vel;
                Policy::Frame frame;
                if (!obj76 || !PositionOf(unit, pos) || !ReadVec(unit, kGameObjectVelocityOffset, vel) ||
                    !FrameOf(obj76, frame))
                    return;
                const float radius = RadiusOf(unit);
                const bool sp = SinglePlayerNow();
                Policy::UnitView u;
                ReadOrders(unit, u);
                const float now = NowSeconds();
                Policy::Vec3 sum;
                bool anyThreat = false;
                uint32_t firstBomb = 0;
                for (size_t i = 0; i < g_Registry.Capacity(); ++i)
                {
                    Policy::BombEntry& e = g_Registry.At(i);
                    if (e.handle == 0)
                        continue;
                    if (Policy::IsStale(now, e.lastSeen))
                    {
                        e = Policy::BombEntry{};
                        continue;
                    }
                    void* const bomb = SafeGetObj(e.handle);
                    if (!bomb || BombKindOf(bomb) == BombKind::None)
                    {
                        e = Policy::BombEntry{};
                        continue;
                    }
                    Policy::Vec3 bombPos;
                    Policy::Vec3 bombVel;
                    if (!PositionOf(bomb, bombPos) || !ReadVec(bomb, kGameObjectVelocityOffset, bombVel))
                        continue;
                    const bool detected = Policy::Detects(pos, frame.front, bombPos);
                    if (!Policy::ShouldEvade(true, SafeEnemyP(unit, bomb), false, Policy::TargetsBomb(u, e.handle),
                                             detected, g_Enabled, sp))
                        continue;
                    const Policy::EvadeResult r = Policy::EvadeForce(pos, vel, frame, radius, bombPos, bombVel,
                                                                     RadiusOf(bomb), Policy::kBombWeight);
                    if (!r.threat)
                        continue;
                    sum = Policy::Add(sum, r.force);
                    anyThreat = true;
                    if (!firstBomb)
                        firstBomb = e.handle;
                }
                const uint32_t unitHandle = HandleOf(unit);
                // Keyed on the bomb, not the unit: several units dodging the
                // same bomb would otherwise alternate every tick and use up
                // the shared log budget.
                const bool changed = anyThreat ? (!g_LastEvadeOn || g_LastEvadeBomb != firstBomb)
                                               : (g_LastEvadeOn && g_LastEvadeUnit == unitHandle);
                if (changed)
                {
                    g_LastEvadeOn = anyThreat;
                    g_LastEvadeUnit = unitHandle;
                    g_LastEvadeBomb = firstBomb;
                    LogBudgeted(L"[DWDEF] evade %ls unit=0x%08X bomb=0x%08X force=(%.1f,%.1f,%.1f)\n",
                                anyThreat ? L"on" : L"off", unitHandle, firstBomb, static_cast<double>(sum.x),
                                static_cast<double>(sum.y), static_cast<double>(sum.z));
                }
                if (!anyThreat)
                    return;
                Policy::Vec3 stock;
                if (!ReadVec(ret, 0, stock))
                    return;
                const Policy::Vec3 f = Policy::Combine(stock, stockThreat, sum, anyThreat);
                __try
                {
                    ret[0] = f.x;
                    ret[1] = f.y;
                    ret[2] = f.z;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
            }

            float* __cdecl EvadeHook(float* ret, void* unit, void* threat, void** outThreat)
            {
                // The stock out-threat is how we learn whether stock recorded
                // a threat; a caller passing null gets a local in its place.
                void* localThreat = nullptr;
                void** out = outThreat ? outThreat : &localThreat;
                float* const result = reinterpret_cast<FnEvade>(g_EvadeTrampoline)(ret, unit, threat, out);
                if (g_Active && g_Registry.Count() != 0)
                {
                    void* recorded = nullptr;
                    __try
                    {
                        recorded = *out;
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                        recorded = nullptr;
                    }
                    AddBombForces(ret, unit, recorded != nullptr);
                }
                return result;
            }

            // ---- install --------------------------------------------------

            bool InThisModule(const void* address)
            {
                HMODULE owner = nullptr;
                HMODULE self = nullptr;
                const DWORD flags =
                    GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT;
                if (!address || !GetModuleHandleExW(flags, static_cast<LPCWSTR>(address), &owner) ||
                    !GetModuleHandleExW(flags, reinterpret_cast<LPCWSTR>(&InThisModule), &self))
                    return false;
                return owner == self;
            }

            void* SlotValue(uint32_t vtable, size_t slot)
            {
                return ReadPtr(reinterpret_cast<void*>(static_cast<uintptr_t>(vtable)), slot * sizeof(void*));
            }

            struct CraftSlot
            {
                const char* row;
                const char* rtti;
                uint32_t vtable;
            };

            // Every vtable whose slot 13 holds Craft::GetCommand 0x004AE110
            // (scripts/audit_vtable_hooks.py, CRAFT_GETCOMMAND).
            CraftSlot g_CraftSlots[] = {
                { "CraftVtable", ".?AVCraft@@", 0 },
                { "HoverCraftVtable", ".?AVHoverCraft@@", 0 },
                { "MinelayerVtable", ".?AVMinelayer@@", 0 },
                { "PersonVtable", ".?AVPerson@@", 0 },
                { "SAVVtable", ".?AVSAV@@", 0 },
                { "WalkerVtable", ".?AVWalker@@", 0 },
                { "WingmanVtable", ".?AVWingman@@", 0 },
            };

            void InstallGetCommand()
            {
                uint32_t turretVtable = 0;
                const HookEngine::EngineRow rows[] = {
                    { "CraftGetCommand", &g_CraftGetCommandAddr },
                    { "TurretTankGetCommand", &g_TurretTankGetCommandAddr },
                    { "TurretTankVtable", &turretVtable },
                    { g_CraftSlots[0].row, &g_CraftSlots[0].vtable },
                    { g_CraftSlots[1].row, &g_CraftSlots[1].vtable },
                    { g_CraftSlots[2].row, &g_CraftSlots[2].vtable },
                    { g_CraftSlots[3].row, &g_CraftSlots[3].vtable },
                    { g_CraftSlots[4].row, &g_CraftSlots[4].vtable },
                    { g_CraftSlots[5].row, &g_CraftSlots[5].vtable },
                    { g_CraftSlots[6].row, &g_CraftSlots[6].vtable },
                };
                static_assert(sizeof(g_CraftSlots) / sizeof(g_CraftSlots[0]) == 7, "rows above list every slot");
                if (!HookEngine::BindEngineRows("Daywrecker defence GetCommand", rows))
                    return;
                void* const craftHook = reinterpret_cast<void*>(&CraftGetCommandHook);
                void* const turretHook = reinterpret_cast<void*>(&TurretGetCommandHook);
                // All or nothing: check every slot first.
                for (const CraftSlot& s : g_CraftSlots)
                {
                    void* const current = SlotValue(s.vtable, kGetCommandSlot);
                    if (!VtableTypeNameMatches(s.vtable, s.rtti) ||
                        (current != reinterpret_cast<void*>(static_cast<uintptr_t>(g_CraftGetCommandAddr)) &&
                         current != craftHook))
                    {
                        Log(L"[DWDEF] %hs slot 13 holds 0x%08X, not Craft::GetCommand 0x%08X; GetCommand not "
                            L"installed\n",
                            s.row, static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)), g_CraftGetCommandAddr);
                        return;
                    }
                }
                void* const turretCurrent = SlotValue(turretVtable, kGetCommandSlot);
                if (!VtableTypeNameMatches(turretVtable, ".?AVTurretTank@@") ||
                    (turretCurrent != reinterpret_cast<void*>(static_cast<uintptr_t>(g_TurretTankGetCommandAddr)) &&
                     !InThisModule(turretCurrent)))
                {
                    Log(L"[DWDEF] TurretTank slot 13 holds 0x%08X, neither stock nor an OpenShim wrapper; GetCommand "
                        L"not installed\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(turretCurrent)));
                    return;
                }
                g_StockCraftGetCommand = reinterpret_cast<FnGetCommand>(static_cast<uintptr_t>(g_CraftGetCommandAddr));
                if (turretCurrent != turretHook)
                    g_TurretGetCommandNext = turretCurrent;
                bool all = true;
                for (const CraftSlot& s : g_CraftSlots)
                {
                    const uintptr_t slot = s.vtable + kGetCommandSlot * sizeof(void*);
                    if (SlotValue(s.vtable, kGetCommandSlot) != craftHook && !WritePointerValue(slot, craftHook))
                        all = false;
                }
                const uintptr_t turretSlot = turretVtable + kGetCommandSlot * sizeof(void*);
                if (g_TurretGetCommandNext && turretCurrent != turretHook && !WritePointerValue(turretSlot, turretHook))
                    all = false;
                g_GetCommandInstalled = all;
                Log(L"[DWDEF] GetCommand %ls (7 Craft::GetCommand slots + TurretTank, chained on 0x%08X)\n",
                    all ? L"installed" : L"partially installed (check above)",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_TurretGetCommandNext)));
            }

            bool PatchSimulate(uint32_t& vtable, const char* rtti, uint32_t stockAddr, void* hook, void*& next,
                               const wchar_t* label)
            {
                if (!VtableTypeNameMatches(vtable, rtti))
                {
                    Log(L"[DWDEF] %ls vtable 0x%08X RTTI mismatch; not installed\n", label, vtable);
                    return false;
                }
                void* const current = SlotValue(vtable, kSimulateSlot);
                if (current != reinterpret_cast<void*>(static_cast<uintptr_t>(stockAddr)) && !InThisModule(current))
                {
                    Log(L"[DWDEF] %ls Simulate slot holds 0x%08X, neither 0x%08X nor an OpenShim wrapper; not "
                        L"installed\n",
                        label, static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)), stockAddr);
                    return false;
                }
                void* holder = &vtable;
                const ComVtablePatch::Result patched =
                    ComVtablePatch::PatchEntry(holder, kSimulateSlot, hook, next, ComVtablePatch::OnForeignWrapper::Refuse);
                if (!ComVtablePatch::Succeeded(patched) || !next)
                {
                    Log(L"[DWDEF] %ls Simulate slot not patched (%d)\n", label, static_cast<int>(patched));
                    return false;
                }
                Log(L"[DWDEF] %ls Simulate wrapper installed (was 0x%08X)\n", label,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(next)));
                return true;
            }

            void InstallRegistryAndEvade()
            {
                const HookEngine::EngineRow rows[] = {
                    { "DayWreckerVtable", &g_DayWreckerVtable },
                    { "DayWreckerSimulate", &g_DayWreckerSimulateAddr },
                    { "GameObjectEnemyP", &g_EnemyPAddr },
                    { "GameObjectSetCommandObj", &g_SetCommandObjAddr },
                    { "GameObjectHandleGetObj", &g_GetObjAddr },
                    { "GetGameTime", &g_GetTimeAddr },
                };
                if (!HookEngine::BindEngineRows("Daywrecker defence", rows))
                    return;
                g_ObjectListGlobal = HookEngine::ResolveNamedAddress("GameObject::objectList");
                if (!g_ObjectListGlobal)
                {
                    Log(L"[DWDEF] GameObject::objectList did not resolve; scan and evade not installed\n");
                    return;
                }
                g_DwSimulateInstalled = PatchSimulate(g_DayWreckerVtable, ".?AVDayWrecker@@", g_DayWreckerSimulateAddr,
                                                      reinterpret_cast<void*>(&DwSimulateHook), g_DwSimulateNext,
                                                      L"DayWrecker");
                const HookEngine::EngineRow torpedoRows[] = {
                    { "TorpedoVtable", &g_TorpedoVtable },
                    { "TorpedoSimulate", &g_TorpedoSimulateAddr },
                };
                if (HookEngine::BindEngineRows("Daywrecker defence (Comet)", torpedoRows))
                    g_TorpedoSimulateInstalled =
                        PatchSimulate(g_TorpedoVtable, ".?AVTorpedo@@", g_TorpedoSimulateAddr,
                                      reinterpret_cast<void*>(&TorpedoSimulateHook), g_TorpedoSimulateNext, L"Torpedo");
                if (!g_TorpedoSimulateInstalled)
                    g_TorpedoVtable = 0; // a Comet is then never a bomb anywhere
                if (!g_DwSimulateInstalled && !g_TorpedoSimulateInstalled)
                    return;

                const HookEngine::EngineRow evadeRows[] = {
                    { "EvadeOrdnanceForce", &g_EvadeAddr },
                };
                if (!HookEngine::BindEngineRows("Daywrecker defence evade", evadeRows))
                    return;
                // push ebp; mov ebp,esp; sub esp,0x198 (bytes read from the
                // shipped image; no branch lands inside them: the function
                // has six E8 callers and the body loops back to 0x005FD6xx).
                static const uint8_t kEvadeStolen[] = { 0x55, 0x8B, 0xEC, 0x81, 0xEC, 0x98, 0x01, 0x00, 0x00 };
                if (!InstallInlineDetour32(g_EvadeDetour, g_EvadeAddr, reinterpret_cast<void*>(&EvadeHook),
                                           sizeof(kEvadeStolen), kEvadeStolen, sizeof(kEvadeStolen),
                                           &g_EvadeTrampoline))
                {
                    Log(L"[DWDEF] EvadeOrdnanceForce 0x%08X failed its byte guard; evade not installed\n", g_EvadeAddr);
                    return;
                }
                g_EvadeInstalled = true;
                Log(L"[DWDEF] EvadeOrdnanceForce detour installed at 0x%08X\n", g_EvadeAddr);
            }

            void InitializeConfig()
            {
                if (g_ConfigInitialized)
                    return;
                g_ConfigInitialized = true;
                bool value = false;
                g_Enabled = TryGetUserConfigBool(kUserConfigSinglePlayerSection, "DaywreckerDefence", value) && value;
                Log(L"[DWDEF] Baseline enabled=%hs (SP-only)\n", g_Enabled ? "yes" : "no");
            }

            void ClearState()
            {
                g_Registry.Clear();
                g_Cooldowns.Clear();
                g_LastOffer = -1;
                g_LastEvadeOn = false;
                g_LastEvadeUnit = 0;
                g_LastEvadeBomb = 0;
                for (uint32_t& s : g_LastScanSummary)
                    s = 0;
            }
        }

        void InstallDaywreckerDefenceIfPossible()
        {
            static bool s_tried = false;
            if (s_tried)
                return;
            s_tried = true;
            InitializeConfig();
            if (!g_Enabled)
            {
                Log(L"[DWDEF] Disabled in openshim.ini; hooks not installed\n");
                return;
            }
            if (EnvFlagEnabled("OPENSHIM_DISABLE_DAYWRECKER_DEFENCE"))
            {
                Log(L"[DWDEF] Disabled by OPENSHIM_DISABLE_DAYWRECKER_DEFENCE; hooks not installed\n");
                return;
            }
            // GetCommand only needs its own rows and the identification rows.
            InstallRegistryAndEvade();
            if (g_DayWreckerVtable)
                InstallGetCommand();
            else
                Log(L"[DWDEF] DayWreckerVtable not bound; Attack-order hook not installed\n");
            RefreshDaywreckerDefenceState();
        }

        void RefreshDaywreckerDefenceState()
        {
            InitializeConfig();
            const bool installed = g_GetCommandInstalled || g_DwSimulateInstalled || g_TorpedoSimulateInstalled;
            const bool want = g_Enabled && installed && IsSinglePlayerSession();
            if (want != g_Active)
            {
                g_Active = want;
                Log(L"[DWDEF] %hs (getCommand=%d dwSimulate=%d torpedoSimulate=%d evade=%d)\n",
                    want ? "Active (SP-only)" : "Stood down", g_GetCommandInstalled ? 1 : 0,
                    g_DwSimulateInstalled ? 1 : 0, g_TorpedoSimulateInstalled ? 1 : 0, g_EvadeInstalled ? 1 : 0);
            }
            if (!g_Active)
                ClearState();
        }

        void ResetDaywreckerDefence()
        {
            ClearState();
            g_LogBudget = 400;
            RefreshDaywreckerDefenceState();
        }
    }
}
