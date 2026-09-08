// bzn_load_trace.h
// BZR Open Shim - mission (.bzn) load diagnostics
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// WHY THIS EXISTS
// ===============
//
// When a mission fails to load, the engine says exactly one thing:
//
//     Quiting Game because failed to load game files
//
// Everything before it is a stream of "(Scrap) is loading (obj #113)" lines
// that name the object's CLASS but not which object it was, and nothing after
// it says what went wrong. Diagnosing a bad .bzn therefore means hand-parsing
// the file and counting blocks to work out what "#114" was -- which is exactly
// what it took to find the 2026-09-07 misn04 failure.
//
// That failure is the case this module is built around. An agent hand-edited
// misn04.bzn and wrote LF line endings for the lines it touched, leaving a file
// that was CRLF everywhere except one run inside GameObject #114. The engine's
// ASCII reader is line-oriented on CRLF, so that run collapsed into a single
// unparseable line, the object's position failed to read, and the load aborted.
// git reported the working tree clean the whole time, because with
// core.autocrlf=true a mixed file normalizes to the same blob as a clean one.
//
// So this reports two things when the game opens a mission:
//
//   1. Structural defects, always. Mixed line endings (with the enclosing
//      GameObject index, which is the number the engine's own log stops on),
//      count fields that disagree with the blocks they count, duplicate labels
//      or sequence numbers, and pointer ids that resolve to nothing.
//
//   2. The full object table, gated behind Diagnostics/TraceBznLoad, so
//      "obj #114" can be read straight off as an ODF and a label without
//      opening the file at all.
//
// This is a reader. It never modifies the mission, and a file it cannot make
// sense of is reported and left alone.

#pragma once

#include <cstdint>

namespace BZROpenShim
{
    // Called from the CreateFile hooks when the game opens a path for reading.
    // Ignores everything that is not a .bzn, and is safe to call on every open:
    // it filters before it does any work. `desiredAccess` is the caller's
    // original access mask; write opens are left to the editor save path.
    void BznLoadTraceOnOpen(const wchar_t* absolutePath, uint32_t desiredAccess) noexcept;

    // ANSI call sites hand over the narrow path they were given; the conversion
    // happens here so the hook stays one line and needs no widening helper of
    // its own.
    void BznLoadTraceOnOpenA(const char* absolutePath, uint32_t desiredAccess) noexcept;

    // True when the per-object table is enabled. Exposed for the startup
    // banner; the structural report runs regardless.
    bool IsBznLoadTraceVerbose() noexcept;
}
