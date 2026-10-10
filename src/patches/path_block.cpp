// path_block.cpp
// BZR Open Shim - PathBlockFaces: building path-grid footprints from collision
// faces for ODFs that opt in (pathBlock = "faces" / "none").
//
// Stock AI planning marks the whole oriented SDF bounding box of every class
// 2/5/10/TURR object as building (cellType |= 0xB). Tunnels, arcades and walk-in
// rooms are therefore solid to the planner even though vehicles and pilots fit
// through them. Local steering (FindPotentialField) ignores class 2/10, so the
// grid is the only obstacle. The geometry and the contract shared with EXU live
// in include/path_block_geometry.h (pure, host tested); this file is the engine
// seam.
//
// Engine facts, GOG Redux 2.2.301 (SHA-256 8d71f56c...3377413), confirmed in
// the shipping image:
//   BlockCells(GameObject*, bool add)  0x00468A70  cdecl; detoured here (entry)
//     callers: ProcessBuildings 0x00469C70 (map PostLoad, call 0x00469D77),
//     AiUtilFeature::AddObject 0x0046B100 (0x0046B18A; Lua BuildObject and every
//     runtime spawn), AiUtilFeature::DeleteObject 0x0046B1A0 (0x0046B22A), and
//     the Producer/ConstructionRig deploy paths (0x005AC047, 0x005AC0A8,
//     0x005AC95B, 0x005AD46D, 0x005AFF38).
//     Class 5 takes the perimeter branch (bit 8 only); everything else builds
//     the quad blockVertArray (0x0260D158, 4 x {x,z} floats) from
//     get_obj_bounding_box and the object matrix ([obj+0xF4]+0x20), stores the
//     quad's AABB in buildingArea, and calls BuildingCells -> UpdateCells
//     (0x004690F0) with BuildingBlock (0x004693C0, |= 0xB) or, on delete,
//     BuildingUnblock (0x004697C0: &= 0xF4, then re-derives the steep/slope
//     bits 2/1 from terrain) over the WHOLE stored AABB, then InvalidateStrips
//     (0x0058D090).
//   cellType byte grid 0x0260D178; GridMinX/MaxX 0x02CE99C0/0x02CE99A0,
//   GridMinZ/MaxZ 0x02CD9984/0x02CE99C4; Grid_Size 0x02CC50E0 (5.0, stored by
//   0x0077E990), Grid_Scale 0x02CC50E4 = 1/size.
//   Cell (gx,gz) = (floor(x/size), floor(z/size)); index = (gx - MinX) +
//   (MaxX - MinX) * (gz - MinZ); BuildingBlock tests the cell centre
//   ((g + 0.5) * size).
//
// Flow, per the shared contract's idempotence rule:
//   add:    the stock call runs first (it owns buildingArea, the quad and strip
//           invalidation). For a flagged ODF every cell of its stock box is
//           then recomputed from scratch: building bits are cleared through
//           the engine's own BuildingUnblock (terrain bits re-derived, never
//           guessed) and re-added when the cell is inside this object's solids
//           or covered by any other blocker (stock box for unflagged objects,
//           face mask for flagged ones). Strips are invalidated again.
//   delete: the stock call clears the whole AABB (which also wipes overlapping
//           neighbours: a stock bug). When any flagged object exists, every
//           remaining blocker's cells in that AABB are re-added.
// Running twice, or after an EXU pass over the same contract, converges on
// the same grid. Unflagged worlds are untouched: no recompute happens until a
// flagged object is present.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "patcher.h"
#include "path_block_geometry.h"

#include <Windows.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
namespace Hooks
{
namespace
{
    namespace PB = ::BZROpenShim::PathBlock;

    using FnBlockCells = void(__cdecl*)(void* object, int add);
    using FnBuildingUnblock = void(__cdecl*)(int index, int gx, int gz);
    using FnInvalidateStrips = void(__cdecl*)(float x0, float z0, float x1, float z1);
    // Engine file-system read 0x008290F0: (name, out size, caller buffer, capacity) -> nonzero on success.
    using FnReadFile = int(__cdecl*)(const char* name, int* size, void* buffer, int capacity);

