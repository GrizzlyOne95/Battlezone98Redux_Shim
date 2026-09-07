// bzn_load_trace.cpp
// BZR Open Shim - mission (.bzn) load diagnostics
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// See include/bzn_load_trace.h for why this exists. The analysis itself is a
// pure function in include/bzn_analysis.h so it can be unit tested off-target;
// this file is only the file-open hook, the read, and the report.

#include "bzn_load_trace.h"

#include "bzn_analysis.h"
#include "bzr_options_ui.h"
#include "patcher.h"

#include <Windows.h>

#include <algorithm>
#include <string>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        // A mission is a few hundred KB. Anything past this is not a mission we
        // understand, and reading it would be the diagnostic causing a stall.
        constexpr size_t kMaxBznBytes = 16u * 1024u * 1024u;

        // Missions are opened more than once per session (shell preview, load,
        // restart). Bound the total so a long session cannot fill the log.
        constexpr int kMaxReportsPerProcess = 64;

        // The per-object table is the large part of the output. Cap it so an
        // unexpectedly large mission cannot produce a multi-megabyte log.
        constexpr size_t kMaxObjectRows = 4096;

        bool g_ConfigLoaded = false;
        bool g_Verbose = false;
        int g_ReportsEmitted = 0;

        // Separate budget from the reports themselves: an open that gets
        // filtered out still costs a line, and "the hook never ran" and "a
        // filter dropped it" have to be distinguishable in the log.
        constexpr int kMaxSeenLogs = 32;
        int g_SeenLogged = 0;

        // Reading the file re-enters the CreateFile hook that called us.
        // Per-thread so a background open cannot mask a real one on the main
        // thread.
        thread_local bool t_InTrace = false;

        void LoadConfig()
        {
            if (g_ConfigLoaded)
                return;
            g_ConfigLoaded = true;

            bool verbose = false;
            if (TryGetUserConfigBool("Diagnostics", "TraceBznLoad", verbose))
                g_Verbose = verbose;
            if (EnvFlagEnabled("OPENSHIM_TRACE_BZN_LOAD"))
                g_Verbose = true;
        }

        bool PathEndsWithBzn(const wchar_t* path)
        {
            if (!path)
                return false;
            const size_t len = wcslen(path);
            if (len < 4)
                return false;
            const wchar_t* ext = path + (len - 4);
            return (ext[0] == L'.') &&
                   (ext[1] == L'b' || ext[1] == L'B') &&
                   (ext[2] == L'z' || ext[2] == L'Z') &&
                   (ext[3] == L'n' || ext[3] == L'N');
        }

        const wchar_t* BaseName(const wchar_t* path)
        {
            const wchar_t* slash = wcsrchr(path, L'\\');
            const wchar_t* fwd = wcsrchr(path, L'/');
            if (fwd && (!slash || fwd > slash))
                slash = fwd;
            return slash ? slash + 1 : path;
        }

        bool ReadWholeFile(const wchar_t* path, std::vector<char>& out)
        {
            const HANDLE handle = CreateFileW(path, GENERIC_READ,
                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (handle == INVALID_HANDLE_VALUE)
                return false;

            LARGE_INTEGER size{};
            if (!GetFileSizeEx(handle, &size) || size.QuadPart <= 0 ||
                static_cast<unsigned long long>(size.QuadPart) > kMaxBznBytes)
            {
                CloseHandle(handle);
                return false;
            }

            out.resize(static_cast<size_t>(size.QuadPart));
            size_t offset = 0;
            while (offset < out.size())
            {
                DWORD read = 0;
                const DWORD want = static_cast<DWORD>(
                    (std::min)(static_cast<size_t>(1u << 20), out.size() - offset));
                if (!ReadFile(handle, out.data() + offset, want, &read, nullptr) || read == 0)
                    break;
                offset += read;
            }
            CloseHandle(handle);
            return offset == out.size();
        }

        // The reason this module exists: say plainly that the file is mixed, and
        // name the object the engine will stop on, so the log answers the
        // question instead of posing it.
        void ReportLineEndings(const BznAnalysis::Result& report, const wchar_t* name)
        {
            const auto& endings = report.endings;

            if (!endings.mixed())
            {
                Log(L"[BZNLOAD] %s line endings uniform (%zu %hs)\n",
                    name,
                    endings.crlf ? endings.crlf : endings.bareLf,
                    endings.crlf ? "CRLF" : "LF");
                return;
            }

            Log(L"[BZNLOAD] *** %s HAS MIXED LINE ENDINGS: %zu CRLF lines, %zu bare-LF lines\n",
                name, endings.crlf, endings.bareLf);
            Log(L"[BZNLOAD] *** The engine reads this file as CRLF lines, so a bare-LF run collapses\n");
            Log(L"[BZNLOAD] *** into one unparseable line and object loading stops there.\n");

            if (report.mixedEnclosingObject != BznAnalysis::kNone)
            {
                const auto& rec = report.objects[report.mixedEnclosingObject];
                Log(L"[BZNLOAD] *** First bare LF is line %zu, inside GameObject #%zu "
                    L"(PrjID=%hs label=%hs). Expect the load to stop at obj #%zu.\n",
                    endings.firstBareLine, rec.index,
                    rec.prjId.empty() ? "?" : rec.prjId.c_str(),
                    rec.label.empty() ? "?" : rec.label.c_str(),
                    rec.index);
            }
            else
            {
                Log(L"[BZNLOAD] *** First bare LF is line %zu, before the first GameObject.\n",
                    endings.firstBareLine);
            }

            Log(L"[BZNLOAD] *** Fix: rewrite with uniform CRLF. Under git the file may still report\n");
            Log(L"[BZNLOAD] *** as unmodified, because autocrlf normalizes it to the same blob --\n");
            Log(L"[BZNLOAD] *** restore it with: rm <file> && git checkout -- <file>\n");
        }

        void EmitReport(const wchar_t* path, const std::vector<char>& data)
        {
            const wchar_t* name = BaseName(path);
            const BznAnalysis::Result report =
                BznAnalysis::Analyze(std::string_view(data.data(), data.size()));

            Log(L"[BZNLOAD] %s: %zu bytes, %zu lines, format=%hs version=%hs terrain=%hs\n",
                name, data.size(), report.lineCount,
                report.ascii ? "ascii" : "binary/unknown",
                report.version.empty() ? "?" : report.version.c_str(),
                report.terrainName.empty() ? "?" : report.terrainName.c_str());

            if (!report.ascii)
            {
                // A binary save has no line structure to check and no readable
                // object table; saying so beats reporting nothing.
                Log(L"[BZNLOAD] %s is not an ascii save; structural checks skipped\n", name);
                return;
            }

            Log(L"[BZNLOAD] %s: %zu GameObject blocks, %zu AiPath blocks (declared %hs), seq_count=%hs\n",
                name, report.objects.size(), report.pathBlocks,
                report.declaredPathCount.empty() ? "?" : report.declaredPathCount.c_str(),
                report.seqCount.empty() ? "?" : report.seqCount.c_str());

            ReportLineEndings(report, name);

            for (const std::string& problem : report.problems)
                Log(L"[BZNLOAD] *** %s: %hs\n", name, problem.c_str());

            if (report.problems.empty() && !report.endings.mixed())
                Log(L"[BZNLOAD] %s structural checks passed\n", name);

            if (!g_Verbose)
            {
                Log(L"[BZNLOAD] %s object table suppressed; set [Diagnostics] TraceBznLoad=1 to list "
                    L"every object by index\n", name);
                return;
            }

            const size_t rows = (std::min)(report.objects.size(), kMaxObjectRows);
            for (size_t i = 0; i < rows; ++i)
            {
                const auto& rec = report.objects[i];
                Log(L"[BZNLOAD]   obj #%zu PrjID=%hs label=%hs team=%hs seqno=%hs addr=%hs\n",
                    rec.index,
                    rec.prjId.empty() ? "?" : rec.prjId.c_str(),
                    rec.label.empty() ? "?" : rec.label.c_str(),
                    rec.team.empty() ? "?" : rec.team.c_str(),
                    rec.seqno.empty() ? "?" : rec.seqno.c_str(),
                    rec.objAddr.empty() ? "?" : rec.objAddr.c_str());
            }
            if (rows < report.objects.size())
                Log(L"[BZNLOAD]   ... %zu further objects not listed\n", report.objects.size() - rows);
        }

        // Everything with a destructor lives here: MSVC refuses __try in a
        // function that requires object unwinding, so the SEH frame below can
        // hold no C++ objects of its own.
        void TraceBody(const wchar_t* path)
        {
            std::vector<char> data;
            if (!ReadWholeFile(path, data) || data.empty())
                return;
            g_ReportsEmitted++;
            EmitReport(path, data);
        }
    }

    bool IsBznLoadTraceVerbose() noexcept
    {
        LoadConfig();
        return g_Verbose;
    }

    void BznLoadTraceOnOpenA(const char* absolutePath, uint32_t desiredAccess) noexcept
    {
        if (t_InTrace || !absolutePath || !absolutePath[0])
            return;

        const int wide = MultiByteToWideChar(CP_ACP, 0, absolutePath, -1, nullptr, 0);
        if (wide <= 0 || wide > MAX_PATH * 4)
            return;

        std::wstring converted(static_cast<size_t>(wide), L'\0');
        if (MultiByteToWideChar(CP_ACP, 0, absolutePath, -1, converted.data(), wide) <= 0)
            return;
        converted.resize(static_cast<size_t>(wide) - 1);

        BznLoadTraceOnOpen(converted.c_str(), desiredAccess);
    }

    void BznLoadTraceOnOpen(const wchar_t* absolutePath, uint32_t desiredAccess) noexcept
    {
        if (t_InTrace)
            return;
        if (!absolutePath || !absolutePath[0])
            return;
        if (!PathEndsWithBzn(absolutePath))
            return;

        LoadConfig();

        // Record the open before any filter can drop it, so a missing report is
        // never ambiguous between "the hook did not run" and "the hook ran and
        // skipped it".
        if (g_SeenLogged < kMaxSeenLogs)
        {
            g_SeenLogged++;
            Log(L"[BZNLOAD] open %s access=0x%08X%hs\n",
                BaseName(absolutePath),
                desiredAccess,
                (desiredAccess & GENERIC_WRITE) ? " (write; not analysed)" : "");
        }

        if ((desiredAccess & GENERIC_WRITE) != 0)
            return;  // the editor save path owns writes
        if (g_ReportsEmitted >= kMaxReportsPerProcess)
            return;

        // A C++ catch would not see an access violation under /EHsc, and this
        // parses a file that is by definition suspect. Guard it with SEH so a
        // malformed mission is reported rather than turned into a crash.
        t_InTrace = true;
        __try
        {
            TraceBody(absolutePath);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            // A diagnostic must never be the reason a mission fails to load.
        }
        t_InTrace = false;
    }
}
