// OpenShim Enhanced resource bootstrap policy tests. Pure logic: no engine,
// no game. Build+run via scripts/run_render_profile_tests.ps1 and CTest.

#include "enhanced_resource_bootstrap.h"

#include <cstdio>
#include <string>

using namespace BZROpenShim::RenderProfiles::EnhancedBootstrap;

namespace
{
    int g_failures = 0;

    void ExpectTrue(bool condition, const char* what)
    {
        if (!condition)
        {
            std::printf("  FAIL: %s\n", what);
            ++g_failures;
        }
    }

    void ExpectContains(const std::string& haystack, const char* needle,
                        const char* what)
    {
        if (haystack.find(needle) == std::string::npos)
        {
            std::printf("  FAIL: %s ('%s' missing '%s')\n", what,
                        haystack.c_str(), needle);
            ++g_failures;
        }
    }

    BootstrapObservations AllGood()
    {
        BootstrapObservations o;
        o.probeResolvedDirectory = true;
        o.ogreApiResolved = true;
        o.groupRegistered = true;
        o.canonicalProgramResolved = true;
        return o;
    }
}

void TestReadyRequiresEveryStep()
{
    std::printf("TestReadyRequiresEveryStep\n");
    ExpectTrue(DecideBootstrapState(AllGood()) == BootstrapState::Ready,
               "all four observations -> Ready");

    // Each step alone is enough to withhold the capability. Any one of these
    // failing leaves the OSE namespace absent, and a synthesis path that
    // believed otherwise would bind names that do not exist.
    BootstrapObservations o = AllGood();
    o.probeResolvedDirectory = false;
    ExpectTrue(DecideBootstrapState(o) == BootstrapState::Unavailable,
               "no asset pack -> Unavailable");

    o = AllGood();
    o.ogreApiResolved = false;
    ExpectTrue(DecideBootstrapState(o) == BootstrapState::Unavailable,
               "ResourceGroupManager exports missing -> Unavailable");

    o = AllGood();
    o.groupRegistered = false;
    ExpectTrue(DecideBootstrapState(o) == BootstrapState::Unavailable,
               "group registration failed -> Unavailable");

    // The one that matters most: an empty or wrong directory still creates
    // and initialises a group perfectly happily, so "the group exists" says
    // nothing about whether the payload actually declares anything.
    o = AllGood();
    o.canonicalProgramResolved = false;
    ExpectTrue(DecideBootstrapState(o) == BootstrapState::Unavailable,
               "group present but OSE programs unresolvable -> Unavailable");

    ExpectTrue(DecideBootstrapState(BootstrapObservations{}) ==
                   BootstrapState::Unavailable,
               "nothing succeeded -> Unavailable");
}

void TestIdempotency()
{
    std::printf("TestIdempotency\n");
    ExpectTrue(ShouldAttemptBootstrap(BootstrapState::NotAttempted),
               "first call may attempt");
    ExpectTrue(!ShouldAttemptBootstrap(BootstrapState::Ready),
               "never re-register once ready");
    ExpectTrue(!ShouldAttemptBootstrap(BootstrapState::Attempting),
               "a concurrent caller cannot duplicate registration");
    // A failed attempt is as final as a successful one -- retrying per draw
    // or per material is precisely the behaviour this must not have.
    ExpectTrue(!ShouldAttemptBootstrap(BootstrapState::Unavailable),
               "never retry after failure");
}

void TestCapabilityGate()
{
    std::printf("TestCapabilityGate\n");
    ExpectTrue(IsEnhancedCapabilityAvailable(BootstrapState::Ready),
               "Ready grants the capability");
    ExpectTrue(!IsEnhancedCapabilityAvailable(BootstrapState::NotAttempted),
               "capability withheld before the bootstrap runs");
    ExpectTrue(!IsEnhancedCapabilityAvailable(BootstrapState::Attempting),
               "capability withheld while registration is in flight");
    ExpectTrue(!IsEnhancedCapabilityAvailable(BootstrapState::Unavailable),
               "capability withheld after failure");
}

void TestGroupContract()
{
    std::printf("TestGroupContract\n");
    const std::string group = ResourceGroupName();
    ExpectTrue(!group.empty(), "group name is set");
    // The game clears and re-initialises Modable on every mod staging cycle,
    // which would drop OpenShim's payload mid-session.
    ExpectTrue(group != "Modable", "never share the Modable lifecycle");
    ExpectTrue(group != "General" && group != "Internal" &&
                   group != "Autodetect",
               "never reuse an Ogre/game boot group");
    ExpectTrue(std::string(ResourceLocationType()) == "FileSystem",
               "a deployed directory is a FileSystem archive");
    const std::string probe = CanonicalProbeProgram();
    ExpectTrue(probe.rfind("OSE_", 0) == 0, "probe program is OpenShim-owned");
}

void TestLogFormats()
{
    std::printf("TestLogFormats\n");
    ExpectContains(FormatBootstrapReadyLog("C:\\game\\mods\\123\\openshim\\renderer\\enhanced"),
                   "[OSE]", "ready line is tagged");
    ExpectContains(FormatBootstrapReadyLog("C:\\game\\mods\\123\\openshim\\renderer\\enhanced"),
                   "mods", "ready line names the resolved directory");
    ExpectContains(FormatBootstrapReadyLog(""), "<unresolved>",
                   "empty directory is explicit");

    BootstrapObservations o;
    o.probeResolvedDirectory = true;
    const std::string failed = FormatBootstrapFailedLog(o, "no such group");
    ExpectContains(failed, "[OSE]", "failure line is tagged");
    ExpectContains(failed, "probe=ok", "failure line reports what did work");
    ExpectContains(failed, "abi=MISSING", "failure line names the failing step");
    ExpectContains(failed, "disabled", "failure line states the consequence");
    ExpectContains(failed, "no such group", "failure line carries the detail");
    ExpectContains(FormatBootstrapFailedLog(o, ""), "probe=ok",
                   "empty detail still formats");
}

int main()
{
    TestReadyRequiresEveryStep();
    TestIdempotency();
    TestCapabilityGate();
    TestGroupContract();
    TestLogFormats();

    if (g_failures != 0)
    {
        std::printf("\nenhanced_resource_bootstrap_tests FAILED (%d)\n",
                    g_failures);
        return 1;
    }
    std::printf("\nenhanced_resource_bootstrap_tests passed\n");
    return 0;
}
