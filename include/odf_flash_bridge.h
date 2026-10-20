#pragma once
#include <cstdint>

// Optional EXU companion ABI. Strings are copied during the call. No engine
// or Ogre pointers cross this boundary. Pose: simulation-space right, up,
// front, position (twelve floats).
namespace BzrOdfFlashBridge
{
    inline constexpr uint32_t kVersion = 1;
    struct Spec
    {
        uint32_t size = sizeof(Spec);
        uint32_t version = kVersion;
        uint32_t owner = 0;
        const char* mesh = nullptr;
        const char* material = nullptr;
        float pose[12] = {};
        float duration = 0.1f;
        float startScale = 1;
        float finishScale = 1;
        float rollRadians = 0;
        uint64_t cookie = 0; // nonzero, unique to this caller's flash lifetime
    };
#if INTPTR_MAX == INT32_MAX
    static_assert(sizeof(Spec) == 96, "Win32 flash ABI drift");
#endif
    inline bool Matches(uint32_t id, uint64_t cookie, uint32_t requestedId, uint64_t requestedCookie) noexcept
    { return requestedId != 0 && requestedCookie != 0 && id == requestedId && cookie == requestedCookie; }
}
