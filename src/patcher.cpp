// patcher.cpp
// BZR Open Shim - runtime patcher implementation
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Reconstructed from: bzcp_hopfix_decompiled.txt (FUN_1000eb30),
// FINAL_RE_REPORT.md, COMPLETE_RE_REPORT.md
//
// The original _bzcp.dll patch flow:
//  1. Open bzcp.log
//  2. Read BZR.exe file version via GetFileVersionInfoA; expect 0x12D (301)
//  3. Loop up to 1000 times polling ReadProcessMemory at 0x00868300
//     until the 256-byte signature block matches the expected value
//  4. Once matched, apply all JMP/DWORD/BYTE patches via WriteProcessMemory
//  5. Log each patch name and result

#include "patcher.h"
#include "patches.h"
#include "scroll_helper.h"
#include "trampolines.h"
#include "netcode_hooks.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstdio>
#include <cstring>
#include <vector>

namespace BZROpenShim
{
    // -----------------------------------------------------------------------
    // Internal log helper.
    // CRT's per-FILE lock handles thread safety for individual fwprintf calls.
    // LogHit is budget-limited to prevent I/O saturation from trampolines
    // firing on hot paths.
    // -----------------------------------------------------------------------
    static FILE* g_Log = nullptr;

    void Log(const wchar_t* fmt, ...)
    {
        if (!g_Log) return;
        va_list args;
        va_start(args, fmt);
        vfwprintf(g_Log, fmt, args);
        va_end(args);
        fflush(g_Log);
    }

    extern "C" void LogHit(const char* name)
    {
        static volatile long s_budget = 50;
        if (InterlockedDecrement(&s_budget) >= 0)
            Log(L"[HIT]  %hs\n", name);
    }

    // -----------------------------------------------------------------------
    // Detect Steam executable by filename.
    // -----------------------------------------------------------------------
    static bool IsSteamExe()
    {
        char path[MAX_PATH] = {};
        GetModuleFileNameA(nullptr, path, MAX_PATH);
        const char* base = strrchr(path, '\\');
        base = base ? (base + 1) : path;
        return _stricmp(base, "battlezone98redux.exe") == 0;
    }

    // -----------------------------------------------------------------------
    // Read BZR.exe file version (minor build number)
    // Mirrors _bzcp.dll logic: reads VS_FIXEDFILEINFO.dwFileVersionMS fields
    // Expected value: 0x12D == 301 decimal
    // -----------------------------------------------------------------------
    static uint32_t GetBZRVersion()
    {
        char path[MAX_PATH] = {};
        GetModuleFileNameA(nullptr, path, MAX_PATH);

        DWORD dummy = 0;
        DWORD size = GetFileVersionInfoSizeA(path, &dummy);
        if (size == 0) return 0xFFFFFFFF;

        std::vector<uint8_t> buf(size);
        if (!GetFileVersionInfoA(path, 0, size, buf.data())) return 0xFFFFFFFF;

        VS_FIXEDFILEINFO* ffi = nullptr;
        UINT ffiLen = 0;
        if (!VerQueryValueA(buf.data(), "\\",
            reinterpret_cast<LPVOID*>(&ffi), &ffiLen))
            return 0xFFFFFFFF;
        if (!ffi || ffi->dwSignature != 0xFEEF04BD) return 0xFFFFFFFF;

        Log(L"[INFO] FileVersion MS: 0x%08X, LS: 0x%08X\n", ffi->dwFileVersionMS, ffi->dwFileVersionLS);
        Log(L"[INFO] ProductVersion MS: 0x%08X, LS: 0x%08X\n", ffi->dwProductVersionMS, ffi->dwProductVersionLS);

        // _bzcp.dll reads *(ushort*)((int)local_160 + 0xe) 
        // local_160 is likely the start of VS_FIXEDFILEINFO.
        // +0xE is the HIWORD of dwFileVersionLS? 
        // No, in memory it's: 0x8 (MS), 0xC (LS). 
        // 0xC is LOWORD of LS, 0xE is HIWORD of LS.
        // So it's probably return static_cast<uint32_t>(HIWORD(ffi->dwFileVersionLS));
        
        uint32_t ver = static_cast<uint32_t>(LOWORD(ffi->dwFileVersionLS));
        if (ver == 0) ver = static_cast<uint32_t>(HIWORD(ffi->dwFileVersionLS));

        return ver;
    }

