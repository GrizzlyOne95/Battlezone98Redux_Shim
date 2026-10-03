#include "native_hud_layout.h"
#include "native_hud_runtime.h"
#include "test_check.h"
#include <climits>
#include <cmath>
#include <cstdio>
#include <limits>

using namespace BZROpenShim::NativeHud;

namespace
{
    bool Same(Rect a, Rect b) { return a.x == b.x && a.y == b.y && a.w == b.w && a.h == b.h; }
    void Geometry()
    {
        // Native missing-row clipping still names the same full instrument.
        const Rect full{100, 200, 20, 100};
        Rect recovered;
        CHECK(InferFullRect({100, 200, 119, 299}, 0, recovered) && Same(recovered, full));
        CHECK(InferFullRect({100, 250, 119, 299}, -50, recovered) && Same(recovered, full));
        CHECK(InferFullRect({100, 300, 119, 299}, -100, recovered) && Same(recovered, full));
        CHECK(!InferFullRect({100, 301, 119, 299}, -101, recovered));
        CHECK(!InferFullRect({100, 250, 119, 299}, 1, recovered));
        CHECK(!InferFullRect({INT_MIN, 0, INT_MAX, 99}, 0, recovered));
        CHECK(!ValidRect({0, 0, 0, 10}));
        CHECK(!ValidRect({0, 0, 10, -10}));
        CHECK(!ValidRect({INT_MAX, 0, INT_MAX, 10}));
        CHECK(ValidRect({-100, -100, 20, 40}));

        const RenderPlan plan{full, {500, 300, 40, 200}, true};
        Clip clip;
        CHECK(plan.MapClip({100, 250, 119, 299}, clip));
        CHECK(clip.left == 500 && clip.top == 400 && clip.right == 539 && clip.bottom == 499);
        CHECK(plan.MapClip({100, 300, 119, 299}, clip));
        CHECK(clip.top == 500 && clip.bottom == 499); // empty stays empty
        CHECK(!plan.MapClip({99, 250, 119, 299}, clip));
        // Sprite destination must be resolved through the ORIGINAL pane first;
        // changing only submit Y would move or stretch the UV crop incorrectly.
        Sprite sprite;
        CHECK(plan.MapSprite({100, 200, 20, 100}, sprite));
        CHECK(sprite.x == 500 && sprite.y == 300 && sprite.w == 40 && sprite.h == 200);
        CHECK(plan.MapSprite({90, 180, 40, 12}, sprite)); // title follows the map
        CHECK(sprite.x == 480 && sprite.y == 260 && sprite.w == 80 && sprite.h == 24);
        Point point;
        CHECK(plan.MapPoint({115, 251}, point)); // ammo-cost row / shots origin
        CHECK(point.x == 530 && point.y == 402);
        CHECK(!plan.MapSprite({NAN, 0, 1, 1}, sprite));
        CHECK(!plan.MapSprite({0, INFINITY, 1, 1}, sprite));
        CHECK(!plan.MapSprite({0, 0, -1, 1}, sprite));
        CHECK(!plan.MapPoint({INT_MAX, INT_MAX}, point));
        const RenderPlan narrow{full, {0, 0, 2, 7}, true};
        CHECK(narrow.MapClip({100, 299, 119, 299}, clip));
        CHECK(clip.top == 7 && clip.bottom == 6); // near-empty rounds to empty
        CHECK(narrow.MapClip({100, 200, 119, 299}, clip));
        CHECK(clip.left == 0 && clip.top == 0 && clip.right == 1 && clip.bottom == 6);
    }

