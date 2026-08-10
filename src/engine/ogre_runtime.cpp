#include "ogre_runtime.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <Psapi.h>

namespace BZROpenShim::OgreRuntime
{
    namespace
    {
        HMODULE GetOgreModule() noexcept
        {
            return GetModuleHandleA("OgreMain.dll");
        }

        bool QueryModuleInfo(MODULEINFO& info) noexcept
        {
            info = {};
            HMODULE module = GetOgreModule();
            return module != nullptr &&
                GetModuleInformation(
                    GetCurrentProcess(),
                    module,
                    &info,
                    static_cast<DWORD>(sizeof(info))) != FALSE;
        }
    }

    bool IsLoaded() noexcept
    {
        return GetOgreModule() != nullptr;
    }

    uintptr_t GetModuleBase() noexcept
    {
        return reinterpret_cast<uintptr_t>(GetOgreModule());
    }

    size_t GetModuleSize() noexcept
    {
        MODULEINFO info = {};
        return QueryModuleInfo(info) ? static_cast<size_t>(info.SizeOfImage) : 0u;
    }

    void* ResolveExport(const char* name) noexcept
    {
        if (!name || !*name)
            return nullptr;

        HMODULE module = GetOgreModule();
        if (!module)
            return nullptr;

        return reinterpret_cast<void*>(GetProcAddress(module, name));
    }

    void* ResolveOffset(uintptr_t offset) noexcept
    {
        const uintptr_t base = GetModuleBase();
        const size_t size = GetModuleSize();
        if (base == 0 || offset >= size)
            return nullptr;

        return reinterpret_cast<void*>(base + offset);
    }

    bool ContainsAddress(const void* address) noexcept
    {
        if (!address)
            return false;

        MODULEINFO info = {};
        if (!QueryModuleInfo(info))
            return false;

        const uintptr_t begin = reinterpret_cast<uintptr_t>(info.lpBaseOfDll);
        const uintptr_t end = begin + static_cast<uintptr_t>(info.SizeOfImage);
        const uintptr_t value = reinterpret_cast<uintptr_t>(address);
        return value >= begin && value < end;
    }
}