    // -----------------------------------------------------------------------
    // Apply a single patch via WriteProcessMemory
    // Mirrors _bzcp.dll FUN_10004930 / FUN_10003810
    // Returns: 1 = applied, 0 = skipped (not a failure), -1 = failed
    // -----------------------------------------------------------------------
    static int ApplyPatch(uint32_t address, const void* data, size_t len, const char* name,
                          const std::vector<uint8_t>& expected_original)
    {
        if (address == 0)
        {
            Log(L"[SKIP] %hs (address not yet verified)\n", name);
            return 0; // skip
        }

        HANDLE hProc = GetCurrentProcess();
        DWORD oldProtect = 0;
        void* ptr = reinterpret_cast<void*>(address);

        // Verify original bytes match (detects Steam vs GOG mismatch)
        if (!expected_original.empty())
        {
            std::vector<uint8_t> current(expected_original.size());
            SIZE_T read = 0;
            if (!ReadProcessMemory(hProc, ptr, current.data(), current.size(), &read) ||
                read != current.size())
            {
                Log(L"[SKIP] %hs - could not read original bytes\n", name);
                return 0; // skip
            }

            bool match = true;
            for (size_t i = 0; i < expected_original.size(); ++i)
            {
                if (current[i] != expected_original[i])
                {
                    match = false;
                    break;
                }
            }

            if (!match)
            {
                Log(L"[SKIP] %hs - original bytes mismatch (likely Steam vs GOG)\n", name);
                Log(L"       Expected: ");
                for (auto b : expected_original) Log(L"%02X ", b);
                Log(L"\n       Found:    ");
                for (auto b : current) Log(L"%02X ", b);
                Log(L"\n");
                return 0; // skip, not a failure
            }
        }

        // Make writable
        if (!VirtualProtect(ptr, len, PAGE_EXECUTE_READWRITE, &oldProtect))
        {
            Log(L"[FAIL] %hs - VirtualProtect failed (err %u)\n", name, GetLastError());
            return false;
        }

        SIZE_T written = 0;
        BOOL ok = WriteProcessMemory(hProc, ptr, data, len, &written);

        // Restore protection
        VirtualProtect(ptr, len, oldProtect, &oldProtect);

        if (!ok || written != len)
        {
            Log(L"[FAIL] %hs - WriteProcessMemory failed (err %u)\n", name, GetLastError());
            return -1; // failure
        }

        Log(L"[OK]   %hs wrote %zu bytes to 0x%08X\n", name, len, address);
        return 1; // applied
    }

    static bool BytesMatchAt(uint32_t address, const uint8_t* expected, size_t len)
    {
        uint8_t buf[16] = {};
        if (len > sizeof(buf))
            return false;

        SIZE_T read = 0;
        if (!ReadProcessMemory(GetCurrentProcess(),
                               reinterpret_cast<LPCVOID>(address),
                               buf, len, &read) ||
            read != len)
            return false;

        for (size_t i = 0; i < len; ++i)
        {
            if (buf[i] != expected[i])
                return false;
        }
        return true;
    }

    // -----------------------------------------------------------------------
    // Resolve a relative CALL target (E8 rel32) at a given instruction address.
    // Returns nullptr if the opcode is not a CALL or the read fails.
    // -----------------------------------------------------------------------
    static void* ResolveRelCallTarget(uint32_t instrAddr)
    {
        uint8_t buf[5] = {};
        SIZE_T read = 0;
        if (!ReadProcessMemory(GetCurrentProcess(),
                               reinterpret_cast<LPCVOID>(instrAddr),
                               buf, sizeof(buf), &read) ||
            read != sizeof(buf))
            return nullptr;

        if (buf[0] != 0xE8)
            return nullptr;

        int32_t rel = 0;
        memcpy(&rel, &buf[1], sizeof(rel));
        uint32_t target = instrAddr + 5 + static_cast<uint32_t>(rel);
        return reinterpret_cast<void*>(target);
    }

