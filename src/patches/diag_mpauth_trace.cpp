// diag_mpauth_trace.cpp
// BZR Open Shim - DIAGNOSTIC ONLY: MPAUTH receiver replay instrumentation
// (Daywrecker and Splinter authority tracing, opt-in via TraceMpauth /
// OPENSHIM_TRACE_MPAUTH), split out of bzr_hooks.cpp. No gameplay change.
#include "bzr_hooks.h"
#include "bzr_object_layout.h"
#include "bzr_hooks_internal.h"
#include "engine_globals.h"
#include "game_state.h"
#include "openshim_ini.h"
#include "openshim_preset_migration.h"
#include "openshim_assets.h"
#include "terrain_proxy.h"
#include "terrain_tile_blend.h"
#include "bzr_options_ui.h"
#include "remembered_mesh_bounds_table.h"
#include "patches.h"
#include "patcher.h"
#include "fog_wake_feature.h"
#include "mp_vehicle_preview_fix.h"
#include "shim_log.h"
#include "x86_length.h"
#include "ogre_shader_cache.h"
#include "ogre_enhanced_light_selection.h"
#include "render_effect_intent.h"
#include "render_profile_runtime.h"
#include "native_ui.h"
#include "../engine/native_ui_validation.h"
#include "ogre_animation_profiler.h"
#include "ogre_profiler_algorithms.h"
#include "weapon_convergence.h"
#include "headlight_falloff.h"
#include "shadow_far_distance.h"
#include "sun_flash.h"
#include "chunk_batch_invalidation.h"
#include "ai_range_policy.h"
#include "lcbench_safety_policy.h"
#include "hook_engine.h"
#include "ui_performance.h"
#include "openshim_events.h"
#include "player_kill_trace.h"
#include "net_optimizer.h"
#include "pond_class_label.h"
#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <array>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <intrin.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <exception>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <new>
#include <string>
#include <string_view>
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
    namespace Hooks
    {
        // MPAUTH diagnostic traces (Redux receiver replay). Opt-in, cheap, no gameplay change.
        bool g_MpauthEnabled = false;
        bool g_MpauthHooksInstalled = false;
        volatile long g_MpauthInstallRetryBudget = 8;
        thread_local bool g_MpauthInOrdnanceReceive = false;
        std::unordered_map<uint32_t, int> g_MpauthSplHitCounts = {};

        // MPAUTH instrumentation (Redux 2.2.301) — diagnostic only, no authority patch.
        // Daywrecker: shared consumed byte at +0x230 (complete) / +0x218 (adjusted).
        // Splinter: payload bSend at +0x80, source at +0x7C, ordid at +0x7E.
        // engine_addresses rows, bound together in MpauthAddressesBound().
        uint32_t g_DayWreckerSimulateAddr = 0;
        uint32_t g_DayWreckerExplodeAddr = 0;
        uint32_t g_DayWreckerVtableAddr = 0;
        uint32_t g_DayWreckerDistributedVtableAddr = 0;
        uint32_t g_GameObjectRemoveAddr = 0;
        uint32_t g_OrdinaryStateReaderAddr = 0;
        uint32_t g_PermanentStateReaderAddr = 0;
        uint32_t g_DayWreckerSetRemoteAddr = 0;
        uint32_t g_OrdnanceReceiverAddr = 0;
        uint32_t g_SprayBombHitAddr = 0;
        uint32_t g_SprayBombSimulateAddr = 0;

        bool MpauthAddressesBound()
        {
            static const bool bound = [] {
                const HookEngine::EngineRow rows[] = {
                    { "DayWreckerSimulate", &g_DayWreckerSimulateAddr },
                    { "DayWreckerExplode", &g_DayWreckerExplodeAddr },
                    { "DayWreckerVtable", &g_DayWreckerVtableAddr },
                    { "DayWreckerDistributedVtable", &g_DayWreckerDistributedVtableAddr },
                    { "GameObjectRemove", &g_GameObjectRemoveAddr },
                    { "DayWreckerOrdinaryStateReader", &g_OrdinaryStateReaderAddr },
                    { "DayWreckerPermanentStateReader", &g_PermanentStateReaderAddr },
                    { "DayWreckerSetRemote", &g_DayWreckerSetRemoteAddr },
                    { "OrdnanceReceive", &g_OrdnanceReceiverAddr },
                    { "SprayBombHit", &g_SprayBombHitAddr },
                    { "SprayBombSimulate", &g_SprayBombSimulateAddr },
                };
                if (!HookEngine::BindEngineRows("MP auth trace", rows))
                    return false;
                return VtableTypeNameMatches(g_DayWreckerVtableAddr, ".?AVDayWrecker@@") &&
                       VtableTypeNameMatches(g_DayWreckerDistributedVtableAddr, ".?AVDayWrecker@@");
            }();
            return bound;
        }

        constexpr size_t kDayWreckerConsumedByteOffset = 0x230;

        constexpr size_t kDayWreckerDistributedConsumedOffset = 0x218;

        constexpr size_t kDayWreckerDistributedOffset = 0x18;

        constexpr size_t kMpauthOrdnanceSourceOffset = 0x7C;

        constexpr size_t kMpauthOrdnanceOrdIdOffset = 0x7E;

        constexpr size_t kMpauthOrdnanceBSendOffset = 0x80;

        constexpr size_t kMpauthOrdnanceDtOffset = 0x10;

        constexpr long kMpauthTraceBudgetMax = 4096;

        static bool g_MpauthDwEnabled = false;

        static bool g_MpauthSplEnabled = false;

        static volatile long g_MpauthDwTraceBudget = kMpauthDwTraceBudgetDefault;

        static volatile long g_MpauthSplTraceBudget = kMpauthSplTraceBudgetDefault;

        static InlineDetour32 g_DayWreckerSimulateDetour = {};

        static InlineDetour32 g_DayWreckerExplodeDetour = {};

        static InlineDetour32 g_GameObjectRemoveDetour = {};

        static InlineDetour32 g_DistributedCreateDetour = {};

        static InlineDetour32 g_OrdnanceReceiverDetour = {};

        static InlineDetour32 g_SprayBombHitDetour = {};

        static InlineDetour32 g_SprayBombSimulateDetour = {};

        static InlineDetour32 g_OrdinaryStateReaderDetour = {};

        static InlineDetour32 g_PermanentStateReaderDetour = {};

        static volatile long g_MpauthSplHitMapLogBudget = 8;

        // =====================================================================
        // MPAUTH receiver replay instrumentation (Redux 2.2.301) — diagnostic only.
        // No gameplay/authority change. Opt-in via TraceMpauth / OPENSHIM_TRACE_MPAUTH.
        // Emits BZRHarness-friendly MPAUTH_* lines for Daywrecker and Splinter.
        // =====================================================================
        static bool ShouldTraceMpauthDw()
        {
            return g_MpauthDwEnabled && g_MpauthDwTraceBudget > 0;
        }
        static bool ShouldTraceMpauthSpl()
        {
            return g_MpauthSplEnabled && g_MpauthSplTraceBudget > 0;
        }

        static const char* MpauthPeerRole()
        {
            __try
            {
                if (g_BzrFn_IsHost && g_BzrFn_IsHost())
                    return "host";
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}
            return "client";
        }
        static uint16_t MpauthLocalNetId()
        {
            return ReadLocalPlayerNetIdValue();
        }
        // DW helpers
        static uint8_t MpauthReadDwConsumedComplete(void* completePtr)
        {
            __try { return *(uint8_t*)((uint8_t*)completePtr + kDayWreckerConsumedByteOffset); }
            __except (EXCEPTION_EXECUTE_HANDLER) { return 0xFF; }
        }
        static uint8_t MpauthReadDwConsumedDistributed(void* distPtr)
        {
            __try { return *(uint8_t*)((uint8_t*)distPtr + kDayWreckerDistributedConsumedOffset); }
            __except (EXCEPTION_EXECUTE_HANDLER) { return 0xFF; }
        }
        static bool MpauthIsDayWreckerObject(void* ptr)
        {
            __try
            {
                void* vt0 = *(void**)ptr;
                if (vt0 == reinterpret_cast<void*>(g_DayWreckerVtableAddr))
                    return true;
                void* vt1 = *(void**)((uint8_t*)ptr + kDayWreckerDistributedOffset);
                if (vt1 == reinterpret_cast<void*>(g_DayWreckerDistributedVtableAddr))
                    return true;
                if (vt0 == reinterpret_cast<void*>(g_DayWreckerDistributedVtableAddr))
                    return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}
            return false;
        }
        static bool MpauthReadDwIdentity(void* completeOrDist, uint32_t& outId, uint8_t& outType, uint16_t& outAct)
        {
            __try
            {
                uint8_t* dist = (uint8_t*)completeOrDist + kDayWreckerDistributedOffset;
                outId = *(uint32_t*)(dist + 0x64);
                outType = *(uint8_t*)(dist + 0x68);
                outAct = *(uint16_t*)(dist + 0x62);
                if (outType <= 2 || outId != 0)
                    return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}
            __try
            {
                uint8_t* dist = (uint8_t*)completeOrDist;
                outId = *(uint32_t*)(dist + 0x64);
                outType = *(uint8_t*)(dist + 0x68);
                outAct = *(uint16_t*)(dist + 0x62);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}
            return false;
        }
        std::unordered_set<uint32_t> g_MpauthRecentDwRemovedIds = {};
        std::unordered_map<uint32_t, uint64_t> g_MpauthDwRemoveTick = {};
        std::unordered_map<uint32_t, int> g_MpauthDwDeletedRecord = {};
        // Ordnance helpers
        static bool MpauthReadOrdnanceFields(void* ordPtr, uint16_t& outSrc, uint16_t& outOrdId, int32_t& outBSend, uint32_t& outFlags, float& outDt)
        {
            __try
            {
                uint8_t* p = (uint8_t*)ordPtr;
                outSrc = *(uint16_t*)(p + kMpauthOrdnanceSourceOffset);
                outOrdId = *(uint16_t*)(p + kMpauthOrdnanceOrdIdOffset);
                outBSend = *(int32_t*)(p + kMpauthOrdnanceBSendOffset);
                void* obj = *(void**)(p + kOrdnanceObjOffset);
                if (obj)
                    outFlags = *(uint32_t*)((uint8_t*)obj + kObjStateFlagsOffset);
                else
                    outFlags = 0;
                outDt = *(float*)(p + kMpauthOrdnanceDtOffset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        using FnMpauthDwSim = void(__thiscall*)(void* thisPtr, float dt);
        using FnMpauthDwExplode = void(__thiscall*)(void* thisPtr);
        using FnMpauthGoRemove = void(__thiscall*)(void* thisPtr);
        using FnMpauthSetRemote = void(__thiscall*)(void* thisPtr);
        using FnMpauthOrdnReceive = void(__cdecl*)(char* a, uint32_t b, uint16_t c);
        using FnMpauthSprayHit = void(__thiscall*)(void* thisPtr, void* a, void* b);
        using FnMpauthSpraySim = void(__thiscall*)(void* thisPtr, float dt);
        static FnMpauthDwSim g_MpauthDwSimOrig = nullptr;
        static FnMpauthDwExplode g_MpauthDwExplodeOrig = nullptr;
        static FnMpauthGoRemove g_MpauthGoRemoveOrig = nullptr;
        static FnMpauthSetRemote g_MpauthSetRemoteOrig = nullptr;
        static FnMpauthOrdnReceive g_MpauthOrdnReceiveOrig = nullptr;
        static FnMpauthSprayHit g_MpauthSprayHitOrig = nullptr;
        static FnMpauthSpraySim g_MpauthSpraySimOrig = nullptr;
        using FnMpauthOrdinaryReader = void(__cdecl*)(uint16_t, uint8_t*, uint32_t, float);
        using FnMpauthPermanentReader = void(__cdecl*)(int16_t, uint32_t, uint16_t, int32_t);
        static FnMpauthOrdinaryReader g_MpauthOrdinaryReaderOrig = nullptr;
        static FnMpauthPermanentReader g_MpauthPermanentReaderOrig = nullptr;

        void __fastcall MpauthDwSimulateHook(void* thisPtr, void* /*edx*/, float dt)
        {
            uint8_t consumedBefore = MpauthReadDwConsumedComplete(thisPtr);
            uint32_t dwId = 0; uint8_t objType = 0xFF; uint16_t act = 0xFFFF;
            MpauthReadDwIdentity(thisPtr, dwId, objType, act);
            if (ShouldTraceMpauthDw())
            {
                if (InterlockedDecrement(&g_MpauthDwTraceBudget) >= 0)
                {
                    uint16_t netId = MpauthLocalNetId();
                    const char* role = MpauthPeerRole();
                    Log(L"[MPAUTH_DW_DETONATE] sim peer=%hs netId=0x%04X id=0x%08X ptr=0x%08X consumed_before=%u type=%u act=0x%04X dt=%f\n",
                        role, netId, dwId, (uint32_t)(uintptr_t)thisPtr, (unsigned)consumedBefore, (unsigned)objType, (unsigned)act, dt);
                    Log(L"MPAUTH_DW_DETONATE peer=%hs id=0x%08X ptr=0x%08X consumed_before=%u\n",
                        role, dwId, (uint32_t)(uintptr_t)thisPtr, (unsigned)consumedBefore);
                }
                else
                {
                    InterlockedIncrement(&g_MpauthDwTraceBudget);
                }
            }
            if (g_MpauthDwSimOrig)
                g_MpauthDwSimOrig(thisPtr, dt);
            else if (g_DayWreckerSimulateDetour.trampoline)
                reinterpret_cast<FnMpauthDwSim>(g_DayWreckerSimulateDetour.trampoline)(thisPtr, dt);
        }
        void __fastcall MpauthDwExplodeHook(void* thisPtr, void* /*edx*/)
        {
            uint8_t consumedBefore = MpauthReadDwConsumedDistributed(thisPtr);
            void* complete = (uint8_t*)thisPtr - kDayWreckerDistributedOffset;
            uint32_t dwId = 0; uint8_t objType = 0xFF; uint16_t act = 0xFFFF;
            bool has = MpauthReadDwIdentity(complete, dwId, objType, act);
            if (!has) MpauthReadDwIdentity(thisPtr, dwId, objType, act);
            if (ShouldTraceMpauthDw())
            {
                if (InterlockedDecrement(&g_MpauthDwTraceBudget) >= 0)
                {
                    uint16_t netId = MpauthLocalNetId();
                    const char* role = MpauthPeerRole();
                    Log(L"[MPAUTH_DW_DETONATE] explode peer=%hs netId=0x%04X id=0x%08X ptr=0x%08X consumed_before=%u type=%u act=0x%04X\n",
                        role, netId, dwId, (uint32_t)(uintptr_t)complete, (unsigned)consumedBefore, (unsigned)objType, (unsigned)act);
                    Log(L"MPAUTH_DW_DETONATE peer=%hs id=0x%08X ptr=0x%08X consumed_before=%u\n",
                        role, dwId, (uint32_t)(uintptr_t)complete, (unsigned)consumedBefore);
                }
                else
                {
                    InterlockedIncrement(&g_MpauthDwTraceBudget);
                }
            }
            if (g_MpauthDwExplodeOrig)
                g_MpauthDwExplodeOrig(thisPtr);
            else if (g_DayWreckerExplodeDetour.trampoline)
                reinterpret_cast<FnMpauthDwExplode>(g_DayWreckerExplodeDetour.trampoline)(thisPtr);
        }
        void __fastcall MpauthGoRemoveHook(void* thisPtr, void* /*edx*/)
        {
            bool isDw = MpauthIsDayWreckerObject(thisPtr);
            uint32_t dwId = 0; uint8_t objType = 0xFF; uint16_t act = 0xFFFF;
            MpauthReadDwIdentity(thisPtr, dwId, objType, act);
            int deletedRecord = 0;
            if (objType == 1) deletedRecord = 1;
            else if (objType == 2 && dwId < 0x10000) deletedRecord = 1;
            else deletedRecord = 0;
            if (isDw && ShouldTraceMpauthDw())
            {
                if (InterlockedDecrement(&g_MpauthDwTraceBudget) >= 0)
                {
                    uint16_t netId = MpauthLocalNetId();
                    const char* role = MpauthPeerRole();
                    Log(L"[MPAUTH_DW_REMOVE] peer=%hs netId=0x%04X id=0x%08X ptr=0x%08X type=%u act=0x%04X deleted_record=%d\n",
                        role, netId, dwId, (uint32_t)(uintptr_t)thisPtr, (unsigned)objType, (unsigned)act, deletedRecord);
                    Log(L"MPAUTH_DW_REMOVE peer=%hs id=0x%08X ptr=0x%08X deleted_record=%d\n",
                        role, dwId, (uint32_t)(uintptr_t)thisPtr, deletedRecord);
                    g_MpauthRecentDwRemovedIds.insert(dwId);
                    g_MpauthDwRemoveTick[dwId] = GetTickCount64();
                    g_MpauthDwDeletedRecord[dwId] = deletedRecord;
                }
                else
                {
                    InterlockedIncrement(&g_MpauthDwTraceBudget);
                }
            }
            if (g_MpauthGoRemoveOrig)
                g_MpauthGoRemoveOrig(thisPtr);
            else if (g_GameObjectRemoveDetour.trampoline)
                reinterpret_cast<FnMpauthGoRemove>(g_GameObjectRemoveDetour.trampoline)(thisPtr);
        }
        void __fastcall MpauthSetRemoteHook(void* thisPtr, void* /*edx*/)
        {
            uint32_t dwId = 0; uint8_t objType = 0xFF; uint16_t act = 0xFFFF;
            bool preHas = MpauthReadDwIdentity((uint8_t*)thisPtr - kDayWreckerDistributedOffset, dwId, objType, act);
            if (!preHas) MpauthReadDwIdentity(thisPtr, dwId, objType, act);
            if (g_MpauthSetRemoteOrig)
                g_MpauthSetRemoteOrig(thisPtr);
            else if (g_DistributedCreateDetour.trampoline)
                reinterpret_cast<FnMpauthSetRemote>(g_DistributedCreateDetour.trampoline)(thisPtr);
            uint32_t postId = dwId; uint8_t postType = objType;
            MpauthReadDwIdentity(thisPtr, postId, postType, act);
            void* complete = (uint8_t*)thisPtr - kDayWreckerDistributedOffset;
            bool isDw = MpauthIsDayWreckerObject(complete) || MpauthIsDayWreckerObject(thisPtr);
            if (isDw && ShouldTraceMpauthDw())
            {
                int revived = 0;
                uint32_t logId = postId != 0 ? postId : dwId;
                auto it = g_MpauthRecentDwRemovedIds.find(logId);
                if (it != g_MpauthRecentDwRemovedIds.end())
                    revived = 1;
                if (InterlockedDecrement(&g_MpauthDwTraceBudget) >= 0)
                {
                    uint16_t netId = MpauthLocalNetId();
                    const char* role = MpauthPeerRole();
                    Log(L"[MPAUTH_DW_CREATE] peer=%hs netId=0x%04X id=0x%08X ptr=0x%08X type=%u->%u revived=%d\n",
                        role, netId, logId, (uint32_t)(uintptr_t)complete, (unsigned)objType, (unsigned)postType, revived);
                    Log(L"MPAUTH_DW_CREATE peer=%hs id=0x%08X ptr=0x%08X revived=%d\n",
                        role, logId, (uint32_t)(uintptr_t)complete, revived);
                }
                else
                {
                    InterlockedIncrement(&g_MpauthDwTraceBudget);
                }
            }
        }
        void __cdecl MpauthOrdnanceReceiverHook(char* a, uint32_t b, uint16_t c)
        {
            g_MpauthInOrdnanceReceive = true;
            // Heuristic for existing vs new: if we've already seen a Hit from this sender, the receiver likely found an existing object
            int rxFound = -1;
            __try
            {
                bool hasSender = false;
                for (auto &kv : g_MpauthSplHitCounts)
                {
                    if ((kv.first >> 16) == (uint32_t)c)
                    {
                        hasSender = true;
                        break;
                    }
                }
                rxFound = hasSender ? 1 : 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { rxFound = -1; }
            if (ShouldTraceMpauthSpl())
            {
                if (InterlockedDecrement(&g_MpauthSplTraceBudget) >= 0)
                {
                    uint16_t netId = MpauthLocalNetId();
                    const char* role = MpauthPeerRole();
                    const char* foundStr = (rxFound == 1 ? "existing" : (rxFound == 0 ? "new" : "unknown"));
                    Log(L"[MPAUTH_SPL_RX] peer=%hs netId=0x%04X sender=0x%04X packet=0x%08X len=%u inRecv=1 found=%hs\n",
                        role, netId, (unsigned)c, (uint32_t)(uintptr_t)a, (unsigned)b, foundStr);
                    Log(L"MPAUTH_SPL_RX peer=%hs source=0x%04X ordid=0xFFFF ptr=0x%08X flags=0x%X dt=0.0 found=%hs\n",
                        role, (unsigned)c, (uint32_t)(uintptr_t)a, foundStr);
                }
                else
                {
                    InterlockedIncrement(&g_MpauthSplTraceBudget);
                }
            }
            if (g_MpauthOrdnReceiveOrig)
                g_MpauthOrdnReceiveOrig(a,b,c);
            else if (g_OrdnanceReceiverDetour.trampoline)
                reinterpret_cast<FnMpauthOrdnReceive>(g_OrdnanceReceiverDetour.trampoline)(a,b,c);
            g_MpauthInOrdnanceReceive = false;
        }
        void __fastcall MpauthSprayBombHitHook(void* thisPtr, void* /*edx*/, void* a, void* b)
        {
            uint16_t src = 0xFFFF, ord = 0xFFFF; int32_t bSend = -1; uint32_t flags = 0; float dt = 0.0f;
            MpauthReadOrdnanceFields(thisPtr, src, ord, bSend, flags, dt);
            uint32_t key = ((uint32_t)src << 16) | ord;
            int count = 1;
            auto it = g_MpauthSplHitCounts.find(key);
            if (it != g_MpauthSplHitCounts.end())
            {
                it->second += 1;
                count = it->second;
            }
            else
            {
                g_MpauthSplHitCounts[key] = 1;
            }
            // Periodic bounding: avoid unbounded growth over very long sessions where (source,ordid) may reuse
            if (g_MpauthSplHitCounts.size() > 1024)
            {
                if (InterlockedDecrement(&g_MpauthSplHitMapLogBudget) >= 0)
                    Log(L"[MPAUTH] Hit map size %zu, clearing to bound reuse confusion\n", g_MpauthSplHitCounts.size());
                g_MpauthSplHitCounts.clear();
                g_MpauthSplHitCounts[key] = count;
            }
            if (ShouldTraceMpauthSpl())
            {
                if (InterlockedDecrement(&g_MpauthSplTraceBudget) >= 0)
                {
                    uint16_t netId = MpauthLocalNetId();
                    const char* role = MpauthPeerRole();
                    Log(L"[MPAUTH_SPL_HIT] peer=%hs netId=0x%04X source=0x%04X ordid=0x%04X ptr=0x%08X flags=0x%08X bSend=%d dt=%f build_count=%d inRecv=%u\n",
                        role, netId, (unsigned)src, (unsigned)ord, (uint32_t)(uintptr_t)thisPtr, flags, bSend, dt, count, g_MpauthInOrdnanceReceive?1u:0u);
                    Log(L"MPAUTH_SPL_HIT peer=%hs source=0x%04X ordid=0x%04X ptr=0x%08X build_count=%d\n",
                        role, (unsigned)src, (unsigned)ord, (uint32_t)(uintptr_t)thisPtr, count);
                }
                else
                {
                    InterlockedIncrement(&g_MpauthSplTraceBudget);
                }
            }
            if (g_MpauthSprayHitOrig)
                g_MpauthSprayHitOrig(thisPtr, a, b);
            else if (g_SprayBombHitDetour.trampoline)
                reinterpret_cast<FnMpauthSprayHit>(g_SprayBombHitDetour.trampoline)(thisPtr, a, b);
        }
        void __fastcall MpauthSprayBombSimulateHook(void* thisPtr, void* /*edx*/, float dt)
        {
            if (g_MpauthInOrdnanceReceive && ShouldTraceMpauthSpl())
            {
                uint16_t src = 0xFFFF, ord = 0xFFFF; int32_t bSend = -1; uint32_t flags = 0; float curDt = 0.0f;
                MpauthReadOrdnanceFields(thisPtr, src, ord, bSend, flags, curDt);
                if (InterlockedDecrement(&g_MpauthSplTraceBudget) >= 0)
                {
                    uint16_t netId = MpauthLocalNetId();
                    const char* role = MpauthPeerRole();
                    Log(L"[MPAUTH_SPL_SIM] peer=%hs netId=0x%04X source=0x%04X ordid=0x%04X ptr=0x%08X flags_before=0x%08X dt=%f bSend=%d\n",
                        role, netId, (unsigned)src, (unsigned)ord, (uint32_t)(uintptr_t)thisPtr, flags, dt, bSend);
                    Log(L"MPAUTH_SPL_SIM peer=%hs source=0x%04X ordid=0x%04X ptr=0x%08X flags_before=0x%08X\n",
                        role, (unsigned)src, (unsigned)ord, (uint32_t)(uintptr_t)thisPtr, flags);
                }
                else
                {
                    InterlockedIncrement(&g_MpauthSplTraceBudget);
                }
            }
            if (g_MpauthSpraySimOrig)
                g_MpauthSpraySimOrig(thisPtr, dt);
            else if (g_SprayBombSimulateDetour.trampoline)
                reinterpret_cast<FnMpauthSpraySim>(g_SprayBombSimulateDetour.trampoline)(thisPtr, dt);
        }
        void __cdecl MpauthOrdinaryStateReaderHook(uint16_t p1, uint8_t* p2, uint32_t p3, float p4)
        {
            // Extract ID from packet: p2+2 is dwLocalID (uint32_t)
            uint32_t dwId = 0;
            uint8_t route = 0xFF;
            __try
            {
                if (p2)
                {
                    dwId = *(uint32_t*)(p2 + 2);
                    route = p2[1] & 3;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}
            bool isCandidate = false;
            int deletedRec = 0;
            __try
            {
                auto it = g_MpauthRecentDwRemovedIds.find(dwId);
                if (it != g_MpauthRecentDwRemovedIds.end())
                    isCandidate = true;
                auto it2 = g_MpauthDwDeletedRecord.find(dwId);
                if (it2 != g_MpauthDwDeletedRecord.end())
                    deletedRec = it2->second;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}
            // Only log when this ID was recently removed as Daywrecker to avoid spam, or when tracing is enabled and budget allows
            if (isCandidate && ShouldTraceMpauthDw())
            {
                if (InterlockedDecrement(&g_MpauthDwTraceBudget) >= 0)
                {
                    uint16_t netId = MpauthLocalNetId();
                    const char* role = MpauthPeerRole();
                    Log(L"[MPAUTH_DW_RX] peer=%hs netId=0x%04X id=0x%08X ptr=0x%08X lookup=MISS deleted_record=%d route=ordinary p1=0x%04X p3=%u\n",
                        role, netId, dwId, (uint32_t)(uintptr_t)p2, deletedRec, (unsigned)p1, (unsigned)p3);
                    Log(L"MPAUTH_DW_RX peer=%hs id=0x%08X lookup=MISS deleted_record=%d route=ordinary\n",
                        role, dwId, deletedRec);
                }
                else
                {
                    InterlockedIncrement(&g_MpauthDwTraceBudget);
                }
            }
            else if (ShouldTraceMpauthDw() && g_MpauthDwTraceBudget > 0)
            {
                // Optionally log all ordinary receives at very low volume for debugging, but only if isCandidate to keep noise low
            }
            if (g_MpauthOrdinaryReaderOrig)
                g_MpauthOrdinaryReaderOrig(p1, p2, p3, p4);
            else if (g_OrdinaryStateReaderDetour.trampoline)
                reinterpret_cast<FnMpauthOrdinaryReader>(g_OrdinaryStateReaderDetour.trampoline)(p1, p2, p3, p4);
        }
        void __cdecl MpauthPermanentStateReaderHook(int16_t p1, uint32_t p2, uint16_t p3, int32_t p4)
        {
            // This reader is called with different packet layout; try to extract dwId from p4 (packet buffer) if possible
            uint32_t dwId = 0;
            __try
            {
                // p4 is packet buffer address (int), try reading at +2 as in ordinary path
                uint8_t* pkt = reinterpret_cast<uint8_t*>(p4);
                if (pkt)
                {
                    // Heuristic: packet at p4, id at +2 (similar to ordinary)
                    dwId = *(uint32_t*)(pkt + 2);
                    // Fallback: if pkt looks not like packet, try p2
                    if (dwId == 0 || dwId == 0xFFFFFFFF)
                    {
                        uint8_t* alt = reinterpret_cast<uint8_t*>(p2);
                        if (alt) dwId = *(uint32_t*)(alt + 2);
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}
            bool isCandidate = false;
            int deletedRec = 0;
            __try
            {
                auto it = g_MpauthRecentDwRemovedIds.find(dwId);
                if (it != g_MpauthRecentDwRemovedIds.end())
                    isCandidate = true;
                auto it2 = g_MpauthDwDeletedRecord.find(dwId);
                if (it2 != g_MpauthDwDeletedRecord.end())
                    deletedRec = it2->second;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}
            if (isCandidate && ShouldTraceMpauthDw())
            {
                if (InterlockedDecrement(&g_MpauthDwTraceBudget) >= 0)
                {
                    uint16_t netId = MpauthLocalNetId();
                    const char* role = MpauthPeerRole();
                    Log(L"[MPAUTH_DW_RX] peer=%hs netId=0x%04X id=0x%08X ptr=0x%08X lookup=MISS deleted_record=%d route=permanent p1=%d p3=0x%04X\n",
                        role, netId, dwId, (uint32_t)(uintptr_t)p4, deletedRec, (int)p1, (unsigned)p3);
                    Log(L"MPAUTH_DW_RX peer=%hs id=0x%08X lookup=MISS deleted_record=%d route=permanent\n",
                        role, dwId, deletedRec);
                }
                else
                {
                    InterlockedIncrement(&g_MpauthDwTraceBudget);
                }
            }
            if (g_MpauthPermanentReaderOrig)
                g_MpauthPermanentReaderOrig(p1, p2, p3, p4);
            else if (g_PermanentStateReaderDetour.trampoline)
                reinterpret_cast<FnMpauthPermanentReader>(g_PermanentStateReaderDetour.trampoline)(p1, p2, p3, p4);
        }

        void InitializeMpauthConfig()
        {
            bool enabled = false;
            bool dwEnabled = false;
            bool splEnabled = false;
            bool iniAll = false, iniDw = false, iniSpl = false;
            if (TryGetUserConfigBool("Diagnostics", "TraceMpauth", iniAll))
                enabled = iniAll;
            if (TryGetUserConfigBool("Diagnostics", "TraceMpauthDw", iniDw))
                dwEnabled = iniDw;
            if (TryGetUserConfigBool("Diagnostics", "TraceMpauthSpl", iniSpl))
                splEnabled = iniSpl;
            if (EnvFlagEnabled("OPENSHIM_TRACE_MPAUTH") || EnvFlagEnabled("BZR_TRACE_MPAUTH"))
                enabled = true;
            if (EnvFlagEnabled("OPENSHIM_TRACE_MPAUTH_DW") || EnvFlagEnabled("BZR_TRACE_MPAUTH_DW"))
                dwEnabled = true;
            if (EnvFlagEnabled("OPENSHIM_TRACE_MPAUTH_SPL") || EnvFlagEnabled("BZR_TRACE_MPAUTH_SPL"))
                splEnabled = true;
            if (enabled && !dwEnabled && !splEnabled)
            {
                dwEnabled = true;
                splEnabled = true;
            }
            if ((dwEnabled || splEnabled) && !enabled)
                enabled = true;
            g_MpauthEnabled = enabled;
            g_MpauthDwEnabled = enabled && dwEnabled;
            g_MpauthSplEnabled = enabled && splEnabled;
            long budgetDw = kMpauthDwTraceBudgetDefault;
            long budgetSpl = kMpauthSplTraceBudgetDefault;
            long tmp = 0;
            if (TryGetEnvLong("OPENSHIM_TRACE_MPAUTH_DW_BUDGET", tmp) || TryGetEnvLong("BZR_TRACE_MPAUTH_DW_BUDGET", tmp))
                budgetDw = tmp;
            else if (TryGetEnvLong("OPENSHIM_TRACE_MPAUTH_BUDGET", tmp) || TryGetEnvLong("BZR_TRACE_MPAUTH_BUDGET", tmp))
                budgetDw = tmp;
            if (TryGetEnvLong("OPENSHIM_TRACE_MPAUTH_SPL_BUDGET", tmp) || TryGetEnvLong("BZR_TRACE_MPAUTH_SPL_BUDGET", tmp))
                budgetSpl = tmp;
            else if (TryGetEnvLong("OPENSHIM_TRACE_MPAUTH_BUDGET", tmp) || TryGetEnvLong("BZR_TRACE_MPAUTH_BUDGET", tmp))
                budgetSpl = tmp;
            if (budgetDw < 0) budgetDw = 0;
            if (budgetDw > kMpauthTraceBudgetMax) budgetDw = kMpauthTraceBudgetMax;
            if (budgetSpl < 0) budgetSpl = 0;
            if (budgetSpl > kMpauthTraceBudgetMax) budgetSpl = kMpauthTraceBudgetMax;
            g_MpauthDwTraceBudget = budgetDw;
            g_MpauthSplTraceBudget = budgetSpl;
            if (g_MpauthEnabled)
                Log(L"[MPAUTH] Trace enabled dw=%hs spl=%hs dwBudget=%ld splBudget=%ld\n",
                    BoolText(g_MpauthDwEnabled), BoolText(g_MpauthSplEnabled), budgetDw, budgetSpl);
        }

        void InstallMpauthHooksIfPossible()
        {
            if (!g_MpauthEnabled)
                return;
            if (g_MpauthHooksInstalled)
                return;
            if (!MpauthAddressesBound())
                return;
            {
                // push ebp; mov ebp,esp; sub esp,0x4C: steal all three (GOG 2.2.301).
                static const uint8_t kExpectedDwSim[6] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x4C };
                if (ExpectedBytesMatchAt(g_DayWreckerSimulateAddr, kExpectedDwSim, sizeof(kExpectedDwSim)))
                {
                    if (InstallInlineDetour32(g_DayWreckerSimulateDetour, g_DayWreckerSimulateAddr,
                        reinterpret_cast<void*>(MpauthDwSimulateHook), sizeof(kExpectedDwSim), kExpectedDwSim, sizeof(kExpectedDwSim)))
                    {
                        g_MpauthDwSimOrig = reinterpret_cast<FnMpauthDwSim>(g_DayWreckerSimulateDetour.trampoline);
                        Log(L"[MPAUTH] Installed DayWrecker::Simulate hook at 0x%08X tramp=0x%08X\n",
                            (uint32_t)g_DayWreckerSimulateAddr, (uint32_t)(uintptr_t)g_DayWreckerSimulateDetour.trampoline);
                    }
                    else if (InterlockedDecrement(&g_MpauthInstallRetryBudget) >= 0)
                        Log(L"[MPAUTH] Failed installing DayWrecker::Simulate hook at 0x%08X\n", (uint32_t)g_DayWreckerSimulateAddr);
                }
                else if (InterlockedDecrement(&g_MpauthInstallRetryBudget) >= 0)
                {
                    Log(L"[MPAUTH] DayWrecker::Simulate bytes mismatch at 0x%08X\n", (uint32_t)g_DayWreckerSimulateAddr);
                    __try { uint8_t b[6]={}; memcpy(b, reinterpret_cast<void*>(g_DayWreckerSimulateAddr), 6);
                        Log(L"[MPAUTH] bytes: %02X %02X %02X %02X %02X %02X\n", b[0],b[1],b[2],b[3],b[4],b[5]); } __except(EXCEPTION_EXECUTE_HANDLER) {}
                }
            }
            {
                static const uint8_t kExpectedDwExplode[6] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x4C };
                if (ExpectedBytesMatchAt(g_DayWreckerExplodeAddr, kExpectedDwExplode, sizeof(kExpectedDwExplode)))
                {
                    if (InstallInlineDetour32(g_DayWreckerExplodeDetour, g_DayWreckerExplodeAddr,
                        reinterpret_cast<void*>(MpauthDwExplodeHook), sizeof(kExpectedDwExplode), kExpectedDwExplode, sizeof(kExpectedDwExplode)))
                    {
                        g_MpauthDwExplodeOrig = reinterpret_cast<FnMpauthDwExplode>(g_DayWreckerExplodeDetour.trampoline);
                        Log(L"[MPAUTH] Installed DayWrecker::Explode hook at 0x%08X tramp=0x%08X\n",
                            (uint32_t)g_DayWreckerExplodeAddr, (uint32_t)(uintptr_t)g_DayWreckerExplodeDetour.trampoline);
                    }
                }
                else if (InterlockedDecrement(&g_MpauthInstallRetryBudget) >= 0)
                    Log(L"[MPAUTH] DayWrecker::Explode bytes mismatch at 0x%08X\n", (uint32_t)g_DayWreckerExplodeAddr);
            }
            {
                static const uint8_t kExpectedGoRemove[6] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x38 };
                if (ExpectedBytesMatchAt(g_GameObjectRemoveAddr, kExpectedGoRemove, sizeof(kExpectedGoRemove)))
                {
                    if (InstallInlineDetour32(g_GameObjectRemoveDetour, g_GameObjectRemoveAddr,
                        reinterpret_cast<void*>(MpauthGoRemoveHook), sizeof(kExpectedGoRemove), kExpectedGoRemove, sizeof(kExpectedGoRemove)))
                    {
                        g_MpauthGoRemoveOrig = reinterpret_cast<FnMpauthGoRemove>(g_GameObjectRemoveDetour.trampoline);
                        Log(L"[MPAUTH] Installed GameObject::Remove hook at 0x%08X\n", (uint32_t)g_GameObjectRemoveAddr);
                    }
                }
                else if (InterlockedDecrement(&g_MpauthInstallRetryBudget) >= 0)
                    Log(L"[MPAUTH] GameObject::Remove bytes mismatch at 0x%08X\n", (uint32_t)g_GameObjectRemoveAddr);
            }
            {
                static const uint8_t kExpectedSetRemote[6] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x20 };
                if (ExpectedBytesMatchAt(g_DayWreckerSetRemoteAddr, kExpectedSetRemote, sizeof(kExpectedSetRemote)))
                {
                    if (InstallInlineDetour32(g_DistributedCreateDetour, g_DayWreckerSetRemoteAddr,
                        reinterpret_cast<void*>(MpauthSetRemoteHook), sizeof(kExpectedSetRemote), kExpectedSetRemote, sizeof(kExpectedSetRemote)))
                    {
                        g_MpauthSetRemoteOrig = reinterpret_cast<FnMpauthSetRemote>(g_DistributedCreateDetour.trampoline);
                        Log(L"[MPAUTH] Installed SetRemote hook at 0x%08X\n", (uint32_t)g_DayWreckerSetRemoteAddr);
                    }
                }
                else if (InterlockedDecrement(&g_MpauthInstallRetryBudget) >= 0)
                    Log(L"[MPAUTH] SetRemote bytes mismatch at 0x%08X\n", (uint32_t)g_DayWreckerSetRemoteAddr);
            }
            {
                // push ebp; mov ebp,esp; sub esp,0x150 (imm32 form): boundary at 9.
                static const uint8_t kExpectedOrdnRecv[9] = { 0x55, 0x8B, 0xEC, 0x81, 0xEC, 0x50, 0x01, 0x00, 0x00 };
                if (ExpectedBytesMatchAt(g_OrdnanceReceiverAddr, kExpectedOrdnRecv, sizeof(kExpectedOrdnRecv)))
                {
                    if (InstallInlineDetour32(g_OrdnanceReceiverDetour, g_OrdnanceReceiverAddr,
                        reinterpret_cast<void*>(MpauthOrdnanceReceiverHook), sizeof(kExpectedOrdnRecv), kExpectedOrdnRecv, sizeof(kExpectedOrdnRecv)))
                    {
                        g_MpauthOrdnReceiveOrig = reinterpret_cast<FnMpauthOrdnReceive>(g_OrdnanceReceiverDetour.trampoline);
                        Log(L"[MPAUTH] Installed Ordnance_Receive hook at 0x%08X\n", (uint32_t)g_OrdnanceReceiverAddr);
                    }
                }
                else if (InterlockedDecrement(&g_MpauthInstallRetryBudget) >= 0)
                {
                    Log(L"[MPAUTH] Ordnance_Receive bytes mismatch at 0x%08X\n", (uint32_t)g_OrdnanceReceiverAddr);
                    __try { uint8_t b[6]={}; memcpy(b, reinterpret_cast<void*>(g_OrdnanceReceiverAddr), 6);
                        Log(L"[MPAUTH] ordn recv bytes: %02X %02X %02X %02X %02X %02X\n", b[0],b[1],b[2],b[3],b[4],b[5]); } __except(EXCEPTION_EXECUTE_HANDLER) {}
                }
            }
            {
                static const uint8_t kExpectedHit[9] = { 0x55, 0x8B, 0xEC, 0x81, 0xEC, 0x08, 0x03, 0x00, 0x00 };
                if (ExpectedBytesMatchAt(g_SprayBombHitAddr, kExpectedHit, sizeof(kExpectedHit)))
                {
                    if (InstallInlineDetour32(g_SprayBombHitDetour, g_SprayBombHitAddr,
                        reinterpret_cast<void*>(MpauthSprayBombHitHook), sizeof(kExpectedHit), kExpectedHit, sizeof(kExpectedHit)))
                    {
                        g_MpauthSprayHitOrig = reinterpret_cast<FnMpauthSprayHit>(g_SprayBombHitDetour.trampoline);
                        Log(L"[MPAUTH] Installed SprayBomb::Hit hook at 0x%08X\n", (uint32_t)g_SprayBombHitAddr);
                    }
                }
                else if (InterlockedDecrement(&g_MpauthInstallRetryBudget) >= 0)
                    Log(L"[MPAUTH] SprayBomb::Hit bytes mismatch at 0x%08X\n", (uint32_t)g_SprayBombHitAddr);
            }
            {
                static const uint8_t kExpectedSim[6] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x08 };
                if (ExpectedBytesMatchAt(g_SprayBombSimulateAddr, kExpectedSim, sizeof(kExpectedSim)))
                {
                    if (InstallInlineDetour32(g_SprayBombSimulateDetour, g_SprayBombSimulateAddr,
                        reinterpret_cast<void*>(MpauthSprayBombSimulateHook), sizeof(kExpectedSim), kExpectedSim, sizeof(kExpectedSim)))
                    {
                        g_MpauthSpraySimOrig = reinterpret_cast<FnMpauthSpraySim>(g_SprayBombSimulateDetour.trampoline);
                        Log(L"[MPAUTH] Installed SprayBomb::Simulate hook at 0x%08X\n", (uint32_t)g_SprayBombSimulateAddr);
                    }
                }
                else if (InterlockedDecrement(&g_MpauthInstallRetryBudget) >= 0)
                    Log(L"[MPAUTH] SprayBomb::Simulate bytes mismatch at 0x%08X\n", (uint32_t)g_SprayBombSimulateAddr);
            }
            // Ordinary state reader (004B8590) — daywrecker revive path, GOG 2.2.301 only
            {
                // push ebp; mov ebp,esp; sub esp,0x160 (imm32 form): boundary at 9.
                static const uint8_t kExpectedOrdinary[9] = { 0x55, 0x8B, 0xEC, 0x81, 0xEC, 0x60, 0x01, 0x00, 0x00 };
                if (ExpectedBytesMatchAt(g_OrdinaryStateReaderAddr, kExpectedOrdinary, sizeof(kExpectedOrdinary)))
                {
                    if (InstallInlineDetour32(g_OrdinaryStateReaderDetour, g_OrdinaryStateReaderAddr,
                        reinterpret_cast<void*>(MpauthOrdinaryStateReaderHook), sizeof(kExpectedOrdinary), kExpectedOrdinary, sizeof(kExpectedOrdinary)))
                    {
                        g_MpauthOrdinaryReaderOrig = reinterpret_cast<FnMpauthOrdinaryReader>(g_OrdinaryStateReaderDetour.trampoline);
                        Log(L"[MPAUTH] Installed ordinary state reader hook at 0x%08X\n", (uint32_t)g_OrdinaryStateReaderAddr);
                    }
                }
                else if (InterlockedDecrement(&g_MpauthInstallRetryBudget) >= 0)
                    Log(L"[MPAUTH] Ordinary reader bytes mismatch at 0x%08X\n", (uint32_t)g_OrdinaryStateReaderAddr);
            }
            // Permanent state reader (004B8FA0)
            {
                static const uint8_t kExpectedPermanent[6] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x68 };
                if (ExpectedBytesMatchAt(g_PermanentStateReaderAddr, kExpectedPermanent, sizeof(kExpectedPermanent)))
                {
                    if (InstallInlineDetour32(g_PermanentStateReaderDetour, g_PermanentStateReaderAddr,
                        reinterpret_cast<void*>(MpauthPermanentStateReaderHook), sizeof(kExpectedPermanent), kExpectedPermanent, sizeof(kExpectedPermanent)))
                    {
                        g_MpauthPermanentReaderOrig = reinterpret_cast<FnMpauthPermanentReader>(g_PermanentStateReaderDetour.trampoline);
                        Log(L"[MPAUTH] Installed permanent state reader hook at 0x%08X\n", (uint32_t)g_PermanentStateReaderAddr);
                    }
                }
                else if (InterlockedDecrement(&g_MpauthInstallRetryBudget) >= 0)
                    Log(L"[MPAUTH] Permanent reader bytes mismatch at 0x%08X\n", (uint32_t)g_PermanentStateReaderAddr);
            }
            g_MpauthHooksInstalled = g_MpauthDwSimOrig || g_MpauthDwExplodeOrig || g_MpauthGoRemoveOrig || g_MpauthSetRemoteOrig || g_MpauthOrdnReceiveOrig || g_MpauthSprayHitOrig;
            if (g_MpauthHooksInstalled)
                Log(L"[MPAUTH] Hooks installed dwSim=%hs explode=%hs remove=%hs setRemote=%hs ordRecv=%hs hit=%hs sim=%hs\n",
                    BoolText(g_MpauthDwSimOrig!=nullptr), BoolText(g_MpauthDwExplodeOrig!=nullptr), BoolText(g_MpauthGoRemoveOrig!=nullptr),
                    BoolText(g_MpauthSetRemoteOrig!=nullptr), BoolText(g_MpauthOrdnReceiveOrig!=nullptr), BoolText(g_MpauthSprayHitOrig!=nullptr), BoolText(g_MpauthSpraySimOrig!=nullptr));
        }
    }

}
