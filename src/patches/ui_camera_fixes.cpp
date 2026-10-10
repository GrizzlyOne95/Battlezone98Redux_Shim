// ui_camera_fixes.cpp
// BZR Open Shim - stock UI and camera fixes: guarded briefing/archive
// scrolling, the multiplayer render-count clamp, the thumbnail BMP
// material guard, the earthquake replay fade, the target-cam satellite
// gate and the cinematic satellite zoom fix, split out of bzr_hooks.cpp.
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
        bool g_BriefingScrollFixInstalled = false;
        bool g_BriefingScrollFixEnabled = true;
        bool g_MultiRenderCountClampInstalled = false;
        bool g_MultiRenderCountClampEnabled = true;
        volatile long g_MultiRenderCountClampLogBudget = 8;
        bool g_ThumbnailBmpGuardEnabled = true;
        bool g_ThumbnailBmpGuardInstalled = false;
        bool g_QuakeReplayFadeInstalled = false;
        bool g_QuakeReplayFadeEnabled = true;
        long g_QuakeReplayFadeSeconds = kQuakeReplayFadeSecondsDefault;
        InlineDetour32 g_EarthQuakeSimulateDetour = {};
        volatile long g_QuakeReplayArmed = 0;
        bool g_TargetCamSatelliteFixInstalled = false;
        bool g_TargetCamSatelliteFixEnabled = true;
        volatile long g_TargetCamSatelliteLogBudget = 8;
        bool g_CinematicSatelliteZoomFixInstalled = false;
        bool g_CinematicSatelliteZoomFixEnabled = true;
        volatile long g_CinematicSatelliteZoomLogBudget = 8;

        // Mission briefing and mission archive callbacks use the unguarded
        // scrolling methods. Redirect just those four calls to the guarded
        // variants already used by the lobby/chat UI so the final partial page
        // is clamped instead of snapping back to the top.
        uint32_t g_BriefingScrollUpCallAddr = 0;

        uint32_t g_BriefingScrollDownCallAddr = 0;

        uint32_t g_ArchiveScrollUpCallAddr = 0;

        uint32_t g_ArchiveScrollDownCallAddr = 0;

        uint32_t g_GuardedScrollUpAddr = 0;

        uint32_t g_GuardedScrollDownAddr = 0;

        uint32_t g_UnguardedScrollUpAddr = 0;

        uint32_t g_UnguardedScrollDownAddr = 0;

        // renderCount allocation crash (#65). The MultiRenderClass constructor
        // (0x0044D7B0, selected by [Render] renderBase="draw_multi") reads the
        // ODF key "rendercount" (FNV-1a 0x8C8E76EC) into this+0x108, multiplies
        // it by 4 with overflow saturation to 0xFFFFFFFF, and passes the result
        // straight to operator new[]. A missing/nil/garbage count therefore
        // dies with "invalid allocation size". Clamp the stored count to
        // [0, kMultiRenderCountMax] between the ParameterDB read and the
        // allocation; the same field bounds the renderName%d copy loop, so the
        // single clamp protects both the allocation and the loop.
        uint32_t g_MultiRenderCountClampSiteAddr = 0;

        uint32_t g_MultiRenderCountClampResumeAddr = 0;

        constexpr size_t kMultiRenderCountClampDetourLen = 11;

        // Undecodable menu/mod thumbnail BMP crash. FUN_007D3FF0 is the shared
        // "build thumbnail material" helper used by every map/mod list screen:
        // it clones the stock "UI" material, applies the requested texture name
        // and synchronously loads it (virtual Material::load call at
        // 0x007D429C). FreeImage inside the shipped OgreMain.dll cannot decode
        // some user-supplied BMPs (observed live: BITMAPV5HEADER ->
        // "unknown bmp subtype with id 124") and Ogre::FreeImageCodec::decode
        // then throws InternalErrorException. No caller has a handler, so one
        // bad thumbnail terminates the whole process from a menu click.
        // Entry-detour 0x007D3FF0 (5 bytes over push ebp/mov ebp,esp/push -1)
        // and run the stock body under an SEH filter that converts only C++
        // exceptions (0xE06D7363) into the same outcome as a missing thumbnail:
        // a cleared out SharedPtr slot. AVs and other faults still crash loudly.
        // See reverse_engineering/bmp_thumbnail_crash_20260824.md.
        uint32_t g_ThumbnailMaterialApplySiteAddr = 0;

        constexpr size_t kThumbnailMaterialApplyDetourLen = 5;

        // Last-resort substitute name for the swallow path below: passing "UI"
        // makes the stock body take its material-already-exists branch, which
        // hands back the loaded base material without touching any texture.
        // It is only ever reached if the generated placeholder below could not
        // be produced -- "UI" is the stock chrome material, so an entry that
        // falls back to it shows button art in the thumbnail slot.
        static const char kUiMaterialSubstituteName[] = "UI";

		// Earthquake/dayquake save replay bug (#57). Quake ordnance (QuakeBlast,
		// the "dayquake"/quake-weapon effects) drives the global EarthQuake
		// object: Init starts it, Simulate decays it, Cleanup stops it.
		// Explosions are not persisted, so a save taken mid-quake stores
		// quakeMag != 0 and PostLoadScriptUtils (0x005C7A50) restarts the quake
		// with no owner left to stop it -- the shake plus the looping
		// gquak01.wav repeat forever. Keep the replay (script-started quakes
		// still rely on it) but arm a fade watchdog on the restarted quake:
		// EarthQuake::Simulate ramps the replayed scale to zero and calls
		// StopQuake unless a mission script takes ownership by writing the
		// scale itself first.
		uint32_t g_PostLoadQuakeRestartCallAddr = 0;

		uint32_t g_EarthQuakeStartQuakeAddr = 0;

		uint32_t g_EarthQuakeUpdateQuakeAddr = 0;

		uint32_t g_EarthQuakeStopQuakeAddr = 0;

		uint32_t g_EarthQuakeSimulateAddr = 0;

		uint32_t g_EarthQuakeObjectAddr = 0;

		constexpr size_t kEarthQuakeScaleOffset = 0x28;

		constexpr size_t kEarthQuakeSimulateDetourLen = 9;

		// Stale target camera in satellite/F9 view (#56/#78). The Ogre frame
		// driver (0x00682540) shows the target-camera picture-in-picture
		// viewport while the legacy TargetCam enabled flag (targetCam
		// 0x025F5FE0 + 0x1F1) reads true. That flag is recomputed by the
		// legacy per-frame updater (0x005DDE00), which stops running in the
		// satellite/editor overview -- so entering F9 while targeting leaves
		// the flag latched and the PiP frozen on screen. Retarget only the
		// frame driver's enabled-predicate call (0x00682679 -> 0x005DDDE0) to
		// a gate that also reports "disabled" while the view mode global
		// (0x008EAAD8) is satellite (3) or editor (9); the stock code then
		// removes the viewport itself and re-creates it on return to cockpit.
		// The gameplay target is never touched.
		uint32_t g_TargetCamEnabledCallAddr = 0;

		uint32_t g_TargetCamEnabledWrapperAddr = 0;

		uint32_t g_ViewModeAddr = 0;

		constexpr int32_t kGogViewModeSatellite = 3;

		constexpr int32_t kGogViewModeEditor = 9;

		// Cinematic camera zoomed in satellite mode (#58). Entering satellite
		// view (0x0061BD20) rebuilds the main camera record (0x00439E60) via
		// the camera-record builder (0x00688370) with a pi/2 FOV and the
		// overview zoom. The cinematic-camera begin (0x00821E30, view mode 5)
		// only reconfigures the window and reuses the record's current
		// zoom-dependent scale fields, so a cinematic triggered from satellite
		// inherits the overview zoom and renders incorrectly zoomed. Retarget
		// both begin call sites to a gate that first rebuilds the record with
		// the cockpit parameters (FOV bits at 0x0087256C, zoom 1.0 bits at
		// 0x008A2604) exactly like the cockpit view setter (0x0061BAB0) does.
		uint32_t g_CinematicCameraBeginAddr = 0;

		uint32_t g_CinematicBeginCallAddr1 = 0;

		uint32_t g_CinematicBeginCallAddr2 = 0;

		uint32_t g_GetCameraRecordAddr = 0;

		uint32_t g_BuildCameraRecordAddr = 0;

		uint32_t g_CockpitFovBitsAddr = 0;

		uint32_t g_CockpitZoomBitsAddr = 0;

		constexpr size_t kGogCameraRecordDwords = 0x76;

        static bool g_ThumbnailBmpGuardMismatchLogged = false;

        static volatile long g_ThumbnailBmpGuardLogBudget = 8;

        static uint32_t g_QuakeReplayInitialScaleBits = 0;

        static uint32_t g_QuakeReplayLastWrittenBits = 0;

        static ULONGLONG g_QuakeReplayArmTick = 0;

        // Each fix binds its own engine_addresses rows, all or nothing, the
        // first time it is asked to install; a fix whose rows do not bind on
        // this build stays off and the others are unaffected.
        template <size_t N>
        static bool BindUiCameraRows(const char* feature, const HookEngine::EngineRow (&rows)[N], int& state)
        {
            if (state == 0)
                state = HookEngine::BindEngineRows(feature, rows) ? 1 : -1;
            return state > 0;
        }

        void InstallBriefingScrollFixIfPossible()
        {
            if (!g_BriefingScrollFixEnabled || g_BriefingScrollFixInstalled)
                return;
            static int s_bound = 0;
            const HookEngine::EngineRow rows[] = {
                { "BriefingScrollUpCall", &g_BriefingScrollUpCallAddr },
                { "BriefingScrollDownCall", &g_BriefingScrollDownCallAddr },
                { "ArchiveScrollUpCall", &g_ArchiveScrollUpCallAddr },
                { "ArchiveScrollDownCall", &g_ArchiveScrollDownCallAddr },
                { "UiScrollUpGuarded", &g_GuardedScrollUpAddr },
                { "UiScrollDownGuarded", &g_GuardedScrollDownAddr },
                { "UiScrollUpUnguarded", &g_UnguardedScrollUpAddr },
                { "UiScrollDownUnguarded", &g_UnguardedScrollDownAddr },
            };
            if (!BindUiCameraRows("Briefing scroll fix", rows, s_bound))
                return;

            const bool briefingUp = RedirectCallTarget(
                g_BriefingScrollUpCallAddr,
                g_UnguardedScrollUpAddr,
                g_GuardedScrollUpAddr);
            const bool briefingDown = RedirectCallTarget(
                g_BriefingScrollDownCallAddr,
                g_UnguardedScrollDownAddr,
                g_GuardedScrollDownAddr);
            const bool archiveUp = RedirectCallTarget(
                g_ArchiveScrollUpCallAddr,
                g_UnguardedScrollUpAddr,
                g_GuardedScrollUpAddr);
            const bool archiveDown = RedirectCallTarget(
                g_ArchiveScrollDownCallAddr,
                g_UnguardedScrollDownAddr,
                g_GuardedScrollDownAddr);

            g_BriefingScrollFixInstalled =
                briefingUp && briefingDown && archiveUp && archiveDown;
            if (g_BriefingScrollFixInstalled)
            {
                Log(L"[BRIEFSCROLL] Redirected mission briefing/archive callbacks to guarded scroll handlers\n");
            }
        }

        // renderCount clamp (#65) helpers. The naked detour below runs between
        // the MultiRenderClass constructor's ParameterDB read of "rendercount"
        // and the operator new[] that consumes it.
        static void* g_MultiRenderCountClampResumePtr = nullptr;

        static int32_t __stdcall ClampMultiRenderCountValue(int32_t count)
        {
            const int32_t clamped =
                count < 0 ? 0 :
                (count > kMultiRenderCountMax ? kMultiRenderCountMax : count);
            if (InterlockedDecrement(&g_MultiRenderCountClampLogBudget) >= 0)
            {
                Log(L"[RENDERCOUNT] Clamped draw_multi renderCount %d -> %d (invalid allocation guard)\n",
                    count, clamped);
            }
            return clamped;
        }

