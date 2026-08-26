# BZR-OpenShim

Native `winmm.dll` shim for Battlezone 98 Redux. This repo owns low-level engine hooks/patches, SDK/native integration, patch trampolines, and reverse-engineering work.

## Local Environment
- Sibling Battlezone repos normally live under `%USERPROFILE%\Documents\GIT`. Prefer a local sibling checkout for reference when present; verify its `origin` before editing because historical folder names may differ from GitHub names.
- Working game/test copy is the GOG install at `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux`.
- Campaign content/deployment rules belong to Campaign Reimagined's `AGENTS.md`. Never use Steam's Workshop download cache as a development deploy target.

## BZR Bundle
Core sibling repos:
- **OpenShim** — `GrizzlyOne95/Battlezone98Redux_Shim` (this repo): low-level hooks, patches, RE, SDK/native engine integration.
- **EXU / ExtraUtilities** — `GrizzlyOne95/ExtraUtilities`: reusable native/Lua-facing runtime features. **EXU always means this repository.**
- **Campaign Reimagined / CR** — `GrizzlyOne95/Battlezone98Redux_CampaignReimagined`: addon content, Lua consumers, assets, packaging, and end-user integration/validation.
- **bzfile** — `GrizzlyOne95/bzfile`: Lua-accessible file I/O and update/deployment support.

Cross-repo reading is encouraged to avoid duplicate APIs or repeated RE. Do not edit another repo merely because it was consulted; read that repo's `AGENTS.md` before coordinated changes.

## Shared BZR Lua Reference
Before writing, reviewing, or changing BZR Lua behavior—or adding Lua-facing native APIs—read `Docs/BZR_LUA_AGENT_REFERENCE.md`. This document is mirrored across the four core BZR repos and should remain byte-identical. Repo-specific `AGENTS.md`/architecture docs still govern implementation ownership. When the shared reference changes, mirror the same content to OpenShim, EXU, Campaign Reimagined, and bzfile in the same workstream.

Reference/tooling repos commonly available under `%USERPROFILE%\Documents\GIT` (reference, not default edit targets): `BZ98RBlenderToolKit`, `Battlezone98Redux_DedicatedServer`, `BZ1-GameWatcher`, `BZ1_Source`, `BZ2_Source`, `Battlezone_LobbyMonitor`, `BZNTools`, `Battlezone98Redux_AudioTool`, `Battlezone98Redux_WorldBuilder`, `Battlezone98Redux_ZFSSpecialist`. Rendering work may also consult local `ogre-1.10.0`.

## Architecture
- `include/`: public SDK and internal engine headers.
- `src/engine/`: generic hook engine, memory I/O, pattern scanning.
- `src/patches/`: Battlezone-specific hooks/trampolines.
- `scripts/patches.json`: external patterns/offsets; prefer it over hardcoding patch addresses in feature code.
  - `"patches"` / `"globals"`: sites the shim **overwrites**.
  - `"resolves"`: addresses the shim only **calls or reads**, resolved via
    `HookEngine::ResolveNamedAddress("Name")`. Use this instead of adding a new
    `uint8_t` pattern/mask array pair to feature code. Fields: `pattern`
    (IDA-style, `??` wildcards), `offset` (signed, match to anchor), `mode`
    (`address` | `rel32_target`), `fallback` (known-good constant), `prefer`
    (`scan` | `fallback`, default `scan`), `require_unique`, and a mandatory
    `identity` note. Parsing lives in `src/engine/resolve_table.cpp` and is
    covered by `tests/resolve_table_tests.cpp`, which checks the shipped file.
- Signature discipline: a unique byte string is not proof of identity — it can
  belong to a function you did not mean, and an anchor that misses by a couple
  of bytes resolves to a plausible neighbour. Every `resolves` entry therefore
  carries an `identity` note recording independent evidence (call site, xref,
  decompile), and every resolution emits one `[RESOLVE]` log line with the
  match count, scanned address, fallback, which source won, and whether the two
  agree. Read that line before trusting a new signature; a signature generated
  by a sigmaker such as Sigga is robust, not correct.
