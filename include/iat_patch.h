// SPDX-License-Identifier: MIT
//
// Copyright (C) 2026 BZR Open Shim contributors
//
// Import-address-table patching that survives racing the Windows loader.
//
// Why this is shared
// ------------------
// Two OpenShim subsystems patch the *same* third-party module's IAT
// (RenderSystem_Direct3D11.dll) from their *own* background threads, both by
// polling GetModuleHandle and patching the moment it answers:
//
//   * src/patches/dx11_colorspace_diagnostic.cpp   -- discovery thread
//   * src/patches/ogre_animation_profiler/...      -- profiler worker thread
//
// GetModuleHandle reports a module as soon as the loader has put it in the
// module list, which is well before the loader has snapped its imports and
// re-applied final section protections. Patching in that window produced two
// unhandled write access violations across 22 launches on 2026-08-22:
//
//   [CRASH] 2026-08-22 12:25:36 code=0xC0000005 write=0x6B5F6FF4 tid=41188
//
// tid 41188 was the colorspace discovery thread; the fault address is that
// module's base (0x6B520000) plus 0xD6FF4, an IAT slot in the last four bytes
// of its page. VirtualProtect(PAGE_READWRITE) had returned success and the
// loader re-protected the page before the store landed. The run had logged
// "found RenderSystem_Direct3D11.dll" and never logged "installed=".
//
// A third site, PatchIATByFuncName in src/patches/file_io_hooks.cpp, patches the
// main executable's IAT from the patcher on the main thread. Its hazard profile
// is different (nothing is concurrently loading the exe) and that file is being
// rewritten by PR #42, so it is deliberately left alone here.
//
// What this provides
// ------------------
//   WaitForModuleLoadToFinish() closes the race: taking a real reference by
//   full path serialises on the loader lock, so it returns only once any
//   in-flight load of that exact file has completed.
//
//   PatchImport() is the second line of defence: every RVA is bounds-checked
//   against SizeOfImage, both walks are bounded, and the whole thing runs under
//   structured exception handling so a fault becomes a retryable Result rather
//   than a dead process.

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
namespace IatPatch
{
    enum class Result
    {
        Patched,     // the entry now points at the replacement
        NotFound,    // the module does not import that function -- not an error
        Faulted,     // something raced or looked wrong; retrying may succeed
    };

    namespace Detail
    {
        // A bounds-checked view of a mapped image. Every pointer handed out is
        // known to lie inside the module, so a half-initialised import
        // directory cannot walk the caller off into unmapped memory.
        struct MappedImageView
        {
            unsigned char* base = nullptr;
            std::size_t size = 0;

            bool Contains(const void* pointer, std::size_t bytes) const
            {
                if (!base || !pointer || bytes == 0)
                    return false;
                const auto* candidate = static_cast<const unsigned char*>(pointer);
                if (candidate < base)
                    return false;
                const std::size_t offset =
                    static_cast<std::size_t>(candidate - base);
                return offset <= size && bytes <= size - offset;
            }

            template <typename T>
            T* At(DWORD rva, std::size_t bytes = sizeof(T)) const
            {
                if (!base || rva >= size || bytes > size - rva)
                    return nullptr;
                return reinterpret_cast<T*>(base + rva);
            }

            // Import names are NUL-terminated and their length is declared
            // nowhere, so the terminator has to be found without leaving the
            // image.
            const char* StringAt(DWORD rva) const
            {
                if (!base || rva >= size)
                    return nullptr;
                const char* text = reinterpret_cast<const char*>(base + rva);
                const std::size_t remaining = size - rva;
                for (std::size_t index = 0; index < remaining; ++index)
                {
                    if (!text[index])
                        return text;
                }
                return nullptr;
            }
        };

        inline bool TryGetMappedImageView(HMODULE module, MappedImageView& view)
        {
            if (!module)
                return false;
            auto* base = reinterpret_cast<unsigned char*>(module);

            // SizeOfImage is itself read out of the headers, so read the
            // headers through a minimal view first and widen once trusted.
            MappedImageView headerView{ base, 0x1000 };
            const auto* dos = headerView.At<IMAGE_DOS_HEADER>(0);
            if (!dos || dos->e_magic != IMAGE_DOS_SIGNATURE)
                return false;
            if (dos->e_lfanew < 0)
                return false;
            const auto* nt = headerView.At<IMAGE_NT_HEADERS>(
                static_cast<DWORD>(dos->e_lfanew));
            if (!nt || nt->Signature != IMAGE_NT_SIGNATURE)
                return false;
            if (nt->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR_MAGIC)
                return false;
            const DWORD imageSize = nt->OptionalHeader.SizeOfImage;
            if (imageSize < 0x1000)
                return false;

            view.base = base;
            view.size = imageSize;
            return true;
        }

