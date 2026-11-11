// ordnance_entity_leak.cpp
// BZR Open Shim - [Fixes] OrdnanceEntityLeak: destroy the Ogre Entity that
// stock ordnance teardown orphans.
//
// GOG 0x00680620 (cdecl, one Ordnance* argument, only caller 0x00585635 in
// the ordnance cleanup FUN_00585560) does:
//     node = ord->+0xD0; if (node) { node->detachAllObjects(); FUN_0067E550(node); }
// detachAllObjects is SceneNode vtable slot +0x140 (OgreMain ??_7SceneNode
// at 0x106CA17C, slot 0x106CA2BC = 0x1001DE44 ?detachAllObjects@SceneNode).
// FUN_0067E550 -> FUN_0067CFA0 destroys only the objects still attached to
// the node (SceneManager vtbl +0x48C), then destroys the node. The Entity at
// +0xCC was detached first, so it is never destroyed and stays registered in
// the SceneManager for the rest of the mission: one leaked Entity per round
// (gatst00.mesh for rockets/bullets). FUN_0067EC70 creates the trio:
// Entity +0xCC, SceneNode +0xD0, SkeletonInstance +0xD4, and is what both
// creation paths (0x0058552B, 0x00680A5E) call, after zeroing all three.
//
// The hook runs the stock function first, then destroys the Entity only when
// it is still the same pointer, still registered under its name in the live
// SceneManager (getEntity(name) == entity) and no longer attached (decision
// in include/ordnance_entity_leak_policy.h). That makes
// a double destroy impossible even if a later build starts destroying it: a
// destroyed Entity is no longer in the SceneManager's map. +0xCC and +0xD4
// (the SkeletonInstance belongs to the Entity) are then zeroed. +0xD0 is left
// as stock leaves it.
//
// Live set: stock FUN_0067D0C0 (mission end, save load, replay) runs
// SceneManager::destroyAllEntities, which frees every Entity while ordnance
// keeps its +0xCC pointer. A second detour on the creator FUN_0067EC70 (cdecl,
// one Ordnance*; callers clean with add esp,4) records each Entity it makes;
// SceneManagerDestroyAllEntitiesHook (lifecycle_seams.cpp) clears the set
// before the free. Teardown only touches a pointer that is in the set, so a
// freed or reused address is never dereferenced. Without the creation detour
// the teardown detour is not installed.
//
// Bench census: OPENSHIM_ORDNANCE_ENTITY_LEAK_COUNT_ONLY=1 installs the hook
// even when the fix is off and logs "[ORDLEAK] orphaned(countOnly)=N" for
// the Entities it would have destroyed, leaving them leaked as stock does.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "hook_engine.h"
#include "ordnance_entity_leak_policy.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>

#include <cstdint>
#include <string>
#include <unordered_set>

namespace BZROpenShim
{
    namespace Hooks
    {
        bool g_OrdnanceEntityLeakFixEnabled = true;

        namespace
        {
            constexpr size_t kOrdnanceEntityOffset = 0xCC;
            constexpr size_t kOrdnanceSkeletonOffset = 0xD4;
            // push ebp; mov ebp,esp; sub esp,0Ch; mov eax,[ebp+8]; mov [ebp-8],eax.
            // Must cover the whole signature: InstallInlineDetour32 refuses an
            // expected-bytes length longer than the patch (hook_patch_helpers.cpp).
            constexpr size_t kTeardownPatchLen = 12;
            // push ebp; mov ebp,esp; push -1; push 0x0084F6E0 (SEH frame
            // prologue; the push imm32 is absolute, so it relocates as is).
            constexpr size_t kCreatePatchLen = 10;
            constexpr unsigned long kMsvcCppException = 0xE06D7363UL;

            using FnTeardown = void(__cdecl*)(void*);
            using FnCreate = void(__cdecl*)(void*);
            using FnIsAttached = bool(__thiscall*)(const void*);
            using FnGetName = const std::string*(__thiscall*)(const void*);
            using FnHasEntity = bool(__thiscall*)(const void*, const std::string&);
            using FnGetEntity = void*(__thiscall*)(const void*, const std::string&);
            using FnDestroyEntity = void(__thiscall*)(void*, void*);

            InlineDetour32 g_TeardownDetour = {};
            uintptr_t g_TeardownAddr = 0;
            InlineDetour32 g_CreateDetour = {};
            uintptr_t g_CreateAddr = 0;
            bool g_CreateInstalled = false;
            bool g_Installed = false;
            bool g_InstallAttempted = false;
            bool g_MismatchLogged = false;

