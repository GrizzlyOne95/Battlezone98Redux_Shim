// patches.h
// BZR Open Shim - patch definitions for BZR.exe v2.2.301
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once
#include "hook_engine.h"
#include <vector>

namespace BZROpenShim
{
    // Signature check block - 256 bytes at this address must match before patching
    // Default address, can be overridden by config
    static constexpr uint32_t DEFAULT_BZR_SIGNATURE_ADDR = 0x00868300;

    // -----------------------------------------------------------------------
    // Hop-fix trampoline addresses in this DLL.
    // -----------------------------------------------------------------------
    struct BzrString;
    extern "C" {
        void __cdecl Trampoline_HopFix1();
        void __cdecl Trampoline_HopFix2();
        void __cdecl Trampoline_HopFix3();
        void __cdecl Trampoline_MapListFixSupport1();
        void __cdecl Trampoline_Probe_MapSorting();
        void __cdecl Trampoline_Probe_MapFilter1();
        void __cdecl Trampoline_Probe_MapListFix1();
        void __cdecl Trampoline_Probe_MapListFix2();
        void __cdecl Trampoline_MapFilters1();
        void __cdecl Trampoline_MapFilters2();
        void __cdecl Trampoline_MapFilters3();
        void __cdecl Trampoline_MapFilters4();
        void __cdecl Trampoline_MapFilters5();
        void __cdecl Trampoline_MapFilters7();
        void __cdecl Trampoline_MapFilters8();
        void __cdecl Trampoline_VehicleListModFix1();
        void __cdecl Trampoline_VehicleListModFix4();
        void __cdecl Trampoline_BzrnetHost();
        void __cdecl Trampoline_BzrnetClient();
        void __cdecl Trampoline_CommandHelp();
        void __cdecl Trampoline_JoinerEventHook();
        void __cdecl Trampoline_BanButtonHook1();
        void __cdecl Trampoline_BanButtonHook2();
        void __cdecl Trampoline_AutoSaveLoadButtonHook();
        void __cdecl Trampoline_RestartMissionPauseHook();
        void __cdecl Trampoline_RestartMissionFailureHook();
        void __cdecl Trampoline_TurretCraftAimPitchMultiplier();
        void __cdecl Trampoline_TurretTankAimPitchMultiplier();
        void __cdecl Trampoline_UnderAttackAlertHook1();
        void __cdecl Trampoline_UnderAttackAlertHook2();
        void __cdecl Trampoline_OffensiveAttackRevealHook();
        void __cdecl Trampoline_TurretTankAttackRevealHook();
        void __cdecl Trampoline_EngineFlameHoverCraftEmit();
        void __cdecl Trampoline_DecodedWeaponMaskBias();
        void __cdecl Trampoline_RawWeaponMaskBias();
        void __cdecl Trampoline_ArtilleryWeaponSelect();
        void __cdecl Trampoline_LayMinesWeaponSelect();
        void __cdecl Trampoline_LayMinesSetSelected();
    }

    // -----------------------------------------------------------------------
    // Return-jump pointer storage (filled at patch time by the loader).
    // Each holds the address in BZR.exe where its trampoline resumes.
    // -----------------------------------------------------------------------
    inline void* g_RetAddr_HopFix1           = nullptr;
    inline void* g_RetAddr_HopFix2           = nullptr;
    inline void* g_RetAddr_HopFix3           = nullptr;
    inline void* g_RetAddr_MapListFixSupport1 = nullptr;
    inline void* g_RetAddr_Probe_MapSorting  = nullptr;
    inline void* g_RetAddr_Probe_MapFilter1  = nullptr;
    inline void* g_RetAddr_Probe_MapListFix1 = nullptr;
    inline void* g_RetAddr_Probe_MapListFix2 = nullptr;
    inline void* g_RetAddr_VersionNotice     = nullptr;
    inline void* g_RetAddr_MapFilters1       = nullptr;
    inline void* g_RetAddr_MapFilters2       = nullptr;
    inline void* g_RetAddr_MapFilters3       = nullptr;
    inline void* g_RetAddr_MapFilters4       = nullptr;
    inline void* g_RetAddr_MapFilters5       = nullptr;
    inline void* g_RetAddr_MapFilters7       = nullptr;
    inline void* g_RetAddr_MapFilters8_A     = nullptr;
    inline void* g_RetAddr_MapFilters8_B     = nullptr;
    inline void* g_RetAddr_MapFilters8_C     = nullptr;
    inline void* g_RetAddr_VehicleListModFix1 = nullptr;
    inline void* g_RetAddr_VehicleListModFix4 = nullptr;
    inline void* g_RetAddr_BzrnetHost         = nullptr;
    inline void* g_RetAddr_BzrnetClient       = nullptr;
    inline void* g_RetAddr_CommandHelpHandled = nullptr;
    inline void* g_RetAddr_CommandHelpFallback = nullptr;
    inline void* g_RetAddr_JoinerEventHook    = nullptr;
    inline void* g_RetAddr_BanHook1           = nullptr;
    inline void* g_RetAddr_BanHook2           = nullptr;
    inline void* g_RetAddr_AutoSaveLoadHook   = nullptr;
    inline void* g_RetAddr_TurretCraftAimPitchMultiplier = nullptr;
    inline void* g_RetAddr_TurretTankAimPitchMultiplier = nullptr;
    inline void* g_RetAddr_UnderAttackAlertHook1 = nullptr;
    inline void* g_RetAddr_UnderAttackAlertHook2 = nullptr;
    inline void* g_RetAddr_OffensiveAttackRevealHook = nullptr;
    inline void* g_RetAddr_TurretTankAttackRevealHook = nullptr;
    inline void (*g_BZRFnPtr_JoinerEventOriginal)() = nullptr;
    inline void** g_MapListObject = nullptr;

