#include "ogre_profiler_algorithms.h"

#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits>

namespace
{
    using namespace BZROpenShim::OgreProfilerAlgorithms;

    [[noreturn]] void Fail(const char* message)
    {
        std::fprintf(stderr, "ogre_profiler_algorithms_tests: %s\n", message);
        std::exit(1);
    }

    void Require(bool condition, const char* message)
    {
        if (!condition)
            Fail(message);
    }

    void RequireNear(double actual, double expected, const char* message)
    {
        if (std::fabs(actual - expected) > 0.00001)
            Fail(message);
    }

    void TestHistogramAndFrameBuckets()
    {
        std::array<std::uint64_t, 4> buckets = { 1, 1, 2, 6 };
        RequireNear(PercentileFromHistogram(buckets, 10, 50, 250), 1.0,
            "histogram p50 did not use the containing bucket upper edge");
        RequireNear(PercentileFromHistogram(buckets, 10, 95, 250), 1.0,
            "histogram p95 was incorrect");
        RequireNear(PercentileFromHistogram(buckets, 0, 95, 250), 0.0,
            "empty histogram did not return zero");

        Require(FrameBucket(0) == 0, "zero frame time mapped outside bucket zero");
        Require(FrameBucket(249) == 0, "sub-bucket frame time mapped too high");
        Require(FrameBucket(250) == 1, "bucket boundary mapped incorrectly");
        Require(FrameBucket(1000000) == kFrameTimeBucketCount - 1,
            "frame overflow did not clamp to the final bucket");
    }

    void TestWorkloadBuckets()
    {
        Require(VertexBucket(1023) == 0 && VertexBucket(1024) == 1,
            "vertex 1K boundary failed");
        Require(VertexBucket(32767) == 6 && VertexBucket(32768) == 7,
            "vertex overflow boundary failed");
        Require(MatrixBucket(8) == 0 && MatrixBucket(9) == 1,
            "matrix 8 boundary failed");
        Require(MatrixBucket(64) == 3 && MatrixBucket(65) == 4,
            "matrix overflow boundary failed");
        Require(LatencyBucketFromMicroseconds(24) == 0 &&
                LatencyBucketFromMicroseconds(25) == 1 &&
                LatencyBucketFromMicroseconds(799) == 5 &&
                LatencyBucketFromMicroseconds(800) == 6,
            "latency boundaries failed");
    }

    void TestDuplicateSemantics()
    {
        std::uintptr_t key = 0;
        std::uint64_t frame = 0;
        Require(!UpdateAndCheckDuplicate(key, frame, 0x1000, 7),
            "first entity observation was marked duplicate");
        Require(UpdateAndCheckDuplicate(key, frame, 0x1000, 7),
            "same entity in same frame was not marked duplicate");
        Require(!UpdateAndCheckDuplicate(key, frame, 0x1000, 8),
            "same entity in next frame was marked duplicate");
        Require(!UpdateAndCheckDuplicate(key, frame, 0x2000, 8),
            "different entity in same frame was marked duplicate");
    }

    void TestBoundedContributorRanking()
    {
        std::array<ContributorRank, 3> top = {};
        std::size_t count = 0;
        InsertContributor(top, count, { 4, 40, 1 });
        InsertContributor(top, count, { 2, 20, 1 });
        InsertContributor(top, count, { 3, 30, 1 });
        InsertContributor(top, count, { 1, 50, 1 });
        Require(count == 3, "bounded contributor table exceeded capacity");
        Require(top[0].key == 1 && top[1].key == 4 && top[2].key == 3,
            "higher-cost contributor did not replace the bounded tail");
        InsertContributor(top, count, { 9, 10, 100 });
        Require(top[2].key == 3, "low-cost contributor displaced a ranked entry");
    }

    void TestProfilerStates()
    {
        Require(ComputeProfilerState(false, false, false, false, false, false, false) ==
                ProfilerState::Disabled, "disabled state failed");
        Require(ComputeProfilerState(true, false, false, false, false, false, false) ==
                ProfilerState::WaitingForOgre, "waiting-for-Ogre state failed");
        Require(ComputeProfilerState(true, true, true, false, false, false, false) ==
                ProfilerState::OgreReady, "Ogre-ready state failed");
        Require(ComputeProfilerState(true, true, true, true, true, false, false) ==
                ProfilerState::WaitingForDX11, "waiting-for-Present state failed");
        Require(ComputeProfilerState(true, true, true, true, true, true, false) ==
                ProfilerState::FullyActive, "fully-active state failed");
        Require(ComputeProfilerState(true, true, false, true, true, false, true) ==
                ProfilerState::PartialDiagnostics, "partial diagnostics state failed");
        Require(ComputeProfilerState(true, true, false, false, false, false, false) ==
                ProfilerState::Failed, "failed state failed");
    }

    void TestConfigurationPrecedence()
    {
        RequestDecision decision = ResolveRequest(false, nullptr, false, nullptr, true);
        Require(decision.enabled && decision.source == RequestSource::BuildDefault,
            "build-default config decision failed");
        decision = ResolveRequest(false, nullptr, true, "off", true);
        Require(!decision.enabled && decision.source == RequestSource::Ini,
            "INI did not override build default");
        decision = ResolveRequest(true, "YES", true, "off", false);
        Require(decision.enabled && decision.source == RequestSource::Environment,
            "environment did not override INI");
        Require(!StringIsTruthy("FALSE") && !StringIsTruthy("0") &&
                StringIsTruthy("1") && StringIsTruthy("enabled"),
            "truthy parser semantics changed");
    }