    // BlockCells' prologue: push ebp / mov ebp,esp / sub esp,0x64. The detour
    // overwrites five bytes, landing inside the sub, so six are relocated.
    constexpr uint8_t kBlockCellsPrologue[6] = {0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x64};
    constexpr size_t kRelocated = sizeof(kBlockCellsPrologue);

    // Written into blockVertArray[0].x before the stock call: still present
    // afterwards means the stock call built no quad (perimeter class 5, a
    // degenerate bbox, or no grid).
    constexpr uint32_t kQuadSentinel = 0x7FBADBADu;

    constexpr size_t kObjMatrixOffset = 0x20;        // [obj+0xF4]+0x20, read by BlockCells 0x00468B07
    constexpr size_t kMatrixPositXOffset = 0x28;     // double, 0x00468B3D
    constexpr size_t kMatrixPositZOffset = 0x38;     // double
    constexpr uint8_t kBuildingBits = 0x0B;

    struct Engine
    {
        uint8_t** cellType = nullptr;
        float* gridSize = nullptr;
        int* gridMinX = nullptr;
        int* gridMaxX = nullptr;
        int* gridMinZ = nullptr;
        int* gridMaxZ = nullptr;
        float* blockVerts = nullptr;
        FnBuildingUnblock buildingUnblock = nullptr;
        FnInvalidateStrips invalidateStrips = nullptr;
        FnReadFile readFile = nullptr;
        FnBlockCells original = nullptr;
    };

    Engine g_Engine;
    bool g_Ready = false;
    bool g_Trace = false;

    struct OdfEntry
    {
        PB::Spec spec;
        bool flagged = false;
        std::unique_ptr<PB::Model> model;
        std::unordered_map<uint64_t, bool> memo; // quantised local (x,z) -> solid
    };

    struct Blocker
    {
        PB::Mode mode = PB::Mode::Box;
        PB::Quad quad;
        float x0 = 0, z0 = 0, x1 = 0, z1 = 0; // quad AABB == stock buildingArea
        std::vector<int> solid;                // sorted cell indices (faces mode)
        std::string odf;
    };

    std::unordered_map<std::string, std::unique_ptr<OdfEntry>> g_Odfs;
    std::unordered_map<void*, Blocker> g_Blockers;
    int g_FlaggedCount = 0;
    uint8_t* g_SeenGrid = nullptr;
    int g_SeenDims[4] = {};
    unsigned g_SummaryLines = 0;
    constexpr unsigned kSummaryLineBudget = 256;

    // --- SEH-guarded engine reads (POD only) ------------------------------