#if defined(_M_IX86)
        static void __declspec(naked) MultiRenderCountClampHook()
        {
            __asm
            {
                // Stolen bytes from 0x0044D858:
                //   33 C9              xor ecx, ecx
                //   8B 55 AC           mov edx, [ebp-0x54]
                //   8B 82 08 01 00 00  mov eax, [edx+0x108]
                xor  ecx, ecx
                mov  edx, [ebp - 0x54]
                mov  eax, [edx + 0x108]
                cmp  eax, 0
                jl   clampNeeded
                cmp  eax, 256              // kMultiRenderCountMax
                jle  clampDone
            clampNeeded:
                pushad
                push eax
                call ClampMultiRenderCountValue
                mov  [esp + 28], eax       // replace saved eax in the pushad frame
                popad
                mov  [edx + 0x108], eax    // store the clamped count for the copy loop
            clampDone:
                // Resume expects ecx == 0 (feeds the stock seto/neg overflow
                // saturation) and eax == count.
                xor  ecx, ecx
                jmp  [g_MultiRenderCountClampResumePtr]
            }
        }
#endif

        void InstallMultiRenderCountClampIfPossible()
        {
            if (!g_MultiRenderCountClampEnabled || g_MultiRenderCountClampInstalled)
                return;
            static int s_bound = 0;
            const HookEngine::EngineRow rows[] = {
                { "MultiRenderCountClampSite", &g_MultiRenderCountClampSiteAddr },
            };
            if (!BindUiCameraRows("renderCount clamp", rows, s_bound))
                return;
            // The row's guard is exactly the 11 displaced bytes; resume after them.
            g_MultiRenderCountClampResumeAddr = g_MultiRenderCountClampSiteAddr + kMultiRenderCountClampDetourLen;
            g_MultiRenderCountClampResumePtr = reinterpret_cast<void*>(g_MultiRenderCountClampResumeAddr);

#if !defined(_M_IX86)
            return;
#else
            // xor ecx,ecx / mov edx,[ebp-0x54] / mov eax,[edx+0x108] directly
            // after the ParameterDB::Get call for hash 0x8C8E76EC.
            static const uint8_t kExpectedClampSiteBytes[kMultiRenderCountClampDetourLen] =
            {
                0x33, 0xC9, 0x8B, 0x55, 0xAC, 0x8B, 0x82, 0x08, 0x01, 0x00, 0x00
            };

            if (!ExpectedBytesMatchAt(g_MultiRenderCountClampSiteAddr,
                                      kExpectedClampSiteBytes,
                                      sizeof(kExpectedClampSiteBytes)))
            {
                return;
            }

            uint8_t patch[kMultiRenderCountClampDetourLen] =
            {
                0xE9, 0x00, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90
            };
            const int32_t relative =
                static_cast<int32_t>(reinterpret_cast<uintptr_t>(MultiRenderCountClampHook)) -
                static_cast<int32_t>(g_MultiRenderCountClampSiteAddr + 5);
            std::memcpy(patch + 1, &relative, sizeof(relative));

            if (!WritePatchBytes(g_MultiRenderCountClampSiteAddr, patch, sizeof(patch)))
            {
                Log(L"[RENDERCOUNT] Failed installing draw_multi renderCount clamp at 0x%08X\n",
                    static_cast<uint32_t>(g_MultiRenderCountClampSiteAddr));
                return;
            }

            g_MultiRenderCountClampInstalled = true;
            Log(L"[RENDERCOUNT] Installed draw_multi renderCount clamp site=0x%08X resume=0x%08X max=%d\n",
                static_cast<uint32_t>(g_MultiRenderCountClampSiteAddr),
                static_cast<uint32_t>(g_MultiRenderCountClampResumeAddr),
                kMultiRenderCountMax);
#endif
        }

        // Undecodable thumbnail guard helpers. The stock helper receives a
        // caller-provided 8-byte SharedPtr<Material> slot as its first stack
        // argument and returns that same pointer (mov eax, [ebp+8] in the
        // epilogue). On a swallowed decode failure we clear the slot to a null
        // SharedPtr - the exact value Ogre's SharedPtr::operator= treats as
        // "no material" without dereferencing - and hand the slot back.
        using FnThumbnailMaterialApply =
            void* (__thiscall*)(void* self, void* outMaterialSlot, const void* nameArg);

        static FnThumbnailMaterialApply g_BzrFn_ThumbnailMaterialApplyOriginal = nullptr;

        // Only Microsoft C++ exceptions are converted. Access violations and
        // every other fault keep their default behaviour so real memory
        // corruption stays visible.
        static long ThumbnailBmpGuardFilter(unsigned long exceptionCode)
        {
            if (!g_ThumbnailBmpGuardEnabled)
                return EXCEPTION_CONTINUE_SEARCH;
            return exceptionCode == 0xE06D7363UL ? EXCEPTION_EXECUTE_HANDLER
                                                 : EXCEPTION_CONTINUE_SEARCH;
        }

        // Best-effort removal of the half-created clone an aborted stock
        // attempt leaves registered under the real thumbnail/material name:
        // the stock body registers the cloned material before Material::load
        // throws, so after a swallow the manager map still owns an unloaded
        // material whose texture unit names the undecodable image.
        //
        // Leaving it registered makes every later selection take the stock
        // exists-branch, which hands back that half-loaded material without
        // loading it - consumers see an untextured entry instead of the UI
        // substitute, and any unrelated future load() of that material would
        // rethrow the same decode failure outside this guard. Removing the
        // entry forces later selections back through the fully guarded build
        // path, which deterministically substitutes "UI" again.
        //
        // Uses the same exported ResourceManager::remove(MaterialManager
        // singleton) pair proven live by the material collision listener in
        // trampolines.cpp. Ogre's remove(const String&) is a no-op for absent
        // names and merely detaches the manager reference, so live SharedPtrs
        // stay valid. Failures here are non-fatal by construction; non-C++
        // faults are deliberately not caught (corruption stays loud).
        static void RemoveHalfCreatedThumbnailMaterial(const char* name)
        {
            using FnMaterialManagerGetSingletonPtr = void* (__cdecl*)();
            using FnResourceManagerRemoveByName =
                void (__thiscall*)(void*, const std::string&);

            // Never touch the substitute target itself: if the base "UI"
            // material were ever removed the fallback would lose its source.
            if (!name || !*name ||
                std::strcmp(name, kUiMaterialSubstituteName) == 0)
            {
                return;
            }

            const auto getMaterialManager =
                ResolveOgreProc<FnMaterialManagerGetSingletonPtr>(
                    "?getSingletonPtr@MaterialManager@Ogre@@SAPAV12@XZ");
            const auto removeByName =
                ResolveOgreProc<FnResourceManagerRemoveByName>(
                    "?remove@ResourceManager@Ogre@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            if (!getMaterialManager || !removeByName)
                return;

            void* manager = getMaterialManager();
            if (!manager)
                return;

            try
            {
                removeByName(manager, std::string(name));
            }
            catch (...)
            {
                // A failed cleanup only costs one extra guarded decode on the
                // next selection; it must not turn recovery into a crash.
            }
        }

        // Writes the "preview unavailable" plate into the generated-UI resource
        // location on first use and returns its bare texture name, or nullptr
        // if it could not be produced. Defined further down, beside the other
        // GDI+/Ogre resource-location helpers it depends on.

        // Fill the caller's SharedPtr<Material> slot by re-running the guarded
        // body under a substitute name. Some callers - notably the campaign
        // preview builder FUN_007D2B70 - dereference the material without a
        // null check, so a cleared slot is not survivable everywhere.
        //
        // Two names are used, in order: the generated placeholder texture, and
        // failing that "UI", whose exists-branch returns the loaded base
        // material without touching any texture and cannot throw.
        //
        // The handler is deliberately the same narrow C++-exception-only
        // filter as the outer guard. For "UI" the stock body takes its
        // exists-branch, so any exception there means something genuinely
        // unexpected; for the placeholder a throw is expected-ish (the file or
        // the resource location may not be reachable yet) and is what makes
        // the caller fall through to "UI". An access violation or other
        // hardware fault inside the retry propagates out of this function (and
        // out of the enclosing __except handler, which cannot re-catch it) and
        // crashes loudly instead of being silently converted into a fallback.
        static bool ThumbnailGuardRetryWithName(void* self,
                                                void* outMaterialSlot,
                                                const char* substituteName)
        {
            if (!outMaterialSlot || !substituteName || !*substituteName ||
                !g_BzrFn_ThumbnailMaterialApplyOriginal)
            {
                return false;
            }

            bool recovered = false;
            __try
            {
                g_BzrFn_ThumbnailMaterialApplyOriginal(
                    self, outMaterialSlot, substituteName);
                recovered = true;
            }
            __except (ThumbnailBmpGuardFilter(GetExceptionCode()))
            {
                recovered = false;
            }
            return recovered;
        }

        static void* __cdecl ThumbnailMaterialGuardCall(void* self,
                                                        void* outMaterialSlot,
                                                        const void* nameArg)
        {
            if (!g_BzrFn_ThumbnailMaterialApplyOriginal || !outMaterialSlot)
                return outMaterialSlot;

            void* result = nullptr;
            __try
            {
                result = g_BzrFn_ThumbnailMaterialApplyOriginal(
                    self, outMaterialSlot, nameArg);
            }
            __except (ThumbnailBmpGuardFilter(GetExceptionCode()))
            {
                // The stock body threw while decoding/loading the thumbnail
                // image. Re-run it under a substitute name so every consumer -
                // including ones that never null-check, like the campaign
                // preview builder - receives a valid loaded material.
                //
                // The generated placeholder is tried first: it says "preview
                // unavailable" in the slot, which is what the entry actually
                // means. "UI" remains the fall-through, but it is the stock
                // chrome material and can read as a stray corner button, so it
                // is a fail-safe rather than the intended look.
                const char* placeholder = EnsureInvalidThumbnailTextureName();
                const char* substituteUsed = nullptr;
                bool substituted = false;
                if (placeholder)
                {
                    substituted = ThumbnailGuardRetryWithName(
                        self, outMaterialSlot, placeholder);
                    if (substituted)
                        substituteUsed = placeholder;
                    else
                    {
                        // A failed placeholder attempt leaves its own
                        // half-created clone registered, exactly as the
                        // original attempt did; drop it so the next failure
                        // retries cleanly instead of inheriting it.
                        RemoveHalfCreatedThumbnailMaterial(placeholder);
                    }
                }
                if (!substituted)
                {
                    substituted = ThumbnailGuardRetryWithName(
                        self, outMaterialSlot, kUiMaterialSubstituteName);
                    if (substituted)
                        substituteUsed = kUiMaterialSubstituteName;
                }
                if (!substituted)
                {
                    // Deliberately unguarded: the slot was already validated
                    // non-null above and is caller-provided storage, so these
                    // two plain stores cannot fault on their own. If one ever
                    // did, that is real memory corruption and must crash
                    // loudly rather than be swallowed here.
                    void** slot = reinterpret_cast<void**>(outMaterialSlot);
                    slot[0] = nullptr; // SharedPtr representation
                    slot[1] = nullptr; // use-count pointer
                }

                // Drop the half-created clone the aborted stock attempt left
                // registered under the real name so repeat selections re-run
                // the guarded path (and get the same UI substitution) instead
                // of silently receiving the half-loaded leftover from the
                // stock exists-branch. See
                // RemoveHalfCreatedThumbnailMaterial for the full rationale.
                RemoveHalfCreatedThumbnailMaterial(
                    static_cast<const char*>(nameArg));

                const long remaining = InterlockedDecrement(&g_ThumbnailBmpGuardLogBudget);
                if (remaining >= 0)
                {
                    Log(L"[BMPFIX] Rejected undecodable thumbnail image; substitute=%hs (self=0x%08X name-arg=0x%08X remaining=%ld)\n",
                        substituteUsed ? substituteUsed
                                       : "none, material cleared to blank",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(self)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(nameArg)),
                        remaining);
                }
                result = outMaterialSlot;
            }
            return result;
        }

