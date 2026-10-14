// scavenger_process_guard.h
// BZR Open Shim - decision logic for the AI_Team_Compute_Other scavenger
// process guard (see Docs/SCAVENGER_NETPROCESS_OVERWRITE_20261014.md).
//
// Header-only and free of Windows and engine dependencies so that
// tests/scavenger_process_guard_tests.cpp can pin every verdict.
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cstddef>
#include <cstdint>

namespace BZROpenShim::ScavengerProcessGuard
{
    // The ScavengerProcess family on exact GOG Redux 2.2.301 has three
    // concrete vtables: ScavengerProcess itself plus ScavengerFriend and
    // ScavengerEnemy (RTTI hierarchy walk, 2026-10-14). A fourth slot is kept
    // free so a future qualified build can add one without a layout change.
    constexpr size_t kMaxVtables = 4;

    struct Config
    {
        uintptr_t vtables[kMaxVtables] = {};
        size_t count = 0;
    };

    // A usable configuration lists at least one vtable and no null entry.
    // An unusable one makes every object fail the guard, which is why the
    // installer refuses to patch with it instead of installing a call site
    // that would hide every scavenger from the AI.
    inline bool ConfigIsUsable(const Config& config)
    {
        if (config.count == 0 || config.count > kMaxVtables)
            return false;
        for (size_t i = 0; i < config.count; ++i)
        {
            if (config.vtables[i] == 0)
                return false;
            for (size_t j = 0; j < i; ++j)
            {
                if (config.vtables[j] == config.vtables[i])
                    return false;
            }
        }
        return true;
    }

    enum class Verdict
    {
        Accept,             // genuine ScavengerProcess-family instance
        NullProcess,        // GameObject+FC was null (the caller tests this, kept for completeness)
        UnreadableProcess,  // the process pointer or its vtable word faulted
        ForeignVtable,      // NetProcess, base AiProcess/SObject (destroying), or anything else
        BadConfig
    };

    // `vtableReadable` is false when reading the first word of the object
    // faulted. `vtable` is that first word otherwise.
    inline Verdict Classify(const Config& config, const void* process,
                            bool vtableReadable, uintptr_t vtable)
    {
        if (!ConfigIsUsable(config))
            return Verdict::BadConfig;
        if (!process)
            return Verdict::NullProcess;
        if (!vtableReadable)
            return Verdict::UnreadableProcess;
        for (size_t i = 0; i < config.count; ++i)
        {
            if (config.vtables[i] == vtable)
                return Verdict::Accept;
        }
        return Verdict::ForeignVtable;
    }

    inline const char* VerdictName(Verdict verdict)
    {
        switch (verdict)
        {
        case Verdict::Accept: return "accept";
        case Verdict::NullProcess: return "null-process";
        case Verdict::UnreadableProcess: return "unreadable-process";
        case Verdict::ForeignVtable: return "foreign-vtable";
        case Verdict::BadConfig: return "bad-config";
        }
        return "unknown";
    }

    // The vector handed back for every rejected process: an independent,
    // read-only 12-byte position whose y is -1.
    //
    // The sole caller (AI_Team_Compute_Other at 0x006A3961) copies x,y,z out of
    // the returned pointer, then promotes the scavenger's contribution to the
    // team map only when y > 0.0f (comiss against the constant at 0x008A2498).
    // Stock GetScrapPosition returns y = -1 for "no scrap position known", so
    // the caller's existing no-scrap path (state stays 0, loop continues with
    // the next object) is exactly what a rejected process must produce. The
    // caller never writes through the pointer, so the storage can be const.
    inline const float* NoScrapPosition()
    {
        static const float kNoScrap[3] = { 0.0f, -1.0f, 0.0f };
        return kNoScrap;
    }

    constexpr size_t kPositionYOffset = 4;
}
