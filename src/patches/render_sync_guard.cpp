// render_sync_guard.cpp -- the render-node sync skips an object whose Ogre
// Entity or SceneNode has already been destroyed, instead of calling through
// a dead vtable.
//
// Site: GameObject::UpdatePosition (0x004DB100) calls the render-node sync
// FUN_00680BD0 (void __cdecl(renderData*), renderData = go+0xF0) at 0x004DB498
// (`push eax; call rel32; add esp,4`). Only that rel32 is redirected; the
// stock function is untouched and is the only thing the hook calls.
//
// FUN_00680BD0 (FUN_00680bd0.c): node = renderData+0x98, entity =
// renderData+0x94. With a non-null node it calls node vtbl+0x24
// (setOrientation) and +0x2C (setPosition), then entity vtbl+0xC8
// (MovableObject::setVisibilityFlags) with no check on the entity. Crash
// reports (EIP 0x61206F4E, ecx = entity, edx = OgreMain
// ??_7ShadowCaster@Ogre@@6B@) show an entity already destroyed: MSVC leaves
// the base class vtable in a destroyed object, so slot 0xC8 lands on the text
// "No animable value named '" in OgreMain .rdata. Both reports were taken
// inside the Lua error alert that a failing DeleteObject callback opens,
// whose nested UI loop keeps simulating and rendering.
//
// Check: entity primary vptr == ??_7Entity@Ogre@@6BShadowCaster@1@@ (exact;
// a destructor always rewrites the primary vptr first), node vptr ==
// ??_7SceneNode@Ogre@@6B@ or an RTTI subclass of SceneNode (cached), all
// resolved from OgreMain exports. Anything else: skip the sync for this call
// and log once per render data. Reads are under SEH; no VirtualQuery per
// object per frame.

#include "render_sync_guard_install.h"
#include "render_sync_guard_policy.h"

#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>

namespace BZROpenShim
{
    namespace RenderSyncGuard
    {
        namespace
        {
            constexpr const char* kComponent = "RENDERSYNC";
            constexpr uint32_t kEntityOffset = 0x94;
            constexpr uint32_t kNodeOffset = 0x98;

            using FnRenderSync = void(__cdecl*)(void* renderData);

            std::atomic<bool> g_Done{ false };
            FnRenderSync g_Stock = nullptr;

            uintptr_t g_EntityShadowCasterVtbl = 0;
            uintptr_t g_SceneNodeVtbl = 0;

            // SceneNode subclasses seen live (e.g. an OctreeNode if a scene
            // manager plugin is ever loaded). Render thread only.
            uintptr_t g_ExtraNodeVtbls[4] = {};
            unsigned g_ExtraNodeCount = 0;

            SeenSet<64> g_Logged;
            volatile LONG g_LogBudget = 32;
            volatile LONG g_SkipCount = 0;

            struct Raw
            {
                uintptr_t entity;
                uintptr_t node;
                uintptr_t entityVptr0;
                uintptr_t nodeVptr;
                uintptr_t obj76;
            };

