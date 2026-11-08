#include "terrain_tile_blend.h"
#include "engine_globals.h"

#include "hook_engine.h"
#include "memory_access.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <array>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace
    {
        constexpr std::size_t kTerrainVertexCount = 0x24C1; // 97 * 97
        constexpr std::size_t kTerrainVertexStride = 16;
        constexpr std::size_t kTerrainColorOffset = 12;
        constexpr std::size_t kTerrainVertexBytes =
            kTerrainVertexCount * kTerrainVertexStride;
        constexpr std::size_t kExpectedSeamVertexCount = 2848;

        constexpr std::ptrdiff_t kManagerGpuBufferSharedPtrOffset = 0x04;
        constexpr std::ptrdiff_t kManagerCpuVertexBufferOffset = 0x80;

        constexpr char kTrnSection[] = "OpenShim";
        constexpr char kTrnKey[] = "TerrainTileBlend";

        using FnTerrainManager = void* (__cdecl*)();
        using FnTrnGetFloat = float (__cdecl*)(
            const char* section, const char* key, float fallback, const char* path);
        using FnWriteData = void (__thiscall*)(
            void* buffer, std::size_t offset, std::size_t length,
            const void* source, bool discardWholeBuffer);

        std::array<std::uint8_t, kTerrainVertexCount> g_seamMask = {};
        bool g_seamMaskCaptured = false;
        std::uint8_t g_currentEdgeAlpha = 0;

        bool CaptureSeamMask(std::uint8_t* vertices)
        {
            std::size_t seamCount = 0;
            for (std::size_t index = 0; index < kTerrainVertexCount; ++index)
            {
                const std::uint8_t* color =
                    vertices + index * kTerrainVertexStride + kTerrainColorOffset;
                if (color[0] != 0xFF || color[1] != 0xFF || color[2] != 0xFF ||
                    (color[3] != 0x00 && color[3] != 0xFF))
                {
                    return false;
                }
                g_seamMask[index] = color[3] == 0x00 ? 1u : 0u;
                seamCount += g_seamMask[index];
            }

            if (seamCount != kExpectedSeamVertexCount)
                return false;

            g_seamMaskCaptured = true;
            g_currentEdgeAlpha = 0;
            return true;
        }

        bool ReadCurrentTrnName(char (&name)[MAX_PATH])
        {
            name[0] = '\0';
            const auto* source = reinterpret_cast<const char*>(EngineGlobals::CurrentTrnName());
            if (!source || !BZROpenShim::MemoryAccess::IsReadable(source, MAX_PATH))
                return false;

            __try
            {
                strncpy_s(name, source, _TRUNCATE);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                name[0] = '\0';
                return false;
            }
            return name[0] != '\0';
        }

        bool UploadTerrainVertices(void* gpuBuffer, const void* vertices)
        {
            if (!BZROpenShim::MemoryAccess::IsReadable(gpuBuffer, sizeof(void*)))
                return false;

            void** vtable = nullptr;
            __try
            {
                vtable = *reinterpret_cast<void***>(gpuBuffer);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            if (!BZROpenShim::MemoryAccess::IsReadable(vtable, 7 * sizeof(void*)))
                return false;

            const auto writeData = reinterpret_cast<FnWriteData>(vtable[6]);
            if (!BZROpenShim::MemoryAccess::IsExecutable(reinterpret_cast<const void*>(writeData)))
                return false;

            __try
            {
                writeData(gpuBuffer, 0, kTerrainVertexBytes, vertices, true);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            return true;
        }
    }

    namespace
    {
        std::atomic<bool> g_BlendPending{ false };
        // Ticks to keep retrying while the TRN name or the terrain vertex
        // buffer is not there yet (~10 s at 60 fps), then give up and log.
        constexpr int kBlendRetryTicks = 600;
        int g_BlendRetriesLeft = 0;

        // Returns false only for "not ready yet" (worth retrying next tick).
        bool ApplyTerrainTileBlend(bool lastAttempt);
    }

    void RequestTerrainTileBlendAtFirstSimTick()
    {
        g_BlendRetriesLeft = kBlendRetryTicks;
        g_BlendPending.store(true, std::memory_order_release);
    }

    void TerrainTileBlendSimTick()
    {
        if (!g_BlendPending.exchange(false, std::memory_order_acq_rel))
            return;
        const bool lastAttempt = --g_BlendRetriesLeft <= 0;
        if (!ApplyTerrainTileBlend(lastAttempt) && !lastAttempt)
            g_BlendPending.store(true, std::memory_order_release);
    }

    void ApplyTerrainTileBlendForCurrentMission()
    {
        ApplyTerrainTileBlend(true);
    }

    namespace {
    bool ApplyTerrainTileBlend(bool lastAttempt)
    {
        const auto managerAddress =
            HookEngine::ResolveNamedAddress("Terrain::GetManager");
        const auto getFloatAddress =
            HookEngine::ResolveNamedAddress("Terrain::GetFloat");
        if (!managerAddress || !getFloatAddress ||
            !BZROpenShim::MemoryAccess::IsExecutable(reinterpret_cast<const void*>(managerAddress)) ||
            !BZROpenShim::MemoryAccess::IsExecutable(reinterpret_cast<const void*>(getFloatAddress)))
        {
            LogShimA(LogLevel::Warn, "terrain-blend",
                "[TERRAIN-BLEND] required released terrain helpers unresolved; stock seams retained");
            return true;
        }

        char trnName[MAX_PATH] = {};
        if (!ReadCurrentTrnName(trnName))
        {
            if (lastAttempt)
                LogShimA(LogLevel::Warn, "terrain-blend",
                    "[TERRAIN-BLEND] current TRN name unavailable; stock seams retained");
            return false;
        }

        const auto getManager = reinterpret_cast<FnTerrainManager>(managerAddress);
        const auto getFloat = reinterpret_cast<FnTrnGetFloat>(getFloatAddress);
        void* manager = nullptr;
        float requestedBlend = 1.0f;
        __try
        {
            manager = getManager();
            requestedBlend = getFloat(kTrnSection, kTrnKey, 1.0f, trnName);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            LogShimA(LogLevel::Warn, "terrain-blend",
                "[TERRAIN-BLEND] native TRN read failed trn=\"%s\"; stock seams retained",
                trnName);
            return true;
        }

        if (!manager || !BZROpenShim::MemoryAccess::IsReadable(manager, 0x84))
            return false;

        std::uint8_t* vertices = nullptr;
        void* gpuBuffer = nullptr;
        __try
        {
            vertices = *reinterpret_cast<std::uint8_t**>(
                static_cast<std::uint8_t*>(manager) + kManagerCpuVertexBufferOffset);
            gpuBuffer = *reinterpret_cast<void**>(
                static_cast<std::uint8_t*>(manager) + kManagerGpuBufferSharedPtrOffset);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return true;
        }

        if (!BZROpenShim::MemoryAccess::IsWritable(vertices, kTerrainVertexBytes))
            return false;
        if (!g_seamMaskCaptured && !CaptureSeamMask(vertices))
        {
            LogShimA(LogLevel::Warn, "terrain-blend",
                "[TERRAIN-BLEND] shared COLOR0 layout did not match the released 97x97 seam mask; stock seams retained");
            return true;
        }

        const float blend = NormalizeTerrainTileBlend(requestedBlend);
        const std::uint8_t edgeAlpha = TerrainTileBlendEdgeAlpha(blend);
        if (edgeAlpha == g_currentEdgeAlpha)
        {
            LogShimA(LogLevel::Info, "terrain-blend",
                "[TERRAIN-BLEND] trn=\"%s\" blend=%.3f edgeAlpha=%u unchanged",
                trnName, static_cast<double>(blend), edgeAlpha);
            return true;
        }

        for (std::size_t index = 0; index < kTerrainVertexCount; ++index)
        {
            vertices[index * kTerrainVertexStride + kTerrainColorOffset + 3] =
                g_seamMask[index] ? edgeAlpha : 0xFF;
        }

        if (!gpuBuffer || !UploadTerrainVertices(gpuBuffer, vertices))
        {
            LogShimA(LogLevel::Warn, "terrain-blend",
                "[TERRAIN-BLEND] trn=\"%s\" blend=%.3f CPU mask updated but GPU upload failed",
                trnName, static_cast<double>(blend));
            return true;
        }

        g_currentEdgeAlpha = edgeAlpha;
        LogShimA(LogLevel::Info, "terrain-blend",
            "[TERRAIN-BLEND] trn=\"%s\" blend=%.3f edgeAlpha=%u seamVertices=%zu applied",
            trnName, static_cast<double>(blend), edgeAlpha,
            kExpectedSeamVertexCount);
        return true;
    }
    } // namespace
}
