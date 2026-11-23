#pragma once

// Where OpenShim keeps its own files in the game folder.
//
// Removing OpenShim by hand is meant to be: delete winmm.dll, bzloader.dll,
// plugins\openshim.dll, the openshim\ folder and the logs\ folder. Player data
// (Save\, career_stats.cfg, bans.cfg, flags\, multi.ini, ...) stays in the
// game root and is not handled here.
//
//   openshim\openshim.ini (+ .canonical, .new, installer backups)
//   openshim\patches.json (+ .previous)
//   openshim\cache\shaders\        DXBC and Ogre microcode caches
//   openshim\state\                updater status, Steam tunnel peer list
//   openshim\tools\lan\            BZRServer.exe LAN helper
//   openshim\stock-backup\         pristine copies of stock files OpenShim edits
//   logs\                          every log, profile CSV and test capture
//
// Older builds wrote these to the game root (scripts\patches.json, tools\lan,
// shader_cache\, openshim.ini, ...). Each family is migrated once per process,
// lazily, the first time its path is asked for, so a config read can never
// beat the openshim.ini move. Rules: an old file moves only when the new one
// does not exist (never overwritten); if the move fails the old location is
// read as a fallback; old caches are deleted instead of moved. Each step is
// recorded as one line; the module drains them into its log with
// DrainMigrationLog once its logger is up, because the first ini read can
// happen before that (even under the loader lock, where only kernel32 file
// calls are made here).
//
// Header-only and stateless apart from per-module function statics, so
// winmm.dll and openshim.dll can both include it. Each module migrates on its
// own first use; the second one finds nothing left to move. Windows-only.

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <cstdio>
#include <filesystem>
#include <string>
#include <utility>
#include <vector>

namespace BZROpenShim
{
namespace Layout
{
    namespace Detail
    {
        struct MigrationLogState
        {
            SRWLOCK lock = SRWLOCK_INIT;
            std::vector<std::string> lines;
        };

        inline MigrationLogState& LogState()
        {
            static MigrationLogState s_state;
            return s_state;
        }

