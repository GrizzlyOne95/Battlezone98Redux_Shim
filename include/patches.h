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
        void __cdecl Trampoline_ArtilleryWeaponSelect();
        void __cdecl Trampoline_LayMinesWeaponSelect();
        void __cdecl Trampoline_LayMinesSetSelected();
        void __cdecl Trampoline_ArtilleryTriggerVolley();
        void __cdecl Trampoline_LensFlareMatMgrGuard1();
        void __cdecl Trampoline_LensFlareMatMgrGuard2();
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
    // Global the AutoSave load-button site loads (mov eax, [global]); read
    // from the site in ResolveStaticReturnPointers before the hook goes in.
    inline uint32_t g_AutoSaveLoadReplayGlobal = 0;
    inline void* g_RetAddr_TurretCraftAimPitchMultiplier = nullptr;
    inline void* g_RetAddr_TurretTankAimPitchMultiplier = nullptr;
    inline void* g_RetAddr_UnderAttackAlertHook1 = nullptr;
    inline void* g_RetAddr_UnderAttackAlertHook2 = nullptr;
    inline void* g_RetAddr_OffensiveAttackRevealHook = nullptr;
    inline void* g_RetAddr_TurretTankAttackRevealHook = nullptr;
    inline void (*g_BZRFnPtr_JoinerEventOriginal)() = nullptr;
    inline void** g_MapListObject = nullptr;

    // -----------------------------------------------------------------------
    // LensFlare::~LensFlare singleton guards.
    //
    // Each holds the address of its own detour site in BZR.exe. The stolen
    // bytes are exactly the two instructions the trampoline replays, so the
    // trampolines derive both of their destinations from this one value:
    // site+5 resumes after the replay, site+13 skips the virtual call. The
    // two sites have identical relative layout, so no other address is baked
    // into the guards. See scripts/patches.json for the scanned sites.
    // -----------------------------------------------------------------------
    inline void* g_Site_LensFlareMatMgrGuard1 = nullptr;
    inline void* g_Site_LensFlareMatMgrGuard2 = nullptr;

    // Helper functions (implemented in trampolines.cpp and the src/patches hook files)
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
            // ODF legacy-section compatibility (odf_item_hooks.cpp): JMP5
            // detours on the engine UseItem/GetItemSize/UnlockItem trio so
            // ODF text is normalized before the ParameterDB parser runs.
            // Each site re-verifies its prologue and builds an original-call
            // trampoline at install; any failure keeps stock behavior.
            { 0, HookEngine::PatchType::JMP5, {}, "ODF UseItem Hook", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "ODF GetItemSize Hook", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "ODF UnlockItem Hook", false, {} },
            // EditTerrain keeps a mission-owned Ogre texture at +0xBC and an
            // independent "map initialized" latch at +0xD0. Mission cleanup
            // releases the texture but leaves the latch set, so entering the
            // editor in a later mission skips reconstruction. The next terrain
            // edit then dereferences the null texture while refreshing the
            // lower-right world map. Test the resource itself instead; this is
            // the same seven-byte CMP with only its field displacement changed.
            { 0, HookEngine::PatchType::BYTES, { 0x83, 0xB8, 0xBC, 0x00, 0x00, 0x00, 0x00 }, "Editor World Map Resource Lifetime Guard", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Map List Rewrite for Hop-Fix 1/3", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Map List Rewrite for Hop-Fix 2/3", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Map List Rewrite for Hop-Fix 3/3", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "Map List Fix Support 1/3", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Main Menu Version Text OpenShim", false, {} },
            // View setup stores the screen-space 2D depth floor as
            // near * 1.0000001, one float ULP in front of the near plane. HUD
            // text, gauges, weapon icons and the reticle all sit on that floor,
            // so for some far-clip values (driven by the TRN's NormalView
            // VisibilityRange) the projected z rounds past the near plane and
            // the whole layer is clipped. Repoint the mulss operand at a
            // constant with real margin; see Docs/FEEDBACK_MASTER_20260909.md
            // section 12.1.
            { 0, HookEngine::PatchType::DWORD, {}, "HUD 2D Depth Floor Margin", false, {} },
            { 0, HookEngine::PatchType::BYTE1, { 0xEB }, "Vehicle List Mod Fix 3/4 (Always Update Vehicle Control)", false, {} },
            // Rewrites the whole `push 0x10188` that supplies DSBUFFERDESC.dwFlags
            // for the streaming music buffer, adding DSBCAPS_GLOBALFOCUS (0x8000)
            // so DirectSound stops muting it when the game loses foreground. The
            // guard and the payload both cover the five-byte instruction rather
            // than the immediate alone, so a build whose layout moved cannot land
            // this on some other instruction's operand.
            { 0, HookEngine::PatchType::BYTES, { 0x68, 0x88, 0x81, 0x01, 0x00 }, "Music Buffer Global Focus", false, {} },
            // SetPlatform writes the engine's input-smoothing bypass flag
            // (0x009198F4) as 1 only for the iOS platform and 0 otherwise.
            // Rewriting the whole else-branch `mov dword [0x9198F4], 0` to store
            // 1 makes every call leave UserProcess's steer/pitch/throttle/strafe
            // low-pass off -- BZCC's "Control Smoothing: Off". Opt-in.
            { 0, HookEngine::PatchType::BYTES, { 0xC7, 0x05, 0xF4, 0x98, 0x91, 0x00, 0x01, 0x00, 0x00, 0x00 }, "Disable Control Smoothing", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "Chunk Render Resolve Hook", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "Target Reticle Popup Recent-Hit Getter Hook", false, {} },
            // Person::Simulate selected-mask call: substitute only the carrier
            // getter so a malformed pilot with no carrier gets mask 0 and the
            // remainder of the stock simulation continues.
            { 0, HookEngine::PatchType::REL32, {}, "Pilot Carrier Null Guard", false, {} },
            // The same null carrier reached through a second accessor: a
            // five-slot loop calls Carrier::GetWeapon without checking
            // Person+0x1A0, so guarding GetSelected alone left this live.
            { 0, HookEngine::PatchType::REL32, {}, "Pilot Carrier Weapon Null Guard", false, {} },
            // Person::Simulate's sniper-crouch scan dereferences every
            // Carrier::GetWeapon result for the selected mask; an empty
            // selected hardpoint gets a non-SNIP stand-in instead of null.
            { 0, HookEngine::PatchType::REL32, {}, "Person Sniper Scan Weapon Null Guard", false, {} },
            // ShellCasings: the OrdnanceClass factory call of an accepted
            // Cannon/Mortar/SniperGun and MachineGun shot goes through a
            // bridge that runs the factory, then queues a cosmetic casing.
            // Removed at startup when [General] ShellCasings = 0.
            { 0, HookEngine::PatchType::REL32, {}, "Shell Casings Cannon Shot Call", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "Shell Casings MachineGun Shot Call", false, {} },

            // PathBlockFaces: BlockCells entry detour. ODFs with pathBlock =
            // "faces"/"none" block only the path-grid cells inside their
            // collision solids; every other object keeps the stock box.
            // Removed at startup when [General] PathBlockFaces = 0.
            { 0, HookEngine::PatchType::JMP5, {}, "Path Block Faces BlockCells Hook", false, {} },
            // LensFlare::~LensFlare at 0x004F9250 runs from an atexit thunk
            // during CRT exit, after Ogre::MaterialManager has been destroyed.
            // It calls getSingleton and dereferences the null result twice for
            // a vtable+0x38 virtual call. Both sites are 5-byte JMP5 detours:
            // null resumes past the call with the pushed std::string argument
            // still balanced, non-null replays the stolen instructions, so the
            // remainder of the destructor (state byte, local string cleanup,
            // sub-objects, base dtors) behaves exactly as stock.
            { 0, HookEngine::PatchType::JMP5, {}, "LensFlare MaterialManager Guard 1/2", false, {} },
            { 0, HookEngine::PatchType::JMP5, {}, "LensFlare MaterialManager Guard 2/2", false, {} },
            // The atexit thunk 0x00866C60 is the destructor's only entry point
            // at process exit; NOPing its 5-byte call keeps the whole
            // destructor from running after Ogre has torn MaterialManager down.
            // This covers the sub-object release at 0x004C85D0, which faults
            // before the two guarded derefs above.
            { 0, HookEngine::PatchType::BYTES, { 0x90, 0x90, 0x90, 0x90, 0x90 }, "LensFlare Exit Destructor Skip", false, {} },
            // HoverCraft::UpdateSounds' turbo-stop lookup: stop the craft's
            // own cached turbo loop, never the thrust loop that shares its
            // filename (which left +0x2C0 dangling and heap-corrupting).
            { 0, HookEngine::PatchType::REL32, {}, "HoverCraft Turbo Sound Stop Guard", false, {} },
            // HoverCraft construction collects every type-67 (throttle nacelle)
            // geo into an eight-slot stack array with no bound check; a ninth
            // overran the /GS cookie. The rewritten store stops at eight.
            { 0, HookEngine::PatchType::BYTES, { 0x8B, 0x85, 0x3C, 0xFF, 0xFF, 0xFF, 0x83, 0xF8, 0x08, 0x7D, 0x36, 0x8B, 0x8D, 0x50, 0xFF, 0xFF, 0xFF, 0x89, 0x4C, 0x85, 0xD0, 0x40, 0x89, 0x85, 0x3C, 0xFF, 0xFF, 0xFF, 0xEB, 0x23, 0x90, 0x90, 0x90 }, "HoverCraft Nacelle Array Cap", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "World Builder Save Destination Dialog", false, {} },
            // ControlPanel target-list EnemyP call: an opt-in local order
            // authoring relaxation. The global EnemyP implementation stays stock.
            { 0, HookEngine::PatchType::REL32, {}, "Neutral Attack Order Target Hook", false, {} },
            // AIP_Load_Account's one PREREQ_WhatIs call, wrapped by a
            // pass-through probe. It exists to log what the AI's construction
            // program resolves each item_name to; the stock result is always
            // returned unchanged, so no build decision moves.
            { 0, HookEngine::PatchType::REL32, {}, "AIP Prereq Name Resolve Probe", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "AIP Prereq Name Resolve Probe Force Matching", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "AIP Prereq Name Resolve Probe Building Matching", false, {} },
            // AddObjectClass's duplicate test, and the Units_Init call that
            // finishes class registration. Together they let a built class
            // carry every producer that can make it instead of only the first.
            { 0, HookEngine::PatchType::REL32, {}, "AI Multi Producer Maker Collect", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "AI Multi Producer Maker Apply", false, {} },
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
            { 0, HookEngine::PatchType::REL32, {}, "Splinter Emitter Owner Propagation", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "HoverCraft Engine Flame Emit Hook 1/2", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "HoverCraft Engine Flame Emit Hook 2/2", false, {} },
            // Redirect the two AI weapon-selection call sites so artillery and
            // lay-mines honour weaponMask. Each guard covers the original rel32
            // operand, so a build whose layout moved fails closed and the stock
            // call stays in place.
            { 0, HookEngine::PatchType::REL32, {}, "Artillery Weapon Mask Select Hook", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "LayMines Weapon Mask Select Hook", false, {} },
            { 0, HookEngine::PatchType::REL32, {}, "LayMines Weapon Mask Trigger Hook", false, {} },
            // Synchronized multi-hardpoint artillery volley. Each of these
            // replaces the five bytes of one indirect `Weapon::Trigger` virtual
            // call inside ArtilleryProcess::DoAttack with a CALL rel32, so the
            // guard covers the whole original instruction pair rather than an
            // operand. A build whose encoding moved fails the guard and the
            // stock indirect call stays in place.
            { 0, HookEngine::PatchType::BYTES, {}, "Artillery Volley Trigger Hook 1/4", false, {} },
            { 0, HookEngine::PatchType::BYTES, {}, "Artillery Volley Trigger Hook 2/4", false, {} },
            { 0, HookEngine::PatchType::BYTES, {}, "Artillery Volley Trigger Hook 3/4", false, {} },
            { 0, HookEngine::PatchType::BYTES, {}, "Artillery Volley Trigger Hook 4/4", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Engine Flame Control VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Engine Flame Submit VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Chunk Effect Simulate VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Legacy World Update RenderQueue VTable Hook", false, {} },
            // Producer nested build menus (producer_build_menu.cpp): each
            // entry swaps one stock vtable slot, guarded by its stock pointer.
            { 0, HookEngine::PatchType::DWORD, {}, "Producer UpdateModeList VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Recycler UpdateModeList VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Factory UpdateModeList VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Producer SetActiveMode VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Recycler SetActiveMode VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Factory SetActiveMode VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Producer Deselect VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Recycler Deselect VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "Factory Deselect VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "ConstructionRig UpdateModeList VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "ConstructionRig SetActiveMode VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "ConstructionRig Deselect VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "ControlPanel PostLoad VTable Hook", false, {} },
            { 0, HookEngine::PatchType::DWORD, {}, "ControlPanel Cleanup VTable Hook", false, {} },
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
            { 0, HookEngine::PatchType::BYTES, {}, "P2P Reliable Send Backlog", false, {} },
            { 0, HookEngine::PatchType::BYTES, {}, "P2P Reliable First Retry", false, {} },
            { 0, HookEngine::PatchType::BYTES, {}, "P2P Reliable Retry Interval", false, {} },
            { 0, HookEngine::PatchType::BYTES, {}, "P2P Early Unreliable Drop Log", false, {} },
            { 0, HookEngine::PatchType::BYTES, {}, "P2P Early Unreliable Deliver", false, {} },
            { 0, HookEngine::PatchType::BYTES, {}, "P2P Early NAK Accept", false, {} },
        };

        // Future: could also load this list from JSON
        return patches;
    }
} // namespace BZROpenShim
