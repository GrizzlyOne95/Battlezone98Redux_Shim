# BZR platform and distribution compatibility

This policy applies to the four repositories that ship together as the BZR
bundle: OpenShim, Extra Utilities (EXU), Campaign Reimagined, and bzfile.

The compatibility baseline was established and tested with help from
**PiercingXX**. Preserving it is a release requirement, not an optional cleanup
task after a feature is complete.

## Supported runtime matrix

| Host | Distribution | Runtime model |
|---|---|---|
| Windows | GOG | Native 32-bit Windows game and BZR binaries |
| Windows | Steam | Native 32-bit Windows game and BZR binaries |
| Linux | Steam | The same Win32 game and BZR binaries under Proton |
| Linux | GOG | The same Win32 game and BZR binaries in a compatible Wine/Proton prefix |

Linux support means running the shipped Win32 components through Proton or a
compatible Wine environment. It does not imply native Linux `.so` builds for
OpenShim, EXU, or bzfile.

## Compatibility rules

- Treat operating system and store as independent dimensions. Code that works
  on Windows/GOG is not automatically proven on Windows/Steam or Linux/Proton.
- Do not hard-code one store's install or content layout into runtime behavior.
  Discover the game root and enabled addon/mod roots through supported runtime
  APIs or explicit configuration. Steam Workshop content is a read-only
  downloaded source, never a development deployment target.
- Keep file and directory names case-correct. Linux filesystems may be
  case-sensitive even though the game and its DLLs use Win32 interfaces.
- Keep shipped native binaries 32-bit Windows PE files unless the architecture
  is deliberately changed across the whole bundle. Proton/Wine must load the
  same artifacts that are released for Windows.
- Avoid new dependencies on Windows-only shell tools, registry state, drive
  letters, or process behavior unless a Proton/Wine-compatible path exists and
  is validated. Host-side install and deployment scripts may be platform
  specific; the resulting game layout and payload contract must remain aligned.
- Preserve store-neutral feature degradation. Optional Workshop or addon assets
  may add capabilities, but their absence must not crash or corrupt a standalone
  GOG, Steam, Proton, or Wine installation.
- Keep updater, manifest, hashing, and replacement behavior equivalent across
  store layouts and compatibility prefixes. Never weaken path or DLL-write
  safety to make one platform easier to support.

## Required change review

Every change must be assessed for effects on:

1. Win32 ABI, loader behavior, injected/proxy DLL behavior, and Lua C modules.
2. Path discovery, separators, case sensitivity, permissions, and writable
   locations.
3. GOG versus Steam executable or content-root behavior.
4. Proton/Wine process, filesystem, environment, and launch-option behavior.
5. Packaging, manifests, installers, update helpers, and Workshop staging.

Documentation-only or clearly platform-neutral changes do not need four runtime
launches. Changes touching any boundary above require the relevant tests and a
runtime smoke check in every affected lane before release. At minimum:

- Build and test the Release x86 Windows artifacts.
- Run the repository's Linux host-side validation where provided.
- Run Lua 5.1 and case-sensitive content checks for Lua/assets/packages.
- Validate GOG deployment separately from Steam staging/download behavior.
- Exercise Proton/Wine when changing loading, paths, module discovery, process
  launch, replacement, install/deploy scripts, or packaged file layout.

If a required lane is unavailable, record it as **unverified** and obtain a test
from a maintainer or tester with that environment before publishing. Do not
silently infer compatibility from a different OS or store.

## Repository responsibilities

- **OpenShim:** keep proxy loading, native hooks, resource discovery, runtime
  paths, and feature gates compatible across the matrix.
- **EXU:** keep the Win32 Lua module, signatures, Ogre integration, and Lua-facing
  behavior compatible under native Windows and Proton/Wine.
- **bzfile:** keep file APIs, allowed roots, hashing, update staging, and deferred
  replacement safe and equivalent across native and compatibility-prefix paths.
- **Campaign Reimagined:** keep Lua/assets case-correct, package store-neutral
  content, validate all bundled binaries, and perform integration/release checks
  across the matrix.

This file is mirrored across all four repositories and should remain
byte-identical. When the policy changes, update every copy in the same
workstream.