        // UTF-8 without std::filesystem::path::string(), which throws on
        // names the ANSI code page cannot hold.
        inline std::string Utf8(const std::filesystem::path& path)
        {
            const std::wstring& wide = path.native();
            if (wide.empty())
                return {};
            const int size = WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), static_cast<int>(wide.size()),
                                                 nullptr, 0, nullptr, nullptr);
            std::string out(size > 0 ? static_cast<size_t>(size) : 0, '\0');
            if (size > 0)
                WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), static_cast<int>(wide.size()),
                                    &out[0], size, nullptr, nullptr);
            return out;
        }

        // Every format takes, in order: %s (a), %s (b), %lu (error); a format
        // may stop early but never reorders them.
        inline void Note(const char* format, const std::filesystem::path& a,
                         const std::filesystem::path& b = {}, unsigned long error = 0)
        {
            char line[1024] = {};
            _snprintf_s(line, sizeof(line), _TRUNCATE, format,
                        Utf8(a).c_str(), Utf8(b).c_str(), error);
            MigrationLogState& state = LogState();
            AcquireSRWLockExclusive(&state.lock);
            state.lines.emplace_back(line);
            ReleaseSRWLockExclusive(&state.lock);
        }

        inline bool Exists(const std::filesystem::path& path)
        {
            return GetFileAttributesW(path.c_str()) != INVALID_FILE_ATTRIBUTES;
        }

        inline bool IsDirectory(const std::filesystem::path& path)
        {
            const DWORD attributes = GetFileAttributesW(path.c_str());
            return attributes != INVALID_FILE_ATTRIBUTES &&
                   (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
        }

        inline void EnsureDirectory(const std::filesystem::path& path)
        {
            std::error_code ec;
            std::filesystem::create_directories(path, ec);
        }
    }

    // The game executable's folder, or empty when it cannot be determined.
    inline const std::filesystem::path& GameRoot()
    {
        static const std::filesystem::path s_root = []
        {
            wchar_t buffer[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameW(nullptr, buffer, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return std::filesystem::path();
            return std::filesystem::path(buffer).parent_path();
        }();
        return s_root;
    }

    inline std::filesystem::path OpenShimDirectory() { return GameRoot() / L"openshim"; }
    inline std::filesystem::path LogsDirectory() { return GameRoot() / L"logs"; }
    inline std::filesystem::path StockBackupDirectory() { return OpenShimDirectory() / L"stock-backup"; }

    // Moves one old-layout file or folder to its new home. Returns true when
    // the new path now holds the data or nothing needed moving; false only
    // when an old file is still the only copy (the caller then reads it).
    inline bool MigrateEntry(const std::filesystem::path& oldPath,
                             const std::filesystem::path& newPath)
    {
        if (!Detail::Exists(oldPath))
            return true;
        if (Detail::Exists(newPath))
        {
            // An older installer or updater may still write the old path;
            // say so loudly when the ignored copy differs from the one used.
            std::error_code ec1, ec2;
            const bool differs = !Detail::IsDirectory(oldPath) &&
                std::filesystem::file_size(oldPath, ec1) != std::filesystem::file_size(newPath, ec2);
            Detail::Note(differs
                ? "[LAYOUT] WARNING: ignoring %s, which differs from %s (in use); delete one of them"
                : "[LAYOUT] kept %s in place: %s already exists and is used", oldPath, newPath);
            return true;
        }
        Detail::EnsureDirectory(newPath.parent_path());
        if (MoveFileExW(oldPath.c_str(), newPath.c_str(), MOVEFILE_COPY_ALLOWED | MOVEFILE_WRITE_THROUGH))
        {
            Detail::Note("[LAYOUT] moved %s to %s", oldPath, newPath);
            return true;
        }
        const DWORD moveError = GetLastError();
        if (!Detail::IsDirectory(oldPath) && CopyFileW(oldPath.c_str(), newPath.c_str(), TRUE))
        {
            if (DeleteFileW(oldPath.c_str()))
                Detail::Note("[LAYOUT] copied %s to %s and removed the old copy", oldPath, newPath);
            else
                Detail::Note("[LAYOUT] copied %s to %s; the old copy could not be removed (error %lu)",
                             oldPath, newPath, GetLastError());
            return true;
        }
        // winmm.dll and openshim.dll each migrate on first use; the other
        // module may have just moved the file.
        if (!Detail::Exists(oldPath) && Detail::Exists(newPath))
            return true;
        Detail::Note("[LAYOUT] could not move %s to %s (error %lu); still reading the old location",
                     oldPath, newPath, moveError);
        return false;
    }

    // Moves every root file matching a wildcard (e.g. "openshim.ini.bak-*")
    // into newDirectory under the same name.
    inline void MigrateMatching(const std::filesystem::path& oldDirectory, const wchar_t* pattern,
                                const std::filesystem::path& newDirectory)
    {
        WIN32_FIND_DATAW data = {};
        HANDLE find = FindFirstFileW((oldDirectory / pattern).c_str(), &data);
        if (find == INVALID_HANDLE_VALUE)
            return;
        std::vector<std::wstring> names;
        do
        {
            if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
                names.emplace_back(data.cFileName);
        } while (FindNextFileW(find, &data));
        FindClose(find);
        for (const auto& name : names)
            MigrateEntry(oldDirectory / name, newDirectory / name);
    }

    // Removes an old-layout folder only once nothing is left in it.
    inline void RemoveIfEmpty(const std::filesystem::path& directory)
    {
        if (Detail::IsDirectory(directory) && RemoveDirectoryW(directory.c_str()))
            Detail::Note("[LAYOUT] removed the empty folder %s", directory);
    }

    // openshim\openshim.ini, or the root copy when moving it failed. The
    // openshim.ini family (canonical preset and backups) migrates on the
    // first call, before any caller can read config.
    inline const std::filesystem::path& OpenShimIniPath()
    {
        static const std::filesystem::path s_path = []
        {
            const std::filesystem::path& root = GameRoot();
            if (root.empty())
                return std::filesystem::path(L"openshim") / L"openshim.ini";
            const std::filesystem::path directory = OpenShimDirectory();
            Detail::EnsureDirectory(directory);
            const std::filesystem::path oldIni = root / L"openshim.ini";
            const std::filesystem::path newIni = directory / L"openshim.ini";
            const bool moved = MigrateEntry(oldIni, newIni);
            MigrateEntry(root / L"openshim.ini.canonical", directory / L"openshim.ini.canonical");
            MigrateEntry(root / L"openshim.ini.new", directory / L"openshim.ini.new");
            MigrateMatching(root, L"openshim.ini.bak-*", directory);
            MigrateMatching(root, L"openshim.ini.pre-reset-*.bak", directory);
            MigrateMatching(root, L"openshim.ini.premigrate-r*.bak", directory);
            return moved ? newIni : oldIni;
        }();
        return s_path;
    }

    // ANSI form for the *ProfileStringA readers. Converted with the ANSI code
    // page by hand: path::string() throws on names it cannot represent.
    inline std::string AnsiPath(const std::filesystem::path& path)
    {
        const std::wstring& wide = path.native();
        const int size = WideCharToMultiByte(CP_ACP, 0, wide.c_str(), static_cast<int>(wide.size()),
                                             nullptr, 0, nullptr, nullptr);
        std::string out(size > 0 ? static_cast<size_t>(size) : 0, '\0');
        if (size > 0)
            WideCharToMultiByte(CP_ACP, 0, wide.c_str(), static_cast<int>(wide.size()),
                                &out[0], size, nullptr, nullptr);
        return out;
    }

    inline std::string OpenShimIniPathA() { return AnsiPath(OpenShimIniPath()); }

    // An older installer or updater can still write scripts\patches.json after
    // the layout move. When both copies exist and the old one was written
    // later, the old one is the fresh one: set the current file aside as
    // patches.json.superseded (replacing any earlier one) and put the old file
    // in its place. Anything else is left to MigrateEntry. patches.json only;
    // openshim.ini is player data and is never replaced this way.
    inline void ReplaceIfOldPatchesNewer(const std::filesystem::path& oldJson,
                                         const std::filesystem::path& newJson)
    {
        WIN32_FILE_ATTRIBUTE_DATA oldData = {};
        WIN32_FILE_ATTRIBUTE_DATA newData = {};
        if (!GetFileAttributesExW(oldJson.c_str(), GetFileExInfoStandard, &oldData) ||
            !GetFileAttributesExW(newJson.c_str(), GetFileExInfoStandard, &newData) ||
            (oldData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 ||
            (newData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
            return;
        if (CompareFileTime(&oldData.ftLastWriteTime, &newData.ftLastWriteTime) <= 0)
            return;
        std::filesystem::path superseded = newJson;
        superseded += L".superseded";
        if (!MoveFileExW(newJson.c_str(), superseded.c_str(),
                         MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED | MOVEFILE_WRITE_THROUGH))
        {
            Detail::Note("[LAYOUT] could not set %s%s aside (error %lu); keeping it in use",
                         newJson, {}, GetLastError());
            return;
        }
        if (MoveFileExW(oldJson.c_str(), newJson.c_str(), MOVEFILE_COPY_ALLOWED | MOVEFILE_WRITE_THROUGH))
        {
            Detail::Note("[LAYOUT] %s is newer than %s: moved it into place and kept the other as .superseded",
                         oldJson, newJson);
            return;
        }
        // Put the current file back rather than leave no patches.json.
        const DWORD error = GetLastError();
        MoveFileExW(superseded.c_str(), newJson.c_str(), MOVEFILE_REPLACE_EXISTING);
        Detail::Note("[LAYOUT] could not move the newer %s into place (error %lu); keeping %s",
                     oldJson, newJson, error);
    }

    // openshim\patches.json, or scripts\patches.json when moving it failed.
    inline const std::filesystem::path& PatchesJsonPath()
    {
        static const std::filesystem::path s_path = []
        {
            const std::filesystem::path& root = GameRoot();
            if (root.empty())
                return std::filesystem::path(L"openshim") / L"patches.json";
            const std::filesystem::path oldJson = root / L"scripts" / L"patches.json";
            const std::filesystem::path newJson = OpenShimDirectory() / L"patches.json";
            ReplaceIfOldPatchesNewer(oldJson, newJson);
            const bool moved = MigrateEntry(oldJson, newJson);
            MigrateEntry(root / L"scripts" / L"patches.json.previous",
                         OpenShimDirectory() / L"patches.json.previous");
            RemoveIfEmpty(root / L"scripts");
            return moved ? newJson : oldJson;
        }();
        return s_path;
    }

    // openshim\state\<name>; the files that lived in the root migrate on the
    // first call.
    inline std::filesystem::path StatePath(const wchar_t* name)
    {
        static const std::filesystem::path s_directory = []
        {
            const std::filesystem::path directory = OpenShimDirectory() / L"state";
            const std::filesystem::path& root = GameRoot();
            if (!root.empty())
            {
                Detail::EnsureDirectory(directory);
                for (const wchar_t* file : { L"openshim_update.status", L"steam_tunnel_peers.txt",
                                             L"steam_tunnel_peers.txt.lock" })
                    MigrateEntry(root / file, directory / file);
            }
            return directory;
        }();
        return s_directory / name;
    }

    // openshim\cache\shaders. The old root shader_cache\ is only a cache, so
    // it is deleted rather than moved.
    inline const std::filesystem::path& ShaderCacheDirectory()
    {
        static const std::filesystem::path s_directory = []
        {
            const std::filesystem::path oldCache = GameRoot() / L"shader_cache";
            if (!GameRoot().empty() && Detail::IsDirectory(oldCache))
            {
                std::error_code ec;
                std::filesystem::remove_all(oldCache, ec);
                if (ec)
                    Detail::Note("[LAYOUT] could not delete the old shader cache %s%s (error %lu)",
                                 oldCache, {}, static_cast<unsigned long>(ec.value()));
                else
                    Detail::Note("[LAYOUT] deleted the old shader cache %s", oldCache);
            }
            return OpenShimDirectory() / L"cache" / L"shaders";
        }();
        return s_directory;
    }

    // openshim\tools\lan, or the old tools\lan when moving it failed.
    inline const std::filesystem::path& LanToolsDirectory()
    {
        static const std::filesystem::path s_directory = []
        {
            const std::filesystem::path& root = GameRoot();
            const std::filesystem::path oldDirectory = root / L"tools" / L"lan";
            const std::filesystem::path newDirectory = OpenShimDirectory() / L"tools" / L"lan";
            if (root.empty())
                return newDirectory;
            const bool moved = MigrateEntry(oldDirectory, newDirectory);
            RemoveIfEmpty(root / L"tools");
            return moved ? newDirectory : oldDirectory;
        }();
        return s_directory;
    }

    // Root profile CSVs and test frame captures from older builds move into
    // logs\. Logs only, so no fallback is needed.
    inline void MigrateLegacyLogs()
    {
        static const bool s_done = []
        {
            const std::filesystem::path& root = GameRoot();
            if (root.empty())
                return true;
            const std::filesystem::path logs = LogsDirectory();
            MigrateMatching(root, L"openshim_ogre_profile*.csv", logs);
            MigrateMatching(root, L"openshim_frame_*.png", logs);
            return true;
        }();
        (void)s_done;
    }

    // Runs every family's migration. Called once at startup (off the loader
    // lock) so files a session never touches still leave the root.
    inline void MigrateLegacyLayout()
    {
        (void)OpenShimIniPath();
        (void)PatchesJsonPath();
        (void)StatePath(L"");
        (void)ShaderCacheDirectory();
        (void)LanToolsDirectory();
        MigrateLegacyLogs();
    }

    // Before OpenShim first edits or replaces a stock file in the game root
    // (Ogre.cfg, net.ini, input.map, gamekey.map), keep one pristine copy in
    // openshim\stock-backup\. An existing backup is never overwritten. Returns
    // false only when a copy was needed and could not be made.
    inline bool BackupStockFileOnce(const std::filesystem::path& source)
    {
        if (source.empty() || !source.has_filename())
            return false;
        const std::filesystem::path backup = StockBackupDirectory() / source.filename();
        if (GameRoot().empty() || Detail::Exists(backup) || !Detail::Exists(source))
            return true;
        Detail::EnsureDirectory(backup.parent_path());
        if (CopyFileW(source.c_str(), backup.c_str(), TRUE) || GetLastError() == ERROR_FILE_EXISTS)
        {
            Detail::Note("[LAYOUT] saved the stock %s to %s", source, backup);
            return true;
        }
        Detail::Note("[LAYOUT] could not save the stock %s to %s (error %lu)", source, backup, GetLastError());
        return false;
    }

    // Hands every recorded migration line to sink and forgets them.
    template <typename Sink>
    inline void DrainMigrationLog(Sink&& sink)
    {
        std::vector<std::string> lines;
        Detail::MigrationLogState& state = Detail::LogState();
        AcquireSRWLockExclusive(&state.lock);
        lines.swap(state.lines);
        ReleaseSRWLockExclusive(&state.lock);
        for (const auto& line : lines)
            sink(line.c_str());
    }
}
}
