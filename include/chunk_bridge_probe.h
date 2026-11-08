#pragma once

#include "memory_access.h"

#if defined(_WIN32) && defined(_MSC_VER)
namespace BZROpenShim
{
namespace ChunkBridgeProbe
{
    // These are candidate layout reads, not proof that the object is a bridge.
    // OBJ76 +0xF0 can contain aligned integers such as 0x000E0000. Check the
    // entire span before reading either link; keep SEH for a lifetime change
    // between VirtualQuery and the reads. Publish both links or neither.
    inline constexpr size_t kOgreLinksSpan = 0xA8 + sizeof(void*);

    // The reads alone, for a caller that already holds a readable verdict for
    // this candidate. SEH is the only guard here.
    inline bool TryReadOgreLinksUnchecked(const void* candidate, void*& entity, void*& light) noexcept
    {
        entity = nullptr;
        light = nullptr;
        __try
        {
            const auto* bytes = static_cast<const uint8_t*>(candidate);
            void* const readEntity = *reinterpret_cast<void* const*>(bytes + 0x94);
            void* const readLight = *reinterpret_cast<void* const*>(bytes + 0xA8);
            entity = readEntity;
            light = readLight;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    inline bool TryReadOgreLinks(const void* candidate, void*& entity, void*& light) noexcept
    {
        entity = nullptr;
        light = nullptr;
        const uintptr_t address = reinterpret_cast<uintptr_t>(candidate);
        if (address < 0x00010000 || address % sizeof(void*) != 0 ||
            !MemoryAccess::IsReadable(candidate, kOgreLinksSpan))
        {
            return false;
        }
        return TryReadOgreLinksUnchecked(candidate, entity, light);
    }

    // The +0x8C owner walk reads owner+0xF0..+0xFC, then names at the owner
    // entity's +0xC4/+0xD4 (16 bytes each, plus the +0x84/+0x94 fallbacks).
    // Pointer shape alone let text (0x61657720) and 1.0f (0x3F800000) through
    // in a 1.0.0.66 player log; both faulted under SEH.
    inline constexpr size_t kLegacyOwnerReadSpan = 0xF8 + sizeof(void*);
    inline constexpr size_t kOwnerEntityNameSpan = 0xD4 + 16;

    inline bool IsCandidateSpanReadable(const void* candidate, size_t span) noexcept
    {
        const uintptr_t address = reinterpret_cast<uintptr_t>(candidate);
        return address >= 0x00010000 && address % sizeof(void*) == 0 &&
               MemoryAccess::IsReadable(candidate, span);
    }
}
}
#endif
