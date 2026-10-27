// mp_splinter_sync.cpp -- keep the deployed Splinter (SprayBuilding) the same
// object on every peer of a multiplayer session.
//
// ============================================================================
// THE DEFECT (Redux 2.2.301, exact GOG image; Docs/MP_SPLINTER_RUNS_20261027.md)
// ============================================================================
//
// A thrown SprayBomb is replicated as ordnance (the launcher's bounces already
// resync it), but the SprayBuilding it turns into is not: every peer's own
// SprayBomb::Hit (0x005DB080) settles the bomb, builds a SprayBuilding with
// GameObjectClass::Build (call at 0x005DB37F) and gives it no network
// identity. A peer that lags deploys it somewhere else (87 m was seen), and
// killing it on one peer leaves it alive and firing on all the others.
//
// ============================================================================
// THE FIX
// ============================================================================
//
// The bomb itself is the only shared key: (source u16 at SprayBomb+0x7C,
// ordid u16 at SprayBomb+0x7E), the same pair Ordnance_Receive matches on. The
// SprayBomb::Hit's EBP - 0x1B0 holds the SprayBomb pointer. The Build call site is already
// wrapped by the Splinter Emitter Owner Propagation hook (perceived_team_reveal
// .cpp), which calls BeforeDeployBuild / AfterDeployBuild around the original.
//
//   'S','D' deploy v1 (32 bytes): tag2 ver1 pad1 u16 source u16 ordid
//           double x, y, z. Sent by the launcher (source == my id) once the
//           building exists. A receiver whose own building is registered
//           moves it (obj76 posit doubles + GameObject::UpdatePosition
//           0x004DB100); otherwise the position is held and BeforeDeployBuild
//           rewrites the build matrix posit when the receiver's own Hit gets
//           there.
//   'S','K' kill v1 (8 bytes): tag2 ver1 pad1 u16 source u16 ordid. Any peer
//           whose building dies of damage (flags & 0x01000000, set only by
//           Building::DamageAlloc; ammo exhaustion sets 0x200 alone) sends it
//           once. A receiver ORs 0x01000200 into the building's flags and does
//           not echo. With [Fixes] SplinterUndead on, the dead-gate in
//           SprayBuilding::Simulate then stops the payload fire loop; the
//           SplinterUndead gate runs in a network game while this is active.
//
// Both go out through Net::BroadcastSend 0x00575890(buf, len, 1, 1) and are
// received through the shared Net::Receive dispatcher (net_tag_dispatch.cpp).
// A peer without the fix ignores an unknown tag. Messages are accepted from
// any sender except this machine's own player id.
//
// The building<->key map is dropped in the SprayBuilding scalar deleting
// destructor (vtable slot 0, 0x005DA680). Early messages wait in a small
// pending table and expire after 60 s.
//
// Every engine address is a named row in scripts/patches.json.

#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "mp_splinter_sync_install.h"

#include "bzr_options_ui.h"
#include "com_vtable_patch.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "net_tag_dispatch.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <unordered_map>

namespace BZROpenShim
{
    namespace SplinterSync
    {
        namespace
        {
            constexpr const char* kComponent = "SPLINTERSYNC";

            constexpr uint16_t kTagDeploy = 0x4453; // 'S','D' read little-endian
            constexpr uint16_t kTagKill = 0x4B53;   // 'S','K'
            constexpr uint8_t kVersion = 1;
            constexpr unsigned kDeployLen = 32;
            constexpr unsigned kKillLen = 8;

            constexpr int kSessionInGame = 4;
            constexpr uintptr_t kSessionStateOffset = 8;

            // SprayBomb (Ordnance) fields; Hit's EBP - 0x1B0 holds the bomb pointer.
            constexpr intptr_t kSprayBombFrameOffset = -0x1B0;
            constexpr uintptr_t kOrdnanceSourceOffset = 0x7C;
            constexpr uintptr_t kOrdnanceOrdIdOffset = 0x7E;
            // SprayBuilding (complete object): obj76 pointer, then obj76 fields.
            constexpr uintptr_t kBuildingObj76Offset = 0xF4;
            constexpr uintptr_t kObj76FlagsOffset = 0x14;
            constexpr uintptr_t kObj76PositOffset = 0x48; // doubles x, y, z at +0x48/+0x50/+0x58
            // MAT_3D posit doubles.
            constexpr uintptr_t kMatrixPositOffset = 0x28; // +0x28/+0x30/+0x38
            constexpr uint32_t kDeadMask = 0x01000200u;
            constexpr uint32_t kDamageDeathFlag = 0x01000000u;

