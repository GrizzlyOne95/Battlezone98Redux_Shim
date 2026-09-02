// cli_multiparam_parser.cpp
// BZR Open Shim - command-line multi-parameter option compatibility fix
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Two command-line grammars in the same binary contradict each other.
//
// ProcessCommandLine (FUN_007D5120, VA 0x007D5120) tokenises the command line
// with strtok and the delimiter set at 0x008F068C:
//
//     0x008F068C   20 2C 09 00      " ,\t"
//
// so a comma ENDS a token. But the shellmap handler inside that same function
// parses its value with a comma-bearing format:
//
//     0x007D5600   68 80 0E 8A 00    push offset 0x008A0E80  ; ":%d,%d"
//     0x007D5611   FF 15 0C 95 86 00 call ds:[0x0086950C]    ; sscanf
//
// so a comma SEPARATES two values inside one token. Both cannot hold. Given
// "-shellmap:216,178" strtok NUL-terminates at the comma, sscanf sees ":216",
// returns 1, and the handler's res==1 branch copies width over height.
//
// Battlezone 1.5 has the identical contradiction (delimiters " ," at
// bzone.exe:0x006311D8 against the same ":%d,%d" handler grammar), so this is
// an inherited 1.5 defect rather than a Redux regression. Redux additionally
// added tab to the delimiter set; that is a real divergence but not the cause.
//
// ---------------------------------------------------------------------------
// Why the delimiter and not a post-parser write
//
// Docs/CLI_MULTIPARAM_PARSER_ACTIVE_PATCH_20260831.md proposed repairing the
// parsed dimensions after ProcessCommandLine returns. Reading the decompile
// out to the positional branch shows that cannot restore the feature, because
// the split does more damage than losing the height. The orphaned "178" token
// re-enters the loop and takes the non-switch path:
//
//     strncpy(&DAT_00945708, token, 0x1000);   // mission/save path
//     strncpy(&DAT_00915540, token, 0x10);     // map name
//     FUN_00434170(5);                         // SetRunning(5)
//     DAT_0091556C = 1;
//
// DAT_00915540 is the very buffer the shellmap consumer passes as the map
// name (FUN_00617110: if (DAT_009183D4 == 1) FUN_0050F920(&DAT_00915540,
// packed & 0xFFFF, packed >> 16 & 0xFFFF)). A post-parser write to the
// dimension globals would therefore hand the consumer correct dimensions and
// a map name of "178", plus a changed run state. Unpicking that means
// re-deriving the positional token as well -- i.e. reimplementing the parser,
// which is the outcome the narrow strategy set out to avoid.
//
// Removing the comma from the delimiter set makes the split not happen at all,
// so sscanf returns 2, no orphan token is produced, and none of the collateral
// state is touched. It also repairs every other option in this parser whose
// value grammar contains a comma, rather than shellmap alone.
//
// The delimiter string is referenced by exactly one function in the image
// (ProcessCommandLine, at the two push sites guarded below), so editing it in
// place cannot affect any other tokenizer.
//
// Trade-off: a command line that used a comma where a space belongs -- e.g.
// "-win,-nointro" -- parsed as two options before and becomes one unmatched
// token after. Space is the universal argument separator and any comma-bearing
// value is broken today, so this is judged negligible; [Fixes]
// CliMultiParameterOptions = 0 restores stock tokenising for anyone who needs
// it.
//
// ---------------------------------------------------------------------------
// Timing and SteamStub
//
// The parser runs from WinMain via FUN_00618C10 (call at 0x00618D0E), which is
// far earlier than RunPatcher's WaitForSignature poll on the patch thread, so
// this is applied synchronously from DllMain like editor_view_order.cpp.
//
// That has a consequence for the guards. The delimiter lives at 0x008F068C in
// .data, which SteamStub never encrypts, so the write itself is safe on both
// stores. The two push instructions are in .text, which on Steam is still
// being decrypted in stages at DllMain time. Requiring them would make the fix
// silently GOG-only. So identity is established by the exe's file version plus
// the exact .data bytes at a fixed (never scanned) address, and the .text
// sites are checked as best-effort corroboration that is logged, not required.

