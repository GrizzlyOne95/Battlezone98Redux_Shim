// pilot_flashlight.cpp
// BZR Open Shim - player pilot flashlight (SinglePlayer tier), split out of
// bzr_hooks.cpp. The dispatchers that drive it stay there; shared helpers
// and Ogre ABI types come from bzr_hooks_internal.h.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "headlight_falloff.h"
#include "patcher.h"
#include "shim_log.h"

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
        void PilotFlashlightNotifyMissionRunStateChanged(bool enteringSimulation)
        {
            g_PilotFlashlightWorldRunning = enteringSimulation;
            if (!enteringSimulation)
                ForgetPilotFlashlight(L"left simulation");
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
            if (!g_PilotFlashlightLight && !CreatePilotFlashlight(player, node))
                return;

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
                    g_PilotFlashlightColourR = preset.r;
                    g_PilotFlashlightColourG = preset.g;
                    g_PilotFlashlightColourB = preset.b;
                    return true;
                }
            }

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

        void RevertPilotFlashlightToBaseline()
        {
            InitializePilotFlashlightConfig();
            g_PilotFlashlightLastRefreshTick = 0;
            RefreshPilotFlashlightState();
        }

    }
}
