#include "../src/engine/native_ui_validation.h"

#include <cstdlib>
#include <iostream>

namespace
{
    void Require(bool condition, const char* message)
    {
        if (!condition)
        {
            std::cerr << "FAIL: " << message << '\n';
            std::exit(1);
        }
    }
}

int main()
{
    using namespace BZROpenShim::NativeUiValidation;

    Require(IsSupportedHost(kOptionsParentHost, false),
            "OptionsParent remains supported");
    Require(!IsSupportedHost(kMainMenuHost, false),
            "MainMenu fails closed while disabled");
    Require(IsSupportedHost(kMainMenuHost, true),
            "MainMenu is accepted only after an explicit enable");
    Require(!IsSupportedHost(0, true) && !IsSupportedHost(999, true),
            "invalid hosts fail closed");

    HostIdentity first = {};
    first.host = kMainMenuHost;
    first.screen = 0x1000;
    first.parent = 0x2000;
    first.baselineChildCount = 11;
    first.currentChildCount = 12;
    first.allocatedWidgetCount = 1;
    first.fingerprint = 0x1234;
    first.generation = 7;
    Require(IsValidHostIdentity(first, true), "valid MainMenu identity");

    HostIdentity current = first;
    Require(SameHostLifetime(first, current, true),
            "identical generation and fingerprint stay live");

    current.generation = 8;
    Require(!SameHostLifetime(first, current, true),
            "generation change invalidates stale handles despite address reuse");
    current = first;
    current.fingerprint ^= 1;
    Require(!SameHostLifetime(first, current, true),
            "hierarchy fingerprint change invalidates stale handles");
    current = first;
    current.currentChildCount = 11;
    Require(!SameHostLifetime(first, current, true),
            "missing injected child invalidates the prior lifetime");
    current = first;
    current.parent = 0;
    Require(!SameHostLifetime(first, current, true),
            "invalid host parent fails closed");

    Require(EffectiveVisibility(true, true, true),
            "live visible widget is active");
    Require(!EffectiveVisibility(true, false, true),
            "hidden surface deactivates widgets");
    Require(!EffectiveVisibility(true, true, false),
            "individually hidden widget stays inactive");
    Require(!EffectiveVisibility(false, true, true),
            "released surface stays inactive");

    std::cout << "native_ui_validation_tests passed\n";
    return 0;
}
