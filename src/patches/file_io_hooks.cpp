// file_io_hooks.cpp
// BZR Open Shim - automatic TRN save normalization hooks
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "file_io_hooks.h"

#include "bootstrap_file_io.h"

#include "bzn_load_trace.h"
#include "bzn_save_path.h"
#include "patcher.h"
#include "hook_engine.h"
#include "shim_log.h"
#include "ogre_shader_cache.h"
#include "ui_performance.h"
#include "trn_codec.h"
#include "terrain_atlas_rect_repair.h"

#include <Windows.h>

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cwctype>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
    using PFN_CloseHandle = BOOL(WINAPI*)(HANDLE);
    using PFN_MoveFileExA = BOOL(WINAPI*)(LPCSTR, LPCSTR, DWORD);
    using PFN_MoveFileExW = BOOL(WINAPI*)(LPCWSTR, LPCWSTR, DWORD);

    static PFN_CloseHandle g_RealCloseHandle = nullptr;
    static PFN_MoveFileExA g_RealMoveFileExA = nullptr;
    static PFN_MoveFileExW g_RealMoveFileExW = nullptr;

    namespace
    {
        struct TrnWriteRecord
        {
            std::wstring path;
        };

        static std::mutex g_TrnWriteMutex;
        static std::unordered_map<uintptr_t, TrnWriteRecord> g_TrnWriteHandles;
        static std::mutex g_BznSourceMutex;
        static BznSourceRegistry g_BznSources;
        using EditorSaveDialog = bool(__thiscall*)(void*, char*, bool);
        static EditorSaveDialog g_OriginalEditorSaveDialog = nullptr;
        static thread_local bool g_InTrnNormalization = false;
        static std::wstring ToLowerWide(std::wstring value);

        // Cheap case-insensitive ".program" suffix test used to trigger the
        // Ogre microcode cache before the resource-group parser compiles the
        // mod's GPU programs. Kept tiny because it runs on every file open.
        static bool PathEndsWithProgramW(const wchar_t* path)
        {
            if (!path)
                return false;
            size_t len = 0;
            while (path[len])
                ++len;
            static const wchar_t kSuffix[] = L".program";
            constexpr size_t kSuffixLen = 8; // wcslen(".program")
            if (len < kSuffixLen)
                return false;
            const wchar_t* tail = path + (len - kSuffixLen);
            for (size_t i = 0; i < kSuffixLen; ++i)
            {
                if (::towlower(tail[i]) != kSuffix[i])
                    return false;
            }
            return true;
        }

        static bool PathEndsWithProgramA(const char* path)
        {
            if (!path)
                return false;
            size_t len = 0;
            while (path[len])
                ++len;
            static const char kSuffix[] = ".program";
            constexpr size_t kSuffixLen = 8;
            if (len < kSuffixLen)
                return false;
            const char* tail = path + (len - kSuffixLen);
            for (size_t i = 0; i < kSuffixLen; ++i)
            {
                if (static_cast<char>(::tolower(static_cast<unsigned char>(tail[i]))) != kSuffix[i])
                    return false;
            }
            return true;
        }


        // ------------------------------------------------------------------
        // Terrain detail-atlas rect repair.
        //
        // Two of Redux's eleven `<xx>_detail_atlas.csv` files place a tile
        // rectangle off the atlas grid (0.825 where every sibling row uses
        // 0.875), so that tile samples across a cell boundary and renders half
        // of the wrong texture. See terrain_atlas_rect_repair.h for the
        // evidence and the conditions under which a file is touched at all.
        //
        // The correction happens here, at the open, rather than by patching the
        // parsed rect table: the atlas parser is a private native method that
        // would need an address, a byte guard and a layout assumption, whereas
        // the file open is a public ABI already hooked for TRN normalization.
        // Redux is handed a path to a corrected copy under the shim's own
        // directory; the shipped file is never written to.
        // ------------------------------------------------------------------
        static thread_local bool g_InAtlasRepair = false;

        // Read through GetEnvironmentVariableA rather than EnvFlagEnabled, as
        // BznSourceSaveEnabled above does: openshim_env_config.h is force
        // included, so this name already resolves the [Fixes] key first, and
        // it keeps this TU free of the hook module that EnvFlagEnabled lives
        // in -- which editor_save_dialog_win32_tests compiles without.
        static bool TerrainAtlasRectRepairEnabled()
        {
            static const bool enabled = []
            {
                char value[8] = {};
                for (const char* name : { "OPENSHIM_TERRAIN_ATLAS_RECT_REPAIR",
                                          "BZR_TERRAIN_ATLAS_RECT_REPAIR" })
                {
                    if (GetEnvironmentVariableA(name, value, static_cast<DWORD>(sizeof(value))) == 1 &&
                        value[0] == '1')
                    {
                        return true;
                    }
                }
                return false;
            }();
            return enabled;
        }

        static std::filesystem::path GetRepairedAtlasDirectory()
        {
            static const std::filesystem::path dir = []
            {
                std::vector<wchar_t> modulePath(32768, L'\0');
                const DWORD written = GetModuleFileNameW(
                    nullptr, modulePath.data(), static_cast<DWORD>(modulePath.size()));
                if (written == 0 || written >= modulePath.size())
                    return std::filesystem::path{};
                return std::filesystem::path(
                           std::wstring(modulePath.data(), modulePath.data() + written))
                           .parent_path() / L"openshim" / L"_generated" / L"atlas";
            }();
            return dir;
        }

        // Writes are never redirected, and neither is anything but a plain
        // open of an existing file: a create/truncate of one of these names is
        // somebody authoring an atlas, and must reach the real path.
        static bool IsPlainReadOpen(DWORD desiredAccess, DWORD creationDisposition)
        {
            constexpr DWORD kWriteBits =
                GENERIC_WRITE | GENERIC_ALL | FILE_WRITE_DATA | FILE_APPEND_DATA;
            if ((desiredAccess & kWriteBits) != 0)
                return false;
            return creationDisposition == OPEN_EXISTING;
        }

        static std::wstring RepairedAtlasPathFor(const std::wstring& requested)
        {
            static std::mutex mutex;
            static std::unordered_map<std::wstring, std::wstring> cache;

            const std::wstring key = ToLowerWide(requested);
            {
                std::lock_guard<std::mutex> lock(mutex);
                const auto found = cache.find(key);
                if (found != cache.end())
                    return found->second;  // empty means "use the original"
            }

            std::wstring replacement;  // stays empty on every failure path
            {
                // Our own read and write go back through these hooks; without
                // this the first open would recurse into itself.
                g_InAtlasRepair = true;

                std::string text;
                {
                    std::ifstream in(requested, std::ios::binary);
                    if (in)
                    {
                        std::ostringstream buffer;
                        buffer << in.rdbuf();
                        text = buffer.str();
                    }
                }

                TerrainAtlas::RepairReport report;
                std::string repaired;
                const bool changed =
                    !text.empty() && TerrainAtlas::RepairAtlasCsv(text, repaired, report);

                if (changed)
                {
                    const std::filesystem::path dir = GetRepairedAtlasDirectory();
                    std::error_code ec;
                    if (!dir.empty())
                        std::filesystem::create_directories(dir, ec);
                    if (!dir.empty() && !ec)
                    {
                        const std::filesystem::path out =
                            dir / std::filesystem::path(requested).filename();
                        std::ofstream stream(out, std::ios::binary | std::ios::trunc);
                        if (stream)
                        {
                            stream.write(repaired.data(),
                                         static_cast<std::streamsize>(repaired.size()));
                            if (stream.good())
                                replacement = out.wstring();
                        }
                    }
                }

                Log(L"[ATLASFIX] %ls outcome=%hs rows=%u offGrid=%u redirected=%hs\n",
                    requested.c_str(),
                    TerrainAtlas::RepairOutcomeName(report.outcome),
                    static_cast<unsigned>(report.dataRows),
                    static_cast<unsigned>(report.offGridRows),
                    replacement.empty() ? "no" : "yes");
                for (const TerrainAtlas::RepairedRow& row : report.repairs)
                {
                    Log(L"[ATLASFIX]   line %u %hs %c %.4f -> %.4f\n",
                        static_cast<unsigned>(row.lineNumber),
                        row.name.empty() ? "<unnamed>" : row.name.c_str(),
                        row.axis,
                        row.from,
                        row.to);
                }

                g_InAtlasRepair = false;
            }

            std::lock_guard<std::mutex> lock(mutex);
            cache[key] = replacement;
            return replacement;
        }

        static std::wstring RouteTerrainAtlasPath(const std::wstring& requested,
                                                  DWORD desiredAccess,
                                                  DWORD creationDisposition)
        {
            if (requested.empty() || g_InAtlasRepair || !TerrainAtlasRectRepairEnabled())
                return requested;
            if (!IsPlainReadOpen(desiredAccess, creationDisposition))
                return requested;

            // The name test is ASCII-only, so narrow it here rather than via
            // path::string(), which can throw on a path the active codepage
            // cannot represent. Any non-ASCII unit becomes '?' and simply
            // fails to match.
            const std::wstring wideLeaf = std::filesystem::path(requested).filename().wstring();
            std::string leaf;
            leaf.reserve(wideLeaf.size());
            for (wchar_t ch : wideLeaf)
                leaf.push_back(ch < 128 ? static_cast<char>(ch) : '?');
            if (!TerrainAtlas::IsDetailAtlasCsvName(leaf))
                return requested;

            const std::wstring replacement = RepairedAtlasPathFor(requested);
            return replacement.empty() ? requested : replacement;
        }

        // ANSI callers get the same treatment. The replacement always lives
        // under the game directory, so it normally round-trips through the
        // active codepage; if it cannot, the original path is used and the
        // only cost is that this one open is not corrected.
        static std::string RouteTerrainAtlasPath(const std::string& requested,
                                                 DWORD desiredAccess,
                                                 DWORD creationDisposition)
        {
            if (requested.empty() || g_InAtlasRepair || !TerrainAtlasRectRepairEnabled())
                return requested;
            if (!IsPlainReadOpen(desiredAccess, creationDisposition))
                return requested;

            const int wideCount =
                MultiByteToWideChar(CP_ACP, 0, requested.c_str(), -1, nullptr, 0);
            if (wideCount <= 1)
                return requested;
            std::wstring wide(static_cast<size_t>(wideCount), L'\0');
            MultiByteToWideChar(CP_ACP, 0, requested.c_str(), -1, wide.data(), wideCount);
            wide.pop_back();

            const std::wstring routed =
                RouteTerrainAtlasPath(wide, desiredAccess, creationDisposition);
            if (routed == wide)
                return requested;

            BOOL unconvertible = FALSE;
            const int byteCount = WideCharToMultiByte(
                CP_ACP, 0, routed.c_str(), -1, nullptr, 0, nullptr, nullptr);
            if (byteCount <= 1)
                return requested;
            std::string narrow(static_cast<size_t>(byteCount), '\0');
            WideCharToMultiByte(CP_ACP, 0, routed.c_str(), -1, narrow.data(), byteCount,
                                nullptr, &unconvertible);
            if (unconvertible)
                return requested;
            narrow.pop_back();
            return narrow;
        }

        class ScopedNormalizationGuard
        {
        public:
            ScopedNormalizationGuard()
                : m_Previous(g_InTrnNormalization)
            {
                g_InTrnNormalization = true;
            }

            ~ScopedNormalizationGuard()
            {
                g_InTrnNormalization = m_Previous;
            }

        private:
            bool m_Previous;
        };

        static std::wstring ToLowerWide(std::wstring value)
        {
            std::transform(value.begin(), value.end(), value.begin(), [](wchar_t ch)
            {
                return static_cast<wchar_t>(::towlower(ch));
            });
            return value;
        }

        static std::wstring ResolveAbsolutePath(const wchar_t* path)
        {
            if (!path || !*path)
                return {};

            std::vector<wchar_t> buffer(MAX_PATH, L'\0');
            DWORD written = GetFullPathNameW(path, static_cast<DWORD>(buffer.size()), buffer.data(), nullptr);
            if (written == 0)
                return path;

            if (written >= buffer.size())
            {
                buffer.resize(static_cast<size_t>(written) + 1, L'\0');
                written = GetFullPathNameW(path, static_cast<DWORD>(buffer.size()), buffer.data(), nullptr);
                if (written == 0 || written >= buffer.size())
                    return path;
            }

            return std::wstring(buffer.data(), buffer.data() + written);
        }

        static std::wstring ResolveAbsolutePathFromAnsi(const char* path)
        {
            if (!path || !*path)
                return {};

            const int wideChars = MultiByteToWideChar(CP_ACP, 0, path, -1, nullptr, 0);
            if (wideChars <= 1)
                return {};

            std::vector<wchar_t> wide(static_cast<size_t>(wideChars), L'\0');
            MultiByteToWideChar(CP_ACP, 0, path, -1, wide.data(), wideChars);
            return ResolveAbsolutePath(wide.data());
        }

        static std::wstring AnsiPathToWide(const char* path)
        {
            if (!path || !*path)
                return {};

            const int wideChars = MultiByteToWideChar(CP_ACP, 0, path, -1, nullptr, 0);
            if (wideChars <= 1)
                return {};

            std::vector<wchar_t> wide(static_cast<size_t>(wideChars), L'\0');
            if (MultiByteToWideChar(CP_ACP, 0, path, -1, wide.data(), wideChars) == 0)
                return {};
            wide.pop_back();
            return std::wstring(wide.begin(), wide.end());
        }

        static bool IsTrnPath(const std::wstring& path)
        {
            if (path.empty())
                return false;

            const std::wstring extension =
                ToLowerWide(std::filesystem::path(path).extension().wstring());
            return extension == L".trn";
        }

        static bool ShouldTrackTrnWrite(DWORD desiredAccess, DWORD creationDisposition)
        {
            constexpr DWORD kWriteMask =
                GENERIC_WRITE | GENERIC_ALL | FILE_WRITE_DATA | FILE_APPEND_DATA | DELETE;

            if ((desiredAccess & kWriteMask) != 0)
                return true;

            switch (creationDisposition)
            {
            case CREATE_ALWAYS:
            case CREATE_NEW:
            case OPEN_ALWAYS:
            case TRUNCATE_EXISTING:
                return true;
            default:
                return false;
            }
        }

        static std::filesystem::path GetRootAddonPath()
        {
            static const std::filesystem::path rootAddon = []
            {
                std::vector<wchar_t> modulePath(32768, L'\0');
                const DWORD written = GetModuleFileNameW(
                    nullptr, modulePath.data(), static_cast<DWORD>(modulePath.size()));
                if (written == 0 || written >= modulePath.size())
                    return std::filesystem::path{};
                return std::filesystem::path(
                    std::wstring(modulePath.data(), modulePath.data() + written)).parent_path() / L"addon";
            }();
            return rootAddon;
        }

        static bool BznSourceSaveEnabled()
        {
            // Opt-in while the supported editor/runtime matrix is qualified.
            // Routing itself is confined to the native editor filename dialog.
            static const bool enabled = []
            {
                char value[8] = {};
                return GetEnvironmentVariableA("BZR_BZN_SAVE_SOURCE", value,
                    static_cast<DWORD>(sizeof(value))) == 1 && value[0] == '1';
            }();
            return enabled;
        }

        static std::wstring GetOpenedFilePath(HANDLE handle)
        {
            if (!handle || handle == INVALID_HANDLE_VALUE)
                return {};

            std::vector<wchar_t> buffer(1024, L'\0');
            DWORD written = GetFinalPathNameByHandleW(
                handle, buffer.data(), static_cast<DWORD>(buffer.size()),
                FILE_NAME_NORMALIZED | VOLUME_NAME_DOS);
            if (written == 0)
                return {};
            if (written >= buffer.size())
            {
                buffer.resize(static_cast<size_t>(written) + 1, L'\0');
                written = GetFinalPathNameByHandleW(
                    handle, buffer.data(), static_cast<DWORD>(buffer.size()),
                    FILE_NAME_NORMALIZED | VOLUME_NAME_DOS);
                if (written == 0 || written >= buffer.size())
                    return {};
            }

            std::wstring path(buffer.data(), buffer.data() + written);
            if (_wcsnicmp(path.c_str(), L"\\\\?\\UNC\\", 8) == 0)
                path = L"\\\\" + path.substr(8);
            else if (_wcsnicmp(path.c_str(), L"\\\\?\\", 4) == 0)
                path.erase(0, 4);
            return path;
        }

        static void RememberOpenedBznSource(
            HANDLE handle, DWORD desiredAccess, DWORD creationDisposition)
        {
            if (!BznSourceSaveEnabled() ||
                ShouldTrackTrnWrite(desiredAccess, creationDisposition) ||
                (desiredAccess & (GENERIC_READ | GENERIC_EXECUTE | GENERIC_ALL)) == 0)
            {
                return;
            }

            const std::filesystem::path openedPath = GetOpenedFilePath(handle);
            if (!IsEditorSourcePath(openedPath))
                return;

            const std::wstring value = openedPath.wstring();
            bool changed = false;
            bool ambiguous = false;
            {
                std::lock_guard<std::mutex> lock(g_BznSourceMutex);
                const auto previous = g_BznSources.Lookup(openedPath);
                g_BznSources.Remember(openedPath);
                changed = previous != g_BznSources.Lookup(openedPath);
                ambiguous = g_BznSources.Lookup(openedPath).empty();
            }
            if (changed)
                Log(L"[BZN] Loose map source path=%ls ambiguous=%d\n",
                    value.c_str(), ambiguous ? 1 : 0);
        }

        static std::filesystem::path LookupRememberedBznSource(
            const std::filesystem::path& requested)
        {
            std::lock_guard<std::mutex> lock(g_BznSourceMutex);
            return g_BznSources.LookupForSave(requested);
        }

        static std::string WidePathToAnsi(
            const std::wstring& path, const std::string& fallback)
        {
            if (path.empty())
                return fallback;
            const int byteCount = WideCharToMultiByte(
                CP_ACP, WC_NO_BEST_FIT_CHARS, path.c_str(), -1,
                nullptr, 0, nullptr, nullptr);
            if (byteCount <= 1)
                return fallback;

            std::string converted(static_cast<size_t>(byteCount), '\0');
            BOOL usedDefault = FALSE;
            if (WideCharToMultiByte(
                    CP_ACP, WC_NO_BEST_FIT_CHARS, path.c_str(), -1,
                    converted.data(), byteCount, nullptr, &usedDefault) == 0 || usedDefault)
            {
                return fallback;
            }
            converted.pop_back();
            return converted;
        }

        static EditorSaveFileState InspectEditorSaveFile(const std::filesystem::path& path)
        {
            const DWORD attributes = GetFileAttributesW(path.c_str());
            if (attributes == INVALID_FILE_ATTRIBUTES)
            {
                const DWORD error = GetLastError();
                return error == ERROR_FILE_NOT_FOUND || error == ERROR_PATH_NOT_FOUND
                    ? EditorSaveFileState::Missing : EditorSaveFileState::Blocked;
            }
            return (attributes & (FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_READONLY)) != 0
                ? EditorSaveFileState::Blocked : EditorSaveFileState::Writable;
        }

        static HWND EditorDialogOwner()
        {
            // Never attach our modal prompt to another application's window.
            const HWND window = GetForegroundWindow();
            DWORD process = 0;
            GetWindowThreadProcessId(window, &process);
            return process == GetCurrentProcessId() ? window : GetActiveWindow();
        }

        static bool __fastcall Hooked_EditorSaveDialog(
            void* self, void*, char* filename, bool missionSave)
        {
            if (!g_OriginalEditorSaveDialog)
                return false;
            // This hook replaces only PromptSaveMission's GetSaveName call.
            // The caller's false branch returns before SaveGame/SaveZoneFiles.
            if (!g_OriginalEditorSaveDialog(self, filename, missionSave))
                return false;
            if (!missionSave || !BznSourceSaveEnabled())
                return true;

            try
            {
                constexpr size_t kEditorFilenameCapacity = 4096;
                if (!filename || strnlen_s(filename, kEditorFilenameCapacity) == kEditorFilenameCapacity)
                    return false;
                const std::filesystem::path requested = ResolveAbsolutePathFromAnsi(filename);
                if (!IsEditorSourcePath(requested))
                    return true;
                const auto source = LookupRememberedBznSource(requested);
                const auto plan = BuildEditorSavePlan(
                    ChooseBznSavePath(requested, source, GetRootAddonPath()));
                // The native writer is ANSI and has a 4096-byte name buffer.
                // Never show one destination and then silently save to another.
                const auto converted = WidePathToAnsi(plan.target.wstring(), {});
                if (converted.empty() || converted.size() >= kEditorFilenameCapacity)
                {
                    MessageBoxW(EditorDialogOwner(),
                        L"This save path cannot be represented by the editor. Choose a shorter path or a different folder.",
                        L"World Builder - Save cancelled", MB_OK | MB_ICONERROR);
                    return false;
                }
                const bool approved = ApproveEditorSave(plan, InspectEditorSaveFile,
                    [](const std::wstring& message)
                    {
                        return MessageBoxW(EditorDialogOwner(), message.c_str(),
                            L"World Builder - Confirm save",
                            MB_OKCANCEL | MB_ICONWARNING | MB_DEFBUTTON2) == IDOK;
                    },
                    [](const std::filesystem::path& blocked)
                    {
                        const auto message = L"Cannot save to:\n" + blocked.wstring() +
                            L"\n\nThe destination is read-only, inaccessible, or a directory. No files were saved.";
                        MessageBoxW(EditorDialogOwner(), message.c_str(),
                            L"World Builder - Save cancelled", MB_OK | MB_ICONERROR);
                    });
                if (!approved)
                {
                    Log(L"[BZN] Editor save cancelled before writes target=%ls\n", plan.target.c_str());
                    return false;
                }
                // Change the buffer before native saving AND before the caller
                // remembers the last save name. All native terrain siblings now
                // derive from the confirmed destination in the same directory.
                memcpy(filename, converted.c_str(), converted.size() + 1);
                Log(L"[BZN] Editor save approved requested=%ls target=%ls redirected=%d\n",
                    requested.c_str(), plan.target.c_str(), plan.redirected ? 1 : 0);
                return true;
            }
            catch (...)
            {
                Log(L"[BZN] Editor save preparation failed; cancelled before writes\n");
                return false;
            }
        }

        static void TrackTrnWriteHandle(HANDLE handle, const std::wstring& path)
        {
            if (!handle || handle == INVALID_HANDLE_VALUE || path.empty())
                return;

            std::lock_guard<std::mutex> lock(g_TrnWriteMutex);
            // Growth cap. Entries are removed only by a hooked CloseHandle in
            // a patched module; a close from any other module (or NtClose)
            // leaks the entry. Windows reuses HANDLE values aggressively, so
            // an unbounded leak eventually turns into a stale record for an
            // unrelated file. Eviction is arbitrary because every entry over
            // the cap is, by construction, already orphaned.
            constexpr size_t kMaxTrackedTrnHandles = 4096;
            if (g_TrnWriteHandles.size() >= kMaxTrackedTrnHandles &&
                g_TrnWriteHandles.find(reinterpret_cast<uintptr_t>(handle)) ==
                    g_TrnWriteHandles.end())
            {
                g_TrnWriteHandles.erase(g_TrnWriteHandles.begin());
            }
            g_TrnWriteHandles[reinterpret_cast<uintptr_t>(handle)] = { path };
        }

        // A tracked record must only drive normalization while the closing
        // HANDLE still refers to the file that was recorded. Handles leaked
        // past the hooked modules stay in the map and Windows hands their
        // numeric values back out, so identity has to be re-verified against
        // the still-open handle at close time.
        static bool TrackedHandleMatchesRecord(HANDLE handle, const TrnWriteRecord& record)
        {
            if (record.path.empty())
                return false;

            wchar_t buffer[1024] = {};
            const DWORD written = GetFinalPathNameByHandleW(
                handle, buffer, static_cast<DWORD>(std::size(buffer)),
                FILE_NAME_NORMALIZED | VOLUME_NAME_DOS);
            if (written == 0 || written >= std::size(buffer))
                return false;

            // GetFinalPathNameByHandleW returns \\?\C:\... for DOS paths; the
            // recorded path came from GetFullPathNameW without the prefix.
            std::wstring actual = buffer;
            const wchar_t kNtDosPrefix[] = L"\\\\?\\";
            if (_wcsnicmp(actual.c_str(), kNtDosPrefix, 4) == 0)
                actual.erase(0, 4);

            return _wcsicmp(actual.c_str(), record.path.c_str()) == 0;
        }

        static bool PopTrackedTrnWriteHandle(HANDLE handle, TrnWriteRecord& outRecord)
        {
            if (!handle || handle == INVALID_HANDLE_VALUE)
                return false;

            std::lock_guard<std::mutex> lock(g_TrnWriteMutex);
            const auto it = g_TrnWriteHandles.find(reinterpret_cast<uintptr_t>(handle));
            if (it == g_TrnWriteHandles.end())
                return false;

            outRecord = it->second;
            g_TrnWriteHandles.erase(it);
            return true;
        }

        static bool ReadBinaryFile(const std::wstring& path, std::vector<uint8_t>& outBytes)
        {
            std::ifstream input(std::filesystem::path(path), std::ios::binary);
            if (!input.is_open())
                return false;

            input.seekg(0, std::ios::end);
            const std::streamoff size = input.tellg();
            input.seekg(0, std::ios::beg);
            if (size < 0)
                return false;

            outBytes.resize(static_cast<size_t>(size));
            if (!outBytes.empty())
                input.read(reinterpret_cast<char*>(outBytes.data()), size);

            return input.good() || input.eof();
        }

        static bool WriteBinaryFileAtomic(const std::wstring& path, const std::vector<uint8_t>& bytes)
        {
            const std::filesystem::path targetPath(path);
            const std::filesystem::path tempPath = targetPath.wstring() + L".openshim_tmp";

            {
                std::ofstream output(tempPath, std::ios::binary | std::ios::trunc);
                if (!output.is_open())
                    return false;

                if (!bytes.empty())
                    output.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));

                if (!output.good())
                    return false;
            }

            SetFileAttributesW(path.c_str(), FILE_ATTRIBUTE_NORMAL);
            if (!MoveFileExW(tempPath.c_str(), path.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED))
            {
                std::error_code ignored;
                std::filesystem::remove(tempPath, ignored);
                return false;
            }

            return true;
        }

        static void NormalizeTrnFileIfNeeded(const std::wstring& path, const wchar_t* reason)
        {
            if (path.empty() || g_InTrnNormalization)
                return;

            ScopedNormalizationGuard guard;

            std::vector<uint8_t> originalBytes;
            if (!ReadBinaryFile(path, originalBytes))
            {
                Log(L"[TRN] Failed to read tracked file path=%ls reason=%ls\n",
                    path.c_str(),
                    reason ? reason : L"<unknown>");
                return;
            }

            const TrnCanonicalResult result = CanonicalizeTrnBytes(originalBytes);
            if (result.status != TrnCodecStatus::Ok)
            {
                Log(L"[TRN] Safety normalizer left file unchanged path=%ls reason=%ls status=%hs\n",
                    path.c_str(), reason ? reason : L"<unknown>",
                    TrnCodecStatusName(result.status));
                return;
            }
            if (!result.changed)
                return;

            if (!WriteBinaryFileAtomic(path, result.serializedCrLf))
            {
                Log(L"[TRN] Failed to rewrite normalized file path=%ls reason=%ls\n",
                    path.c_str(),
                    reason ? reason : L"<unknown>");
                return;
            }

            Log(L"[TRN] Safety-normalized file path=%ls reason=%ls encoding=%hs bytes=%u->%u\n",
                path.c_str(),
                reason ? reason : L"<unknown>",
                TrnSourceEncodingName(result.sourceEncoding),
                static_cast<unsigned>(originalBytes.size()),
                static_cast<unsigned>(result.serializedCrLf.size()));
        }

        static void MaybeTrackOpenedTrnHandle(HANDLE handle, const std::wstring& path, DWORD desiredAccess, DWORD creationDisposition)
        {
            if (g_InTrnNormalization)
                return;

            if (!ShouldTrackTrnWrite(desiredAccess, creationDisposition))
                return;

            const std::wstring absolutePath = ResolveAbsolutePath(path.c_str());
            if (!IsTrnPath(absolutePath))
                return;

            TrackTrnWriteHandle(handle, absolutePath);
            Log(L"[TRN] Tracking write handle=0x%p path=%ls disposition=%u access=0x%08X\n",
                handle,
                absolutePath.c_str(),
                static_cast<unsigned>(creationDisposition),
                static_cast<unsigned>(desiredAccess));
        }

        static BOOL WINAPI Hooked_CloseHandle(HANDLE object)
        {
            if (!g_RealCloseHandle)
                return FALSE;

            TrnWriteRecord record = {};
            const bool tracked = !g_InTrnNormalization && PopTrackedTrnWriteHandle(object, record);
            // Identity check must run before the real close, while the handle
            // still resolves. A mismatch means the map held a stale numeric
            // handle value (leaked past a hooked closer and reused by
            // Windows); rewriting the recorded path then would corrupt an
            // unrelated file.
            const bool matches = tracked && TrackedHandleMatchesRecord(object, record);
            const BOOL result = g_RealCloseHandle(object);

            if (tracked && result && matches)
                NormalizeTrnFileIfNeeded(record.path, L"CloseHandle");
            else if (tracked)
            {
                Log(L"[TRN] Dropping stale tracked write handle=0x%p path=%ls closeOk=%d identity=%d\n",
                    object,
                    record.path.c_str(),
                    static_cast<int>(result),
                    static_cast<int>(matches));
            }

            return result;
        }

        static void MaybeNormalizeMovedDestination(const std::wstring& destination, const wchar_t* reason)
        {
            if (g_InTrnNormalization)
                return;

            const std::wstring absoluteDestination = ResolveAbsolutePath(destination.c_str());
            if (IsTrnPath(absoluteDestination))
                NormalizeTrnFileIfNeeded(absoluteDestination, reason);
        }

        static BOOL WINAPI Hooked_MoveFileExW(LPCWSTR existingFileName, LPCWSTR newFileName, DWORD flags)
        {
            if (!g_RealMoveFileExW)
                return FALSE;

            const BOOL result = g_RealMoveFileExW(existingFileName, newFileName, flags);
            if (result && newFileName && *newFileName)
                MaybeNormalizeMovedDestination(newFileName, L"MoveFileExW");
            return result;
        }

        static BOOL WINAPI Hooked_MoveFileExA(LPCSTR existingFileName, LPCSTR newFileName, DWORD flags)
        {
            if (!g_RealMoveFileExA)
                return FALSE;

            const BOOL result = g_RealMoveFileExA(existingFileName, newFileName, flags);
            if (result && newFileName && *newFileName)
                MaybeNormalizeMovedDestination(ResolveAbsolutePathFromAnsi(newFileName), L"MoveFileExA");
            return result;
        }

        // ------------------------------------------------------------------
        // Runtime policy for the bootstrap file-I/O seam.
        //
        // These four callbacks are exactly what the old Hooked_CreateFileW/A
        // did either side of the real call. The bootstrap owns the hook and
        // the log routing; everything here is what OpenShim adds once it
        // exists. Before it does, the wrappers run without any of it.
        //
        // Callable on any thread from the first file the process opens, so
        // nothing here may assume the game is initialised.
        // ------------------------------------------------------------------

        // The seam hands back a borrowed pointer that has to stay valid until
        // this thread routes again, so the storage is thread_local rather
        // than a return-by-value the caller would have to own.
        static thread_local std::wstring g_RoutedPathW;
        static thread_local std::string g_RoutedPathA;

        // The seam calls these from inside the game's own CreateFile. It has
        // a last-resort catch of its own now, but nothing here may throw in
        // the first place: an allocation failure declines the route or drops
        // the observation, and the first occurrence is logged.
        static void NoteProviderCallbackThrew(const wchar_t* which)
        {
            static bool s_logged = false;
            if (s_logged)
                return;
            s_logged = true;
            Log(L"[FILEIO] %s threw a C++ exception inside the game's CreateFile; declined, later occurrences are silent\n",
                which);
        }

        static const wchar_t* __cdecl ProviderRoutePathW(
            const wchar_t* path, DWORD desiredAccess, DWORD creationDisposition)
        {
            if (!path)
                return nullptr;
            try
            {
                std::wstring routed = RouteTerrainAtlasPath(path, desiredAccess, creationDisposition);
                if (routed == path)
                    return nullptr;  // nothing to say; let the seam use its own path
                g_RoutedPathW = std::move(routed);
                return g_RoutedPathW.c_str();
            }
            catch (...)
            {
                NoteProviderCallbackThrew(L"routePathW");
                return nullptr;
            }
        }

        static const char* __cdecl ProviderRoutePathA(
            const char* path, DWORD desiredAccess, DWORD creationDisposition)
        {
            if (!path)
                return nullptr;
            try
            {
                std::string routed = RouteTerrainAtlasPath(std::string(path), desiredAccess, creationDisposition);
                if (routed == path)
                    return nullptr;
                g_RoutedPathA = std::move(routed);
                return g_RoutedPathA.c_str();
            }
            catch (...)
            {
                NoteProviderCallbackThrew(L"routePathA");
                return nullptr;
            }
        }

        static void __cdecl ProviderOnOpenedW(
            HANDLE handle, const wchar_t* requested, const wchar_t* routed,
            DWORD desiredAccess, DWORD creationDisposition)
        {
            try
            {
                // TRN write tracking keys off the name the caller asked for.
                if (!g_InTrnNormalization)
                    MaybeTrackOpenedTrnHandle(handle, requested ? requested : L"", desiredAccess, creationDisposition);
                // Editor-source detection and load tracing follow what was really
                // opened, which is not the same string once a path is rerouted.
                const std::wstring routedPath = routed ? routed : L"";
                if (IsEditorSourcePath(routedPath))
                    RememberOpenedBznSource(handle, desiredAccess, creationDisposition);
                BznLoadTraceOnOpen(routedPath.c_str(), desiredAccess);

                // Ogre parses the mod's *.program scripts (and then compiles the
                // enhanced-lighting shaders) right after this open succeeds. Prime
                // the microcode cache on this exact thread so a prior session's
                // compiled shaders are available before compilation begins.
                if (PathEndsWithProgramW(requested))
                {
                    OgreShaderCacheOnProgramScriptOpen();
                    if (UiPerf::IsEnabled())
                        UiPerf::RecordShaderCache(0, 0, 0.0); // marker: program open triggered cache
                }
            }
            catch (...)
            {
                NoteProviderCallbackThrew(L"onOpenedW");
            }
        }

        static void __cdecl ProviderOnOpenedA(
            HANDLE handle, const char* requested, const char* routed,
            DWORD desiredAccess, DWORD creationDisposition)
        {
            try
            {
                if (!g_InTrnNormalization)
                    MaybeTrackOpenedTrnHandle(handle, ResolveAbsolutePathFromAnsi(requested), desiredAccess, creationDisposition);
                const std::wstring wideRouted = AnsiPathToWide(routed ? routed : "");
                if (IsEditorSourcePath(wideRouted))
                    RememberOpenedBznSource(handle, desiredAccess, creationDisposition);
                BznLoadTraceOnOpenA(routed ? routed : "", desiredAccess);

                if (PathEndsWithProgramA(requested))
                {
                    OgreShaderCacheOnProgramScriptOpen();
                    if (UiPerf::IsEnabled())
                        UiPerf::RecordShaderCache(0, 0, 0.0);
                }
            }
            catch (...)
            {
                NoteProviderCallbackThrew(L"onOpenedA");
            }
        }

        // Static, so installing it is a pointer store with no allocation and
        // no loader work. It has to outlive the process: the seam keeps
        // calling through it and there is no uninstall.
        static const BootstrapFileIo::Provider g_FileIoProvider = {
            sizeof(BootstrapFileIo::Provider),
            ProviderRoutePathW,
            ProviderRoutePathA,
            ProviderOnOpenedW,
            ProviderOnOpenedA,
        };

        static int PatchTrackedFunctionsForModule(HMODULE module, const wchar_t* label)
        {
            if (!module)
                return 0;

            // CreateFileA/W always resolve to the bootstrap's wrappers, never
            // to a second interceptor of our own. For the main executable
            // these entries are already pointing there from process attach,
            // so this is a no-op; for the CRT modules, which only appear
            // later, it routes them through the same seam. Either way the
            // runtime's own behaviour arrives through the installed provider,
            // not through a different hook.
            int patched = BootstrapFileIo::PatchCreateFileHooksForModule(module);
            patched += BootstrapFileIo::PatchIATByFuncName(module, "CloseHandle", reinterpret_cast<void*>(Hooked_CloseHandle), reinterpret_cast<void**>(&g_RealCloseHandle)) ? 1 : 0;
            patched += BootstrapFileIo::PatchIATByFuncName(module, "MoveFileExW", reinterpret_cast<void*>(Hooked_MoveFileExW), reinterpret_cast<void**>(&g_RealMoveFileExW)) ? 1 : 0;
            patched += BootstrapFileIo::PatchIATByFuncName(module, "MoveFileExA", reinterpret_cast<void*>(Hooked_MoveFileExA), reinterpret_cast<void**>(&g_RealMoveFileExA)) ? 1 : 0;

            Log(L"[TRN] Module %ls file hook results: patched=%d base=0x%p\n",
                label ? label : L"<unknown>",
                patched,
                module);
            return patched;
        }
    }

    void* PrepareEditorSaveDialogHook(uint32_t callAddress)
    {
        if (!BznSourceSaveEnabled())
            return nullptr;
        void* original = HookEngine::ResolveRelCallTarget(callAddress);
        const uint32_t expected = HookEngine::ResolveNamedAddress("WorldBuilder::GetSaveName");
        if (!original || !expected || reinterpret_cast<uintptr_t>(original) != expected)
        {
            Log(L"[BZN] Editor dialog identity failed site=0x%08X original=%p expected=0x%08X\n",
                callAddress, original, expected);
            return nullptr;
        }
        g_OriginalEditorSaveDialog = reinterpret_cast<EditorSaveDialog>(original);
        return reinterpret_cast<void*>(Hooked_EditorSaveDialog);
    }

    bool InstallFileIoProvider()
    {
        return BootstrapFileIo::InstallProvider(&g_FileIoProvider);
    }

    void ApplyTrnSaveNormalizeHooks()
    {
        Log(L"=========== TRN SAVE NORMALIZATION HOOKS ===========\n");

        HMODULE mainModule = GetModuleHandleW(nullptr);
        if (!mainModule)
        {
            Log(L"[TRN] GetModuleHandleW(nullptr) failed; file hooks not installed\n");
            return;
        }

        int patched = PatchTrackedFunctionsForModule(mainModule, L"battlezone98redux.exe");

        const wchar_t* modulesToWatch[] =
        {
            L"msvcr120.dll",
            L"ucrtbase.dll"
        };

        for (const wchar_t* moduleName : modulesToWatch)
        {
            HMODULE module = nullptr;
            for (int attempt = 0; attempt < 200; ++attempt)
            {
                module = GetModuleHandleW(moduleName);
                if (module)
                    break;
                Sleep(25);
            }

            if (module)
            {
                patched += PatchTrackedFunctionsForModule(module, moduleName);
            }
            else
            {
                Log(L"[TRN] Module %ls was not loaded during hook watch window\n", moduleName);
            }
        }

        Log(L"[TRN] Automatic save normalization %hs\n", patched > 0 ? "enabled" : "not installed");
    }
}
