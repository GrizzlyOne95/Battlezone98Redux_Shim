#pragma once
#include <algorithm>
#include <array>
#include <cstdint>
#include <string_view>
#include <iterator>

namespace BZROpenShim::MenuTheme
{
    struct Settings
    {
        bool enabled = false;
        std::array<int,3> rgb{255,0,0};
        int saturation=100,whiteLevel=100;
        bool operator==(const Settings& b) const { return enabled==b.enabled && rgb==b.rgb && saturation==b.saturation && whiteLevel==b.whiteLevel; }
        bool operator!=(const Settings& b) const { return !(*this==b); }
    };
    // Explicit menu artwork only. No fonts, faction flags, campaign pictures,
    // map thumbnails, HUD sprites, or arbitrary mod filenames.
    inline constexpr std::string_view MenuImages[] = {
            "mainCenterPanel.png", "topEdge.png", "midhvr.png", "midclk.png",
            "bckground_1920x1080.png", "EdgeBorder.png", "mainb.png",
            "optionhv.png", "optionck.png", "topcorner.png", "topcrnhv.png", "topcrnck.png",
            "tomnoff.png", "tomnon.png", "tomnclk.png", "esc_center.png",
            "goptions_center.png", "aoptions_center.png", "poptions_center.png", "keyOptions_center.png",
            "singlep_center.png", "multi1_center.png", "multi2_center.png", "arrows.png", "kickclk.png",
            "ltarroff.png", "ltarron.png", "ltarrclk.png", "rtarroff.png", "rtarron.png", "rtarrclk.png",
            "uparroff.png", "uparron.png", "uparrclk.png", "dnarron.png", "dnarroff.png", "dnarrclk.png",
            "mpcron.png", "mpcrclk.png", "newon.png", "newclk.png", "backon.png", "backclk.png",
            "uiline.png", "uiplate.png", "uibtn.png", "uibtnhv.png",
            "osh_options_center.png", "osh_hub_center.png", "osh_category_center.png", "osh_reticle_center.png",
            "osh_keys_center.png", "osh_career_center.png", "osh_prelobby_center.png", "osh_menu_theme_center.png",
            "osh_tile_hv.png", "osh_tile_ck.png", "osh_value_hv.png", "osh_value_ck.png",
            "osh_key_hv.png", "osh_key_ck.png", "osh_tool_hv.png", "osh_tool_ck.png"
    };
    inline bool IsMenuImage(std::string_view name)
    {
        return std::find(std::begin(MenuImages),std::end(MenuImages),name) != std::end(MenuImages);
    }
    // CPU reference for the shader. Recolor green-dominant artwork using
    // its peak intensity, with an adjustable neutral contribution. Alpha stays native.
    inline std::array<float,4> Colorize(std::array<float,4> pixel, const Settings& s)
    {
        if (!s.enabled) return pixel;
        const float excess=std::max(0.0f,pixel[1]-std::max(pixel[0],pixel[2]));
        const float t=std::clamp((excess-.005f)/.025f,0.0f,1.0f);
        const float mask=t*t*(3-2*t),sat=std::clamp(s.saturation,0,100)*.01f;
        const float peak=std::max(pixel[0],std::max(pixel[1],pixel[2]));
        const float white=std::clamp(s.whiteLevel,0,200)*.01f;
        for(size_t i=0;i<3;++i)
        {
            const float target=peak*(1-sat+sat*std::clamp(s.rgb[i],0,255)/255.0f);
            pixel[i]=std::clamp((pixel[i]+(target-pixel[i])*mask)*white,0.0f,1.0f);
        }
        return pixel;
    }
}
