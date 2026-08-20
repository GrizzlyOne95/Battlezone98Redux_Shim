#include "ogre_enhanced_light_selection.h"

#include "bzr_options_ui.h"
#include "enhanced_light_selection.h"
#include "shim_log.h"

#include <Windows.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
#include <mutex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        using namespace EnhancedLights;

        // Both supported Redux storefronts ship this byte-identical OgreMain:
        // SHA-256 E5E693960B95AD0D60733A3B688464A6C6CBA234E86950698F9C2BEA4ACFEB45.
        constexpr DWORD kExpectedOgreTimestamp = 0x5866BF6A;
        constexpr DWORD kExpectedOgreImageSize = 0x00A65000;
        constexpr uintptr_t kPopulateLightListBodyRva = 0x003B3930;
        constexpr std::size_t kPopulateHookLength = 5;
        constexpr std::size_t kMaxCandidateCount = 4096;
        constexpr std::size_t kMaxHistoryEntries = 4096;
        constexpr std::size_t kMaxTraceRecords = 64;
        constexpr std::uint64_t kTraceInterval = 120;

        struct OgreVector3
        {
            float x;
            float y;
            float z;
        };

        struct OgreColourValue
        {
            float r;
            float g;
            float b;
            float a;
        };

        // Verified in the shipped MSVC120 OgreMain disassembly at
        // SceneManager::_populateLightList+0x45. HashedVector<Light*> contains
        // the vector triplet at +0/+4/+8, hash at +0x10, dirty byte at +0x14.
        struct RawLightList32
        {
            void** begin;
            void** end;
            void** capacityEnd;
            std::uint32_t vectorPadding;
            std::uint32_t hash;
            std::uint8_t hashDirty;
        };

        static_assert(sizeof(void*) == 4, "Redux Ogre light hook is Win32-only");
        static_assert(offsetof(RawLightList32, hash) == 0x10);
        static_assert(offsetof(RawLightList32, hashDirty) == 0x14);

        using FnPopulateLightList = void(__thiscall*)(
            void*, const OgreVector3&, float, void*, std::uint32_t);
        using FnGetCurrentViewport = void*(__thiscall*)(void*);
        using FnGetMaterialScheme = const std::string&(__thiscall*)(void*);
        using FnGetLightType = int(__thiscall*)(void*);
        using FnGetVector3 = const OgreVector3*(__thiscall*)(void*);
        using FnGetDerivedPosition = const OgreVector3*(__thiscall*)(void*, bool);
        using FnGetColour = const OgreColourValue*(__thiscall*)(void*);
        using FnGetFloat = float(__thiscall*)(void*);
        using FnGetRadian = const float*(__thiscall*)(void*);
        using FnGetName = const std::string&(__thiscall*)(void*);

        struct OgreLightApi
        {
            FnGetCurrentViewport getCurrentViewport = nullptr;
            FnGetMaterialScheme getMaterialScheme = nullptr;
            FnGetLightType getType = nullptr;
            FnGetDerivedPosition getDerivedPosition = nullptr;
            FnGetVector3 getDerivedDirection = nullptr;
            FnGetColour getDiffuse = nullptr;
            FnGetColour getSpecular = nullptr;
            FnGetFloat getPowerScale = nullptr;
            FnGetFloat getRange = nullptr;
            FnGetFloat getConstant = nullptr;
            FnGetFloat getLinear = nullptr;
            FnGetFloat getQuadratic = nullptr;
            FnGetRadian getInnerAngle = nullptr;
            FnGetRadian getOuterAngle = nullptr;
            FnGetFloat getFalloff = nullptr;
            FnGetName getName = nullptr;
        };

        struct SelectionHistory
        {
            std::vector<std::uint64_t> selected;
            Vec3 center = {};
            float radius = 0.0f;
            std::uint64_t lastUse = 0;
            bool initialized = false;
        };

        InlineDetour32 g_PopulateLightListDetour = {};
        FnPopulateLightList g_OriginalPopulateLightList = nullptr;
        OgreLightApi g_Api = {};
        std::mutex g_HistoryMutex;
        std::unordered_map<void*, SelectionHistory> g_History;
        std::atomic<std::uint64_t> g_PopulationCount = 0;
        std::atomic<std::uint64_t> g_CandidateTotal = 0;
        std::atomic<std::size_t> g_MaxCandidates = 0;
        std::atomic<std::size_t> g_TraceRecords = 0;
        bool g_ConfigLoaded = false;
        bool g_SelectionEnabled = true;
        bool g_TraceEnabled = false;
        bool g_InstallAttempted = false;
        bool g_UnsupportedLogged = false;

        template<typename T>
        T Resolve(HMODULE module, const char* name)
        {
            return reinterpret_cast<T>(module ? GetProcAddress(module, name) : nullptr);
        }

        void LoadConfig()
        {
            if (g_ConfigLoaded)
                return;
            g_ConfigLoaded = true;

            bool configured = false;
            if (TryGetUserConfigBool("DX11Enhanced", "EnhancedLightSelectionV2", configured))
                g_SelectionEnabled = configured;
            if (TryGetUserConfigBool("Diagnostics", "EnhancedLightSelectionTrace", configured))
                g_TraceEnabled = configured;

            if (EnvFlagEnabled("OPENSHIM_DISABLE_ENHANCED_LIGHT_SELECTION_V2"))
                g_SelectionEnabled = false;
            if (EnvFlagEnabled("OPENSHIM_ENABLE_ENHANCED_LIGHT_SELECTION_V2"))
                g_SelectionEnabled = true;
            if (EnvFlagEnabled("OPENSHIM_TRACE_ENHANCED_LIGHT_SELECTION"))
                g_TraceEnabled = true;
        }

        bool IsExpectedOgreBuild(HMODULE module)
        {
            if (!module)
                return false;
            __try
            {
                const auto* bytes = reinterpret_cast<const std::uint8_t*>(module);
                const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(bytes);
                if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                    return false;
                const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(bytes + dos->e_lfanew);
                if (nt->Signature != IMAGE_NT_SIGNATURE
                    || nt->FileHeader.TimeDateStamp != kExpectedOgreTimestamp
                    || nt->OptionalHeader.SizeOfImage != kExpectedOgreImageSize)
                {
                    return false;
                }

                // Multi-anchor signature: prologue, verified HashedVector
                // layout writes, and Light::_calcTempSquareDist type dispatch.
                // This rejects a same-sized DLL that happens to share the PE
                // timestamp and first five hook bytes.
                static const std::uint8_t populatePrologue[] =
                    { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };
                static const std::uint8_t listLayoutAnchor[] =
                {
                    0x8B, 0x0B, 0x89, 0x4B, 0x04,
                    0xC7, 0x43, 0x10, 0x00, 0x00, 0x00, 0x00,
                    0xC6, 0x43, 0x14, 0x00
                };
                static const std::uint8_t distanceAnchor[] =
                    { 0x55, 0x8B, 0xEC, 0x56, 0x8B, 0xF1, 0x83, 0xBE, 0xD4, 0x00, 0x00, 0x00, 0x01 };
                return std::memcmp(bytes + kPopulateLightListBodyRva,
                           populatePrologue, sizeof(populatePrologue)) == 0
                    && std::memcmp(bytes + kPopulateLightListBodyRva + 0x45,
                           listLayoutAnchor, sizeof(listLayoutAnchor)) == 0
                    && std::memcmp(bytes + 0x0021BAE0,
                           distanceAnchor, sizeof(distanceAnchor)) == 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool ResolveApi(HMODULE module)
        {
            g_Api.getCurrentViewport = Resolve<FnGetCurrentViewport>(module,
                "?getCurrentViewport@SceneManager@Ogre@@QBEPAVViewport@2@XZ");
            g_Api.getMaterialScheme = Resolve<FnGetMaterialScheme>(module,
                "?getMaterialScheme@Viewport@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
            g_Api.getType = Resolve<FnGetLightType>(module,
                "?getType@Light@Ogre@@QBE?AW4LightTypes@12@XZ");
            g_Api.getDerivedPosition = Resolve<FnGetDerivedPosition>(module,
                "?getDerivedPosition@Light@Ogre@@QBEABVVector3@2@_N@Z");
            g_Api.getDerivedDirection = Resolve<FnGetVector3>(module,
                "?getDerivedDirection@Light@Ogre@@QBEABVVector3@2@XZ");
            g_Api.getDiffuse = Resolve<FnGetColour>(module,
                "?getDiffuseColour@Light@Ogre@@QBEABVColourValue@2@XZ");
            g_Api.getSpecular = Resolve<FnGetColour>(module,
                "?getSpecularColour@Light@Ogre@@QBEABVColourValue@2@XZ");
            g_Api.getPowerScale = Resolve<FnGetFloat>(module,
                "?getPowerScale@Light@Ogre@@QBEMXZ");
            g_Api.getRange = Resolve<FnGetFloat>(module,
                "?getAttenuationRange@Light@Ogre@@QBEMXZ");
            g_Api.getConstant = Resolve<FnGetFloat>(module,
                "?getAttenuationConstant@Light@Ogre@@QBEMXZ");
            g_Api.getLinear = Resolve<FnGetFloat>(module,
                "?getAttenuationLinear@Light@Ogre@@QBEMXZ");
            g_Api.getQuadratic = Resolve<FnGetFloat>(module,
                "?getAttenuationQuadric@Light@Ogre@@QBEMXZ");
            g_Api.getInnerAngle = Resolve<FnGetRadian>(module,
                "?getSpotlightInnerAngle@Light@Ogre@@QBEABVRadian@2@XZ");
            g_Api.getOuterAngle = Resolve<FnGetRadian>(module,
                "?getSpotlightOuterAngle@Light@Ogre@@QBEABVRadian@2@XZ");
            g_Api.getFalloff = Resolve<FnGetFloat>(module,
                "?getSpotlightFalloff@Light@Ogre@@QBEMXZ");
            g_Api.getName = Resolve<FnGetName>(module,
                "?getName@MovableObject@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");

            return g_Api.getCurrentViewport && g_Api.getMaterialScheme
                && g_Api.getType && g_Api.getDerivedPosition && g_Api.getDerivedDirection
                && g_Api.getDiffuse && g_Api.getSpecular && g_Api.getPowerScale
                && g_Api.getRange && g_Api.getConstant && g_Api.getLinear && g_Api.getQuadratic
                && g_Api.getInnerAngle && g_Api.getOuterAngle && g_Api.getFalloff
                && g_Api.getName;
        }

        bool ReadLightList(void* list, void*** outBegin, std::size_t* outCount)
        {
            if (!list || !outBegin || !outCount)
                return false;
            __try
            {
                auto* raw = reinterpret_cast<RawLightList32*>(list);
                if (!raw->begin || !raw->end || raw->end < raw->begin
                    || raw->capacityEnd < raw->end)
                {
                    return false;
                }
                const std::size_t count = static_cast<std::size_t>(raw->end - raw->begin);
                if (count > kMaxCandidateCount)
                    return false;
                *outBegin = raw->begin;
                *outCount = count;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool WriteRankedLightList(void* list, std::span<const RankedCandidate> ranked)
        {
            if (!list)
                return false;
            __try
            {
                auto* raw = reinterpret_cast<RawLightList32*>(list);
                const std::size_t count = static_cast<std::size_t>(raw->end - raw->begin);
                if (count != ranked.size() || count > kMaxCandidateCount)
                    return false;
                for (std::size_t i = 0; i < count; ++i)
                    raw->begin[i] = reinterpret_cast<void*>(ranked[i].light.opaque);
                raw->hashDirty = 1;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool GetEnhancedScheme(void* sceneManager, char* schemeBuffer,
                               std::size_t schemeBufferSize, std::size_t* outBudget)
        {
            if (!sceneManager || !schemeBuffer || schemeBufferSize == 0 || !outBudget
                || !GetModuleHandleA("RenderSystem_Direct3D11.dll"))
            {
                return false;
            }

            __try
            {
                void* viewport = g_Api.getCurrentViewport(sceneManager);
                if (!viewport)
                    return false;
                const std::string& scheme = g_Api.getMaterialScheme(viewport);
                const std::size_t budget = BudgetForEnhancedScheme(scheme);
                if (budget == 0)
                    return false;
                const std::size_t length = std::min(scheme.size(), schemeBufferSize - 1);
                std::memcpy(schemeBuffer, scheme.data(), length);
                schemeBuffer[length] = '\0';
                *outBudget = budget;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool BuildCandidate(void* light, Candidate* out)
        {
            if (!light || !out)
                return false;

            char name[256] = {};
            __try
            {
                const int type = g_Api.getType(light);
                // _populateLightList receives an ordinary world-space object
                // center. Match Ogre::_calcTempSquareDist and request the
                // non-camera-relative light position for the ranking metric.
                const OgreVector3* position = g_Api.getDerivedPosition(light, false);
                const OgreVector3* direction = g_Api.getDerivedDirection(light);
                const OgreColourValue* diffuse = g_Api.getDiffuse(light);
                const OgreColourValue* specular = g_Api.getSpecular(light);
                const float* inner = g_Api.getInnerAngle(light);
                const float* outer = g_Api.getOuterAngle(light);
                const std::string& lightName = g_Api.getName(light);
                if (!position || !direction || !diffuse || !specular || !inner || !outer)
                    return false;

                const std::size_t nameLength = std::min(lightName.size(), sizeof(name) - 1);
                std::memcpy(name, lightName.data(), nameLength);
                name[nameLength] = '\0';

                out->opaque = reinterpret_cast<std::uintptr_t>(light);
                out->type = type == 1 ? LightType::Directional
                    : (type == 2 ? LightType::Spot : LightType::Point);
                out->position = { position->x, position->y, position->z };
                out->direction = { direction->x, direction->y, direction->z };
                out->diffuse = { diffuse->r, diffuse->g, diffuse->b };
                out->specular = { specular->r, specular->g, specular->b };
                out->powerScale = g_Api.getPowerScale(light);
                out->range = g_Api.getRange(light);
                out->attenuationConstant = g_Api.getConstant(light);
                out->attenuationLinear = g_Api.getLinear(light);
                out->attenuationQuadratic = g_Api.getQuadratic(light);
                out->spotInnerCos = std::cos(*inner * 0.5f);
                out->spotOuterCos = std::cos(*outer * 0.5f);
                out->spotFalloff = g_Api.getFalloff(light);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }

            out->stableId = StableLightId(name);
            if (name[0] == '\0')
            {
                // Empty names are not expected from SceneManager-created
                // lights. Pointer fallback is deterministic for the current
                // process and prevents all unnamed lights collapsing to one ID.
                out->stableId ^= static_cast<std::uint64_t>(out->opaque);
            }
            return true;
        }

        float CenterDistance(const Vec3& a, const Vec3& b)
        {
            const float x = a.x - b.x;
            const float y = a.y - b.y;
            const float z = a.z - b.z;
            return std::sqrt(x * x + y * y + z * z);
        }

        std::vector<std::uint64_t> GetPreviousSelection(
            void* list, const Vec3& center, float radius, std::uint64_t useCounter)
        {
            std::scoped_lock lock(g_HistoryMutex);
            const auto found = g_History.find(list);
            if (found == g_History.end() || !found->second.initialized)
                return {};

            SelectionHistory& history = found->second;
            const float resetDistance = std::max(100.0f, std::max(radius, history.radius) * 8.0f);
            const float minRadius = std::max(std::min(radius, history.radius), 0.01f);
            const float maxRadius = std::max(radius, history.radius);
            if (CenterDistance(center, history.center) > resetDistance
                || maxRadius / minRadius > 4.0f)
            {
                history.selected.clear();
                history.initialized = false;
                return {};
            }
            history.lastUse = useCounter;
            return history.selected;
        }

        void StoreSelection(void* list, const Vec3& center, float radius,
                            std::span<const RankedCandidate> ranked,
                            std::size_t budget, std::uint64_t useCounter)
        {
            std::scoped_lock lock(g_HistoryMutex);
            if (!g_History.contains(list) && g_History.size() >= kMaxHistoryEntries)
            {
                const auto oldest = std::min_element(g_History.begin(), g_History.end(),
                    [](const auto& a, const auto& b)
                    {
                        return a.second.lastUse < b.second.lastUse;
                    });
                if (oldest != g_History.end())
                    g_History.erase(oldest);
            }

            SelectionHistory& history = g_History[list];
            history.selected.clear();
            const std::size_t selected = std::min(budget, ranked.size());
            history.selected.reserve(selected);
            for (std::size_t i = 0; i < selected; ++i)
                history.selected.push_back(ranked[i].light.stableId);
            history.center = center;
            history.radius = radius;
            history.lastUse = useCounter;
            history.initialized = true;
        }

        void UpdateMaxCandidates(std::size_t count)
        {
            std::size_t observed = g_MaxCandidates.load(std::memory_order_relaxed);
            while (observed < count
                && !g_MaxCandidates.compare_exchange_weak(
                    observed, count, std::memory_order_relaxed))
            {
            }
        }

        void TraceSelection(const char* scheme,
                            std::span<void* const> stockOrder,
                            std::span<const RankedCandidate> ranked,
                            std::span<const std::uint64_t> previous,
                            std::size_t budget,
                            std::uint64_t populationIndex)
        {
            if (!g_TraceEnabled || g_TraceRecords.load(std::memory_order_relaxed) >= kMaxTraceRecords)
                return;

            const SelectionStats stats = MeasureSelection(ranked, previous, budget);
            std::unordered_set<std::uintptr_t> proposed;
            for (std::size_t i = 0; i < stats.selected; ++i)
                proposed.insert(ranked[i].light.opaque);

            std::size_t changedFromStock = 0;
            for (std::size_t i = 0; i < std::min(budget, stockOrder.size()); ++i)
            {
                if (!proposed.contains(reinterpret_cast<std::uintptr_t>(stockOrder[i])))
                    ++changedFromStock;
            }

            if (populationIndex % kTraceInterval != 0
                && stats.candidates <= budget
                && stats.replacements < 3)
            {
                return;
            }

            const std::size_t record = g_TraceRecords.fetch_add(1, std::memory_order_relaxed);
            if (record >= kMaxTraceRecords)
                return;

            const double average = populationIndex == 0 ? 0.0
                : static_cast<double>(g_CandidateTotal.load(std::memory_order_relaxed))
                    / static_cast<double>(populationIndex);
            LogShimA(LogLevel::Info, "LIGHTSEL",
                "scheme=%s candidates=%zu selected=%zu cutoff=%.6f replacements=%zu changedFromStock=%zu max=%zu avg=%.2f mode=%s record=%zu/%zu",
                scheme, stats.candidates, stats.selected,
                static_cast<double>(stats.cutoffInfluence), stats.replacements,
                changedFromStock, g_MaxCandidates.load(std::memory_order_relaxed),
                average, g_SelectionEnabled ? "v2" : "observe", record + 1, kMaxTraceRecords);

            const std::size_t detailCount = std::min<std::size_t>(4, stats.selected);
            for (std::size_t i = 0; i < detailCount; ++i)
            {
                const RankedCandidate& entry = ranked[i];
                const char* type = entry.light.type == LightType::Directional ? "directional"
                    : (entry.light.type == LightType::Spot ? "spot" : "point");
                LogShimA(LogLevel::Info, "LIGHTSEL",
                    "  rank=%zu type=%s id=%016llX influence=%.6f effective=%.6f distance=%.2f retained=%s",
                    i, type, static_cast<unsigned long long>(entry.light.stableId),
                    static_cast<double>(entry.rawInfluence),
                    static_cast<double>(entry.effectiveInfluence),
                    static_cast<double>(entry.surfaceDistance), entry.retained ? "yes" : "no");
            }
        }

        void __fastcall PopulateLightListHook(
            void* sceneManager, void*, const OgreVector3* position,
            float radius, void* destination, std::uint32_t lightMask)
        {
            if (!g_OriginalPopulateLightList || !position)
                return;

            g_OriginalPopulateLightList(sceneManager, *position, radius, destination, lightMask);

            char scheme[64] = {};
            std::size_t budget = 0;
            if (!GetEnhancedScheme(sceneManager, scheme, sizeof(scheme), &budget))
                return;

            void** listBegin = nullptr;
            std::size_t candidateCount = 0;
            if (!ReadLightList(destination, &listBegin, &candidateCount) || candidateCount == 0)
                return;

            std::vector<void*> stockOrder(listBegin, listBegin + candidateCount);
            std::vector<Candidate> candidates;
            candidates.reserve(candidateCount);
            for (void* light : stockOrder)
            {
                Candidate candidate = {};
                if (!BuildCandidate(light, &candidate))
                    return; // Fail closed: preserve Ogre's completed stock order.
                candidates.push_back(candidate);
            }

            const Vec3 center = { position->x, position->y, position->z };
            const std::uint64_t populationIndex =
                g_PopulationCount.fetch_add(1, std::memory_order_relaxed) + 1;
            g_CandidateTotal.fetch_add(candidateCount, std::memory_order_relaxed);
            UpdateMaxCandidates(candidateCount);

            const std::vector<std::uint64_t> previous =
                GetPreviousSelection(destination, center, radius, populationIndex);
            const RankConfig config = { budget, kDefaultRetentionBonus };
            const std::vector<RankedCandidate> ranked = RankCandidates(
                candidates, center, radius, previous, config);

            TraceSelection(scheme, stockOrder, ranked, previous, budget, populationIndex);

            if (g_SelectionEnabled && !WriteRankedLightList(destination, ranked))
            {
                LogShimA(LogLevel::Warn, "LIGHTSEL",
                    "failed to rewrite verified Ogre light list; stock order retained");
                return;
            }
            StoreSelection(destination, center, radius, ranked, budget, populationIndex);
        }
    }

    void InstallEnhancedLightSelectionIfPossible()
    {
        if (g_PopulateLightListDetour.trampoline || g_InstallAttempted)
            return;

        LoadConfig();
        if (!g_SelectionEnabled && !g_TraceEnabled)
            return;

        // Do not install the Ogre detour at all for DX9. Retry calls can reach
        // this point before the renderer module has finished loading.
        if (!GetModuleHandleA("RenderSystem_Direct3D11.dll"))
            return;

        HMODULE ogreMain = GetModuleHandleA("OgreMain.dll");
        if (!ogreMain)
            return;
        g_InstallAttempted = true;

        if (!IsExpectedOgreBuild(ogreMain))
        {
            if (!g_UnsupportedLogged)
            {
                LogShimA(LogLevel::Warn, "LIGHTSEL",
                    "unsupported OgreMain build; Enhanced light selection was not installed");
                g_UnsupportedLogged = true;
            }
            return;
        }
        if (!ResolveApi(ogreMain))
        {
            LogShimA(LogLevel::Warn, "LIGHTSEL",
                "required Ogre light exports are missing; feature disabled");
            return;
        }

        const uintptr_t target = reinterpret_cast<uintptr_t>(ogreMain) + kPopulateLightListBodyRva;
        static const std::uint8_t expected[kPopulateHookLength] =
            { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };
        if (!InstallInlineDetour32(g_PopulateLightListDetour, target,
                reinterpret_cast<void*>(PopulateLightListHook),
                kPopulateHookLength, expected, sizeof(expected)))
        {
            LogShimA(LogLevel::Warn, "LIGHTSEL",
                "Ogre _populateLightList prologue mismatch; feature failed closed");
            return;
        }

        g_OriginalPopulateLightList = reinterpret_cast<FnPopulateLightList>(
            g_PopulateLightListDetour.trampoline);
        LogShimA(LogLevel::Info, "LIGHTSEL",
            "installed Enhanced-only selector bodyRva=0x%08lX budgetHigh=%zu retention=%.1f%% mode=%s trace=%s",
            static_cast<unsigned long>(kPopulateLightListBodyRva),
            kEnhancedHighBudget, static_cast<double>(kDefaultRetentionBonus * 100.0f),
            g_SelectionEnabled ? "v2" : "observe",
            g_TraceEnabled ? "on" : "off");
    }
}
