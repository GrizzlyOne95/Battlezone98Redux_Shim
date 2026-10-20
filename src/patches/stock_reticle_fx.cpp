#include "stock_reticle_fx.h"
#include "hook_engine.h"
#include "ogre_runtime.h"
#include "patcher.h"
#include "render_profile_runtime.h"
#include "shim_log.h"

#include <Windows.h>
#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <string>

namespace BZROpenShim::HudFeedback::StockReticleFx
{
    namespace
    {
        struct Shared { void* rep = nullptr; void* info = nullptr; };
        static_assert(sizeof(Shared) == 8, "released Ogre SharedPtr ABI");
        using GetIndexed = void*(__thiscall*)(void*, unsigned short);
        using GetName = const std::string&(__thiscall*)(const void*);
        using SetProgram = void(__thiscall*)(void*, const std::string&, bool);
        using GetParams = Shared*(__thiscall*)(const void*, Shared*);
        using FindConstant = const uint32_t*(__thiscall*)(const void*, const std::string&, bool);
        using WriteConstants = void(__thiscall*)(void*, size_t, const float*, size_t);
        using Clone = Shared*(__thiscall*)(const void*, Shared*, const std::string&, bool, const std::string&);
        using Load = void(__thiscall*)(void*, bool);
        using SizedSprite = void(__cdecl*)(void*, const char*, int, int, int, int, int, uint32_t, float);

        constexpr char kProgram[] = "OpenShim_ReticleFx_fragmentHLSL4";
        enum Constant { kCell, kShape, kTint, kRingScale, kRingAlpha, kRingColor, kConstantCount };
        constexpr const char* kConstants[kConstantCount] = {
            "fxCell", "fxShape", "fxTint", "fxRingScale", "fxRingAlpha", "fxRingColor"};

        struct Api
        {
            GetIndexed technique = nullptr, pass = nullptr;
            GetName vertex = nullptr, fragment = nullptr;
            SetProgram setProgram = nullptr;
            GetParams getParams = nullptr;
            FindConstant find = nullptr;
            WriteConstants write = nullptr;
            Clone clone = nullptr;
            Load load = nullptr;
        } g_api;

        enum class State { Unbound, Ready, Unavailable };
        State g_state = State::Unbound;
        uint32_t g_sized = 0, g_table = 0, g_count = 0;

        // One clone per source atlas material. Each clone keeps its native
        // references until process teardown, as Ogre itself would; rebuilds
        // after a mission reset are bounded by the slot recycling below.
        struct Entry
        {
            void* source = nullptr;
            Shared clone, params;
            std::string name;
            std::array<uint32_t, kConstantCount> index{};
        };
        std::array<Entry, 8> g_entries;
        size_t g_used = 0;
        uint32_t g_serial = 0;
        constexpr uint32_t kMaxClones = 64;
        std::atomic<bool> g_invalidate{false};

        template<class T> T Export(const char* name) { return reinterpret_cast<T>(OgreRuntime::ResolveExport(name)); }

