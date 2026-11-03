// troubleshooting_bundle.cpp
// BZR Open Shim - the Options "Build Troubleshooting Bundle" action.
//
// Kernel32 only (plus ntdll by GetProcAddress), so it adds no import and works
// the same under Wine/Proton. See troubleshooting_bundle.h for the contract.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "troubleshooting_bundle.h"

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <cwchar>

namespace BZROpenShim
{
    namespace
    {
        constexpr uint64_t kMaxLogBytes = 64ull * 1024 * 1024;
        constexpr uint64_t kMaxDumpBytes = 256ull * 1024 * 1024;
        // Leaves the archive well inside the 4 GB stored-zip limit.
        constexpr uint64_t kMaxBundleBytes = 768ull * 1024 * 1024;

        // Files beside the exe that describe the install and its settings.
        const wchar_t* const kRootFiles[] = {
            L"openshim.ini", L"net.ini", L"multi.ini", L"Ogre.cfg", L"bz_plugins.cfg",
            L"bz_resources.cfg", L"bzloader.log", L"netcode_manifest.json",
            L"campaignReimagined_settings.cfg", L"scripts\\patches.json",
        };

        // Text logs in logs\ are included by extension; dumps are picked separately.
        const wchar_t* const kLogExtensions[] = { L".log", L".txt", L".json", L".jsonl", L".csv" };

        bool EndsWithNoCase(const std::wstring& text, const wchar_t* suffix)
        {
            const size_t n = std::wcslen(suffix);
            return text.size() >= n && _wcsicmp(text.c_str() + text.size() - n, suffix) == 0;
        }

        std::string Narrow(const std::wstring& text)
        {
            if (text.empty())
                return {};
            const int length = WideCharToMultiByte(CP_UTF8, 0, text.c_str(), static_cast<int>(text.size()),
                                                   nullptr, 0, nullptr, nullptr);
            std::string out(static_cast<size_t>(std::max(length, 0)), '\0');
            if (length > 0)
                WideCharToMultiByte(CP_UTF8, 0, text.c_str(), static_cast<int>(text.size()), out.data(),
                                    length, nullptr, nullptr);
            return out;
        }

        std::string ZipName(const std::wstring& relative)
        {
            std::string name = Narrow(relative);
            std::replace(name.begin(), name.end(), '\\', '/');
            return name;
        }

        void AppendF(std::string& out, const char* fmt, ...)
        {
            char buffer[1024];
            va_list args;
            va_start(args, fmt);
            const int n = std::vsnprintf(buffer, sizeof(buffer), fmt, args);
            va_end(args);
            if (n > 0)
                out.append(buffer, static_cast<size_t>(std::min(n, static_cast<int>(sizeof(buffer) - 1))));
        }

