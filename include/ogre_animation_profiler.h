#pragma once

#include <algorithm>

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
