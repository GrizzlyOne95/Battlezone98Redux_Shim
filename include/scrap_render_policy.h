// scrap_render_policy.h
//
// SPDX-License-Identifier: MIT
//
// Pure logic for [Fixes] ScrapShadowDistance (ogre_entity_frustum_cull.cpp).
// Scrap pieces are small (npscr1/2/3 are 4-6 triangle meshes under a metre),
// so their PSSM shadow lands under the piece itself and is a handful of texels
// at any distance. Past a chosen distance from the main camera the shadow-caster
// submission is skipped; the main-view submission is never touched, so scrap
// stays visible, and nothing here reaches simulation, collision or pickup.
//
// Host-tested in tests/scrap_render_policy_tests.cpp.
#pragma once

#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
    namespace ScrapRender
    {
        // Accepted setting range in metres. 0 = off (stock: every scrap piece
        // casts into every cascade). The outer PSSM split is 256 m, so anything
        // past it would never skip a submission.
        constexpr int kMaxShadowDistanceMetres = 256;

        inline int ClampShadowDistanceMetres(long value)
        {
            if (value <= 0)
                return 0;
            if (value > kMaxShadowDistanceMetres)
                return kMaxShadowDistanceMetres;
            return static_cast<int>(value);
        }

        inline char ToLowerAscii(char c)
        {
            return (c >= 'A' && c <= 'Z') ? static_cast<char>(c - 'A' + 'a') : c;
        }

        // Stock scrap meshes: npscr1.mesh, npscr2.mesh, npscr3.mesh (classLabel
        // "scrap" in npscr1/2/3.odf). Matches "npscr" + one or more digits,
        // with or without ".mesh", case-insensitive. Mod scrap under another
        // name is not matched and keeps stock shadows.
        inline bool IsScrapMeshName(const char* name, std::size_t length)
        {
            if (!name)
                return false;
            static const char kPrefix[] = "npscr";
            constexpr std::size_t kPrefixLength = sizeof(kPrefix) - 1;
            std::size_t stem = length;
            if (stem >= 5 && ToLowerAscii(name[stem - 5]) == '.' &&
                ToLowerAscii(name[stem - 4]) == 'm' && ToLowerAscii(name[stem - 3]) == 'e' &&
                ToLowerAscii(name[stem - 2]) == 's' && ToLowerAscii(name[stem - 1]) == 'h')
            {
                stem -= 5;
            }
            if (stem <= kPrefixLength)
                return false;
            for (std::size_t i = 0; i < kPrefixLength; ++i)
            {
                if (ToLowerAscii(name[i]) != kPrefix[i])
                    return false;
            }
            for (std::size_t i = kPrefixLength; i < stem; ++i)
            {
                if (name[i] < '0' || name[i] > '9')
                    return false;
            }
            return true;
        }

        // True when the caster's centre is strictly farther than the threshold
        // from the main camera. A threshold <= 0 never skips; a non-finite
        // distance (NaN) never skips either, because NaN > x is false.
        inline bool ShouldSkipShadowCaster(float distanceSquared, int thresholdMetres)
        {
            if (thresholdMetres <= 0)
                return false;
            const float threshold = static_cast<float>(thresholdMetres);
            return distanceSquared > threshold * threshold;
        }

        inline float DistanceSquared(const float* a, const float* b)
        {
            const float dx = a[0] - b[0];
            const float dy = a[1] - b[1];
            const float dz = a[2] - b[2];
            return dx * dx + dy * dy + dz * dz;
        }

        // The shared Mesh* resources that are scrap. Fixed capacity, no
        // allocation: a mesh that does not fit is simply never skipped.
        // Not synchronised: Add/Remove run in Mesh::_setBounds and ~Mesh, which
        // Redux drives from the render thread. If a loader thread ever raced
        // them, only Live() (log count, fast path) could drift; Contains reads
        // aligned pointers and never skips a mesh that is not scrap.
        template <std::size_t Capacity>
        class ScrapMeshSet
        {
        public:
            bool Contains(const void* mesh) const
            {
                if (!mesh)
                    return false;
                for (std::size_t i = 0; i < Capacity; ++i)
                {
                    if (m_slots[i] == mesh)
                        return true;
                }
                return false;
            }

            // False when full (or null); true when present afterwards.
            bool Add(const void* mesh)
            {
                if (!mesh)
                    return false;
                if (Contains(mesh))
                    return true;
                for (std::size_t i = 0; i < Capacity; ++i)
                {
                    if (!m_slots[i])
                    {
                        m_slots[i] = mesh;
                        ++m_live;
                        return true;
                    }
                }
                return false;
            }

            bool Remove(const void* mesh)
            {
                if (!mesh)
                    return false;
                for (std::size_t i = 0; i < Capacity; ++i)
                {
                    if (m_slots[i] == mesh)
                    {
                        m_slots[i] = nullptr;
                        --m_live;
                        return true;
                    }
                }
                return false;
            }

            uint32_t Live() const { return m_live; }

        private:
            const void* m_slots[Capacity] = {};
            uint32_t m_live = 0;
        };

        // Telemetry only: numbers the distinct shadow cameras seen since the
        // last non-shadow traversal in order of first appearance (Ogre renders
        // the PSSM textures nearest split first). Never used for a decision, so
        // a wrong guess mislabels a counter and changes no pixel.
        constexpr uint32_t kTrackedCascades = 3;

        class ShadowCameraOrder
        {
        public:
            void Reset() { m_count = 0; }

            // 0..kTrackedCascades-1, or kTrackedCascades for any further camera.
            uint32_t IndexFor(const void* camera)
            {
                for (uint32_t i = 0; i < m_count; ++i)
                {
                    if (m_cameras[i] == camera)
                        return i;
                }
                if (m_count < kTrackedCascades)
                {
                    m_cameras[m_count] = camera;
                    return m_count++;
                }
                return kTrackedCascades;
            }

        private:
            const void* m_cameras[kTrackedCascades] = {};
            uint32_t m_count = 0;
        };
    }
}
