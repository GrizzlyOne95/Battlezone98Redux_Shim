# Map description bounds guard

Selecting a map with a description of 2,400 bytes or more can terminate Redux
2.2.301 with `FAST_FAIL_RANGE_CHECK_FAILURE`. The shared description loader
copies up to 2,400 bytes into its 2,400-byte local array, then rejects that
length as an invalid index for the terminating zero. A 3,020-byte
`arsenals.des` reproduced this exact state in a full crash dump.

`Map Description Bounds Guard` changes the copy-length comparison and clamp
from 2,400 to 2,399 in one guarded instruction span. Oversized descriptions
display their first 2,399 bytes. The stock terminator check, resource
acquisition/release, and shorter descriptions retain their existing behavior.
The signature must match uniquely; there is no address fallback. This applies
to the common loader used by the map description panes, including `.mpdes`
resources scoped through the existing waiting-room resource hooks.

The regression test executes both the registered replacement instructions and
the original instructions in an isolated Win32 x86 buffer. It covers empty,
short, boundary, oversized, and high-bit unsigned resource sizes, including the
3,020-byte failing resource. Native GOG loader bytes were independently checked
in a harness-launched game before writing the patch. Whole-image scanning
found one signature match at the established clamp site.

The local BzE Map Pack descriptions `arsenals.des`, `moonfall.des`,
`cloakers.des`, and `dragoons.des` were also shortened below the stock limit;
those installed content corrections and their original backups are separate
from this source change. No game DLL deployment is part of this branch's
validation. Steam and Proton/Wine runtime behavior remains unverified.
