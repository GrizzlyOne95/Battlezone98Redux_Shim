# FXAA creation-import readiness

The opt-in DX11 presentation worker now waits for the exact renderer load to
finish before patching its creation imports. A successful wait retains the
module reference using the existing shared loader helper. A failed wait never
falls through to patching. Discovery retries transient import failures within
its existing attempt bound and reports incomplete discovery on expiry.

Imports installed on an earlier attempt are not rewritten while retrying the
other import: another observer may already chain through our hook. The shared
IAT helper also rejects a predecessor without committed executable protection,
including an unsnapped import-name RVA, before changing the IAT or recording
the forwarding address.

Offline validation on Windows, 2026-10-27:

- Release Win32 solution build passed (VS 2022 / v143).
- 146 non-rendering CTests passed, including the new IAT readiness test.
- The new test rejects an unresolved RVA and a readable data pointer, checks
  that failure leaves the slot/original untouched, retries after resolution,
  preserves the original across a repeated install, and rejects an installed
  hook without a usable predecessor. Missing optional imports stay NotFound.
- Rendering tests were excluded from the final CTest run. An earlier WARP
  terrain test was stopped after it failed to finish promptly; the three
  frame-bridge hardware tests were never run.

No game launch or deployment occurred. Native Windows/GOG, Windows/Steam,
Proton and Wine loader timing remain unverified for this change. Existing
store-neutral loader APIs and module discovery are preserved. These fixes
address a startup hook race; they do not establish or fix the cause of the
separately observed harness GPU hangs.
