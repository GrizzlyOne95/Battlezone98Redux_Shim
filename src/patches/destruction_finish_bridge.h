#pragma once
#include <Windows.h>
#include <string>

namespace BZROpenShim::Hooks
{
    // Optional EXU presentation at debris creation, with a module lease.
    // No retained cross-DLL callback and no Lua invocation from rendering.
    // Every call into EXU is SEH-guarded and fails closed. The resolved procs
    // are cached per module handle (re-resolved only when it changes) and an
    // absent EXU is re-probed at most once per kExuProbeBackoffMs, so a
    // per-entity caller never repeats the lookup.
    namespace DestructionFinishBridge
    {
        using Apply = void (__cdecl*)(void*);
        using Query = bool (__cdecl*)(const char*, char*, unsigned int);
        constexpr ULONGLONG kExuProbeBackoffMs = 2000;

        inline HMODULE g_module = nullptr;
        inline Apply g_apply = nullptr;
        inline Query g_query = nullptr;
        inline ULONGLONG g_nextProbeMs = 0;

        // No C++ objects with destructors in these: __try forbids unwinding (C2712).
        __declspec(noinline) inline bool GuardedApply(Apply fn, void* entity)
        {
            __try { fn(entity); return true; }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }
        __declspec(noinline) inline bool GuardedQuery(Query fn, const char* source, char* out, unsigned int size)
        {
            __try { return fn(source, out, size); }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        // Leases exu.dll (caller must FreeLibrary) and refreshes the proc cache.
        inline HMODULE Lease()
        {
            if (!g_module)
            {
                const ULONGLONG now = GetTickCount64();
                if (now < g_nextProbeMs) return nullptr;
                g_nextProbeMs = now + kExuProbeBackoffMs;
            }
            HMODULE module = nullptr;
            if (!GetModuleHandleExW(0, L"exu.dll", &module) || !module)
            {
                g_module = nullptr; g_apply = nullptr; g_query = nullptr;
                return nullptr;
            }
            if (module != g_module)
            {
                g_module = module;
                g_apply = reinterpret_cast<Apply>(GetProcAddress(module, "EXU_ApplyDestructionFinish"));
                if (!g_apply) g_apply = reinterpret_cast<Apply>(GetProcAddress(module, "_EXU_ApplyDestructionFinish"));
                g_query = reinterpret_cast<Query>(GetProcAddress(module, "EXU_GetDestructionMaterial"));
                if (!g_query) g_query = reinterpret_cast<Query>(GetProcAddress(module, "_EXU_GetDestructionMaterial"));
            }
            return module;
        }
    }

    inline void ApplyDestructionFinish(void* entity)
    {
        using namespace DestructionFinishBridge;
        HMODULE module = Lease();
        if (!module) return;
        if (g_apply && !GuardedApply(g_apply, entity)) g_apply = nullptr;
        FreeLibrary(module);
    }
    inline std::string DestructionFinishMaterial(const std::string& source)
    {
        using namespace DestructionFinishBridge;
        HMODULE module = Lease();
        if (!module) return source;
        char name[192] = {};
        bool changed = false;
        if (g_query) changed = GuardedQuery(g_query, source.c_str(), name, sizeof(name));
        FreeLibrary(module);
        name[sizeof(name) - 1] = '\0';
        return changed && name[0] ? std::string(name) : source;
    }
}