            constexpr size_t kDtorSlot = 0;
            constexpr ULONGLONG kPendingLifeMs = 60000;
            constexpr size_t kPendingCap = 64;
            constexpr double kMaxCoord = 1.0e7;

            using FnBroadcastSend = char(__cdecl*)(const void* buf, unsigned len, int p3, char p4);
            using FnLocalPlayerId = uint16_t(__cdecl*)();
            using FnUpdatePosition = void(__thiscall*)(void* gameObject);
            using FnDtor = void*(__thiscall*)(void* self, int flags);

            std::atomic<bool> g_Done{ false };
            std::atomic<bool> g_Active{ false };

            FnBroadcastSend g_Send = nullptr;
            FnLocalPlayerId g_LocalPlayerId = nullptr;
            FnUpdatePosition g_UpdatePosition = nullptr;
            FnDtor g_DtorOriginal = nullptr;
            uintptr_t g_SessionPtrAddr = 0;
            uintptr_t g_NetFlagAddr = 0;
            uint32_t g_SprayVtable = 0;

            struct Entry
            {
                uintptr_t building;
                bool killSent;
                bool remoteKilled;
            };
            struct PendingDeploy
            {
                double x, y, z;
                ULONGLONG tick;
            };

            SRWLOCK g_Lock = SRWLOCK_INIT;
            std::unordered_map<uint32_t, Entry> g_ByKey;
            std::unordered_map<uintptr_t, uint32_t> g_ByPtr;
            std::unordered_map<uint32_t, PendingDeploy> g_PendingDeploy;
            std::unordered_map<uint32_t, ULONGLONG> g_PendingKill;

            struct ScopedLock
            {
                ScopedLock() { AcquireSRWLockExclusive(&g_Lock); }
                ~ScopedLock() { ReleaseSRWLockExclusive(&g_Lock); }
                ScopedLock(const ScopedLock&) = delete;
                ScopedLock& operator=(const ScopedLock&) = delete;
            };

