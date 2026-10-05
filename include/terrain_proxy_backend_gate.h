#pragma once

// Pure renderer-backend gate for the terrain proxy / semantic renderer / HD
// terrain path (src/patches/terrain_proxy.cpp).
//
// That path uploads vertex data and texture arrays through the Direct3D11
// render system's own objects (D3D11HardwareVertexBuffer::getD3DVertexBuffer,
// D3D11Texture::getBuffer). RenderSystem_Direct3D11.dll is loaded in every
// process that lists it in plugins.cfg -- including -renderer:dx9 runs -- so
// module presence proves nothing about which render system owns the buffers.
// Under Direct3D9 the D3D11 accessor reads a D3D9 buffer at a D3D11 member
// offset and the following COM call jumps through garbage (dump 61904).
//
// The gate therefore only opens on a positive identification of the ACTIVE
// render system as Direct3D11; every other outcome fails closed to stock
// terrain. Kept header-only and free of Windows/Ogre types so it is unit
// tested in isolation (tests/terrain_proxy_backend_gate_tests.cpp).

#include <cstdint>

namespace BZROpenShim::TerrainProxyGate
{
    // Mirrors RenderProfiles::IdentifyActiveRenderSystem() return codes.
    enum class ActiveRenderSystem : int
    {
        Fault = -1,      // identification faulted (SEH); retryable
        NotReady = 0,    // Root or its active render system not established yet
        Direct3D11 = 1,
        Direct3D9 = 2,
        OpenGL = 3,
        Unrecognized = 4,
    };

    enum class Decision : uint8_t
    {
        Wait,   // keep polling; nothing installed yet
        Allow,  // active render system is Direct3D11
        Deny,   // anything else: leave stock terrain alone
    };

    constexpr ActiveRenderSystem ActiveRenderSystemFromCode(int code) noexcept
    {
        switch (code)
        {
        case -1: return ActiveRenderSystem::Fault;
        case 0: return ActiveRenderSystem::NotReady;
        case 1: return ActiveRenderSystem::Direct3D11;
        case 2: return ActiveRenderSystem::Direct3D9;
        case 3: return ActiveRenderSystem::OpenGL;
        default: return ActiveRenderSystem::Unrecognized;
        }
    }

    // `timedOut` is true once the caller's identification budget is spent.
    // Transient states (NotReady/Fault) wait until then and are denied after:
    // an unidentified backend is never treated as Direct3D11.
    constexpr Decision DecideTerrainProxyBackend(
        ActiveRenderSystem active, bool timedOut) noexcept
    {
        switch (active)
        {
        case ActiveRenderSystem::Direct3D11:
            return Decision::Allow;
        case ActiveRenderSystem::Direct3D9:
        case ActiveRenderSystem::OpenGL:
        case ActiveRenderSystem::Unrecognized:
            return Decision::Deny;
        case ActiveRenderSystem::NotReady:
        case ActiveRenderSystem::Fault:
        default:
            return timedOut ? Decision::Deny : Decision::Wait;
        }
    }

    constexpr const char* ActiveRenderSystemName(ActiveRenderSystem active) noexcept
    {
        switch (active)
        {
        case ActiveRenderSystem::Fault: return "fault";
        case ActiveRenderSystem::NotReady: return "not-ready";
        case ActiveRenderSystem::Direct3D11: return "Direct3D11";
        case ActiveRenderSystem::Direct3D9: return "Direct3D9";
        case ActiveRenderSystem::OpenGL: return "OpenGL";
        case ActiveRenderSystem::Unrecognized: return "unrecognized";
        }
        return "unrecognized";
    }
}
