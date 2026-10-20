// music_single_fill.h
// BZR Open Shim - decode each new music track's first buffer once
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim
{
    // Starting a music track (GOG 0x004378F0, on the main thread) builds the
    // streaming ogg sound, whose constructor decodes a full 3 s DirectSound
    // buffer, and then plays it through OggManager::Play (0x0043F320), which
    // resets the stream to sample 0 and decodes the same 3 s again. The first
    // decode is never heard. Unless [Fixes] MusicSingleFill = 0 (or
    // OPENSHIM_DISABLE_MUSIC_SINGLE_FILL=1) the constructor's fill call is
    // replaced with its stack cleanup, which removes about a quarter to a
    // third of the main-thread stall at each track change. Client-local audio
    // only, so it also runs in network games.
    void InitializeMusicSingleFill();
}