        bool Bind()
        {
            if (g_state != State::Unbound) return g_state == State::Ready;
            if (!OgreRuntime::IsLoaded()) return false;
            g_state = State::Unavailable;
            // ps_4_0 HLSL: Direct3D 11 only.
            if (RenderProfiles::IdentifyActiveRenderSystem() != 1)
            {
                Log(L"[HUDFEEDBACK] Stock reticle shader needs Direct3D 11; using sprite ripple\n");
                return false;
            }
            const HookEngine::EngineRow rows[] = {
                {"HudPaletteSizedSprite", &g_sized}, {"HudSpriteRectTable", &g_table}, {"HudSpriteNameCount", &g_count},
            };
            if (!HookEngine::BindEngineRows("Stock reticle shader", rows)) return false;
            g_api.technique = Export<GetIndexed>("?getTechnique@Material@Ogre@@QAEPAVTechnique@2@G@Z");
            g_api.pass = Export<GetIndexed>("?getPass@Technique@Ogre@@QAEPAVPass@2@G@Z");
            g_api.vertex = Export<GetName>("?getVertexProgramName@Pass@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
            g_api.fragment = Export<GetName>("?getFragmentProgramName@Pass@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
            g_api.setProgram = Export<SetProgram>("?setFragmentProgram@Pass@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
            g_api.getParams = Export<GetParams>("?getFragmentProgramParameters@Pass@Ogre@@QBE?AV?$SharedPtr@VGpuProgramParameters@Ogre@@@2@XZ");
            g_api.find = Export<FindConstant>("?_findNamedConstantDefinition@GpuProgramParameters@Ogre@@QBEPBUGpuConstantDefinition@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
            g_api.write = Export<WriteConstants>("?_writeRawConstants@GpuProgramParameters@Ogre@@QAEXIPBMI@Z");
            g_api.clone = Export<Clone>("?clone@Material@Ogre@@QBE?AV?$SharedPtr@VMaterial@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N0@Z");
            g_api.load = Export<Load>("?load@Resource@Ogre@@UAEX_N@Z");
            if (!g_api.technique || !g_api.pass || !g_api.vertex || !g_api.fragment || !g_api.setProgram ||
                !g_api.getParams || !g_api.find || !g_api.write || !g_api.clone || !g_api.load)
            {
                Log(L"[HUDFEEDBACK] Stock reticle shader: Ogre API unavailable; using sprite ripple\n");
                return false;
            }
            g_state = State::Ready;
            return true;
        }

        // Sprite records start 8 bytes before the rect table with the
        // record's native MaterialPtr; the stock submitter binds that pointer.
        void* SourceMaterial(int sprite) noexcept
        {
            __try
            {
                if (sprite < 0 || sprite >= *reinterpret_cast<const int*>(g_count)) return nullptr;
                return *reinterpret_cast<void* const*>(g_table - 8 + static_cast<uint32_t>(sprite) * 0x24);
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
        }

        bool ReadCell(int sprite, int& w, int& h, float (&uv)[4]) noexcept
        {
            __try
            {
                const auto record = g_table + static_cast<uint32_t>(sprite) * 0x24;
                w = reinterpret_cast<const int16_t*>(record)[2];
                h = reinterpret_cast<const int16_t*>(record)[3];
                for (int i = 0; i < 4; ++i) uv[i] = reinterpret_cast<const float*>(record + 8)[i];
                for (const float v : uv) if (!std::isfinite(v) || v < 0 || v > 1) return false;
                return w > 0 && h > 0 && w <= 512 && h <= 512 && uv[0] != uv[2] && uv[1] != uv[3];
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        bool Build(Entry& slot, void* source)
        {
            try
            {
                Entry e;
                e.source = source;
                e.name = "OpenShim/ReticleFx/" + std::to_string(++g_serial);
                // Same group as the stock atlas material, so the clone resolves
                // the atlas texture exactly as the original does.
                g_api.clone(source, &e.clone, e.name, false, std::string());
                if (!e.clone.rep) return false;
                void* technique = g_api.technique(e.clone.rep, 0);
                void* pass = technique ? g_api.pass(technique, 0) : nullptr;
                // Only the stock HUD sprite pass: its vertex stage feeds the
                // COLOR0/TEXCOORD0 signature the reticle shader expects.
                if (!pass || g_api.vertex(pass) != "UI_vertex" || g_api.fragment(pass) != "UI_fragment") return false;
                g_api.setProgram(pass, kProgram, true);
                g_api.load(e.clone.rep, false);
                g_api.getParams(pass, &e.params);
                if (!e.params.rep) return false;
                for (int i = 0; i < kConstantCount; ++i)
                {
                    // Released GpuConstantDefinition: type, physical index,
                    // logical index, element size, array size. float4 only.
                    const uint32_t* def = g_api.find(e.params.rep, kConstants[i], false);
                    if (!def || def[3] != 4 || def[4] != 1 || def[1] > 1024) return false;
                    e.index[i] = def[1];
                }
                slot = std::move(e);
                return true;
            }
            catch (...) { return false; }
        }

        bool BuildGuarded(Entry& slot, void* source) noexcept
        {
            __try { return Build(slot, source); }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        bool Submit(const Entry& e, void* viewport, const Frame& f, int w, int h,
                    const float (&values)[kConstantCount][4]) noexcept
        {
            __try
            {
                for (int i = 0; i < kConstantCount; ++i) g_api.write(e.params.rep, e.index[i], values[i], 4);
                reinterpret_cast<SizedSprite>(g_sized)(viewport, e.name.c_str(), f.sprite, f.x, f.y, w, h, f.flags, 0.0f);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        void Rgb(uint32_t rgb, float* out)
        {
            out[0] = static_cast<float>((rgb >> 16) & 0xFF) / 255.0f;
            out[1] = static_cast<float>((rgb >> 8) & 0xFF) / 255.0f;
            out[2] = static_cast<float>(rgb & 0xFF) / 255.0f;
        }
    }

    bool Draw(void* viewport, const Frame& f) noexcept
    {
        if (g_invalidate.exchange(false)) g_used = 0;
        if (!Bind()) return false;
        // The quad grows about the aim point: require stock centering and
        // no horizontal mirroring, which would swap the cell's U bounds.
        if ((f.flags & 0x50000u) != 0x50000u || (f.flags & 0x100000u) != 0) return false;
        void* source = SourceMaterial(f.sprite);
        int w = 0, h = 0;
        float uv[4] = {};
        if (!source || !ReadCell(f.sprite, w, h, uv)) return false;

        const Entry* entry = nullptr;
        for (size_t i = 0; i < g_used; ++i) if (g_entries[i].source == source) entry = &g_entries[i];
        if (!entry)
        {
            if (g_serial >= kMaxClones) return false;
            if (g_used == g_entries.size()) g_used = 0;
            Entry& slot = g_entries[g_used];
            if (!BuildGuarded(slot, source))
            {
                g_state = State::Unavailable;
                Log(L"[HUDFEEDBACK] Stock reticle shader material unavailable; using sprite ripple\n");
                return false;
            }
            ++g_used;
            entry = &slot;
            Log(L"[HUDFEEDBACK] Stock reticle shader material %hs ready for sprite %d\n", slot.name.c_str(), f.sprite);
        }

        const GhostPlan& ghost = f.ghost;
        float reach = std::max(1.0f, ghost.baseScale);
        for (size_t i = 0; i < ghost.count; ++i) reach = std::max(reach, ghost.rings[i].scale);
        const float base = f.scale > 0 && std::isfinite(f.scale) ? f.scale : 1.0f;
        const float qw = static_cast<float>(w) * f.uiScaleX * base * reach;
        const float qh = static_cast<float>(h) * f.uiScaleY * base * reach;
        if (!std::isfinite(qw) || !std::isfinite(qh) || qw < 1 || qh < 1 || qw > 4096 || qh > 4096) return false;

        float values[kConstantCount][4] = {
            {uv[0], uv[1], uv[2], uv[3]},
            {reach, std::max(ghost.baseScale, 0.1f), std::clamp(f.flash, 0.0f, 1.0f), 0},
            {1, 1, 1, std::clamp(f.tintAmount, 0.0f, 1.0f)},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {1, 1, 1, 1},
        };
        Rgb(f.tintRgb, values[kTint]);
        Rgb(f.ringRgb, values[kRingColor]);
        for (size_t i = 0; i < ghost.count && i < 4; ++i)
        {
            values[kRingScale][i] = std::max(ghost.rings[i].scale, 0.1f);
            values[kRingAlpha][i] = static_cast<float>(ghost.rings[i].argb >> 24) / 255.0f;
        }
        return Submit(*entry, viewport, f, static_cast<int>(std::lround(qw)), static_cast<int>(std::lround(qh)), values);
    }

    void Invalidate() noexcept { g_invalidate.store(true); }
}
