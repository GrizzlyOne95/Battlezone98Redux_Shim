#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

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

        struct ExportMatch
        {
            std::string name;
            void* address = nullptr;
        };

        // Every OgreMain.dll export whose decorated name contains `token`,
        // skipping forwarded exports and any address outside the image. The
        // diagnostic instruments use it to find a member by a fragment of its
        // mangled name and then insist on exactly one match.
        std::vector<ExportMatch> FindExportsContaining(const char* token);
    }
}