- System DLLs such as `ws2_32.dll` and `gdiplus.dll` are delay-loaded for robustness.

## Git Workflow
- Before editing, inspect `git status -sb` and the relevant diff; preserve pre-existing user changes.
- Normal work goes on a task branch, usually `agent/<short-description>`, never directly on the default/protected branch.
- Agents may commit and push coherent task-owned checkpoints without repeatedly asking. Prefer validated milestones; a clearly labeled `WIP:` checkpoint is acceptable when preserving valuable intermediate work.
- Stage only task-owned files. Never blanket-stage, clean, restore, or otherwise absorb/destroy unrelated changes in a mixed worktree.
- Do not rewrite shared history or force-push unless explicitly requested.
- PR merges, releases/tags, Workshop publication, and other external release/deployment actions require explicit user instruction.
- Do not commit secrets, machine credentials, transient build/runtime output, crash dumps, or scratch RE artifacts the repo does not intentionally track.

## Running the Game Harness
- **Never `Stop-Process -Force` on `battlezone98redux`.** Force-killing it while it owns an exclusive-fullscreen D3D device deadlocks the kernel display stack and hard-locks the workstation with no BSOD, no dump, and no WHEA entry. This happened three times between 2026-08-22 and 2026-08-24.
- Any script that launches the game must dot-source `reverse_engineering/BZRHarness.ps1` and shut down via `Stop-BZRGame` (prefer `-Id` over name matching). Dot-sourcing also serializes launches machine-wide, so concurrent agents cannot collide mid-mode-set.
- Set `$env:BZR_FORCE_WINDOWED = '1'` for stability or correctness runs; it removes the fullscreen mode-set entirely. Leave it unset for anything that reports timing — windowed and fullscreen FPS are not comparable.
- If the machine hard-locks again, the absence of a crash dump is itself the finding. Capture what the harness was doing rather than power-cycling and retrying.
- Full write-up: `docs/HARNESS_SAFETY.md`.

## Task-Specific Guidance
- **RE, binary analysis, Ghidra, debugger, PDB, signatures, or native-hook investigation:** read `AGENT_TOOLING.md` before that work. It is not required for ordinary docs/API/build tasks. Prefer stable `bzr-*` wrappers from `<USER_HOME>\bin`; the persistent Ghidra MCP model is documented there.
- **Installing/repairing/reproducing the RE toolchain:** read `AGENT_TOOLING_SETUP.md` only for that task.
- **Private leaked-PDB hints:** first read `reverse_engineering/private_pdb_semantic_ranking.md` and follow its validation policy. Never treat same-RVA equality as identity evidence; never transfer leaked-build stack/register locations as released-build facts.
- **Steam/GOG executable comparison:** checked builds have matched after SteamStub/runtime bytes settle; GOG is acceptable for static RE unless a concrete mismatch is found. Account for settle delay before declaring Steam divergence.
- **Roadmap / Workshop publication:** `Docs/STEAM_ROADMAP_BBCODE.txt` is the canonical source for the Steam Roadmap discussion at `https://steamcommunity.com/workshop/filedetails/discussion/3686673790/216888303627073611/`. Update it alongside normal release/changelog notes whenever roadmap-relevant OpenShim/EXU/runtime work changes status. For **every real Campaign Reimagined Workshop upload**, review/update this file and then synchronize the complete BBCode into the Steam discussion before the publication is considered complete. Dry-run publishes do not require a public Steam edit. Campaign Reimagined owns the full checklist in `docs/STEAM_PUBLISH_CHECKLIST.md`.
- **Multiplayer map filtering/sorting:** keep the validated hop/refresh preservation behavior separate from the currently disabled clean-room filter/sort port unless that subsystem is explicitly being revisited.
