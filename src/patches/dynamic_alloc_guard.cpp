// dynamic_alloc_guard.cpp
// BZR Open Shim - DynamicMain allocator guard ([Fixes] DynamicAllocGuard).
//
// Every address and offset is GOG 2.2.301 (battlezone98redux.exe-6777ca decompile,
// re-read from the shipping exe in Ghidra):
//   - A DynamicMain chunk holds 0x10000 vertices and 0x18000 16-bit indices.
//     Reserve FUN_0067a110 flushes to a fresh chunk (FUN_00679fe0 zeroes the
//     counts +0x1D4/+0x1D8) when vc+nv > 0x10000 || ic+ni > 0x18000.
//   - Vertex alloc FUN_0067a150: fails ("vertex buffer is full", returns 0) when
//     0x10000-n < [this+0x1D4]; else returns [this+0x1CC] and advances it by
//     n*[this+0x14C] and the vertex count +0x1D4 by n.
//   - Index alloc FUN_0067a1e0: its full-check (cmp at 0x67A1F4) compares
//     0x18000-n with the VERTEX count +0x1D4, though it advances the index
//     count +0x1D8. A valid request fails whenever vc+ni > 0x18000, e.g.
//     PlanarRenderClass::Render FUN_00452580 for a draw_planar radius near 300.
//   - Both checks are unsigned: n above capacity wraps, "succeeds", and the
//     caller writes past the chunk.
//   - Callers write through the result unchecked (crash 0x452CD5, mov [ecx],dx).
//     Every caller runs Reserve, base = FUN_00684c10 (vc - batch start),
//     vertex alloc, then index alloc, and writes indices as base + k.
//
// Fix: patch the cmp to read +0x1D8, and detour both allocators. A request
// that cannot fit, or that the stock function refuses, gets a scratch sink:
// no count or write pointer moves, so commit FUN_00679f10 (which reads the
// counts) draws nothing for it. When a vertex request was sunk, the index
// request that follows on the same object is sunk too, because its indices
// would name vertices that were never written.
#include "bzr_hooks.h"
#include "hook_engine.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "patcher.h"
#include "shim_log.h"

#include <algorithm>
#include <cstdint>
#include <cstdlib>

namespace BZROpenShim
{
    namespace Hooks
    {
        // Both allocators open 55 / 8B EC / 83 EC 08 / 89 4D FC:
        // push ebp; mov ebp,esp; sub esp,8; mov [ebp-4],ecx -- 9 bytes,
        // whole instructions, nothing relative.
        static constexpr size_t kAllocPatchLen = 9;
        static constexpr uint8_t kAllocPrologue[kAllocPatchLen] =
            { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x08, 0x89, 0x4D, 0xFC };
        static constexpr uint8_t kIndexCheckStock[8] = { 0x39, 0x81, 0xD4, 0x01, 0x00, 0x00, 0x76, 0x26 };
        static constexpr uint8_t kIndexCountDisp = 0xD8;

        static constexpr uint32_t kMaxVertices = 0x10000;
        static constexpr uint32_t kMaxIndices = 0x18000;
        static constexpr size_t kOffVertexStride = 0x14C;
        static constexpr size_t kOffVertexCount = 0x1D4;
        static constexpr size_t kOffIndexCount = 0x1D8;
        // Callers write 0x18-byte vertices whatever the stride says; leave room.
        static constexpr uint64_t kMinSinkStride = 0x40;
        // A request beyond this is not a draw; return the stock failure value.
        static constexpr uint64_t kMaxSinkBytes = 64ull * 1024 * 1024;

        typedef void*(__fastcall* FnDynamicAlloc)(void* self, void* edx, uint32_t n);

        static InlineDetour32 g_DynVertexDetour;
        static InlineDetour32 g_DynIndexDetour;
        static FnDynamicAlloc g_StockAllocVertices = nullptr;
        static FnDynamicAlloc g_StockAllocIndices = nullptr;
        static bool g_DynAllocGuardInitialized = false;

        // Render-thread only, like the allocators themselves. Every caller pairs a
        // vertex request with the index request that follows it; an index-only
        // request right after a sunk vertex request would also be sunk (a missed
        // draw, never a crash). Accepted rather than hooking commit/reserve.
        static void* g_VertexSunkOwner = nullptr;
        static volatile long g_VertexSinkCount = 0;
        static volatile long g_IndexSinkCount = 0;

        struct Sink
        {
            uint8_t* data = nullptr;
            uint64_t size = 0;
        };
        static Sink g_VertexSink;
        static Sink g_IndexSink;

        // Grow-only. An outgrown block is kept, not freed, in case a pointer to
        // it is still in use; growth doubles, so that is a few blocks at most.
        static void* SinkFor(Sink& sink, uint64_t bytes)
        {
            if (bytes == 0)
                bytes = 1;
            if (bytes > kMaxSinkBytes)
                return nullptr;
            if (bytes > sink.size)
            {
                uint64_t size = sink.size ? sink.size : 0x10000;
                while (size < bytes)
                    size *= 2;
                auto* data = static_cast<uint8_t*>(std::calloc(1, static_cast<size_t>(size)));
                if (!data)
                    return nullptr;
                sink.data = data;
                sink.size = size;
            }
            return sink.data;
        }

