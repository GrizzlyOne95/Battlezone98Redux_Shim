#include "native_hud_runtime.h"
#include <mutex>

namespace BZROpenShim::NativeHud::Runtime
{
    namespace
    {
        Layout g_layout;
        std::mutex g_mutex;
    }

    uint32_t Capabilities()
    {
        const std::lock_guard<std::mutex> lock(g_mutex);
        return g_layout.Capabilities();
    }

    bool GetRect(const char* name, bool stock, int* x, int* y, int* w, int* h)
    {
        if (!x || !y || !w || !h) return false;
        Meter meter;
        Rect rect;
        if (!ParseMeter(name, meter)) return false;
        const std::lock_guard<std::mutex> lock(g_mutex);
        if (!g_layout.GetRect(meter, stock, rect)) return false;
        *x = rect.x; *y = rect.y; *w = rect.w; *h = rect.h;
        return true;
    }

    bool SetRect(const char* name, int x, int y, int w, int h)
    {
        Meter meter;
        if (!ParseMeter(name, meter)) return false;
        const std::lock_guard<std::mutex> lock(g_mutex);
        return g_layout.SetRect(meter, {x, y, w, h});
    }

    bool SetVisible(const char* name, bool visible)
    {
        Meter meter;
        if (!ParseMeter(name, meter)) return false;
        const std::lock_guard<std::mutex> lock(g_mutex);
        return g_layout.SetVisible(meter, visible);
    }

    bool Restore(const char* name)
    {
        Meter meter;
        if (!ParseMeter(name, meter)) return false;
        const std::lock_guard<std::mutex> lock(g_mutex);
        return g_layout.Restore(meter);
    }

    bool RestoreAll()
    {
        const std::lock_guard<std::mutex> lock(g_mutex);
        return g_layout.RestoreAll();
    }

    void ResetMission()
    {
        const std::lock_guard<std::mutex> lock(g_mutex);
        g_layout.ResetMission();
    }

    void SetAdapterCapabilities(uint32_t capabilities)
    {
        const std::lock_guard<std::mutex> lock(g_mutex);
        g_layout.SetAdapterCapabilities(capabilities);
    }

    Frame BeginFrame()
    {
        const std::lock_guard<std::mutex> lock(g_mutex);
        return g_layout.BeginFrame();
    }

    bool Observe(Meter meter, Frame frame, Rect stock, RenderPlan& plan)
    {
        const std::lock_guard<std::mutex> lock(g_mutex);
        return g_layout.Observe(meter, frame, stock, plan);
    }
}
