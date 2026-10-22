#pragma once

#include "weapon_presentation.h"

#include <charconv>
#include <cmath>
#include <limits>
#include <optional>
#include <string_view>

namespace BZROpenShim::WeaponPresentation::NativePolicy
{
    // Native ParameterDB lowercases ASCII and uses FNV-1a/32 separately for
    // section and key (two stack DWORDs), rather than a packed string token.
    constexpr uint32_t Hash(std::string_view value) noexcept
    {
        uint32_t result = 0x811c9dc5u;
        for (unsigned char c : value)
        {
            if (c >= 'A' && c <= 'Z') c += 'a' - 'A';
            result = (result ^ c) * 0x01000193u;
        }
        return result;
    }
    static_assert(Hash("WeaponClass") == 0xacda90abu);
    static_assert(Hash("GameObjectClass") == 0xd3dd9cecu);
    static_assert(Hash("BuildingClass") == 0x91e9360fu);

    inline std::string_view Trim(std::string_view value) noexcept
    {
        while (!value.empty() && (value.front() == ' ' || value.front() == '\t'))
            value.remove_prefix(1);
        while (!value.empty() && (value.back() == ' ' || value.back() == '\t'))
            value.remove_suffix(1);
        return value;
    }

    // Preserve case, accept native quoted ODF strings, reject malformed quotes.
    inline std::optional<std::string_view> Name(std::string_view value) noexcept
    {
        value = Trim(value);
        if (!value.empty() && value.front() == '"')
        {
            if (value.size() < 2 || value.back() != '"') return std::nullopt;
            value.remove_prefix(1);
            value.remove_suffix(1);
        }
        for (unsigned char c : value)
            if (c < 0x20 || c > 0x7e || c == '"') return std::nullopt;
        return value;
    }

    // A malformed present duration must disable, never silently inherit.
    inline float Duration(std::string_view value) noexcept
    {
        value = Trim(value);
        if (!value.empty() && value.front() == '+') value.remove_prefix(1);
        if (value.empty()) return std::numeric_limits<float>::quiet_NaN();
        float parsed = 0;
        const auto result = std::from_chars(value.data(), value.data() + value.size(), parsed);
        if (result.ec != std::errc{} || result.ptr != value.data() + value.size() ||
            !std::isfinite(parsed) || parsed <= 0)
            return std::numeric_limits<float>::quiet_NaN();
        return parsed;
    }

    struct MeshFlashFields
    {
        std::optional<std::string_view> mesh, material, duration, scale, endScale, offset, roll;
    };

    inline float Scalar(std::string_view text) noexcept
    {
        text = Trim(text);
        if (!text.empty() && text.front() == '+') text.remove_prefix(1);
        float value = 0;
        if (text.empty()) return std::numeric_limits<float>::quiet_NaN();
        const auto parsed = std::from_chars(text.data(), text.data() + text.size(), value);
        return parsed.ec == std::errc{} && parsed.ptr == text.data() + text.size() && std::isfinite(value)
            ? value : std::numeric_limits<float>::quiet_NaN();
    }

    inline std::optional<WeaponConvergence::Vec3> Offset(std::string_view text) noexcept
    {
        const auto name = Name(text);
        if (!name) return std::nullopt;
        auto remaining = Trim(*name);
        float values[3]{};
        for (float& value : values)
        {
            remaining = Trim(remaining);
            if (!remaining.empty() && remaining.front() == '+') remaining.remove_prefix(1);
            if (remaining.empty()) return std::nullopt;
            const auto parsed = std::from_chars(remaining.data(), remaining.data() + remaining.size(), value);
            if (parsed.ec != std::errc{} || !std::isfinite(value) || std::fabs(value) > 20) return std::nullopt;
            if (parsed.ptr != remaining.data() + remaining.size() && *parsed.ptr != ' ' && *parsed.ptr != '\t') return std::nullopt;
            remaining.remove_prefix(static_cast<size_t>(parsed.ptr - remaining.data()));
        }
        if (!Trim(remaining).empty()) return std::nullopt;
        return WeaponConvergence::Vec3{values[0], values[1], values[2]};
    }

