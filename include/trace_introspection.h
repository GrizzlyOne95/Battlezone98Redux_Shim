#pragma once

// Small introspection helpers for the investigation traces (walker cockpit,
// pilot first-person animation). Both traces carried identical copies of
// these (audit P2-3).
//
// Windows-only. None of these holds an object with a destructor, so each may
// be called from a function that uses __try.

#include <windows.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
namespace TraceIntrospection
{
    // Whether `address` lies inside the game executable's image.
    inline bool MainModuleContains(const void* address)
    {
        if (!address)
            return false;
        HMODULE module = GetModuleHandleA(nullptr);
        if (!module)
            return false;
        const auto* base = reinterpret_cast<const uint8_t*>(module);
        const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
        if (dos->e_magic != IMAGE_DOS_SIGNATURE)
            return false;
        const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
        if (nt->Signature != IMAGE_NT_SIGNATURE)
            return false;
        const auto* pointer = reinterpret_cast<const uint8_t*>(address);
        return pointer >= base && pointer < base + nt->OptionalHeader.SizeOfImage;
    }

    // The return address as an offset into the executable, or 0 with
    // outInMain false when the caller is outside it.
    inline uintptr_t CallerRva(void* returnAddress, bool& outInMain)
    {
        outInMain = MainModuleContains(returnAddress);
        if (!outInMain)
            return 0;
        return reinterpret_cast<uintptr_t>(returnAddress) -
            reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
    }

    // The MSVC RTTI decorated class name of an object whose vtable, complete
    // object locator, type descriptor and name all lie in the executable:
    // vtable[-1] -> locator, locator+12 -> type descriptor, descriptor+8 ->
    // name. Anything outside the executable, or a fault, yields false and an
    // empty buffer.
    inline bool TryGetMainModuleRttiName(const void* object, char* buffer, size_t bufferSize)
    {
        if (!object || !buffer || bufferSize == 0)
            return false;
        buffer[0] = '\0';
        __try
        {
            auto** vtable = *reinterpret_cast<void*** const*>(object);
            if (!vtable || !MainModuleContains(vtable))
                return false;
            const auto* locator = reinterpret_cast<const uint8_t*>(vtable[-1]);
            if (!MainModuleContains(locator) || !MainModuleContains(locator + 15))
                return false;
            const auto* descriptor = *reinterpret_cast<const uint8_t* const*>(locator + 12);
            if (!MainModuleContains(descriptor) || !MainModuleContains(descriptor + 8))
                return false;
            const char* decorated = reinterpret_cast<const char*>(descriptor + 8);
            size_t length = 0;
            while (length + 1 < bufferSize)
            {
                const char* current = decorated + length;
                if (!MainModuleContains(current))
                    return false;
                const char ch = *current;
                buffer[length++] = ch;
                if (ch == '\0')
                    return true;
            }
            buffer[bufferSize - 1] = '\0';
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            buffer[0] = '\0';
            return false;
        }
    }

    // Truncating copy that always terminates; a null source gives "".
    inline void CopyText(char* destination, size_t size, const char* source)
    {
        if (!destination || size == 0)
            return;
        destination[0] = '\0';
        if (!source)
            return;
        strncpy_s(destination, size, source, _TRUNCATE);
    }
}
}
