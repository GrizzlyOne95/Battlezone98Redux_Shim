// music_refill_catchup.h
// BZR Open Shim - keep the music stream's writer level with the play cursor
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim
{
    // The music decoder thread refills one 3/16 s chunk per DirectSound
    // notification, but the notifications share one auto-reset event, so two
    // that fire before the thread wakes count once and the writer falls a
    // chunk behind for the rest of the track. Enough misses replay stale
    // audio (the "scratched CD" skip). Unless [Fixes] MusicRefillCatchUp = 0
    // (or OPENSHIM_DISABLE_MUSIC_REFILL_CATCHUP=1) each wake refills every
    // chunk the play cursor has passed and skips stale wakes. Client-local
    // audio only, so it also runs in network games.
    void InitializeMusicRefillCatchUp();
}