            bool IsEnabled()
            {
                bool enabled = true;
                static const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_MP_SPLINTER_SYNC", "BZR_DISABLE_MP_SPLINTER_SYNC" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            uint32_t MakeKey(uint16_t source, uint16_t ordId)
            {
                return (static_cast<uint32_t>(source) << 16) | ordId;
            }

            // --- SEH leaves (no C++ objects with destructors in these) --------

            bool SafeReadU32(uintptr_t address, uint32_t& out)
            {
                __try
                {
                    out = *reinterpret_cast<const uint32_t*>(address);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool SafeReadU8(uintptr_t address, uint8_t& out)
            {
                __try
                {
                    out = *reinterpret_cast<const uint8_t*>(address);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool IsNetGame()
            {
                uint8_t flag = 0;
                return g_NetFlagAddr && SafeReadU8(g_NetFlagAddr, flag) && flag != 0;
            }

            bool SessionInGame()
            {
                uint32_t session = 0;
                uint32_t state = 0;
                return SafeReadU32(g_SessionPtrAddr, session) && session != 0 &&
                       SafeReadU32(session + kSessionStateOffset, state) &&
                       static_cast<int>(state) == kSessionInGame;
            }

            uint16_t LocalId()
            {
                __try
                {
                    return g_LocalPlayerId ? g_LocalPlayerId() : 0;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return 0;
                }
            }

            bool SafeBroadcast(const uint8_t* packet, unsigned len)
            {
                __try
                {
                    g_Send(packet, len, 1, 1);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            // The SprayBomb's key from SprayBomb::Hit's frame.
            bool ReadBombKey(void* callerFrame, uint16_t& source, uint16_t& ordId)
            {
                __try
                {
                    if (!callerFrame)
                        return false;
                    const uint8_t* bomb = *reinterpret_cast<const uint8_t* const*>(
                        reinterpret_cast<const uint8_t*>(callerFrame) + kSprayBombFrameOffset);
                    if (!bomb)
                        return false;
                    source = *reinterpret_cast<const uint16_t*>(bomb + kOrdnanceSourceOffset);
                    ordId = *reinterpret_cast<const uint16_t*>(bomb + kOrdnanceOrdIdOffset);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool BuildingVtableMatches(uintptr_t building)
            {
                uint32_t vtable = 0;
                return building && SafeReadU32(building, vtable) && vtable == g_SprayVtable;
            }

            bool ReadObj76(uintptr_t building, uintptr_t& obj76)
            {
                uint32_t value = 0;
                if (!SafeReadU32(building + kBuildingObj76Offset, value) || value == 0)
                    return false;
                obj76 = value;
                return true;
            }

            bool ReadFlags(uintptr_t obj76, uint32_t& flags)
            {
                return SafeReadU32(obj76 + kObj76FlagsOffset, flags);
            }

            bool OrFlags(uintptr_t obj76, uint32_t mask)
            {
                __try
                {
                    *reinterpret_cast<uint32_t*>(obj76 + kObj76FlagsOffset) |= mask;
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool ReadDoubles(uintptr_t base, double (&out)[3])
            {
                __try
                {
                    const double* p = reinterpret_cast<const double*>(base);
                    out[0] = p[0];
                    out[1] = p[1];
                    out[2] = p[2];
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool WriteDoubles(uintptr_t base, double x, double y, double z)
            {
                __try
                {
                    double* p = reinterpret_cast<double*>(base);
                    p[0] = x;
                    p[1] = y;
                    p[2] = z;
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool CallUpdatePosition(void* building)
            {
                __try
                {
                    g_UpdatePosition(building);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            // --- shared helpers ----------------------------------------------

            bool Plausible(double v)
            {
                return std::isfinite(v) && std::fabs(v) < kMaxCoord;
            }

            // Caller holds g_Lock. Drops expired entries, then makes room.
            template <class Map, class TickOf>
            void TrimPending(Map& map, ULONGLONG now, TickOf tickOf)
            {
                for (auto it = map.begin(); it != map.end();)
                {
                    if (now - tickOf(it->second) > kPendingLifeMs)
                        it = map.erase(it);
                    else
                        ++it;
                }
                while (map.size() >= kPendingCap)
                    map.erase(map.begin());
            }

            void BroadcastDeploy(uint16_t source, uint16_t ordId, const double (&pos)[3])
            {
                uint8_t packet[kDeployLen] = {};
                packet[0] = 'S';
                packet[1] = 'D';
                packet[2] = kVersion;
                std::memcpy(packet + 4, &source, 2);
                std::memcpy(packet + 6, &ordId, 2);
                std::memcpy(packet + 8, pos, sizeof(pos));
                const bool ok = SafeBroadcast(packet, kDeployLen);
                LogShimA(LogLevel::Info, kComponent,
                         "sent deploy: key %u/%u pos (%.1f, %.1f, %.1f)%s", source, ordId,
                         pos[0], pos[1], pos[2], ok ? "" : " [send faulted]");
            }

            void BroadcastKill(uint16_t source, uint16_t ordId)
            {
                uint8_t packet[kKillLen] = {};
                packet[0] = 'S';
                packet[1] = 'K';
                packet[2] = kVersion;
                std::memcpy(packet + 4, &source, 2);
                std::memcpy(packet + 6, &ordId, 2);
                const bool ok = SafeBroadcast(packet, kKillLen);
                LogShimA(LogLevel::Info, kComponent, "sent kill: key %u/%u%s", source, ordId,
                         ok ? "" : " [send faulted]");
            }

            // --- receive ------------------------------------------------------

            bool OnDeployMessage(unsigned senderId, const unsigned char* buf, unsigned len)
            {
                if (len < kDeployLen || buf[2] != kVersion)
                    return false;
                if (!g_Active.load(std::memory_order_acquire))
                    return true;
                uint16_t source = 0, ordId = 0;
                double pos[3] = {};
                std::memcpy(&source, buf + 4, 2);
                std::memcpy(&ordId, buf + 6, 2);
                std::memcpy(pos, buf + 8, sizeof(pos));
                const uint16_t me = LocalId();
                if ((senderId & 0xFFFF) == me || source == me)
                    return true;
                if (!Plausible(pos[0]) || !Plausible(pos[1]) || !Plausible(pos[2]))
                    return true;

                const uint32_t key = MakeKey(source, ordId);
                uintptr_t building = 0;
                {
                    ScopedLock lock;
                    const auto it = g_ByKey.find(key);
                    if (it != g_ByKey.end())
                        building = it->second.building;
                    else
                    {
                        TrimPending(g_PendingDeploy, GetTickCount64(),
                                    [](const PendingDeploy& p) { return p.tick; });
                        g_PendingDeploy[key] = PendingDeploy{ pos[0], pos[1], pos[2], GetTickCount64() };
                    }
                }
                if (!building)
                {
                    LogShimA(LogLevel::Info, kComponent,
                             "deploy %u/%u from player %u held for our own Hit", source, ordId, senderId & 0xFFFF);
                    return true;
                }

                uintptr_t obj76 = 0;
                uint32_t flags = 0;
                if (!BuildingVtableMatches(building) || !ReadObj76(building, obj76) || !ReadFlags(obj76, flags) || (flags & kDeadMask))
                    return true;
                double before[3] = {};
                ReadDoubles(obj76 + kObj76PositOffset, before);
                if (WriteDoubles(obj76 + kObj76PositOffset, pos[0], pos[1], pos[2]))
                    CallUpdatePosition(reinterpret_cast<void*>(building));
                LogShimA(LogLevel::Info, kComponent,
                         "deploy %u/%u from player %u moved building 0x%08X (%.1f, %.1f, %.1f) -> (%.1f, %.1f, %.1f)",
                         source, ordId, senderId & 0xFFFF, static_cast<uint32_t>(building), before[0], before[1],
                         before[2], pos[0], pos[1], pos[2]);
                return true;
            }

            bool OnKillMessage(unsigned senderId, const unsigned char* buf, unsigned len)
            {
                if (len < kKillLen || buf[2] != kVersion)
                    return false;
                if (!g_Active.load(std::memory_order_acquire))
                    return true;
                uint16_t source = 0, ordId = 0;
                std::memcpy(&source, buf + 4, 2);
                std::memcpy(&ordId, buf + 6, 2);
                const uint16_t me = LocalId();
                if ((senderId & 0xFFFF) == me)
                    return true;

                const uint32_t key = MakeKey(source, ordId);
                uintptr_t building = 0;
                {
                    ScopedLock lock;
                    const auto it = g_ByKey.find(key);
                    if (it != g_ByKey.end())
                    {
                        building = it->second.building;
                        // Mark before the flags change so the dead-gate does not echo.
                        it->second.remoteKilled = true;
                    }
                    else
                    {
                        TrimPending(g_PendingKill, GetTickCount64(), [](ULONGLONG t) { return t; });
                        g_PendingKill[key] = GetTickCount64();
                    }
                }
                if (!building)
                {
                    LogShimA(LogLevel::Info, kComponent, "kill %u/%u from player %u held for our own Hit",
                             source, ordId, senderId & 0xFFFF);
                    return true;
                }
                uintptr_t obj76 = 0;
                uint32_t flags = 0;
                if (BuildingVtableMatches(building) && ReadObj76(building, obj76) && ReadFlags(obj76, flags) &&
                    !(flags & kDeadMask))
                {
                    OrFlags(obj76, kDeadMask);
                    LogShimA(LogLevel::Info, kComponent, "kill %u/%u from player %u applied to building 0x%08X",
                             source, ordId, senderId & 0xFFFF, static_cast<uint32_t>(building));
                }
                return true;
            }

            // --- destructor ---------------------------------------------------

            void* __fastcall DtorHook(void* self, void* /*edx*/, int flags)
            {
                {
                    ScopedLock lock;
                    const auto it = g_ByPtr.find(reinterpret_cast<uintptr_t>(self));
                    if (it != g_ByPtr.end())
                    {
                        const auto key = g_ByKey.find(it->second);
                        if (key != g_ByKey.end() && key->second.building == it->first)
                            g_ByKey.erase(key);
                        g_ByPtr.erase(it);
                    }
                }
                return g_DtorOriginal ? g_DtorOriginal(self, flags) : self;
            }

            bool DoInstall()
            {
                // Literal names so patch_registration_tests can check them
                // against scripts/patches.json.
                const uint32_t sendAddr = HookEngine::ResolveNamedAddress("Net::BroadcastSend");
                const uint32_t sessionAddr = HookEngine::ResolveNamedAddress("Net::Session");
                const uint32_t localIdAddr = HookEngine::ResolveNamedAddress("GetLocalPlayerNetId");
                uint32_t updatePosAddr = 0;
                uint32_t dtorAddr = 0;
                uint32_t netFlagAddr = 0;
                const HookEngine::EngineRow rows[] = {
                    { "SprayBuildingVtable", &g_SprayVtable },
                    { "SprayBuildingDtor", &dtorAddr },
                    { "GameObjectUpdatePosition", &updatePosAddr },
                    { "IsNetGameFlag", &netFlagAddr },
                };
                if (!sendAddr || !sessionAddr || !localIdAddr || !HookEngine::BindEngineRows("SplinterSync", rows))
                {
                    LogShimA(LogLevel::Warn, kComponent, "an address did not resolve; splinter sync not installed");
                    return false;
                }
                if (!Hooks::VtableTypeNameMatches(g_SprayVtable, ".?AVSprayBuilding@@"))
                {
                    LogShimA(LogLevel::Warn, kComponent,
                             "vtable 0x%08X is not a SprayBuilding; splinter sync not installed", g_SprayVtable);
                    return false;
                }
                uint32_t slot0 = 0;
                if (!SafeReadU32(g_SprayVtable + kDtorSlot * sizeof(void*), slot0) || slot0 != dtorAddr)
                {
                    LogShimA(LogLevel::Warn, kComponent,
                             "SprayBuilding vtable slot 0 is 0x%08X, expected 0x%08X; splinter sync not installed",
                             slot0, dtorAddr);
                    return false;
                }

                g_Send = reinterpret_cast<FnBroadcastSend>(sendAddr);
                g_LocalPlayerId = reinterpret_cast<FnLocalPlayerId>(localIdAddr);
                g_UpdatePosition = reinterpret_cast<FnUpdatePosition>(updatePosAddr);
                g_SessionPtrAddr = sessionAddr;
                g_NetFlagAddr = netFlagAddr;

                if (!NetTagDispatch::RegisterNetTagHandler(kTagDeploy, &OnDeployMessage) ||
                    !NetTagDispatch::RegisterNetTagHandler(kTagKill, &OnKillMessage))
                {
                    // A registered handler ignores its packets while inactive.
                    LogShimA(LogLevel::Warn, kComponent, "Net::Receive handlers not registered; splinter sync not installed");
                    return false;
                }

                void* vtableHolder = &g_SprayVtable;
                void* original = nullptr;
                const ComVtablePatch::Result patched = ComVtablePatch::PatchEntry(
                    vtableHolder, kDtorSlot, reinterpret_cast<void*>(&DtorHook), original,
                    ComVtablePatch::OnForeignWrapper::Refuse);
                if (!ComVtablePatch::Succeeded(patched) || !original)
                {
                    LogShimA(LogLevel::Warn, kComponent,
                             "SprayBuilding destructor slot not patched (%d); splinter sync not installed",
                             static_cast<int>(patched));
                    return false;
                }
                g_DtorOriginal = reinterpret_cast<FnDtor>(original);

                g_Active.store(true, std::memory_order_release);
                LogShimA(LogLevel::Info, kComponent,
                         "installed: send 0x%08X, session ptr 0x%08X, vtable 0x%08X, dtor 0x%08X, UpdatePosition 0x%08X",
                         sendAddr, sessionAddr, g_SprayVtable, dtorAddr, updatePosAddr);
                return true;
            }
        }

        void InstallSplinterSyncIfPossible()
        {
            if (g_Done.exchange(true))
                return;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] SplinterSync = 0)");
                return;
            }
            DoInstall();
        }

        bool IsActive()
        {
            return g_Active.load(std::memory_order_acquire);
        }

        void __cdecl BeforeDeployBuild(void* matrix, void* callerFrame)
        {
            if (!g_Active.load(std::memory_order_acquire) || !matrix || !IsNetGame())
                return;
            uint16_t source = 0, ordId = 0;
            if (!ReadBombKey(callerFrame, source, ordId))
                return;
            const uint32_t key = MakeKey(source, ordId);

            PendingDeploy pending = {};
            bool have = false;
            {
                ScopedLock lock;
                const auto it = g_PendingDeploy.find(key);
                if (it != g_PendingDeploy.end())
                {
                    pending = it->second;
                    have = GetTickCount64() - pending.tick <= kPendingLifeMs;
                    g_PendingDeploy.erase(it);
                }
            }
            if (!have)
                return;
            if (WriteDoubles(reinterpret_cast<uintptr_t>(matrix) + kMatrixPositOffset, pending.x, pending.y, pending.z))
                LogShimA(LogLevel::Info, kComponent, "deploy %u/%u built at the launcher's position (%.1f, %.1f, %.1f)",
                         source, ordId, pending.x, pending.y, pending.z);
        }

        void __cdecl AfterDeployBuild(void* building, void* callerFrame)
        {
            if (!g_Active.load(std::memory_order_acquire) || !building || !IsNetGame())
                return;
            const uintptr_t ptr = reinterpret_cast<uintptr_t>(building);
            uint16_t source = 0, ordId = 0;
            if (!ReadBombKey(callerFrame, source, ordId))
                return;
            if (!BuildingVtableMatches(ptr))
            {
                LogShimA(LogLevel::Warn, kComponent,
                         "deploy %u/%u: Build returned 0x%08X, not a SprayBuilding; not tracked", source, ordId,
                         static_cast<uint32_t>(ptr));
                return;
            }
            uintptr_t obj76 = 0;
            if (!ReadObj76(ptr, obj76))
                return;

            const uint32_t key = MakeKey(source, ordId);
            bool killNow = false;
            {
                ScopedLock lock;
                // A reused key or address leaves a stale mapping behind; drop it.
                const auto oldKey = g_ByKey.find(key);
                if (oldKey != g_ByKey.end())
                    g_ByPtr.erase(oldKey->second.building);
                const auto oldPtr = g_ByPtr.find(ptr);
                if (oldPtr != g_ByPtr.end() && oldPtr->second != key)
                    g_ByKey.erase(oldPtr->second);

                Entry entry = { ptr, false, false };
                const auto pendingKill = g_PendingKill.find(key);
                if (pendingKill != g_PendingKill.end())
                {
                    killNow = GetTickCount64() - pendingKill->second <= kPendingLifeMs;
                    g_PendingKill.erase(pendingKill);
                    entry.remoteKilled = killNow;
                }
                g_ByKey[key] = entry;
                g_ByPtr[ptr] = key;
            }
            if (killNow && OrFlags(obj76, kDeadMask))
                LogShimA(LogLevel::Info, kComponent, "deploy %u/%u built dead: a kill arrived first", source, ordId);

            if (source == LocalId() && SessionInGame())
            {
                double pos[3] = {};
                if (ReadDoubles(obj76 + kObj76PositOffset, pos))
                    BroadcastDeploy(source, ordId, pos);
            }
        }

        void __cdecl OnSplinterDead(void* sprayBuilding)
        {
            if (!g_Active.load(std::memory_order_acquire) || !sprayBuilding)
                return;
            uint32_t key = 0;
            bool send = false;
            {
                ScopedLock lock;
                const auto byPtr = g_ByPtr.find(reinterpret_cast<uintptr_t>(sprayBuilding));
                if (byPtr == g_ByPtr.end())
                    return;
                const auto entry = g_ByKey.find(byPtr->second);
                if (entry == g_ByKey.end())
                    return;
                if (!entry->second.killSent && !entry->second.remoteKilled)
                {
                    entry->second.killSent = true;
                    key = byPtr->second;
                    send = true;
                }
            }
            if (send && IsNetGame() && SessionInGame())
                BroadcastKill(static_cast<uint16_t>(key >> 16), static_cast<uint16_t>(key & 0xFFFF));
        }
    }
}
