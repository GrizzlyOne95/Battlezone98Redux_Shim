// pilot_flashlight.cpp
// BZR Open Shim - player pilot flashlight (SinglePlayer tier), split out of
// bzr_hooks.cpp. The dispatchers that drive it stay there; shared helpers
// and Ogre ABI types come from bzr_hooks_internal.h.
#include "bzr_hooks.h"
#include "light_colour_presets.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "headlight_falloff.h"
#include "hook_engine.h"
#include "patcher.h"
#include "shim_log.h"
#include "planet_environment.h"
#include "render_profile_runtime.h"
#include "sun_baseline.h"

#include <Windows.h>

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

namespace BZROpenShim
{
    namespace Hooks
    {
        // --- Player pilot flashlight (SinglePlayer tier) -----------------------
        //
        // Stock BZR gives every craft whose skeleton carries an `hlgt*` bone a
        // spotlight. FUN_0067f599 creates it through SceneManager::createLight,
        // sets diffuse and specular, attenuation (600, 1, 0.007, 0.0002), type 2
        // (LT_SPOTLIGHT), a bone-derived local position and direction, a 10/20
        // degree cone, disables shadow casting, and attaches it to the entity's
        // own scene node -- not to an animated bone TagPoint. The light then
        // rides that node's transform for free, and the engine destroys it with
        // the scene.
        //
        // No stock pilot skeleton has an `hlgt*` bone, so a pilot on foot never
        // gets one: the live probe of 2026-09-05 found the local Person's render
        // bridge light slot (+0xA8) null for the whole time on foot. This builds
        // the same kind of light, with the same parameters and the same
        // ownership, on the pilot's own scene node.
        //
        // Why the node rather than the first-person gun bone. The same probe
        // walked the live first-person skeleton at bridge +0xCC while the player
        // walked and looked around. `asp21mg1` -- the bone every first-person gun
        // and scope vertex is weighted to -- sits at the skeleton origin with a
        // fixed orientation and moves about 14 cm of weapon bob; it carries no
        // aim whatsoever, and `asp11POV` holds identity orientation throughout.
        // The aim lives in the pilot's SceneNode: its derived orientation swung
        // through the full yaw range and pitched +-14 degrees as the view moved,
        // and its -Z axis matched the walking direction exactly. A TagPoint on
        // the gun bone would therefore put the light at the pilot's feet aimed
        // along a fixed axis, and would go stale whenever the first-person
        // entity stops being animated. The node is both the correct aim frame
        // and the ownership the engine itself uses. The bone is still used the
        // way stock uses it: purely as the source of the node-local offset.
        using FnOgreCreateUnnamedLight = void*(__thiscall*)(void*);
        using FnOgreSetLightType = void(__thiscall*)(void*, int);
        using FnOgreEntityGetSkeleton = void*(__thiscall*)(void*);
        using FnOgreSkeletonGetNumBones = uint16_t(__thiscall*)(void*);
        using FnOgreSkeletonGetBone = void*(__thiscall*)(void*, uint16_t);
        using FnOgreNodeGetName = const std::string*(__thiscall*)(void*);
        using FnOgreNodeGetVector3 = const OgreVector3*(__thiscall*)(void*);

        enum class PilotFlashlightBeamMode
        {
            Stock,
            Focused,
            Wide,
        };

        struct PilotFlashlightOgreApi
        {
            FnOgreCreateUnnamedLight createLight = nullptr;
            FnOgreAttachObject attachObject = nullptr;
            FnOgreSetLightType setType = nullptr;
            FnOgreSetLightColour setLightPosition = nullptr;
            FnOgreSetLightColour setLightDirection = nullptr;
            FnOgreSetVisible setCastShadows = nullptr;
            FnOgreEntityGetSkeleton getSkeleton = nullptr;
            FnOgreSkeletonGetNumBones getNumBones = nullptr;
            FnOgreSkeletonGetBone getBone = nullptr;
            FnOgreNodeGetName getNodeName = nullptr;
            FnOgreNodeGetVector3 getDerivedPosition = nullptr;
            bool usable = false;
        };

        // Render bridge fields, read from the released setup bodies:
        // FUN_0067f599 stores the world entity/node/skeleton and the stock
        // headlight; FUN_0067e6a8 stores the first-person entity and skeleton.
        // Same field as kPersonObjOffset above; named locally so this block
        // reads as the bridge walk the released setup bodies describe.
        static constexpr size_t kPilotBridgeFromPersonOffset = 0x0F0;
        static constexpr size_t kRenderBridgeWorldNodeOffset = 0x098;
        static constexpr size_t kRenderBridgeWorldSkeletonOffset = 0x0A4;
        static constexpr size_t kRenderBridgeHeadlightOffset = 0x0A8;
        static constexpr size_t kRenderBridgeFpSkeletonOffset = 0x0CC;

        static constexpr DWORD kPilotFlashlightRefreshMs = 200;
        // Stock craft headlight curve, verbatim from FUN_0067f599. Only the
        // truncation radius is re-solved for our peak brightness, exactly as
        // the headlight falloff repair does for stock lights.
        static constexpr float kPilotFlashlightStockRange = 600.0f;
        static constexpr float kPilotFlashlightStockConstant = 1.0f;
        static constexpr float kPilotFlashlightStockLinear = 0.007f;
        static constexpr float kPilotFlashlightStockQuadratic = 0.0002f;
        // Fallback eye height, used only when no source bone can be resolved.
        // The stock American pilot's asp11POV bone measured (-0.185, 1.685,
        // -0.06) in skeleton space; this is the same height with no lateral
        // bias so an unknown custom pilot still lights its own front.
        static constexpr float kPilotFlashlightFallbackHeight = 1.685f;

        bool g_PilotFlashlightConfigInitialized = false;
        static bool g_PilotFlashlightEnabled = false;
        static bool g_PilotFlashlightRainbow = false;
        static float g_PilotFlashlightColourR = 1.0f;
        static float g_PilotFlashlightColourG = 1.0f;
        static float g_PilotFlashlightColourB = 1.0f;
        static PilotFlashlightBeamMode g_PilotFlashlightBeamMode =
            PilotFlashlightBeamMode::Stock;
        // Degrees below the aim line. Stock craft headlights tilt down 5; a
        // pilot torch reads better straight down the view, so the default is 0.
        static float g_PilotFlashlightPitchDegrees = 0.0f;
        static float g_PilotFlashlightOffsetX = 0.0f;
        static float g_PilotFlashlightOffsetY = 0.0f;
        static float g_PilotFlashlightOffsetZ = 0.0f;
        // Case-insensitive bone-name suffix. Every stock pilot skeleton is
        // faction-prefixed (asp/bsp/ssp/csp), so a suffix is the only spelling
        // that resolves across factions without a hard-coded handle.
        static std::string g_PilotFlashlightBoneSuffix = "11pov";