            FnIsAttached g_IsAttached = nullptr;
            FnGetName g_GetName = nullptr;
            FnHasEntity g_HasEntity = nullptr;
            FnGetEntity g_GetEntity = nullptr;
            FnDestroyEntity g_DestroyEntity = nullptr;

            // Ordnance Entities made by the creator and not yet torn down or
            // freed by destroyAllEntities. Creation, teardown and the scene
            // teardown all run on the game's main thread, so no lock.
            std::unordered_set<void*> g_LiveEntities;

            volatile LONG g_Destroyed = 0;
            volatile LONG g_SkipUntracked = 0;
            volatile LONG g_SkipChanged = 0;
            volatile LONG g_SkipNoScene = 0;
            volatile LONG g_SkipNotRegistered = 0;
            volatile LONG g_SkipAttached = 0;
            volatile LONG g_SkipQueryFailed = 0;
            volatile LONG g_DestroyFaulted = 0;
            volatile LONG g_NextReport = 1;
            volatile LONG g_LastReportTick = 0;
            // OPENSHIM_ORDNANCE_ENTITY_LEAK_COUNT_ONLY=1 (bench census): hook
            // and count the orphans, but leave them leaked as stock does.
            bool g_CountOnly = false;

            int SehFilter(unsigned long code)
            {
                return code == kMsvcCppException ? EXCEPTION_CONTINUE_SEARCH : EXCEPTION_EXECUTE_HANDLER;
            }

            void* ReadPointerSeh(const uint8_t* base, size_t offset)
            {
                __try
                {
                    return *reinterpret_cast<void* const*>(base + offset);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return nullptr;
                }
            }

