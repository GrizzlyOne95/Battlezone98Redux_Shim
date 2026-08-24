// file_io_hooks.h
// BZR Open Shim - automatic TRN save normalization hooks
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim
{
    // Installs only the main-executable CreateFile hooks. Safe to call during
    // process attach before the game opens its stock logger files.
    void ApplyEarlyGameLogHooks();

    // Compatibility/safety layer for .trn writes outside Redux's corrected
    // producer. Canonicalizes tracked files after close and leaves unsupported
    // UTF-16 untouched instead of guessing an encoding.
    void ApplyTrnSaveNormalizeHooks();
}
