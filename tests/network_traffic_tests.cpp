#include "network_traffic.h"
#include "test_check.h"
using OpenShimTest::Check;
int main()
{
    using namespace BZROpenShim;
    NetworkTrafficWindow window;
    window.Reset(10000);
    auto s = window.Snapshot(10000);
    Check(s.route == 0 && s.rxBytes == 0 && s.receiveAgeMs == UINT32_MAX, "empty observer");
    window.Observe(10000, true, 1400, 1);
    window.Observe(10250, false, 800, 1);
    s = window.Snapshot(11000);
    Check(s.txBytes == 1400 && s.rxBytes == 800 && s.txBytesPerSecond == 700 && s.rxBytesPerSecond == 400, "full datagram bytes over fixed window");
    Check(s.route == 1 && s.receiveAgeMs == 750, "relay evidence and wall-clock receive age");
    window.Observe(11250, false, 200, 2);
    Check(window.Snapshot(11250).route == 3, "mixed observed routes");
    s = window.Snapshot(14000);
    Check(s.route == 0 && s.txBytesPerSecond == 0 && s.rxPacketsPerSecond == 0 && s.rxBytes == 1000, "idle ages out without discarding totals");
    window.Observe(14000, true, 600, 4);
    Check(window.Snapshot(14000).route == 4, "unknown endpoint is not direct");
    window.Reset(15000);
    s = window.Snapshot(15000);
    Check(s.txBytes == 0 && s.routeAgeMs == UINT32_MAX, "new lobby resets observations");
    return OpenShimTest::ExitCode();
}
