#include "d3d11_buffer_mirror_policy.h"
#include <cstdio>

using namespace BZROpenShim::D3D11BufferMirror;

int main() {
    int failures = 0;
    const auto check = [&failures](bool ok, const char* text) {
        if (!ok) { std::fprintf(stderr, "FAIL: %s\n", text); ++failures; }
    };
    const auto same = [](UploadPlan plan, UploadKind kind, size_t offset, size_t count) {
        return plan.kind == kind && plan.offset == offset && plan.count == count;
    };

    // Ranges.
    check(RangeFits(0, 100, 100), "whole buffer fits");
    check(RangeFits(100, 0, 100), "empty range at the end fits");
    check(!RangeFits(1, 100, 100), "one byte past the end does not fit");
    check(!RangeFits(101, 0, 100), "offset past the end does not fit");
    check(!RangeFits(8, static_cast<size_t>(-4), 100), "wrapping length does not fit");

    // Default usage: the written range, with a box.
    check(same(PlanUpload(UsageDefault, LockNormal, 16, 32, 100), UploadKind::UpdateSubresource, 16, 32),
          "default + normal updates the range");
    check(same(PlanUpload(UsageDefault, LockDiscard, 0, 100, 100), UploadKind::UpdateSubresource, 0, 100),
          "default + discard updates the range");
    check(same(PlanUpload(UsageDefault, LockWriteOnly, 4, 4, 100), UploadKind::UpdateSubresource, 4, 4),
          "default + write-only updates the range");

    // Dynamic usage.
    check(same(PlanUpload(UsageDynamic, LockDiscard, 16, 32, 100), UploadKind::MapDiscard, 16, 32),
          "dynamic + discard maps discard for the range");
    check(same(PlanUpload(UsageDynamic, LockNoOverwrite, 16, 32, 100), UploadKind::MapNoOverwrite, 16, 32),
          "dynamic + no-overwrite maps no-overwrite for the range");
    check(same(PlanUpload(UsageDynamic, LockNormal, 16, 32, 100), UploadKind::MapDiscard, 0, 100),
          "dynamic + normal re-sends the whole buffer");
    check(same(PlanUpload(UsageDynamic, LockWriteOnly, 16, 32, 100), UploadKind::MapDiscard, 0, 100),
          "dynamic + write-only re-sends the whole buffer");

    // Staging usage.
    check(same(PlanUpload(UsageStaging, LockNormal, 8, 8, 100), UploadKind::MapWrite, 8, 8),
          "staging maps write for the range");

    // Nothing to send.
    check(PlanUpload(UsageDefault, LockReadOnly, 0, 100, 100).kind == UploadKind::None, "read sends nothing");
    check(PlanUpload(UsageDynamic, LockReadOnly, 0, 100, 100).kind == UploadKind::None, "dynamic read sends nothing");
    check(PlanUpload(UsageDefault, LockNormal, 0, 0, 100).kind == UploadKind::None, "empty range sends nothing");
    check(PlanUpload(UsageImmutable, LockNormal, 0, 10, 100).kind == UploadKind::None, "immutable sends nothing");
    check(PlanUpload(UsageDefault, LockNormal, 90, 20, 100).kind == UploadKind::None, "range past the end sends nothing");
    check(PlanUpload(7, LockNormal, 0, 10, 100).kind == UploadKind::None, "unknown usage sends nothing");

    return failures ? 1 : 0;
}
