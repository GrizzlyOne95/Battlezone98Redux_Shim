#pragma once

namespace BZROpenShim
{
    namespace ObjectiveObjectsFix
    {
        void InstallObjectiveObjectsFixIfPossible();
        // True once the iterator step advances (patched here or found patched).
        bool IsActive();
    }
}
