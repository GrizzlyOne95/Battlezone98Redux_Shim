// The SDK record copy honours the caller's declared capacity.
//
// Audit item P1-8 (Docs/CODE_AUDIT_20260925.md): pollEvent and
// captureDeveloperSnapshot assigned a whole OpenShimEvent /
// OpenShimDeveloperSnapshot into the caller's buffer, so a shim built against
// a later, longer record would have written past a v2 caller's struct, and a
// caller built against a longer record than the shim was never told how much
// of its buffer had been filled. These tests pin the v2 layouts the copies
// promise and the copy's behaviour for exact, short, longer and nonsensical
// capacities.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "BZROpenShim.h"
#include "openshim_sdk_record_copy.h"

#include <cstddef>
#include <cstdio>
#include <cstring>

namespace
{
    using namespace BZROpenShim;

    int g_failures = 0;

    void Require(bool condition, const char* message)
    {
        if (!condition)
        {
            std::fprintf(stderr, "openshim_sdk_record_copy_tests: FAIL %s\n", message);
            ++g_failures;
        }
    }

    constexpr uint32_t kEventV2Size = 120u;
    constexpr uint32_t kSnapshotV2Size = 96u;

    OpenShimEvent MakeEvent()
    {
        OpenShimEvent e = {};
        e.type = static_cast<uint32_t>(OpenShimEventType::PatchingCompleted);
        e.threadId = 0x1234u;
        e.sequence = 42u;
        e.qpc = 0x1122334455667788ull;
        e.tickMs = 99u;
        e.arg0 = 7u;
        e.arg1 = 8u;
        std::strcpy(e.text, "patching");
        return e;
    }

    void TestLayouts()
    {
        Require(sizeof(OpenShimEvent) == kEventV2Size, "OpenShimEvent v2 is 120 bytes");
        Require(sizeof(OpenShimDeveloperSnapshot) == kSnapshotV2Size,
                "OpenShimDeveloperSnapshot v2 is 96 bytes");
        Require(offsetof(OpenShimEvent, structSize) == 0, "structSize leads the event");
        Require(offsetof(OpenShimDeveloperSnapshot, structSize) == 0, "structSize leads the snapshot");
        OpenShimEvent defaulted;
        Require(SdkRecord::DeclaredCapacity(&defaulted) == kEventV2Size,
                "a default-constructed record declares its own size");
    }

    void TestExactCapacity()
    {
        const OpenShimEvent source = MakeEvent();
        OpenShimEvent out; // structSize = sizeof(OpenShimEvent) by the header
        const uint32_t written = SdkRecord::CopyToCaller(&out, source, kEventV2Size);
        Require(written == kEventV2Size, "an exact-size buffer takes the whole record");
        Require(out.structSize == kEventV2Size, "structSize reports the bytes written");
        Require(out.sequence == 42u && out.qpc == source.qpc && out.arg1 == 8u,
                "the fields arrive");
        Require(std::strcmp(out.text, "patching") == 0, "the text arrives");

        OpenShimDeveloperSnapshot snapshotSource = {};
        snapshotSource.shimVersion = 0x01000021u;
        snapshotSource.localPlayerX = 1.5f;
        OpenShimDeveloperSnapshot snapshotOut;
        Require(SdkRecord::CopyToCaller(&snapshotOut, snapshotSource, kSnapshotV2Size) ==
                    kSnapshotV2Size,
                "an exact-size snapshot buffer takes the whole record");
        Require(snapshotOut.structSize == kSnapshotV2Size && snapshotOut.shimVersion == 0x01000021u &&
                    snapshotOut.localPlayerX == 1.5f,
                "the snapshot fields arrive");
    }

    void TestShortBufferIsRefusedUntouched()
    {
        const OpenShimEvent source = MakeEvent();
        alignas(OpenShimEvent) unsigned char raw[sizeof(OpenShimEvent)];
        std::memset(raw, 0xAB, sizeof(raw));
        const uint32_t declared = 64u;
        std::memcpy(raw, &declared, sizeof(declared));
        auto* out = reinterpret_cast<OpenShimEvent*>(raw);
        Require(SdkRecord::CopyToCaller(out, source, kEventV2Size) == 0,
                "a buffer shorter than the v2 layout is refused");
        Require(SdkRecord::DeclaredCapacity(raw) == 64u, "a refused buffer keeps its structSize");
        bool untouched = true;
        for (size_t i = sizeof(declared); i < sizeof(raw); ++i)
            untouched = untouched && raw[i] == 0xAB;
        Require(untouched, "a refused buffer is not written at all");
        Require(SdkRecord::CopyToCaller<OpenShimEvent>(nullptr, source, kEventV2Size) == 0,
                "a null buffer is refused");
    }

    // A caller compiled against a later header than this shim: its record is
    // longer, and the appended tail must be left alone and reported unfilled.
    struct EventFromNewerHeader
    {
        OpenShimEvent base;
        uint64_t appended = 0xFEEDFACECAFEBEEFull;
    };

    void TestLongerCallerIsToldWhatWasFilled()
    {
        const OpenShimEvent source = MakeEvent();
        EventFromNewerHeader out;
        out.base.structSize = sizeof(EventFromNewerHeader);
        const uint32_t written = SdkRecord::CopyToCaller(&out.base, source, kEventV2Size);
        Require(written == kEventV2Size, "only this shim's record length is written");
        Require(out.base.structSize == kEventV2Size,
                "the caller learns that the appended fields were not filled");
        Require(out.appended == 0xFEEDFACECAFEBEEFull, "the appended field is untouched");
        Require(out.base.sequence == 42u, "the v2 fields still arrive");

        OpenShimEvent nonsense;
        nonsense.structSize = 0xFFFFFFFFu;
        Require(SdkRecord::CopyToCaller(&nonsense, source, kEventV2Size) == kEventV2Size &&
                    nonsense.structSize == kEventV2Size,
                "an absurd capacity is clamped to the record");
    }

    // A caller compiled against an earlier layout than this shim: the shim's
    // record is longer, and the copy must stop at the caller's capacity.
    struct GrownRecord
    {
        uint32_t structSize = sizeof(GrownRecord);
        uint32_t a = 0;
        uint64_t b = 0;
    };

    void TestOlderCallerGetsOnlyItsPrefix()
    {
        GrownRecord source;
        source.a = 7u;
        source.b = 9u;
        GrownRecord out;
        out.structSize = 8u; // the caller's header knew only structSize and a
        out.a = 0xDEADBEEFu;
        out.b = 0x5A5A5A5A5A5A5A5Aull;
        const uint32_t written = SdkRecord::CopyToCaller(&out, source, 8u);
        Require(written == 8u, "the copy stops at the caller's capacity");
        Require(out.structSize == 8u && out.a == 7u, "the prefix arrives");
        Require(out.b == 0x5A5A5A5A5A5A5A5Aull, "bytes past the caller's capacity are untouched");
    }
}

int main()
{
    TestLayouts();
    TestExactCapacity();
    TestShortBufferIsRefusedUntouched();
    TestLongerCallerIsToldWhatWasFilled();
    TestOlderCallerGetsOnlyItsPrefix();

    if (g_failures == 0)
        std::printf("openshim_sdk_record_copy_tests: all checks passed\n");
    return g_failures == 0 ? 0 : 1;
}
