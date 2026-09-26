#pragma once

#include "BZROpenShim.h"

#include <cstdint>

namespace BZROpenShim
{
    // Returns the native UI sub-API for the requested version (0 = latest).
    // Availability is runtime-gated by the compatible Redux build and the
    // already-resolved cUI constructor/mutation bindings.
    const OpenShimNativeUiApiV1* GetOpenShimNativeUiApi(uint32_t requestedVersion);

    // Installs the supported-build MainScreen lifetime hooks only when the
    // explicit [NativeUiDiagnostics] MainMenuProbe opt-in is enabled. The
    // diagnostic host remains internal until its live input/lifetime gate has
    // passed.
    void EnsureNativeUiMainMenuDiagnosticScaffold();

    // The cUI_MainScreen destructor detour (0x0078ECA0, byte-guarded), shared
    // by everything that needs to know when the title screen dies: the
    // diagnostic probe and the Career page both do, and only one detour can
    // own the site. Installed on demand; returns whether it is in place.
    // Listeners run after the engine's destructor has returned, when the
    // singleton is already cleared and every child is gone, and receive the
    // screen pointer as an identity token only: nothing behind it may be read.
    bool EnsureMainScreenDestroyedHook();
    using MainScreenDestroyedListener = void (*)(void* screen);
    bool AddMainScreenDestroyedListener(MainScreenDestroyedListener listener);

    // Process-shutdown bookkeeping only. Engine-owned cUI children are not
    // destructed here; their owning Redux screen tears them down normally.
    void ShutdownNativeUi();
}
