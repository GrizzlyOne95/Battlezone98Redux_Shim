// mouse_every_frame.h
// BZR Open Shim - per-frame mouse look (experimental, single player)
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim
{
    // Redux's mouse channel reader (GOG 0x00623B20, BZ 1.5 giddi_read_channels)
    // adds the sim step into an accumulator and only applies the gathered mouse
    // deltas once it reaches 0.016666 s, so mouse steer and pitch update at
    // about 60 Hz whatever the frame rate. When
    // [Experimental] MouseEveryFrame = 1 (or OPENSHIM_MOUSE_EVERY_FRAME=1) the
    // reader compares against a shim-owned threshold instead of the shared
    // constant, and a wrapper around its TimeStep call sets that threshold to
    // a fraction of a millisecond in single player. Network games and paused
    // frames keep the stock 1/60 s bucket.
    void InitializeMouseEveryFrame();
}
