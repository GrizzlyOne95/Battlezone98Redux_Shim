// file_io_hooks.h
// BZR Open Shim - automatic TRN save normalization hooks
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once
#include <cstdint>
#include <filesystem>
#include <string>

namespace BZROpenShim
{
    // Validates the original thiscall dialog target before a catalog CALL edit.
    void* PrepareEditorSaveDialogHook(uint32_t callAddress);
    // Installs OpenShim's runtime policy into the bootstrap file-I/O seam:
    // terrain-atlas routing, TRN write tracking, BZN source tracking and load
    // tracing, and shader-cache priming. The seam itself, and the early log
    // routing, belong to the bootstrap and are already running by the time
    // this is called -- see include/bootstrap_file_io.h.
    //
    // A pointer store, so it is safe from DllMain and is deliberately done as
    // early as possible: until it runs, file opens get bootstrap behaviour
    // only.
    bool InstallFileIoProvider();

    // Compatibility/safety layer for .trn writes outside Redux's corrected
    // producer. Canonicalizes tracked files after close and leaves unsupported
    // UTF-16 untouched instead of guessing an encoding.
    void ApplyTrnSaveNormalizeHooks();

    // Folder the engine opened '<base>.bzn' from (any read open, whatever
    // the editor save setting), or empty when unseen or two folders hold that
    // name. Lets map-folder lookups find Workshop items on another Steam
    // library drive, which the gameDir-derived roots never search.
    std::filesystem::path FindLoadedMapFolder(const std::string& base);
}
