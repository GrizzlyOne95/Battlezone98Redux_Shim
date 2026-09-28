// game_object_helpers.cpp
// BZR Open Shim - shared GameObject helpers: the GOG handle -> object
// lookup and the hardened GameObjectHandle::GetObj replacement, the
// GameObject field-base, team, handle and RTTI readers, obj76 and world
// position accessors, arena enumeration, the local player's net id and
// world position, and the terrain line-of-sight query, split out of
// bzr_hooks.cpp.
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
        static_assert(
            kGameObjectDistributedObjectOffset == kGameObjectClassSubObjOffset,
            "GameObject +0x18 interface aliases diverged");

        constexpr size_t kObj76GameObjectOffset = 0x8C;
        static_assert(kGameObjectObjOffset == ObjectLayout::kGameObjectObj76,
                      "obj76 offset disagrees with bzr_object_layout.h");
        static_assert(kObj76GameObjectOffset == ObjectLayout::kObj76GameObject,
                      "obj76 back-pointer disagrees with bzr_object_layout.h");

        // Ties the offsets this file shares with bzr_object_layout.h, whose
        // host test pins them to the disassembly evidence. Editing either side
        // alone is a build break rather than a silent behaviour change.
        static_assert(kGameObjectActualTeamOffset ==
                          ObjectLayout::kGameObjectActualTeam,
                      "actual team offset disagrees with bzr_object_layout.h");
        static_assert(kGameObjectPerceivedTeamOffset ==
                          ObjectLayout::kGameObjectPerceivedTeam,
                      "perceived team offset disagrees with bzr_object_layout.h");
        static_assert(kGameObjectOwnerHandleOffset ==
                          ObjectLayout::kGameObjectOwnerHandle,
                      "owner handle offset disagrees with bzr_object_layout.h");
        static_assert(kGameObjectOwnerHandleOffset !=
                          ObjectLayout::kGameObjectHitch,
                      "owner handle must not alias the hitch field");

        static_assert(kGameObjectTargetHandleOffset ==
                          ObjectLayout::kGameObjectTargetHandle,
                      "target handle offset disagrees with bzr_object_layout.h");
        static_assert(kGameObjectTargetHandleOffset !=
                          ObjectLayout::kGameObjectMaxAmmoObfuscated,
                      "target handle must not alias obfuscated maxAmmo");

        constexpr uintptr_t kLocalPlayerNetIdAddr = 0x009180D4;
        // Returned when the net id cannot be read at all. Every SinglePlayer-tier
        // gate is written as "net id == 0", so a sentinel that is not 0 makes an
        // unreadable net id stand the feature down instead of enabling it. This
        // matches AutoSave, whose gate already treats an unreadable state as "not
        // a live single-player mission" (autosave.cpp IsSinglePlayerMissionActive).
        constexpr uint16_t kLocalPlayerNetIdUnreadable = 0xFFFFu;

        // Non-zero in a network game (the host has an id too). Fails CLOSED:
        // see kLocalPlayerNetIdUnreadable. Callers that only want to know
        // "am I in a network session" should read this as `!= 0`, which is
        // correct for the sentinel as well.
        uint16_t ReadLocalPlayerNetIdValue()
        {
            __try
            {
                return *reinterpret_cast<volatile const uint16_t*>(kLocalPlayerNetIdAddr);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return kLocalPlayerNetIdUnreadable;
            }
        }

        // The one predicate every SinglePlayer-tier feature gate is written
        // against. Named so a new feature does not have to rediscover that
        // "net id 0" means "safe to touch the simulation".
        bool IsSinglePlayerSession()
        {
            return ReadLocalPlayerNetIdValue() == 0;
        }

        bool TryGetGameObjectFieldBase(void* objectPtr, uint8_t*& outBase)
        {
            outBase = nullptr;
            const auto address = reinterpret_cast<uintptr_t>(objectPtr);
            if (address < 0x00010000 || (address % sizeof(void*)) != 0)
                return false;

            MEMORY_BASIC_INFORMATION mbi = {};
            if (VirtualQuery(objectPtr, &mbi, sizeof(mbi)) != sizeof(mbi))
                return false;
            if (mbi.State != MEM_COMMIT || !BZROpenShim::MemoryAccess::ProtectionAllows(mbi.Protect, BZROpenShim::MemoryAccess::Access::Read))
                return false;

            __try
            {
                auto* bytes = reinterpret_cast<uint8_t*>(objectPtr);
                auto** vtable = *reinterpret_cast<void***>(bytes + kGameObjectInterfaceOffset);
                if (!vtable)
                    return false;

                MEMORY_BASIC_INFORMATION vtableInfo = {};
                if (VirtualQuery(vtable, &vtableInfo, sizeof(vtableInfo)) != sizeof(vtableInfo))
                    return false;
                if (vtableInfo.State != MEM_COMMIT || !BZROpenShim::MemoryAccess::ProtectionAllows(vtableInfo.Protect, BZROpenShim::MemoryAccess::Access::Read))
                    return false;

                // Absolute VA, matching kGogGameObjectFriendPAddr and the rest
                // of this file; the shim already assumes the image loads at its
                // preferred base. Rebase defensively anyway so a relocated
                // image degrades to "no entries match" rather than to a
                // mis-identification.
                const uintptr_t base = GetMainModuleBase();
                const uintptr_t expected = base
                    ? base + (kGogGameObjectGetTeamAddr - kGogPreferredImageBase)
                    : kGogGameObjectGetTeamAddr;
                if (reinterpret_cast<uintptr_t>(vtable[kGameObjectGetTeamVtableOffset / sizeof(void*)]) != expected)
                    return false;

                outBase = bytes;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }



        bool IsLikelyGameObjectEntry(void* objectPtr)
        {
            uint8_t* base = nullptr;
            return TryGetGameObjectFieldBase(objectPtr, base);
        }

        int GetGameObjectActualTeam(void* objectPtr)
        {
            uint8_t* base = nullptr;
            if (!TryGetGameObjectFieldBase(objectPtr, base))
                return INT_MIN;

            // Direct field read. GetTeam's whole body is
            // `mov eax,[interface+0x15C]; ret`, and interface is complete+0x18,
            // so this reads exactly what the virtual would have returned.
            __try
            {
                return *reinterpret_cast<const int*>(base + kGameObjectActualTeamOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return INT_MIN;
            }
        }

        bool IsNeutralTeamObject(void* objectPtr)
        {
            return GetGameObjectActualTeam(objectPtr) == 0;
        }


        int GetGameObjectTeamForLog(void* objectPtr)
        {
            return GetGameObjectActualTeam(objectPtr);
        }

        // Defined later (headlight/flag sections); declared here so the
        // earlier diagnostic samplers can share the verified user-object
        // global and arena enumeration instead of the removed stale globals.
        // Defined with the pilot flashlight below. Declared here so the Ogre
        // scene-teardown hooks -- which run earlier in this file -- can drop the
        // shim-owned pilot light before the scene frees it.

        // MSVC RTTI: vtable[-1] -> CompleteObjectLocator, +12 -> TypeDescriptor,
        // +8 -> the decorated name. Every step is bounds-checked and the whole
        // walk sits under SEH, so an object without RTTI yields "?" rather than
        // a fault.
        const char* TryGetRttiClassName(const void* object, char* buffer, size_t bufferSize)
        {
            if (!object || !buffer || bufferSize == 0)
                return "?";
            buffer[0] = '\0';
            __try
            {
                auto* const* vtable = *reinterpret_cast<void* const* const*>(object);
                if (!vtable)
                    return "?";
                const auto* col = reinterpret_cast<const uint8_t*>(vtable[-1]);
                if (!col)
                    return "?";
                const auto* descriptor = *reinterpret_cast<const uint8_t* const*>(col + 12);
                if (!descriptor)
                    return "?";
                const char* name = reinterpret_cast<const char*>(descriptor + 8);
                size_t i = 0;
                for (; i + 1 < bufferSize && name[i] >= 0x20 && name[i] < 0x7F; ++i)
                    buffer[i] = name[i];
                buffer[i] = '\0';
                return (i > 0) ? buffer : "?";
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return "?";
            }
        }

        bool TryGetGameObjectHandleValue(void* objectPtr, int& outHandle)
        {
            outHandle = 0;
            if (!objectPtr || g_GameObjectGetHandleAddr == 0)
                return false;

            using GetHandleThiscallFn = uint32_t(__thiscall*)(void*);
            __try
            {
                outHandle = static_cast<int>(
                    reinterpret_cast<GetHandleThiscallFn>(g_GameObjectGetHandleAddr)(objectPtr));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outHandle = 0;
            }
            return outHandle != 0;
        }

        bool TryGetGameObjectObj76(void* gameObject, void*& outObj76)
        {
            outObj76 = nullptr;
            if (!gameObject)
                return false;

            __try
            {
                outObj76 =
                    *reinterpret_cast<void* const*>(reinterpret_cast<const uint8_t*>(gameObject) + kGameObjectObjOffset);
                return outObj76 != nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outObj76 = nullptr;
                return false;
            }
        }

        bool TryGetGameObjectFromObj76(void* obj76, void*& outGameObject)
        {
            outGameObject = nullptr;
            if (!obj76)
                return false;

            __try
            {
                outGameObject =
                    *reinterpret_cast<void* const*>(reinterpret_cast<const uint8_t*>(obj76) + kObj76GameObjectOffset);
                return outGameObject != nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outGameObject = nullptr;
                return false;
            }
        }

        bool TryGetObjectWorldPositionFromObj76(void* obj76, float (&outPosition)[3])
        {
            outPosition[0] = 0.0f;
            outPosition[1] = 0.0f;
            outPosition[2] = 0.0f;
            if (!obj76)
                return false;

            __try
            {
                const auto* transform = reinterpret_cast<const LegacyMat3*>(
                    reinterpret_cast<const uint8_t*>(obj76) + kObj76TransformOffset);
                outPosition[0] = static_cast<float>(transform->posit_x);
                outPosition[1] = static_cast<float>(transform->posit_y);
                outPosition[2] = static_cast<float>(transform->posit_z);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outPosition[0] = 0.0f;
                outPosition[1] = 0.0f;
                outPosition[2] = 0.0f;
                return false;
            }
        }

        bool TryGetGameObjectWorldPosition(void* gameObject, float (&outPosition)[3])
        {
            void* obj76 = nullptr;
            return TryGetGameObjectObj76(gameObject, obj76) &&
                   TryGetObjectWorldPositionFromObj76(obj76, outPosition);
        }

        // The advisory-PDB "object list" global (removed; it landed in string
        // data on the live exe) never produced objects from pointer-array
        // walks. Enumerate the verified GameObject arena instead:
        // the same 0x400-stride pool the GetObjByHandle slot formula indexes
        // (base 0x0260DB20, 4096 slots), filtered by the live-vtable check
        // the headlight walker uses.
        // Read-only runtime probes (2026-08-18).
        //
        // Static tracing has repeatedly named the wrong function in this
        // codebase, so these two probes answer the remaining questions by
        // observation instead. Both are diagnostic only: they read memory,
        // format a log line, and change nothing.
        // ---------------------------------------------------------------

        // Discovers owner/parent links empirically rather than assuming an
        // offset: reports which dwords inside `object` point at another live
        // slot of the GameObject arena. That is what turns "the damager might
        // be owned by a craft" into a measured field offset.
        void LogArenaPointerFields(const wchar_t* tag, void* object, size_t scanBytes)
        {
            if (!object)
                return;
            auto* arena = reinterpret_cast<uint8_t*>(EngineGlobals::GameObjectArena());
            if (!arena)
                return;
            const uintptr_t arenaLow = reinterpret_cast<uintptr_t>(arena);
            const uintptr_t arenaHigh = arenaLow + kHeadlightObjectSlotCount * kHeadlightObjectSlotSize;

            wchar_t line[512];
            int used = _snwprintf_s(line, _countof(line), _TRUNCATE, L"[DMGREVEAL]     %ls arenaRefs:", tag);
            if (used < 0)
                return;
            int found = 0;
            for (size_t off = 0; off + sizeof(void*) <= scanBytes && found < 8; off += sizeof(void*))
            {
                uintptr_t value = 0;
                __try
                {
                    value = *reinterpret_cast<const uintptr_t*>(reinterpret_cast<uint8_t*>(object) + off);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    break;
                }
                if (value < arenaLow || value >= arenaHigh)
                    continue;
                if (((value - arenaLow) % kHeadlightObjectSlotSize) != 0)
                    continue;
                if (!IsLikelyGameObjectEntry(reinterpret_cast<void*>(value)))
                    continue;
                const int wrote = _snwprintf_s(line + used, _countof(line) - used, _TRUNCATE,
                                               L" +0x%03X=0x%08X", static_cast<unsigned>(off),
                                               static_cast<uint32_t>(value));
                if (wrote < 0)
                    break;
                used += wrote;
                ++found;
            }
            if (found == 0)
                return;
            Log(L"%ls\n", line);
        }

        size_t CollectLiveGameObjectsFromArena(void** outObjects, size_t capacity)
        {
            if (!outObjects || capacity == 0)
                return 0;
            auto* arena = reinterpret_cast<uint8_t*>(EngineGlobals::GameObjectArena());
            if (!arena)
                return 0;
            size_t count = 0;
            for (size_t i = 0; i < kHeadlightObjectSlotCount && count < capacity; ++i)
            {
                void* object = arena + i * kHeadlightObjectSlotSize;
                if (IsLiveHeadlightObjectSlot(object))
                    outObjects[count++] = object;
            }
            return count;
        }

        bool HasTerrainLineOfSight(double startX,
                                          double startY,
                                          double startZ,
                                          double endX,
                                          double endY,
                                          double endZ)
        {
            if (!g_BzrFn_TerrainGetIntersection)
                return true;

            const float diffX = static_cast<float>(endX - startX);
            const float diffY = static_cast<float>(endY - startY);
            const float diffZ = static_cast<float>(endZ - startZ);
            float fraction = 1.0f;
            __try
            {
                return g_BzrFn_TerrainGetIntersection(startX,
                                                       startY,
                                                       startZ,
                                                       diffX,
                                                       diffY,
                                                       diffZ,
                                                       &fraction,
                                                       nullptr) == 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }
    }

    using namespace Hooks;

    FnGetPlayerHandle g_BzrFn_GetPlayerHandle = nullptr;
    FnGameObjectGetObjByHandle g_BzrFn_GameObjectGetObjByHandle = nullptr;
    static volatile long g_StaleGameObjectHandleLogBudget = 16;

    // Correct GOG handle->object conversion. The engine's GameObject pool is a
    // fixed 0x1000-slot table (patches.json "GameObject::Arena", 0x0260DB20 on
    // GOG) with a 0x400-byte stride; a
    // handle's slot index is its top 12 bits (handle >> 0x14). Verified live: a
    // craft pointer satisfies (ptr - 0x0260DB20) == slot * 0x400 exactly. The
    // former binding (kGogGameObjectGetObjByHandleAddr = 0x0046B160) actually
    // pointed into an unrelated ODF class-dispatch routine, so every call
    // crashed (deterministic null+0x19 fault via the scavenger retarget hook,
    // 2026-07-14). Round-trips through GetHandle (0x00462380) to reject stale or
    // empty slots; the pool memory is always mapped so the probe read is safe.
    void* __cdecl GameObjectFromHandleGog(int handle)
    {
        if (handle == 0)
            return nullptr;
        const uintptr_t arena = EngineGlobals::GameObjectArena();
        if (arena == 0)
            return nullptr;
        const uint32_t slot = (static_cast<uint32_t>(handle) >> 0x14) & 0xFFFu;
        void* obj = reinterpret_cast<void*>(
            static_cast<uintptr_t>(slot) * 0x400u + arena);
        using GetHandleThiscallFn = uint32_t(__thiscall*)(void*);
        if (g_GameObjectGetHandleAddr == 0)
            return nullptr;
        __try
        {
            if (reinterpret_cast<GetHandleThiscallFn>(g_GameObjectGetHandleAddr)(obj) ==
                static_cast<uint32_t>(handle))
                return obj;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
        return nullptr;
    }

    void* __cdecl GameObjectHandleGetObjHardened(int handle)
    {
        // GameObject::GetObj validates the low 20-bit generation against the
        // selected pool slot, but generation zero is also the empty-slot value.
        // A stale handle whose generation bits are zero therefore passes the
        // stock check and returns a completely empty GameObject slot. The stock
        // GameObjectHandle::GetObj wrapper immediately dereferences +0xF4 on
        // that slot to test the dead bit and crashes.
        //
        // battlezone98redux.exe.16444.dmp captured this in PathSpawn::Execute
        // owned by Inst4XMission. Redux reconstructs PathSpawn through a load
        // constructor that initializes only its AiProcess base, allowing cached
        // derived-state handles to be stale. Handle 0xBF800000 selected slot
        // 0xBF8, whose generation and object pointer were both zero.
        // Round-tripping through GetHandle rejects that slot because an empty
        // object returns handle 0.
        void* object = GameObjectFromHandleGog(handle);
        if (!object)
        {
            if (handle != 0 &&
                InterlockedDecrement(&g_StaleGameObjectHandleLogBudget) >= 0)
            {
                Log(L"[SAVELOAD] Rejected stale GameObject handle=0x%08X before object-state access\n",
                    static_cast<uint32_t>(handle));
            }
            return nullptr;
        }

        void* objectState = nullptr;
        uint32_t flags = 0;
        __try
        {
            objectState = *reinterpret_cast<void**>(
                reinterpret_cast<uint8_t*>(object) + 0xF4u);
            if (objectState)
            {
                flags = *reinterpret_cast<uint32_t*>(
                    reinterpret_cast<uint8_t*>(objectState) + 0x14u);
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            objectState = nullptr;
        }

        if (!objectState)
        {
            if (InterlockedDecrement(&g_StaleGameObjectHandleLogBudget) >= 0)
            {
                Log(L"[SAVELOAD] Rejected incomplete GameObject handle=0x%08X object=%p\n",
                    static_cast<uint32_t>(handle), object);
            }
            return nullptr;
        }

        return (flags & 0x200u) == 0 ? object : nullptr;
    }

    // Authoritative local-player world position. Consumers that need to know
    // where the player actually is should use this rather than the render
    // camera, which can be a chase or satellite view a long way from them.
    // Reuses the handle -> object -> transform path the chunk proxy path
    // already depends on; no new offsets are introduced here.
    // g_BzrFn_GetPlayerHandle used to be assigned in exactly one place: inside
    // InstallJumpSnipingProbeIfRequested, which early-returns unless
    // OPENSHIM_TRACE_JUMP_SNIPING is set. Every other caller therefore got a
    // null pointer and a silent "no player" forever -- which is how the terrain
    // follow-camera rule reported aimOrigin=camera on every record while
    // claiming to anchor on the player. The address is a GOG-build constant, so
    // callers must have already established they are on that exact build; the
    // terrain proxy gates its whole worker on an exe SHA-256 match before
    // calling this.
    void ResolveLocalPlayerLookupForVerifiedGogBuild()
    {
        if (!g_BzrFn_GetPlayerHandle)
        {
            g_BzrFn_GetPlayerHandle =
                reinterpret_cast<FnGetPlayerHandle>(kGogGetPlayerHandleAddr);
        }
        if (!g_BzrFn_GameObjectGetObjByHandle)
        {
            g_BzrFn_GameObjectGetObjByHandle =
                &GameObjectFromHandleGog; // was 0x0046B160 (wrong fn; crashed)
        }
    }

    bool TryGetLocalPlayerWorldPosition(float& x, float& y, float& z)
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        if (!g_BzrFn_GetPlayerHandle || !g_BzrFn_GameObjectGetObjByHandle)
            return false;

        const int handle = g_BzrFn_GetPlayerHandle();
        if (handle == 0)
            return false;
        void* person = g_BzrFn_GameObjectGetObjByHandle(handle);
        if (!person)
            return false;

        float position[3] = {};
        if (!TryGetGameObjectWorldPosition(person, position))
            return false;
        x = position[0];
        y = position[1];
        z = position[2];
        return true;
    }
}
