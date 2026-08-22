#pragma once

#include <algorithm>
#include <array>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cmath>

namespace BZROpenShim
{
namespace OgreProfilerAlgorithms
{
    constexpr std::size_t kFrameTimeBucketCount = 401;
    constexpr std::uint64_t kFrameTimeBucketUs = 250;

    enum class ProfilerState : std::uint32_t
    {
        Disabled,
        WaitingForOgre,
        OgreReady,
        WaitingForRenderer,
        FullyActive,
        PartialDiagnostics,
        Failed
    };

    enum class RequestSource : std::uint32_t
    {
        BuildDefault,
        Ini,
        Environment
    };

    struct RequestDecision
    {
        bool enabled = false;
        RequestSource source = RequestSource::BuildDefault;
    };

    inline bool StringIsTruthy(const char* value)
    {
        if (!value || !*value)
            return false;

        char normalized[8] = {};
        std::size_t length = 0;
        while (value[length] && length + 1 < sizeof(normalized))
        {
            normalized[length] = static_cast<char>(
                std::tolower(static_cast<unsigned char>(value[length])));
            ++length;
        }
        if (value[length] != '\0')
            return true;
        normalized[length] = '\0';
        return std::strcmp(normalized, "0") != 0 &&
            std::strcmp(normalized, "false") != 0 &&
            std::strcmp(normalized, "no") != 0 &&
            std::strcmp(normalized, "off") != 0;
    }

    inline bool ContainsAsciiCaseInsensitive(const char* text, const char* token)
    {
        if (!text || !token || !*token)
            return false;
        for (const char* start = text; *start; ++start)
        {
            const char* haystack = start;
            const char* needle = token;
            while (*haystack && *needle &&
                   std::tolower(static_cast<unsigned char>(*haystack)) ==
                       std::tolower(static_cast<unsigned char>(*needle)))
            {
                ++haystack;
                ++needle;
            }
            if (!*needle)
                return true;
        }
        return false;
    }

    inline bool EqualsAsciiCaseInsensitive(const char* left, const char* right)
    {
        if (!left || !right)
            return false;
        while (*left && *right)
        {
            if (std::tolower(static_cast<unsigned char>(*left)) !=
                std::tolower(static_cast<unsigned char>(*right)))
            {
                return false;
            }
            ++left;
            ++right;
        }
        return *left == '\0' && *right == '\0';
    }

    inline bool IsNativeTransientChunkMeshName(const char* meshName)
    {
        return EqualsAsciiCaseInsensitive(meshName, "chunk1/chunk1.mesh") ||
            EqualsAsciiCaseInsensitive(meshName, "chunk2/chunk2.mesh");
    }

    inline float QuantizeDynamicAlphaDepthKey(float key, std::uint32_t stride)
    {
        if (stride <= 1 || !std::isfinite(key))
            return key;
        const float width = static_cast<float>(stride);
        return std::floor(key / width) * width;
    }

    inline RequestDecision ResolveRequest(
        bool environmentPresent,
        const char* environmentValue,
        bool iniPresent,
        const char* iniValue,
        bool buildDefault)
    {
        if (environmentPresent)
            return { StringIsTruthy(environmentValue), RequestSource::Environment };
        if (iniPresent)
            return { StringIsTruthy(iniValue), RequestSource::Ini };
        return { buildDefault, RequestSource::BuildDefault };
    }

    inline ProfilerState ComputeProfilerState(
        bool enabled,
        bool ogreInstallAttempted,
        bool ogreHooks,
        bool rendererCreationObserved,
        bool backendContextObserved,
        bool present,
        bool partialObserver)
    {
        if (!enabled)
            return ProfilerState::Disabled;
        if (!ogreInstallAttempted)
            return ProfilerState::WaitingForOgre;
        if (ogreHooks && backendContextObserved && present)
            return ProfilerState::FullyActive;
        if (ogreHooks && !rendererCreationObserved)
            return ProfilerState::OgreReady;
        if (ogreHooks)
            return ProfilerState::WaitingForRenderer;
        if (partialObserver || rendererCreationObserved ||
            backendContextObserved || present)
            return ProfilerState::PartialDiagnostics;
        return ProfilerState::Failed;
    }

    inline std::size_t FrameBucket(std::uint64_t microseconds)
    {
        const std::size_t bucket = static_cast<std::size_t>(
            microseconds / kFrameTimeBucketUs);
        return (std::min)(bucket, kFrameTimeBucketCount - 1);
    }

