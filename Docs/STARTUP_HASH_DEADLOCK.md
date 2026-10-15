# Startup hashing and the Windows loader lock

Launching `battlezone98redux.exe misn07.bzn /edit` could leave OpenShim
1.0.0.50 running without a game window. A captured GOG 2.2.301 process using
`misn04.bzn /edit` was stopped before renderer initialization:

- The main thread was initializing Steam's client DLL through `SteamAPI_Init`,
  held the DLL loader initialization path, and requested BCrypt randomness.
- An OpenShim worker owned BCrypt's provider lock while opening SHA-256 and
  waited for a provider DLL to load.
- The main thread waited for that provider lock; the worker waited for DLL
  loading. The GOG executable can also load Steam's client, so distribution
  detection cannot make this operation safe.

Noninvasive native thread stacks and the BCrypt critical-section owner
established the cycle. Matching OpenShim symbols were unavailable; the exact
worker caller was correlated with source and the last startup log rather than
asserted from an unmatched PDB. Disabling the local bootstrap proxy allowed the
same misn07 command to initialize DX11 and load its mission with the terrain
addon still enabled.

## Fix

Move the existing asset-set streaming SHA-256 implementation, unchanged, into
`include/streaming_sha256.h`. `startup_file_sha256.h` combines that core with
Win32 file reads; it opens no crypto provider or DLL. The compatibility gate,
loader executable-identity API, and early preset migration use it. Missing,
unreadable, or size-changing files still fail without returning a digest.
Compatibility hashes stay uppercase; the loader and migration APIs retain their
lowercase output. Executable pins, byte settlement, and patch guards are unchanged.
The shared file/product revision advances to 1.0.0.53 so the suite updater
cannot replace the local fix with the existing bundled 1.0.0.52 payload.
This source revision does not publish a release or Workshop update.

This removes OpenShim's side of the provider/loader lock inversion without a
sleep, a store-specific workaround, or a bypass of executable verification.
It does not move work into `DllMain` or add a platform dependency.

## Regression checks

`startup_sha256_tests` covers standard empty, abc, 56-byte and million-a vectors,
incremental updates, padding/block/file-buffer boundaries, binary and Unicode
files, and unavailable input. On Windows a fixture DLL deliberately holds the
real loader lock while an already-running worker hashes a file. Hashing must
finish before the initializer returns. A separate negative-control process
attempts `LoadLibraryW` from that worker and must be detected as blocked.
The fixture's wait is bounded so a regression reports failure instead of
deadlocking the test runner.

Windows Release x86: all 109 CTest cases, 23 INI writer checks, 67 preset
migration checks, and the BZLoader host lifecycle test pass. The portable SHA
vector/chunking test also passes under Ubuntu 24.04/GCC. Live Windows/GOG
tests of `misn07.bzn /edit` and `misn04.bzn /edit` both initialize the simulation,
render through DX11 with OpenShim loaded, pass the original executable hash
and settled-byte gates, and exit normally with return code zero. Terrain stays
enabled; display settings and enabled-mod configuration are restored unchanged.
The BZLoader lifecycle test exercises the public hash callback and its stable
lowercase cached result; its digest also matches Windows `Get-FileHash`.
The final 1.0.0.53 build passes a further misn07 command smoke and
`verify_windows.ps1 -GamePath <GOG install>`, including deployment version
precedence over the bundled 1.0.0.52 and no stale patch configuration.
Editor-command evidence and deployment hashes are retained locally, outside
the public repository. Windows/Steam and Proton/Wine runtime qualification
remain unverified; this patch is not a release qualification for those lanes.
