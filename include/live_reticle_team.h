#pragma once

// Only for the byte-guarded SelectionDisplay recent-hit callback. Its input
// is the live complete GameObject that the retail renderer already reads.
// Untrusted handles and arena enumeration must keep the VirtualQuery-based
// helpers. No object address or team is cached here: teams can change live.
#include "bzr_object_layout.h"
#include <Windows.h>
#include <cstdint>
#include <climits>

namespace BZROpenShim::Reticle
{
    inline int ReadLiveActualTeam(const void* object, uintptr_t expectedGetTeam)
    {
        const auto address = reinterpret_cast<uintptr_t>(object);
        if (address < 0x10000 || address % sizeof(void*) != 0 || !expectedGetTeam)
            return INT_MIN;
        __try
        {
            // Verified Redux interface offset and GetTeam slot. Check identity
            // on every read, retaining the original helper's rejection rule.
            const auto* bytes = static_cast<const uint8_t*>(object);
            auto* const* table = *reinterpret_cast<void* const* const*>(bytes + 0x18);
            if (!table || reinterpret_cast<uintptr_t>(table[1]) != expectedGetTeam)
                return INT_MIN;
            return *reinterpret_cast<const int*>(bytes + ObjectLayout::kGameObjectActualTeam);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return INT_MIN;
        }
    }
}