    struct MuzzleRenderFields
    {
        std::optional<std::string_view> effect, duration, offset;
    };

    inline MuzzleRenderConfig ResolveMuzzleRenderConfig(const MuzzleRenderConfig& parent,
        const MuzzleRenderFields& fields, const WeaponConvergence::Vec3& defaultOffset)
    {
        MuzzleRenderConfig result = parent.Valid() ? parent : MuzzleRenderConfig{};
        if (!parent.Valid()) result.offset = defaultOffset;
        if (fields.effect)
        {
            const auto name = Name(*fields.effect);
            if (!name || name->empty()) return {};
            result.effect = *name;
        }
        if (fields.duration) result.duration = Scalar(*fields.duration);
        if (fields.offset)
        {
            const auto offset = Offset(*fields.offset);
            if (!offset) return {};
            result.offset = *offset;
        }
        return result.Valid() ? result : MuzzleRenderConfig{};
    }

    // Per-craft, per-slot override of the weapon's flash placement. Replaces the
    // mesh offset; replaces the render offset only when it was defaulted from the
    // mesh offset (an explicit muzzleRenderOffset wins).
    inline void ApplyCraftFlashOffset(FlashConfig& flash, bool renderOffsetDefaulted,
        const WeaponConvergence::Vec3& offset) noexcept
    {
        if (flash.IsMesh()) flash.offset = offset;
        if (renderOffsetDefaulted && flash.muzzleRender.Valid()) flash.muzzleRender.offset = offset;
    }

    // Weapon presentation opt-in. Recoil needs a kick (weapon recoilKick, or the
    // craft's recoilKick<N> which overrides it); a vehicle's mesh flash and
    // muzzleRender layer need a craft flashOffset<N>. Persons have no fitted
    // craft section and keep the weapon's flashOffset.
    constexpr float kMaxRecoilKick = 4.0f;

    // Absent is the caller's job (nullopt). A present value outside 0..4 or
    // malformed is nullopt here and must be treated as absent after a WARN.
    inline std::optional<float> Kick(std::string_view text) noexcept
    {
        const float value = Scalar(text);
        if (!std::isfinite(value) || value < 0 || value > kMaxRecoilKick) return std::nullopt;
        return value;
    }

    inline float EffectiveKick(std::optional<float> craftOverride, float weaponKick) noexcept
    {
        const float kick = craftOverride ? *craftOverride : weaponKick;
        return std::isfinite(kick) && kick > 0 ? kick : 0.0f;
    }

    inline float ScaledRecoilDistance(float craftDistance, float kick) noexcept
    {
        return craftDistance * kick;
    }

    inline bool FlashAllowed(bool isPerson, bool hasCraftOffset) noexcept
    {
        return isPerson || hasCraftOffset;
    }

    // recoilCockpit<N>: "1"/"true" or "0"/"false"; anything else is nullopt
    // and the caller fails closed (no cockpit kick).
    inline std::optional<bool> CockpitFlag(std::string_view text) noexcept
    {
        const auto flag = Trim(text);
        if (flag == "1" || flag == "true") return true;
        if (flag == "0" || flag == "false") return false;
        return std::nullopt;
    }

