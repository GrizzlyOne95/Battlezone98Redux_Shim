#include "openshim_updater.h"

#include "BZROpenShim.h"
#include "bzr_string.h"
#include "hook_engine.h"
#include "openshim_update_manifest.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <process.h>
#include <wincrypt.h>

#include <algorithm>
#include <array>
#include <atomic>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <set>
#include <sstream>
#include <string>
#include <system_error>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "updater";
        constexpr char kWorkshopItemId[] = "3686673790";
        constexpr wchar_t kWorkshopItemIdW[] = L"3686673790";
        constexpr wchar_t kSteamAppIdW[] = L"301650";
        constexpr ULONGLONG kWorkshopTimeoutMs = 2 * 60 * 1000;
        constexpr ULONGLONG kWorkshopPollIntervalMs = 500;
        constexpr unsigned kReadyPollsRequired = 2;

        using FnGetWorkshopManager = void* (__cdecl*)();
        using FnEnsureWorkshopItem = bool (__thiscall*)(void*, const BzrString*, bool);
        using FnIsWorkshopItemReady = bool (__thiscall*)(void*, const BzrString*);

        struct CryptProvider
        {
            HCRYPTPROV handle = 0;
            ~CryptProvider() { if (handle) CryptReleaseContext(handle, 0); }
        };

        struct CryptHash
        {
            HCRYPTHASH handle = 0;
            ~CryptHash() { if (handle) CryptDestroyHash(handle); }
        };

        struct RuntimePayload
        {
            const OpenShimUpdatePayloadManifest* manifest = nullptr;
            std::filesystem::path source;
            std::filesystem::path destination;
            std::filesystem::path staged;
            std::filesystem::path backup;
        };

        std::atomic<OpenShimUpdateState> g_State{ OpenShimUpdateState::Idle };
        std::atomic<uint64_t> g_Generation{ 0 };
        std::mutex g_StatusMutex;
        std::string g_StatusMessage;
        std::atomic<bool> g_ShutdownRequested{ false };
        uintptr_t g_WorkerThread = 0;
        ULONGLONG g_CheckStartTick = 0;
        ULONGLONG g_LastWorkshopPollTick = 0;
        unsigned g_ReadyPollCount = 0;

        bool IsBusy(OpenShimUpdateState state)
        {
            return state == OpenShimUpdateState::WaitingForWorkshop ||
                state == OpenShimUpdateState::Validating;
        }

        void SetState(OpenShimUpdateState state, std::string message)
        {
            {
                std::lock_guard<std::mutex> lock(g_StatusMutex);
                g_StatusMessage = std::move(message);
            }
            g_State.store(state, std::memory_order_release);
            g_Generation.fetch_add(1, std::memory_order_acq_rel);
        }

        std::filesystem::path GetGameRoot()
        {
            std::wstring path(MAX_PATH, L'\0');
            for (;;)
            {
                const DWORD length = GetModuleFileNameW(
                    nullptr, path.data(), static_cast<DWORD>(path.size()));
                if (length == 0)
                    return {};
                if (length < path.size())
                {
                    path.resize(length);
                    return std::filesystem::path(path).parent_path();
                }
                path.resize(path.size() * 2);
            }
        }

        bool IsExecutableAddress(void* address)
        {
            if (!address)
                return false;
            MEMORY_BASIC_INFORMATION info = {};
            if (VirtualQuery(address, &info, sizeof(info)) != sizeof(info) ||
                info.State != MEM_COMMIT)
                return false;
            const DWORD protection = info.Protect & 0xFFu;
            return protection == PAGE_EXECUTE ||
                protection == PAGE_EXECUTE_READ ||
                protection == PAGE_EXECUTE_READWRITE ||
                protection == PAGE_EXECUTE_WRITECOPY;
        }

        bool ResolveWorkshopMethods(void*& manager,
                                    FnEnsureWorkshopItem& ensureItem,
                                    FnIsWorkshopItemReady& isReady,
                                    std::string& error)
        {
            manager = nullptr;
            ensureItem = nullptr;
            isReady = nullptr;

            const uint32_t getterAddress =
                HookEngine::ResolveNamedAddress("Workshop::GetManager");
            if (getterAddress == 0 ||
                !IsExecutableAddress(reinterpret_cast<void*>(getterAddress)))
            {
                error = "the Battlezone Workshop manager could not be resolved";
                return false;
            }

            __try
            {
                manager = reinterpret_cast<FnGetWorkshopManager>(getterAddress)();
                if (!manager)
                {
                    error = "the Battlezone Workshop manager is not initialized";
                    return false;
                }

                void** vtable = *reinterpret_cast<void***>(manager);
                if (!vtable || !IsExecutableAddress(vtable[1]) ||
                    !IsExecutableAddress(vtable[3]))
                {
                    error = "the Battlezone Workshop interface failed validation";
                    return false;
                }
                ensureItem = reinterpret_cast<FnEnsureWorkshopItem>(vtable[1]);
                isReady = reinterpret_cast<FnIsWorkshopItemReady>(vtable[3]);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                manager = nullptr;
                ensureItem = nullptr;
                isReady = nullptr;
                error = "the Battlezone Workshop interface raised an exception";
                return false;
            }

            return true;
        }

        bool InvokeWorkshopEnsure(bool requestDownload,
                                  bool& ready,
                                  std::string& error)
        {
            void* manager = nullptr;
            FnEnsureWorkshopItem ensureItem = nullptr;
            FnIsWorkshopItemReady isReady = nullptr;
            if (!ResolveWorkshopMethods(manager, ensureItem, isReady, error))
                return false;

            BzrString itemId = {};
            BzrStringInitEmpty(&itemId);
            BzrStringAssign(&itemId, kWorkshopItemId, sizeof(kWorkshopItemId) - 1);

            bool succeeded = true;
            __try
            {
                if (requestDownload)
                    ensureItem(manager, &itemId, true);
                ready = isReady(manager, &itemId);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                error = "the Battlezone Workshop request raised an exception";
                succeeded = false;
            }
            BzrStringFree(&itemId);
            return succeeded;
        }

        std::wstring ReadRegistryString(HKEY root,
                                        const wchar_t* subKey,
                                        const wchar_t* valueName)
        {
            DWORD type = 0;
            DWORD bytes = 0;
            if (RegGetValueW(root, subKey, valueName, RRF_RT_REG_SZ,
                             &type, nullptr, &bytes) != ERROR_SUCCESS || bytes < sizeof(wchar_t))
                return {};

            std::wstring value(bytes / sizeof(wchar_t), L'\0');
            if (RegGetValueW(root, subKey, valueName, RRF_RT_REG_SZ,
                             &type, value.data(), &bytes) != ERROR_SUCCESS)
                return {};
            while (!value.empty() && value.back() == L'\0')
                value.pop_back();
            return value;
        }

        std::string ReadSmallTextFile(const std::filesystem::path& path,
                                      size_t maximumBytes = 256 * 1024)
        {
            std::ifstream input(path, std::ios::binary);
            if (!input.is_open())
                return {};
            input.seekg(0, std::ios::end);
            const std::streamoff size = input.tellg();
            if (size < 0 || static_cast<uint64_t>(size) > maximumBytes)
                return {};
            input.seekg(0, std::ios::beg);
            std::string text(static_cast<size_t>(size), '\0');
            if (size > 0)
                input.read(text.data(), size);
            return input ? text : std::string();
        }

        std::vector<std::filesystem::path> FindSteamLibraries()
        {
            std::set<std::filesystem::path> libraries;
            const std::filesystem::path gameRoot = GetGameRoot();
            if (!gameRoot.empty())
            {
                const std::filesystem::path steamapps = gameRoot.parent_path().parent_path();
                if (steamapps.filename() == L"steamapps")
                    libraries.insert(steamapps.parent_path());
            }

            std::wstring steamPath = ReadRegistryString(
                HKEY_CURRENT_USER, L"Software\\Valve\\Steam", L"SteamPath");
            if (!steamPath.empty())
                libraries.insert(std::filesystem::path(steamPath));

            std::vector<std::filesystem::path> roots(libraries.begin(), libraries.end());
            for (size_t index = 0; index < roots.size(); ++index)
            {
                const std::string vdf = ReadSmallTextFile(
                    roots[index] / L"steamapps" / L"libraryfolders.vdf");
                size_t cursor = 0;
                while ((cursor = vdf.find("\"path\"", cursor)) != std::string::npos)
                {
                    const size_t quote = vdf.find('"', cursor + 6);
                    const size_t end = quote == std::string::npos
                        ? std::string::npos : vdf.find('"', quote + 1);
                    if (quote == std::string::npos || end == std::string::npos)
                        break;
                    std::string raw = vdf.substr(quote + 1, end - quote - 1);
                    std::string decoded;
                    decoded.reserve(raw.size());
                    for (size_t rawIndex = 0; rawIndex < raw.size(); ++rawIndex)
                    {
                        if (raw[rawIndex] == '\\' && rawIndex + 1 < raw.size() &&
                            raw[rawIndex + 1] == '\\')
                            ++rawIndex;
                        decoded.push_back(raw[rawIndex]);
                    }
                    if (!decoded.empty())
                        libraries.insert(std::filesystem::path(decoded));
                    cursor = end + 1;
                }
            }
            return std::vector<std::filesystem::path>(libraries.begin(), libraries.end());
        }

        bool FindWorkshopItemDirectory(std::filesystem::path& itemDirectory,
                                       std::string& error)
        {
            itemDirectory.clear();
            std::filesystem::file_time_type newest =
                std::filesystem::file_time_type::min();
            for (const auto& library : FindSteamLibraries())
            {
                const std::filesystem::path candidate = library / L"steamapps" /
                    L"workshop" / L"content" / kSteamAppIdW / kWorkshopItemIdW;
                std::error_code fileError;
                const std::filesystem::path manifest = candidate / L"OpenShimManifest.lua";
                if (!std::filesystem::is_regular_file(manifest, fileError) || fileError)
                    continue;
                const auto modified = std::filesystem::last_write_time(manifest, fileError);
                if (!fileError && (itemDirectory.empty() || modified > newest))
                {
                    itemDirectory = candidate;
                    newest = modified;
                }
            }
            if (itemDirectory.empty())
            {
                error = "Workshop item 3686673790 is not installed in a Steam library";
                return false;
            }
            return true;
        }

        bool ComputeSha256(const std::filesystem::path& path,
                           std::string& output,
                           uint64_t& fileSize,
                           std::string& error)
        {
            output.clear();
            fileSize = 0;
            std::ifstream input(path, std::ios::binary);
            if (!input.is_open())
            {
                error = "could not open " + path.filename().string();
                return false;
            }
            input.seekg(0, std::ios::end);
            const std::streamoff size = input.tellg();
            if (size < 0)
            {
                error = "could not read " + path.filename().string() + " size";
                return false;
            }
            fileSize = static_cast<uint64_t>(size);
            input.seekg(0, std::ios::beg);

            CryptProvider provider;
            CryptHash hash;
            if (!CryptAcquireContextW(&provider.handle, nullptr, nullptr,
                                      PROV_RSA_AES, CRYPT_VERIFYCONTEXT) ||
                !CryptCreateHash(provider.handle, CALG_SHA_256, 0, 0, &hash.handle))
            {
                error = "Windows SHA-256 initialization failed";
                return false;
            }

            std::array<char, 64 * 1024> buffer = {};
            while (input.good())
            {
                input.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
                const std::streamsize read = input.gcount();
                if (read > 0 && !CryptHashData(
                    hash.handle, reinterpret_cast<const BYTE*>(buffer.data()),
                    static_cast<DWORD>(read), 0))
                {
                    error = "Windows SHA-256 update failed";
                    return false;
                }
            }

            std::array<BYTE, 32> digest = {};
            DWORD digestSize = static_cast<DWORD>(digest.size());
            if (!CryptGetHashParam(hash.handle, HP_HASHVAL, digest.data(), &digestSize, 0) ||
                digestSize != digest.size())
            {
                error = "Windows SHA-256 finalization failed";
                return false;
            }
            std::ostringstream text;
            text << std::hex << std::setfill('0');
            for (const BYTE byte : digest)
                text << std::setw(2) << static_cast<unsigned>(byte);
            output = text.str();
            return true;
        }

        bool ValidateX86Dll(const std::filesystem::path& path, std::string& error)
        {
            std::ifstream input(path, std::ios::binary);
            IMAGE_DOS_HEADER dos = {};
            input.read(reinterpret_cast<char*>(&dos), sizeof(dos));
            if (!input || dos.e_magic != IMAGE_DOS_SIGNATURE || dos.e_lfanew <= 0)
            {
                error = "OpenShim payload has an invalid DOS header";
                return false;
            }
            input.seekg(dos.e_lfanew, std::ios::beg);
            DWORD signature = 0;
            IMAGE_FILE_HEADER file = {};
            input.read(reinterpret_cast<char*>(&signature), sizeof(signature));
            input.read(reinterpret_cast<char*>(&file), sizeof(file));
            if (!input || signature != IMAGE_NT_SIGNATURE ||
                file.Machine != IMAGE_FILE_MACHINE_I386 ||
                (file.Characteristics & IMAGE_FILE_DLL) == 0)
            {
                error = "OpenShim payload is not an x86 DLL";
                return false;
            }
            return true;
        }

        bool ReadFileVersion(const std::filesystem::path& path, std::string& version)
        {
            DWORD ignored = 0;
            const DWORD size = GetFileVersionInfoSizeW(path.c_str(), &ignored);
            if (size == 0)
                return false;
            std::vector<BYTE> data(size);
            if (!GetFileVersionInfoW(path.c_str(), 0, size, data.data()))
                return false;
            VS_FIXEDFILEINFO* info = nullptr;
            UINT infoSize = 0;
            if (!VerQueryValueW(data.data(), L"\\", reinterpret_cast<void**>(&info),
                                &infoSize) || !info || infoSize < sizeof(*info))
                return false;
            std::ostringstream text;
            text << HIWORD(info->dwFileVersionMS) << '.' << LOWORD(info->dwFileVersionMS)
                 << '.' << HIWORD(info->dwFileVersionLS) << '.' << LOWORD(info->dwFileVersionLS);
            version = text.str();
            return true;
        }

        bool ParseVersion(const std::string& text, std::vector<uint32_t>& parts)
        {
            parts.clear();
            size_t begin = 0;
            while (begin < text.size())
            {
                const size_t end = text.find('.', begin);
                const std::string part = text.substr(begin,
                    end == std::string::npos ? std::string::npos : end - begin);
                if (part.empty() || !std::all_of(part.begin(), part.end(), [](unsigned char ch)
                    { return std::isdigit(ch) != 0; }))
                    return false;
                try { parts.push_back(static_cast<uint32_t>(std::stoul(part))); }
                catch (...) { return false; }
                if (end == std::string::npos)
                    break;
                begin = end + 1;
            }
            return !parts.empty();
        }

        int CompareVersions(const std::string& left, const std::string& right)
        {
            std::vector<uint32_t> leftParts;
            std::vector<uint32_t> rightParts;
            if (!ParseVersion(left, leftParts) || !ParseVersion(right, rightParts))
                return 0;
            const size_t count = (std::max)(leftParts.size(), rightParts.size());
            for (size_t index = 0; index < count; ++index)
            {
                const uint32_t lhs = index < leftParts.size() ? leftParts[index] : 0;
                const uint32_t rhs = index < rightParts.size() ? rightParts[index] : 0;
                if (lhs < rhs) return -1;
                if (lhs > rhs) return 1;
            }
            return 0;
        }

        std::wstring QuoteCommandLineArgument(const std::wstring& value)
        {
            if (value.empty())
                return L"\"\"";
            if (value.find_first_of(L" \t\n\v\"") == std::wstring::npos)
                return value;

            std::wstring quoted(1, L'"');
            size_t backslashes = 0;
            for (const wchar_t ch : value)
            {
                if (ch == L'\\')
                {
                    ++backslashes;
                    continue;
                }
                if (ch == L'"')
                {
                    quoted.append(backslashes * 2 + 1, L'\\');
                    quoted.push_back(ch);
                    backslashes = 0;
                    continue;
                }
                quoted.append(backslashes, L'\\');
                backslashes = 0;
                quoted.push_back(ch);
            }
            quoted.append(backslashes * 2, L'\\');
            quoted.push_back(L'"');
            return quoted;
        }

        bool LaunchHiddenProcess(const std::filesystem::path& executable,
                                 const std::vector<std::wstring>& arguments,
                                 std::string& error)
        {
            std::wstring commandLine = QuoteCommandLineArgument(executable.wstring());
            for (const auto& argument : arguments)
            {
                commandLine.push_back(L' ');
                commandLine += QuoteCommandLineArgument(argument);
            }
            std::vector<wchar_t> mutableCommand(commandLine.begin(), commandLine.end());
            mutableCommand.push_back(L'\0');

            STARTUPINFOW startup = {};
            startup.cb = sizeof(startup);
            startup.dwFlags = STARTF_USESHOWWINDOW;
            startup.wShowWindow = SW_HIDE;
            PROCESS_INFORMATION process = {};
            if (!CreateProcessW(executable.c_str(), mutableCommand.data(), nullptr, nullptr,
                                FALSE, CREATE_NO_WINDOW | DETACHED_PROCESS |
                                CREATE_BREAKAWAY_FROM_JOB,
                                nullptr, nullptr, &startup, &process))
            {
                error = std::error_code(static_cast<int>(GetLastError()),
                                        std::system_category()).message();
                return false;
            }
            CloseHandle(process.hThread);
            CloseHandle(process.hProcess);
            return true;
        }

        void WriteInstallerStatus(const std::filesystem::path& path,
                                  const char* state,
                                  const std::string& hash,
                                  const char* detail)
        {
            std::ofstream output(path, std::ios::trunc);
            if (output.is_open())
                output << "state=" << state << "\nexpected_sha256=" << hash
                       << "\ndetail=" << detail << "\n";
        }

        bool ValidatePayload(const RuntimePayload& payload, std::string& error)
        {
            std::string hash;
            uint64_t size = 0;
            if (!ComputeSha256(payload.source, hash, size, error))
                return false;
            if (hash != payload.manifest->sha256 || size != payload.manifest->size)
            {
                error = payload.source.filename().string() +
                    " does not match the Workshop manifest metadata";
                return false;
            }
            return true;
        }

        bool InstalledPayloadMatches(const RuntimePayload& payload)
        {
            std::string hash;
            uint64_t size = 0;
            std::string ignored;
            return ComputeSha256(payload.destination, hash, size, ignored) &&
                hash == payload.manifest->sha256 && size == payload.manifest->size;
        }

        bool StageSuite(const std::filesystem::path& itemDirectory,
                        const OpenShimUpdateManifest& manifest,
                        std::array<RuntimePayload, 3>& payloads,
                        std::string& error)
        {
            const std::filesystem::path helper = itemDirectory / L"bzfile_replace_helper.exe";
            std::error_code fileError;
            if (!std::filesystem::is_regular_file(helper, fileError) || fileError)
            {
                error = "bzfile_replace_helper.exe is missing from the Workshop item";
                return false;
            }

            HANDLE existingMutex = OpenMutexW(SYNCHRONIZE, FALSE,
                                                L"Local\\BZR_OpenShim_Update");
            if (existingMutex)
            {
                CloseHandle(existingMutex);
                SetState(OpenShimUpdateState::Staged,
                         "An OpenShim update is already staged. Close and restart Battlezone to install it.");
                return true;
            }

            for (size_t index = 0; index < payloads.size(); ++index)
            {
                const std::wstring prefix(payloads[index].manifest->sha256.begin(),
                                          payloads[index].manifest->sha256.begin() + 12);
                payloads[index].staged = itemDirectory /
                    (L"openshim_suite_" + std::to_wstring(index + 1) +
                     L".pending." + prefix);
                fileError.clear();
                std::filesystem::copy_file(payloads[index].source,
                    payloads[index].staged,
                    std::filesystem::copy_options::overwrite_existing, fileError);
                if (fileError)
                {
                    for (size_t cleanup = 0; cleanup <= index; ++cleanup)
                    {
                        std::error_code ignored;
                        std::filesystem::remove(payloads[cleanup].staged, ignored);
                    }
                    error = "could not stage " + payloads[index].source.filename().string() +
                        ": " + fileError.message();
                    return false;
                }
            }

            const std::filesystem::path gameRoot = GetGameRoot();
            const std::filesystem::path status = gameRoot / L"openshim_update.status";
            const std::filesystem::path log = GetGameLogPath("openshim_update.log");
            std::vector<std::wstring> arguments = {
                L"--suite", std::to_wstring(GetCurrentProcessId()),
                log.wstring(), status.wstring()
            };
            for (const auto& payload : payloads)
            {
                arguments.push_back(payload.staged.wstring());
                arguments.push_back(payload.destination.wstring());
                arguments.emplace_back(payload.manifest->sha256.begin(),
                                       payload.manifest->sha256.end());
                arguments.push_back(payload.backup.wstring());
            }

            WriteInstallerStatus(status, "staged", manifest.sha256, "suite verified by OpenShim");
            if (!LaunchHiddenProcess(helper, arguments, error))
            {
                for (const auto& payload : payloads)
                {
                    std::error_code ignored;
                    std::filesystem::remove(payload.staged, ignored);
                }
                WriteInstallerStatus(status, "failed", manifest.sha256,
                                     "could not launch replacement helper");
                return false;
            }
            return true;
        }

        unsigned __stdcall ValidationThreadProc(void*)
        {
            std::filesystem::path itemDirectory;
            std::string error;
            if (!FindWorkshopItemDirectory(itemDirectory, error))
            {
                SetState(OpenShimUpdateState::Failed, "Update check failed: " + error + ".");
                return 0;
            }

            const std::string manifestText =
                ReadSmallTextFile(itemDirectory / L"OpenShimManifest.lua", 64 * 1024);
            OpenShimUpdateManifest manifest;
            if (manifestText.empty() ||
                !ParseOpenShimUpdateManifest(manifestText, manifest, error))
            {
                SetState(OpenShimUpdateState::Failed,
                         "Update check failed: the Workshop OpenShim manifest is invalid.");
                LogShimA(LogLevel::Error, kComponent,
                         "Manifest validation failed at %ls: %s",
                         itemDirectory.c_str(), error.c_str());
                return 0;
            }

            const std::filesystem::path gameRoot = GetGameRoot();
            std::array<RuntimePayload, 3> payloads = {{
                { &manifest.winmm, itemDirectory / L"winmm.dll",
                  gameRoot / L"winmm.dll", {}, gameRoot / L"winmm.dll.previous" },
                { &manifest.network, itemDirectory / L"openshim_net.ini.payload",
                  gameRoot / L"net.ini", {}, gameRoot / L"net.ini.previous" },
                { &manifest.patches, itemDirectory / L"openshim_patches.json.payload",
                  gameRoot / L"scripts" / L"patches.json", {},
                  gameRoot / L"scripts" / L"patches.json.previous" },
            }};

            for (const auto& payload : payloads)
            {
                if (g_ShutdownRequested.load(std::memory_order_acquire))
                    return 0;
                if (!ValidatePayload(payload, error))
                {
                    SetState(OpenShimUpdateState::Failed,
                             "Update check failed: " + error + ".");
                    LogShimA(LogLevel::Error, kComponent, "%s", error.c_str());
                    return 0;
                }
            }
            if (!ValidateX86Dll(payloads[0].source, error))
            {
                SetState(OpenShimUpdateState::Failed, "Update check failed: " + error + ".");
                return 0;
            }

            const bool allCurrent = std::all_of(payloads.begin(), payloads.end(),
                [](const RuntimePayload& payload) { return InstalledPayloadMatches(payload); });
            if (allCurrent)
            {
                SetState(OpenShimUpdateState::UpToDate,
                         "OpenShim " + manifest.version + " is up to date.");
                return 0;
            }

            std::string installedVersion;
            if (ReadFileVersion(payloads[0].destination, installedVersion) &&
                CompareVersions(installedVersion, manifest.version) > 0)
            {
                SetState(OpenShimUpdateState::UpToDate,
                         "Installed OpenShim " + installedVersion +
                         " is newer than Workshop " + manifest.version + "; no downgrade was staged.");
                return 0;
            }

            if (!StageSuite(itemDirectory, manifest, payloads, error))
            {
                SetState(OpenShimUpdateState::Failed,
                         "Update staging failed: " + error + ". See openshim_update.log.");
                LogShimA(LogLevel::Error, kComponent, "Suite staging failed: %s", error.c_str());
                return 0;
            }

            if (g_State.load(std::memory_order_acquire) != OpenShimUpdateState::Staged)
            {
                SetState(OpenShimUpdateState::Staged,
                         "OpenShim " + manifest.version +
                         " is staged. Close and restart Battlezone to install it.");
            }
            LogShimA(LogLevel::Info, kComponent,
                     "OpenShim suite %s staged from Workshop item %s",
                     manifest.version.c_str(), kWorkshopItemId);
            return 0;
        }

        void CloseFinishedWorker()
        {
            if (!g_WorkerThread)
                return;
            HANDLE thread = reinterpret_cast<HANDLE>(g_WorkerThread);
            if (WaitForSingleObject(thread, 0) == WAIT_OBJECT_0)
            {
                CloseHandle(thread);
                g_WorkerThread = 0;
            }
        }

        bool StartValidationWorker()
        {
            CloseFinishedWorker();
            if (g_WorkerThread)
                return true;
            SetState(OpenShimUpdateState::Validating,
                     "Workshop download is ready. Verifying the OpenShim update...");
            g_WorkerThread = _beginthreadex(nullptr, 0, ValidationThreadProc,
                                            nullptr, 0, nullptr);
            if (!g_WorkerThread)
            {
                SetState(OpenShimUpdateState::Failed,
                         "Update check failed: could not start the validation worker.");
                return false;
            }
            return true;
        }
    }

    bool BeginOpenShimUpdateCheck()
    {
        CloseFinishedWorker();
        if (IsBusy(g_State.load(std::memory_order_acquire)))
            return false;
        if (!IsCompatibleGameVersion() || !IsPatchingComplete())
        {
            SetState(OpenShimUpdateState::Unsupported,
                     "Update checking is unavailable on an unsupported Battlezone build.");
            return false;
        }
        if (GetBzrDistribution() != BzrDistribution::Steam)
        {
            SetState(OpenShimUpdateState::Unsupported,
                     "Steam Workshop update checks are available in the Steam build of Battlezone.");
            return false;
        }

        bool ready = false;
        std::string error;
        if (!InvokeWorkshopEnsure(true, ready, error))
        {
            SetState(OpenShimUpdateState::Failed, "Update check failed: " + error + ".");
            LogShimA(LogLevel::Error, kComponent, "Workshop request failed: %s", error.c_str());
            return false;
        }

        g_CheckStartTick = GetTickCount64();
        g_LastWorkshopPollTick = 0;
        g_ReadyPollCount = ready ? 1u : 0u;
        SetState(OpenShimUpdateState::WaitingForWorkshop,
                 ready ? "Checking Steam Workshop for OpenShim updates..."
                       : "Downloading the latest OpenShim package from Steam Workshop...");
        LogShimA(LogLevel::Info, kComponent,
                 "Requested Workshop item %s; initiallyReady=%u",
                 kWorkshopItemId, ready ? 1u : 0u);
        return true;
    }

    void PollOpenShimUpdateCheck()
    {
        if (g_State.load(std::memory_order_acquire) !=
            OpenShimUpdateState::WaitingForWorkshop)
            return;

        const ULONGLONG now = GetTickCount64();
        if (now - g_CheckStartTick >= kWorkshopTimeoutMs)
        {
            SetState(OpenShimUpdateState::Failed,
                     "Steam Workshop did not finish the update check in time. Try Refresh in New Game, then retry.");
            return;
        }
        if (g_LastWorkshopPollTick != 0 &&
            now - g_LastWorkshopPollTick < kWorkshopPollIntervalMs)
            return;
        g_LastWorkshopPollTick = now;

        bool ready = false;
        std::string error;
        if (!InvokeWorkshopEnsure(false, ready, error))
        {
            SetState(OpenShimUpdateState::Failed, "Update check failed: " + error + ".");
            return;
        }
        if (!ready)
        {
            g_ReadyPollCount = 0;
            return;
        }
        if (++g_ReadyPollCount >= kReadyPollsRequired)
            StartValidationWorker();
    }

    OpenShimUpdateSnapshot GetOpenShimUpdateSnapshot()
    {
        OpenShimUpdateSnapshot snapshot;
        snapshot.state = g_State.load(std::memory_order_acquire);
        snapshot.generation = g_Generation.load(std::memory_order_acquire);
        snapshot.busy = IsBusy(snapshot.state);
        std::lock_guard<std::mutex> lock(g_StatusMutex);
        snapshot.message = g_StatusMessage;
        return snapshot;
    }

    void CancelOpenShimUpdateCheck(const char* reason)
    {
        if (g_State.load(std::memory_order_acquire) ==
            OpenShimUpdateState::WaitingForWorkshop)
        {
            SetState(OpenShimUpdateState::Failed,
                     reason && *reason ? reason : "The update check was cancelled.");
        }
    }

    void ShutdownOpenShimUpdater()
    {
        g_ShutdownRequested.store(true, std::memory_order_release);
        if (g_WorkerThread)
        {
            HANDLE thread = reinterpret_cast<HANDLE>(g_WorkerThread);
            // Shutdown() is explicitly a normal-thread, fully joined teardown.
            // Do not leave updater code executing after its handle is closed.
            WaitForSingleObject(thread, INFINITE);
            CloseHandle(thread);
            g_WorkerThread = 0;
        }
        SetState(OpenShimUpdateState::Idle, {});
    }
}
