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

    // Called from the patch thread once WaitForSignature reports the image has
    // settled, which on Steam is the first moment .text is decrypted.
    //
    // Two jobs, both diagnostic rather than corrective:
    //
    //   * confirm the delimiter write survived. It is applied under SteamStub's
    //     nose at DLL_PROCESS_ATTACH, and while .data is plaintext at rest on
    //     both stores (so the stub has no ciphertext to restore over it), a
    //     revert would otherwise be invisible. If the stock bytes are back, this
    //     says so loudly and re-applies.
    //   * verify the two .text push sites now that they are readable. At attach
    //     on Steam they are still ciphertext and are deliberately not required,
    //     so this is where a Steam run finally proves the delimiter belongs to
    //     the parser this patch believes it does.
    //
    // Safe to call when the fix is disabled or was never applied; it reports
    // and returns.
    void VerifyCliMultiParameterOptionFix();
}
