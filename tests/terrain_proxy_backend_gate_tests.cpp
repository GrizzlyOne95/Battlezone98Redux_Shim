#include "terrain_proxy_backend_gate.h"

#include <cstdio>
#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim::TerrainProxyGate;

int main()
{
    // Only a positive Direct3D11 identification opens the gate.
    Check(DecideTerrainProxyBackend(ActiveRenderSystem::Direct3D11, false) == Decision::Allow,
        "Direct3D11 allows the terrain proxy");
    Check(DecideTerrainProxyBackend(ActiveRenderSystem::Direct3D11, true) == Decision::Allow,
        "Direct3D11 allows even at the identification deadline");

    // Dump 61904: -renderer:dx9 with TerrainHdEnabled=1 must stay stock.
    Check(DecideTerrainProxyBackend(ActiveRenderSystem::Direct3D9, false) == Decision::Deny,
        "Direct3D9 denies immediately");
    Check(DecideTerrainProxyBackend(ActiveRenderSystem::OpenGL, false) == Decision::Deny,
        "OpenGL denies immediately");
    Check(DecideTerrainProxyBackend(ActiveRenderSystem::Unrecognized, false) == Decision::Deny,
        "unrecognized render system denies immediately");

    // Transient states wait, then fail closed.
    Check(DecideTerrainProxyBackend(ActiveRenderSystem::NotReady, false) == Decision::Wait,
        "not-ready waits");
    Check(DecideTerrainProxyBackend(ActiveRenderSystem::Fault, false) == Decision::Wait,
        "fault waits");
    Check(DecideTerrainProxyBackend(ActiveRenderSystem::NotReady, true) == Decision::Deny,
        "not-ready at deadline denies");
    Check(DecideTerrainProxyBackend(ActiveRenderSystem::Fault, true) == Decision::Deny,
        "fault at deadline denies");

    // Code mapping matches RenderProfiles::IdentifyActiveRenderSystem().
    Check(ActiveRenderSystemFromCode(-1) == ActiveRenderSystem::Fault, "code -1 is fault");
    Check(ActiveRenderSystemFromCode(0) == ActiveRenderSystem::NotReady, "code 0 is not-ready");
    Check(ActiveRenderSystemFromCode(1) == ActiveRenderSystem::Direct3D11, "code 1 is D3D11");
    Check(ActiveRenderSystemFromCode(2) == ActiveRenderSystem::Direct3D9, "code 2 is D3D9");
    Check(ActiveRenderSystemFromCode(3) == ActiveRenderSystem::OpenGL, "code 3 is OpenGL");
    Check(ActiveRenderSystemFromCode(4) == ActiveRenderSystem::Unrecognized, "code 4 is unrecognized");
    Check(ActiveRenderSystemFromCode(99) == ActiveRenderSystem::Unrecognized,
        "unknown codes are unrecognized, never D3D11");
    Check(DecideTerrainProxyBackend(ActiveRenderSystemFromCode(-7), true) == Decision::Deny,
        "garbage codes never allow");

    if (OpenShimTest::FailureCount() == 0)
        std::puts("terrain proxy backend gate tests passed");
    return OpenShimTest::ExitCode();
}
