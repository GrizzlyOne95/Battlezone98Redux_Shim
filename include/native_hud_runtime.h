// Native adapter/provider boundary. No released build is qualified yet.
#pragma once
#include "native_hud_layout.h"

namespace BZROpenShim::NativeHud::Runtime
{
    uint32_t Capabilities();
    bool GetRect(const char* name, bool stock, int* x, int* y, int* w, int* h);
    bool SetRect(const char* name, int x, int y, int w, int h);
    bool SetVisible(const char* name, bool visible);
    bool Restore(const char* name);
    bool RestoreAll();
    void ResetMission();

    // Called only by a native adapter after build, bytes, draw ABI and mission
    // lifetime qualification. Zero disables the provider and drops all intent.
    // This checkpoint intentionally has NO native caller of this function.
    void SetAdapterCapabilities(uint32_t capabilities);
    Frame BeginFrame();
    bool Observe(Meter meter, Frame frame, Rect stock, RenderPlan& plan);
}