    // -----------------------------------------------------------------------
    // Build final patch payloads for JMP5 patches.
    // For each JMP5 patch, the payload is a 5-byte E9 sequence jumping to
    // the corresponding Trampoline_xxx function in this DLL.
    // -----------------------------------------------------------------------
    // -----------------------------------------------------------------------
    // Resolve internal BZR.exe pointers for trampolines/helpers.
    // Now uses dynamic addresses found by pattern scanning.
    // -----------------------------------------------------------------------
    static void ResolvePointers(uint32_t hopFix1Addr, uint32_t hopFix2Addr, uint32_t hopFix3Addr, uint32_t probeMapSortingAddr, uint32_t probeMapFilter1Addr, uint32_t versionNoticeAddr, uint32_t probeMapListFix1Addr, uint32_t probeMapListFix2Addr)
    {
        Log(L"=========== RESOLVING POINTERS ===========\n");

        // Hop-Fix 1 - _bzcp jumps back to patch site + 0xE
        // (covers overwritten + inlined original call block).
        if (hopFix1Addr) {
            g_RetAddr_HopFix1 = reinterpret_cast<void*>(hopFix1Addr + 0x0E);
            if (void* callTarget = ResolveRelCallTarget(hopFix1Addr + 0x09))
            {
                g_BZRFnPtr_HopFix1 = reinterpret_cast<void (*)()>(callTarget);
                Log(L"[PTR] Hop-Fix 1 call target (decoded): 0x%08X\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(callTarget)));
            }
            else
            {
                g_BZRFnPtr_HopFix1 = reinterpret_cast<void (*)()>(0x005D4260);
                Log(L"[PTR] Hop-Fix 1 call target fallback: 0x%08X\n", 0x005D4260);
            }
            Log(L"[PTR] Hop-Fix 1 return: 0x%08X\n", hopFix1Addr + 0x0E);
        }

        // Hop-Fix 2 - _bzcp jumps back to patch site + 0x13.
        if (hopFix2Addr) {
            g_RetAddr_HopFix2 = reinterpret_cast<void*>(hopFix2Addr + 0x13);
            g_MapListObject = reinterpret_cast<void**>(0x0094555C);
            // Stability mode: replay original call site target from 0x00799279 context.
            if (void* callTarget = ResolveRelCallTarget(hopFix2Addr + 0x0E))
            {
                g_BZRFnPtr_HopFix2 = reinterpret_cast<void (*)()>(callTarget);
                Log(L"[PTR] Hop-Fix 2 call target (decoded): 0x%08X\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(callTarget)));
            }
            else
            {
                g_BZRFnPtr_HopFix2 = reinterpret_cast<void (*)()>(0x007CAFA0);
                Log(L"[PTR] Hop-Fix 2 call target fallback: 0x%08X\n", 0x007CAFA0);
            }
            Log(L"[PTR] Hop-Fix 2 return: 0x%08X\n", hopFix2Addr + 0x13);
        }

        // Hop-Fix 3 - _bzcp jumps back to patch site + 7
        // (CALL EDX + PUSH 0x930).
        if (hopFix3Addr) {
            g_RetAddr_HopFix3 = reinterpret_cast<void*>(hopFix3Addr + 0x07);
            Log(L"[PTR] Hop-Fix 3 return: 0x%08X\n", hopFix3Addr + 0x07);
        }

        if (probeMapSortingAddr) {
            g_RetAddr_Probe_MapSorting = reinterpret_cast<void*>(probeMapSortingAddr + 0x07);
            Log(L"[PTR] Probe MapSorting return: 0x%08X\n", probeMapSortingAddr + 0x07);
        }
        if (probeMapFilter1Addr) {
            g_RetAddr_Probe_MapFilter1 = reinterpret_cast<void*>(probeMapFilter1Addr + 0x05);
            Log(L"[PTR] Probe MapFilter1 return: 0x%08X\n", probeMapFilter1Addr + 0x05);
        }

        if (probeMapListFix1Addr) {
            g_RetAddr_Probe_MapListFix1 = reinterpret_cast<void*>(probeMapListFix1Addr + 0x05);
            Log(L"[PTR] Probe MapListFix1 return: 0x%08X\n", probeMapListFix1Addr + 0x05);
        }
        if (probeMapListFix2Addr) {
            g_RetAddr_Probe_MapListFix2 = reinterpret_cast<void*>(probeMapListFix2Addr + 0x05);
            Log(L"[PTR] Probe MapListFix2 return: 0x%08X\n", probeMapListFix2Addr + 0x05);
        }

        if (versionNoticeAddr) {
            g_RetAddr_VersionNotice = reinterpret_cast<void*>(versionNoticeAddr + 0x05);
            Log(L"[PTR] Version Notice return: 0x%08X\n", versionNoticeAddr + 0x05);
        }

        // Scroll Helpers — DISABLED: these are GOG-specific addresses that
        // hang on Steam.  Leaving them nullptr safely skips scroll restoration
        // (all callers null-check).  The core hop-fix still works without them.
        // TODO: decode these dynamically from nearby call sites like HopFix1/2.
        // g_BZRFn_GetScrollState   = reinterpret_cast<uint32_t (*)()>(0x007D3360);
        // g_BZRFn_ScrollUp         = reinterpret_cast<void (*)()>(0x007CB540);
        // g_BZRFn_ScrollDown       = reinterpret_cast<void (*)()>(0x007CB500);

        Log(L"[OK]   Pointers resolved\n");
    }

    // -----------------------------------------------------------------------
    // Runtime pattern scanner - finds patch addresses by scanning memory
    // This works for both Steam and GOG versions since we search for actual
    // instruction patterns rather than hardcoded addresses.
    // -----------------------------------------------------------------------
    static void ScanForPatchAddresses(std::vector<PatchDef>& patches)
    {
        Log(L"=========== SCANNING FOR PATTERNS ===========\n");

        // Define patterns to search for
        struct ScanTarget {
            const char* patchName;
            std::vector<uint8_t> pattern;
            std::vector<uint8_t> mask;  // 0xFF = must match, 0x00 = wildcard
        };

        std::vector<ScanTarget> targets = {
            // Hop-Fix 1 at 0x0079B85F (confirmed identical on Steam and GOG).
            // Unique 14-byte pattern verified against full process dump (1 hit only):
            //   8B 45 FC  = MOV EAX,[EBP-4]
            //   8B 88 38 01 00 00 = MOV ECX,[EAX+0x138]
            //   E8 F3 89 E3 FF = CALL (relative, follows directly - makes this unique)
            { "Map List Rewrite for Hop-Fix 1/3",
              { 0x8B, 0x45, 0xFC, 0x8B, 0x88, 0x38, 0x01, 0x00, 0x00, 0xE8, 0xF3, 0x89, 0xE3, 0xFF },
              { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } },

            // Hop-Fix 2 at 0x00799279 (confirmed identical on Steam and GOG).
            // Unique 15-byte pattern verified against full process dump (1 hit only):
            //   6A 00  = PUSH 0
            //   8B 85 5C FF FF FF = MOV EAX,[EBP-0xA4]
            //   8B 88 7C 01 00 00 = MOV ECX,[EAX+0x17C]  (7C 01 makes this unique vs other hits)
            //   E8 = CALL follows
            { "Map List Rewrite for Hop-Fix 2/3",
              { 0x6A, 0x00, 0x8B, 0x85, 0x5C, 0xFF, 0xFF, 0xFF, 0x8B, 0x88, 0x7C, 0x01, 0x00, 0x00, 0xE8 },
              { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } },

            // Hop-Fix 3 at 0x00799377 (confirmed identical on Steam and GOG).
            // Unique 7-byte pattern verified against full process dump (1 hit only):
            //   FF D2 = CALL EDX
            //   68 30 09 00 00 = PUSH 0x930
            { "Map List Rewrite for Hop-Fix 3/3",
              { 0xFF, 0xD2, 0x68, 0x30, 0x09, 0x00, 0x00 },
              { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } },
        };

        // Restrict scan to executable pages inside the main BZR.exe image.
        HMODULE hMain = GetModuleHandleA(nullptr);
        uint8_t* mainBase = reinterpret_cast<uint8_t*>(hMain);
        size_t mainSize = 0;
        if (hMain)
        {
            auto dos = reinterpret_cast<IMAGE_DOS_HEADER*>(hMain);
            if (dos->e_magic == IMAGE_DOS_SIGNATURE)
            {
                auto nt = reinterpret_cast<IMAGE_NT_HEADERS*>(
                    reinterpret_cast<uint8_t*>(hMain) + dos->e_lfanew);
                if (nt->Signature == IMAGE_NT_SIGNATURE)
                    mainSize = nt->OptionalHeader.SizeOfImage;
            }
        }

        if (!mainBase || !mainSize)
        {
            Log(L"[SCAN] Failed to resolve main module bounds; skipping scan.\n");
            return;
        }

        uint8_t* mainEnd = mainBase + mainSize;
        Log(L"[SCAN] Main image: 0x%08X - 0x%08X\n",
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(mainBase)),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(mainEnd)));

        // Scan BZR-only memory for each pattern
        HANDLE hProc = GetCurrentProcess();
        MEMORY_BASIC_INFORMATION mbi = {};
        uint8_t* addr = mainBase;

        // Collect all executable memory regions
        std::vector<std::pair<uint8_t*, size_t>> regions;
        while (addr < mainEnd && VirtualQuery(addr, &mbi, sizeof(mbi)) == sizeof(mbi))
        {
            uint8_t* rBase = reinterpret_cast<uint8_t*>(mbi.BaseAddress);
            uint8_t* rEnd = rBase + mbi.RegionSize;
            if (rEnd <= mainBase || rBase >= mainEnd)
            {
                addr = rEnd;
                continue;
            }
            uint8_t* clipStart = (rBase < mainBase) ? mainBase : rBase;
            uint8_t* clipEnd = (rEnd > mainEnd) ? mainEnd : rEnd;
            size_t clipSize = static_cast<size_t>(clipEnd - clipStart);

            if (clipSize > 0 && mbi.State == MEM_COMMIT &&
                (mbi.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)))
            {
                regions.push_back({ clipStart, clipSize });
            }
            addr = rEnd;
        }

