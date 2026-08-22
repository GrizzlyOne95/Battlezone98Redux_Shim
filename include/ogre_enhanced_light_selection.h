#pragma once

namespace BZROpenShim
{
    // Installs the exact-build Ogre light-list observer/reorder hook when the
    // feature or its trace is requested. Safe to call repeatedly while Ogre is
    // loading; unknown builds fail closed.
    void InstallEnhancedLightSelectionIfPossible();
}
