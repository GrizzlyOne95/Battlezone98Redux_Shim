// engine_globals.cpp
// BZR Open Shim - engine data globals, resolved through scripts/patches.json.
// See include/engine_globals.h.
#include "engine_globals.h"

#include "hook_engine.h"

#include <Windows.h>

#include <atomic>

namespace BZROpenShim
{
    namespace EngineGlobals
    {
        namespace
        {
            struct CachedGlobal
            {
                std::atomic<uintptr_t> address{ 0 };
                std::atomic<ULONGLONG> lastMissTick{ 0 };
            };

            // ResolveNamedAddress takes a lock, rescans the image on a miss and
            // logs every miss. Callers of these accessors include per-frame
            // and per-object paths, so only the first success and one retry a
            // second ever reach it.
            uintptr_t Lookup(CachedGlobal& cache, const char* name)
            {
                const uintptr_t known = cache.address.load(std::memory_order_acquire);
                if (known != 0)
                    return known;

                const ULONGLONG now = GetTickCount64();
                const ULONGLONG last = cache.lastMissTick.load(std::memory_order_relaxed);
                if (last != 0 && now - last < 1000)
                    return 0;

                const uintptr_t resolved = HookEngine::ResolveNamedAddress(name);
                if (resolved == 0)
                {
                    cache.lastMissTick.store(now, std::memory_order_relaxed);
                    return 0;
                }
                cache.address.store(resolved, std::memory_order_release);
                return resolved;
            }
        }

        uintptr_t GameObjectArena()
        {
            static CachedGlobal cache;
            return Lookup(cache, "GameObject::Arena");
        }

        uintptr_t UserObjectSlot()
        {
            static CachedGlobal cache;
            return Lookup(cache, "GameObject::userObject");
        }

        uintptr_t RenderGlobals()
        {
            static CachedGlobal cache;
            return Lookup(cache, "RenderGlobals");
        }

        uintptr_t CurrentTrnName()
        {
            static CachedGlobal cache;
            return Lookup(cache, "CurrentTrnName");
        }

        // One literal per name: patch_registration_tests reads the names out
        // of the ResolveNamedAddress calls themselves.
        uintptr_t NetTunableAddress(NetTunable which)
        {
            static CachedGlobal caches[static_cast<size_t>(NetTunable::GovernorRate) + 1];
            CachedGlobal& cache = caches[static_cast<size_t>(which)];
            switch (which)
            {
            case NetTunable::MinBandwidth:  return Lookup(cache, "Net::MinBandwidth");
            case NetTunable::MaxBandwidth:  return Lookup(cache, "Net::MaxBandwidth");
            case NetTunable::UpCount:       return Lookup(cache, "Net::UpCount");
            case NetTunable::DownCount:     return Lookup(cache, "Net::DownCount");
            case NetTunable::MaxPing:       return Lookup(cache, "Net::MaxPing");
            case NetTunable::MaxPingsLost:  return Lookup(cache, "Net::MaxPingsLost");
            case NetTunable::AutoKickStart: return Lookup(cache, "Net::AutoKickStart");
            case NetTunable::AutoKickPing:  return Lookup(cache, "Net::AutoKickPing");
            case NetTunable::AutoKickLoss:  return Lookup(cache, "Net::AutoKickLoss");
            case NetTunable::AutoKickTime:  return Lookup(cache, "Net::AutoKickTime");
            case NetTunable::GovernorRate:  return Lookup(cache, "Net::GovernorRate");
            }
            return 0;
        }
    }
}
