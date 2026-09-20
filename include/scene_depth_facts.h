// Scene-depth qualification: the bookkeeping half.
//
// Phase A of Docs/DX11_SCENE_DEPTH_AND_SCREENSPACE_EFFECTS.md asks one
// question: which D3D11 depth texture is the main gameplay depth surface, and
// how do we tell it apart from shadow maps, the satellite view, the scope, and
// temporary RTTs? Everything downstream - MSAA depth extraction, a linear-depth
// product, SSAO, depth haze, soft particles - is blocked on answering it from
// evidence rather than from API convention.
//
// This header is the part of that instrument with no D3D11 in it. It holds the
// facts recorded about each depth resource and the rules for deciding whether
// an address we have seen before is the same resource or a new one in a reused
// allocation. That distinction is the whole lifetime question - a mission
// change or a resize destroys and recreates depth surfaces, and COM will
// happily hand back the same address - so it is worth being able to test
// without a game present.
//
// Deliberately free of <Windows.h> and of every D3D11 type: formats, bind flags
// and view dimensions arrive as plain integers with the same numeric values the
// DXGI/D3D11 headers give them. The shell that does the hooking lives in
// src/patches/dx11_scene_depth.cpp.
//
// Nothing here classifies a resource as "the main scene depth". That is the
// conclusion Phase A is meant to REACH, and inventing the rule before the
// capture exists is exactly what the investigation warns against.

#pragma once

#include <cstddef>
#include <cstdint>

namespace BZROpenShim::SceneDepth
{
    // Numeric values match the D3D11/DXGI headers. Only the ones this
    // instrument reasons about are named.
    namespace Native
    {
        constexpr uint32_t kBindDepthStencil = 0x40u;   // D3D11_BIND_DEPTH_STENCIL
        constexpr uint32_t kBindShaderResource = 0x8u;  // D3D11_BIND_SHADER_RESOURCE

        constexpr uint32_t kFormatUnknown = 0u;
        constexpr uint32_t kFormatR32Typeless = 39u;    // DXGI_FORMAT_R32_TYPELESS
        constexpr uint32_t kFormatD32Float = 40u;       // DXGI_FORMAT_D32_FLOAT
        constexpr uint32_t kFormatR32Float = 41u;       // DXGI_FORMAT_R32_FLOAT
        constexpr uint32_t kFormatR24G8Typeless = 44u;  // DXGI_FORMAT_R24G8_TYPELESS
        constexpr uint32_t kFormatD24UnormS8Uint = 45u; // DXGI_FORMAT_D24_UNORM_S8_UINT
        constexpr uint32_t kFormatR16Typeless = 53u;    // DXGI_FORMAT_R16_TYPELESS
        constexpr uint32_t kFormatD16Unorm = 55u;       // DXGI_FORMAT_D16_UNORM

        constexpr uint32_t kDsvDimensionTexture2D = 3u;   // D3D11_DSV_DIMENSION_TEXTURE2D
        constexpr uint32_t kDsvDimensionTexture2DMs = 5u; // D3D11_DSV_DIMENSION_TEXTURE2DMS
    }

    // What CreateTexture2D was asked for. `resource` is the returned interface
    // address, used as identity only and never dereferenced here.
    struct TextureFacts
    {
        uint64_t resource = 0;
        uint32_t width = 0;
        uint32_t height = 0;
        uint32_t format = Native::kFormatUnknown;
        uint32_t sampleCount = 1;
        uint32_t sampleQuality = 0;
        uint32_t bindFlags = 0;
        uint32_t miscFlags = 0;
        uint32_t arraySize = 1;
        uint32_t mipLevels = 1;
        uint32_t usage = 0;
    };

    // What was observed about a depth resource while it was alive.
    struct Observation
    {
        TextureFacts facts;
        uint32_t serial = 0;       // stable within a process; survives address reuse
        uint32_t generation = 0;   // bumped each time this address is reused
        uint32_t dsvCount = 0;     // depth-stencil views created over it
        uint32_t dsvFormat = Native::kFormatUnknown;
        uint32_t dsvDimension = 0;
        uint64_t bindCount = 0;    // times it was the active DSV
        uint32_t lastRtWidth = 0;  // render target bound alongside it
        uint32_t lastRtHeight = 0;
        uint32_t lastRtCount = 0;
        bool everBoundWithRenderTarget = false;
        bool inUse = false;
    };

    // A depth resource is one the engine asked to be usable as a depth-stencil
    // target. Read from the bind flags rather than from the format: BZR's
    // shipped path creates R32_TYPELESS, and a typeless format on its own says
    // nothing about what the resource is for.
    bool IsDepthCandidate(uint32_t bindFlags);

    // Can this resource be sampled as it stands? The fog qualification found
    // that at FSAA=8 Ogre does NOT add BIND_SHADER_RESOURCE, which is the
    // single fact that decides whether Phase B needs a creation-time change.
    bool IsShaderReadable(uint32_t bindFlags);

    bool IsMultisampled(const TextureFacts& facts);

    // Two sets of facts describe the same surface. Used to tell "COM handed
    // back an address we have seen before, for the same thing" from "this
    // address has been recycled for a different surface", which is how a
    // recreate across a mission change or a resize is detected without hooking
    // Release.
    bool SameResourceShape(const TextureFacts& a, const TextureFacts& b);

    // Human-readable names for the log. Unknown values render as a number, so a
    // capture is never silently lossy.
    const char* FormatName(uint32_t format);
    const char* DsvDimensionName(uint32_t dimension);

    // Bounded registry of the depth resources seen so far.
    //
    // Bounded on purpose: this runs inside CreateTexture2D on the render
    // thread, and an instrument that can grow without limit in response to
    // engine behaviour is a way to turn a diagnostic into an outage. Overflow
    // is recorded and reported rather than absorbed.
    class Registry
    {
    public:
        static constexpr size_t kCapacity = 64;

        enum class Event
        {
            Ignored,    // not a depth resource
            Added,      // first sighting
            Recreated,  // known address, different surface
            Known,      // already recorded, unchanged
            Overflow,   // no room left; nothing recorded
        };

        Event Observe(const TextureFacts& facts, uint32_t* outSerial = nullptr);

        // Associates a depth-stencil view with the resource it was created
        // over. Returns false when the resource is not one we are tracking.
        bool NoteDepthStencilView(uint64_t resource, uint32_t dsvFormat, uint32_t dsvDimension);

        // Records that the resource was the active DSV, with the dimensions of
        // the render target bound alongside it. Those dimensions are how the
        // main view is eventually told apart from shadow and RTT passes.
        bool NoteBind(uint64_t resource, uint32_t rtWidth, uint32_t rtHeight, uint32_t rtCount);

        const Observation* Find(uint64_t resource) const;
        const Observation* At(size_t index) const;

        size_t Size() const { return m_count; }
        bool Overflowed() const { return m_overflowed; }
        uint32_t NextSerial() const { return m_nextSerial; }

        void Clear();

    private:
        Observation* FindMutable(uint64_t resource);

        Observation m_entries[kCapacity] = {};
        size_t m_count = 0;
        uint32_t m_nextSerial = 1;
        bool m_overflowed = false;
    };
}
