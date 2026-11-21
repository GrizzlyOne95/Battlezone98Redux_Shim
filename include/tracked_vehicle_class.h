#pragma once

#include <cstdint>

namespace BZROpenShim
{
    // ODF-driven `classLabel = "tracked"` support (Docs/TRACKED_VEHICLES.md).
    // The label shares the GameObjectClass::Find compare hook that
    // pond_class_label.cpp installs, so it waits for that install. Safe to
    // call from the normal deferred-hook retry loop.
    void InstallTrackedVehicleClassIfPossible();
    bool IsTrackedVehicleClassInstalled();

    // Called from the shared Find label-compare hook after stock _stricmp
    // reported a mismatch: true aliases a `tracked` ODF onto the registered
    // `hover` descriptor and arms the following HoverCraftClass::BuildClass.
    bool MatchTrackedClassLabel(const char* registeredLabel,
                                const char* odfLabel,
                                int (__cdecl* stricmp)(const char*, const char*));

    // Tread texture scroll: true when `sourceMaterialName` (the material a
    // GPU skinning clone is made from) is a treadMaterialL/R of a tracked
    // ODF. Its clones get no instanced twin. Any thread.
    bool TrackedTreadMaterialRegistered(const char* sourceMaterialName);
    // Changes when a name is added, so existing twins can be re-checked.
    uint32_t TrackedTreadMaterialRevision();
}
