// cli_multiparam_parser.h
// BZR Open Shim - command-line multi-parameter option compatibility fix
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

namespace BZROpenShim
{
    // Repairs command-line options whose own value grammar contains a comma
    // (the canonical case is -shellmap:<W>,<H>) by removing the comma from the
    // top-level tokenizer's delimiter set, which is what splits the value away
    // from its option before the option's own sscanf ever sees it.
    //
    // MUST be called synchronously from DllMain. The stock parser runs from
    // WinMain almost immediately after CRT startup, long before RunPatcher's
    // WaitForSignature poll on the patch thread can win the race.
    void ApplyCliMultiParameterOptionFix();
}
