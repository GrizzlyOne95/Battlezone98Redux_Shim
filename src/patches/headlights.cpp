// headlights.cpp
// BZR Open Shim - stock headlights (SinglePlayer tier), the emission-light
// state fix and the expected-Ogre-export check, split out of bzr_hooks.cpp.
// The dispatchers that drive them stay there; shared helpers come from
// bzr_hooks_internal.h.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "engine_globals.h"
#include "headlight_falloff.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace BZROpenShim
{
    namespace Hooks
    {
        // --- Stock headlights (SinglePlayer tier) -----------------------------
        // EXU exposed these Ogre Light calls first. OpenShim applies the same
        // controls directly to the stock GameObject list so campaign scripts are
        // not required. The feature stands down in multiplayer and whenever EXU
        // is loaded, leaving Campaign Reimagined's per-mission controls in charge.
        enum class HeadlightColourMode
        {
            Stock,
            Fixed,
            Rainbow,
        };

        enum class HeadlightBeamMode
        {
            Stock,
            Focused,
            Wide,
        };


        struct HeadlightOriginalState
        {
            bool hasColour = false;
            bool hasBeam = false;
            bool hasVisible = false;
            bool hasAttenuation = false;
            // World stamp. A mission change destroys every GameObject and its
            // Ogre light without any teardown callback, so an entry whose
            // worldGeneration no longer matches names either freed memory or a
            // recycled address. Such entries are discarded instead of restored.
            uint32_t worldGeneration = 0;
            OgreColourValue diffuse = {};
            OgreColourValue specular = {};
            float innerAngle = 0.0f;
            float outerAngle = 0.0f;
            float falloff = 1.0f;
            bool visible = true;
            HeadlightFalloff::Attenuation attenuation = {};
        };

        static constexpr DWORD kHeadlightRefreshMs = 200;
        // The exponent the shim shipped before the falloff repair. Kept only
        // so the A/B switch can reproduce the hard cone terminator on demand.
        static constexpr float kHeadlightPreRepairSpotFalloff = 0.35f;
        // LightRenderClass::Simulate iterates the Ogre lights emitted by
        // draw_light particle records. Stock deletes a renderer when its
        // active flag clears, which means an empty craft's running lights can
        // never return when a pilot re-enters. The stock phase is also clamped
        // after one interpolation instead of cycling.
        static constexpr uintptr_t kEmissionLightStateBranchAddr = 0x0044CBD0;
        static constexpr uintptr_t kEmissionLightActiveResumeAddr = 0x0044CBDF;
        static constexpr uintptr_t kEmissionLightLoopResumeAddr = 0x0044CF49;
        static constexpr size_t kEmissionLightStateBranchPatchLen = 9;
        static bool g_HeadlightConfigInitialized = false;
        static bool g_HeadlightPlayerVisibleConfigured = false;
        static bool g_HeadlightPlayerVisible = true;
        static bool g_HeadlightOtherVisibleConfigured = false;
        static bool g_HeadlightOtherVisible = true;
        static HeadlightColourMode g_HeadlightColourMode = HeadlightColourMode::Stock;
        static HeadlightBeamMode g_HeadlightBeamMode = HeadlightBeamMode::Stock;
        static float g_HeadlightColourR = 5.0f;
        static float g_HeadlightColourG = 5.0f;
        static float g_HeadlightColourB = 5.0f;
        static float g_HeadlightBrightness = 1.0f;
        static bool g_HeadlightRuntimeActive = false;
        static bool g_HeadlightLightTraceEnabled = false;
        // A/B switch for validation: restores the pre-repair constants
        // (cone falloff 0.35, stock attenuation untouched) so a capture run
        // can show the hard terminator and its repair from one binary.
        static bool g_HeadlightFalloffRepairEnabled = true;
        static std::unordered_set<void*> g_HeadlightFalloffPlanLogged;
        static int g_HeadlightLightTraceCount = 0;
        static constexpr int kHeadlightLightTraceLimit = 40;
        static DWORD g_HeadlightLastRefreshTick = 0;
        static std::unordered_map<void*, HeadlightOriginalState> g_HeadlightOriginalStates;
        // World identity for headlight baselines. The authoritative oracle is
        // the mission lifecycle seam (BzrSetRunningHook leaving/entering
        // RUN_STARTED): every baseline captured before a mission left
        // simulation refers to objects from a destroyed world, and anything
        // captured between missions belongs to no world at all. While the
        // seam is installed it is the SOLE generation authority: the player
        // object can legitimately change during a live world (ejection,
        // vehicle transition, engine-side recreation), so a pointer change
        // must not invalidate current-world baselines. The tracked player
        // pointer gates the generation only on installs where the seam could
        // not be installed (Steam/relocated): there a changed pointer still
        // proves the previous world is gone, while an unchanged pointer
        // proves nothing because the allocator can hand the next mission the
        // same address.
        static uint32_t s_HeadlightWorldGeneration = 0;
        static void* s_HeadlightWorldPlayerIdentity = nullptr;
        // Discarded-without-restore accounting; budgeted log only. The log
        // budget makes the first few discards of each world transition visible
        // in the session log without letting a pathological map flood it.
        static uint32_t g_HeadlightStaleEntryDiscards = 0;
        static constexpr uint32_t kHeadlightStaleDiscardLogBudget = 3;
        static uint32_t g_HeadlightStaleDiscardsLogged = 0;
        static void LogHeadlightStaleDiscard(
            const void* light, uint32_t entryGeneration)
        {
            ++g_HeadlightStaleEntryDiscards;
            if (g_HeadlightStaleDiscardsLogged >= kHeadlightStaleDiscardLogBudget)
                return;
            ++g_HeadlightStaleDiscardsLogged;
            Log(L"[HEADLIGHT] stale-world baseline discarded (not restored) "
                L"light=0x%p entryGen=%u currentGen=%u total=%u\n",
                light, entryGeneration,
                static_cast<unsigned>(s_HeadlightWorldGeneration),
                static_cast<unsigned>(g_HeadlightStaleEntryDiscards));
        }
        static InlineDetour32 g_EmissionLightStateDetour = {};
        static uintptr_t g_EmissionLightActiveResume = kEmissionLightActiveResumeAddr;
        static uintptr_t g_EmissionLightLoopResume = kEmissionLightLoopResumeAddr;
        static bool g_EmissionLightFixInstallAttempted = false;
        static bool g_EmissionLightFixInstalled = false;
        static bool g_EmissionLightFixMismatchLogged = false;

        // Resolves the Ogre Light/MovableObject entry points the headlight and
        // emission-light work needs. This runs exactly once.
        //
        // It used to retry every still-null field on every call, which looks
        // harmless until one of the names cannot resolve: that field stays null
        // forever and its GetProcAddress runs again on the next call. One of the
        // twenty names below was mis-mangled -- getCastShadows is virtual on
        // MovableObject, so it is `U`, not `Q` -- and HandleEmissionLightState
        // runs per emission light per frame. Sampling an 80-craft four-team
        // battle put that single failing lookup, plus the loader's error
        // reporting for it, at 43% of the main thread's CPU.
        HeadlightOgreApi& GetHeadlightOgreApi()
        {
            static HeadlightOgreApi api;
            static bool resolved = false;
            if (resolved)
                return api;

            if (!api.getDiffuse)
                api.getDiffuse = ResolveOgreProc<FnOgreGetLightColour>(
                    "?getDiffuseColour@Light@Ogre@@QBEABVColourValue@2@XZ");
            if (!api.setDiffuse)
                api.setDiffuse = ResolveOgreProc<FnOgreSetLightColour>(
                    "?setDiffuseColour@Light@Ogre@@QAEXMMM@Z");
            if (!api.getSpecular)
                api.getSpecular = ResolveOgreProc<FnOgreGetLightColour>(
                    "?getSpecularColour@Light@Ogre@@QBEABVColourValue@2@XZ");
            if (!api.setSpecular)
                api.setSpecular = ResolveOgreProc<FnOgreSetLightColour>(
                    "?setSpecularColour@Light@Ogre@@QAEXMMM@Z");
            if (!api.getInnerAngle)
                api.getInnerAngle = ResolveOgreProc<FnOgreGetLightRadian>(
                    "?getSpotlightInnerAngle@Light@Ogre@@QBEABVRadian@2@XZ");
            if (!api.getOuterAngle)
                api.getOuterAngle = ResolveOgreProc<FnOgreGetLightRadian>(
                    "?getSpotlightOuterAngle@Light@Ogre@@QBEABVRadian@2@XZ");
            if (!api.getFalloff)
                api.getFalloff = ResolveOgreProc<FnOgreGetLightFloat>(
                    "?getSpotlightFalloff@Light@Ogre@@QBEMXZ");
            if (!api.setRange)
                api.setRange = ResolveOgreProc<FnOgreSetSpotlightRange>(
                    "?setSpotlightRange@Light@Ogre@@QAEXABVRadian@2@0M@Z");
            if (!api.getVisible)
                api.getVisible = ResolveOgreProc<FnOgreGetLightVisible>(
                    "?getVisible@MovableObject@Ogre@@UBE_NXZ");
            if (!api.setVisible)
                api.setVisible = ResolveOgreProc<FnOgreSetVisible>(
                    "?setVisible@Light@Ogre@@UAEX_N@Z");
            if (!api.setAttenuation)
                api.setAttenuation = ResolveOgreProc<FnOgreSetAttenuation>(
                    "?setAttenuation@Light@Ogre@@QAEXMMMM@Z");
            if (!api.getAttenuationRange)
                api.getAttenuationRange = ResolveOgreProc<FnOgreGetLightFloat>(
                    "?getAttenuationRange@Light@Ogre@@QBEMXZ");
            if (!api.getAttenuationConstant)
                api.getAttenuationConstant = ResolveOgreProc<FnOgreGetLightFloat>(
                    "?getAttenuationConstant@Light@Ogre@@QBEMXZ");
            if (!api.getAttenuationLinear)
                api.getAttenuationLinear = ResolveOgreProc<FnOgreGetLightFloat>(
                    "?getAttenuationLinear@Light@Ogre@@QBEMXZ");
            if (!api.getAttenuationQuadratic)
                api.getAttenuationQuadratic = ResolveOgreProc<FnOgreGetLightFloat>(
                    "?getAttenuationQuadric@Light@Ogre@@QBEMXZ");
            if (!api.getPowerScale)
                api.getPowerScale = ResolveOgreProc<FnOgreGetLightFloat>(
                    "?getPowerScale@Light@Ogre@@QBEMXZ");
            if (!api.getType)
                api.getType = ResolveOgreProc<FnOgreGetLightType>(
                    "?getType@Light@Ogre@@QBE?AW4LightTypes@12@XZ");
            if (!api.getDerivedPosition)
                api.getDerivedPosition = ResolveOgreProc<FnOgreGetLightDerivedPosition>(
                    "?getDerivedPosition@Light@Ogre@@QBEABVVector3@2@_N@Z");
            if (!api.getDerivedDirection)
                api.getDerivedDirection = ResolveOgreProc<FnOgreGetLightVector3>(
                    "?getDerivedDirection@Light@Ogre@@QBEABVVector3@2@XZ");
            if (!api.getCastShadows)
                api.getCastShadows = ResolveOgreProc<FnOgreGetCastShadows>(
                    "?getCastShadows@MovableObject@Ogre@@UBE_NXZ");

            resolved = true;

            // Name anything that did not resolve, once. A null entry point here
            // degrades a headlight behaviour silently; the mis-mangled name
            // above survived because nothing ever said it had failed.
            const struct { const wchar_t* field; const void* value; } audit[] = {
                { L"getDiffuseColour", reinterpret_cast<const void*>(api.getDiffuse) },
                { L"setDiffuseColour", reinterpret_cast<const void*>(api.setDiffuse) },
                { L"getSpecularColour", reinterpret_cast<const void*>(api.getSpecular) },
                { L"setSpecularColour", reinterpret_cast<const void*>(api.setSpecular) },
                { L"getSpotlightInnerAngle", reinterpret_cast<const void*>(api.getInnerAngle) },
                { L"getSpotlightOuterAngle", reinterpret_cast<const void*>(api.getOuterAngle) },
                { L"getSpotlightFalloff", reinterpret_cast<const void*>(api.getFalloff) },
                { L"setSpotlightRange", reinterpret_cast<const void*>(api.setRange) },
                { L"getVisible", reinterpret_cast<const void*>(api.getVisible) },
                { L"setVisible", reinterpret_cast<const void*>(api.setVisible) },
                { L"setAttenuation", reinterpret_cast<const void*>(api.setAttenuation) },
                { L"getAttenuationRange", reinterpret_cast<const void*>(api.getAttenuationRange) },
                { L"getAttenuationConstant", reinterpret_cast<const void*>(api.getAttenuationConstant) },
                { L"getAttenuationLinear", reinterpret_cast<const void*>(api.getAttenuationLinear) },
                { L"getAttenuationQuadric", reinterpret_cast<const void*>(api.getAttenuationQuadratic) },
                { L"getPowerScale", reinterpret_cast<const void*>(api.getPowerScale) },
                { L"getType", reinterpret_cast<const void*>(api.getType) },
                { L"getDerivedPosition", reinterpret_cast<const void*>(api.getDerivedPosition) },
                { L"getDerivedDirection", reinterpret_cast<const void*>(api.getDerivedDirection) },
                { L"getCastShadows", reinterpret_cast<const void*>(api.getCastShadows) },
            };
            int unresolved = 0;
            for (const auto& entry : audit)
            {
                if (!entry.value)
                {
                    ++unresolved;
                    Log(L"[HEADLIGHT] Ogre entry point %ls did not resolve\n", entry.field);
                }
            }
            Log(L"[HEADLIGHT] Ogre entry points resolved once: %d of %d\n",
                static_cast<int>(_countof(audit)) - unresolved,
                static_cast<int>(_countof(audit)));
            return api;
        }

        // Startup sweep over the Ogre exports the shim depends on in hot paths.
        //
        // ResolveOgreProcRaw already warns once per bad name, but only when
        // something asks for it -- so a typo in a feature that has not run yet
        // stays invisible until it does, and then it is a runtime warning
        // rather than a startup one. This forces the load-bearing names to
        // resolve as soon as OgreMain is present, so a bad decoration is a
        // single clear line in the log before any frame is drawn.
        //
        // The list is deliberately short: hot-path entry points, plus the
        // headlight/light API by way of GetHeadlightOgreApi's own audit. It can
        // drift from the full set of names the shim uses; when it does, the
        // consequence is only that those names are reported later, by the
        // resolver, rather than here.
        void VerifyExpectedOgreExportsIfPossible()
        {
            static bool verified = false;
            if (verified || !GetModuleHandleA("OgreMain.dll"))
                return;
            verified = true;

            static const char* const kHotPathExports[] = {
                "?getRenderQueue@SceneManager@Ogre@@UAEPAVRenderQueue@2@XZ",
                "?getCurrentViewport@SceneManager@Ogre@@QBEPAVViewport@2@XZ",
                "?getCamera@Viewport@Ogre@@QBEPAVCamera@2@XZ",
                "?getNumSubEntities@Entity@Ogre@@QBEIXZ",
                "?getSubEntity@Entity@Ogre@@QBEPAVSubEntity@2@I@Z",
                "?_notifyCurrentCamera@Entity@Ogre@@UAEXPAVCamera@2@@Z",
                "?_updateRenderQueue@Entity@Ogre@@UAEXPAVRenderQueue@2@@Z",
                "?setVisible@MovableObject@Ogre@@UAEX_N@Z",
                "?setPosition@Node@Ogre@@UAEXMMM@Z",
                "?setOrientation@Node@Ogre@@UAEXMMMM@Z",
                "?getRootSceneNode@SceneManager@Ogre@@UAEPAVSceneNode@2@XZ",
                "?attachObject@SceneNode@Ogre@@UAEXPAVMovableObject@2@@Z",
                "?getDerivedPosition@Camera@Ogre@@QBEABVVector3@2@XZ",
            };

            int missing = 0;
            for (const char* const name : kHotPathExports)
            {
                if (!ResolveOgreProcRaw(name))
                {
                    ++missing;
                }
            }

            // Forces the twenty light entry points to resolve and audit now
            // rather than on the first emission light of the first battle.
            GetHeadlightOgreApi();

            if (missing == 0)
            {
                Log(L"[OGRE-EXPORTS] Startup verification: %d of %d hot-path exports resolved\n",
                    static_cast<int>(_countof(kHotPathExports)),
                    static_cast<int>(_countof(kHotPathExports)));
            }
            else
            {
                Log(L"[OGRE-EXPORTS] WARNING: startup verification found %d of %d "
                    L"hot-path exports missing; see the per-name warnings above\n",
                    missing, static_cast<int>(_countof(kHotPathExports)));
            }
        }

        // Full parameter dump for one Ogre Light. This is the instrument that
        // decides between the four candidate causes of a hard terrain
        // terminator -- outer-cone cutoff, attenuation range cutoff,
        // attenuation curve, or a backend difference -- because every one of
        // them is visible in these numbers.
        //
        // Enable with [Diagnostics] HeadlightLightTrace = 1 (or
        // OPENSHIM_TRACE_HEADLIGHT_LIGHT=1).
        static void LogHeadlightLightParameters(void* light, bool isPlayer, const wchar_t* phase)
        {
            if (!light)
                return;

            auto& api = GetHeadlightOgreApi();
            __try
            {
                const int type = api.getType ? api.getType(light) : -1;
                const OgreVector3* position =
                    api.getDerivedPosition ? api.getDerivedPosition(light, false) : nullptr;
                const OgreVector3* direction =
                    api.getDerivedDirection ? api.getDerivedDirection(light) : nullptr;
                const OgreColourValue* diffuse = api.getDiffuse ? api.getDiffuse(light) : nullptr;
                const OgreColourValue* specular = api.getSpecular ? api.getSpecular(light) : nullptr;
                const float* inner = api.getInnerAngle ? api.getInnerAngle(light) : nullptr;
                const float* outer = api.getOuterAngle ? api.getOuterAngle(light) : nullptr;
                const float range = api.getAttenuationRange ? api.getAttenuationRange(light) : -1.0f;
                const float constant =
                    api.getAttenuationConstant ? api.getAttenuationConstant(light) : -1.0f;
                const float linear =
                    api.getAttenuationLinear ? api.getAttenuationLinear(light) : -1.0f;
                const float quadratic =
                    api.getAttenuationQuadratic ? api.getAttenuationQuadratic(light) : -1.0f;

                // The number that actually decides whether the cutoff is
                // visible: how much light still reaches the terrain at the
                // instant the range clamp zeroes it. Anything above roughly
                // 1/255 of a diffuse unit is a step a player can see.
                const float peakDiffuse = diffuse
                    ? (std::max)((std::max)(diffuse->r, diffuse->g), diffuse->b)
                    : 0.0f;
                const float denominatorAtRange =
                    constant + range * (linear + range * quadratic);
                const float edgeIntensity = (denominatorAtRange > 0.0f && range > 0.0f)
                    ? peakDiffuse / denominatorAtRange
                    : -1.0f;

                Log(L"[HEADLIGHT-PROBE] %ls light=0x%p owner=%hs type=%d pos=(%.2f, %.2f, %.2f) dir=(%.3f, %.3f, %.3f) "
                    L"diffuse=(%.3f, %.3f, %.3f) specular=(%.3f, %.3f, %.3f) power=%.3f "
                    L"range=%.1f attenuation=(c=%.4f l=%.5f q=%.6f) inner=%.2fdeg outer=%.2fdeg falloff=%.3f "
                    L"visible=%hs castShadows=%hs edgeIntensityAtRange=%.5f (%hs)\n",
                    phase,
                    light,
                    isPlayer ? "player" : "other",
                    type,
                    position ? static_cast<double>(position->x) : 0.0,
                    position ? static_cast<double>(position->y) : 0.0,
                    position ? static_cast<double>(position->z) : 0.0,
                    direction ? static_cast<double>(direction->x) : 0.0,
                    direction ? static_cast<double>(direction->y) : 0.0,
                    direction ? static_cast<double>(direction->z) : 0.0,
                    diffuse ? static_cast<double>(diffuse->r) : 0.0,
                    diffuse ? static_cast<double>(diffuse->g) : 0.0,
                    diffuse ? static_cast<double>(diffuse->b) : 0.0,
                    specular ? static_cast<double>(specular->r) : 0.0,
                    specular ? static_cast<double>(specular->g) : 0.0,
                    specular ? static_cast<double>(specular->b) : 0.0,
                    api.getPowerScale ? static_cast<double>(api.getPowerScale(light)) : -1.0,
                    static_cast<double>(range),
                    static_cast<double>(constant),
                    static_cast<double>(linear),
                    static_cast<double>(quadratic),
                    inner ? static_cast<double>(*inner) * (180.0 / 3.14159265358979) : -1.0,
                    outer ? static_cast<double>(*outer) * (180.0 / 3.14159265358979) : -1.0,
                    api.getFalloff ? static_cast<double>(api.getFalloff(light)) : -1.0,
                    (api.getVisible && api.getVisible(light)) ? "yes" : "no",
                    (api.getCastShadows && api.getCastShadows(light)) ? "yes" : "no",
                    static_cast<double>(edgeIntensity),
                    (edgeIntensity > (1.0f / 255.0f))
                        ? "VISIBLE STEP AT RANGE"
                        : "below 8-bit floor");
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[HEADLIGHT-PROBE] faulted reading light=0x%p\n", light);
            }
        }

        static void HandleEmissionLightState(void* renderer, void* renderClass)
        {
            if (!renderer)
                return;

            __try
            {
                auto* rendererBytes = reinterpret_cast<uint8_t*>(renderer);
                const bool active = rendererBytes[0x1C] != 0;
                void* light = *reinterpret_cast<void**>(rendererBytes + 0x70);
                auto& api = GetHeadlightOgreApi();
                if (light && api.setVisible)
                    api.setVisible(light, active);

                if (!active || !renderClass)
                    return;

                // The stock blend is clamp(phase * rate, 0, 1), followed by
                // phase += dt. Feed it a repeating cosine blend each frame so
                // configured start/end colours and intensity visibly pulse.
                const float rate = *reinterpret_cast<const float*>(
                    reinterpret_cast<const uint8_t*>(renderClass) + 0x178);
                if (std::isfinite(rate) && rate > 0.0001f)
                {
                    constexpr double kPi = 3.14159265358979323846;
                    const double seconds = static_cast<double>(GetTickCount64()) / 1000.0;
                    const float blend = static_cast<float>(
                        0.5 - 0.5 * std::cos(kPi * seconds * static_cast<double>(rate)));
                    *reinterpret_cast<float*>(rendererBytes + 0x60) = blend / rate;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        static void __declspec(naked) EmissionLightStateHook()
        {
            __asm
            {
                pushad
                pushfd
                push dword ptr [ebp - 0x08]
                push dword ptr [ebp - 0x04]
                call HandleEmissionLightState
                add esp, 8
                popfd
                popad

                // Replay the displaced active-state test.
                mov eax, [ebp - 0x04]
                movzx ecx, byte ptr [eax + 0x1C]
                test ecx, ecx
                jz emissionInactive
                jmp dword ptr [g_EmissionLightActiveResume]

            emissionInactive:
                // Keep the renderer dormant instead of invoking its deleting
                // destructor. Its producer can set active again on re-entry.
                jmp dword ptr [g_EmissionLightLoopResume]
            }
        }

        void InstallEmissionLightFixIfPossible()
        {
            if (g_EmissionLightFixInstalled || g_EmissionLightFixInstallAttempted)
                return;
            g_EmissionLightFixInstallAttempted = true;

            if (EnvFlagEnabled("OPENSHIM_DISABLE_EMISSION_LIGHT_FIX"))
            {
                Log(L"[EMISSIONLIGHT] Fix disabled by environment\n");
                return;
            }

            static const uint8_t kExpectedBytes[kEmissionLightStateBranchPatchLen] =
            {
                0x8B, 0x45, 0xFC,
                0x0F, 0xB6, 0x48, 0x1C,
                0x85, 0xC9
            };
            if (!InstallInlineDetour32(
                    g_EmissionLightStateDetour,
                    kEmissionLightStateBranchAddr,
                    reinterpret_cast<void*>(EmissionLightStateHook),
                    kEmissionLightStateBranchPatchLen,
                    kExpectedBytes,
                    sizeof(kExpectedBytes)))
            {
                if (!g_EmissionLightFixMismatchLogged)
                {
                    Log(L"[EMISSIONLIGHT] Stock bytes not ready/mismatched; running-light fix deferred at 0x%08X\n",
                        static_cast<uint32_t>(kEmissionLightStateBranchAddr));
                    g_EmissionLightFixMismatchLogged = true;
                }
                // Steam's packed on-disk image settles to the GOG bytes after
                // launch. Let RetryDeferredRuntimeHooks try again then.
                if (g_IsSteamExe)
                    g_EmissionLightFixInstallAttempted = false;
                return;
            }

            g_EmissionLightFixInstalled = true;
            Log(L"[EMISSIONLIGHT] Installed re-entry visibility and continuous pulse fix at 0x%08X\n",
                static_cast<uint32_t>(kEmissionLightStateBranchAddr));
        }

        static void* TryGetGameObjectHeadlight(void* gameObject)
        {
            if (!gameObject)
                return nullptr;
            __try
            {
                auto* bridge = *reinterpret_cast<uint8_t**>(
                    reinterpret_cast<uint8_t*>(gameObject) + 0xF0);
                return bridge ? *reinterpret_cast<void**>(bridge + 0xA8) : nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        bool IsLiveHeadlightObjectSlot(void* gameObject)
        {
            if (!gameObject)
                return false;
            __try
            {
                const uintptr_t vtable = *reinterpret_cast<const uintptr_t*>(gameObject);
                const uintptr_t mainBase = GetMainModuleBase();
                // Live GameObject primary vtables are in the exe's compact
                // code/rdata region (observed around 0x0088xxxx). Empty handle
                // slots are zero; this also rejects stale heap-looking values.
                return vtable >= mainBase && vtable < mainBase + 0x00600000;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void* TryGetHeadlightPlayerObject()
        {
            __try
            {
                auto* const userObjectSlot =
                    reinterpret_cast<void* const*>(EngineGlobals::UserObjectSlot());
                return userObjectSlot ? *userObjectSlot : nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        static void RestoreHeadlightState(void* light, const HeadlightOriginalState& state)
        {
            if (!light)
                return;
            auto& api = GetHeadlightOgreApi();
            __try
            {
                if (state.hasColour && api.setDiffuse && api.setSpecular)
                {
                    api.setDiffuse(light, state.diffuse.r, state.diffuse.g, state.diffuse.b);
                    api.setSpecular(light, state.specular.r, state.specular.g, state.specular.b);
                }
                if (state.hasBeam && api.setRange)
                {
                    float inner = state.innerAngle;
                    float outer = state.outerAngle;
                    api.setRange(light, &inner, &outer, state.falloff);
                }
                if (state.hasAttenuation && api.setAttenuation)
                {
                    api.setAttenuation(
                        light,
                        state.attenuation.range,
                        state.attenuation.constant,
                        state.attenuation.linear,
                        state.attenuation.quadratic);
                }
                if (state.hasVisible && api.setVisible)
                    api.setVisible(light, state.visible);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        static void RestoreAllHeadlightStates(bool writeBack)
        {
            if (writeBack)
            {
                for (const auto& entry : g_HeadlightOriginalStates)
                {
                    // A baseline from a previous world must not be written
                    // through its stored pointer: the light is either freed or
                    // the address was recycled by an unrelated object.
                    if (entry.second.worldGeneration != s_HeadlightWorldGeneration)
                        LogHeadlightStaleDiscard(entry.first, entry.second.worldGeneration);
                    else
                        RestoreHeadlightState(entry.first, entry.second);
                }
            }
            g_HeadlightOriginalStates.clear();
        }

        static bool CaptureHeadlightState(
            void* light,
            bool needColour,
            bool needBeam,
            bool needAttenuation,
            bool needVisible)
        {
            if (!light)
                return false;
            auto& state = g_HeadlightOriginalStates[light];
            // A recycled light address must not inherit the dead light's
            // baseline: the has* flags below would suppress recapture and the
            // new light would be restored from another object's values. Reset
            // on a world change so every property is captured fresh (capture
            // runs before any modification, so the fresh values are stock).
            if (state.worldGeneration != s_HeadlightWorldGeneration)
                state = {};
            state.worldGeneration = s_HeadlightWorldGeneration;
            auto& api = GetHeadlightOgreApi();
            __try
            {
                if (needColour && !state.hasColour)
                {
                    if (!api.getDiffuse || !api.getSpecular || !api.setDiffuse || !api.setSpecular)
                        return false;
                    const OgreColourValue* diffuse = api.getDiffuse(light);
                    const OgreColourValue* specular = api.getSpecular(light);
                    if (!diffuse || !specular)
                        return false;
                    state.diffuse = *diffuse;
                    state.specular = *specular;
                    state.hasColour = true;
                }
                if (needBeam && !state.hasBeam)
                {
                    if (!api.getInnerAngle || !api.getOuterAngle ||
                        !api.getFalloff || !api.setRange)
                    {
                        return false;
                    }
                    const float* inner = api.getInnerAngle(light);
                    const float* outer = api.getOuterAngle(light);
                    if (!inner || !outer)
                        return false;
                    state.innerAngle = *inner;
                    state.outerAngle = *outer;
                    state.falloff = api.getFalloff(light);
                    state.hasBeam = true;
                }
                if (needAttenuation && !state.hasAttenuation)
                {
                    if (!api.setAttenuation || !api.getAttenuationRange ||
                        !api.getAttenuationConstant || !api.getAttenuationLinear ||
                        !api.getAttenuationQuadratic)
                    {
                        return false;
                    }
                    state.attenuation.range = api.getAttenuationRange(light);
                    state.attenuation.constant = api.getAttenuationConstant(light);
                    state.attenuation.linear = api.getAttenuationLinear(light);
                    state.attenuation.quadratic = api.getAttenuationQuadratic(light);
                    if (!HeadlightFalloff::IsUsable(state.attenuation))
                        return false;
                    state.hasAttenuation = true;
                }
                if (needVisible && !state.hasVisible)
                {
                    if (!api.getVisible || !api.setVisible)
                        return false;
                    state.visible = api.getVisible(light);
                    state.hasVisible = true;
                }
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                g_HeadlightOriginalStates.erase(light);
                return false;
            }
        }

        // One line per light per session recording what the falloff repair
        // actually changed, so a regression shows up as a number in the log
        // rather than as "the boundary is back".
        static void LogHeadlightFalloffPlanOnce(
            void* light,
            float peakDiffuse,
            const HeadlightFalloff::Plan& plan)
        {
            if (!g_HeadlightFalloffPlanLogged.insert(light).second)
                return;
            Log(L"[HEADLIGHT] falloff repair light=0x%p peak=%.2f range %.1f -> %.1f "
                L"edgeIntensity %.5f -> %.5f (floor %.5f) coneFalloff ramp %.4f -> %.4f of penumbra (%hs)\n",
                light,
                static_cast<double>(peakDiffuse),
                static_cast<double>(plan.rangeBefore),
                static_cast<double>(plan.attenuation.range),
                static_cast<double>(plan.edgeIntensityBefore),
                static_cast<double>(plan.edgeIntensityAfter),
                static_cast<double>(HeadlightFalloff::kDisplayFloor),
                static_cast<double>(plan.rampFractionBefore),
                static_cast<double>(plan.rampFractionAfter),
                (plan.edgeIntensityAfter <= HeadlightFalloff::kDisplayFloor &&
                 plan.rampFractionAfter >= HeadlightFalloff::kMinAcceptableRampFraction)
                    ? "both terminators below the visible threshold"
                    : "TERMINATOR STILL VISIBLE");
        }

        // Recomputes the truncation radius and the cone exponent for whatever
        // brightness is about to be written, so neither terminator lands where
        // a player can see it. Returns false if the light's own attenuation
        // cannot be read, in which case the caller leaves attenuation alone.
        static bool BuildHeadlightFalloffPlan(
            void* light,
            float peakDiffuse,
            HeadlightFalloff::Plan& outPlan)
        {
            auto& api = GetHeadlightOgreApi();
            if (!api.setAttenuation || !api.getAttenuationRange ||
                !api.getAttenuationConstant || !api.getAttenuationLinear ||
                !api.getAttenuationQuadratic || !api.getFalloff)
            {
                return false;
            }

            HeadlightFalloff::Attenuation stock = {};
            float previousFalloff = 1.0f;
            __try
            {
                stock.range = api.getAttenuationRange(light);
                stock.constant = api.getAttenuationConstant(light);
                stock.linear = api.getAttenuationLinear(light);
                stock.quadratic = api.getAttenuationQuadratic(light);
                previousFalloff = api.getFalloff(light);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }

            if (!HeadlightFalloff::IsUsable(stock))
                return false;

            // The captured baseline is the engine's own curve, not whatever a
            // previous refresh already widened it to, so the solve stays
            // idempotent across the 200 ms refresh tick.
            const auto existing = g_HeadlightOriginalStates.find(light);
            if (existing != g_HeadlightOriginalStates.end() &&
                existing->second.hasAttenuation &&
                existing->second.worldGeneration == s_HeadlightWorldGeneration)
                stock = existing->second.attenuation;

            outPlan = HeadlightFalloff::BuildPlan(stock, peakDiffuse, previousFalloff);
            return true;
        }

        static bool ApplyHeadlightState(
            void* light,
            bool setColour,
            float r,
            float g,
            float b,
            bool setBeam,
            float inner,
            float outer,
            bool setVisible,
            bool visible)
        {
            // Only a shim-owned brightness or beam change can push a terminator
            // into view, so a run that is merely toggling visibility leaves the
            // engine's own falloff untouched and stays stock-identical.
            const bool setFalloff =
                g_HeadlightFalloffRepairEnabled && (setColour || setBeam);
            const float peakDiffuse = setColour
                ? (std::max)((std::max)(r, g), b)
                : 1.0f;

            HeadlightFalloff::Plan plan = {};
            const bool haveFalloffPlan =
                setFalloff && BuildHeadlightFalloffPlan(light, peakDiffuse, plan);

            if (!CaptureHeadlightState(light, setColour, setBeam, haveFalloffPlan, setVisible))
                return false;
            auto& api = GetHeadlightOgreApi();
            __try
            {
                if (setColour)
                {
                    api.setDiffuse(light, r, g, b);
                    api.setSpecular(light, r, g, b);
                }
                if (setBeam || haveFalloffPlan)
                {
                    // setSpotlightRange carries the falloff exponent, so a
                    // beam-less colour override still has to go through it to
                    // soften the cone; reuse the light's current angles in that
                    // case rather than inventing new ones.
                    float innerCopy = inner;
                    float outerCopy = outer;
                    if (!setBeam)
                    {
                        const float* currentInner =
                            api.getInnerAngle ? api.getInnerAngle(light) : nullptr;
                        const float* currentOuter =
                            api.getOuterAngle ? api.getOuterAngle(light) : nullptr;
                        if (!currentInner || !currentOuter)
                            return false;
                        innerCopy = *currentInner;
                        outerCopy = *currentOuter;
                    }
                    api.setRange(
                        light,
                        &innerCopy,
                        &outerCopy,
                        g_HeadlightFalloffRepairEnabled
                            ? (haveFalloffPlan ? plan.falloff
                                               : HeadlightFalloff::kSmoothSpotFalloff)
                            : kHeadlightPreRepairSpotFalloff);
                }
                if (haveFalloffPlan)
                {
                    api.setAttenuation(
                        light,
                        plan.attenuation.range,
                        plan.attenuation.constant,
                        plan.attenuation.linear,
                        plan.attenuation.quadratic);
                    LogHeadlightFalloffPlanOnce(light, peakDiffuse, plan);
                }
                if (setVisible)
                    api.setVisible(light, visible);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void HueToHeadlightRgb(float hue, float& r, float& g, float& b)
        {
            const float scaled = hue * 6.0f;
            const int sector = static_cast<int>(std::floor(scaled)) % 6;
            const float f = scaled - std::floor(scaled);
            const float q = 1.0f - f;
            switch (sector)
            {
            case 0: r = 1.0f; g = f;    b = 0.0f; break;
            case 1: r = q;    g = 1.0f; b = 0.0f; break;
            case 2: r = 0.0f; g = 1.0f; b = f;    break;
            case 3: r = 0.0f; g = q;    b = 1.0f; break;
            case 4: r = f;    g = 0.0f; b = 1.0f; break;
            default:r = 1.0f; g = 0.0f; b = q;    break;
            }
            r *= 5.0f;
            g *= 5.0f;
            b *= 5.0f;
        }

        static bool ParseHeadlightColour(const std::string& raw)
        {
            std::string value = raw;
            for (char& c : value)
                c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

            g_HeadlightColourMode = HeadlightColourMode::Fixed;
            if (value == "stock" || value == "default" || value == "off")
            {
                g_HeadlightColourMode = HeadlightColourMode::Stock;
                return true;
            }
            if (value == "rainbow")
            {
                g_HeadlightColourMode = HeadlightColourMode::Rainbow;
                return true;
            }

            struct Preset { const char* name; float r; float g; float b; };
            static constexpr Preset presets[] = {
                { "white",   5.0f, 5.0f, 5.0f },
                { "red",     5.0f, 1.0f, 1.0f },
                { "green",   1.0f, 5.0f, 1.0f },
                { "blue",    1.0f, 1.0f, 5.0f },
                { "yellow",  5.0f, 5.0f, 1.0f },
                { "cyan",    1.0f, 5.0f, 5.0f },
                { "magenta", 5.0f, 1.0f, 5.0f },
                { "orange",  5.0f, 2.5f, 1.0f },
                { "purple",  2.5f, 1.0f, 5.0f },
                { "teal",    1.0f, 5.0f, 2.5f },
            };
            for (const auto& preset : presets)
            {
                if (value == preset.name)
                {
                    g_HeadlightColourR = preset.r;
                    g_HeadlightColourG = preset.g;
                    g_HeadlightColourB = preset.b;
                    return true;
                }
            }

            float r = 0.0f;
            float g = 0.0f;
            float b = 0.0f;
            char extra = 0;
            if (std::sscanf(value.c_str(), " %f , %f , %f %c", &r, &g, &b, &extra) == 3 &&
                std::isfinite(r) && std::isfinite(g) && std::isfinite(b) &&
                r >= 0.0f && g >= 0.0f && b >= 0.0f &&
                r <= 20.0f && g <= 20.0f && b <= 20.0f)
            {
                g_HeadlightColourR = r;
                g_HeadlightColourG = g;
                g_HeadlightColourB = b;
                return true;
            }
            g_HeadlightColourMode = HeadlightColourMode::Stock;
            return false;
        }

        static bool ParseHeadlightBeam(const std::string& raw)
        {
            std::string value = raw;
            for (char& c : value)
                c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            if (value == "stock" || value == "default" || value == "off")
                g_HeadlightBeamMode = HeadlightBeamMode::Stock;
            else if (value == "focused" || value == "focus" || value == "narrow")
                g_HeadlightBeamMode = HeadlightBeamMode::Focused;
            else if (value == "wide")
                g_HeadlightBeamMode = HeadlightBeamMode::Wide;
            else
                return false;
            return true;
        }

        static bool IsHeadlightFeatureConfigured()
        {
            return g_HeadlightPlayerVisibleConfigured ||
                   g_HeadlightOtherVisibleConfigured ||
                   g_HeadlightColourMode != HeadlightColourMode::Stock ||
                   g_HeadlightBeamMode != HeadlightBeamMode::Stock ||
                   std::abs(g_HeadlightBrightness - 1.0f) > 0.001f;
        }

        // Lifecycle-seam hook: advances the headlight world generation from
        // the mission run-state machine. Leaving RUN_STARTED means the world's
        // lights are going away; entering it means a fresh world is starting.
        // Both edges invalidate every tracked baseline, so a baseline can only
        // ever be restored within the single mission whose scene it was
        // captured in. Entries invalidated here become discard-only: the
        // restore paths refuse to write through their stored pointers.
        void HeadlightNotifyMissionRunStateChanged(bool enteringSimulation)
        {
            if (!g_HeadlightRuntimeActive && g_HeadlightOriginalStates.empty())
                return;
            ++s_HeadlightWorldGeneration;
            g_HeadlightStaleEntryDiscards = 0;
            g_HeadlightStaleDiscardsLogged = 0;
            Log(L"[HEADLIGHT] Mission %hs simulation: world generation advanced to %u\n",
                enteringSimulation ? "entered" : "left",
                static_cast<unsigned>(s_HeadlightWorldGeneration));
        }

        void RefreshHeadlightState()
        {
            const bool exuLoaded = IsExuModuleLoaded();
            const bool wantActive =
                IsHeadlightFeatureConfigured() &&
                ReadLocalPlayerNetIdValue() == 0 &&
                !exuLoaded;
            if (!wantActive)
            {
                if (g_HeadlightRuntimeActive || !g_HeadlightOriginalStates.empty())
                {
                    // Once EXU is present, do not write old stock values over a
                    // campaign setting that may already have been applied.
                    RestoreAllHeadlightStates(!exuLoaded);
                    Log(L"[HEADLIGHT] Stood down (%hs)\n",
                        exuLoaded ? "EXU authoritative" : "multiplayer/disabled");
                }
                g_HeadlightRuntimeActive = false;
                g_HeadlightLastRefreshTick = 0;
                return;
            }

            if (!g_HeadlightRuntimeActive)
            {
                g_HeadlightRuntimeActive = true;
                g_HeadlightLastRefreshTick = 0;
                Log(L"[HEADLIGHT] Stock headlight policy active (SP-only)\n");
            }

            const DWORD now = GetTickCount();
            if (g_HeadlightLastRefreshTick != 0 &&
                static_cast<DWORD>(now - g_HeadlightLastRefreshTick) < kHeadlightRefreshMs)
            {
                return;
            }
            g_HeadlightLastRefreshTick = now;

            void* player = TryGetHeadlightPlayerObject();

            // Fallback sanity signal, and ONLY while the lifecycle seam is
            // unavailable. When g_MissionSeamInstalled is true, its enter/
            // leave edges are the sole world-generation authority: the player
            // object can legitimately change during a live world (ejection,
            // vehicle transition, engine-side recreation), so a pointer
            // change must not invalidate current-world baselines or recapture
            // already-modified values as stock. On installs where the seam
            // could not be installed (Steam/relocated builds) a changed
            // pointer is the only available evidence that the previous
            // world's lights are gone.
            if (!g_MissionSeamInstalled && player != s_HeadlightWorldPlayerIdentity)
            {
                s_HeadlightWorldPlayerIdentity = player;
                ++s_HeadlightWorldGeneration;
                g_HeadlightStaleEntryDiscards = 0;
                g_HeadlightStaleDiscardsLogged = 0;
            }

            float colourR = g_HeadlightColourR;
            float colourG = g_HeadlightColourG;
            float colourB = g_HeadlightColourB;
            if (g_HeadlightColourMode == HeadlightColourMode::Rainbow)
            {
                const float hue = static_cast<float>(now % 5000u) / 5000.0f;
                HueToHeadlightRgb(hue, colourR, colourG, colourB);
            }

            // Beam shape only. The cone exponent and the attenuation cutoff are
            // no longer hard-coded here: ApplyHeadlightState solves both from
            // the brightness actually being written, because a fixed exponent
            // that looks smooth at peak 1.0 is a hard edge at peak 10.
            float inner = 0.0f;
            float outer = 0.0f;
            float colourMultiplier = 1.0f;
            if (g_HeadlightBeamMode == HeadlightBeamMode::Focused)
            {
                inner = 0.2f;
                outer = 0.4f;
                colourMultiplier = 2.0f;
            }
            else if (g_HeadlightBeamMode == HeadlightBeamMode::Wide)
            {
                inner = 1.1f;
                outer = 1.5f;
                colourMultiplier = 0.8f;
            }
            colourR *= colourMultiplier;
            colourG *= colourMultiplier;
            colourB *= colourMultiplier;

            std::unordered_set<void*> touched;
            size_t scannedObjects = 0;
            size_t lightsFound = 0;
            const bool setPlayerColour =
                g_HeadlightColourMode != HeadlightColourMode::Stock ||
                std::abs(g_HeadlightBrightness - 1.0f) > 0.001f;
            const bool setPlayerBeam = g_HeadlightBeamMode != HeadlightBeamMode::Stock;
            auto applyObject = [&](void* object, bool isPlayer)
            {
                void* light = TryGetGameObjectHeadlight(object);
                if (!light)
                    return;
                ++lightsFound;
                const bool setVisible = isPlayer
                    ? g_HeadlightPlayerVisibleConfigured
                    : g_HeadlightOtherVisibleConfigured;
                const bool setColour = isPlayer && setPlayerColour;
                const bool setBeam = isPlayer && setPlayerBeam;
                if (!setVisible && !setColour && !setBeam)
                    return;
                const bool visible = isPlayer ? g_HeadlightPlayerVisible : g_HeadlightOtherVisible;
                const bool trace = g_HeadlightLightTraceEnabled && isPlayer &&
                                   g_HeadlightLightTraceCount < kHeadlightLightTraceLimit;
                if (trace)
                    LogHeadlightLightParameters(light, isPlayer, L"before");
                float objectR = colourR;
                float objectG = colourG;
                float objectB = colourB;
                if (setColour && g_HeadlightColourMode == HeadlightColourMode::Stock)
                {
                    // Brightness-only mode scales the engine's actual stock
                    // colour, not the White preset. Reuse the captured baseline
                    // after the first refresh so the operation is idempotent.
                    const auto original = g_HeadlightOriginalStates.find(light);
                    const OgreColourValue* baseline =
                        original != g_HeadlightOriginalStates.end() && original->second.hasColour &&
                                original->second.worldGeneration == s_HeadlightWorldGeneration
                            ? &original->second.diffuse
                            : (GetHeadlightOgreApi().getDiffuse
                                ? GetHeadlightOgreApi().getDiffuse(light) : nullptr);
                    if (!baseline)
                        return;
                    objectR = baseline->r;
                    objectG = baseline->g;
                    objectB = baseline->b;
                }
                if (setColour)
                {
                    objectR *= g_HeadlightBrightness;
                    objectG *= g_HeadlightBrightness;
                    objectB *= g_HeadlightBrightness;
                }
                if (ApplyHeadlightState(light, setColour, objectR, objectG, objectB,
                                        setBeam, inner, outer,
                                        setVisible, visible))
                {
                    touched.insert(light);
                }
                if (trace)
                {
                    ++g_HeadlightLightTraceCount;
                    LogHeadlightLightParameters(light, isPlayer, L"after ");
                }
            };

            if (player)
                applyObject(player, true);

            auto* arena = reinterpret_cast<uint8_t*>(EngineGlobals::GameObjectArena());
            if (arena)
            {
                for (size_t i = 0; i < kHeadlightObjectSlotCount; ++i)
                {
                    void* object = arena + i * kHeadlightObjectSlotSize;
                    if (object != player && IsLiveHeadlightObjectSlot(object))
                    {
                        ++scannedObjects;
                        applyObject(object, false);
                    }
                }
            }

            for (auto it = g_HeadlightOriginalStates.begin();
                 it != g_HeadlightOriginalStates.end();)
            {
                if (touched.find(it->first) == touched.end())
                {
                    // An entry from a previous world is erased only. Its
                    // pointer refers to a destroyed world's light, and writing
                    // through it would hit freed or recycled memory.
                    const bool staleWorld =
                        it->second.worldGeneration != s_HeadlightWorldGeneration;
                    if (staleWorld)
                        LogHeadlightStaleDiscard(it->first, it->second.worldGeneration);
                    else
                        RestoreHeadlightState(it->first, it->second);
                    it = g_HeadlightOriginalStates.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            if (EnvFlagEnabled("OPENSHIM_TRACE_HEADLIGHTS"))
            {
                Log(L"[HEADLIGHT] refresh player=0x%08X objects=%u lights=%u touched=%u tracked=%u worldGen=%u staleDiscards=%u\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(player)),
                    static_cast<unsigned>(scannedObjects),
                    static_cast<unsigned>(lightsFound),
                    static_cast<unsigned>(touched.size()),
                    static_cast<unsigned>(g_HeadlightOriginalStates.size()),
                    static_cast<unsigned>(s_HeadlightWorldGeneration),
                    static_cast<unsigned>(g_HeadlightStaleEntryDiscards));
            }
        }

        void InitializeHeadlightConfig()
        {
            if (g_HeadlightConfigInitialized)
                return;
            g_HeadlightConfigInitialized = true;

            // Reapplication after a settings click must also honor keys that
            // were removed by hand, so begin from the stock baseline each time.
            g_HeadlightPlayerVisibleConfigured = false;
            g_HeadlightPlayerVisible = true;
            g_HeadlightOtherVisibleConfigured = false;
            g_HeadlightOtherVisible = true;
            g_HeadlightColourMode = HeadlightColourMode::Stock;
            g_HeadlightBeamMode = HeadlightBeamMode::Stock;
            g_HeadlightColourR = 5.0f;
            g_HeadlightColourG = 5.0f;
            g_HeadlightColourB = 5.0f;
            g_HeadlightBrightness = 1.0f;

            bool boolValue = false;
            if (TryGetUserConfigBool("Diagnostics", "HeadlightLightTrace", boolValue))
                g_HeadlightLightTraceEnabled = boolValue;
            if (EnvFlagEnabled("OPENSHIM_TRACE_HEADLIGHT_LIGHT"))
                g_HeadlightLightTraceEnabled = true;
            if (TryGetUserConfigBool(
                    kUserConfigSinglePlayerSection, "HeadlightFalloffRepair", boolValue))
            {
                g_HeadlightFalloffRepairEnabled = boolValue;
            }
            if (EnvFlagEnabled("OPENSHIM_DISABLE_HEADLIGHT_FALLOFF_REPAIR"))
                g_HeadlightFalloffRepairEnabled = false;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "Headlights", boolValue))
            {
                g_HeadlightPlayerVisibleConfigured = true;
                g_HeadlightPlayerVisible = boolValue;
            }
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "OtherHeadlights", boolValue))
            {
                g_HeadlightOtherVisibleConfigured = true;
                g_HeadlightOtherVisible = boolValue;
            }

            std::string value;
            if (TryGetUserConfigString(kUserConfigSinglePlayerSection, "HeadlightColor", value) &&
                !ParseHeadlightColour(value))
            {
                Log(L"[HEADLIGHT] Ignoring invalid HeadlightColor=%hs\n", value.c_str());
            }
            if (TryGetUserConfigString(kUserConfigSinglePlayerSection, "HeadlightBeam", value) &&
                !ParseHeadlightBeam(value))
            {
                Log(L"[HEADLIGHT] Ignoring invalid HeadlightBeam=%hs\n", value.c_str());
            }
            if (TryGetUserConfigString(kUserConfigSinglePlayerSection, "HeadlightBrightness", value))
            {
                char* end = nullptr;
                const float parsed = std::strtof(value.c_str(), &end);
                while (end && *end && std::isspace(static_cast<unsigned char>(*end)))
                    ++end;
                if (end != value.c_str() && end && *end == '\0' && std::isfinite(parsed))
                    g_HeadlightBrightness = (std::max)(0.25f, (std::min)(2.0f, parsed));
                else
                    Log(L"[HEADLIGHT] Ignoring invalid HeadlightBrightness=%hs\n", value.c_str());
            }

            const char* colourName =
                g_HeadlightColourMode == HeadlightColourMode::Rainbow ? "rainbow" :
                (g_HeadlightColourMode == HeadlightColourMode::Fixed ? "fixed" : "stock");
            const char* beamName =
                g_HeadlightBeamMode == HeadlightBeamMode::Focused ? "focused" :
                (g_HeadlightBeamMode == HeadlightBeamMode::Wide ? "wide" : "stock");
            Log(L"[HEADLIGHT] Baseline configured=%hs player=%hs other=%hs colour=%hs(%.2f,%.2f,%.2f) beam=%hs brightness=%.2f (SP-only; defers to EXU)\n",
                IsHeadlightFeatureConfigured() ? "yes" : "no",
                g_HeadlightPlayerVisibleConfigured ? (g_HeadlightPlayerVisible ? "on" : "off") : "stock",
                g_HeadlightOtherVisibleConfigured ? (g_HeadlightOtherVisible ? "on" : "off") : "stock",
                colourName,
                static_cast<double>(g_HeadlightColourR),
                static_cast<double>(g_HeadlightColourG),
                static_cast<double>(g_HeadlightColourB),
                beamName,
                static_cast<double>(g_HeadlightBrightness));
            RefreshHeadlightState();
        }

        void RevertHeadlightsToBaseline()
        {
            InitializeHeadlightConfig();
            g_HeadlightLastRefreshTick = 0;
            RefreshHeadlightState();
        }

        // Live re-apply for the settings page (ShimSettingApplyGroup::Headlights).
        // RevertHeadlightsToBaseline is the mission-end contract and is the wrong
        // entry point here on two counts:
        //
        //   1. It reaches the ini only through InitializeHeadlightConfig, which
        //      is latched, so after the first pass it re-applies the values the
        //      process started with. Clearing the latch is what makes the four
        //      headlight rows take effect without a restart. The initializer is
        //      re-run whole, so its precedence chain is reproduced exactly:
        //      the ini writes the baseline and the environment overrides
        //      (OPENSHIM_TRACE_HEADLIGHT_LIGHT,
        //      OPENSHIM_DISABLE_HEADLIGHT_FALLOFF_REPAIR) still win over it.
        //
        //   2. RefreshHeadlightState only ever writes the properties the feature
        //      is *currently* overriding, and it restores a light only when that
        //      light goes untouched entirely. Narrowing a setting -- HeadlightColor
        //      back to Stock while Headlights stays on, say -- would therefore
        //      leave the shim's last colour on a light that is still touched for
        //      its visibility. Putting every captured baseline back first makes
        //      the re-apply start from the engine's own values, so a property
        //      that is no longer overridden really does return to stock, and the
        //      recapture that follows records genuine stock values rather than
        //      the shim's own output.
        //
        // The EXU rule is the same one RefreshHeadlightState applies: with EXU
        // loaded the campaign owns these lights, so drop the baselines without
        // writing them back.
        void ReapplyHeadlightConfigFromUserConfig()
        {
            RestoreAllHeadlightStates(!IsExuModuleLoaded());
            g_HeadlightConfigInitialized = false;
            g_HeadlightLastRefreshTick = 0;
            InitializeHeadlightConfig();
        }

    }
}