        Log(L"[SCAN] Found %zu executable regions\n", regions.size());

        // Search for each pattern
        for (const auto& target : targets)
        {
            bool found = false;
            for (const auto& region : regions)
            {
                std::vector<uint8_t> buf(region.second);
                SIZE_T read = 0;
                if (!ReadProcessMemory(hProc, region.first, buf.data(), region.second, &read) || read == 0)
                    continue;
                if (read < target.pattern.size())
                    continue;

                for (size_t i = 0; i <= read - target.pattern.size(); i++)
                {
                    bool match = true;
                    for (size_t j = 0; j < target.pattern.size(); j++)
                    {
                        if ((buf[i + j] & target.mask[j]) != (target.pattern[j] & target.mask[j]))
                        {
                            match = false;
                            break;
                        }
                    }

                    if (match)
                    {
                        uint32_t foundAddr = static_cast<uint32_t>(
                            reinterpret_cast<uintptr_t>(region.first + i));
                        
                        Log(L"[SCAN] Found '%hs' at 0x%08X\n", target.patchName, foundAddr);
                        
                        // Update the patch address
                        for (auto& p : patches)
                        {
                            if (strcmp(p.name, target.patchName) == 0)
                            {
                                p.bzr_address = foundAddr;
                                p.verified = true;
                                
                                // Update expected original bytes: always the first 5 bytes
                                // at the patch site (the bytes our JMP5 will overwrite).
                                p.expected_original.clear();
                                for (size_t j = 0; j < 5 && (i + j) < read; j++)
                                    p.expected_original.push_back(buf[i + j]);
                                
                                found = true;
                                break;
                            }
                        }
                        break;
                    }
                }
                if (found) break;
            }

            if (!found)
            {
                Log(L"[SCAN] Pattern '%hs' NOT FOUND\n", target.patchName);
            }
        }