        std::wstring GameRoot()
        {
            wchar_t path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameW(nullptr, path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return {};
            wchar_t* slash = std::wcsrchr(path, L'\\');
            if (!slash)
                return {};
            slash[1] = L'\0';
            return path;
        }

        bool QueryFile(const std::wstring& path, uint64_t& size, FILETIME& written)
        {
            WIN32_FILE_ATTRIBUTE_DATA data = {};
            if (!GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &data) ||
                (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
                return false;
            size = (static_cast<uint64_t>(data.nFileSizeHigh) << 32) | data.nFileSizeLow;
            written = data.ftLastWriteTime;
            return true;
        }

        std::string FormatFileTime(const FILETIME& time)
        {
            SYSTEMTIME utc = {};
            if (!FileTimeToSystemTime(&time, &utc))
                return "?";
            char text[32];
            std::snprintf(text, sizeof(text), "%04u-%02u-%02u %02u:%02u:%02u UTC", utc.wYear, utc.wMonth,
                          utc.wDay, utc.wHour, utc.wMinute, utc.wSecond);
            return text;
        }

        void AppendSystemInfo(std::string& out, const std::wstring& root)
        {
            using RtlGetVersionFn = LONG(WINAPI*)(OSVERSIONINFOW*);
            using WineGetVersionFn = const char*(__cdecl*)();
            HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
            OSVERSIONINFOW version = { sizeof(version) };
            const auto rtlGetVersion =
                ntdll ? reinterpret_cast<RtlGetVersionFn>(GetProcAddress(ntdll, "RtlGetVersion")) : nullptr;
            if (rtlGetVersion && rtlGetVersion(&version) == 0)
                AppendF(out, "Windows: %lu.%lu build %lu\n", version.dwMajorVersion, version.dwMinorVersion,
                        version.dwBuildNumber);
            const auto wineGetVersion =
                ntdll ? reinterpret_cast<WineGetVersionFn>(GetProcAddress(ntdll, "wine_get_version")) : nullptr;
            AppendF(out, "Wine/Proton: %s\n", wineGetVersion ? wineGetVersion() : "no");
            AppendF(out, "Game folder: %s\n", Narrow(root).c_str());
            AppendF(out, "Command line: %s\n", Narrow(GetCommandLineW()).c_str());

            // Identity of the shim and loader on disk: a stale copy is a common cause.
            const wchar_t* const binaries[] = { L"winmm.dll", L"bzloader.dll", L"battlezone98redux.exe" };
            for (const wchar_t* binary : binaries)
            {
                uint64_t size = 0;
                FILETIME written = {};
                if (QueryFile(root + binary, size, written))
                    AppendF(out, "%s: %llu bytes, modified %s\n", Narrow(binary).c_str(),
                            static_cast<unsigned long long>(size), FormatFileTime(written).c_str());
                else
                    AppendF(out, "%s: not found\n", Narrow(binary).c_str());
            }
        }
    }

    uint32_t Crc32Update(uint32_t crc, const void* data, size_t length)
    {
        static uint32_t table[256] = {};
        static const bool built = [] {
            for (uint32_t i = 0; i < 256; ++i)
            {
                uint32_t c = i;
                for (int k = 0; k < 8; ++k)
                    c = (c & 1) ? 0xEDB88320u ^ (c >> 1) : c >> 1;
                table[i] = c;
            }
            return true;
        }();
        (void)built;
        const auto* bytes = static_cast<const unsigned char*>(data);
        crc = ~crc;
        for (size_t i = 0; i < length; ++i)
            crc = table[(crc ^ bytes[i]) & 0xFF] ^ (crc >> 8);
        return ~crc;
    }

    StoreZipWriter::~StoreZipWriter()
    {
        if (m_file != INVALID_HANDLE_VALUE)
            CloseHandle(m_file);
    }

    bool StoreZipWriter::Open(const std::wstring& path)
    {
        m_file = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
                             nullptr);
        if (m_file == INVALID_HANDLE_VALUE)
            return false;
        SYSTEMTIME now = {};
        GetLocalTime(&now);
        m_dosTime = static_cast<uint16_t>((now.wHour << 11) | (now.wMinute << 5) | (now.wSecond / 2));
        m_dosDate = static_cast<uint16_t>(((std::max<int>(now.wYear, 1980) - 1980) << 9) | (now.wMonth << 5) |
                                          now.wDay);
        return true;
    }

    bool StoreZipWriter::Write(const void* data, size_t length)
    {
        if (m_failed)
            return false;
        DWORD written = 0;
        if (!WriteFile(m_file, data, static_cast<DWORD>(length), &written, nullptr) || written != length)
        {
            m_failed = true;
            return false;
        }
        m_offset += length;
        return true;
    }

    namespace
    {
        void Put16(unsigned char* p, uint16_t v) { p[0] = static_cast<unsigned char>(v); p[1] = static_cast<unsigned char>(v >> 8); }
        void Put32(unsigned char* p, uint32_t v)
        {
            for (int i = 0; i < 4; ++i)
                p[i] = static_cast<unsigned char>(v >> (8 * i));
        }
    }

    bool StoreZipWriter::BeginEntry(const std::string& name, Entry& entry)
    {
        if (m_file == INVALID_HANDLE_VALUE || m_failed || name.empty() || name.size() > 0xFFFF ||
            m_offset > 0xFFFFFFFFull)
            return false;
        entry.name = name;
        entry.offset = static_cast<uint32_t>(m_offset);
        unsigned char header[30] = {};
        Put32(header, 0x04034B50u);
        Put16(header + 4, 10);  // version needed: stored
        Put16(header + 6, 0x0800);  // UTF-8 names
        Put16(header + 10, m_dosTime);
        Put16(header + 12, m_dosDate);
        Put16(header + 26, static_cast<uint16_t>(name.size()));
        return Write(header, sizeof(header)) && Write(name.data(), name.size());
    }

