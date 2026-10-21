#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

namespace BZROpenShim::ShellCasings
{
    inline constexpr const char* kFinishMarker = "// OpenShim ShellCasings default casing materials";
    inline constexpr const char* kFinishTgaMarker = "OpenShim casing finish ";
    inline constexpr const char* kFinishDiffuse = "openshim_casing_finish_d.tga";
    inline constexpr const char* kFinishSpecular = "openshim_casing_finish_s.tga";
    inline constexpr unsigned kFinishWidth = 256, kFinishHeight = 128;

    inline uint32_t FinishNoise(uint32_t x, uint32_t y) noexcept
    {
        uint32_t value = x * 374761393u + y * 668265263u + 0xB2A55u;
        value = (value ^ (value >> 13)) * 1274126177u;
        return value ^ (value >> 16);
    }

    // Shared UV atlas: body 0..0.5, machined rim .62, soot .76, primer .90.
    // Variation is surface grain/annealing, not a baked camera-facing glint.
    // Real moving highlights come from BZBase's view/light-dependent specular.
    inline std::vector<uint8_t> FinishRgb(bool specular)
    {
        std::vector<uint8_t> pixels(kFinishWidth * kFinishHeight * 3);
        for (unsigned y = 0; y < kFinishHeight; ++y) for (unsigned x = 0; x < kFinishWidth; ++x)
        {
            const float u = static_cast<float>(x) / kFinishWidth;
            const float v = static_cast<float>(y) / kFinishHeight;
            const float grain = static_cast<float>(FinishNoise(x, y / 12) & 255u) / 255.0f;
            const float fine = static_cast<float>(FinishNoise(x, y) & 255u) / 255.0f;
            const float brushed = 0.93f + grain * 0.12f + (fine - 0.5f) * 0.035f;
            float r = 0, g = 0, b = 0;
            if (v < 0.52f)
            {
                const float neck = std::clamp((v - 0.405f) / 0.055f, 0.0f, 1.0f);
                const float stain = neck * (0.6f + 0.4f * std::sin(u * 18.849556f + v * 30));
                const float scratch = (FinishNoise(x, y / 35) % 83u == 0u) ? 0.10f : 0.0f;
                if (specular) { r = .82f - stain * .32f; g = .72f - stain * .34f; b = .43f - stain * .22f; }
                else { r = .67f - stain * .15f + scratch; g = .43f - stain * .20f + scratch * .8f; b = .15f - stain * .04f + scratch * .4f; }
            }
            else if (v < 0.70f)
            {
                // Warm bright machined rim, fine concentric tooling marks.
                const float radial = std::sqrt((u - .5f) * (u - .5f) +
                    ((v - .62f) * 23.5f) * ((v - .62f) * 23.5f));
                const float tool = 0.96f + .04f * std::cos(radial * 340.0f);
                if (specular) { r = .90f * tool; g = .79f * tool; b = .51f * tool; }
                else { r = .75f * tool; g = .52f * tool; b = .22f * tool; }
            }
            else if (v < 0.84f)
            {
                // Deep mouth/groove: no glow and very little polished response.
                r = specular ? .035f : .055f; g = specular ? .025f : .038f; b = .018f;
            }
            else
            {
                // Recessed pale primer distinguishes the base from the body.
                r = specular ? .74f : .60f; g = specular ? .70f : .55f; b = specular ? .56f : .40f;
                const float dy = (v - .90f) * 23.5f;
                const float pin = std::exp(-((u - .5f) * (u - .5f) + dy * dy) * 950.0f);
                const float dent = 1.0f - pin * .58f;
                r *= dent; g *= dent; b *= dent;
            }
            const size_t at = (static_cast<size_t>(y) * kFinishWidth + x) * 3;
            pixels[at] = static_cast<uint8_t>(std::clamp(r * brushed, 0.0f, 1.0f) * 255);
            pixels[at + 1] = static_cast<uint8_t>(std::clamp(g * brushed, 0.0f, 1.0f) * 255);
            pixels[at + 2] = static_cast<uint8_t>(std::clamp(b * brushed, 0.0f, 1.0f) * 255);
        }
        return pixels;
    }

    inline std::vector<uint8_t> FinishTga(bool specular)
    {
        const std::string id = std::string(kFinishTgaMarker) + "v2";
        // Uncompressed 24-bit, top-left origin. Both Ogre renderers support TGA.
        std::vector<uint8_t> out(18, 0);
        out[0] = static_cast<uint8_t>(id.size()); out[2] = 2;
        out[12] = kFinishWidth & 255; out[13] = kFinishWidth >> 8;
        out[14] = kFinishHeight & 255; out[15] = kFinishHeight >> 8;
        out[16] = 24; out[17] = 0x20;
        out.insert(out.end(), id.begin(), id.end());
        const auto rgb = FinishRgb(specular);
        for (size_t i = 0; i < rgb.size(); i += 3)
        { out.push_back(rgb[i + 2]); out.push_back(rgb[i + 1]); out.push_back(rgb[i]); }
        return out;
    }

    inline bool IsGeneratedFinishTga(const std::vector<uint8_t>& bytes)
    {
        const std::string marker(kFinishTgaMarker);
        return bytes.size() >= 18 + marker.size() && bytes[0] >= marker.size() &&
            std::equal(marker.begin(), marker.end(), bytes.begin() + 18);
    }

    inline std::string FinishMaterialScript()
    {
        std::string script = std::string(kFinishMarker) + " v2 (generated; do not edit).\n";
        for (const auto* name : {"openshim_casing_brass", "openshim_casing_rim"})
            script += std::string("material ") + name + " : BZBase\n{\n"
                "    set_texture_alias DiffuseMap " + kFinishDiffuse + "\n"
                "    set_texture_alias SpecularMap " + kFinishSpecular + "\n"
                "    set $diffuse \"1 1 1\"\n    set $ambient \"1 1 1\"\n"
                "    set $specular \"1 1 1\"\n    set $shininess \"64\"\n"
                "    set $bias \"0\"\n}\n";
        return script;
    }
}
