#pragma once

#include <algorithm>
#include <cstdint>

// The Ogre-facing profiler translation unit is compiled as C++14 because the
// pinned Ogre 1.10 headers depend on standard-library surfaces removed in newer
// language modes. Provide the one C++20 bit helper used by the profiler locally
// rather than lowering the language standard for the rest of OpenShim.
#if defined(_MSVC_LANG) && _MSVC_LANG < 202002L
namespace std
{
    inline int popcount(unsigned long long value) noexcept
    {
        int count = 0;
        while (value != 0)
        {
            value &= (value - 1);
            ++count;
        }
        return count;
    }
}
#endif

namespace BZROpenShim
{
    // Returns true when the Ogre animation/render profiler is enabled. The
    // diagnostic build defaults it on; OPENSHIM_PROFILE_OGRE_ANIMATION or
    // [Diagnostics] ProfileOgreAnimation can explicitly override that default.
    bool IsOgreAnimationProfilerRequested();

    // Starts the read-only profiler. The profiler observes Ogre animation and
    // render submission plus basic DX11 Draw/DrawIndexed activity. It does not
    // change animation state, culling decisions, materials, or render state.
    void InitializeOgreAnimationProfiler();

    // Stops the reporting/discovery worker. Installed observation hooks remain
    // process-lifetime, matching the lifetime of the Ogre/D3D objects they wrap;
    // after shutdown they simply forward without collecting data.
    void ShutdownOgreAnimationProfiler();

    // Hot-path bridge used by the native ChunkEffect hook. The elapsed value
    // is in QueryPerformanceCounter ticks; collection is lock-free and does
    // nothing while the profiler is disabled.
    bool IsOgreAnimationProfilerCollecting() noexcept;
    void RecordNativeChunkSimulationSample(
        uint32_t activeChunks,
        uint64_t elapsedQpcTicks) noexcept;
    void RecordNativeDynamicGeometryPrepareSample(
        const void* objectIdentity,
        bool rebuilt,
        uint64_t elapsedQpcTicks) noexcept;
    void RecordNativeDynamicGeometryQueueSample(
        const void* objectIdentity,
        uint32_t batchCount,
        uint32_t mergeableBatchCount,
        uint32_t blendedBatchCount,
        uint32_t distinctMaterialCount,
        uint64_t vertexCount,
        uint64_t indexCount) noexcept;
    void RecordNativeDynamicGeometryMaterialSample(
        const void* materialIdentity,
        uint32_t batchCount,
        uint32_t blendedBatchCount) noexcept;
}