    // Cockpit counterpart of a world recoil node. The native binder hides
    // every VDF band-1 bone (name[3] == '1') in the cockpit entity and shows
    // band 2. A cockpit that reuses the world mesh (CR avtank) draws its gun
    // through the band-2 twin of the same slot: AGR11BGA -> AGR21bga,
    // SCZ11BGB -> SCZ21BGB. Only name[3] changes; case is not preserved
    // between bands, so the match ignores ASCII case. Names that are not
    // band 1 have no twin.
    inline bool CockpitTwinMatches(std::string_view bone, const MeshId& worldNode) noexcept
    {
        size_t length = 0;
        while (length < worldNode.size() && worldNode[length]) ++length;
        if (length < 4 || worldNode[3] != '1' || bone.size() != length) return false;
        auto lower = [](char c) { return c >= 'A' && c <= 'Z' ? static_cast<char>(c + ('a' - 'A')) : c; };
        for (size_t i = 0; i < length; ++i)
        {
            const char expected = i == 3 ? '2' : worldNode[i];
            if (lower(bone[i]) != lower(expected)) return false;
        }
        return true;
    }

    // Signed slide along the node's own front axis; Visual() is
    // rest + front * displacement, so this recovers displacement.
    inline float RecoilDisplacement(const Matrix& rest, const Matrix& visual) noexcept
    {
        const double dx = visual.positionX - rest.positionX;
        const double dy = visual.positionY - rest.positionY;
        const double dz = visual.positionZ - rest.positionZ;
        const double length = double(visual.frontX) * visual.frontX + double(visual.frontY) * visual.frontY +
            double(visual.frontZ) * visual.frontZ;
        if (!(length > 1e-6)) return 0.0f;
        const double value = (dx * visual.frontX + dy * visual.frontY + dz * visual.frontZ) / length;
        return std::isfinite(value) ? static_cast<float>(value) : 0.0f;
    }

    struct BoneQuat { float w = 1, x = 0, y = 0, z = 0; }; // Ogre::Quaternion order
    struct BoneVec { float x = 0, y = 0, z = 0; };

    // Ogre bone local +Z expressed in the parent's space. BZ->Ogre mirrors X
    // only, so a node's BZ front axis stays the bone's +Z.
    inline BoneVec BoneForward(const BoneQuat& q) noexcept
    {
        return { 2 * (q.x * q.z + q.w * q.y), 2 * (q.y * q.z - q.w * q.x), 1 - 2 * (q.x * q.x + q.y * q.y) };
    }

    inline BoneVec CockpitRecoilPosition(const BoneVec& rest, const BoneQuat& orientation, float displacement) noexcept
    {
        const auto f = BoneForward(orientation);
        return { rest.x + f.x * displacement, rest.y + f.y * displacement, rest.z + f.z * displacement };
    }

    // Removes the mesh flash and muzzleRender layer; legacy flashName is untouched.
    inline void StripMeshAndRenderFlash(FlashConfig& flash) noexcept
    {
        flash.mesh.clear();
        flash.material.clear();
        flash.muzzleRender = {};
    }

    // No filesystem lookups: names are engine resource names, preserving case.
    // Explicitly empty/invalid mesh disables the flash, including inheritance.
    inline FlashConfig ResolveMeshFlashConfig(const FlashConfig& parent, const MeshFlashFields& fields)
    {
        FlashConfig result = parent.IsMesh() ? parent : FlashConfig{};
        result.effect.clear();
        if (!parent.IsMesh()) result.duration = 0.08f;
        if (fields.mesh)
        {
            auto name = Name(*fields.mesh);
            if (!name || name->empty()) return {};
            result.mesh = *name;
        }
        if (fields.material)
        {
            auto name = Name(*fields.material);
            if (!name) return {};
            result.material = *name;
        }
        if (fields.duration) result.duration = Scalar(*fields.duration);
        if (fields.scale) result.startScale = result.finishScale = Scalar(*fields.scale);
        if (fields.endScale) result.finishScale = Scalar(*fields.endScale);
        if (fields.roll) result.rollDegrees = Scalar(*fields.roll);
        if (fields.offset)
        {
            const auto offset = Offset(*fields.offset);
            if (!offset) return {};
            result.offset = *offset;
        }
        return result.IsMesh() && result.Valid() ? result : FlashConfig{};
    }
}
