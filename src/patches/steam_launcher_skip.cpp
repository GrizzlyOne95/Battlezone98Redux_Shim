#include "steam_launcher_skip.h"

#include "BZROpenShim.h"
#include "bzr_options_ui.h"
#include "launcher_proxy_resources.h"
#include "shim_log.h"
#include "troubleshooting_bundle.h"

#include <Windows.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <system_error>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "launcher";
        static int s_ResourceAnchor = 0;

        bool LoadEmbeddedProxy(const char*& data, size_t& size)
        {
            HMODULE module = nullptr;
            if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                    reinterpret_cast<LPCSTR>(&s_ResourceAnchor), &module))
                return false;
            HRSRC resource = FindResourceA(module, MAKEINTRESOURCEA(IDR_OPENSHIM_LAUNCHER_PROXY), RT_RCDATA);
            HGLOBAL loaded = resource ? LoadResource(module, resource) : nullptr;
            data = loaded ? static_cast<const char*>(LockResource(loaded)) : nullptr;
            size = resource ? SizeofResource(module, resource) : 0;
            return data != nullptr && size != 0;
        }

        bool ReadFileBytes(const std::filesystem::path& path, std::vector<char>& out)
        {
            std::ifstream file(path, std::ios::binary);
            if (!file)
                return false;
            out.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
            return true;
        }

        // Same test as scripts/uninstall_windows.ps1 Test-OpenShimBinary: the
        // version resource carries the UTF-16 product name.
        bool IsOpenShimBinary(const std::vector<char>& bytes)
        {
            static const char kMarker[] = "B\0Z\0R\0 \0O\0p\0e\0n\0 \0S\0h\0i\0m\0";
            const size_t markerSize = sizeof(kMarker) - 1;
            return std::search(bytes.begin(), bytes.end(), kMarker, kMarker + markerSize) != bytes.end();
        }

        bool ShouldDeploy(const std::filesystem::path& launcherDir)
        {
            bool toggle = false;
            TryGetUserConfigBool("Steam", "SkipRebellionLauncher", toggle);
            std::error_code ec;
            return toggle && GetBzrDistribution() == BzrDistribution::Steam && !RunningUnderWine() &&
                   std::filesystem::is_regular_file(launcherDir / L"BZLauncher.exe", ec);
        }

        // Moves our copy aside, then deletes it. The rename works while the
        // launcher has it loaded; the delete then fails and a later start
        // finishes it.
        bool MoveAside(const std::filesystem::path& target, const std::filesystem::path& aside)
        {
            if (!MoveFileExW(target.c_str(), aside.c_str(), MOVEFILE_REPLACE_EXISTING))
                return false;
            DeleteFileW(aside.c_str());
            return true;
        }
    }

    bool SyncSteamLauncherProxy()
    {
        const std::filesystem::path gameRoot = GetMainModuleDirectory();
        if (gameRoot.empty())
            return true;
        const std::filesystem::path launcherDir = gameRoot / L"Launcher";
        const std::filesystem::path target = launcherDir / L"d3d9.dll";
        const std::filesystem::path aside = launcherDir / L"d3d9.dll.openshim-old";
        const std::filesystem::path staged = launcherDir / L"d3d9.dll.openshim-new";

        std::error_code ec;
        if (std::filesystem::exists(aside, ec))
            DeleteFileW(aside.c_str());

        std::vector<char> existing;
        const bool haveExisting = std::filesystem::exists(target, ec) && ReadFileBytes(target, existing);
        const bool existingIsOurs = haveExisting && IsOpenShimBinary(existing);

        if (!ShouldDeploy(launcherDir))
        {
            if (!existingIsOurs)
                return true;
            if (!MoveAside(target, aside))
            {
                LogShimA(LogLevel::Warn, kComponent, "[Launcher] could not remove Launcher\\d3d9.dll (error %lu)",
                         GetLastError());
                return false;
            }
            LogShimA(LogLevel::Info, kComponent, "[Launcher] removed Launcher\\d3d9.dll; Steam shows the launcher again");
            return true;
        }

        const char* data = nullptr;
        size_t size = 0;
        if (!LoadEmbeddedProxy(data, size))
        {
            LogShimA(LogLevel::Error, kComponent, "[Launcher] embedded launcher proxy missing from openshim.dll");
            return false;
        }
        if (haveExisting && existing.size() == size && std::equal(existing.begin(), existing.end(), data))
            return true;
        if (haveExisting && !existingIsOurs)
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[Launcher] Launcher\\d3d9.dll exists and is not OpenShim's; leaving it, launcher skip off");
            return false;
        }

        {
            std::ofstream out(staged, std::ios::binary | std::ios::trunc);
            out.write(data, static_cast<std::streamsize>(size));
            if (!out)
            {
                LogShimA(LogLevel::Warn, kComponent, "[Launcher] could not write %ls",
                         staged.wstring().c_str());
                DeleteFileW(staged.c_str());
                return false;
            }
        }
        if (haveExisting && !MoveAside(target, aside))
        {
            LogShimA(LogLevel::Warn, kComponent, "[Launcher] could not replace Launcher\\d3d9.dll (error %lu)",
                     GetLastError());
            DeleteFileW(staged.c_str());
            return false;
        }
        if (!MoveFileExW(staged.c_str(), target.c_str(), MOVEFILE_REPLACE_EXISTING))
        {
            LogShimA(LogLevel::Warn, kComponent, "[Launcher] could not install Launcher\\d3d9.dll (error %lu)",
                     GetLastError());
            DeleteFileW(staged.c_str());
            return false;
        }
        LogShimA(LogLevel::Info, kComponent, "[Launcher] %s Launcher\\d3d9.dll; Steam starts the game directly",
                 haveExisting ? "updated" : "installed");
        return true;
    }
}
