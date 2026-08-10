#pragma once

#include <algorithm>
#include <cstdint>

// The Ogre-facing profiler translation unit is compiled as C++14 because the
// pinned Ogre 1.10 headers depend on standard-library surfaces removed in newer
// language modes. Provide the one C++20 bit helper used by the profiler locally
// rather than lowering the language standard for the rest of OpenShim.
#if defined(_MSVC_LANG) && _MSVC_LANG < 202002L
namespace std
{
    inline int popcount(unsigned long long value) noexcept
    {
        int count = 0;
        while (value != 0)
        {
            value &= (value - 1);
            ++count;
        }
        return count;
    }
}
#endif

namespace BZROpenShim
{
    // Returns true when the opt-in Ogre animation/render profiler was requested
    // through OPENSHIM_PROFILE_OGRE_ANIMATION=1 or openshim.ini.
    bool IsOgreAnimationProfilerRequested();

    // Starts the read-only profiler. The profiler observes Ogre animation and
    // render submission plus basic DX11 Draw/DrawIndexed activity. It does not
    // change animation state, culling decisions, materials, or render state.
    void InitializeOgreAnimationProfiler();

    // Stops the reporting/discovery worker. Installed observation hooks remain
    // process-lifetime, matching the lifetime of the Ogre/D3D objects they wrap;
    // after shutdown they simply forward without collecting data.
    void ShutdownOgreAnimationProfiler();
}
