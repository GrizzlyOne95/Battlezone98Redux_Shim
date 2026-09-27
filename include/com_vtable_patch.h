#pragma once

// Replace one entry of a COM object's vtable, the way OpenShim's D3D/DXGI
// observers attach to devices, contexts, factories and swap chains.
//
// The FXAA, scene-depth, colorspace and Ogre-profiler observers each had their
// own copy (audit P2-3). They disagree on one rule, which is kept as a
// parameter: when the entry holds a different wrapper than the one saved as
// `original`, the colorspace and profiler observers refuse (ForeignWrapper),
// while FXAA and scene depth overwrite it. Overwriting cuts the other wrapper
// out of the chain; refusing leaves the refusing observer detached. A boot with
// all four on showed scene depth refusing OMSetRenderTargets every frame once
// colorspace held it, so picking one rule for all needs real chaining first.
//
// The write is made writable with VirtualProtect, done under SEH, restored and
// flushed. Callers hold their own lock around the call and keep their own
// bookkeeping (the profiler records the slot so it can restore it).
//
// Windows-only.

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <cstddef>

namespace BZROpenShim
{
namespace ComVtablePatch
{
    enum class Result
    {
        Patched,        // the entry now holds the hook
        AlreadyHooked,  // the entry already held the hook; nothing written
        ForeignWrapper, // someone else replaced the entry after `original` was saved
        NotWritable,    // VirtualProtect refused, or the write faulted
        NoObject,       // null object, vtable or hook
    };

    enum class OnForeignWrapper
    {
        Refuse,    // leave the entry alone and return ForeignWrapper
        Overwrite, // write the hook anyway; `original` is kept
    };

    inline bool Succeeded(Result result)
    {
        return result == Result::Patched || result == Result::AlreadyHooked;
    }

    namespace Detail
    {
        inline bool WriteGuarded(void** slot, void* value)
        {
            __try
            {
                *slot = value;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }
    }

    // `original` is the entry the hook forwards to. The first successful
    // patch saves what was there; later calls (a second device, a recreated
    // context sharing the vtable) keep it and only re-point the entry.
    inline Result PatchEntry(void* object, size_t index, void* hook, void*& original,
                             OnForeignWrapper onForeign, void*** outSlot = nullptr)
    {
        if (!object || !hook)
            return Result::NoObject;

        void** vtable = *reinterpret_cast<void***>(object);
        if (!vtable)
            return Result::NoObject;

        void** slot = &vtable[index];
        if (outSlot)
            *outSlot = slot;
        void* current = *slot;
        if (current == hook)
            return Result::AlreadyHooked;
        if (original && current != original && onForeign == OnForeignWrapper::Refuse)
            return Result::ForeignWrapper;

        DWORD oldProtect = 0;
        if (!VirtualProtect(slot, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect))
            return Result::NotWritable;

        if (!original)
            original = current;
        const bool wrote = Detail::WriteGuarded(slot, hook);

        DWORD ignored = 0;
        VirtualProtect(slot, sizeof(void*), oldProtect, &ignored);
        if (!wrote)
            return Result::NotWritable;
        FlushInstructionCache(GetCurrentProcess(), slot, sizeof(void*));
        return Result::Patched;
    }

    template <typename T>
    Result PatchEntry(void* object, size_t index, T hook, T& original,
                      OnForeignWrapper onForeign, void*** outSlot = nullptr)
    {
        void* originalPointer = reinterpret_cast<void*>(original);
        const Result result = PatchEntry(
            object, index, reinterpret_cast<void*>(hook), originalPointer, onForeign, outSlot);
        original = reinterpret_cast<T>(originalPointer);
        return result;
    }
}
}