    bool StoreZipWriter::FinishEntry(Entry& entry)
    {
        if (m_failed || m_offset > 0xFFFFFFFFull)
        {
            m_failed = true;
            return false;
        }
        // Patch crc and sizes into the local header, then return to the end.
        unsigned char fields[12];
        Put32(fields, entry.crc);
        Put32(fields + 4, entry.size);
        Put32(fields + 8, entry.size);
        LARGE_INTEGER at = {};
        at.QuadPart = static_cast<LONGLONG>(entry.offset) + 14;
        DWORD written = 0;
        LARGE_INTEGER end = {};
        end.QuadPart = static_cast<LONGLONG>(m_offset);
        if (!SetFilePointerEx(m_file, at, nullptr, FILE_BEGIN) ||
            !WriteFile(m_file, fields, sizeof(fields), &written, nullptr) || written != sizeof(fields) ||
            !SetFilePointerEx(m_file, end, nullptr, FILE_BEGIN))
        {
            m_failed = true;
            return false;
        }
        m_entries.push_back(entry);
        return true;
    }

    bool StoreZipWriter::AddBytes(const std::string& name, const void* data, size_t length)
    {
        Entry entry;
        if (!BeginEntry(name, entry) || !Write(data, length))
            return false;
        entry.crc = Crc32Update(0, data, length);
        entry.size = static_cast<uint32_t>(length);
        return FinishEntry(entry);
    }

