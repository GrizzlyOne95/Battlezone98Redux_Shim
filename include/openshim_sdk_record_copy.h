#pragma once

// openshim_sdk_record_copy.h
// BZR Open Shim - copying append-only SDK records into caller-owned buffers.
//
// Every record that crosses the SDK boundary (OpenShimEvent,
// OpenShimDeveloperSnapshot, the API tables) starts with a uint32_t
// structSize. On the way in it is the caller's capacity: the size of the
// record as the caller's header defined it. A shim built against a later,
// longer definition must not write past it, and a caller built against a
// later definition than the shim must be told how much was filled. So a copy
// writes min(capacity, sizeof(record)) bytes and sets structSize to that
// count, and refuses a capacity below the layout the API version promises
// (nothing shorter than the v2 layout has ever existed, so such a buffer is
// a caller bug, not an older caller).
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include <cstdint>
#include <cstring>
#include <type_traits>

namespace BZROpenShim::SdkRecord
{
    // The capacity the caller declared. The first field of every SDK record
    // is its structSize, so this reads correctly from any buffer that holds
    // at least that field.
    inline uint32_t DeclaredCapacity(const void* record)
    {
        uint32_t capacity = 0;
        std::memcpy(&capacity, record, sizeof(capacity));
        return capacity;
    }

    // Copies `source` into `out`, honouring the capacity `out` declares.
    // Returns the number of bytes written and leaves that count in the
    // caller's structSize, or returns 0 with `out` untouched when the
    // declared capacity is below `minimumBytes` (the record's promised
    // layout) or `out` is null.
    template <typename Record>
    uint32_t CopyToCaller(Record* out, const Record& source, uint32_t minimumBytes)
    {
        static_assert(std::is_trivially_copyable_v<Record>,
                      "SDK records are plain copyable data");
        static_assert(sizeof(Record) >= sizeof(uint32_t),
                      "an SDK record starts with its structSize");
        if (out == nullptr || minimumBytes < sizeof(uint32_t))
            return 0;
        const uint32_t capacity = DeclaredCapacity(out);
        if (capacity < minimumBytes)
            return 0;
        const uint32_t written =
            capacity < sizeof(Record) ? capacity : static_cast<uint32_t>(sizeof(Record));
        std::memcpy(out, &source, written);
        std::memcpy(out, &written, sizeof(written));
        return written;
    }
}
