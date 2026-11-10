#pragma once

// Fog-distance submission cull: the pure decision.
//
// Kept free of Windows and of Ogre so tests/fog_distance_cull_tests.cpp can
// exercise it on the host. ogre_entity_frustum_cull.cpp gathers the inputs
// inside RenderQueue::processVisibleObject and suppresses only
// Entity::_updateRenderQueue, so this is render-only: nothing here reaches
// simulation, AI, collision, targeting, radar or the network.
//
// Why an object past fog end can be skipped (Redux DX11 shaders,
// BZ_ASSETS_CORE/pc/programs/dx11/base-sm4.hlsl:146 and :396-397):
//
//   vDepth   = oPosition.z;                                  // clip-space z
//   fogValue = saturate((vDepth - fogParams.y) * fogParams.w);
//   oColor.xyz = lerp(oColor.xyz, fogColour.xyz, fogValue);
//
// fogParams is Ogre's (density, start, end, 1/(end-start)), so for linear fog
// every pixel whose clip z is at or past fog end is exactly the fog colour.
// With Ogre's D3D perspective projection clip z = f(d-n)/(f-n) >= d - n for
// view depth d, near n and far f, so any point with d >= fogEnd + n is fully
// fogged. The cull therefore tests the box's *nearest planar view depth*
// against fogEnd + nearClip + margin. It is never radial distance.
//
// Everything else fails closed: anything the caller could not verify keeps
// stock behaviour.

#include <cmath>
#include <cstdint>

namespace openshim::fogcull
{
    // Ogre::FogMode: FOG_NONE=0, FOG_EXP=1, FOG_EXP2=2, FOG_LINEAR=3.
    constexpr int kFogModeLinear = 3;
    // Ogre::AxisAlignedBox::Extent: EXTENT_NULL=0, EXTENT_FINITE=1, EXTENT_INFINITE=2.
    constexpr uint32_t kExtentFinite = 1u;
    // Ogre::ProjectionType: PT_ORTHOGRAPHIC=0, PT_PERSPECTIVE=1.
    constexpr int kProjectionPerspective = 1;
    // Extra metres past the fully-fogged depth. Absorbs skeletal animation
    // outside the bind-pose box and the infinite-far-plane epsilon.
    constexpr float kMarginMetres = 10.0f;

    enum class Decision : uint8_t
    {
        KeepDisabled,
        KeepShadowPass,
        KeepNotMainCamera,
        KeepPassNotAllowed,   // not the main viewport or its glow render target
        KeepViewMode,         // satellite, cinematic, editor, unknown
        KeepNotPerspective,
        KeepFogNotLinear,
        KeepFogInvalid,
        KeepNoFiniteBounds,
        KeepInsideFog,
        KeepFogOverride,      // a pass on this entity ignores scene fog
        Cull,
    };

    // Current_View values (View_Record +8) whose main camera sits on or just
    // behind the player: COCKPIT_VIEW=0, FIX_EXTERN_VIEW=1, CHASE_VIEW=7
    // (BZ 1.5 PDB enum, Battlezone_Source/BZ1/derived/bz15_pdb/raw/types.txt:6471-6478).
    // Because the camera is on the player in these views, the player's own
    // craft is never past fog end and so never culled. Everything else --
    // binocular zoom (2), satellite (3), padlock (4), cinematic/FSM camera
    // (5), free eye (6), missile camera (8), 2D/editor (9, 10), track (11) and
    // any unknown value -- keeps stock submission.
    constexpr bool IsAllowedViewMode(int32_t currentView)
    {
        return currentView == 0 || currentView == 1 || currentView == 7;
    }

    // Nearest view depth (metres in front of the camera) of a world AABB.
    // viewRow2 is row 2 of Ogre's row-major view matrix, so view z = row2.(p,1)
    // and depth = -z. The box corner with the largest z is the nearest one.
    inline float NearestViewDepthOfAabb(
        const float viewRow2[4], const float boxMin[3], const float boxMax[3])
    {
        float maxZ = viewRow2[3];
        for (int axis = 0; axis < 3; ++axis)
        {
            const float a = viewRow2[axis] * boxMin[axis];
            const float b = viewRow2[axis] * boxMax[axis];
            maxZ += (a > b) ? a : b;
        }
        return -maxZ;
    }

    struct Inputs
    {
        bool featureEnabled = false;
        bool shadowPass = false;
        bool isMainCamera = false;
        bool passAllowed = false;
        bool viewModeAllowed = false;
        int projectionType = -1;
        int fogMode = 0;
        float fogStart = 0.0f;
        float fogEnd = 0.0f;
        float nearClip = 0.0f;
        uint32_t extent = 0u;
        float nearestDepth = 0.0f;
    };

    inline float CullDepth(float fogEnd, float nearClip)
    {
        return fogEnd + nearClip + kMarginMetres;
    }

    // Everything except the material check, which is the expensive input and
    // is only worth gathering for an object this already wants to cull.
    inline Decision DecideGeometry(const Inputs& in)
    {
        if (!in.featureEnabled)
            return Decision::KeepDisabled;
        if (in.shadowPass)
            return Decision::KeepShadowPass;
        if (!in.isMainCamera)
            return Decision::KeepNotMainCamera;
        if (!in.passAllowed)
            return Decision::KeepPassNotAllowed;
        if (!in.viewModeAllowed)
            return Decision::KeepViewMode;
        if (in.projectionType != kProjectionPerspective)
            return Decision::KeepNotPerspective;
        if (in.fogMode != kFogModeLinear)
            return Decision::KeepFogNotLinear;
        if (!std::isfinite(in.fogStart) || !std::isfinite(in.fogEnd) ||
            !std::isfinite(in.nearClip) ||
            in.fogEnd <= 0.0f || in.fogEnd <= in.fogStart || in.nearClip < 0.0f)
        {
            return Decision::KeepFogInvalid;
        }
        if (in.extent != kExtentFinite)
            return Decision::KeepNoFiniteBounds;
        // Written so a NaN depth keeps the object.
        if (!(in.nearestDepth > CullDepth(in.fogEnd, in.nearClip)))
            return Decision::KeepInsideFog;
        return Decision::Cull;
    }

    inline Decision ApplyMaterial(Decision geometry, bool anyPassOverridesFog)
    {
        if (geometry == Decision::Cull && anyPassOverridesFog)
            return Decision::KeepFogOverride;
        return geometry;
    }
}