        // The whole walk lives here so the __try/__except sits in a scope with
        // no objects requiring unwinding.
        inline Result PatchImportGuarded(
            const MappedImageView& view,
            const char* importedDll,
            const char* functionName,
            FARPROC targetProc,
            void* replacement,
            void** original)
        {
            __try
            {
                const auto* dos = view.At<IMAGE_DOS_HEADER>(0);
                const auto* nt = dos
                    ? view.At<IMAGE_NT_HEADERS>(
                          static_cast<DWORD>(dos->e_lfanew))
                    : nullptr;
                if (!nt)
                    return Result::Faulted;

                const IMAGE_DATA_DIRECTORY& imports =
                    nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
                if (!imports.VirtualAddress || !imports.Size)
                    return Result::NotFound;

                // Bound the descriptor walk by the directory size rather than
                // trusting a NUL terminator that may not be written yet.
                const std::size_t descriptorCount =
                    imports.Size / sizeof(IMAGE_IMPORT_DESCRIPTOR);
                auto* descriptors = view.At<IMAGE_IMPORT_DESCRIPTOR>(
                    imports.VirtualAddress, imports.Size);
                if (!descriptors || descriptorCount == 0)
                    return Result::NotFound;

                for (std::size_t index = 0; index < descriptorCount; ++index)
                {
                    const IMAGE_IMPORT_DESCRIPTOR& descriptor = descriptors[index];
                    if (!descriptor.Name)
                        break;

                    const char* dllName = view.StringAt(descriptor.Name);
                    if (!dllName || _stricmp(dllName, importedDll) != 0)
                        continue;

                    auto* firstThunk =
                        view.At<IMAGE_THUNK_DATA>(descriptor.FirstThunk);
                    auto* nameThunk = descriptor.OriginalFirstThunk
                        ? view.At<IMAGE_THUNK_DATA>(descriptor.OriginalFirstThunk)
                        : nullptr;
                    if (!firstThunk)
                        continue;

                    for (;;)
                    {
                        if (!view.Contains(firstThunk, sizeof(IMAGE_THUNK_DATA)))
                            break;
                        if (nameThunk &&
                            !view.Contains(nameThunk, sizeof(IMAGE_THUNK_DATA)))
                        {
                            break;
                        }
                        if (!firstThunk->u1.Function)
                            break;

                        bool matches = false;
                        if (nameThunk)
                        {
                            if (!IMAGE_SNAP_BY_ORDINAL(nameThunk->u1.Ordinal))
                            {
                                const DWORD nameRva = static_cast<DWORD>(
                                    nameThunk->u1.AddressOfData);
                                const char* importName = view.StringAt(
                                    nameRva +
                                    offsetof(IMAGE_IMPORT_BY_NAME, Name));
                                matches = importName &&
                                    std::strcmp(importName, functionName) == 0;
                            }
                            ++nameThunk;
                        }
                        else if (targetProc)
                        {
                            matches =
                                reinterpret_cast<void*>(firstThunk->u1.Function) ==
                                reinterpret_cast<void*>(targetProc);
                        }

                        if (!matches)
                        {
                            ++firstThunk;
                            continue;
                        }

                        auto** entry =
                            reinterpret_cast<void**>(&firstThunk->u1.Function);
                        if (*entry == replacement)
                            return Result::Patched;

                        DWORD oldProtect = 0;
                        if (!VirtualProtect(
                                entry, sizeof(void*), PAGE_READWRITE, &oldProtect))
                        {
                            return Result::Faulted;
                        }

                        if (original && !*original)
                            *original = *entry;

                        // The store that used to lose the race against the
                        // loader. If it faults now, __except turns it into a
                        // retry instead of an unhandled access violation.
                        *entry = replacement;

                        DWORD ignored = 0;
                        VirtualProtect(entry, sizeof(void*), oldProtect, &ignored);
                        FlushInstructionCache(
                            GetCurrentProcess(), entry, sizeof(void*));
                        return Result::Patched;
                    }
                }

                return Result::NotFound;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return Result::Faulted;
            }
        }
    }  // namespace Detail

    // Redirect one imported function in `module` to `replacement`, recording the
    // previous value in `*original` if it is still null. Never throws, never
    // faults the process.
    inline Result PatchImport(
        HMODULE module,
        const char* importedDll,
        const char* functionName,
        void* replacement,
        void** original)
    {
        if (!module || !importedDll || !functionName || !replacement)
            return Result::NotFound;

        Detail::MappedImageView view;
        if (!Detail::TryGetMappedImageView(module, view))
            return Result::Faulted;

        FARPROC targetProc = nullptr;
        if (HMODULE importedModule = GetModuleHandleA(importedDll))
            targetProc = GetProcAddress(importedModule, functionName);

        return Detail::PatchImportGuarded(
            view, importedDll, functionName, targetProc, replacement, original);
    }

    // Block until the loader has finished with `module`.
    //
    // GetModuleHandle reports a module as soon as the loader lists it, which is
    // before its imports are snapped and its final section protections applied.
    // Taking a real reference by full path serialises on the loader lock, so
    // this returns only once any in-flight load of that exact file completed.
    //
    // The reference is deliberately never released: the caller's function
    // pointers live in that module's IAT for the rest of the process, and
    // pinning it removes any chance of an unload racing the patched entries.
    //
    // Returns false when the wait could not be taken; callers should then still
    // attempt the patch, which is guarded, rather than give up.
    inline bool WaitForModuleLoadToFinish(HMODULE module, DWORD* lastError)
    {
        if (lastError)
            *lastError = 0;
        if (!module)
            return false;

        wchar_t modulePath[MAX_PATH] = {};
        const DWORD length = GetModuleFileNameW(
            module, modulePath, static_cast<DWORD>(MAX_PATH));
        if (length == 0 || length >= MAX_PATH)
        {
            if (lastError)
                *lastError = GetLastError();
            return false;
        }

        const HMODULE pinned = LoadLibraryExW(modulePath, nullptr, 0);
        if (!pinned)
        {
            if (lastError)
                *lastError = GetLastError();
            return false;
        }
        if (pinned != module)
        {
            // A different image answered to that path. Keep the reference
            // rather than unloading something we did not load, and decline to
            // claim the wait succeeded.
            return false;
        }
        return true;
    }
}  // namespace IatPatch
}  // namespace BZROpenShim
