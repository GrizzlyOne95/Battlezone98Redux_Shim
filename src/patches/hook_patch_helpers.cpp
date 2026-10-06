// hook_patch_helpers.cpp
// BZR Open Shim - code patching helpers: the inline detour installer
// (steal planning, trampoline, single-write jump) and its refusal log,
// expected-byte checks, REL32 call-target read and redirect, protected
// pointer and byte writes, RTTI vtable identity, the main module base and
// the EXU module check, split out of bzr_hooks.cpp.
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
        uintptr_t GetMainModuleBase()
        {
            static uintptr_t s_moduleBase = 0;
            if (s_moduleBase == 0)
                s_moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
            return s_moduleBase;
        }

        uintptr_t ExpectedGameObjectGetTeamAddr()
        {
            // Cached once bound: the reticle getter asks per visible selection.
            static uintptr_t s_expected = 0;
            if (s_expected == 0)
            {
                const uintptr_t addr = HookEngine::EngineAddress("GameObjectGetTeam");
                const uintptr_t base = GetMainModuleBase();
                if (addr)
                    s_expected = base ? base + (addr - kGogPreferredImageBase) : addr;
            }
            return s_expected;
        }

        uintptr_t FindMainImageImportSlot(const char* dllName, const char* importName)
        {
            const uintptr_t base = GetMainModuleBase();
            if (!base || !dllName || !importName)
                return 0;
            __try
            {
                const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
                if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                    return 0;
                const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(base + dos->e_lfanew);
                if (nt->Signature != IMAGE_NT_SIGNATURE)
                    return 0;
                const IMAGE_DATA_DIRECTORY& dir =
                    nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
                if (dir.VirtualAddress == 0)
                    return 0;
                for (auto* desc = reinterpret_cast<const IMAGE_IMPORT_DESCRIPTOR*>(base + dir.VirtualAddress);
                     desc->Name != 0;
                     ++desc)
                {
                    if (_stricmp(reinterpret_cast<const char*>(base + desc->Name), dllName) != 0)
                        continue;
                    if (desc->OriginalFirstThunk == 0)
                        return 0;
                    const auto* names =
                        reinterpret_cast<const IMAGE_THUNK_DATA32*>(base + desc->OriginalFirstThunk);
                    for (size_t i = 0; names[i].u1.AddressOfData != 0; ++i)
                    {
                        if (IMAGE_SNAP_BY_ORDINAL32(names[i].u1.Ordinal))
                            continue;
                        const auto* byName = reinterpret_cast<const IMAGE_IMPORT_BY_NAME*>(
                            base + names[i].u1.AddressOfData);
                        if (strcmp(reinterpret_cast<const char*>(byName->Name), importName) == 0)
                            return base + desc->FirstThunk + i * sizeof(IMAGE_THUNK_DATA32);
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return 0;
        }

        uintptr_t ViewRecordAddr()
        {
            static uintptr_t s_addr = 0;
            if (s_addr == 0)
                s_addr = HookEngine::EngineAddress("ViewRecord");
            return s_addr;
        }

        bool IsKnownOgreMainBuild(HMODULE ogreMain)
        {
            // SHA-256 E5E693960B95AD0D60733A3B688464A6C6CBA234E86950698F9C2BEA4ACFEB45,
            // identical on GOG and Steam (see ogre_enhanced_light_selection.cpp).
            constexpr DWORD kKnownOgreTimestamp = 0x5866BF6A;
            constexpr DWORD kKnownOgreImageSize = 0x00A65000;
            static const bool known = [ogreMain] {
                __try
                {
                    const auto base = reinterpret_cast<uintptr_t>(ogreMain);
                    const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
                    const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(base + dos->e_lfanew);
                    const bool match = dos->e_magic == IMAGE_DOS_SIGNATURE &&
                                       nt->Signature == IMAGE_NT_SIGNATURE &&
                                       nt->FileHeader.TimeDateStamp == kKnownOgreTimestamp &&
                                       nt->OptionalHeader.SizeOfImage == kKnownOgreImageSize;
                    if (!match)
                        Log(L"[BUILD] OgreMain.dll is not the known build; offset-resolved Ogre helpers stand down\n");
                    return match;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }();
            return known;
        }

        uintptr_t WorldRenderOriginAddr()
        {
            static uintptr_t s_addr = 0;
            if (s_addr == 0)
                s_addr = HookEngine::EngineAddress("WorldRenderOrigin");
            return s_addr;
        }

        uint32_t ResolveRel32Target(uint8_t* callInstr)
        {
            if (!callInstr || callInstr[0] != 0xE8)
                return 0;

            const int32_t rel = *reinterpret_cast<int32_t*>(callInstr + 1);
            return static_cast<uint32_t>(
                reinterpret_cast<uintptr_t>(callInstr + 5) + rel);
        }

        bool WritePointerValue(uintptr_t address, void* value)
        {
            if (address == 0)
                return false;

            DWORD oldProtect = 0;
            if (!VirtualProtect(reinterpret_cast<void*>(address), sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;

            *reinterpret_cast<void**>(address) = value;
            FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<void*>(address), sizeof(void*));

            DWORD restoreProtect = 0;
            VirtualProtect(reinterpret_cast<void*>(address), sizeof(void*), oldProtect, &restoreProtect);
            return true;
        }

        bool VtableTypeNameMatches(uintptr_t vtableAddress, const char* expectedName)
        {
            if (!vtableAddress || !expectedName || !*expectedName)
                return false;

            __try
            {
                const uintptr_t completeObjectLocator =
                    *reinterpret_cast<const uint32_t*>(vtableAddress - sizeof(uint32_t));
                if (!completeObjectLocator)
                    return false;

                const uintptr_t typeDescriptor =
                    *reinterpret_cast<const uint32_t*>(completeObjectLocator + 0x0C);
                if (!typeDescriptor)
                    return false;

                const char* typeName = reinterpret_cast<const char*>(typeDescriptor + 0x08);
                return std::strcmp(typeName, expectedName) == 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool IsExuModuleLoaded()
        {
            return GetModuleHandleA("exu.dll") != nullptr ||
                   GetModuleHandleA("ExtraUtilities.dll") != nullptr;
        }

        // Generic protected in-place byte write (VirtualProtect + memcpy + flush).
        bool WritePatchBytes(uintptr_t address, const uint8_t* bytes, size_t len)
        {
            auto* target = reinterpret_cast<uint8_t*>(address);
            DWORD oldProtect = 0;
            if (!VirtualProtect(target, len, PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;
            std::memcpy(target, bytes, len);
            FlushInstructionCache(GetCurrentProcess(), target, len);
            DWORD restoreProtect = 0;
            VirtualProtect(target, len, oldProtect, &restoreProtect);
            return true;
        }

        // SEH leaves used by AttackTaskDoStateTuningHook. Keep all checked
        // STL iterators/RAII in the caller so Debug builds do not hit C2712.
        bool RedirectCallTarget(uintptr_t callAddress,
                                       uintptr_t originalTarget,
                                       uintptr_t desiredTarget)
        {
            uint8_t call[5] = {};
            SIZE_T read = 0;
            if (!ReadProcessMemory(GetCurrentProcess(),
                                   reinterpret_cast<const void*>(callAddress),
                                   call,
                                   sizeof(call),
                                   &read) ||
                read != sizeof(call) || call[0] != 0xE8)
            {
                return false;
            }

            int32_t currentRelative = 0;
            std::memcpy(&currentRelative, call + 1, sizeof(currentRelative));
            const uintptr_t currentTarget = callAddress + 5 + currentRelative;
            if (currentTarget == desiredTarget)
                return true;
            if (currentTarget != originalTarget)
                return false;

            const int32_t desiredRelative =
                static_cast<int32_t>(desiredTarget) -
                static_cast<int32_t>(callAddress + 5);
            std::memcpy(call + 1, &desiredRelative, sizeof(desiredRelative));
            return WritePatchBytes(callAddress, call, sizeof(call));
        }
    }

    using namespace Hooks;

    // Retry loops call the installer every 100 ms; log each refused site once.
    static void LogDetourStealRefusal(uintptr_t target, size_t patchLen,
                                      const BZROpenShim::X86StealPlan& plan,
                                      const uint8_t* bytes, size_t byteCount)
    {
        static volatile LONG s_loggedTargets[64] = {};
        for (auto& slot : s_loggedTargets)
        {
            const LONG seen = InterlockedCompareExchange(&slot, static_cast<LONG>(target), 0);
            if (seen == 0) break;
            if (seen == static_cast<LONG>(target)) return;
        }
        char hex[3 * kInlineDetourMaxPatchLen + 1] = {};
        size_t n = 0;
        for (size_t i = 0; i < byteCount && i < kInlineDetourMaxPatchLen && n + 3 < sizeof(hex); ++i)
            n += static_cast<size_t>(snprintf(hex + n, sizeof(hex) - n, "%02X ", bytes[i]));
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Warn, "DETOUR",
            "refused %u-byte steal at 0x%08X: %s at +%u (boundary %u, %u instr) bytes=%s",
            static_cast<unsigned>(patchLen), static_cast<unsigned>(target),
            BZROpenShim::X86StealStatusName(plan.status), static_cast<unsigned>(plan.failOffset),
            static_cast<unsigned>(plan.boundary), static_cast<unsigned>(plan.instructionCount), hex);
    }

    bool InstallInlineDetour32(InlineDetour32& detour,
                                      uintptr_t target,
                                      void* hook,
                                      size_t patchLen,
                                      const uint8_t* expectedBytes,
                                      size_t expectedLen)
    {
        if (!target || !hook || patchLen < 5 || patchLen > detour.original.size())
            return false;

        // Held from the "already installed" check through the write: the
        // patch thread's settle loop and a game-thread SDK bridge can both
        // arrive here for one site, and the loser used to see the other's
        // half-written jump as a prologue mismatch, or copy it into its own
        // trampoline.
        HookEngine::CodePatchLock lock;

        if (detour.trampoline)
            return true;

        auto* targetBytes = reinterpret_cast<uint8_t*>(target);
        if (expectedBytes && expectedLen > 0)
        {
            if (expectedLen > patchLen || memcmp(targetBytes, expectedBytes, expectedLen) != 0)
                return false;
        }

        // The stolen range must end on an instruction boundary and contain
        // nothing that changes meaning at the trampoline address. Read past
        // patchLen so an instruction straddling the boundary can be sized;
        // if that read fails (page end) fall back to the exact range.
        uint8_t probe[kInlineDetourMaxPatchLen + 15] = {};
        size_t probeLen = patchLen + 15;
        SIZE_T probeRead = 0;
        if (!ReadProcessMemory(GetCurrentProcess(), targetBytes, probe, probeLen, &probeRead) || probeRead != probeLen)
        {
            probeLen = patchLen;
            probeRead = 0;
            if (!ReadProcessMemory(GetCurrentProcess(), targetBytes, probe, probeLen, &probeRead) || probeRead != probeLen)
                return false;
        }
        const BZROpenShim::X86StealPlan plan = BZROpenShim::PlanDetourSteal32(probe, probeLen, patchLen);
        if (plan.status != BZROpenShim::X86StealStatus::Ok)
        {
            LogDetourStealRefusal(target, patchLen, plan, probe, probeLen);
            return false;
        }

        auto* trampolineBytes = reinterpret_cast<uint8_t*>(
            VirtualAlloc(nullptr, patchLen + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
        if (!trampolineBytes)
            return false;

        memcpy(detour.original.data(), targetBytes, patchLen);
        memcpy(trampolineBytes, targetBytes, patchLen);

        // rel32 call/jmp/jcc inside the stolen range keep their absolute
        // destination once re-based by the copy distance.
        for (size_t r = 0; r < plan.rel32Count; ++r)
        {
            const size_t at = plan.rel32Offsets[r];
            int32_t rel = 0;
            memcpy(&rel, trampolineBytes + at, sizeof(rel));
            rel += static_cast<int32_t>(target - reinterpret_cast<uintptr_t>(trampolineBytes));
            memcpy(trampolineBytes + at, &rel, sizeof(rel));
        }

        const uintptr_t resumeAddr = target + patchLen;
        trampolineBytes[patchLen] = 0xE9;
        const int32_t trampolineRel =
            static_cast<int32_t>(resumeAddr) -
            static_cast<int32_t>(reinterpret_cast<uintptr_t>(trampolineBytes + patchLen) + 5);
        memcpy(trampolineBytes + patchLen + 1, &trampolineRel, sizeof(trampolineRel));

        // The whole jump goes in through one WriteMemory call, which holds
        // every other thread off the site while the bytes land and flushes
        // the instruction cache. It used to be stored a byte at a time,
        // opcode first and rel32 after, on code the game thread may have
        // been executing.
        uint8_t patchImage[kInlineDetourMaxPatchLen] = {};
        patchImage[0] = 0xE9;
        const int32_t hookRel =
            static_cast<int32_t>(reinterpret_cast<uintptr_t>(hook)) -
            static_cast<int32_t>(target + 5);
        memcpy(patchImage + 1, &hookRel, sizeof(hookRel));
        for (size_t i = 5; i < patchLen; ++i)
            patchImage[i] = 0x90;
        if (!HookEngine::WriteMemory(static_cast<uint32_t>(target), patchImage, patchLen))
        {
            VirtualFree(trampolineBytes, 0, MEM_RELEASE);
            return false;
        }

        detour.target = target;
        detour.hook = hook;
        detour.trampoline = trampolineBytes;
        detour.patchLen = patchLen;
        return true;
    }

    bool ExpectedBytesMatchAt(uintptr_t address,
                                     const uint8_t* expectedBytes,
                                     size_t expectedLen)
    {
        if (!address || !expectedBytes || expectedLen == 0 || expectedLen > kInlineDetourMaxPatchLen)
            return false;

        uint8_t current[kInlineDetourMaxPatchLen] = {};
        SIZE_T read = 0;
        if (!ReadProcessMemory(GetCurrentProcess(),
                               reinterpret_cast<const void*>(address),
                               current,
                               expectedLen,
                               &read) ||
            read != expectedLen)
        {
            return false;
        }

        return memcmp(current, expectedBytes, expectedLen) == 0;
    }
}