    // Helper functions (implemented in trampolines.cpp or bzr_hooks.cpp)
    void SetProducerBuildMenuOriginal(void* original);
    void InstallBriefingAssetOverrides();
    void InstallOgreMaterialCollisionGuard();

    // -----------------------------------------------------------------------
    // Build the active hop-fix patch list.
    // -----------------------------------------------------------------------
    inline std::vector<HookEngine::PatchDef> BuildPatchList()
    {

        std::vector<HookEngine::PatchDef> patches =
        {
            { 0, HookEngine::PatchType::JMP5, {}, "Map Sorting", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "GameObject Handle Stale Slot Guard", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Map List Rewrite for Hop-Fix 1/3", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Map List Rewrite for Hop-Fix 2/3", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Map List Rewrite for Hop-Fix 3/3", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Map List Fix Support 1/3", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Main Menu Version Text OpenShim", false, {} },
            { 0, HookEngine::PatchType::BYTE1, { 0xEB }, "Vehicle List Mod Fix 3/4 (Always Update Vehicle Control)", false, {} },
            // Rewrites the whole `push 0x10188` that supplies DSBUFFERDESC.dwFlags
            // for the streaming music buffer, adding DSBCAPS_GLOBALFOCUS (0x8000)
            // so DirectSound stops muting it when the game loses foreground. The
            // guard and the payload both cover the five-byte instruction rather
            // than the immediate alone, so a build whose layout moved cannot land
            // this on some other instruction's operand.
            { 0, HookEngine::PatchType::BYTES, { 0x68, 0x88, 0x81, 0x01, 0x00 }, "Music Buffer Global Focus", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "Chunk Render Resolve Hook", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "Producer Build Menu Root Hook", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "Target Reticle Popup Recent-Hit Getter Hook", false, {} },
            // Redirect the sun's one contribution to the global ScreenFlash so
            // the fullscreen white quad can be dropped without touching the sun
            // disc, the six lens-flare sprites, or the two explosion callers of
            // the same ScreenFlash method. See include/sun_flash.h. The guard
            // covers the original rel32 operand, and the payload is only built
            // after SunFlash::VerifyCallSite confirms the preceding byte is a
            // CALL rel32 that resolves to ScreenFlash::AddFlash.
            { 0, HookEngine::PatchType::REL32, {}, "Sun Screen Flash Contribution Hook", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "Damage Reveal Probe 1/4", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "Damage Reveal Probe 2/4", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "Damage Reveal Probe 3/4", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "Damage Reveal Probe 4/4", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "HoverCraft Engine Flame Emit Hook 1/2", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "HoverCraft Engine Flame Emit Hook 2/2", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Decoded Weapon Mask Carrier Bias Hook", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Raw Weapon Mask Carrier Bias Hook", false, {} },
            // Redirect the two AI weapon-selection call sites so artillery and
            // lay-mines honour weaponMask. Each guard covers the original rel32
            // operand, so a build whose layout moved fails closed and the stock
            // call stays in place.
            { 0, HookEngine::PatchType::REL32, {}, "Artillery Weapon Mask Select Hook", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "LayMines Weapon Mask Select Hook", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "LayMines Weapon Mask Trigger Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Engine Flame Control VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Engine Flame Submit VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Chunk Effect Simulate VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Legacy World Update RenderQueue VTable Hook", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Vehicle List Mod Fix 1/4 (Force Mod-Scoped Assets 1/3)", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "Vehicle List Mod Fix 2/4 (Force Mod-Scoped Assets 2/3)", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Vehicle List Mod Fix 4/4 (Force Mod-Scoped Assets 3/3)", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Lobby BZRNET Integration HOST", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Lobby BZRNET Integration CLIENT", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Custom Command /help Handler", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Joiner Event Hook", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Ban Button Hook 1/2", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Ban Button Hook 2/2", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "AutoSave Load Button Hook", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Restart Mission Hook Pause", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Restart Mission Hook Failure", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "TurretCraft Aim Pitch Multiplier", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "TurretTank Aim Pitch Multiplier", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Under Attack Alert Hook 1/2", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Under Attack Alert Hook 2/2", false, {} },
            // Attack-reveal trampolines remain compiled for future requalification,
            // but the curated patches.json intentionally omits their call sites
            // because the previous definitions were known to crash the GOG build.
            // Keep them out of the active registry so a deliberately absent unsafe
            // patch is not misreported as stale deployment configuration.
            // Confirmed Redux 2.2.301 compatibility defects. These three sites
            // are hash-gated, must resolve uniquely, and are applied by
            // redux_compatibility.cpp rather than the generic patch loop.
            { 0, HookEngine::PatchType::BYTES, {}, "Redux Numeric Locale Compatibility Call", false, {} },
            { 0, HookEngine::PatchType::BYTES, {}, "Redux TRN Binary Writer Mode", false, {} },
            { 0, HookEngine::PatchType::BYTES, {}, "Redux TRN Canonical Fwrite Hook", false, {} },
        };

        // Future: could also load this list from JSON
        return patches;
    }
} // namespace BZROpenShim