            // SEH leaf: plain types only.
            bool ReadRaw(const void* renderData, Raw& out)
            {
                out = {};
                if (!renderData)
                    return false;
                __try
                {
                    const uint8_t* rd = static_cast<const uint8_t*>(renderData);
                    out.obj76 = *reinterpret_cast<const volatile uintptr_t*>(rd);
                    out.entity = *reinterpret_cast<const volatile uintptr_t*>(rd + kEntityOffset);
                    out.node = *reinterpret_cast<const volatile uintptr_t*>(rd + kNodeOffset);
                    // With no node, stock never touches the entity (it either
                    // does nothing or builds both), so neither is read here.
                    if (!out.node)
                        return true;
                    out.nodeVptr = *reinterpret_cast<const volatile uintptr_t*>(out.node);
                    if (out.entity)
                        out.entityVptr0 = *reinterpret_cast<const volatile uintptr_t*>(out.entity);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool IsNodeVtable(uintptr_t vptr)
            {
                if (vptr == g_SceneNodeVtbl)
                    return true;
                for (unsigned i = 0; i < g_ExtraNodeCount; ++i)
                    if (g_ExtraNodeVtbls[i] == vptr)
                        return true;
                // A destroyed SceneNode carries Node's vtable, which does not
                // derive from SceneNode, so this cannot accept a dead node.
                if (vptr == 0 || !Hooks::VtableDerivesFrom(vptr, ".?AVSceneNode@Ogre@@"))
                    return false;
                if (g_ExtraNodeCount < _countof(g_ExtraNodeVtbls))
                {
                    g_ExtraNodeVtbls[g_ExtraNodeCount++] = vptr;
                    LogShimA(LogLevel::Info, kComponent, "accepting SceneNode subclass vtable 0x%08X",
                             static_cast<unsigned>(vptr));
                }
                return true;
            }

            void LogSkip(const void* renderData, const Raw& raw, Verdict verdict)
            {
                const LONG skips = InterlockedIncrement(&g_SkipCount);
                if (!g_Logged.FirstTime(reinterpret_cast<uintptr_t>(renderData)))
                    return;
                if (InterlockedDecrement(&g_LogBudget) < 0)
                    return;
                char entityClass[96] = {};
                char nodeClass[96] = {};
                const char* ec = raw.entity ? Hooks::TryGetRttiClassName(reinterpret_cast<const void*>(raw.entity),
                                                                          entityClass, sizeof(entityClass))
                                            : nullptr;
                const char* nc = raw.node ? Hooks::TryGetRttiClassName(reinterpret_cast<const void*>(raw.node),
                                                                        nodeClass, sizeof(nodeClass))
                                          : nullptr;
                LogShimA(LogLevel::Warn, kComponent,
                         "skipped render sync (%s): renderData=0x%08X obj76=0x%08X entity=0x%08X vptr=0x%08X "
                         "(%s) node=0x%08X vptr=0x%08X (%s); total skips=%ld",
                         VerdictName(verdict), static_cast<unsigned>(reinterpret_cast<uintptr_t>(renderData)),
                         static_cast<unsigned>(raw.obj76), static_cast<unsigned>(raw.entity),
                         static_cast<unsigned>(raw.entityVptr0),
                         ec ? ec : "?", static_cast<unsigned>(raw.node), static_cast<unsigned>(raw.nodeVptr),
                         nc ? nc : "?", static_cast<long>(skips));
            }

            void __cdecl RenderSyncHook(void* renderData)
            {
                Raw raw;
                Observed o;
                o.readOk = ReadRaw(renderData, raw);
                o.node = raw.node;
                o.entity = raw.entity;
                o.nodeLive = raw.node != 0 && IsNodeVtable(raw.nodeVptr);
                o.entityLive = raw.entity != 0 && raw.entityVptr0 == g_EntityShadowCasterVtbl;
                const Verdict verdict = Decide(o);
                if (verdict == Verdict::CallStock)
                {
                    g_Stock(renderData);
                    return;
                }
                LogSkip(renderData, raw, verdict);
            }

            bool Fail(const char* what)
            {
                LogShimA(LogLevel::Warn, kComponent, "%s; leaving the stock render-node sync call", what);
                return false;
            }

            bool IsEnabled()
            {
                bool enabled = true;
                const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_RENDER_SYNC_GUARD", "BZR_DISABLE_RENDER_SYNC_GUARD" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            bool DoInstall()
            {
                uint32_t call = 0, stock = 0;
                const HookEngine::EngineRow rows[] = {
                    { "RenderNodeSyncCall", &call },
                    { "RenderNodeSync", &stock },
                };
                if (!HookEngine::BindEngineRows("render sync guard", rows))
                    return Fail("a byte guard did not match");

                g_EntityShadowCasterVtbl = reinterpret_cast<uintptr_t>(
                    Hooks::ResolveOgreProc<const void*>("??_7Entity@Ogre@@6BShadowCaster@1@@"));
                g_SceneNodeVtbl = reinterpret_cast<uintptr_t>(
                    Hooks::ResolveOgreProc<const void*>("??_7SceneNode@Ogre@@6B@"));
                if (!g_EntityShadowCasterVtbl || !g_SceneNodeVtbl)
                    return Fail("Ogre::Entity / Ogre::SceneNode vtables are not exported by OgreMain");

                g_Stock = reinterpret_cast<FnRenderSync>(static_cast<uintptr_t>(stock));
                if (!Hooks::RedirectCallTarget(call, stock, reinterpret_cast<uintptr_t>(&RenderSyncHook)))
                    return Fail("the call at the site no longer targets the stock render-node sync");

                LogShimA(LogLevel::Info, kComponent,
                         "installed: call 0x%08X -> guard (stock 0x%08X; Entity 0x%08X, SceneNode 0x%08X)",
                         call, stock, static_cast<unsigned>(g_EntityShadowCasterVtbl),
                         static_cast<unsigned>(g_SceneNodeVtbl));
                return true;
            }
        }

        void InstallRenderSyncGuardIfPossible()
        {
            if (g_Done.exchange(true))
                return;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] RenderSyncVtableGuard = 0)");
                return;
            }
            DoInstall();
        }
    }
}
