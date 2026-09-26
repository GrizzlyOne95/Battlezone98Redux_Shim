# Agent patch workflow

Read this document for work that changes OpenShim patch sites, named address resolution, signatures, patch registration, test deployment, or their validation. It is intentionally separate from the always-loaded root instructions.

## Address configuration

`scripts/patches.json` is the source for build-specific patterns and offsets:

- `patches` and `globals` describe sites the shim overwrites.
- `resolves` describes addresses the shim only calls or reads. Resolve these with `HookEngine::ResolveNamedAddress("Name")` instead of adding feature-local pattern/mask arrays.
- A resolve supports `pattern` (IDA syntax with `??` wildcards), signed `offset`, `mode` (`address`, `rel32_target`, or `abs32_operand` for a data global read out of a code site that uses it; `include/engine_globals.h` is where feature code gets those), `fallback`, `prefer` (`scan` by default or `fallback`), `require_unique`, and a mandatory `identity` note.
- A `patches` entry without `require_unique` takes its `fallback` after a signature miss only when its own pattern is present at `fallback - offset`; the byte guard is then the `expected_size` bytes observed there, so the window may sit on wildcards such as a rel32 operand. The `[FALLBACK]` line reports the verdict. `require_unique` entries never fall back.

A unique byte sequence is not identity proof. Record independent evidence such as a call site, xref, or decompile in `identity`, then inspect the emitted `[RESOLVE]` line for match count, scanned address, fallback, selected source, and agreement. A sigmaker can produce a robust signature for the wrong function.

## Patch registration checklist

Adding a patch normally requires both:

1. A `scripts/patches.json` entry: `patches` for a scanned site or `globals` for a direct address.
2. An entry in the patch list in `include/patches.h`.

If the patch needs a hook target, add its `p.name == "..."` branch in `src/engine/patcher.cpp`. Every `HookEngine::ResolveNamedAddress("Name")` call also needs a matching `resolves` entry.

An entry present only in `patches.json` is never walked and produces no runtime diagnostic. An entry present only in `patches.h` resolves to zero and logs `[STALE-CONFIG]`. `tests/patch_registration_tests.cpp` checks both directions for `patches` and `globals` entries, and every `ResolveNamedAddress` literal anywhere under `src/`; run the test suite after changing either file. A `globals` entry kept deliberately unwalked carries a `"parked"` key giving the reason (the map filter port, the superseded version-notice sites); the test fails if a parked entry is also listed.

## Deploying a test build

Deploy the complete current load chain and configuration with `scripts/Deploy-OpenShim.ps1`; do not hand-copy only `winmm.dll`. At minimum, `scripts/patches.json` must match the DLL because the binary does not embed patch addresses.

The CR suite updater can replace a development build with its bundled files. A development DLL often has the same `version.rc` version as the release, so the downgrade guard cannot distinguish it. After the game exits, redeploy and confirm the deployed artifacts before trusting another run. `verify_windows.ps1 -GamePath <install>` verifies the source `patches.json` and checks the last session for `[STALE-CONFIG]`.

## Targeted validation

Run the lanes touched by the change during iteration; run the complete applicable set before pushing a stable patch milestone.

| Change | Required check |
|---|---|
| New or edited `openshim.ini` key | `./scripts/run_ini_tests.ps1` |
| `src/patches/net_*`, `bzrnet_*`, or `netcode_*` | `./tools/validate-network-baseline.ps1` |
| New/edited test or covered behavior | `cmake -S tests -B build/tests -A Win32`; build Release; `ctest --test-dir build/tests -C Release --output-on-failure` |
| `shaders/dx11_enhanced_fxaa.hlsl` | Compile `VSMain` and `PSMain` with `fxc` as shown in `.github/workflows/build-win32.yml` |

`openshim.ini` ships conservatively. Values that read as enabled fail validation unless their `Section/Key` is in the documented allowlist in `scripts/run_ini_tests.ps1`; default new settings to disabled, or add an explained allowlist entry. Keep `openshim.ini` and `openshim.ini.example` synchronized.

Tests that compare real paths must canonicalize them. CI can expose `TEMP` through an 8.3 path, making `GetTempPathW` and `GetFinalPathNameByHandleW` disagree even when local long paths appear equal.
