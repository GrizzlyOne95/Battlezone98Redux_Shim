#pragma once

namespace BZROpenShim { namespace FogWake {
    // Borrowed for this call only. Row-major clearance sampled at cell centres.
    // A POD boundary keeps the pinned Ogre 1.10 C++14 translation unit separate
    // from the simulation's C++20 implementation.
    struct RendererField
    {
        const float* clearance = nullptr;
        unsigned width = 0, height = 0;
        float cellSize = 1, originX = 0, originZ = 0;
    };
    struct RendererConfig
    {
        float groundY = 0, height = 8, density = .35f;
        float red = .65f, green = .70f, blue = .72f;
        unsigned maxBillboards = 4096;
    };
    // Main world-render thread only, before normal scene visibility gathering.
    // True means resources and geometry are ready, not visual qualification.
    bool UpdateFogWakeRenderer(void* sceneManager, const RendererField& field,
        const RendererConfig& config) noexcept;
    // Pass the current LIVE scene manager. A mismatching/null pointer abandons
    // old scene-owned objects without dereferencing them after scene teardown.
    void ResetFogWakeRenderer(void* liveSceneManager) noexcept;
    unsigned FogWakeRendererBillboardCount() noexcept;
}}