        static bool ShouldLogCount(long count)
        {
            return count > 0 && (count & (count - 1)) == 0;  // 1, 2, 4, 8, ...
        }

        static uint32_t ReadU32(void* self, size_t offset)
        {
            return *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(self) + offset);
        }

        static bool Fits(uint32_t used, uint32_t n, uint32_t capacity)
        {
            return n <= capacity && used <= capacity - n;
        }

        static void* __fastcall DynamicAllocVerticesHook(void* self, void* edx, uint32_t n)
        {
            const uint32_t used = ReadU32(self, kOffVertexCount);
            void* result = nullptr;
            if (Fits(used, n, kMaxVertices))
                result = g_StockAllocVertices(self, edx, n);
            if (result)
            {
                g_VertexSunkOwner = nullptr;
                return result;
            }

            const uint64_t stride = std::max<uint64_t>(ReadU32(self, kOffVertexStride), kMinSinkStride);
            result = SinkFor(g_VertexSink, static_cast<uint64_t>(n) * stride);
            g_VertexSunkOwner = self;
            const long count = InterlockedIncrement(&g_VertexSinkCount);
            if (ShouldLogCount(count))
                Log(L"[DYNALLOC] vertex request %u (in use %u of %u) refused; %s (count %ld)\n",
                    n, used, kMaxVertices, result ? L"sunk, not drawn" : L"too large for the sink", count);
            return result;
        }

        static void* __fastcall DynamicAllocIndicesHook(void* self, void* edx, uint32_t n)
        {
            const bool vertexSunk = g_VertexSunkOwner == self;
            g_VertexSunkOwner = nullptr;
            const uint32_t used = ReadU32(self, kOffIndexCount);
            void* result = nullptr;
            if (!vertexSunk && Fits(used, n, kMaxIndices))
                result = g_StockAllocIndices(self, edx, n);
            if (result)
                return result;

            result = SinkFor(g_IndexSink, static_cast<uint64_t>(n) * 2);
            const long count = InterlockedIncrement(&g_IndexSinkCount);
            if (ShouldLogCount(count))
                Log(L"[DYNALLOC] index request %u (in use %u of %u%s) refused; %s (count %ld)\n",
                    n, used, kMaxIndices, vertexSunk ? L", vertices sunk" : L"",
                    result ? L"sunk, not drawn" : L"too large for the sink", count);
            return result;
        }

        static void PatchIndexFullCheck()
        {
            uint32_t site = 0;
            const HookEngine::EngineRow rows[] = {
                { "DynamicMainIndexFullCheck", &site },
            };
            if (!HookEngine::BindEngineRows("DynamicMain index full-check", rows))
                return;
            if (!ExpectedBytesMatchAt(site, kIndexCheckStock, sizeof(kIndexCheckStock)))
            {
                Log(L"[DYNALLOC] index full-check bytes differ at 0x%08X; not patched\n", site);
                return;
            }
            if (!WritePatchBytes(site + 2, &kIndexCountDisp, 1))
            {
                Log(L"[DYNALLOC] failed patching index full-check at 0x%08X\n", site);
                return;
            }
            Log(L"[DYNALLOC] index full-check reads the index count (0x%08X)\n", site);
        }

        static bool InstallAllocDetour(const char* row, InlineDetour32& detour, void* hook,
                                       FnDynamicAlloc& stock)
        {
            uint32_t fn = 0;
            const HookEngine::EngineRow rows[] = {
                { row, &fn },
            };
            if (!HookEngine::BindEngineRows("DynamicMain alloc guard", rows))
                return false;
            if (!InstallInlineDetour32(detour, fn, hook, kAllocPatchLen,
                                       kAllocPrologue, sizeof(kAllocPrologue),
                                       reinterpret_cast<void* volatile*>(&stock)))
            {
                Log(L"[DYNALLOC] failed installing %hs hook at 0x%08X\n", row, fn);
                return false;
            }
            stock = reinterpret_cast<FnDynamicAlloc>(detour.trampoline);
            return true;
        }

        void InitializeDynamicAllocGuardConfig()
        {
            if (g_DynAllocGuardInitialized)
                return;
            g_DynAllocGuardInitialized = true;

            bool enabled = true;
            bool cfg = true;
            if (TryGetUserConfigBool(kUserConfigFixesSection, "DynamicAllocGuard", cfg))
                enabled = cfg;
            if (!enabled)
            {
                Log(L"[DYNALLOC] Allocator guard disabled by config\n");
                return;
            }

            // Independent of the detours: on its own it removes the spurious
            // "index buffer is full" for requests that do fit.
            PatchIndexFullCheck();

            // The index hook relies on the vertex hook's latch, so install the
            // vertex hook first and skip the index hook without it.
            if (!InstallAllocDetour("DynamicMainAllocVertices", g_DynVertexDetour,
                                    reinterpret_cast<void*>(DynamicAllocVerticesHook),
                                    g_StockAllocVertices))
                return;
            if (!InstallAllocDetour("DynamicMainAllocIndices", g_DynIndexDetour,
                                    reinterpret_cast<void*>(DynamicAllocIndicesHook),
                                    g_StockAllocIndices))
                return;
            Log(L"[DYNALLOC] Allocator guard installed\n");
        }
    }
}