        // Fallback for v2.2.301 when pattern scan misses due environment noise.
        // On Steam, the hop-fix patterns are NOT found and the trampolines
        // crash/freeze because they call into GOG-specific function addresses.
        // We ONLY fallback for safe patches (Version Notice, Map Jump Fix).
        // Hop-fix 1/2/3 and probe patches are SKIPPED when not found by scan.
        for (auto& p : patches)
        {
            if (p.verified) continue;

            if (strcmp(p.name, "Version Notice OpenShim") == 0)
            {
                p.bzr_address = 0x0062480B;
                p.verified = true;
                p.expected_original = { 0x68, 0x3C, 0xD5, 0x88, 0x00 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else if (strcmp(p.name, "Map Jump Fix Branch Override") == 0)
            {
                p.bzr_address = 0x007AA5A1;
                p.verified = true;
                p.expected_original = { 0x75 };
                Log(L"[SCAN] Fallback %hs => 0x%08X\n", p.name, p.bzr_address);
            }
            else
            {
                Log(L"[SCAN] SKIPPED %hs (pattern not found, no safe fallback)\n", p.name);
            }
        }
    }

    static void FillJmp5Payloads(std::vector<PatchDef>& patches)
    {
        // Map patch names to their trampoline addresses
        struct { const char* name; void* fn; } map[] =
        {
            { "Map List Rewrite for Hop-Fix 1/3",              (void*)Trampoline_HopFix1 },
            { "Map List Rewrite for Hop-Fix 2/3",              (void*)Trampoline_HopFix2 },
            { "Map List Rewrite for Hop-Fix 3/3",              (void*)Trampoline_HopFix3 },
            { "Probe Refresh Path MapSorting",                 (void*)Trampoline_Probe_MapSorting },
            { "Probe Refresh Path MapFilter1",                 (void*)Trampoline_Probe_MapFilter1 },
            { "Probe MapListFix1",                              (void*)Trampoline_Probe_MapListFix1 },
            { "Probe MapListFix2",                              (void*)Trampoline_Probe_MapListFix2 },
            { "Version Notice OpenShim",                       (void*)Trampoline_VersionNotice },
        };

        for (auto& p : patches)
        {
            if (p.type != PatchType::JMP5) continue;
            if (!p.verified) continue;   // skip unverified entries

            for (auto& m : map)
            {
                if (strcmp(p.name, m.name) == 0 && m.fn)
                {
                    uint32_t targetVal = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(m.fn));
                    p.payload = MakeJmpPatch(p.bzr_address, targetVal, 5);
                    break;
                }
            }
        }
    }

    // -----------------------------------------------------------------------
    // RunPatcher - main patch thread
    // -----------------------------------------------------------------------
    void RunPatcher(uint32_t shimVersion)
    {
        // 1. Open log
        _wfopen_s(&g_Log, L"bzcp.log", L"w");
        if (g_Log)
        {
            Log(L"=========== BZR Open Shim ===========\n");
            Log(L"Open source replacement for _bzcp.dll / winmm.bin\n");
            Log(L"Shim Version: %u\n", shimVersion);
        }

        const bool isSteam = IsSteamExe();
        Log(L"[INFO] Executable: %hs\n", isSteam ? "battlezone98redux.exe (Steam)" : "BZR.exe (GOG)");
        g_EnableScrollRestore = !isSteam;
        if (!g_EnableScrollRestore)
            Log(L"[INFO] Steam build detected: HopFix3 scroll restore disabled\n");

        // Apply netcode socket buffer hooks EARLY before the game initializes its networking.
        ApplyNetcodeHooks();

        // 2. Check BZR.exe version
        uint32_t gameVer = GetBZRVersion();
        // Keep the log file open for runtime hook telemetry (LogHit in trampolines).
        // Closing here leaves g_Log dangling while hooks are still active.
    }

} // namespace BZROpenShim