#if defined(_M_IX86)
        static void __declspec(naked) ThumbnailMaterialGuardEntry()
        {
            __asm
            {
                // Stock prologue at 0x007D3FF0 is __thiscall with two stack
                // arguments: [esp+4] = caller SharedPtr<Material> slot,
                // [esp+8] = texture/material name argument. ecx = this.
                push dword ptr [esp + 8]   // nameArg
                push dword ptr [esp + 8]   // outMaterialSlot
                push ecx                   // this
                call ThumbnailMaterialGuardCall
                add esp, 12
                retn 8           // stock callee pops both stack arguments
            }
        }
#endif

        void InstallThumbnailBmpGuardIfPossible()
        {
            if (!g_ThumbnailBmpGuardEnabled || g_ThumbnailBmpGuardInstalled)
                return;
            static int s_bound = 0;
            const HookEngine::EngineRow rows[] = {
                { "ThumbnailMaterialApply", &g_ThumbnailMaterialApplySiteAddr },
            };
            if (!BindUiCameraRows("Thumbnail BMP guard", rows, s_bound))
                return;

#if !defined(_M_IX86)
            return;
#else
            static const uint8_t kExpectedThumbApplyBytes[kThumbnailMaterialApplyDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x6A, 0xFF // push ebp; mov ebp,esp; push -1
            };

            static InlineDetour32 g_ThumbnailBmpGuardDetour = {};
            if (!InstallInlineDetour32(g_ThumbnailBmpGuardDetour,
                                       g_ThumbnailMaterialApplySiteAddr,
                                       &ThumbnailMaterialGuardEntry,
                                       kThumbnailMaterialApplyDetourLen,
                                       kExpectedThumbApplyBytes,
                                       sizeof(kExpectedThumbApplyBytes)))
            {
                if (!g_ThumbnailBmpGuardMismatchLogged)
                {
                    g_ThumbnailBmpGuardMismatchLogged = true;
                    Log(L"[BMPFIX] Thumbnail guard not installed: byte validation failed at 0x%08X\n",
                        static_cast<uint32_t>(g_ThumbnailMaterialApplySiteAddr));
                }
                return;
            }

            g_BzrFn_ThumbnailMaterialApplyOriginal =
                reinterpret_cast<FnThumbnailMaterialApply>(g_ThumbnailBmpGuardDetour.trampoline);

            g_ThumbnailBmpGuardInstalled = true;
            Log(L"[BMPFIX] Installed thumbnail decode guard site=0x%08X trampoline=0x%08X\n",
                static_cast<uint32_t>(g_ThumbnailMaterialApplySiteAddr),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_ThumbnailBmpGuardDetour.trampoline)));
