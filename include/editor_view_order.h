// editor_view_order.h
// BZR Open Shim - overhead-editor display order compatibility fix
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim
{
    // Restores the BZ 1.5 render/simulate order of OverView vs ControlPanel in
    // the overhead view (Shift+F10), which is what makes editor object
    // placement work while the simulation is running.
    //
    // MUST be called synchronously from DllMain. Both patch sites are global
    // constructors that run from the CRT's _initterm before main, which is
    // long before the normal patch thread reaches RunPatcher.
    void ApplyEditorOverheadPlacementOrderFix();
}