    void Lifecycle()
    {
        Layout layout;
        Rect rect{9, 9, 9, 9};
        RenderPlan plan;
        CHECK(layout.Capabilities() == 0);
        CHECK(!layout.SetRect(Meter::Hull, {500, 300, 40, 200}));
        CHECK(!layout.SetVisible(Meter::Hull, false));
        CHECK(!layout.GetRect(Meter::Hull, false, rect));
        CHECK(Same(rect, {9, 9, 9, 9})); // unavailable doesn't overwrite output
        layout.SetAdapterCapabilities(kHullCapability);
        CHECK(!layout.SetRect(Meter::Ammo, {0, 0, 20, 100}));
        CHECK(!layout.SetRect(Meter::Hull, {INT_MAX, 0, 1, 1}));
        CHECK(layout.SetRect(Meter::Hull, {500, 300, 40, 200})); // before first render
        CHECK(layout.SetVisible(Meter::Hull, false));
        CHECK(!layout.GetRect(Meter::Hull, false, rect)); // no invented stock snapshot
        auto frame = layout.BeginFrame();
        CHECK(layout.Observe(Meter::Hull, frame, {100, 200, 20, 100}, plan));
        CHECK(!plan.visible && Same(plan.target, {500, 300, 40, 200}));
        CHECK(layout.GetRect(Meter::Hull, false, rect) && Same(rect, plan.target));
        CHECK(layout.GetRect(Meter::Hull, true, rect) && Same(rect, plan.source));
        auto newFrame = layout.BeginFrame();
        CHECK(!layout.GetRect(Meter::Hull, false, rect)); // absent player this frame
        CHECK(!layout.Observe(Meter::Hull, frame, {100, 200, 20, 100}, plan));
        CHECK(layout.Observe(Meter::Hull, newFrame, {200, 400, 40, 200}, plan));
        CHECK(Same(plan.target, {500, 300, 40, 200})); // physical pixels across UI scale
        CHECK(layout.Restore(Meter::Hull));
        CHECK(layout.GetRect(Meter::Hull, false, rect) && Same(rect, {200, 400, 40, 200}));
        CHECK(layout.Observe(Meter::Hull, newFrame, rect, plan) && plan.visible);
        CHECK(layout.SetVisible(Meter::Hull, false));
        layout.ResetMission();
        CHECK(layout.Capabilities() == kHullCapability);
        CHECK(!layout.Observe(Meter::Hull, newFrame, rect, plan));
        frame = layout.BeginFrame();
        CHECK(layout.Observe(Meter::Hull, frame, {300, 500, 20, 100}, plan));
        CHECK(plan.visible && Same(plan.source, plan.target));
        layout.SetAdapterCapabilities(kAllCapabilities);
        frame = layout.BeginFrame();
        CHECK(layout.SetRect(Meter::Ammo, {600, 400, 20, 90}));
        CHECK(layout.SetVisible(Meter::Hull, false));
        CHECK(layout.RestoreAll());
        CHECK(layout.Observe(Meter::Ammo, frame, {600, 500, 20, 100}, plan));
        CHECK(plan.visible && Same(plan.source, plan.target));
        layout.SetAdapterCapabilities(0);
        CHECK(!layout.GetRect(Meter::Ammo, false, rect));
        CHECK(!layout.RestoreAll());
        CHECK(!layout.SetVisible(static_cast<Meter>(99), false));
        Meter meter;
        CHECK(ParseMeter("hull", meter) && meter == Meter::Hull);
        CHECK(ParseMeter("ammo", meter) && meter == Meter::Ammo);
        CHECK(!ParseMeter("radar", meter) && !ParseMeter(nullptr, meter));
    }

    void RuntimeBoundary()
    {
        int x = 9, y = 9, w = 9, h = 9;
        CHECK(Runtime::Capabilities() == 0); // production begins unavailable
        CHECK(!Runtime::SetRect("hull", 100, 100, 20, 90));
        CHECK(!Runtime::SetVisible("ammo", false));
        CHECK(!Runtime::GetRect("hull", false, &x, &y, &w, &h));
        CHECK(x == 9 && y == 9 && w == 9 && h == 9);
        Runtime::SetAdapterCapabilities(kAllCapabilities); // fake qualified adapter
        CHECK(!Runtime::GetRect("hull", false, nullptr, &y, &w, &h));
        CHECK(!Runtime::SetRect("radar", 100, 100, 20, 90));
        CHECK(Runtime::SetRect("hull", 100, 100, 20, 90));
        const auto frame = Runtime::BeginFrame();
        RenderPlan plan;
        CHECK(Runtime::Observe(Meter::Hull, frame, {1, 2, 10, 80}, plan));
        CHECK(Runtime::GetRect("hull", false, &x, &y, &w, &h));
        CHECK(x == 100 && y == 100 && w == 20 && h == 90);
        CHECK(Runtime::GetRect("hull", true, &x, &y, &w, &h));
        CHECK(x == 1 && y == 2 && w == 10 && h == 80);
        CHECK(Runtime::Restore("hull"));
        CHECK(Runtime::RestoreAll());
        Runtime::ResetMission();
        CHECK(!Runtime::GetRect("hull", false, &x, &y, &w, &h));
        CHECK(!Runtime::Observe(Meter::Hull, frame, {1, 2, 10, 80}, plan));
        Runtime::SetAdapterCapabilities(0);
    }
}

int main()
{
    Geometry(); Lifecycle(); RuntimeBoundary();
    if (OpenShimTest::FailureCount()) return 1;
    std::puts("native HUD geometry/lifecycle/provider tests passed");
    return 0;
}