    template <std::size_t N>
    inline double PercentileFromHistogram(
        const std::array<std::uint64_t, N>& buckets,
        std::uint64_t samples,
        unsigned percentile,
        std::uint64_t bucketWidthUs)
    {
        if (!samples || !bucketWidthUs || percentile == 0 || percentile > 100)
            return 0.0;
        const std::uint64_t target = (samples * percentile + 99u) / 100u;
        std::uint64_t cumulative = 0;
        for (std::size_t i = 0; i < buckets.size(); ++i)
        {
            cumulative += buckets[i];
            if (cumulative >= target)
                return static_cast<double>((i + 1) * bucketWidthUs) / 1000.0;
        }
        return static_cast<double>(buckets.size() * bucketWidthUs) / 1000.0;
    }

    inline std::size_t VertexBucket(std::size_t vertices)
    {
        if (vertices < 1024) return 0;
        if (vertices < 2048) return 1;
        if (vertices < 4096) return 2;
        if (vertices < 8192) return 3;
        if (vertices < 12288) return 4;
        if (vertices < 16384) return 5;
        if (vertices < 32768) return 6;
        return 7;
    }

    inline std::size_t MatrixBucket(std::size_t matrices)
    {
        if (matrices <= 8) return 0;
        if (matrices <= 16) return 1;
        if (matrices <= 32) return 2;
        if (matrices <= 64) return 3;
        return 4;
    }

    inline std::size_t LatencyBucketFromMicroseconds(std::uint64_t microseconds)
    {
        if (microseconds < 25) return 0;
        if (microseconds < 50) return 1;
        if (microseconds < 100) return 2;
        if (microseconds < 200) return 3;
        if (microseconds < 400) return 4;
        if (microseconds < 800) return 5;
        return 6;
    }

    inline bool UpdateAndCheckDuplicate(
        std::uintptr_t& previousKey,
        std::uint64_t& previousFrame,
        std::uintptr_t key,
        std::uint64_t frame)
    {
        const bool duplicate = previousKey == key && previousFrame == frame;
        previousKey = key;
        previousFrame = frame;
        return duplicate;
    }

    struct ContributorRank
    {
        std::uintptr_t key = 0;
        std::uint64_t primary = 0;
        std::uint64_t secondary = 0;
    };

    inline bool RanksBefore(const ContributorRank& left, const ContributorRank& right)
    {
        if (left.primary != right.primary)
            return left.primary > right.primary;
        if (left.secondary != right.secondary)
            return left.secondary > right.secondary;
        return left.key < right.key;
    }

    template <std::size_t N>
    inline void InsertContributor(
        std::array<ContributorRank, N>& top,
        std::size_t& count,
        const ContributorRank& candidate)
    {
        if (!candidate.key || N == 0)
            return;
        std::size_t position = 0;
        while (position < count && !RanksBefore(candidate, top[position]))
            ++position;
        if (position >= N)
            return;
        const std::size_t newCount = (std::min)(count + 1, N);
        for (std::size_t i = newCount - 1; i > position; --i)
            top[i] = top[i - 1];
        top[position] = candidate;
        count = newCount;
    }

    struct ThunkResolution
    {
        bool valid = false;
        std::size_t implementationOffset = 0;
        unsigned depth = 0;
    };

    inline ThunkResolution ResolveRel32Thunks(
        const std::uint8_t* image,
        std::size_t imageSize,
        std::size_t exportOffset,
        unsigned maximumDepth)
    {
        if (!image || exportOffset >= imageSize)
            return {};
        std::size_t current = exportOffset;
        unsigned depth = 0;
        while (image[current] == 0xE9)
        {
            if (depth == maximumDepth || current + 5 > imageSize)
                return {};
            std::int32_t relative = 0;
            std::memcpy(&relative, image + current + 1, sizeof(relative));
            const std::int64_t destination =
                static_cast<std::int64_t>(current) + 5 + relative;
            if (destination < 0 || static_cast<std::uint64_t>(destination) >= imageSize ||
                static_cast<std::size_t>(destination) == current)
            {
                return {};
            }
            current = static_cast<std::size_t>(destination);
            ++depth;
        }
        return { true, current, depth };
    }

    inline bool ValidateDetourPrologue(
        const std::uint8_t* actual,
        const std::uint8_t* expected,
        std::size_t length,
        std::size_t maximumLength)
    {
        return actual && expected && length >= 5 && length <= maximumLength &&
            std::memcmp(actual, expected, length) == 0;
    }

    constexpr char kCsvHeader[] =
        "tick_ms,fps,frame_mean_ms,frame_p50_ms,frame_p95_ms,frame_p99_ms,frame_max_ms,"
        "anim_calls,anim_render_driven,anim_external,anim_ms_per_frame,nonblend_ms_per_frame,"
        "skin_calls,skin_vertices,skin_ms_per_frame,dup_anim_same_frame,dup_skin_same_frame,"
        "orphan_skin_calls,matrix_avg,matrix_max,map_calls,map_during_anim,map_during_blend,"
        "map_ms_per_frame,update_subresource_calls,update_during_anim,draw_calls,draw_indexed_calls,"
        "draw_instanced_calls,draw_indexed_instanced_calls";
}
}
