// ogre_runtime_helpers.cpp
// BZR Open Shim - OgreMain runtime helpers: the cached by-name export
// resolver, the OgreMain image range and the "is this an Ogre object"
// vtable check, split out of bzr_hooks.cpp.
#include "bzr_hooks.h"
#include "env_switch_table.h"
#include "bool_token.h"
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
#include "memory_access.h"
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
        // Resolves one decorated export from the shipped OgreMain.dll, caching
        // both outcomes.
        //
        // Caching the *failure* is the point. A caller written as
        // `if (!fn) fn = ResolveOgreProc<T>("...")` retries forever when the
        // name is wrong, because the field it guards on can never be filled.
        // That is not hypothetical: one mis-decorated name in
        // GetHeadlightOgreApi -- `Q` where Ogre::MovableObject::getCastShadows
        // is virtual, so `U` -- turned into a GetProcAddress per emission light
        // per frame and measured 45% of the main thread's CPU in an 80-craft
        // battle. The call sites have been repaired, but the resolver is the
        // place where a *future* typo stops being able to recreate that.
        //
        // A miss is only cached once OgreMain is actually loaded; a lookup made
        // before the module exists is a timing answer, not an answer about the
        // name, and must not be recorded as one.
        void* ResolveOgreProcRaw(const char* name)
        {
            if (!name || !*name)
                return nullptr;

            static std::mutex cacheMutex;
            static std::unordered_map<std::string, void*> cache;

            const HMODULE ogreMain = GetModuleHandleA("OgreMain.dll");
            if (!ogreMain)
                return nullptr;

            std::lock_guard<std::mutex> lock(cacheMutex);
            const auto existing = cache.find(name);
            if (existing != cache.end())
                return existing->second;

            void* const resolved =
                reinterpret_cast<void*>(GetProcAddress(ogreMain, name));
            cache.emplace(name, resolved);
            if (!resolved)
            {
                // One warning per distinct name, for the lifetime of the
                // process. A null Ogre entry point degrades a feature silently,
                // which is exactly how the getCastShadows typo survived.
                Log(L"[OGRE-EXPORTS] WARNING: OgreMain.dll has no export '%hs'. "
                    L"The feature using it will be degraded; the lookup will not "
                    L"be retried.\n",
                    name);
            }
            return resolved;
        }

        // The render-bridge offsets do not hold a bridge on every object that
        // reaches the fragment hooks, and what comes back instead is not even
        // pointer-shaped: observed values include 0x3F3F3F3F ("????") and
        // 0x003D003C (UTF-16 "<="), i.e. the read landed inside a string. Handing
        // those to a __thiscall Ogre method is a virtual dispatch through text --
        // that is the OgreMain write fault at 0x3F3F3F6C in the crash log. Every
        // Ogre object begins with a vtable pointer into OgreMain.dll, so require
        // that before making any call on a candidate.

        bool TryGetOgreModuleRange(uintptr_t& outBase, uintptr_t& outEnd)
        {
            static uintptr_t s_base = 0;
            static uintptr_t s_end = 0;
            static bool s_attempted = false;

            if (!s_attempted)
            {
                // Image size straight off the PE headers, so this needs no psapi.
                // Only a mapped module settles it: asking before OgreMain loads
                // is timing, not an answer, and used to latch "not Ogre" for
                // the life of the process.
                if (const HMODULE ogreMain = GetModuleHandleA("OgreMain.dll"))
                {
                    s_attempted = true;
                    __try
                    {
                        const auto* moduleBytes = reinterpret_cast<const uint8_t*>(ogreMain);
                        const auto* dosHeader = reinterpret_cast<const IMAGE_DOS_HEADER*>(moduleBytes);
                        if (dosHeader->e_magic == IMAGE_DOS_SIGNATURE)
                        {
                            const auto* ntHeaders =
                                reinterpret_cast<const IMAGE_NT_HEADERS*>(moduleBytes + dosHeader->e_lfanew);
                            if (ntHeaders->Signature == IMAGE_NT_SIGNATURE &&
                                ntHeaders->OptionalHeader.SizeOfImage > 0)
                            {
                                s_base = reinterpret_cast<uintptr_t>(moduleBytes);
                                s_end = s_base + ntHeaders->OptionalHeader.SizeOfImage;
                            }
                        }
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                        s_base = 0;
                        s_end = 0;
                    }
                }
            }

            outBase = s_base;
            outEnd = s_end;
            return s_base != 0 && s_end > s_base;
        }

        bool LooksLikeOgreObject(const void* candidate)
        {
            const uintptr_t address = reinterpret_cast<uintptr_t>(candidate);
            // Cheap shape rejects first: null, misaligned, or in the bottom 64K.
            if (address < 0x00010000 || (address % sizeof(void*)) != 0)
                return false;

            uintptr_t ogreBase = 0;
            uintptr_t ogreEnd = 0;
            if (!TryGetOgreModuleRange(ogreBase, ogreEnd))
                return false;

            MEMORY_BASIC_INFORMATION mbi = {};
            if (VirtualQuery(candidate, &mbi, sizeof(mbi)) != sizeof(mbi))
                return false;
            if (mbi.State != MEM_COMMIT || !BZROpenShim::MemoryAccess::ProtectionAllows(mbi.Protect, BZROpenShim::MemoryAccess::Access::Read))
                return false;

            uintptr_t vtable = 0;
            __try
            {
                vtable = *reinterpret_cast<const uintptr_t*>(candidate);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }

            return vtable >= ogreBase && vtable < ogreEnd;
        }
    }

}