    bool StoreZipWriter::AddFile(const std::string& name, const std::wstring& source, uint64_t maxBytes,
                                 uint64_t& copiedBytes, uint64_t& sourceBytes)
    {
        copiedBytes = 0;
        sourceBytes = 0;
        // Share everything: the shim log and the engine logs are still open for writing.
        HANDLE input = CreateFileW(source.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                   nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
        if (input == INVALID_HANDLE_VALUE)
            return false;
        LARGE_INTEGER size = {};
        if (!GetFileSizeEx(input, &size))
        {
            CloseHandle(input);
            return false;
        }
        sourceBytes = static_cast<uint64_t>(size.QuadPart);
        const uint64_t want = std::min(sourceBytes, maxBytes);
        if (want < sourceBytes)
        {
            LARGE_INTEGER start = {};
            start.QuadPart = static_cast<LONGLONG>(sourceBytes - want);
            if (!SetFilePointerEx(input, start, nullptr, FILE_BEGIN))
            {
                CloseHandle(input);
                return false;
            }
        }

        Entry entry;
        bool ok = BeginEntry(name, entry);
        std::vector<unsigned char> buffer(1 << 20);
        uint32_t crc = 0;
        while (ok && copiedBytes < want)
        {
            const DWORD chunk = static_cast<DWORD>(std::min<uint64_t>(buffer.size(), want - copiedBytes));
            DWORD read = 0;
            if (!ReadFile(input, buffer.data(), chunk, &read, nullptr) || read == 0)
                break;  // the file shrank while we read it; keep what we have
            crc = Crc32Update(crc, buffer.data(), read);
            ok = Write(buffer.data(), read);
            copiedBytes += read;
        }
        CloseHandle(input);
        if (!ok)
            return false;
        entry.crc = crc;
        entry.size = static_cast<uint32_t>(copiedBytes);
        return FinishEntry(entry);
    }

    bool StoreZipWriter::Close()
    {
        if (m_file == INVALID_HANDLE_VALUE)
            return false;
        const uint64_t directoryStart = m_offset;
        for (const Entry& entry : m_entries)
        {
            unsigned char header[46] = {};
            Put32(header, 0x02014B50u);
            Put16(header + 4, 20);
            Put16(header + 6, 10);
            Put16(header + 8, 0x0800);
            Put16(header + 12, m_dosTime);
            Put16(header + 14, m_dosDate);
            Put32(header + 16, entry.crc);
            Put32(header + 20, entry.size);
            Put32(header + 24, entry.size);
            Put16(header + 28, static_cast<uint16_t>(entry.name.size()));
            Put32(header + 42, entry.offset);
            if (!Write(header, sizeof(header)) || !Write(entry.name.data(), entry.name.size()))
                break;
        }
        const uint64_t directoryBytes = m_offset - directoryStart;
        bool ok = !m_failed && m_entries.size() <= 0xFFFF && m_offset <= 0xFFFFFFFFull;
        if (ok)
        {
            unsigned char end[22] = {};
            Put32(end, 0x06054B50u);
            Put16(end + 8, static_cast<uint16_t>(m_entries.size()));
            Put16(end + 10, static_cast<uint16_t>(m_entries.size()));
            Put32(end + 12, static_cast<uint32_t>(directoryBytes));
            Put32(end + 16, static_cast<uint32_t>(directoryStart));
            ok = Write(end, sizeof(end));
        }
        CloseHandle(m_file);
        m_file = INVALID_HANDLE_VALUE;
        return ok;
    }

    TroubleshootingBundleResult BuildTroubleshootingBundle()
    {
        TroubleshootingBundleResult result;
        const std::wstring root = GameRoot();
        if (root.empty())
        {
            result.error = "could not find the game folder";
            return result;
        }
        const std::wstring logs = root + L"logs\\";
        CreateDirectoryW(logs.c_str(), nullptr);

        SYSTEMTIME now = {};
        GetLocalTime(&now);
        wchar_t stamp[32];
        std::swprintf(stamp, 32, L"%04u%02u%02u_%02u%02u%02u", now.wYear, now.wMonth, now.wDay, now.wHour,
                      now.wMinute, now.wSecond);
        result.zipPath = logs + L"OpenShim_Troubleshooting_" + stamp + L".zip";
        const std::wstring partial = result.zipPath + L".partial";

        StoreZipWriter zip;
        if (!zip.Open(partial))
        {
            result.error = "could not create the zip in logs\\ (error " + std::to_string(GetLastError()) + ")";
            return result;
        }

        std::string manifest;
        AppendF(manifest, "OpenShim troubleshooting bundle, %04u-%02u-%02u %02u:%02u:%02u local\n\n", now.wYear,
                now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);
        AppendSystemInfo(manifest, root);
        manifest += "\nFiles:\n";

        auto add = [&](const std::wstring& relative, uint64_t cap) {
            const std::wstring source = root + relative;
            uint64_t size = 0;
            FILETIME written = {};
            if (!QueryFile(source, size, written))
                return;
            if (zip.BytesWritten() + std::min(size, cap) > kMaxBundleBytes)
            {
                AppendF(manifest, "  SKIPPED (bundle size cap) %s, %llu bytes\n", ZipName(relative).c_str(),
                        static_cast<unsigned long long>(size));
                return;
            }
            uint64_t copied = 0;
            uint64_t total = 0;
            if (zip.AddFile(ZipName(relative), source, cap, copied, total))
            {
                ++result.fileCount;
                AppendF(manifest, "  %s, %llu bytes, modified %s%s\n", ZipName(relative).c_str(),
                        static_cast<unsigned long long>(total), FormatFileTime(written).c_str(),
                        copied == total ? "" : copied < std::min(total, cap) ? " (SHORT: file shrank while read)"
                                                                             : " (TRUNCATED: last part only)");
            }
            else if (!zip.Failed())
            {
                AppendF(manifest, "  UNREADABLE %s (error %lu)\n", ZipName(relative).c_str(), GetLastError());
            }
        };

        for (const wchar_t* file : kRootFiles)
            add(file, kMaxLogBytes);

        // logs\: every text log, plus only the newest crash dump (dumps run
        // to hundreds of MB each and older ones rarely matter).
        std::wstring newestDump;
        FILETIME newestDumpTime = {};
        uint64_t olderDumps = 0;
        WIN32_FIND_DATAW found = {};
        HANDLE search = FindFirstFileW((logs + L"*").c_str(), &found);
        if (search != INVALID_HANDLE_VALUE)
        {
            do
            {
                if ((found.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
                    continue;
                const std::wstring name = found.cFileName;
                if (EndsWithNoCase(name, L".dmp"))
                {
                    if (newestDump.empty() || CompareFileTime(&found.ftLastWriteTime, &newestDumpTime) > 0)
                    {
                        if (!newestDump.empty())
                            ++olderDumps;
                        newestDump = name;
                        newestDumpTime = found.ftLastWriteTime;
                    }
                    else
                    {
                        ++olderDumps;
                    }
                    continue;
                }
                for (const wchar_t* extension : kLogExtensions)
                {
                    if (EndsWithNoCase(name, extension))
                    {
                        add(L"logs\\" + name, kMaxLogBytes);
                        break;
                    }
                }
            } while (!zip.Failed() && FindNextFileW(search, &found));
            FindClose(search);
        }

        if (!newestDump.empty())
        {
            uint64_t size = 0;
            FILETIME written = {};
            if (QueryFile(logs + newestDump, size, written) && size > kMaxDumpBytes)
                AppendF(manifest, "  SKIPPED (over %llu MB) logs/%s, %llu bytes\n",
                        static_cast<unsigned long long>(kMaxDumpBytes >> 20), Narrow(newestDump).c_str(),
                        static_cast<unsigned long long>(size));
            else
                add(L"logs\\" + newestDump, kMaxDumpBytes);
        }
        if (olderDumps > 0)
            AppendF(manifest, "  (%llu older crash dump(s) left out)\n", static_cast<unsigned long long>(olderDumps));

        const bool manifestOk = zip.AddBytes("summary.txt", manifest.data(), manifest.size());
        result.zipBytes = zip.BytesWritten();
        if (!zip.Close() || !manifestOk)
        {
            result.error = "writing the zip failed (disk full?)";
            DeleteFileW(partial.c_str());
            return result;
        }
        if (!MoveFileExW(partial.c_str(), result.zipPath.c_str(), MOVEFILE_REPLACE_EXISTING))
        {
            result.error = "could not finish the zip (error " + std::to_string(GetLastError()) + ")";
            DeleteFileW(partial.c_str());
            return result;
        }
        result.ok = true;
        return result;
    }

    bool RunningUnderWine()
    {
        HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
        return ntdll != nullptr && GetProcAddress(ntdll, "wine_get_version") != nullptr;
    }

    std::string HostPathForDisplay(const std::wstring& path)
    {
        // Wine's kernel32 export; the result is allocated on the process heap.
        using WineGetUnixFileNameFn = char*(__cdecl*)(const wchar_t*);
        HMODULE kernel = GetModuleHandleW(L"kernel32.dll");
        const auto toUnix = kernel ? reinterpret_cast<WineGetUnixFileNameFn>(
                                         GetProcAddress(kernel, "wine_get_unix_file_name"))
                                   : nullptr;
        if (!toUnix)
            return {};
        char* unixPath = toUnix(path.c_str());
        if (!unixPath)
            return {};
        std::string out = unixPath;
        HeapFree(GetProcessHeap(), 0, unixPath);
        return out;
    }

    void RevealTroubleshootingBundle(const std::wstring& zipPath)
    {
        if (RunningUnderWine())
            return;
        // Explorer taking focus from a fullscreen game can minimize it or lose
        // the D3D device; the status line already names the file.
        HWND foreground = GetForegroundWindow();
        DWORD owner = 0;
        if (foreground)
            GetWindowThreadProcessId(foreground, &owner);
        if (owner == GetCurrentProcessId())
        {
            RECT window = {};
            MONITORINFO monitor = { sizeof(monitor) };
            if (GetWindowRect(foreground, &window) &&
                GetMonitorInfoW(MonitorFromWindow(foreground, MONITOR_DEFAULTTONEAREST), &monitor) &&
                EqualRect(&window, &monitor.rcMonitor))
                return;
        }
        wchar_t windows[MAX_PATH] = {};
        const UINT length = GetWindowsDirectoryW(windows, MAX_PATH);
        if (length == 0 || length >= MAX_PATH)
            return;
        const std::wstring explorer = std::wstring(windows) + L"\\explorer.exe";
        std::wstring command = L"\"" + explorer + L"\" /select,\"" + zipPath + L"\"";
        STARTUPINFOW startup = { sizeof(startup) };
        PROCESS_INFORMATION process = {};
        if (CreateProcessW(explorer.c_str(), command.data(), nullptr, nullptr, FALSE, 0, nullptr, nullptr,
                           &startup, &process))
        {
            CloseHandle(process.hThread);
            CloseHandle(process.hProcess);
        }
    }
}
