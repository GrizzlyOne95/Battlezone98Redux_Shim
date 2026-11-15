#include "d3d11_recovery_policy.h"
#include <cstdio>

using namespace BZROpenShim::D3D11RecoveryPolicy;

int main() {
    int failures = 0;
    const auto check = [&failures](bool ok, const char* text) {
        if (!ok) { std::fprintf(stderr, "FAIL: %s\n", text); ++failures; }
    };

    // Budget: three recoveries in the window are allowed, the fourth is not.
    {
        Budget budget;
        check(budget.Admit(1000), "first recovery admitted");
        check(budget.Admit(2000), "second recovery admitted");
        check(budget.Admit(3000), "third recovery admitted");
        check(!budget.Admit(4000), "fourth recovery inside the window refused");
        check(!budget.Admit(4500), "refusal does not consume a slot (still refused)");
    }
    // The window slides: an old recovery stops counting.
    {
        Budget budget;
        check(budget.Admit(0), "slide: first");
        check(budget.Admit(60000), "slide: second");
        check(budget.Admit(61000), "slide: third");
        check(!budget.Admit(119999), "slide: first still inside the window");
        check(budget.Admit(120000), "slide: first aged out exactly at the window");
        check(!budget.Admit(121000), "slide: three inside again");
    }
    // Spread-out recoveries never exhaust it.
    {
        Budget budget;
        bool all = true;
        for (uint32_t i = 0; i < 20; ++i)
            all = budget.Admit(i * (kWindowMs / 2)) && all;
        check(all, "one recovery per half window is always admitted");
    }
    // GetTickCount wraps every ~49.7 days.
    {
        Budget budget;
        check(budget.Admit(0xFFFFF000u), "wrap: before the wrap");
        check(budget.Admit(0xFFFFFF00u), "wrap: just before the wrap");
        check(budget.Admit(0x00000100u), "wrap: after the wrap");
        check(!budget.Admit(0x00001000u), "wrap: all three still inside the window");
        check(budget.Admit(0xFFFFF000u + kWindowMs), "wrap: first aged out across the wrap");
    }

    // Decisions before the device is created.
    check(BudgetReason(true) == nullptr, "admitted recovery goes ahead");
    check(BudgetReason(false) != nullptr, "exhausted budget fails closed");
    check(AdapterReason(true, false) == nullptr, "settled hardware request goes ahead");
    check(AdapterReason(true, true) == nullptr, "settled: software request goes ahead (hardware is substituted)");
    check(AdapterReason(false, false) == nullptr, "unsettled hardware request is forwarded");
    check(AdapterReason(false, true) != nullptr, "unsettled software request fails closed");

    // Decisions after creation.
    check(AfterCreate(true) == nullptr, "created device goes ahead");
    check(AfterCreate(false) != nullptr, "failed creation fails closed");

    // An exception escaping handleDeviceLost.
    check(!DeviceLostThrowFailsClosed(true, true, true), "throw with back buffer and render target present is rethrown");
    check(DeviceLostThrowFailsClosed(true, false, false), "throw with the back buffer gone fails closed (null swap chain)");
    check(DeviceLostThrowFailsClosed(true, true, false), "back buffer restored but no render target view fails closed (half-restored)");
    check(DeviceLostThrowFailsClosed(false, true, true), "window query failed: state unknown, fails closed");
    check(DeviceLostThrowFailsClosed(false, false, false), "window query failed and nothing restored fails closed");

    if (failures) {
        std::fprintf(stderr, "%d failure(s)\n", failures);
        return 1;
    }
    std::printf("d3d11_recovery_policy_tests: all passed\n");
    return 0;
}
