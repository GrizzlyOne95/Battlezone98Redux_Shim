// des_reader.cpp
// BZR Open Shim - shared briefing page reader (include/des_reader.h), split
// out of lobby_briefing.cpp so the Database screen's Briefings tab reads pages
// the same way. Behaviour is unchanged from the lobby's own copy.
#include <Windows.h>
#include "des_reader.h"
#include "bzr_hooks_internal.h"
#include "hook_engine.h"
#include "patcher.h"
#include "lobby_briefing_policy.h"
#include <vector>

namespace BZROpenShim::DesReader
{
    namespace
    {
        namespace Pages = BriefingPagesPolicy;

        constexpr size_t kDesBufferSize = 0x1F401; // loader caps at 0x1F400 + NUL

        using FnDesLoad = uintptr_t(__cdecl*)(const char* name, char* buffer);
        using FnResourceSize = size_t(__cdecl*)(const char* name);

        bool g_Bound = false;
        uint32_t g_DesLoadAddr = 0;
        FnResourceSize g_ResourceSize = nullptr;
        void*(__cdecl* g_OgreGroupManager)() = nullptr;
        bool(__thiscall* g_OgreResourceExists)(void*, const std::string&) = nullptr;

        void* OgreManagerSeh()
        {
            __try
            {
                return g_OgreGroupManager();
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        bool OgreExistsSeh(void* manager, const std::string& name, bool& exists)
        {
            __try
            {
                exists = g_OgreResourceExists(manager, name);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            return true;
        }
    }

    bool Bind()
    {
        if (g_Bound)
            return true;
        const HookEngine::EngineRow rows[] = {
            { "DescriptionFileLoad", &g_DesLoadAddr },
        };
        if (!HookEngine::BindEngineRows("Briefing page reader", rows))
            return false;
        g_ResourceSize = reinterpret_cast<FnResourceSize>(
            static_cast<uintptr_t>(HookEngine::ResolveNamedAddress("Music::ResourceSize")));
        if (!g_ResourceSize)
        {
            Log(L"[DESREADER] Music::ResourceSize unresolved; briefing pages unavailable\n");
            return false;
        }
        g_OgreGroupManager = Hooks::ResolveOgreProc<decltype(g_OgreGroupManager)>(
            "?getSingletonPtr@ResourceGroupManager@Ogre@@SAPAV12@XZ");
        g_OgreResourceExists = Hooks::ResolveOgreProc<decltype(g_OgreResourceExists)>(
            "?resourceExistsInAnyGroup@ResourceGroupManager@Ogre@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
        if (!g_OgreGroupManager || !g_OgreResourceExists)
            Log(L"[DESREADER] Ogre resource lookup unavailable; page images off\n");
        g_Bound = true;
        return true;
    }

    bool ImagesAvailable()
    {
        return g_OgreGroupManager && g_OgreResourceExists;
    }

    size_t ResourceSize(const std::string& name)
    {
        return g_ResourceSize && name.size() <= Pages::kMaxNameLength ? g_ResourceSize(name.c_str()) : 0;
    }

    bool ResourceExists(const std::string& name)
    {
        return ResourceSize(name) > 0;
    }

    // Images load through Ogre's resource groups, so look them up there.
    bool ImageExists(const std::string& name)
    {
        if (!ImagesAvailable())
            return false;
        void* manager = OgreManagerSeh();
        bool exists = false;
        return manager && OgreExistsSeh(manager, name, exists) && exists;
    }

    std::string LoadPage(const std::string& file)
    {
        if (!g_DesLoadAddr)
            return std::string();
        std::vector<char> buffer(kDesBufferSize, '\0');
        std::vector<char> name(file.begin(), file.end());
        name.push_back('\0');
        reinterpret_cast<FnDesLoad>(static_cast<uintptr_t>(g_DesLoadAddr))(name.data(), buffer.data());
        buffer.back() = '\0';
        return LobbyBriefingPolicy::ClipPageText(buffer.data());
    }
}
