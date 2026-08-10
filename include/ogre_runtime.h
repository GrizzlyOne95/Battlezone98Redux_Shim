#pragma once

#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
    namespace OgreRuntime
    {
        // OpenShim never loads OgreMain.dll itself. These helpers operate only on
        // the Ogre runtime already loaded by Battlezone 98 Redux.
        bool IsLoaded() noexcept;
        uintptr_t GetModuleBase() noexcept;
        size_t GetModuleSize() noexcept;

        // Resolve an exported symbol from the shipped OgreMain.dll. Prefer this for
        // stable exported APIs; do not assume pristine upstream 1.10 decorated names
        // match BZR without verification.
        void* ResolveExport(const char* name) noexcept;

        // Convert a verified OgreMain-relative offset to a live process address.
        // The caller remains responsible for validating the target bytes/signature.
        void* ResolveOffset(uintptr_t offset) noexcept;

        // Returns true only when address lies inside the currently loaded
        // OgreMain.dll image.
        bool ContainsAddress(const void* address) noexcept;
    }
}