        // Live ownership. Pilot lights are retired (hidden and forgotten), not
        // destroyed during simulation: Ogre may retain a light pointer in the
        // current frame's cached light list after SceneManager::destroyLight.
        // Scene teardown remains the sole owner of the final destruction.
        static void* g_PilotFlashlightLight = nullptr;
        static void* g_PilotFlashlightNode = nullptr;
        static void* g_PilotFlashlightSceneManager = nullptr;
        static void* g_PilotFlashlightOwner = nullptr;
        static bool g_PilotFlashlightRuntimeActive = false;
        // Leaving RUN_STARTED does not clear the scene immediately: the local
        // player object and its node stay readable for several seconds before
        // clearScene runs. Without this gate the refresh happily built a second
        // light into a world that was already being torn down (observed:
        // "forgot (left simulation)" followed 229 ms later by "created ...
        // total=2", then "forgot (clearScene)"). Default true so an install
        // where the mission seam could not be hooked behaves as before.
        static bool g_PilotFlashlightWorldRunning = true;
        static bool g_PilotFlashlightApiFailureLogged = false;
        static DWORD g_PilotFlashlightLastRefreshTick = 0;
        static uint32_t g_PilotFlashlightCreations = 0;
        static uint32_t g_PilotFlashlightForgets = 0;
        // An in-place class swap builds the new pilot and then removes the old
        // one, and that removal also destroys and rebuilds the sun. A light
        // created in the same tick has been seen landing at the freed sun's
        // address. Wait until the same pilot and node have been seen for this
        // long before building, so the swap's teardown has finished first.
        static constexpr DWORD kPilotFlashlightSettleMs = 400;
        static void* g_PilotFlashlightCandidateOwner = nullptr;
        static void* g_PilotFlashlightCandidateNode = nullptr;
        static DWORD g_PilotFlashlightCandidateSinceTick = 0;
        // Every ineligibility path below is silent by design -- it runs at the
        // render cadence -- so a feature that never lights up leaves no trace at
        // all. This budgeted opt-in trace names the exact step that refused.
        static bool g_PilotFlashlightTraceEnabled = false;
        static uint32_t g_PilotFlashlightTraceCount = 0;
        static constexpr uint32_t kPilotFlashlightTraceLimit = 40;
        static void TracePilotFlashlight(const wchar_t* stage, void* player, void* node)
        {
            if (!g_PilotFlashlightTraceEnabled ||
                g_PilotFlashlightTraceCount >= kPilotFlashlightTraceLimit)
            {
                return;
            }
            ++g_PilotFlashlightTraceCount;
            char className[128] = {};
            const char* name = player
                ? TryGetRttiClassName(player, className, sizeof(className)) : "<null>";
            Log(L"[PILOTLIGHT] eval %ls player=0x%08X class=%hs node=0x%08X "
                L"light=0x%08X sceneManager=0x%08X\n",
                stage,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(player)), name,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(node)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_PilotFlashlightLight)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(GetOgreSceneManagerRuntime())));
        }

        static PilotFlashlightOgreApi& GetPilotFlashlightOgreApi()
        {
            static PilotFlashlightOgreApi api;
            static bool resolved = false;
            if (resolved)
                return api;
            resolved = true;

            api.createLight = ResolveOgreProc<FnOgreCreateUnnamedLight>(
                "?createLight@SceneManager@Ogre@@UAEPAVLight@2@XZ");
            api.attachObject = ResolveOgreProc<FnOgreAttachObject>(
                "?attachObject@SceneNode@Ogre@@UAEXPAVMovableObject@2@@Z");
            api.setType = ResolveOgreProc<FnOgreSetLightType>(
                "?setType@Light@Ogre@@QAEXW4LightTypes@12@@Z");
            api.setLightPosition = ResolveOgreProc<FnOgreSetLightColour>(
                "?setPosition@Light@Ogre@@QAEXMMM@Z");
            api.setLightDirection = ResolveOgreProc<FnOgreSetLightColour>(
                "?setDirection@Light@Ogre@@QAEXMMM@Z");
            api.setCastShadows = ResolveOgreProc<FnOgreSetVisible>(
                "?setCastShadows@MovableObject@Ogre@@QAEX_N@Z");
            api.getSkeleton = ResolveOgreProc<FnOgreEntityGetSkeleton>(
                "?getSkeleton@Entity@Ogre@@QBEPAVSkeletonInstance@2@XZ");
            api.getNumBones = ResolveOgreProc<FnOgreSkeletonGetNumBones>(
                "?getNumBones@Skeleton@Ogre@@UBEGXZ");
            api.getBone = ResolveOgreProc<FnOgreSkeletonGetBone>(
                "?getBone@Skeleton@Ogre@@UBEPAVBone@2@G@Z");
            api.getNodeName = ResolveOgreProc<FnOgreNodeGetName>(
                "?getName@Node@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@"
                "V?$allocator@D@2@@std@@XZ");
            api.getDerivedPosition = ResolveOgreProc<FnOgreNodeGetVector3>(
                "?_getDerivedPosition@Node@Ogre@@UBEABVVector3@2@XZ");

            // Bone lookup is optional -- without it the light still sits at the
            // fallback eye height. Everything else is required to create and
            // aim the light. Scene teardown owns destruction.
            api.usable =
                api.createLight && api.attachObject &&
                api.setType && api.setLightPosition && api.setLightDirection &&
                api.setCastShadows;
            return api;
        }

        static bool TryReadPilotBridgeField(
            void* person, size_t offset, void*& outValue)
        {
            outValue = nullptr;
            if (!person)
                return false;
            __try
            {
                auto* bridge = *reinterpret_cast<void* const*>(
                    reinterpret_cast<const uint8_t*>(person) +
                    kPilotBridgeFromPersonOffset);
                if (!bridge)
                    return false;
                outValue = *reinterpret_cast<void* const*>(
                    reinterpret_cast<const uint8_t*>(bridge) + offset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outValue = nullptr;
                return false;
            }
        }

        // True when the local player object is a Person -- i.e. on foot. The
        // object is a Craft while piloting, and the light must not exist then.
        bool IsPilotOnFoot(void* player)
        {
            if (!player)
                return false;
            char className[128] = {};
            const char* name = TryGetRttiClassName(player, className, sizeof(className));
            return name && std::strstr(name, "Person") != nullptr;
        }

        static void PilotFlashlightBeamAngles(float& outInner, float& outOuter)
        {
            switch (g_PilotFlashlightBeamMode)
            {
            case PilotFlashlightBeamMode::Focused:
                outInner = 0.12f;
                outOuter = 0.28f;
                break;
            case PilotFlashlightBeamMode::Wide:
                outInner = 0.40f;
                outOuter = 0.85f;
                break;
            case PilotFlashlightBeamMode::Stock:
            default:
                // Slightly wider than the stock craft cone (10/20 degrees),
                // because a hand torch lights the ground you are walking on.
                outInner = 0.22f;
                outOuter = 0.50f;
                break;
            }
        }

        // One SEH-guarded raw bone read. Kept POD-only and separate because a
        // function that uses __try may not require object unwinding, and the
        // suffix match below wants std::string.
        static bool TryReadPilotBoneSample(
            const PilotFlashlightOgreApi& api,
            void* skeleton,
            uint16_t index,
            char* outName,
            size_t outNameSize,
            OgreVector3& outPosition)
        {
            __try
            {
                void* bone = api.getBone(skeleton, index);
                if (!bone)
                    return false;
                const std::string* boneName = api.getNodeName(bone);
                if (!boneName)
                    return false;
                const char* chars = boneName->c_str();
                const size_t length = boneName->size();
                if (length == 0 || length >= outNameSize)
                    return false;
                std::memcpy(outName, chars, length);
                outName[length] = '\0';

                const OgreVector3* derived = api.getDerivedPosition(bone);
                if (!derived)
                    return false;
                outPosition = *derived;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool TryReadPilotBoneCount(
            const PilotFlashlightOgreApi& api, void* skeleton, uint16_t& outCount)
        {
            __try
            {
                outCount = api.getNumBones(skeleton);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outCount = 0;
                return false;
            }
        }

        // Locates the source bone by case-insensitive name suffix and reports
        // its skeleton-space position. Falls through to the world skeleton when
        // the first-person one has no match, and reports failure rather than a
        // guess so the caller can use the documented fallback height.
        static bool TryResolvePilotFlashlightBoneOffset(
            void* person, OgreVector3& outPosition, char* outBoneName, size_t boneNameSize)
        {
            if (outBoneName && boneNameSize)
                outBoneName[0] = '\0';
            auto& api = GetPilotFlashlightOgreApi();
            if (!api.getNumBones || !api.getBone || !api.getNodeName ||
                !api.getDerivedPosition)
            {
                return false;
            }

            const size_t suffixLength = g_PilotFlashlightBoneSuffix.size();
            if (suffixLength == 0)
                return false;

            void* skeletons[2] = { nullptr, nullptr };
            TryReadPilotBridgeField(person, kRenderBridgeFpSkeletonOffset, skeletons[0]);
            TryReadPilotBridgeField(person, kRenderBridgeWorldSkeletonOffset, skeletons[1]);

            for (void* skeleton : skeletons)
            {
                if (!skeleton)
                    continue;
                uint16_t boneCount = 0;
                if (!TryReadPilotBoneCount(api, skeleton, boneCount))
                    continue;
                for (uint16_t i = 0; i < boneCount; ++i)
                {
                    char name[64] = {};
                    OgreVector3 position = {};
                    if (!TryReadPilotBoneSample(api, skeleton, i, name, sizeof(name), position))
                        continue;
                    const size_t nameLength = std::strlen(name);
                    if (nameLength < suffixLength)
                        continue;
                    if (_strnicmp(name + (nameLength - suffixLength),
                                  g_PilotFlashlightBoneSuffix.c_str(),
                                  suffixLength) != 0)
                    {
                        continue;
                    }
                    outPosition = position;
                    if (outBoneName && boneNameSize)
                    {
                        const size_t copy = (std::min)(nameLength, boneNameSize - 1);
                        std::memcpy(outBoneName, name, copy);
                        outBoneName[copy] = '\0';
                    }
                    return true;
                }
            }
            return false;
        }

        // Drops every reference without touching Ogre. Used when the scene that
        // owns the light is being destroyed: the engine frees the light with the
        // scene, so calling destroyLight here would run through freed memory.
        void ForgetPilotFlashlight(const wchar_t* reason)
        {
            if (!g_PilotFlashlightLight && !g_PilotFlashlightNode)
                return;
            ++g_PilotFlashlightForgets;
            Log(L"[PILOTLIGHT] forgot light=0x%08X node=0x%08X (%ls)\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_PilotFlashlightLight)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_PilotFlashlightNode)),
                reason ? reason : L"unspecified");
            g_PilotFlashlightLight = nullptr;
            g_PilotFlashlightNode = nullptr;
            g_PilotFlashlightSceneManager = nullptr;
            g_PilotFlashlightOwner = nullptr;
        }

        // A destroyed Ogre object leaves its allocation readable for a while,
        // so a null check proves nothing. A live Light's vptr points into
        // OgreMain.dll's image; a freed or recycled allocation's does not.
        static bool PilotFlashlightLightLooksLive(void* light)
        {
            if (!light)
                return false;
            uintptr_t ogreBase = 0;
            uintptr_t ogreEnd = 0;
            if (!TryGetOgreModuleRange(ogreBase, ogreEnd))
                return false;
            __try
            {
                const uintptr_t vptr = *reinterpret_cast<const uintptr_t*>(light);
                return vptr >= ogreBase && vptr < ogreEnd;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Mission lifecycle seam. Leaving simulation destroys every Ogre object
        // with no teardown callback, so the light is forgotten, never destroyed,
        // and nothing new is built until a world is running again.
        static void NoteSunMissionBoundary();

        void PilotFlashlightNotifyMissionRunStateChanged(bool enteringSimulation)
        {
            g_PilotFlashlightWorldRunning = enteringSimulation;
            if (!enteringSimulation)
            {
                ForgetPilotFlashlight(L"left simulation");
                NoteSunMissionBoundary();
            }
        }

        static void RetirePilotFlashlight(const wchar_t* reason)
        {
            if (!g_PilotFlashlightLight)
            {
                ForgetPilotFlashlight(reason);
                return;
            }

            // Only the manager that created the light may free it, and only
            // while it is still the live one. Anything else means the scene has
            // already gone and the light with it.
            void* const liveManager = GetOgreSceneManagerRuntime();
            if (!liveManager || liveManager != g_PilotFlashlightSceneManager)
            {
                ForgetPilotFlashlight(L"scene manager changed");
                return;
            }

            if (!PilotFlashlightLightLooksLive(g_PilotFlashlightLight))
            {
                ForgetPilotFlashlight(L"light no longer looks live");
                return;
            }

            auto& hl = GetHeadlightOgreApi();
            bool hidden = false;
            DWORD exceptionCode = 0;
            __try
            {
                // Do not detach through the recorded node: boarding or script
                // removal may already have freed it. More importantly, do not
                // destroy the light here. The renderer can retain it in the
                // current frame's light list; destroying it produced a proven
                // PopulateLightList use-after-free. Hiding is safe, and Ogre's
                // normal scene teardown reclaims the retired object.
                if (hl.setVisible)
                {
                    hl.setVisible(g_PilotFlashlightLight, false);
                    hidden = true;
                }
            }
            __except (exceptionCode = GetExceptionCode(), EXCEPTION_EXECUTE_HANDLER)
            {
                hidden = false;
            }

            if (hidden)
            {
                Log(L"[PILOTLIGHT] retired light=0x%08X (%ls)\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_PilotFlashlightLight)),
                    reason ? reason : L"unspecified");
            }
            else
            {
                Log(L"[PILOTLIGHT] retire hide FAILED light=0x%08X code=0x%08X (%ls)\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_PilotFlashlightLight)),
                    static_cast<unsigned>(exceptionCode),
                    reason ? reason : L"unspecified");
            }
            g_PilotFlashlightLight = nullptr;
            g_PilotFlashlightNode = nullptr;
            g_PilotFlashlightSceneManager = nullptr;
            g_PilotFlashlightOwner = nullptr;
        }

        static void ApplyPilotFlashlightAppearance(float r, float g, float b)
        {
            auto& api = GetPilotFlashlightOgreApi();
            auto& hl = GetHeadlightOgreApi();
            if (!g_PilotFlashlightLight || !hl.setDiffuse || !hl.setSpecular ||
                !hl.setRange || !hl.setAttenuation)
            {
                return;
            }

            float inner = 0.0f;
            float outer = 0.0f;
            PilotFlashlightBeamAngles(inner, outer);

            HeadlightFalloff::Attenuation stock = {};
            stock.range = kPilotFlashlightStockRange;
            stock.constant = kPilotFlashlightStockConstant;
            stock.linear = kPilotFlashlightStockLinear;
            stock.quadratic = kPilotFlashlightStockQuadratic;
            const float peak = (std::max)((std::max)(r, g), b);
            const HeadlightFalloff::Plan plan = HeadlightFalloff::BuildPlan(
                stock, peak, HeadlightFalloff::kSmoothSpotFalloff);

            __try
            {
                hl.setDiffuse(g_PilotFlashlightLight, r, g, b);
                hl.setSpecular(g_PilotFlashlightLight, r, g, b);
                hl.setAttenuation(
                    g_PilotFlashlightLight,
                    plan.attenuation.range,
                    plan.attenuation.constant,
                    plan.attenuation.linear,
                    plan.attenuation.quadratic);
                hl.setRange(g_PilotFlashlightLight, &inner, &outer, plan.falloff);
                if (api.setType)
                    api.setType(g_PilotFlashlightLight, 2);  // LT_SPOTLIGHT
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        static bool CreatePilotFlashlight(void* person, void* node)
        {
            auto& api = GetPilotFlashlightOgreApi();
            if (!api.usable)
            {
                if (!g_PilotFlashlightApiFailureLogged)
                {
                    g_PilotFlashlightApiFailureLogged = true;
                    Log(L"[PILOTLIGHT] Ogre light API unresolved; feature stands down\n");
                }
                return false;
            }

            void* const sceneManager = GetOgreSceneManagerRuntime();
            if (!sceneManager)
            {
                TracePilotFlashlight(L"no-scene-manager", person, node);
                return false;
            }

            OgreVector3 bonePosition = { 0.0f, kPilotFlashlightFallbackHeight, 0.0f };
            char boneName[64] = {};
            const bool haveBone = TryResolvePilotFlashlightBoneOffset(
                person, bonePosition, boneName, sizeof(boneName));

            const float px = bonePosition.x + g_PilotFlashlightOffsetX;
            const float py = bonePosition.y + g_PilotFlashlightOffsetY;
            const float pz = bonePosition.z + g_PilotFlashlightOffsetZ;

            // The pilot node's -Z is its facing: the probe's derived forward
            // matched the walking direction exactly. Pitch is applied about the
            // node's X so a positive value raises the beam.
            const float pitch = g_PilotFlashlightPitchDegrees * 3.14159265358979f / 180.0f;
            const float dx = 0.0f;
            const float dy = std::sin(pitch);
            const float dz = -std::cos(pitch);

            void* light = nullptr;
            __try
            {
                light = api.createLight(sceneManager);
                if (light)
                {
                    api.setType(light, 2);  // LT_SPOTLIGHT
                    api.setLightPosition(light, px, py, pz);
                    api.setLightDirection(light, dx, dy, dz);
                    api.setCastShadows(light, false);
                    api.attachObject(node, light);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                light = nullptr;
            }

            if (!light)
            {
                Log(L"[PILOTLIGHT] createLight failed (sceneManager=0x%08X node=0x%08X)\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sceneManager)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(node)));
                return false;
            }

            g_PilotFlashlightLight = light;
            g_PilotFlashlightNode = node;
            g_PilotFlashlightSceneManager = sceneManager;
            g_PilotFlashlightOwner = person;
            ++g_PilotFlashlightCreations;

            Log(L"[PILOTLIGHT] created light=0x%08X node=0x%08X bone=%hs "
                L"local=(%.3f,%.3f,%.3f) dir=(%.3f,%.3f,%.3f) total=%u\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(light)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(node)),
                haveBone ? boneName : "<fallback>",
                static_cast<double>(px), static_cast<double>(py), static_cast<double>(pz),
                static_cast<double>(dx), static_cast<double>(dy), static_cast<double>(dz),
                static_cast<unsigned>(g_PilotFlashlightCreations));
            return true;
        }

        void RefreshPilotFlashlightState()
        {
            // Deliberately NOT gated on EXU. The EXU stand-down on stock
            // headlights exists because both write the same engine-owned light;
            // this light is created by the shim, belongs to no ODF or campaign
            // script, and nothing else can touch it.
            const bool wantActive =
                g_PilotFlashlightEnabled && ReadLocalPlayerNetIdValue() == 0;
            if (!wantActive)
            {
                if (g_PilotFlashlightRuntimeActive || g_PilotFlashlightLight)
                {
                    RetirePilotFlashlight(L"feature inactive");
                    Log(L"[PILOTLIGHT] Stood down (%hs)\n",
                        g_PilotFlashlightEnabled ? "multiplayer" : "disabled");
                }
                g_PilotFlashlightRuntimeActive = false;
                g_PilotFlashlightLastRefreshTick = 0;
                return;
            }

            if (!g_PilotFlashlightRuntimeActive)
            {
                g_PilotFlashlightRuntimeActive = true;
                g_PilotFlashlightLastRefreshTick = 0;
                Log(L"[PILOTLIGHT] Pilot flashlight active (SP-only)\n");
            }

            const DWORD now = GetTickCount();
            if (g_PilotFlashlightLastRefreshTick != 0 &&
                static_cast<DWORD>(now - g_PilotFlashlightLastRefreshTick) <
                    kPilotFlashlightRefreshMs)
            {
                return;
            }
            g_PilotFlashlightLastRefreshTick = now;

            if (!g_PilotFlashlightWorldRunning)
            {
                TracePilotFlashlight(L"world-not-running", nullptr, nullptr);
                // Forget, never destroy: the scene owns the light and is about
                // to free it along with everything else.
                ForgetPilotFlashlight(L"world not running");
                return;
            }

            void* const player = TryGetHeadlightPlayerObject();
            if (!player || !IsLiveHeadlightObjectSlot(player) || !IsPilotOnFoot(player))
            {
                TracePilotFlashlight(L"not-on-foot", player, nullptr);
                RetirePilotFlashlight(L"player is not on foot");
                return;
            }

            void* node = nullptr;
            if (!TryReadPilotBridgeField(player, kRenderBridgeWorldNodeOffset, node) || !node)
            {
                TracePilotFlashlight(L"no-scene-node", player, node);
                RetirePilotFlashlight(L"pilot has no scene node");
                return;
            }

            // A modded pilot mesh could carry an `hlgt*` bone and get a stock
            // engine light of its own; leave that one alone rather than lighting
            // the pilot twice.
            void* stockHeadlight = nullptr;
            TryReadPilotBridgeField(player, kRenderBridgeHeadlightOffset, stockHeadlight);
            if (stockHeadlight)
            {
                TracePilotFlashlight(L"stock-headlight-present", player, node);
                RetirePilotFlashlight(L"pilot already has a stock headlight");
                return;
            }

            if (g_PilotFlashlightLight &&
                (g_PilotFlashlightNode != node || g_PilotFlashlightOwner != player))
            {
                // Same world, different pilot object or node -- the previous
                // light belongs to an object that is gone.
                RetirePilotFlashlight(L"pilot object or node changed");
            }

            TracePilotFlashlight(
                g_PilotFlashlightLight ? L"eligible-have-light" : L"eligible-creating",
                player, node);
            if (!g_PilotFlashlightLight)
            {
                if (g_PilotFlashlightCandidateOwner != player ||
                    g_PilotFlashlightCandidateNode != node)
                {
                    g_PilotFlashlightCandidateOwner = player;
                    g_PilotFlashlightCandidateNode = node;
                    g_PilotFlashlightCandidateSinceTick = now;
                    TracePilotFlashlight(L"settling", player, node);
                    return;
                }
                if (static_cast<DWORD>(now - g_PilotFlashlightCandidateSinceTick) <
                    kPilotFlashlightSettleMs)
                    return;
                if (!CreatePilotFlashlight(player, node))
                    return;
            }

            float r = g_PilotFlashlightColourR;
            float g = g_PilotFlashlightColourG;
            float b = g_PilotFlashlightColourB;
            if (g_PilotFlashlightRainbow)
            {
                const float hue = static_cast<float>(now % 5000u) / 5000.0f;
                HueToHeadlightRgb(hue, r, g, b);
                r *= g_PilotFlashlightColourR;
                g *= g_PilotFlashlightColourG;
                b *= g_PilotFlashlightColourB;
            }
            ApplyPilotFlashlightAppearance(r, g, b);
        }

        static bool ParsePilotFlashlightVector3(
            const std::string& value, float& outX, float& outY, float& outZ)
        {
            float parsed[3] = {};
            size_t index = 0;
            size_t cursor = 0;
            while (index < 3 && cursor <= value.size())
            {
                const size_t comma = value.find(',', cursor);
                const std::string part = value.substr(
                    cursor, comma == std::string::npos ? std::string::npos : comma - cursor);
                const char* begin = part.c_str();
                char* end = nullptr;
                const float number = std::strtof(begin, &end);
                if (end == begin || !std::isfinite(number))
                    return false;
                parsed[index++] = number;
                if (comma == std::string::npos)
                    break;
                cursor = comma + 1;
            }
            if (index != 3)
                return false;
            outX = parsed[0];
            outY = parsed[1];
            outZ = parsed[2];
            return true;
        }

        // Same vocabulary as HeadlightColor so both rows can share the
        // settings-page value list. "Stock" is the brightness the engine itself
        // writes for a craft headlight (1,1,1); the named presets follow the
        // shim's brighter headlight palette so a pilot torch and a vehicle
        // headlight of the same name look alike.
        static bool ParsePilotFlashlightColour(const std::string& raw)
        {
            std::string value = raw;
            for (char& c : value)
                c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

            g_PilotFlashlightRainbow = false;
            if (value == "stock" || value == "default")
            {
                g_PilotFlashlightColourR = 1.0f;
                g_PilotFlashlightColourG = 1.0f;
                g_PilotFlashlightColourB = 1.0f;
                return true;
            }
            if (value == "rainbow")
            {
                g_PilotFlashlightRainbow = true;
                g_PilotFlashlightColourR = 5.0f;
                g_PilotFlashlightColourG = 5.0f;
                g_PilotFlashlightColourB = 5.0f;
                return true;
            }

            if (LightColourPresets::TryFind(
                    value.c_str(), g_PilotFlashlightColourR, g_PilotFlashlightColourG, g_PilotFlashlightColourB))
                return true;

            float r = 0.0f;
            float g = 0.0f;
            float b = 0.0f;
            if (ParsePilotFlashlightVector3(value, r, g, b) &&
                r >= 0.0f && g >= 0.0f && b >= 0.0f &&
                r <= 20.0f && g <= 20.0f && b <= 20.0f)
            {
                g_PilotFlashlightColourR = r;
                g_PilotFlashlightColourG = g;
                g_PilotFlashlightColourB = b;
                return true;
            }
            return false;
        }

        static bool ParsePilotFlashlightBeam(const std::string& raw)
        {
            std::string value = raw;
            for (char& c : value)
                c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            if (value == "stock")
                g_PilotFlashlightBeamMode = PilotFlashlightBeamMode::Stock;
            else if (value == "focused")
                g_PilotFlashlightBeamMode = PilotFlashlightBeamMode::Focused;
            else if (value == "wide")
                g_PilotFlashlightBeamMode = PilotFlashlightBeamMode::Wide;
            else
                return false;
            return true;
        }

        void InitializePilotFlashlightConfig()
        {
            if (g_PilotFlashlightConfigInitialized)
                return;
            g_PilotFlashlightConfigInitialized = true;

            bool boolValue = false;
            if (TryGetUserConfigBool(
                    kUserConfigSinglePlayerSection, "PilotFlashlight", boolValue))
            {
                g_PilotFlashlightEnabled = boolValue;
            }
            if (EnvFlagEnabled("OPENSHIM_PILOT_FLASHLIGHT"))
                g_PilotFlashlightEnabled = true;
            if (TryGetUserConfigBool("Diagnostics", "PilotFlashlightTrace", boolValue))
                g_PilotFlashlightTraceEnabled = boolValue;
            if (EnvFlagEnabled("OPENSHIM_TRACE_PILOT_FLASHLIGHT"))
                g_PilotFlashlightTraceEnabled = true;

            std::string value;
            if (TryGetUserConfigString(
                    kUserConfigSinglePlayerSection, "PilotFlashlightColor", value) &&
                !ParsePilotFlashlightColour(value))
            {
                Log(L"[PILOTLIGHT] Ignoring invalid PilotFlashlightColor=%hs\n", value.c_str());
            }
            if (TryGetUserConfigString(
                    kUserConfigSinglePlayerSection, "PilotFlashlightBeam", value) &&
                !ParsePilotFlashlightBeam(value))
            {
                Log(L"[PILOTLIGHT] Ignoring invalid PilotFlashlightBeam=%hs\n", value.c_str());
            }
            if (TryGetUserConfigString(
                    kUserConfigSinglePlayerSection, "PilotFlashlightOffset", value) &&
                !ParsePilotFlashlightVector3(
                    value, g_PilotFlashlightOffsetX,
                    g_PilotFlashlightOffsetY, g_PilotFlashlightOffsetZ))
            {
                Log(L"[PILOTLIGHT] Ignoring invalid PilotFlashlightOffset=%hs\n", value.c_str());
            }
            if (TryGetUserConfigString(
                    kUserConfigSinglePlayerSection, "PilotFlashlightPitch", value))
            {
                const char* begin = value.c_str();
                char* end = nullptr;
                const float degrees = std::strtof(begin, &end);
                if (end != begin && std::isfinite(degrees) &&
                    degrees >= -80.0f && degrees <= 80.0f)
                {
                    g_PilotFlashlightPitchDegrees = degrees;
                }
                else
                {
                    Log(L"[PILOTLIGHT] Ignoring invalid PilotFlashlightPitch=%hs\n",
                        value.c_str());
                }
            }
            if (TryGetUserConfigString(
                    kUserConfigSinglePlayerSection, "PilotFlashlightBone", value) &&
                !value.empty() && value.size() < 32)
            {
                for (char& c : value)
                    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                g_PilotFlashlightBoneSuffix = value;
            }

            const char* beamName =
                g_PilotFlashlightBeamMode == PilotFlashlightBeamMode::Focused ? "focused" :
                (g_PilotFlashlightBeamMode == PilotFlashlightBeamMode::Wide ? "wide" : "stock");
            Log(L"[PILOTLIGHT] Baseline enabled=%hs colour=%hs(%.2f,%.2f,%.2f) beam=%hs "
                L"bone=*%hs offset=(%.3f,%.3f,%.3f) pitch=%.1f (SP-only)\n",
                g_PilotFlashlightEnabled ? "yes" : "no",
                g_PilotFlashlightRainbow ? "rainbow" : "fixed",
                static_cast<double>(g_PilotFlashlightColourR),
                static_cast<double>(g_PilotFlashlightColourG),
                static_cast<double>(g_PilotFlashlightColourB),
                beamName,
                g_PilotFlashlightBoneSuffix.c_str(),
                static_cast<double>(g_PilotFlashlightOffsetX),
                static_cast<double>(g_PilotFlashlightOffsetY),
                static_cast<double>(g_PilotFlashlightOffsetZ),
                static_cast<double>(g_PilotFlashlightPitchDegrees));
            RefreshPilotFlashlightState();
        }

        // --- Sun replacement watch -----------------------------------------
        // The sun (terrain_masterlight) lives in one engine global. Destroying
        // a GameObject with render info deletes it -- RemoveObject of the old
        // pilot in an in-place class swap does -- and the next frame builds a
        // new one at a new address. Every cached per-object light list still
        // names the old one until something marks the lists dirty, so the
        // world can draw without its sun. Mark them dirty whenever the global
        // changes within one scene. Pure render state: no simulation effect,
        // so it is not gated on SP.
        using FnOgreNotifyLightsDirty = void(__thiscall*)(void*);
        static uint32_t g_SunLightGlobalAddr = 0;
        static FnOgreNotifyLightsDirty g_NotifyLightsDirty = nullptr;
        static int g_SunWatchBound = 0;  // 0 untried, 1 bound, -1 stood down
        static void* g_LastSunLight = nullptr;
        static void* g_LastSunSceneManager = nullptr;
        static uint32_t g_SunReplacements = 0;
        static uint32_t g_RejectedSunLights = 0;
        static const void* g_LastRejectedSunLight = nullptr;
        static constexpr uint32_t kSunReplacementLogLimit = 20;

        // The allocator can put a rebuilt sun at the address of the one it
        // replaced, and then the pointer alone reads as "unchanged" and the
        // saved overrides are snapshotted away. Every sun is built by one
        // engine function, so counting its calls gives each sun a generation.
        // Without the detour the count stays 0 and only the address is used.
        using FnSunBuild = void(__cdecl*)();
        static InlineDetour32 g_SunBuildDetour = {};
        static FnSunBuild g_SunBuildOriginal = nullptr;
        static volatile LONG g_SunBuilds = 0;
        static LONG g_LastSunBuild = 0;
        static int g_SunBuildHook = 0;  // 0 untried, 1 installed, -1 stood down

        static void __cdecl SunBuildHook()
        {
            g_SunBuildOriginal();
            InterlockedIncrement(&g_SunBuilds);
        }

        // Called from the frame callback; the builder runs only on this
        // thread (the frame render and the object teardown that calls
        // RefreshTerrainMasterLight), so the write needs no thread freeze,
        // which deadlocks from here. Waits for the first frame to be noted.
        static void InstallSunBuildHook()
        {
            if (g_SunBuildHook != 0)
                return;
            HookEngine::FrameThreadSitesScope frameSites;
            if (!frameSites.Engaged())
                return;
            uint32_t address = 0;
            const HookEngine::EngineRow rows[] = {
                { "TerrainMasterLightBuild", &address },
            };
            static const uint8_t kPrologue[] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };
            if (!HookEngine::BindEngineRows("Sun build generation", rows) ||
                !InstallInlineDetour32(g_SunBuildDetour, address,
                                       reinterpret_cast<void*>(SunBuildHook),
                                       sizeof(kPrologue), kPrologue, sizeof(kPrologue)))
            {
                g_SunBuildHook = -1;
                Log(L"[SUNWATCH] sun build hook unavailable; a sun rebuilt at the same address is not restored\n");
                return;
            }
            g_SunBuildOriginal = reinterpret_cast<FnSunBuild>(g_SunBuildDetour.trampoline);
            g_SunBuildHook = 1;
            Log(L"[SUNWATCH] sun build hook installed at 0x%08X\n", static_cast<uint32_t>(address));
        }

        static bool BindSunWatch()
        {
            if (g_SunWatchBound == 0)
            {
                const HookEngine::EngineRow rows[] = {
                    { "TerrainMasterLight", &g_SunLightGlobalAddr },
                };
                g_NotifyLightsDirty = ResolveOgreProc<FnOgreNotifyLightsDirty>(
                    "?_notifyLightsDirty@SceneManager@Ogre@@UAEXXZ");
                g_SunWatchBound =
                    HookEngine::BindEngineRows("Sun light watch", rows) && g_NotifyLightsDirty
                        ? 1 : -1;
                if (g_SunWatchBound < 0)
                    Log(L"[SUNWATCH] stood down (row or Ogre export unresolved)\n");
            }
            return g_SunWatchBound > 0;
        }

        static void* ReadSunLight()
        {
            __try
            {
                return *reinterpret_cast<void* const*>(
                    static_cast<uintptr_t>(g_SunLightGlobalAddr));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        // TerrainMasterLight can outlive the light it names: a co-op crash dump
        // had it pointing at a recycled allocation (a D3D11 shader resource
        // view), and the Light setters below wrote the restored sun into it.
        // SEH cannot catch a write that lands in readable memory, so the sun is
        // only touched while both of its vtable pointers are Ogre::Light's. A
        // destroyed Light carries its base classes' vtables after the
        // destructor runs, so this also rejects a freed, not yet reused sun.
        static bool IsLiveOgreLight(const void* light)
        {
            static const void* s_ShadowCasterVtable = nullptr;
            static const void* s_AnimableVtable = nullptr;
            static int s_Bound = 0;
            if (s_Bound == 0)
            {
                s_ShadowCasterVtable = ResolveOgreProc<const void*>("??_7Light@Ogre@@6BShadowCaster@1@@");
                s_AnimableVtable = ResolveOgreProc<const void*>("??_7Light@Ogre@@6BAnimableObject@1@@");
                s_Bound = s_ShadowCasterVtable && s_AnimableVtable ? 1 : -1;
                if (s_Bound < 0)
                    Log(L"[SUNWATCH] Ogre::Light vtables unresolved; the sun is never read or written\n");
            }
            if (s_Bound < 0 || !light)
                return false;
            __try
            {
                const void* const* const vptrs = static_cast<const void* const*>(light);
                return vptrs[0] == s_ShadowCasterVtable && vptrs[1] == s_AnimableVtable;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool NotifySceneLightsDirty(void* sceneManager)
        {
            __try
            {
                g_NotifyLightsDirty(sceneManager);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // --- Sun rebuild restore ---------------------------------------------
        // The rebuilt sun re-reads stock Sun_Ambient/Sun_Diffuse/Sun_Specular
        // (0x0067DD60), takes its direction from the engine sun vector, forces
        // a 128 m shadow far distance and leaves powerScale at Ogre's 1.0, so
        // anything a mod pushed through EXU (SetSunDiffuse, SetSunDirection,
        // SetAmbientLight, ...) is wiped a few seconds into a mission. EXU keeps
        // no cache, so snapshot the live values once per frame and put back the
        // ones the rebuild changed. Direction is put back only while the engine
        // sun vector is unchanged: if it moved, the rebuild was a deliberate
        // RefreshTerrainMasterLight (time of day) and the new direction stands.
        // [Fixes] SunRebuildRestore, default on.
        using FnOgreSetLightFloat = void(__thiscall*)(void*, float);
        using FnOgreGetAmbientLight = const OgreColourValue*(__thiscall*)(void*);
        using FnOgreSetAmbientLight = void(__thiscall*)(void*, const OgreColourValue&);

        struct SunRestoreApi
        {
            FnOgreGetLightColour getDiffuse = nullptr;
            FnOgreSetLightColour setDiffuse = nullptr;
            FnOgreGetLightColour getSpecular = nullptr;
            FnOgreSetLightColour setSpecular = nullptr;
            FnOgreGetLightVector3 getDirection = nullptr;
            FnOgreSetLightColour setDirection = nullptr;  // (x, y, z) floats
            FnOgreGetLightFloat getPowerScale = nullptr;
            FnOgreSetLightFloat setPowerScale = nullptr;
            FnOgreGetLightFloat getShadowFar = nullptr;
            FnOgreSetLightFloat setShadowFar = nullptr;
            FnOgreGetAmbientLight getAmbient = nullptr;
            FnOgreSetAmbientLight setAmbient = nullptr;
        };

        // Plain data only: the guarded cores copy it inside __try.
        struct SunLightState
        {
            OgreColourValue diffuse;
            OgreColourValue specular;
            OgreColourValue ambient;
            OgreVector3 direction;
            float powerScale;
            float shadowFar;
            float engineSun[3];
        };

        enum SunField : uint32_t
        {
            kSunFieldDiffuse = 1u << 0,
            kSunFieldSpecular = 1u << 1,
            kSunFieldDirection = 1u << 2,
            kSunFieldPowerScale = 1u << 3,
            kSunFieldShadowFar = 1u << 4,
            kSunFieldAmbient = 1u << 5,
        };

        static SunRestoreApi g_SunRestore;
        static uint32_t g_SunDirectionStateAddr = 0;
        static int g_SunRestoreBound = 0;  // 0 untried, 1 bound, -1 off or stood down
        static SunLightState g_SunSnapshot = {};
        static void* g_SunSnapshotLight = nullptr;
        static bool g_SunSnapshotValid = false;

        static bool BindSunRestore()
        {
            if (g_SunRestoreBound != 0)
                return g_SunRestoreBound > 0;

            bool enabled = true;
            TryGetUserConfigBool("Fixes", "SunRebuildRestore", enabled);
            if (!enabled)
            {
                g_SunRestoreBound = -1;
                Log(L"[SUNWATCH] restore off ([Fixes] SunRebuildRestore=0)\n");
                return false;
            }

            SunRestoreApi& api = g_SunRestore;
            api.getDiffuse = ResolveOgreProc<FnOgreGetLightColour>(
                "?getDiffuseColour@Light@Ogre@@QBEABVColourValue@2@XZ");
            api.setDiffuse = ResolveOgreProc<FnOgreSetLightColour>(
                "?setDiffuseColour@Light@Ogre@@QAEXMMM@Z");
            api.getSpecular = ResolveOgreProc<FnOgreGetLightColour>(
                "?getSpecularColour@Light@Ogre@@QBEABVColourValue@2@XZ");
            api.setSpecular = ResolveOgreProc<FnOgreSetLightColour>(
                "?setSpecularColour@Light@Ogre@@QAEXMMM@Z");
            api.getDirection = ResolveOgreProc<FnOgreGetLightVector3>(
                "?getDirection@Light@Ogre@@QBEABVVector3@2@XZ");
            api.setDirection = ResolveOgreProc<FnOgreSetLightColour>(
                "?setDirection@Light@Ogre@@QAEXMMM@Z");
            api.getPowerScale = ResolveOgreProc<FnOgreGetLightFloat>(
                "?getPowerScale@Light@Ogre@@QBEMXZ");
            api.setPowerScale = ResolveOgreProc<FnOgreSetLightFloat>(
                "?setPowerScale@Light@Ogre@@QAEXM@Z");
            api.getShadowFar = ResolveOgreProc<FnOgreGetLightFloat>(
                "?getShadowFarDistance@Light@Ogre@@QBEMXZ");
            api.setShadowFar = ResolveOgreProc<FnOgreSetLightFloat>(
                "?setShadowFarDistance@Light@Ogre@@QAEXM@Z");
            api.getAmbient = ResolveOgreProc<FnOgreGetAmbientLight>(
                "?getAmbientLight@SceneManager@Ogre@@QBEABVColourValue@2@XZ");
            api.setAmbient = ResolveOgreProc<FnOgreSetAmbientLight>(
                "?setAmbientLight@SceneManager@Ogre@@QAEXABVColourValue@2@@Z");

            const bool exportsOk =
                api.getDiffuse && api.setDiffuse && api.getSpecular && api.setSpecular &&
                api.getDirection && api.setDirection && api.getPowerScale &&
                api.setPowerScale && api.getShadowFar && api.setShadowFar &&
                api.getAmbient && api.setAmbient;
            const HookEngine::EngineRow rows[] = {
                { "SunDirectionState", &g_SunDirectionStateAddr },
            };
            const bool rowOk = HookEngine::BindEngineRows("Sun rebuild restore", rows);

            g_SunRestoreBound = exportsOk && rowOk ? 1 : -1;
            if (g_SunRestoreBound < 0)
            {
                Log(L"[SUNWATCH] restore stood down (%ls%ls%ls); light lists are still marked dirty\n",
                    exportsOk ? L"" : L"Ogre export unresolved",
                    !exportsOk && !rowOk ? L", " : L"",
                    rowOk ? L"" : L"SunDirectionState row unresolved");
            }
            return g_SunRestoreBound > 0;
        }

        __declspec(noinline) static bool ReadSunLightStateGuarded(
            void* light, void* sceneManager, uint32_t engineSunAddr, SunLightState* out)
        {
            __try
            {
                const OgreColourValue* const diffuse = g_SunRestore.getDiffuse(light);
                const OgreColourValue* const specular = g_SunRestore.getSpecular(light);
                const OgreVector3* const direction = g_SunRestore.getDirection(light);
                const OgreColourValue* const ambient = g_SunRestore.getAmbient(sceneManager);
                if (!diffuse || !specular || !direction || !ambient)
                    return false;
                out->diffuse = *diffuse;
                out->specular = *specular;
                out->direction = *direction;
                out->ambient = *ambient;
                out->powerScale = g_SunRestore.getPowerScale(light);
                out->shadowFar = g_SunRestore.getShadowFar(light);
                const float* const engineSun =
                    reinterpret_cast<const float*>(static_cast<uintptr_t>(engineSunAddr));
                out->engineSun[0] = engineSun[0];
                out->engineSun[1] = engineSun[1];
                out->engineSun[2] = engineSun[2];
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        __declspec(noinline) static bool ApplySunLightStateGuarded(
            void* light, void* sceneManager, const SunLightState* want, uint32_t fields)
        {
            __try
            {
                if (fields & kSunFieldDiffuse)
                    g_SunRestore.setDiffuse(light, want->diffuse.r, want->diffuse.g, want->diffuse.b);
                if (fields & kSunFieldSpecular)
                    g_SunRestore.setSpecular(light, want->specular.r, want->specular.g, want->specular.b);
                if (fields & kSunFieldDirection)
                    g_SunRestore.setDirection(light, want->direction.x, want->direction.y, want->direction.z);
                if (fields & kSunFieldPowerScale)
                    g_SunRestore.setPowerScale(light, want->powerScale);
                if (fields & kSunFieldShadowFar)
                    g_SunRestore.setShadowFar(light, want->shadowFar);
                if (fields & kSunFieldAmbient)
                    g_SunRestore.setAmbient(sceneManager, want->ambient);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static void SnapshotSunLight(void* sun, void* sceneManager)
        {
            g_SunSnapshotValid = ReadSunLightStateGuarded(
                sun, sceneManager, g_SunDirectionStateAddr, &g_SunSnapshot);
            g_SunSnapshotLight = g_SunSnapshotValid ? sun : nullptr;
        }

        static bool SameRgb(const OgreColourValue& a, const OgreColourValue& b)
        {
            return a.r == b.r && a.g == b.g && a.b == b.b;
        }

        static void AppendSunFieldNames(uint32_t fields, wchar_t* out, size_t outCount)
        {
            static const struct { uint32_t bit; const wchar_t* name; } kNames[] = {
                { kSunFieldDiffuse, L"diffuse" },
                { kSunFieldSpecular, L"specular" },
                { kSunFieldDirection, L"direction" },
                { kSunFieldPowerScale, L"powerScale" },
                { kSunFieldShadowFar, L"shadowFar" },
                { kSunFieldAmbient, L"ambient" },
            };
            bool any = false;
            for (const auto& entry : kNames)
            {
                if (!(fields & entry.bit))
                    continue;
                if (any)
                    wcscat_s(out, outCount, L",");
                wcscat_s(out, outCount, entry.name);
                any = true;
            }
            if (!any)
                wcscat_s(out, outCount, L"none");
        }

        // Puts the previous sun's mod-set values back on the rebuilt one and
        // describes what it did in `out` for the one replacement log line.
        static void RestoreSunAfterRebuild(
            void* previous, void* sun, void* sceneManager, wchar_t* out, size_t outCount)
        {
            if (!g_SunSnapshotValid || g_SunSnapshotLight != previous)
            {
                wcscpy_s(out, outCount, L"; restore skipped (no snapshot of the previous sun)");
                return;
            }
            SunLightState fresh = {};
            if (!ReadSunLightStateGuarded(sun, sceneManager, g_SunDirectionStateAddr, &fresh))
            {
                wcscpy_s(out, outCount, L"; restore skipped (fault reading the new sun)");
                return;
            }

            // The rebuild only ever produces stock config values, so any field
            // that differs from last frame's snapshot is a mod override.
            const SunLightState& want = g_SunSnapshot;
            uint32_t restore = 0;
            uint32_t kept = 0;
            if (!SameRgb(want.diffuse, fresh.diffuse))
                restore |= kSunFieldDiffuse;
            if (!SameRgb(want.specular, fresh.specular))
                restore |= kSunFieldSpecular;
            if (want.powerScale != fresh.powerScale)
                restore |= kSunFieldPowerScale;
            if (want.shadowFar != fresh.shadowFar)
                restore |= kSunFieldShadowFar;
            if (!SameRgb(want.ambient, fresh.ambient) || want.ambient.a != fresh.ambient.a)
                restore |= kSunFieldAmbient;
            if (want.direction.x != fresh.direction.x || want.direction.y != fresh.direction.y ||
                want.direction.z != fresh.direction.z)
            {
                const bool engineSunUnchanged =
                    want.engineSun[0] == fresh.engineSun[0] &&
                    want.engineSun[1] == fresh.engineSun[1] &&
                    want.engineSun[2] == fresh.engineSun[2];
                if (engineSunUnchanged)
                    restore |= kSunFieldDirection;
                else
                    kept |= kSunFieldDirection;
            }

            const bool applied =
                restore == 0 || ApplySunLightStateGuarded(sun, sceneManager, &want, restore);
            wcscpy_s(out, outCount, applied ? L"; restored=" : L"; restore FAULTED for=");
            AppendSunFieldNames(restore, out, outCount);
            wcscat_s(out, outCount, L" kept=");
            AppendSunFieldNames(kept, out, outCount);
            if (kept & kSunFieldDirection)
                wcscat_s(out, outCount, L" (engine sun vector moved)");
        }

        // --- Enhanced sun lighting baseline -----------------------------------
        // The Enhanced profile's sun look was calibrated with Campaign
        // Reimagined's Lua, which pushes a power scale and a per-world colour
        // grade through EXU; stock maps never got it. Apply the same
        // calibration (include/sun_baseline.h) natively to the first sun of
        // each mission, before the rebuild-restore snapshot, so the snapshot
        // carries it across engine sun rebuilds and any later EXU/Lua write
        // still wins. Lua runs between frames and this runs once per rendered
        // frame, so nothing can have written to a sun created this frame.
        // Enhanced profile on Direct3D 11 only; leaving the profile reverts the
        // fields still holding our values. [SunBaseline] in openshim.ini.
        static_assert(static_cast<unsigned>(openshim::sunbaseline::kFieldDiffuse) == kSunFieldDiffuse &&
                          static_cast<unsigned>(openshim::sunbaseline::kFieldSpecular) == kSunFieldSpecular &&
                          static_cast<unsigned>(openshim::sunbaseline::kFieldPowerScale) == kSunFieldPowerScale &&
                          static_cast<unsigned>(openshim::sunbaseline::kFieldShadowFar) == kSunFieldShadowFar &&
                          static_cast<unsigned>(openshim::sunbaseline::kFieldAmbient) == kSunFieldAmbient,
                      "sun baseline field bits must match SunField");

        static int g_BaselineState = 0;  // 0 untried, 1 active, -1 disabled or stood down
        static openshim::sunbaseline::SunBaselineConfig g_BaselineConfig;
        static bool g_BaselineApplied = false;
        static bool g_BaselineGateLast = false;
        static char g_BaselineWorld[4] = "";
        static SunLightState g_BaselinePre = {};
        static SunLightState g_BaselinePost = {};
        static uint32_t g_BaselineMask = 0;
        // Set when the mission leaves simulation: Redux keeps one SceneManager
        // for the process, so the next mission's sun reads as a rebuild unless
        // the boundary is remembered.
        static bool g_SunMissionBoundaryPending = false;

        static void NoteSunMissionBoundary()
        {
            g_SunMissionBoundaryPending = true;
            g_BaselineApplied = false;
            g_BaselineGateLast = false;
        }

        static bool SunBaselineGatePasses()
        {
            return RenderProfiles::Exports::GetActiveBackend() ==
                       static_cast<uint32_t>(RenderProfiles::ActiveBackend::DX11) &&
                   RenderProfiles::Exports::GetEffectiveRenderProfile() ==
                       RenderProfiles::Abi::kProfileEnhanced &&
                   RenderProfiles::IdentifyActiveRenderSystem() == 1;
        }

        static void StandDownSunBaseline(const wchar_t* reason)
        {
            g_BaselineState = -1;
            g_BaselineApplied = false;
            Log(L"[SUNBASE] stood down (%ls)\n", reason);
        }

        static openshim::sunbaseline::SunLightStateLike ToBaselineState(const SunLightState& state)
        {
            openshim::sunbaseline::SunLightStateLike out = {};
            out.diffuse[0] = state.diffuse.r;
            out.diffuse[1] = state.diffuse.g;
            out.diffuse[2] = state.diffuse.b;
            out.specular[0] = state.specular.r;
            out.specular[1] = state.specular.g;
            out.specular[2] = state.specular.b;
            out.ambient[0] = state.ambient.r;
            out.ambient[1] = state.ambient.g;
            out.ambient[2] = state.ambient.b;
            out.powerScale = state.powerScale;
            out.shadowFar = state.shadowFar;
            return out;
        }

        // Alpha channels and the direction stay as they were in `state`.
        static void FromBaselineState(const openshim::sunbaseline::SunLightStateLike& in,
                                      SunLightState& state)
        {
            state.diffuse.r = in.diffuse[0];
            state.diffuse.g = in.diffuse[1];
            state.diffuse.b = in.diffuse[2];
            state.specular.r = in.specular[0];
            state.specular.g = in.specular[1];
            state.specular.b = in.specular[2];
            state.ambient.r = in.ambient[0];
            state.ambient.g = in.ambient[1];
            state.ambient.b = in.ambient[2];
            state.powerScale = in.powerScale;
            state.shadowFar = in.shadowFar;
        }

        static bool SunNearlyEqual(float a, float b)
        {
            return std::fabs(a - b) <= 1e-4f;
        }

        static bool SunNearlyEqualRgb(const OgreColourValue& a, const OgreColourValue& b)
        {
            return SunNearlyEqual(a.r, b.r) && SunNearlyEqual(a.g, b.g) && SunNearlyEqual(a.b, b.b);
        }

        // Fields of `mask` whose live value still holds what the baseline wrote.
        static uint32_t SunBaselineFieldsStillOurs(const SunLightState& live, uint32_t mask)
        {
            const SunLightState& post = g_BaselinePost;
            uint32_t ours = 0;
            if ((mask & kSunFieldDiffuse) && SunNearlyEqualRgb(live.diffuse, post.diffuse))
                ours |= kSunFieldDiffuse;
            if ((mask & kSunFieldSpecular) && SunNearlyEqualRgb(live.specular, post.specular))
                ours |= kSunFieldSpecular;
            if ((mask & kSunFieldAmbient) && SunNearlyEqualRgb(live.ambient, post.ambient))
                ours |= kSunFieldAmbient;
            if ((mask & kSunFieldPowerScale) && SunNearlyEqual(live.powerScale, post.powerScale))
                ours |= kSunFieldPowerScale;
            if ((mask & kSunFieldShadowFar) && SunNearlyEqual(live.shadowFar, post.shadowFar))
                ours |= kSunFieldShadowFar;
            return ours;
        }

        static void ApplySunBaseline(void* sun, void* sceneManager)
        {
            SunLightState live = {};
            if (!ReadSunLightStateGuarded(sun, sceneManager, g_SunDirectionStateAddr, &live))
            {
                StandDownSunBaseline(L"fault reading the sun");
                return;
            }

            const std::string world = LastTerrainWorldCode();
            openshim::sunbaseline::SunLightStateLike computed = {};
            unsigned mask = 0;
            openshim::sunbaseline::ComputeBaseline(
                g_BaselineConfig, openshim::sunbaseline::BaselineForWorldCode(world),
                ToBaselineState(live), computed, mask);
            SunLightState want = live;
            FromBaselineState(computed, want);
            if (mask != 0 && !ApplySunLightStateGuarded(sun, sceneManager, &want, mask))
            {
                StandDownSunBaseline(L"fault writing the sun");
                return;
            }

            g_BaselinePre = live;
            g_BaselinePost = want;
            g_BaselineMask = mask;
            g_BaselineApplied = true;
            strncpy_s(g_BaselineWorld, world.c_str(), _TRUNCATE);

            wchar_t shadowDetail[64] = L"";
            if (mask & kSunFieldShadowFar)
            {
                swprintf_s(shadowDetail, L" shadowFar %.1f->%.1f",
                    static_cast<double>(live.shadowFar), static_cast<double>(want.shadowFar));
            }
            Log(L"[SUNBASE] applied world=%hs power %.2f->%.2f"
                L" diffuse (%.2f,%.2f,%.2f)->(%.2f,%.2f,%.2f)"
                L" ambient (%.2f,%.2f,%.2f)->(%.2f,%.2f,%.2f)"
                L" specular (%.2f,%.2f,%.2f)->(%.2f,%.2f,%.2f)%ls\n",
                g_BaselineWorld[0] ? g_BaselineWorld : "none",
                static_cast<double>(live.powerScale), static_cast<double>(want.powerScale),
                static_cast<double>(live.diffuse.r), static_cast<double>(live.diffuse.g),
                static_cast<double>(live.diffuse.b),
                static_cast<double>(want.diffuse.r), static_cast<double>(want.diffuse.g),
                static_cast<double>(want.diffuse.b),
                static_cast<double>(live.ambient.r), static_cast<double>(live.ambient.g),
                static_cast<double>(live.ambient.b),
                static_cast<double>(want.ambient.r), static_cast<double>(want.ambient.g),
                static_cast<double>(want.ambient.b),
                static_cast<double>(live.specular.r), static_cast<double>(live.specular.g),
                static_cast<double>(live.specular.b),
                static_cast<double>(want.specular.r), static_cast<double>(want.specular.g),
                static_cast<double>(want.specular.b),
                shadowDetail);
        }

        // Puts back the stock value of every field that still holds ours; a
        // field EXU/Lua has since changed is left alone.
        static void RevertSunBaseline(void* sun, void* sceneManager)
        {
            SunLightState live = {};
            if (!ReadSunLightStateGuarded(sun, sceneManager, g_SunDirectionStateAddr, &live))
            {
                StandDownSunBaseline(L"fault reading the sun");
                return;
            }
            const uint32_t revert = SunBaselineFieldsStillOurs(live, g_BaselineMask);
            if (revert != 0 && !ApplySunLightStateGuarded(sun, sceneManager, &g_BaselinePre, revert))
            {
                StandDownSunBaseline(L"fault writing the sun");
                return;
            }
            g_BaselineApplied = false;

            wchar_t reverted[128] = L"";
            wchar_t kept[128] = L"";
            AppendSunFieldNames(revert, reverted, sizeof(reverted) / sizeof(reverted[0]));
            AppendSunFieldNames(g_BaselineMask & ~revert, kept, sizeof(kept) / sizeof(kept[0]));
            Log(L"[SUNBASE] reverted (profile left Enhanced) fields=%ls kept=%ls\n", reverted, kept);
        }

        // Runs each frame with the live sun, before the restore snapshot.
        // `firstSun` is the first sun of a scene or mission.
        static void TickSunBaseline(void* sun, void* sceneManager, bool firstSun, bool restoreOn)
        {
            if (g_BaselineState < 0)
                return;
            if (firstSun)
            {
                g_BaselineApplied = false;
                g_BaselineGateLast = false;
            }
            if (g_BaselineState == 0)
            {
                g_BaselineConfig = openshim::sunbaseline::ParseSunBaselineConfig(
                    [](const char* key, std::string& out) {
                        return TryGetUserConfigString("SunBaseline", key, out);
                    },
                    [](const char* key, bool& out) {
                        return TryGetUserConfigBool("SunBaseline", key, out);
                    },
                    [](const char* key) {
                        Log(L"[SUNBASE] Ignoring invalid [SunBaseline] %hs\n", key);
                    });
                if (!g_BaselineConfig.enabled)
                {
                    g_BaselineState = -1;
                    Log(L"[SUNBASE] disabled by [SunBaseline] Enabled=0\n");
                    return;
                }
                if (!restoreOn)
                {
                    StandDownSunBaseline(L"sun rebuild restore unavailable");
                    return;
                }
                g_BaselineState = 1;
            }

            const bool gate = SunBaselineGatePasses();
            const bool entered = gate && (firstSun || !g_BaselineGateLast);
            g_BaselineGateLast = gate;
            if (g_BaselineApplied)
            {
                if (!gate)
                    RevertSunBaseline(sun, sceneManager);
                return;
            }
            if (entered)
                ApplySunBaseline(sun, sceneManager);
        }

        void WatchSunLightReplacement()
        {
            if (!BindSunWatch())
                return;
            void* const sceneManager = GetOgreSceneManagerRuntime();
            void* const sun = ReadSunLight();
            // While the sun is null between destroy and rebuild, keep the last
            // pointer so the rebuilt one still reads as a change.
            if (!sceneManager || !sun)
                return;
            // A stale global is handled like a null one: keep the last pointer
            // and wait for the engine to name a live light again.
            if (!IsLiveOgreLight(sun))
            {
                if (sun != g_LastRejectedSunLight && ++g_RejectedSunLights <= kSunReplacementLogLimit)
                {
                    char type[96] = {};
                    const char* const name = TryGetRttiClassName(sun, type, sizeof(type));
                    Log(L"[SUNWATCH] sun global 0x%08X is not a live Ogre::Light (%hs); not touched (#%u)\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sun)),
                        name ? name : "unknown type",
                        static_cast<unsigned>(g_RejectedSunLights));
                }
                g_LastRejectedSunLight = sun;
                return;
            }
            const bool restoreOn = BindSunRestore();
            InstallSunBuildHook();
            // Read once: a build between here and the bookkeeping below is
            // seen next frame as a new generation.
            const LONG builds = g_SunBuilds;
            if (sun == g_LastSunLight && sceneManager == g_LastSunSceneManager &&
                builds == g_LastSunBuild)
            {
                // After a mission boundary the same pointer is either the
                // outgoing sun (leave it alone) or, once the next mission is
                // running, a new sun the allocator put at the same address.
                bool firstSun = false;
                if (g_SunMissionBoundaryPending)
                {
                    if (!g_PilotFlashlightWorldRunning)
                        return;
                    g_SunMissionBoundaryPending = false;
                    firstSun = true;
                }
                TickSunBaseline(sun, sceneManager, firstSun, restoreOn);
                if (restoreOn)
                    SnapshotSunLight(sun, sceneManager);
                return;
            }

            void* const previous = g_LastSunLight;
            const bool sameScene = sceneManager == g_LastSunSceneManager;
            g_LastSunLight = sun;
            g_LastSunSceneManager = sceneManager;
            g_LastSunBuild = builds;
            if (!previous || !sameScene)
            {
                // First sun of this scene: nothing cached yet. The baseline
                // goes on before the snapshot so rebuilds carry it.
                g_SunMissionBoundaryPending = false;
                TickSunBaseline(sun, sceneManager, true, restoreOn);
                if (restoreOn)
                    SnapshotSunLight(sun, sceneManager);
                return;
            }

            // The first sun of the next mission shares the scene manager, so
            // it arrives here. The snapshot belongs to the mission that ended:
            // do not carry it over.
            const bool newMission = g_SunMissionBoundaryPending;
            g_SunMissionBoundaryPending = false;

            const bool notified = NotifySceneLightsDirty(sceneManager);
            wchar_t restoreDetail[256] = L"";
            if (restoreOn)
            {
                if (newMission)
                {
                    wcscpy_s(restoreDetail, L"; restore skipped (new mission)");
                }
                else
                {
                    RestoreSunAfterRebuild(previous, sun, sceneManager,
                        restoreDetail, sizeof(restoreDetail) / sizeof(restoreDetail[0]));
                }
            }
            TickSunBaseline(sun, sceneManager, newMission, restoreOn);
            if (restoreOn)
                SnapshotSunLight(sun, sceneManager);
            if (++g_SunReplacements <= kSunReplacementLogLimit)
            {
                Log(L"[SUNWATCH] sun replaced 0x%08X -> 0x%08X; light lists %ls%ls (#%u)\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(previous)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sun)),
                    notified ? L"marked dirty" : L"NOT marked (fault)",
                    restoreDetail,
                    static_cast<unsigned>(g_SunReplacements));
            }
        }

        void RevertPilotFlashlightToBaseline()
        {
            InitializePilotFlashlightConfig();
            g_PilotFlashlightLastRefreshTick = 0;
            RefreshPilotFlashlightState();
        }

    }
}
