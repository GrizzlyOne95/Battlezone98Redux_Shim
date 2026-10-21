#pragma once
#include <Windows.h>
#include <string>

namespace BZROpenShim::Hooks
{
    // Optional EXU presentation at debris creation, with a module lease.
    // No retained cross-DLL callback and no Lua invocation from rendering.
    inline void ApplyDestructionFinish(void* entity)
    {
        HMODULE module = nullptr;
        if (!GetModuleHandleExW(0, L"exu.dll", &module)) return;
        using Apply = void (__cdecl*)(void*);
        auto fn = reinterpret_cast<Apply>(GetProcAddress(module, "EXU_ApplyDestructionFinish"));
        if (!fn) fn = reinterpret_cast<Apply>(GetProcAddress(module, "_EXU_ApplyDestructionFinish"));
        if (fn) fn(entity);
        FreeLibrary(module);
    }
    inline std::string DestructionFinishMaterial(const std::string& source)
    {
        HMODULE module = nullptr;
        if (!GetModuleHandleExW(0, L"exu.dll", &module)) return source;
        using Query = bool (__cdecl*)(const char*, char*, unsigned int);
        auto fn = reinterpret_cast<Query>(GetProcAddress(module, "EXU_GetDestructionMaterial"));
        if (!fn) fn = reinterpret_cast<Query>(GetProcAddress(module, "_EXU_GetDestructionMaterial"));
        char name[192] = {};
        const bool changed = fn && fn(source.c_str(), name, sizeof(name));
        FreeLibrary(module);
        return changed ? std::string(name) : source;
    }
}