#endif
        }

        using FnEarthQuakeStartQuake = void(__fastcall*)(void* thisPtr, void* edx, float scale);
        using FnEarthQuakeUpdateQuake = void(__fastcall*)(void* thisPtr, void* edx, float scale);
        using FnEarthQuakeStopQuake = void(__fastcall*)(void* thisPtr, void* edx);
        FnEarthQuakeSimulate g_BzrFn_EarthQuakeSimulateOriginal = nullptr;

        static void ArmQuakeReplayWatchdog(float scale)
        {
            if (!g_QuakeReplayFadeEnabled || !(scale > 0.0f))
            {
                InterlockedExchange(&g_QuakeReplayArmed, 0);
                return;
            }

            std::memcpy(&g_QuakeReplayInitialScaleBits, &scale, sizeof(scale));
            g_QuakeReplayLastWrittenBits = g_QuakeReplayInitialScaleBits;
            g_QuakeReplayArmTick = GetTickCount64();
            InterlockedExchange(&g_QuakeReplayArmed, 1);
            Log(L"[QUAKEFADE] Armed post-load quake fade scale=%.3f fadeSeconds=%ld\n",
                static_cast<double>(scale), g_QuakeReplayFadeSeconds);
        }

        static void __fastcall PostLoadQuakeRestartArmHook(void* thisPtr, void* /*edx*/, float scale)
        {
            ArmQuakeReplayWatchdog(scale);
            reinterpret_cast<FnEarthQuakeStartQuake>(g_EarthQuakeStartQuakeAddr)(
                thisPtr, nullptr, scale);
        }

        static void QuakeReplayFadeTick(void* quakePtr)
        {
            if (!g_QuakeReplayArmed ||
                reinterpret_cast<uintptr_t>(quakePtr) != g_EarthQuakeObjectAddr)
                return;

            __try
            {
                auto* scalePtr = reinterpret_cast<const float*>(
                    g_EarthQuakeObjectAddr + kEarthQuakeScaleOffset);
                uint32_t currentBits = 0;
                std::memcpy(&currentBits, scalePtr, sizeof(currentBits));
                if (currentBits != g_QuakeReplayLastWrittenBits)
                {
                    // A mission script (or a live QuakeBlast) wrote the scale:
                    // that owner is responsible for stopping the quake.
                    InterlockedExchange(&g_QuakeReplayArmed, 0);
                    Log(L"[QUAKEFADE] Released quake fade: script took ownership of quake scale\n");
                    return;
                }

                float current = 0.0f;
                std::memcpy(&current, &currentBits, sizeof(current));
                if (!(current > 0.0f))
                {
                    InterlockedExchange(&g_QuakeReplayArmed, 0);
                    return;
                }

                float initial = 0.0f;
                std::memcpy(&initial, &g_QuakeReplayInitialScaleBits, sizeof(initial));
                const float elapsedSeconds = static_cast<float>(
                    static_cast<double>(GetTickCount64() - g_QuakeReplayArmTick) / 1000.0);
                const float target =
                    initial * (1.0f - elapsedSeconds / static_cast<float>(g_QuakeReplayFadeSeconds));

                if (target <= 0.01f)
                {
                    reinterpret_cast<FnEarthQuakeStopQuake>(g_EarthQuakeStopQuakeAddr)(
                        quakePtr, nullptr);
                    InterlockedExchange(&g_QuakeReplayArmed, 0);
                    Log(L"[QUAKEFADE] Stopped replayed quake after %lds fade\n",
                        g_QuakeReplayFadeSeconds);
                    return;
                }

                if (target < current)
                {
                    // UpdateQuake also re-scales the looping gquak01.wav.
                    reinterpret_cast<FnEarthQuakeUpdateQuake>(g_EarthQuakeUpdateQuakeAddr)(
                        quakePtr, nullptr, target);
                    std::memcpy(&g_QuakeReplayLastWrittenBits, &target, sizeof(target));
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                InterlockedExchange(&g_QuakeReplayArmed, 0);
                Log(L"[QUAKEFADE] Quake fade tick raised an exception; watchdog disarmed\n");
            }
        }

        static void __fastcall EarthQuakeSimulateReplayFadeHook(void* thisPtr, void* edx, float dt)
        {
            QuakeReplayFadeTick(thisPtr);
            if (g_BzrFn_EarthQuakeSimulateOriginal)
                g_BzrFn_EarthQuakeSimulateOriginal(thisPtr, edx, dt);
        }

        void InstallQuakeReplayFadeIfPossible()
        {
            if (!g_QuakeReplayFadeEnabled || g_QuakeReplayFadeInstalled)
                return;

            // The PostLoadQuakeRestart row is `mov ecx, offset earthQuake`
            // followed by the PostLoadScriptUtils StartQuake call we redirect;
            // the EarthQuake object is that mov's operand. The row is bound
            // once, before the call is rewritten, so it stays valid across
            // retries.
            static int s_bound = 0;
            uint32_t restartSetup = 0;
            const HookEngine::EngineRow rows[] = {
                { "PostLoadQuakeRestart", &restartSetup },
                { "EarthQuakeStartQuake", &g_EarthQuakeStartQuakeAddr },
                { "EarthQuakeUpdateQuake", &g_EarthQuakeUpdateQuakeAddr },
                { "EarthQuakeStopQuake", &g_EarthQuakeStopQuakeAddr },
                { "EarthQuakeSimulate", &g_EarthQuakeSimulateAddr },
            };
            static uint32_t s_restartSetup = 0;
            if (s_bound == 0)
            {
                if (!BindUiCameraRows("Quake replay fade", rows, s_bound))
                    return;
                s_restartSetup = restartSetup;
            }
            if (s_bound < 0)
                return;
            const auto* setup = reinterpret_cast<const uint8_t*>(s_restartSetup);
            if (setup[0] != 0xB9 || setup[5] != 0xE8)
                return;
            g_EarthQuakeObjectAddr = *reinterpret_cast<const uint32_t*>(setup + 1);
            g_PostLoadQuakeRestartCallAddr = s_restartSetup + 5;

            // push ebp / mov ebp, esp / sub esp, 0x90 at EarthQuake::Simulate.
            static const uint8_t kExpectedSimulateEntry[kEarthQuakeSimulateDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x81, 0xEC, 0x90, 0x00, 0x00, 0x00
            };
            if (!InstallInlineDetour32(g_EarthQuakeSimulateDetour,
                                       g_EarthQuakeSimulateAddr,
                                       reinterpret_cast<void*>(EarthQuakeSimulateReplayFadeHook),
                                       kEarthQuakeSimulateDetourLen,
                                       kExpectedSimulateEntry,
                                       sizeof(kExpectedSimulateEntry)))
            {
                return;
            }
            g_BzrFn_EarthQuakeSimulateOriginal =
                reinterpret_cast<FnEarthQuakeSimulate>(g_EarthQuakeSimulateDetour.trampoline);

            if (!RedirectCallTarget(g_PostLoadQuakeRestartCallAddr,
                                    g_EarthQuakeStartQuakeAddr,
                                    reinterpret_cast<uintptr_t>(PostLoadQuakeRestartArmHook)))
            {
                Log(L"[QUAKEFADE] Failed redirecting post-load quake restart call at 0x%08X\n",
                    static_cast<uint32_t>(g_PostLoadQuakeRestartCallAddr));
                return;
            }

            g_QuakeReplayFadeInstalled = true;
            Log(L"[QUAKEFADE] Installed post-load quake fade restartCall=0x%08X simulate=0x%08X fadeSeconds=%ld\n",
                static_cast<uint32_t>(g_PostLoadQuakeRestartCallAddr),
                static_cast<uint32_t>(g_EarthQuakeSimulateAddr),
                g_QuakeReplayFadeSeconds);
        }

        // Stale target camera fix (#56/#78) helpers.
        using FnTargetCamEnabled = uint8_t(__cdecl*)();

        static uint8_t __cdecl TargetCamEnabledOverviewGateHook()
        {
            const uint8_t enabled =
                reinterpret_cast<FnTargetCamEnabled>(g_TargetCamEnabledWrapperAddr)();
            if (!enabled)
                return 0;

            const int32_t viewMode =
                *reinterpret_cast<const volatile int32_t*>(g_ViewModeAddr);
            if (viewMode != kGogViewModeSatellite && viewMode != kGogViewModeEditor)
                return enabled;

            if (InterlockedDecrement(&g_TargetCamSatelliteLogBudget) >= 0)
            {
                Log(L"[TARGETCAM] Suppressed stale target camera overlay in overview viewMode=%d\n",
                    viewMode);
            }
            return 0;
        }

        void InstallTargetCamSatelliteFixIfPossible()
        {
            if (!g_TargetCamSatelliteFixEnabled || g_TargetCamSatelliteFixInstalled)
                return;
            static int s_bound = 0;
            const HookEngine::EngineRow rows[] = {
                { "TargetCamEnabledCall", &g_TargetCamEnabledCallAddr },
                { "TargetCamEnabledWrapper", &g_TargetCamEnabledWrapperAddr },
            };
            if (!BindUiCameraRows("Target camera satellite fix", rows, s_bound))
                return;
            // Current_View is +8 in the ViewRecord row.
            if (ViewRecordAddr() == 0)
                return;
            g_ViewModeAddr = static_cast<uint32_t>(ViewRecordAddr() + 8);

            // movzx ecx, al / test ecx, ecx directly after the enabled-predicate
            // call in the Ogre frame driver.
            static const uint8_t kExpectedAfterEnabledCall[5] =
            {
                0x0F, 0xB6, 0xC8, 0x85, 0xC9
            };
            if (!ExpectedBytesMatchAt(g_TargetCamEnabledCallAddr + 5,
                                      kExpectedAfterEnabledCall,
                                      sizeof(kExpectedAfterEnabledCall)))
            {
                return;
            }

            if (!RedirectCallTarget(g_TargetCamEnabledCallAddr,
                                    g_TargetCamEnabledWrapperAddr,
                                    reinterpret_cast<uintptr_t>(TargetCamEnabledOverviewGateHook)))
            {
                Log(L"[TARGETCAM] Failed redirecting target camera predicate call at 0x%08X\n",
                    static_cast<uint32_t>(g_TargetCamEnabledCallAddr));
                return;
            }

            g_TargetCamSatelliteFixInstalled = true;
            Log(L"[TARGETCAM] Installed satellite/F9 stale target camera fix call=0x%08X viewMode=0x%08X\n",
                static_cast<uint32_t>(g_TargetCamEnabledCallAddr),
                static_cast<uint32_t>(g_ViewModeAddr));
        }

        // Cinematic camera satellite zoom fix (#58) helpers.
        using FnCinematicCameraBegin = void(__cdecl*)();
        using FnGetCameraRecord = void*(__cdecl*)();
        using FnBuildCameraRecord = void*(__cdecl*)(void* outBuf,
                                                    void* viewport,
                                                    uint32_t fovBits,
                                                    uint32_t paneBits,
                                                    uint32_t farBits,
                                                    uint32_t zoomBits);

        static void RestoreCockpitCameraRecordForCinematic(int32_t viewMode)
        {
            __try
            {
                auto* record = static_cast<uint8_t*>(
                    reinterpret_cast<FnGetCameraRecord>(g_GetCameraRecordAddr)());
                if (!record)
                    return;

                // Mirror of the cockpit view setter's record rebuild: keep the
                // record's viewport/pane/far values, swap in cockpit FOV and
                // zoom 1.0 so the cinematic does not inherit the overview zoom.
                static uint8_t rebuildBuffer[1024];
                void* rebuilt = reinterpret_cast<FnBuildCameraRecord>(g_BuildCameraRecordAddr)(
                    rebuildBuffer,
                    *reinterpret_cast<void**>(record + 0x38),
                    *reinterpret_cast<const uint32_t*>(g_CockpitFovBitsAddr),
                    *reinterpret_cast<const uint32_t*>(record + 0x2C),
                    *reinterpret_cast<const uint32_t*>(record + 0x10),
                    *reinterpret_cast<const uint32_t*>(g_CockpitZoomBitsAddr));
                if (rebuilt)
                    memcpy(record, rebuilt, kGogCameraRecordDwords * 4);

                if (InterlockedDecrement(&g_CinematicSatelliteZoomLogBudget) >= 0)
                {
                    Log(L"[CINECAM] Rebuilt camera record with cockpit FOV/zoom before cinematic (viewMode=%d)\n",
                        viewMode);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[CINECAM] Camera record rebuild raised an exception; using stock cinematic path\n");
            }
        }

        static void __cdecl CinematicCameraBeginZoomFixHook()
        {
            const int32_t viewMode =
                *reinterpret_cast<const volatile int32_t*>(g_ViewModeAddr);
            if (g_CinematicSatelliteZoomFixEnabled &&
                (viewMode == kGogViewModeSatellite || viewMode == kGogViewModeEditor))
            {
                RestoreCockpitCameraRecordForCinematic(viewMode);
            }
            reinterpret_cast<FnCinematicCameraBegin>(g_CinematicCameraBeginAddr)();
        }

        void InstallCinematicSatelliteZoomFixIfPossible()
        {
            if (!g_CinematicSatelliteZoomFixEnabled || g_CinematicSatelliteZoomFixInstalled)
                return;
            static int s_bound = 0;
            const HookEngine::EngineRow rows[] = {
                { "CinematicCameraBegin", &g_CinematicCameraBeginAddr },
                { "CinematicBeginCallMission", &g_CinematicBeginCallAddr1 },
                { "CinematicBeginCallScript", &g_CinematicBeginCallAddr2 },
                { "GetCameraRecord", &g_GetCameraRecordAddr },
                { "BuildCameraRecord", &g_BuildCameraRecordAddr },
                { "CockpitFovBits", &g_CockpitFovBitsAddr },
                { "CockpitZoomBits", &g_CockpitZoomBitsAddr },
            };
            if (!BindUiCameraRows("Cinematic satellite zoom fix", rows, s_bound))
                return;
            if (ViewRecordAddr() == 0)
                return;
            g_ViewModeAddr = static_cast<uint32_t>(ViewRecordAddr() + 8);

            // push ebp / mov ebp, esp / push ecx at the cinematic begin entry.
            static const uint8_t kExpectedCinematicBeginEntry[4] =
            {
                0x55, 0x8B, 0xEC, 0x51
            };
            if (!ExpectedBytesMatchAt(g_CinematicCameraBeginAddr,
                                      kExpectedCinematicBeginEntry,
                                      sizeof(kExpectedCinematicBeginEntry)))
            {
                return;
            }

            const bool missionCall = RedirectCallTarget(
                g_CinematicBeginCallAddr1,
                g_CinematicCameraBeginAddr,
                reinterpret_cast<uintptr_t>(CinematicCameraBeginZoomFixHook));
            const bool scriptCall = RedirectCallTarget(
                g_CinematicBeginCallAddr2,
                g_CinematicCameraBeginAddr,
                reinterpret_cast<uintptr_t>(CinematicCameraBeginZoomFixHook));

            g_CinematicSatelliteZoomFixInstalled = missionCall && scriptCall;
            if (g_CinematicSatelliteZoomFixInstalled)
            {
                Log(L"[CINECAM] Installed cinematic-from-satellite zoom fix calls=0x%08X,0x%08X begin=0x%08X\n",
                    static_cast<uint32_t>(g_CinematicBeginCallAddr1),
                    static_cast<uint32_t>(g_CinematicBeginCallAddr2),
                    static_cast<uint32_t>(g_CinematicCameraBeginAddr));
            }
            else
            {
                Log(L"[CINECAM] Cinematic zoom fix call redirect incomplete mission=%hs script=%hs\n",
                    missionCall ? "ok" : "failed",
                    scriptCall ? "ok" : "failed");
            }
        }
    }

}
