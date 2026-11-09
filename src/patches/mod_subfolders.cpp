// mod_subfolders.cpp
// BZR Open Shim - opt-in: also mount the subfolders of an addon / mods /
// packaged_mods / Workshop mod folder, not just its top level.
//
// Stock: every mount path (buildMPResources, buildSingleMPResource,
// buildIAResources, ... FUN_0076A030..FUN_0076B7A0) hands the mod's folder to
// the source table at 0x00820E00 (cdecl bool(const char* path); 0x800 slots of
// 0x100 bytes, case-insensitive de-duplicated, strncpy 0xFF). The virtual file
// system is then built from that table (0x00820F10 -> 0x00827910 per source,
// 0x008282E0 -> 0x008283E0 -> scan 0x008279C0). The scan lists one directory
// per source, non-recursively, and keys every file by its lower-cased name cut
// to 16 characters (0x00827640); entries with the same key from different
// sources are kept and ordered by source index (0x00828180).
//
// This detours 0x00820E00. After the original registers a mod root (a path
// whose parent folder is addon, mods, packaged_mods or workshop\content\301650)
// each descendant directory that holds files is registered the same way,
// shallowest first and alphabetical within a level, so the order is
// deterministic and a file in the mod root always precedes a same-named file
// in a subfolder. Duplicate file names are logged.
//
// The 16-character limit applies to file names only; folder names count only
// toward the 255-character path limit, so deep or long folder names are
// skipped with a warning when the full path would not fit.
//
// Precedence: a mod's subfolders are registered right after that mod's root,
// so they rank above the roots of mods registered later (stock: every root of
// an earlier mod outranks a later one).
//
// Multiplayer: the stock whitelist check (FUN_0076E020) tests the files of the
// mod root's top level, so subfolder content is never vetted. In a network
// game (or when the caller is one of the MP mount builders) a subfolder is
// therefore registered only if every file in it passes the same whitelist
// (plus .tga when AllowTgaInMultiplayerMods is on). A peer without this
// setting does not mount subfolders at all, so its asset view differs.
//
// Off unless [Mods] RecurseModSubfolders = 1.
#include "bzr_hooks.h"
#include "hook_engine.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>
#include <intrin.h>

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            namespace fs = std::filesystem;
            using FnRegisterSource = unsigned char(__cdecl*)(const char* path);

            // push ebp / mov ebp,esp / sub esp,8 / mov [ebp-4],0: 13 bytes.
            constexpr size_t kRegisterPatchLen = 13;
            constexpr uint8_t kRegisterStock[kRegisterPatchLen] =
                { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x08, 0xC7, 0x45, 0xFC, 0x00, 0x00, 0x00, 0x00 };

            // The MP mount builders: FUN_0076A240 (buildMPResources, up to
            // 0x0076A430) and FUN_0076B350 (buildSingleMPResource, up to 0x0076B7A0).
            constexpr uintptr_t kMpBuilderRanges[2][2] = {
                { 0x0076A240, 0x0076A430 }, { 0x0076B350, 0x0076B7A0 } };

            constexpr size_t kEnginePathLimit = 0xFF;   // strncpy(…, 0xFF)
            constexpr size_t kEngineNameKey = 16;       // FUN_00827640
            constexpr int kMaxDepth = 8;
            constexpr size_t kMaxDirsPerRoot = 256;

            InlineDetour32 g_RegisterDetour = {};
            FnRegisterSource g_OrigRegister = nullptr;
            volatile bool g_Recurse = false;
            bool g_AllowTga = false;
            bool g_ConfigInitialized = false;
            bool g_InExpand = false;

            std::string Lower(std::string s)
            {
                for (char& c : s)
                    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                return s;
            }

            bool EndsWith(const std::string& s, const char* suffix)
            {
                const size_t n = std::char_traits<char>::length(suffix);
                return s.size() >= n && s.compare(s.size() - n, n, suffix) == 0;
            }

            bool IsModRootPath(const fs::path& p)
            {
                const fs::path parent = p.parent_path();
                const std::string pn = Lower(parent.filename().string());
                if (pn == "addon" || pn == "mods" || pn == "packaged_mods")
                    return true;
                // ...\workshop\content\301650\<id>
                if (pn == "301650" && Lower(parent.parent_path().filename().string()) == "content")
                    return true;
                return false;
            }

            // Same list FUN_00767A30 builds, plus .tga when allowed.
            bool PassesMpWhitelist(const std::string& lowerName)
            {
                static const char* const kExt[] = {
                    ".wav", ".ogg", ".ini", ".inf", ".jpg", ".txt", ".stb", ".des", ".dds", ".png", ".sta" };
                for (const char* e : kExt)
                    if (EndsWith(lowerName, e))
                        return true;
                if (EndsWith(lowerName, "mod.material"))
                    return true;
                return g_AllowTga && EndsWith(lowerName, ".tga");
            }

            bool IsReparsePoint(const fs::path& p)
            {
                const DWORD a = GetFileAttributesW(p.c_str());
                return a != INVALID_FILE_ATTRIBUTES && (a & FILE_ATTRIBUTE_REPARSE_POINT) != 0;
            }

            bool CallerIsMpBuilder(uintptr_t ret)
            {
                for (const auto& r : kMpBuilderRanges)
                    if (ret >= r[0] && ret < r[1])
                        return true;
                return false;
            }

            struct DirInfo
            {
                fs::path path;
                std::vector<std::string> lowerFiles;  // regular file names, lower-case
            };

            bool ListDir(const fs::path& dir, DirInfo& info, std::vector<fs::path>& subdirs)
            {
                std::error_code ec;
                info.path = dir;
                for (fs::directory_iterator it(dir, ec), end; !ec && it != end; it.increment(ec))
                {
                    std::error_code e2;
                    if (it->is_directory(e2) && !e2)
                    {
                        const std::string name = it->path().filename().string();
                        if (!name.empty() && name[0] != '.' && !IsReparsePoint(it->path()))
                            subdirs.push_back(it->path());
                    }
                    else if (it->is_regular_file(e2) && !e2)
                    {
                        info.lowerFiles.push_back(Lower(it->path().filename().string()));
                    }
                }
                std::sort(subdirs.begin(), subdirs.end(), [](const fs::path& a, const fs::path& b) {
                    return Lower(a.filename().string()) < Lower(b.filename().string());
                });
                return !ec;
            }

            void ExpandModRoot(const char* rootPath, bool strictMp)
            {
                std::error_code ec;
                std::string rootStr(rootPath);
                while (rootStr.size() > 1 && (rootStr.back() == '\\' || rootStr.back() == '/'))
                    rootStr.pop_back();
                const fs::path root(rootStr);
                if (!IsModRootPath(root) || !fs::is_directory(root, ec) || ec)
                    return;

                // file-name key (16 chars) -> directory that listed it first
                std::unordered_map<std::string, fs::path> seen;
                auto noteFiles = [&](const DirInfo& d) {
                    for (const std::string& f : d.lowerFiles)
                    {
                        const std::string key = f.substr(0, kEngineNameKey);
                        auto ins = seen.emplace(key, d.path);
                        if (!ins.second && ins.first->second != d.path)
                            Log(L"[MODSUB] duplicate file name '%hs': first in %hs, also in %hs\n",
                                f.c_str(), ins.first->second.string().c_str(), d.path.string().c_str());
                    }
                };

                std::vector<fs::path> level;
                {
                    DirInfo rootInfo;
                    ListDir(root, rootInfo, level);
                    noteFiles(rootInfo);
                }

                size_t registered = 0, skipped = 0, visited = 0;
                for (int depth = 1; depth <= kMaxDepth && !level.empty(); ++depth)
                {
                    std::vector<fs::path> next;
                    for (const fs::path& dir : level)
                    {
                        if (++visited > kMaxDirsPerRoot)
                        {
                            Log(L"[MODSUB] %hs: more than %u subfolders; the rest are not mounted\n",
                                rootPath, static_cast<unsigned>(kMaxDirsPerRoot));
                            next.clear();
                            goto done;
                        }
                        DirInfo info;
                        try { ListDir(dir, info, next); }
                        catch (...) { ++skipped; continue; }
                        {
                            // The engine takes ANSI paths: skip names that do not round-trip.
                            const std::string probe = dir.string();
                            if (probe.find('?') != std::string::npos)
                            {
                                Log(L"[MODSUB] skipping folder with non-ANSI characters: %hs\n", probe.c_str());
                                ++skipped;
                                continue;
                            }
                        }
                        if (info.lowerFiles.empty())
                            continue;

                        if (strictMp)
                        {
                            bool ok = true;
                            for (const std::string& f : info.lowerFiles)
                            {
                                if (!PassesMpWhitelist(f))
                                {
                                    Log(L"[MODSUB] network game: skipping %hs (non-whitelisted file '%hs')\n",
                                        dir.string().c_str(), f.c_str());
                                    ok = false;
                                    break;
                                }
                            }
                            if (!ok)
                            {
                                ++skipped;
                                continue;
                            }
                        }

                        std::string narrow;
                        try { narrow = fs::path(dir).make_preferred().string(); }
                        catch (...) { ++skipped; continue; }
                        if (narrow.size() >= kEnginePathLimit)
                        {
                            Log(L"[MODSUB] path too long for the engine source table (%u chars): %hs\n",
                                static_cast<unsigned>(narrow.size()), narrow.c_str());
                            ++skipped;
                            continue;
                        }
                        noteFiles(info);
                        if (g_OrigRegister(narrow.c_str()))
                            ++registered;
                        else
                            Log(L"[MODSUB] source table refused %hs (full or already registered)\n", narrow.c_str());
                    }
                    level = std::move(next);
                }
            done:
                if (registered || skipped)
                    Log(L"[MODSUB] %hs: %u subfolder source(s) registered, %u skipped\n",
                        rootPath, static_cast<unsigned>(registered), static_cast<unsigned>(skipped));
            }

            unsigned char __cdecl RegisterSourceHook(const char* path)
            {
                const uintptr_t ret = reinterpret_cast<uintptr_t>(_ReturnAddress());
                const unsigned char result = g_OrigRegister(path);
                // A refused root (duplicate or full table) was already expanded or cannot be.
                if (result && g_Recurse && path && *path && !g_InExpand)
                {
                    g_InExpand = true;
                    try
                    {
                        // Unknown session state is treated as multiplayer.
                        ExpandModRoot(path, CallerIsMpBuilder(ret) || !IsSinglePlayerSession());
                    }
                    catch (...)
                    {
                        Log(L"[MODSUB] exception while expanding %hs; ignored\n", path);
                    }
                    g_InExpand = false;
                }
                return result;
            }

            void InstallRegisterDetour()
            {
                if (g_OrigRegister)
                    return;
                const uintptr_t addr = HookEngine::EngineAddress("ModSourceRegister");
                if (addr == 0)
                {
                    Log(L"[MODSUB] ModSourceRegister did not resolve; leaving mod folders flat\n");
                    return;
                }
                if (!ExpectedBytesMatchAt(addr, kRegisterStock, sizeof(kRegisterStock)))
                {
                    Log(L"[MODSUB] Register bytes at 0x%08X are not stock; standing down\n",
                        static_cast<uint32_t>(addr));
                    return;
                }
                if (!InstallInlineDetour32(g_RegisterDetour, addr, reinterpret_cast<void*>(RegisterSourceHook),
                                           kRegisterPatchLen, kRegisterStock, sizeof(kRegisterStock)))
                {
                    Log(L"[MODSUB] Detour install failed at 0x%08X\n", static_cast<uint32_t>(addr));
                    return;
                }
                g_OrigRegister = reinterpret_cast<FnRegisterSource>(g_RegisterDetour.trampoline);
                Log(L"[MODSUB] Source registration hooked at 0x%08X\n", static_cast<uint32_t>(addr));
            }
        }

        void InitializeModSubfoldersConfig()
        {
            if (g_ConfigInitialized)
                return;
            g_ConfigInitialized = true;
            bool cfg = false;
            const bool on = TryGetUserConfigBool("Mods", "RecurseModSubfolders", cfg) && cfg;
            cfg = false;
            g_AllowTga = TryGetUserConfigBool(kUserConfigNetworkSection, "AllowTgaInMultiplayerMods", cfg) && cfg;
            g_Recurse = on;
            Log(L"[MODSUB] RecurseModSubfolders=%hs\n", on ? "on" : "off");
            if (on)
                InstallRegisterDetour();
        }

        void ReloadModSubfoldersConfig()
        {
            g_ConfigInitialized = false;
            InitializeModSubfoldersConfig();
        }
    }
}
