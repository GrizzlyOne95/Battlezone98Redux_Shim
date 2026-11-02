#include "lan_no_auth_policy.h"
#include "test_check.h"
using namespace BZROpenShim::LanNoAuth;
int main()
{
    std::string out;
    CHECK(PrivateEndpoint("192.168.1.7", out) && out == "192.168.1.7:1337");
    CHECK(PrivateEndpoint("127.0.0.1:1437", out) && out == "127.0.0.1:1437");
    CHECK(PrivateEndpoint("10.1.2.3:65534", out));
    CHECK(PrivateEndpoint("172.31.1.1", out));
    CHECK(PrivateEndpoint("169.254.7.9", out));
    for (const auto* text : {"8.8.8.8", "172.32.0.1", "100.64.1.2", "localhost", "host.lan",
         "192.168.1.255", "255.255.255.255", "0.0.0.0", "127.0.0.1:0", "127.0.0.1:65535",
         "192.168.1", "192.168.1.1.extra", "192.168.1.256", "::1", "192.168.1.1:abc",
         "ws://192.168.1.1/", "127.0000.0.1"})
        CHECK(!PrivateEndpoint(text, out) && out.empty());
    CHECK(NativeIdentityMatches(3, 42, 42));
    CHECK(!NativeIdentityMatches(1, 42, 42));
    CHECK(!NativeIdentityMatches(2, 42, 42));
    CHECK(!NativeIdentityMatches(3, 0, 0));
    CHECK(!NativeIdentityMatches(3, 42, 43));
    return OpenShimTest::ExitCode();
}
