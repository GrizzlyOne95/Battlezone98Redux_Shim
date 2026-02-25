// patches.h
// BZR Open Shim - clean-room patch definitions for BZR.exe v2.2.301
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// --- Architecture overview ---
// _bzcp.dll exposes a Lua module "install" function that is called from
// Lua mission scripts via require("_bzcp").install().
//
// The patch thread (FUN_1000eb30) runs on a background thread, waits for
// BZR.exe bytes at 0x00868300 to match a known signature (256 bytes),
// then applies all patches via WriteProcessMemory JMP hooks.
//
// Each JMP hook is:
//   E9 [rel32]   -- relative jump to replacement code inside _bzcp.dll
//
// We replicate this by applying the same JMP patches pointing to our own
// replacement trampolines defined here.
//
// --- Version lock ---
// ALL addresses in this file are STRICTLY for BZR.exe v2.2.301 (GOG).
// The version is verified by checking file version info == 0x12D (301).
//
// --- Address notes ---
// The BZR.exe addresses stored in _bzcp.dll's DAT_1002axxx variables are
// resolved at runtime from a secondary source (maplist.txt / external).
// The values here were extracted from memory dumps of a patched v2.2.301
// process. Where the dump addresses were outside BZR.exe range due to ASLR
// they are marked TODO and MUST be re-verified with a live debugger session
// against the GOG build before enabling those patches.

#pragma once
#include <cstdint>
#include <cstring>
#include <vector>

namespace BZROpenShim
{
    // -----------------------------------------------------------------------
    // Patch descriptor
    // -----------------------------------------------------------------------
    enum class PatchType : uint8_t
    {
        JMP5,       // 5-byte relative JMP:  E9 rel32
        DWORD,      // 4-byte DWORD overwrite
        BYTE1,      // 1-byte overwrite
        BYTES,      // raw byte array
    };

    struct PatchDef
    {
        uint32_t    bzr_address;    // Absolute VA in BZR.exe process space
        PatchType   type;
        std::vector<uint8_t> payload; // Bytes to write (JMP5 payload = target VA)
        const char* name;
        bool        verified;       // true = address confirmed against GOG build
        std::vector<uint8_t> expected_original; // Original bytes to verify before patching
    };

    // -----------------------------------------------------------------------
    // Helper: build a 5-byte E9 JMP from src to dst (both absolute VAs)
    // plus NOP padding to reach total_len.
    // -----------------------------------------------------------------------
    inline std::vector<uint8_t> MakeJmpPatch(uint32_t src, uint32_t dst, size_t total_len = 5)
    {
        int32_t rel = static_cast<int32_t>(dst) - static_cast<int32_t>(src + 5);
        std::vector<uint8_t> buf(total_len, 0x90); // fill with NOPs
        buf[0] = 0xE9;
        memcpy(&buf[1], &rel, 4);
        return buf;
    }

    // Signature check block - 256 bytes at this address must match before patching
    static constexpr uint32_t BZR_SIGNATURE_ADDR = 0x00868300;

    // -----------------------------------------------------------------------
    // Hop-fix trampoline addresses in this DLL.
    // -----------------------------------------------------------------------
    extern void __cdecl Trampoline_HopFix1();
    extern void __cdecl Trampoline_HopFix2();
    extern void __cdecl Trampoline_HopFix3();
    extern void __cdecl Trampoline_Probe_MapSorting();
    extern void __cdecl Trampoline_Probe_MapFilter1();
    extern void __cdecl Trampoline_VersionNotice();

    // -----------------------------------------------------------------------
    // Return-jump pointer storage (filled at patch time by the loader)
    // These mirror the _bzcp.dll hop-fix return-address pointers.
    // -----------------------------------------------------------------------
    inline void* g_RetAddr_HopFix1           = nullptr;
    inline void* g_RetAddr_HopFix2           = nullptr;
    inline void* g_RetAddr_HopFix3           = nullptr;
    inline void* g_RetAddr_Probe_MapSorting  = nullptr;
    inline void* g_RetAddr_Probe_MapFilter1  = nullptr;
    inline void* g_RetAddr_VersionNotice     = nullptr;

    // -----------------------------------------------------------------------
    // Build the active hop-fix patch list.
    // -----------------------------------------------------------------------
    inline std::vector<PatchDef> BuildPatchList()
    {
        using PT = PatchType;
        // Hop-fix only mode: keep the patch surface minimal and reliable.
        return
        {
            // -- Hop-Fix 1/3 --
            { 0x0, PT::JMP5, {}, "Map List Rewrite for Hop-Fix 1/3", false },
            // -- Hop-Fix 2/3 --
            { 0x0, PT::JMP5, {}, "Map List Rewrite for Hop-Fix 2/3", false },
            // -- Hop-Fix 3/3 --
            { 0x0, PT::JMP5, {}, "Map List Rewrite for Hop-Fix 3/3", false },
            // -- Refresh path probe (log-only) --
            { 0x0, PT::JMP5, {}, "Probe Refresh Path MapSorting", false },
            { 0x0, PT::JMP5, {}, "Probe Refresh Path MapFilter1", false },
            // -- Main-menu version transparency --
            { 0x0, PT::JMP5, {}, "Version Notice OpenShim", false },
            // -- Known map-jump fix (conditional -> unconditional branch) --
            { 0x0, PT::BYTE1, { 0xEB }, "Map Jump Fix Branch Override", false },
        };
    }
} // namespace BZROpenShim
