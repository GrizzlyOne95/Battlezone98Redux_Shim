# Player field of view

Options → OpenShim Options → Video → **Field of View** selects Stock (80),
60, 70, 80, 90, 100, 110 or 120 degrees. Restart the game after changing it.
The shipped default is Stock, which installs no FOV hook.

The equivalent preference is `[Display] FieldOfView = 0` in `openshim.ini`.
Zero, a missing key or an invalid value keeps stock behavior. Hand editing
accepts whole degrees from 60 through 120.

These are **4:3 reference horizontal degrees**, following the engine's own
angle convention. The engine uses `0.75 * tan(baseFov / 2)` as its vertical
projection tangent, so widescreen displays show a larger horizontal angle.
For example, a base setting of 80 gives approximately 96.4 horizontal degrees
at 16:9, before any gameplay zoom. The option preserves the engine's zoom.

The override covers normal player/cockpit variants and chase view. Satellite,
free-camera and target-camera builders keep their own inputs. Cinematics can
inherit the current player angle, as stock cinematics inherit the current
camera record; explicit scripted view setters are not overridden.

## Native implementation and evidence

The released GOG 2.2.301 camera builder has a six-argument cdecl ABI and returns
its output record. It stores the angle at record offset `0x24`, the vertical
tangent at `0x28` and zoom at `0x30`. Its stock player input is float bits
`0x3FB2B8C2` (80 degrees in radians).

`scripts/patches.json` owns the builder and five guarded caller sites:
main-view initialization, three cockpit variants, and chase view. The hook
changes only that exact stock input from those callers. A single guarded
entry detour covers them; unrelated callers pass through. Missing or mismatched
catalog rows prevent installation. The shared FOV constant is never written.

Local baseline qualification used Frida against live GOG PID 21212 on
2026-10-19, launched with `bin/fov-research/baseline.ps1` through `BZRHarness.ps1`.
Executable SHA-256:
`8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413`.
The five caller guards and builder entry matched Ghidra's released-image
analysis. Mission initialization and cockpit entry produced 1.39626336 radians
with zoom 1; target-camera builders used separate angles. Scratch captures and
binary analysis output stay in ignored local build directories.

The Release x86 implementation was then deployed with
`scripts/Deploy-OpenShim.ps1`. `bin/fov-research/live.ps1 -Label custom -Degrees 100`
and the read-only `observe.py` probe confirmed 100.0000005 degrees, the expected
vertical tangent 0.89381522 and zoom 1 in live PID 14616. The same harness with
`-Label guard -Degrees 100 -Mismatch` intentionally corrupted one **catalog
guard**, leaving the executable untouched: PID 32352 logged that
`PlayerFovInitCall` differed, kept the builder entry unmodified and rendered
with the original 79.9999977-degree value. Temporary test preferences and the
catalog were restored byte-for-byte after each run.

Stock was independently retested in PID 16556: the builder entry remained
original and the record returned to 79.9999977 degrees. A main-thread native
transition probe (`transitions.py`, PID 29052) exercised chase, all three
cockpit variants and return to cockpit at 100 degrees with zoom 1. The lcbench
fixture declined satellite entry (mode stayed 0), so that run does not qualify
satellite rendering. Satellite passthrough is covered by static call-site
exclusion and the policy tests; an interactive satellite smoke remains pending.

Unit tests cover parsing, safe bounds, degree conversion and passthrough of
non-player/nonstandard camera inputs. All 112 Win32 CTests and all 91 Linux
CTests passed, along with the Release Win32 solution build, INI/migration checks
and loader host integration test. Linux tests ran in Ubuntu 24.04 under WSL;
this validates portable host code, not game execution under Proton or Wine.
Steam, Proton and Wine runtime behavior
remains unverified; their address and byte guards must pass independently.
Visual menu inspection is also unverified: the computer-use capture helper
failed with monitor-capture/access-denied errors on this desktop session.

`verify_windows.ps1 -GamePath <GOG install>` confirmed the deployed catalog
matches source, the real proxy loaded and the final session had no stale patch
configuration. Its overall result is FAIL because this development build and
the installed CR suite both report version 1.0.0.53: suite promotion can replace
the development build. Test launches entered the fixture mission directly,
bypassing the main-menu automatic staging trigger, and restored the user's INI
afterward; the full load chain was redeployed after testing. No release version
was assigned by this workstream.