            bool ClearPointersSeh(uint8_t* ord)
            {
                __try
                {
                    *reinterpret_cast<void**>(ord + kOrdnanceEntityOffset) = nullptr;
                    *reinterpret_cast<void**>(ord + kOrdnanceSkeletonOffset) = nullptr;
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            // C++ half: lets an Ogre throw unwind OgreMain's frames before it is
            // caught (see the CatchOgreThrow note in chunk_proxy_render.cpp).
            bool QueryRegistrationCpp(const void* sceneManager, const void* entity,
                                      bool& registered, bool& attached)
            {
                try
                {
                    // Registration first: isAttached is only asked of an
                    // Entity the live scene still owns.
                    const std::string* name = g_GetName(entity);
                    registered = name && g_HasEntity(sceneManager, *name) &&
                        g_GetEntity(sceneManager, *name) == entity;
                    attached = registered && g_IsAttached(entity);
                    return true;
                }
                catch (...)
                {
                    return false;
                }
            }

            bool QueryRegistrationSeh(const void* sceneManager, const void* entity,
                                      bool& registered, bool& attached)
            {
                __try
                {
                    return QueryRegistrationCpp(sceneManager, entity, registered, attached);
                }
                __except (SehFilter(GetExceptionCode()))
                {
                    return false;
                }
            }

            bool DestroyEntityCpp(void* sceneManager, void* entity)
            {
                try
                {
                    g_DestroyEntity(sceneManager, entity);
                    return true;
                }
                catch (...)
                {
                    return false;
                }
            }

            bool DestroyEntitySeh(void* sceneManager, void* entity)
            {
                __try
                {
                    return DestroyEntityCpp(sceneManager, entity);
                }
                __except (SehFilter(GetExceptionCode()))
                {
                    return false;
                }
            }

            void ReportIfDue(LONG destroyed)
            {
                // First destroy, every power of two, and at most every 30 s
                // otherwise: proves the fix is live without spamming a long
                // mission, and keeps the running total current for a census.
                const LONG due = g_NextReport;
                const LONG now = static_cast<LONG>(GetTickCount());
                const LONG last = g_LastReportTick;
                const bool powerOfTwo = destroyed >= due &&
                    InterlockedCompareExchange(&g_NextReport, due * 2, due) == due;
                const bool periodic = !powerOfTwo && now - last >= 30000 &&
                    InterlockedCompareExchange(&g_LastReportTick, now, last) == last;
                if (!powerOfTwo && !periodic)
                    return;
                if (powerOfTwo)
                    g_LastReportTick = now;
                Log(L"[ORDLEAK] %s=%ld skipped untracked=%ld changed=%ld noScene=%ld notRegistered=%ld "
                    L"attached=%ld queryFailed=%ld destroyFaulted=%ld\n",
                    g_CountOnly ? L"orphaned(countOnly)" : L"destroyed",
                    destroyed, g_SkipUntracked, g_SkipChanged, g_SkipNoScene, g_SkipNotRegistered,
                    g_SkipAttached, g_SkipQueryFailed, g_DestroyFaulted);
            }

            // Main thread only (see g_LiveEntities).
            void TrackEntity(void* entity)
            {
                try
                {
                    g_LiveEntities.insert(entity);
                }
                catch (...)
                {
                    // Untracked is the safe side: teardown leaves it leaked.
                }
            }

            void __cdecl OrdnanceCreateHook(uint8_t* ord)
            {
                reinterpret_cast<FnCreate>(g_CreateDetour.trampoline)(ord);
                void* const entity = ord ? ReadPointerSeh(ord, kOrdnanceEntityOffset) : nullptr;
                // Tracked only once teardown is hooked, so the set cannot
                // grow unchecked if the teardown detour never installs.
                if (entity && g_Installed)
                    TrackEntity(entity);
            }

            void __cdecl OrdnanceTeardownHook(uint8_t* ord)
            {
                void* const entityBefore =
                    ord ? ReadPointerSeh(ord, kOrdnanceEntityOffset) : nullptr;
                // Membership is decided on the raw pointer value before the
                // stock call and before any Ogre call touches it. Main thread
                // only, like the creation hook and the scene teardown.
                const bool tracked = entityBefore && g_CreateInstalled &&
                    g_LiveEntities.erase(entityBefore) != 0;

                reinterpret_cast<FnTeardown>(g_TeardownDetour.trampoline)(ord);

                if (!entityBefore)
                    return;

                void* const sceneManager = GetOgreSceneManagerRuntime();
                OrdnanceEntityLeak::TeardownObservation o;
                o.entityBefore = entityBefore;
                o.tracked = tracked;
                o.entityAfter = ReadPointerSeh(ord, kOrdnanceEntityOffset);
                o.hasRuntimeScene = sceneManager != nullptr;
                if (tracked && o.entityAfter == entityBefore && sceneManager)
                {
                    o.queryOk = QueryRegistrationSeh(
                        sceneManager, entityBefore, o.registeredInRuntimeScene, o.stillAttached);
                }

                switch (OrdnanceEntityLeak::Decide(o))
                {
                case OrdnanceEntityLeak::Decision::NothingToDo:
                    return;
                case OrdnanceEntityLeak::Decision::SkipUntracked:
                    InterlockedIncrement(&g_SkipUntracked);
                    return;
                case OrdnanceEntityLeak::Decision::SkipChanged:
                    InterlockedIncrement(&g_SkipChanged);
                    return;
                case OrdnanceEntityLeak::Decision::SkipNoScene:
                    InterlockedIncrement(&g_SkipNoScene);
                    return;
                case OrdnanceEntityLeak::Decision::SkipNotRegistered:
                    InterlockedIncrement(&g_SkipNotRegistered);
                    return;
                case OrdnanceEntityLeak::Decision::SkipAttached:
                    InterlockedIncrement(&g_SkipAttached);
                    return;
                case OrdnanceEntityLeak::Decision::SkipQueryFailed:
                    InterlockedIncrement(&g_SkipQueryFailed);
                    return;
                case OrdnanceEntityLeak::Decision::Destroy:
                    break;
                }

                if (g_CountOnly)
                {
                    ReportIfDue(InterlockedIncrement(&g_Destroyed));
                    return;
                }

                const bool destroyed = DestroyEntitySeh(sceneManager, entityBefore);
                // The pointers are cleared either way: a half-destroyed Entity
                // must not be touched again by anyone.
                ClearPointersSeh(ord);
                if (!destroyed)
                {
                    InterlockedIncrement(&g_DestroyFaulted);
                    return;
                }
                ReportIfDue(InterlockedIncrement(&g_Destroyed));
            }

            bool ResolveOgreApis()
            {
                g_IsAttached = ResolveOgreProc<FnIsAttached>("?isAttached@MovableObject@Ogre@@UBE_NXZ");
                g_GetName = ResolveOgreProc<FnGetName>(
                    "?getName@MovableObject@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
                g_HasEntity = ResolveOgreProc<FnHasEntity>(
                    "?hasEntity@SceneManager@Ogre@@UBE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
                g_GetEntity = ResolveOgreProc<FnGetEntity>(
                    "?getEntity@SceneManager@Ogre@@UBEPAVEntity@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
                g_DestroyEntity = ResolveOgreProc<FnDestroyEntity>(
                    "?destroyEntity@SceneManager@Ogre@@UAEXPAVEntity@2@@Z");
                return g_IsAttached && g_GetName && g_HasEntity && g_GetEntity && g_DestroyEntity;
            }
        }

        void InstallOrdnanceEntityLeakFixIfPossible()
        {
            if (g_Installed || g_InstallAttempted)
                return;
            g_InstallAttempted = true;

            char countOnly[4] = {};
            g_CountOnly = GetEnvironmentVariableA(
                "OPENSHIM_ORDNANCE_ENTITY_LEAK_COUNT_ONLY", countOnly, sizeof(countOnly)) == 1 &&
                countOnly[0] == '1';
            if (!g_OrdnanceEntityLeakFixEnabled && !g_CountOnly)
            {
                Log(L"[ORDLEAK] Ordnance entity leak fix disabled ([Fixes] OrdnanceEntityLeak=0 or env)\n");
                return;
            }
            if (!ResolveOgreApis())
            {
                Log(L"[ORDLEAK] OgreMain exports missing; ordnance entity leak fix not installed\n");
                return;
            }
            static const bool bound = [] {
                const HookEngine::EngineRow rows[] = {
                    { "OrdnanceNodeTeardown", &g_TeardownAddr },
                    { "OrdnanceRenderCreate", &g_CreateAddr },
                };
                return HookEngine::BindEngineRows("Ordnance entity leak fix", rows);
            }();
            if (!bound)
                return;

            // The creation detour goes first: without it nothing is tracked,
            // so the teardown detour is not installed and the fix does nothing.
            static const uint8_t kCreateExpectedBytes[] = {
                0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0xE0, 0xF6, 0x84, 0x00,
            };
            static_assert(sizeof(kCreateExpectedBytes) == kCreatePatchLen,
                          "creation patch must cover exactly the verified prologue instructions");
            if (!g_CreateInstalled)
            {
                if (!InstallInlineDetour32(
                        g_CreateDetour,
                        g_CreateAddr,
                        reinterpret_cast<void*>(OrdnanceCreateHook),
                        kCreatePatchLen,
                        kCreateExpectedBytes,
                        sizeof(kCreateExpectedBytes)))
                {
                    if (!g_MismatchLogged)
                    {
                        Log(L"[ORDLEAK] Creation hook bytes not ready/mismatched at 0x%08X; "
                            L"fix disabled (no live set, teardown not hooked)\n",
                            static_cast<uint32_t>(g_CreateAddr));
                        g_MismatchLogged = true;
                    }
                    if (g_IsSteamExe)
                        g_InstallAttempted = false;
                    return;
                }
                g_CreateInstalled = true;
            }

            static const uint8_t kExpectedBytes[] = {
                0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C,
                0x8B, 0x45, 0x08, 0x89, 0x45, 0xF8,
            };
            static_assert(sizeof(kExpectedBytes) <= kTeardownPatchLen,
                          "InstallInlineDetour32 rejects a signature longer than the patch");
            if (!InstallInlineDetour32(
                    g_TeardownDetour,
                    g_TeardownAddr,
                    reinterpret_cast<void*>(OrdnanceTeardownHook),
                    kTeardownPatchLen,
                    kExpectedBytes,
                    sizeof(kExpectedBytes)))
            {
                if (!g_MismatchLogged)
                {
                    Log(L"[ORDLEAK] Stock bytes not ready/mismatched at 0x%08X; fix deferred\n",
                        static_cast<uint32_t>(g_TeardownAddr));
                    g_MismatchLogged = true;
                }
                // Steam's packed image settles to the GOG bytes after launch;
                // RetryDeferredRuntimeHooks tries again then.
                if (g_IsSteamExe)
                    g_InstallAttempted = false;
                return;
            }

            g_Installed = true;
            Log(L"[ORDLEAK] Installed ordnance entity leak %s at 0x%08X (creation tracked at 0x%08X)\n",
                g_CountOnly ? L"census (count only, entities stay leaked)" : L"fix",
                static_cast<uint32_t>(g_TeardownAddr), static_cast<uint32_t>(g_CreateAddr));
        }

        void OrdnanceEntityLeakOnSceneEntitiesDestroyed() noexcept
        {
            // Main thread only: runs inside stock FUN_0067D0C0, like the
            // ordnance creation and teardown hooks.
            g_LiveEntities.clear();
        }
    }
}
