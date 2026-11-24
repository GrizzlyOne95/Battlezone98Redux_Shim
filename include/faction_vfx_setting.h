#pragma once

// "Faction-Specific VFX": one switch for the faction engine flames and the
// faction construction/portal blobs. Pure merge logic, unit tested
// (tests/faction_vfx_setting_tests.cpp).
//
// [Display] FactionVfx is the key the options row writes. When it is present
// it decides both features. When it is absent the feature is on if either
// legacy key ([Display] JetFlames, [Display] FactionConstructionBlobs) is on,
// so a hand-edited ini keeps working. Nothing ever rewrites the legacy keys.

namespace BZROpenShim::FactionVfx
{
    struct Tri
    {
        bool present = false;
        bool value = false;
    };

    inline bool Resolve(Tri vfx, Tri jetFlames, Tri constructionBlobs)
    {
        if (vfx.present)
            return vfx.value;
        return (jetFlames.present && jetFlames.value) ||
               (constructionBlobs.present && constructionBlobs.value);
    }
}
