// file_io_hooks.h
// BZR Open Shim - automatic TRN save normalization hooks
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim
{
    // Installs startup-time file IAT hooks that track .trn writes and
    // normalize saved terrain files to Windows CRLF line endings after close.
    void ApplyTrnSaveNormalizeHooks();
}