    bool SafeReadPlacement(void* object, PB::Placement& out)
    {
        __try
        {
            auto* obj = static_cast<uint8_t*>(object);
            auto* obj76 = *reinterpret_cast<uint8_t**>(obj + ObjectLayout::kGameObjectObj76);
            if (!obj76)
                return false;
            const uint8_t* m = obj76 + kObjMatrixOffset;
            const float* f = reinterpret_cast<const float*>(m);
            out.rightX = f[0];
            out.rightZ = f[2];
            out.frontX = f[6];
            out.frontZ = f[8];
            out.positX = *reinterpret_cast<const double*>(m + kMatrixPositXOffset);
            out.positZ = *reinterpret_cast<const double*>(m + kMatrixPositZOffset);
            return std::isfinite(out.rightX) && std::isfinite(out.frontZ) && std::isfinite(out.positX) &&
                   std::isfinite(out.positZ);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool SafeCopy(const void* src, void* dst, size_t n)
    {
        __try
        {
            std::memcpy(dst, src, n);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool SafeCallOriginal(void* object, int add)
    {
        __try
        {
            g_Engine.original(object, add);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool SafeReadFile(const char* name, int& size, void* buffer, int capacity)
    {
        __try
        {
            return g_Engine.readFile(name, &size, buffer, capacity) != 0;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    // Reads a file straight from the engine's file system (0x008290F0, the read
    // under the item cache), so addon directories and packed archives resolve
    // as they do for the game. Never through the item cache (UseItem /
    // UnlockItem): BlockCells runs while the building being added still relies
    // on cached SDF/GEO items, and loading a faces model's SDF + GEOs through
    // that bounded cache left the object with a degenerate bounding box: no
    // stock footprint, no building collision (Bane ruins, 2026-10-06).
    bool ReadGameFile(const std::string& name, std::vector<uint8_t>& out)
    {
        constexpr int kMaxFile = 16 * 1024 * 1024;
        constexpr int kRetryArchive = 4 * 1024 * 1024;
        out.resize(256 * 1024);
        for (int attempt = 0; attempt < 2; ++attempt)
        {
            int size = 0;
            if (SafeReadFile(name.c_str(), size, out.data(), static_cast<int>(out.size())) && size > 0 &&
                static_cast<size_t>(size) <= out.size())
            {
                out.resize(static_cast<size_t>(size));
                return true;
            }
            // Too small a buffer: a loose file fails after reporting its size (0x00828DC0); a packed record
            // (0x008273E0) fails without one, so it gets one retry at kRetryArchive.
            int retry = size > static_cast<int>(out.size()) ? size : (size == 0 ? kRetryArchive : 0);
            if (attempt > 0 || retry <= static_cast<int>(out.size()) || retry > kMaxFile)
                break;
            out.resize(static_cast<size_t>(retry));
        }
        out.clear();
        return false;
    }

    PB::GridDesc ReadGrid()
    {
        PB::GridDesc g;
        g.size = *g_Engine.gridSize;
        g.minX = *g_Engine.gridMinX;
        g.maxX = *g_Engine.gridMaxX;
        g.minZ = *g_Engine.gridMinZ;
        g.maxZ = *g_Engine.gridMaxZ;
        return g;
    }

    void ResetState(const wchar_t* reason)
    {
        if (!g_Blockers.empty() && g_Trace)
            Log(L"[PATHBLOCK] reset (%ls): %zu blockers, %d flagged\n", reason, g_Blockers.size(), g_FlaggedCount);
        g_Blockers.clear();
        g_Odfs.clear(); // a new mission can mount a different addon with the same ODF names
        g_FlaggedCount = 0;
        g_SummaryLines = 0;
    }

    // A freed and reallocated grid (new mission, reload) invalidates the
    // registry. The lifecycle seam calls ResetPathBlockState as well; this
    // covers paths that reallocate without leaving the simulation.
    void SyncGrid(uint8_t* grid)
    {
        const int dims[4] = {*g_Engine.gridMinX, *g_Engine.gridMaxX, *g_Engine.gridMinZ, *g_Engine.gridMaxZ};
        if (grid != g_SeenGrid || std::memcmp(dims, g_SeenDims, sizeof(dims)) != 0)
        {
            ResetState(L"grid changed");
            g_SeenGrid = grid;
            std::memcpy(g_SeenDims, dims, sizeof(dims));
        }
    }

    OdfEntry* LookupOdf(void* object, std::string& odfName)
    {
        char raw[16] = {};
        if (!TryGetCraftOdfName(object, raw, sizeof(raw)))
            return nullptr;
        odfName = raw;
        for (char& c : odfName)
            c = PB::Detail::Lower(c);
        auto found = g_Odfs.find(odfName);
        if (found != g_Odfs.end())
            return found->second.get();

        auto entry = std::make_unique<OdfEntry>();
        std::vector<uint8_t> bytes;
        if (ReadGameFile(odfName + ".odf", bytes))
            entry->flagged = PB::ParseOdfSpec(std::string(bytes.begin(), bytes.end()), entry->spec);
        if (entry->flagged && entry->spec.mode == PB::Mode::Faces)
        {
            const std::string base = entry->spec.baseName.empty() ? odfName : entry->spec.baseName;
            std::vector<PB::SdfGeo> geos;
            auto model = std::make_unique<PB::Model>();
            std::string error;
            if (!ReadGameFile(base + ".sdf", bytes) || !PB::ParseSdfGeos(bytes.data(), bytes.size(), geos))
            {
                error = base + ".sdf unreadable (VDF objects are not supported)";
            }
            else if (PB::BuildModel(
                         geos, [](const std::string& file, std::vector<uint8_t>& out) { return ReadGameFile(file, out); },
                         *model, &error))
            {
                Log(L"[PATHBLOCK] %hs: faces model %d geo(s) (%hs), %zu triangles, heights %.2f/%.2f\n",
                    odfName.c_str(), model->geoCount, model->lodNote.c_str(), model->tris.size(),
                    entry->spec.height1, entry->spec.height2);
                entry->model = std::move(model);
            }
            if (!entry->model)
            {
                Log(L"[PATHBLOCK] %hs: pathBlock = \"faces\" but %hs; using the stock box\n", odfName.c_str(),
                    error.c_str());
                entry->spec.mode = PB::Mode::Box;
            }
        }
        OdfEntry* result = entry.get();
        g_Odfs.emplace(odfName, std::move(entry));
        return result;
    }

    bool BlockerCovers(const Blocker& b, int index, int gx, int gz, float size)
    {
        switch (b.mode)
        {
        case PB::Mode::Box:
            return PB::QuadCoversCell(b.quad, gx, gz, size);
        case PB::Mode::Faces:
            return std::binary_search(b.solid.begin(), b.solid.end(), index);
        default:
            return false;
        }
    }

    std::vector<const Blocker*> BlockersNear(float x0, float z0, float x1, float z1, float pad, const void* exclude)
    {
        std::vector<const Blocker*> out;
        for (const auto& [obj, b] : g_Blockers)
        {
            if (obj == exclude || b.mode == PB::Mode::None)
                continue;
            if (b.x1 + pad < x0 || b.x0 - pad > x1 || b.z1 + pad < z0 || b.z0 - pad > z1)
                continue;
            out.push_back(&b);
        }
        return out;
    }

    // Final state of one cell: building bits present iff `want`. A cell
    // without building bits is never touched. Clearing a cell the stock call
    // just blocked restores its byte from before that call, so terrain bits
    // (including the cliff value 3, which the 0xB OR hides) come back exactly;
    // a cell that was already blocked before (a second pass, an EXU pass) goes
    // through the engine's BuildingUnblock, which re-derives steep/slope from
    // terrain the way stock deletion does.
    std::vector<uint8_t> g_PreCall;

    void ApplyCell(uint8_t* grid, int index, int gx, int gz, bool want, int& changed)
    {
        const uint8_t v = grid[index];
        const bool has = (v & kBuildingBits) == kBuildingBits;
        if (want && !has)
        {
            grid[index] = static_cast<uint8_t>(v | kBuildingBits);
            ++changed;
        }
        else if (!want && has)
        {
            const bool snapshot = index >= 0 && static_cast<size_t>(index) < g_PreCall.size();
            if (snapshot && (g_PreCall[index] & kBuildingBits) != kBuildingBits)
                grid[index] = g_PreCall[index];
            else
                g_Engine.buildingUnblock(index, gx, gz);
            ++changed;
        }
    }

    void DumpGrid(const PB::GridDesc& g, const uint8_t* grid, const Blocker& b, const std::vector<PB::FootprintCell>& cells)
    {
        int ix0, iz0, ix1, iz1;
        PB::CellRange(g, b.x0, b.z0, b.x1, b.z1, ix0, iz0, ix1, iz1);
        ix0 = std::max(0, ix0 - 2);
        iz0 = std::max(0, iz0 - 2);
        ix1 = std::min(g.Width() - 1, ix1 + 2);
        iz1 = std::min(g.Depth() - 1, iz1 + 2);
        Log(L"[PATHBLOCK]   grid x %d..%d, z %d..%d (north up): '#' building, 'o' own box cell open, "
            L"'.' open\n",
            ix0 + g.minX, ix1 + g.minX, iz0 + g.minZ, iz1 + g.minZ);
        for (int iz = iz1; iz >= iz0; --iz)
        {
            std::string row;
            for (int ix = ix0; ix <= ix1; ++ix)
            {
                const int index = ix + g.Width() * iz;
                const bool blocked = (grid[index] & kBuildingBits) == kBuildingBits;
                bool own = false;
                for (const auto& c : cells)
                    if (c.index == index)
                        own = true;
                row.push_back(blocked ? '#' : (own ? 'o' : '.'));
            }
            Log(L"[PATHBLOCK]   %hs\n", row.c_str());
        }
    }

    void HandleAdd(void* object, uint8_t* grid)
    {
        // Flagged objects only: keep the grid bytes from before the stock box
        // so ApplyCell can undo it exactly (see there).
        std::string odfName;
        OdfEntry* odf = LookupOdf(object, odfName);
        g_PreCall.clear();
        if (odf && odf->spec.mode != PB::Mode::Box)
        {
            const PB::GridDesc pre = ReadGrid();
            if (pre.Width() > 0 && pre.Depth() > 0)
            {
                g_PreCall.resize(static_cast<size_t>(pre.Width()) * static_cast<size_t>(pre.Depth()));
                if (!SafeCopy(grid, g_PreCall.data(), g_PreCall.size()))
                    g_PreCall.clear();
            }
        }

        uint32_t sentinel = kQuadSentinel;
        std::memcpy(&g_Engine.blockVerts[0], &sentinel, sizeof(sentinel));
        if (!SafeCallOriginal(object, 1))
            return;

        uint32_t first = 0;
        std::memcpy(&first, &g_Engine.blockVerts[0], sizeof(first));
        if (first == kQuadSentinel)
            return; // perimeter branch, degenerate bbox: nothing of ours to own

        Blocker b;
        for (int i = 0; i < 4; ++i)
        {
            b.quad.x[i] = g_Engine.blockVerts[2 * i];
            b.quad.z[i] = g_Engine.blockVerts[2 * i + 1];
        }
        PB::QuadBounds(b.quad, b.x0, b.z0, b.x1, b.z1);

        b.odf = odfName;
        b.mode = odf ? odf->spec.mode : PB::Mode::Box;

        auto previous = g_Blockers.find(object);
        if (previous != g_Blockers.end())
        {
            if (previous->second.mode != PB::Mode::Box)
                --g_FlaggedCount;
            g_Blockers.erase(previous);
        }

        PB::Placement placement;
        if (b.mode != PB::Mode::Box && !SafeReadPlacement(object, placement))
        {
            Log(L"[PATHBLOCK] %hs: object matrix unreadable; using the stock box\n", b.odf.c_str());
            b.mode = PB::Mode::Box;
        }
        if (b.mode == PB::Mode::Box)
        {
            g_Blockers.emplace(object, std::move(b));
            return;
        }

        const PB::GridDesc g = ReadGrid();
        PB::SolidSampler sampler;
        if (b.mode == PB::Mode::Faces)
        {
            sampler = [odf](double lx, double lz) {
                const auto qx = static_cast<int32_t>(std::lround(lx * 100.0));
                const auto qz = static_cast<int32_t>(std::lround(lz * 100.0));
                const uint64_t key = (static_cast<uint64_t>(static_cast<uint32_t>(qx)) << 32) |
                                     static_cast<uint32_t>(qz);
                auto hit = odf->memo.find(key);
                if (hit != odf->memo.end())
                    return hit->second;
                const bool solid = PB::IsSolidAt(*odf->model, lx, lz, odf->spec.height1, odf->spec.height2);
                odf->memo.emplace(key, solid);
                return solid;
            };
        }
        const auto cells = PB::ComputeFootprint(g, placement, b.quad, sampler);
        for (const auto& c : cells)
            if (c.solid)
                b.solid.push_back(c.index);
        std::sort(b.solid.begin(), b.solid.end());

        const auto others = BlockersNear(b.x0, b.z0, b.x1, b.z1, g.size, object);
        int changed = 0;
        for (const auto& c : cells)
        {
            bool want = c.solid;
            for (size_t i = 0; !want && i < others.size(); ++i)
                want = BlockerCovers(*others[i], c.index, c.gx, c.gz, g.size);
            ApplyCell(grid, c.index, c.gx, c.gz, want, changed);
        }
        g_Engine.invalidateStrips(b.x0, b.z0, b.x1, b.z1);

        if (g_Trace || g_SummaryLines < kSummaryLineBudget)
        {
            ++g_SummaryLines;
            Log(L"[PATHBLOCK] odf=%hs mode=%hs cells=%zu blocked=%zu changed=%d origin=(%.1f, %.1f) obj=%p\n",
                b.odf.c_str(), PB::ModeName(b.mode), cells.size(), b.solid.size(), changed, placement.positX,
                placement.positZ, object);
        }
        if (g_Trace)
            DumpGrid(g, grid, b, cells);

        ++g_FlaggedCount;
        g_Blockers.emplace(object, std::move(b));
    }

    void HandleRemove(void* object, uint8_t* grid)
    {
        g_PreCall.clear(); // removal only re-adds; never restore a stale snapshot
        const bool ok = SafeCallOriginal(object, 0);
        auto found = g_Blockers.find(object);
        if (!ok || found == g_Blockers.end())
            return;
        const Blocker removed = std::move(found->second);
        g_Blockers.erase(found);
        if (removed.mode != PB::Mode::Box)
            --g_FlaggedCount;
        if (g_FlaggedCount <= 0 && removed.mode == PB::Mode::Box)
            return; // nothing flagged anywhere: the stock result stands

        // Stock BuildingUnblock cleared every cell of the stored AABB,
        // including cells other blockers own. Re-add them.
        const PB::GridDesc g = ReadGrid();
        int ix0, iz0, ix1, iz1;
        PB::CellRange(g, removed.x0, removed.z0, removed.x1, removed.z1, ix0, iz0, ix1, iz1);
        const auto others = BlockersNear(removed.x0, removed.z0, removed.x1, removed.z1, g.size, object);
        int changed = 0;
        for (int iz = iz0; iz <= iz1; ++iz)
        {
            for (int ix = ix0; ix <= ix1; ++ix)
            {
                const int index = ix + g.Width() * iz, gx = ix + g.minX, gz = iz + g.minZ;
                bool want = false;
                for (size_t i = 0; !want && i < others.size(); ++i)
                    want = BlockerCovers(*others[i], index, gx, gz, g.size);
                if (want)
                    ApplyCell(grid, index, gx, gz, true, changed);
            }
        }
        if (changed)
            g_Engine.invalidateStrips(removed.x0, removed.z0, removed.x1, removed.z1);
        if (g_Trace)
            Log(L"[PATHBLOCK] removed odf=%hs mode=%hs obj=%p; re-added %d neighbour cell(s)\n",
                removed.odf.c_str(), PB::ModeName(removed.mode), object, changed);
    }

    void __cdecl BlockCellsDetour(void* object, int add)
    {
        uint8_t* grid = (g_Ready && object) ? *g_Engine.cellType : nullptr;
        if (!grid)
        {
            g_Engine.original(object, add);
            return;
        }
        SyncGrid(grid);
        if (static_cast<uint8_t>(add) != 0)
            HandleAdd(object, grid);
        else
            HandleRemove(object, grid);
    }

    template <typename T>
    bool ResolveAs(uint32_t address, const char* name, T& out)
    {
        out = reinterpret_cast<T>(static_cast<uintptr_t>(address));
        if (!address)
            Log(L"[PATHBLOCK] resolve %hs failed\n", name);
        return address != 0;
    }
}

    bool InstallPathBlockHook(uint32_t site)
    {
        if (g_Ready)
            return true;
        g_Trace = EnvFlagEnabled("OPENSHIM_TRACE_PATH_BLOCK");

        uint8_t prologue[kRelocated] = {};
        if (!site || !HookEngine::ReadMemory(site, prologue, kRelocated) ||
            std::memcmp(prologue, kBlockCellsPrologue, kRelocated) != 0)
        {
            Log(L"[PATHBLOCK] BlockCells prologue mismatch at 0x%08X; leaving stock\n", site);
            return false;
        }

        Engine e;
        bool ok = true;
        ok &= ResolveAs(HookEngine::ResolveNamedAddress("PathBlock::CellType"), "PathBlock::CellType", e.cellType);
        ok &= ResolveAs(HookEngine::ResolveNamedAddress("PathBlock::GridSize"), "PathBlock::GridSize", e.gridSize);
        ok &= ResolveAs(HookEngine::ResolveNamedAddress("PathBlock::GridMinX"), "PathBlock::GridMinX", e.gridMinX);
        ok &= ResolveAs(HookEngine::ResolveNamedAddress("PathBlock::GridMaxX"), "PathBlock::GridMaxX", e.gridMaxX);
        ok &= ResolveAs(HookEngine::ResolveNamedAddress("PathBlock::GridMinZ"), "PathBlock::GridMinZ", e.gridMinZ);
        ok &= ResolveAs(HookEngine::ResolveNamedAddress("PathBlock::GridMaxZ"), "PathBlock::GridMaxZ", e.gridMaxZ);
        ok &= ResolveAs(HookEngine::ResolveNamedAddress("PathBlock::BlockVertArray"), "PathBlock::BlockVertArray", e.blockVerts);
        ok &= ResolveAs(HookEngine::ResolveNamedAddress("PathBlock::BuildingUnblock"), "PathBlock::BuildingUnblock", e.buildingUnblock);
        ok &= ResolveAs(HookEngine::ResolveNamedAddress("PathBlock::InvalidateStrips"), "PathBlock::InvalidateStrips", e.invalidateStrips);
        ok &= ResolveAs(HookEngine::ResolveNamedAddress("PathBlock::ReadFile"), "PathBlock::ReadFile", e.readFile);
        if (!ok)
        {
            Log(L"[PATHBLOCK] engine addresses incomplete; leaving stock\n");
            return false;
        }

        auto* tramp =
            static_cast<uint8_t*>(VirtualAlloc(nullptr, 32, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
        if (!tramp)
            return false;
        std::memcpy(tramp, prologue, kRelocated);
        tramp[kRelocated] = 0xE9;
        const int32_t rel = static_cast<int32_t>(site + kRelocated) -
                            static_cast<int32_t>(reinterpret_cast<uintptr_t>(tramp) + kRelocated + 5);
        std::memcpy(tramp + kRelocated + 1, &rel, sizeof(rel));
        FlushInstructionCache(GetCurrentProcess(), tramp, kRelocated + 5);
        e.original = reinterpret_cast<FnBlockCells>(tramp);

        g_Engine = e;
        g_Ready = true;
        Log(L"[PATHBLOCK] BlockCells detour ready site=0x%08X grid=%p size=%p trace=%u\n", site, e.cellType,
            e.gridSize, g_Trace ? 1u : 0u);
        return true;
    }

    void* GetPathBlockCellsDetourAddress()
    {
        return reinterpret_cast<void*>(&BlockCellsDetour);
    }

    void ResetPathBlockState(const wchar_t* reason)
    {
        if (g_Ready)
            ResetState(reason);
    }
}
}