#include "cli_multiparam_parser.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace BZROpenShim
{
    namespace
    {
        constexpr const char* kLogTag = "cliparse";

        // Redux 2.2.301 (GOG and Steam share the build; Steam wraps it in
        // SteamStub). Verified against battlezone98redux.exe SHA-256
        // 8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413,
        // 5425152 bytes, ImageBase 0x00400000.
        constexpr uint32_t kExpectedGameVersion = 301;

        // ProcessCommandLine's private strtok delimiter set, in .data.
        constexpr uintptr_t kDelimiterAddr = 0x008F068Cu;
        constexpr uint8_t kDelimiterStock[4] = { 0x20, 0x2C, 0x09, 0x00 };    // " ,\t"
        constexpr uint8_t kDelimiterRepaired[4] = { 0x20, 0x09, 0x00, 0x00 }; // " \t"

        // Best-effort .text corroboration: the only two instructions in the
        // image that reference kDelimiterAddr. Each guard spans the push and
        // the strtok call it feeds, including the IAT displacement, so it
        // cannot land on an unrelated push of the same constant.
        //
        //   0x007D5156  push offset 0x008F068C
        //               mov  ecx,[ebp+8]
        //               push ecx
        //               call ds:[0x008694CC]        ; strtok(cmdline, delims)
        constexpr uintptr_t kFirstTokenSiteAddr = 0x007D5156u;
        constexpr uint8_t kFirstTokenSiteExpected[] = {
            0x68, 0x8C, 0x06, 0x8F, 0x00,
            0x8B, 0x4D, 0x08,
            0x51,
            0xFF, 0x15, 0xCC, 0x94, 0x86, 0x00
        };

        //   0x007D5FD1  push offset 0x008F068C
        //               push 0
        //               call ds:[0x008694CC]        ; strtok(NULL, delims)
        constexpr uintptr_t kNextTokenSiteAddr = 0x007D5FD1u;
        constexpr uint8_t kNextTokenSiteExpected[] = {
            0x68, 0x8C, 0x06, 0x8F, 0x00,
            0x6A, 0x00,
            0xFF, 0x15, 0xCC, 0x94, 0x86, 0x00
        };

        // The handler this fix exists to unblock. Proves the comma-bearing
        // value grammar is still present in the running build.
        //
        //   0x007D5600  push offset 0x008A0E80       ; ":%d,%d"
        constexpr uintptr_t kShellmapFormatSiteAddr = 0x007D5600u;
        constexpr uint8_t kShellmapFormatSiteExpected[] = {
            0x68, 0x80, 0x0E, 0x8A, 0x00
        };
        constexpr uintptr_t kShellmapFormatAddr = 0x008A0E80u;
        constexpr uint8_t kShellmapFormatExpected[] = {
            0x3A, 0x25, 0x64, 0x2C, 0x25, 0x64, 0x00   // ":%d,%d"
        };

        constexpr bool kFixEnabledDefault = true;

        // Static rather than a local: this runs under the loader lock, where a
        // 64 KiB stack frame is a poor idea and a heap allocation is worse.
        // ApplyCliMultiParameterOptionFix is called once, from DllMain, before
        // any other shim thread exists.
        uint8_t s_versionBuffer[0x10000];

        // Written once at attach, read once on the patch thread.
        bool s_applied = false;

        bool BytesMatch(uintptr_t address, const uint8_t* expected, size_t length)
        {
            __try
            {
                return std::memcmp(reinterpret_cast<const void*>(address), expected, length) == 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool WriteDelimiters(const uint8_t* bytes)
        {
            auto* target = reinterpret_cast<uint8_t*>(kDelimiterAddr);

            DWORD oldProtect = 0;
            if (!VirtualProtect(target, sizeof(kDelimiterStock), PAGE_READWRITE, &oldProtect))
                return false;

            std::memcpy(target, bytes, sizeof(kDelimiterStock));

            DWORD ignored = 0;
            VirtualProtect(target, sizeof(kDelimiterStock), oldProtect, &ignored);
            return true;
        }

        // The executable's file version, read from its own resource rather than
        // from memory. SteamStub does not touch the resource directory, so this
        // is the one identity check that is equally reliable on both stores at
        // DLL_PROCESS_ATTACH.
        uint32_t GetGameFileVersion()
        {
            char path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return 0xFFFFFFFFu;

            DWORD handle = 0;
            const DWORD size = GetFileVersionInfoSizeA(path, &handle);
            if (size == 0 || size > sizeof(s_versionBuffer))
                return 0xFFFFFFFFu;

            if (!GetFileVersionInfoA(path, 0, size, s_versionBuffer))
                return 0xFFFFFFFFu;

            VS_FIXEDFILEINFO* info = nullptr;
            UINT infoLength = 0;
            if (!VerQueryValueA(s_versionBuffer, "\\", reinterpret_cast<LPVOID*>(&info), &infoLength) || !info)
                return 0xFFFFFFFFu;

            uint32_t version = static_cast<uint32_t>(LOWORD(info->dwFileVersionLS));
            if (version == 0)
                version = static_cast<uint32_t>(HIWORD(info->dwFileVersionLS));
            return version;
        }

        // Deliberately self-contained, for the same reason editor_view_order.cpp
        // is: this runs inside DllMain, before the shim's normal config
        // plumbing is initialized. It resolves the same openshim.ini beside the
        // executable that the rest of the shim uses.
        bool ReadEnabledFromUserConfig()
        {
            char exePath[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameA(nullptr, exePath, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return kFixEnabledDefault;

            char* lastBackslash = std::strrchr(exePath, '\\');
            if (!lastBackslash)
                return kFixEnabledDefault;
            *(lastBackslash + 1) = '\0';

            char iniPath[MAX_PATH] = {};
            if (_snprintf_s(iniPath, sizeof(iniPath), _TRUNCATE, "%sopenshim.ini", exePath) < 0)
                return kFixEnabledDefault;

            // A sentinel default reliably detects a missing key: a present key
            // (even blank) never yields the sentinel byte.
            constexpr char kUnsetSentinel[] = "\x01__openshim_unset__";
            char value[64] = {};
            GetPrivateProfileStringA("Fixes", "CliMultiParameterOptions", kUnsetSentinel,
                                     value, static_cast<DWORD>(sizeof(value)), iniPath);
            if (value[0] == '\0' || std::strcmp(value, kUnsetSentinel) == 0)
                return kFixEnabledDefault;

            for (char* c = value; *c != '\0'; ++c)
                *c = static_cast<char>(std::tolower(static_cast<unsigned char>(*c)));

            return !(std::strcmp(value, "0") == 0 || std::strcmp(value, "false") == 0 ||
                     std::strcmp(value, "off") == 0 || std::strcmp(value, "no") == 0 ||
                     std::strcmp(value, "disabled") == 0);
        }
    }

    void ApplyCliMultiParameterOptionFix()
    {
        if (!ReadEnabledFromUserConfig())
            return;

        const uint32_t version = GetGameFileVersion();
        if (version != kExpectedGameVersion)
        {
            LogShimA(LogLevel::Warn, kLogTag,
                     "CLI multi-parameter fix not applied: exe version %u, expected %u",
                     version, kExpectedGameVersion);
            return;
        }

        // Idempotence: a second attach, or a build that already ships without
        // the comma, is a no-op rather than a warning.
        if (BytesMatch(kDelimiterAddr, kDelimiterRepaired, sizeof(kDelimiterRepaired)))
            return;

        if (!BytesMatch(kDelimiterAddr, kDelimiterStock, sizeof(kDelimiterStock)))
        {
            LogShimA(LogLevel::Warn, kLogTag,
                     "CLI multi-parameter fix not applied: delimiter guard mismatch at 0x%08X",
                     static_cast<unsigned>(kDelimiterAddr));
            return;
        }

        // Corroboration only. On Steam these read as SteamStub ciphertext at
        // DLL_PROCESS_ATTACH, which must not veto a .data-only write.
        const bool firstSiteOk = BytesMatch(kFirstTokenSiteAddr, kFirstTokenSiteExpected,
                                            sizeof(kFirstTokenSiteExpected));
        const bool nextSiteOk = BytesMatch(kNextTokenSiteAddr, kNextTokenSiteExpected,
                                           sizeof(kNextTokenSiteExpected));
        const bool formatSiteOk = BytesMatch(kShellmapFormatSiteAddr, kShellmapFormatSiteExpected,
                                             sizeof(kShellmapFormatSiteExpected)) &&
                                  BytesMatch(kShellmapFormatAddr, kShellmapFormatExpected,
                                             sizeof(kShellmapFormatExpected));

        if (!WriteDelimiters(kDelimiterRepaired))
        {
            LogShimA(LogLevel::Error, kLogTag,
                     "CLI multi-parameter fix not applied: write failed at 0x%08X",
                     static_cast<unsigned>(kDelimiterAddr));
            return;
        }

        s_applied = true;

        LogShimA(LogLevel::Info, kLogTag,
                 "CLI multi-parameter options repaired: strtok delimiters \" ,\\t\" -> \" \\t\" "
                 "at 0x%08X (text identity strtok1=%s strtok2=%s shellmapFormat=%s)",
                 static_cast<unsigned>(kDelimiterAddr),
                 firstSiteOk ? "ok" : "unverified",
                 nextSiteOk ? "ok" : "unverified",
                 formatSiteOk ? "ok" : "unverified");
    }

    void VerifyCliMultiParameterOptionFix()
    {
        if (!s_applied)
            return;

        // .text is readable by now on both stores, so the corroboration that
        // had to be skipped at attach can finally be settled. This is the only
        // place a Steam run proves the delimiter belongs to ProcessCommandLine.
        const bool firstSiteOk = BytesMatch(kFirstTokenSiteAddr, kFirstTokenSiteExpected,
                                            sizeof(kFirstTokenSiteExpected));
        const bool nextSiteOk = BytesMatch(kNextTokenSiteAddr, kNextTokenSiteExpected,
                                           sizeof(kNextTokenSiteExpected));
        const bool formatSiteOk = BytesMatch(kShellmapFormatSiteAddr, kShellmapFormatSiteExpected,
                                             sizeof(kShellmapFormatSiteExpected)) &&
                                  BytesMatch(kShellmapFormatAddr, kShellmapFormatExpected,
                                             sizeof(kShellmapFormatExpected));

        if (BytesMatch(kDelimiterAddr, kDelimiterRepaired, sizeof(kDelimiterRepaired)))
        {
            LogShimA(LogLevel::Info, kLogTag,
                     "CLI multi-parameter repair held after image settle "
                     "(text identity strtok1=%s strtok2=%s shellmapFormat=%s)",
                     firstSiteOk ? "ok" : "MISMATCH",
                     nextSiteOk ? "ok" : "MISMATCH",
                     formatSiteOk ? "ok" : "MISMATCH");
            return;
        }

        // Reverted. Nothing observed does this, but if a packer ever restores
        // .data over the write it must not fail silently: the command line has
        // almost certainly already been parsed by now, so re-applying only
        // helps a later re-parse. The log line is the real deliverable.
        if (BytesMatch(kDelimiterAddr, kDelimiterStock, sizeof(kDelimiterStock)))
        {
            const bool rewritten = WriteDelimiters(kDelimiterRepaired);
            LogShimA(LogLevel::Error, kLogTag,
                     "CLI multi-parameter repair was REVERTED at 0x%08X after attach; "
                     "the command line was likely already parsed with stock delimiters. "
                     "Re-applied=%s (text identity strtok1=%s strtok2=%s shellmapFormat=%s)",
                     static_cast<unsigned>(kDelimiterAddr),
                     rewritten ? "yes" : "no",
                     firstSiteOk ? "ok" : "MISMATCH",
                     nextSiteOk ? "ok" : "MISMATCH",
                     formatSiteOk ? "ok" : "MISMATCH");
            return;
        }

        LogShimA(LogLevel::Warn, kLogTag,
                 "CLI multi-parameter delimiters at 0x%08X are neither stock nor repaired "
                 "after image settle; leaving them alone",
                 static_cast<unsigned>(kDelimiterAddr));
    }
}
