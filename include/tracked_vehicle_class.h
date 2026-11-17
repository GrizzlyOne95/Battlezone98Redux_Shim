#pragma once

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
}