    void TestChunkNameClassificationPrimitive()
    {
        Require(ContainsAsciiCaseInsensitive("iechunk1.mesh", "chunk"),
            "lowercase chunk mesh was not classified");
        Require(ContainsAsciiCaseInsensitive("Redux/CHUNK_42", "chunk"),
            "mixed-case chunk entity was not classified");
        Require(!ContainsAsciiCaseInsensitive("avtank.mesh", "chunk"),
            "ordinary vehicle mesh was classified as chunk-like");
        Require(!ContainsAsciiCaseInsensitive(nullptr, "chunk") &&
                !ContainsAsciiCaseInsensitive("chunk", ""),
            "empty chunk classifier input was accepted");
    }

    void TestNativeTransientChunkMeshClassification()
    {
        Require(IsNativeTransientChunkMeshName("chunk1/chunk1.mesh"),
            "stock chunk1 mesh was not classified");
        Require(IsNativeTransientChunkMeshName("CHUNK2/CHUNK2.MESH"),
            "stock chunk2 mesh classification was not case-insensitive");
        Require(!IsNativeTransientChunkMeshName("chunk3/chunk3.mesh") &&
                !IsNativeTransientChunkMeshName("vehicles/chunk1/chunk1.mesh") &&
                !IsNativeTransientChunkMeshName("iechunk1.mesh") &&
                !IsNativeTransientChunkMeshName(nullptr),
            "non-stock or non-exact mesh was classified as native transient debris");
    }

    void TestDynamicAlphaDepthQuantization()
    {
        RequireNear(QuantizeDynamicAlphaDepthKey(31.0f, 8), 24.0,
            "alpha depth key did not round down to the configured bucket");
        RequireNear(QuantizeDynamicAlphaDepthKey(32.0f, 8), 32.0,
            "alpha depth key moved across an exact bucket boundary");
        RequireNear(QuantizeDynamicAlphaDepthKey(-1.0f, 8), -8.0,
            "negative near-camera alpha depth key rounded in the wrong direction");
        RequireNear(QuantizeDynamicAlphaDepthKey(31.0f, 1), 31.0,
            "disabled alpha depth quantization changed the key");
        const float infinity = std::numeric_limits<float>::infinity();
        Require(std::isinf(QuantizeDynamicAlphaDepthKey(infinity, 8)),
            "non-finite alpha depth key was modified");
    }

    void TestThunkAndDetourValidation()
    {
        std::array<std::uint8_t, 32> image = {};
        image[0] = 0xE9;
        const std::int32_t first = 5;
        std::memcpy(image.data() + 1, &first, sizeof(first));
        image[10] = 0xE9;
        const std::int32_t second = 5;
        std::memcpy(image.data() + 11, &second, sizeof(second));
        image[20] = 0x55;

        ThunkResolution resolved = ResolveRel32Thunks(image.data(), image.size(), 0, 2);
        Require(resolved.valid && resolved.implementationOffset == 20 && resolved.depth == 2,
            "bounded rel32 thunk chain did not resolve");
        Require(!ResolveRel32Thunks(image.data(), image.size(), 0, 1).valid,
            "thunk chain exceeded maximum depth without failing");
        const std::int32_t invalid = 1000;
        std::memcpy(image.data() + 1, &invalid, sizeof(invalid));
        Require(!ResolveRel32Thunks(image.data(), image.size(), 0, 2).valid,
            "out-of-image thunk destination was accepted");

        const std::uint8_t expected[5] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };
        std::uint8_t actual[5] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };
        Require(ValidateDetourPrologue(actual, expected, 5, 16),
            "supported detour prologue failed validation");
        actual[4] = 0;
        Require(!ValidateDetourPrologue(actual, expected, 5, 16),
            "mismatched detour prologue was accepted");
        Require(!ValidateDetourPrologue(expected, expected, 4, 16),
            "undersized detour patch was accepted");
    }

    void TestCsvSchema()
    {
        const char* expected =
            "tick_ms,fps,frame_mean_ms,frame_p50_ms,frame_p95_ms,frame_p99_ms,frame_max_ms,"
            "anim_calls,anim_render_driven,anim_external,anim_ms_per_frame,nonblend_ms_per_frame,"
            "skin_calls,skin_vertices,skin_ms_per_frame,dup_anim_same_frame,dup_skin_same_frame,"
            "orphan_skin_calls,matrix_avg,matrix_max,map_calls,map_during_anim,map_during_blend,"
            "map_ms_per_frame,update_subresource_calls,update_during_anim,draw_calls,draw_indexed_calls,"
            "draw_instanced_calls,draw_indexed_instanced_calls";
        Require(std::strcmp(kCsvHeader, expected) == 0, "CSV header schema changed");
        std::size_t columns = 1;
        for (const char* ch = kCsvHeader; *ch; ++ch)
            columns += *ch == ',' ? 1u : 0u;
        Require(columns == 30, "CSV column count changed");
    }
}

int main()
{
    TestHistogramAndFrameBuckets();
    TestWorkloadBuckets();
    TestDuplicateSemantics();
    TestBoundedContributorRanking();
    TestProfilerStates();
    TestConfigurationPrecedence();
    TestChunkNameClassificationPrimitive();
    TestNativeTransientChunkMeshClassification();
    TestDynamicAlphaDepthQuantization();
    TestThunkAndDetourValidation();
    TestCsvSchema();
    std::puts("ogre_profiler_algorithms_tests: all tests passed");
    return 0;
}
