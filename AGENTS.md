# BZR-OpenShim

Native `winmm.dll` shim for Battlezone 98 Redux. This repository owns low-level engine hooks, patch policy, SDK/native integration, trampolines, and reverse engineering. Keep this root file short; read task-specific references only when their trigger applies.

## Repository boundaries

- Sibling BZR repositories normally live under `%USERPROFILE%\Documents\GIT`; verify `origin` and branch before relying on them. Campaign Reimagined's only editable checkout is its Google Drive canonical tree.
- Route reusable Lua/native runtime APIs to **EXU**, campaign content and packaging to **CR**, and Lua file/update primitives to **bzfile**. Read a sibling's `AGENTS.md` before editing it.
- The GOG install at `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux` is the normal test copy. Never use Steam's Workshop cache as a development target.

## Load only when relevant

- Lua behavior or Lua-facing APIs: read `Docs/BZR_LUA_AGENT_REFERENCE.md`.
- Native loading, paths, filesystem/process behavior, discovery, installers, deployment, packaging, or updates: read `Docs/BZR_PLATFORM_COMPATIBILITY.md` and account for the full Windows/GOG, Windows/Steam, Proton, and Wine matrix.
- Patch entries, named resolves, signatures, registration, test deployment, or patch-related CI: read `Docs/AGENT_PATCH_WORKFLOW.md`.
- Binary analysis, Ghidra, debugger, PDB, signature investigation, or native-hook research: read `AGENT_TOOLING.md`. Read `AGENT_TOOLING_SETUP.md` only when installing or repairing that toolchain.
- Private leaked-PDB hints: read `reverse_engineering/private_pdb_semantic_ranking.md`; never treat matching RVAs or leaked-build register/stack locations as released-build proof.
- Any game launch or harness work: dot-source `reverse_engineering/BZRHarness.ps1`, which serializes launches machine-wide, and stop via `Stop-BZRGame` (prefer `-Id`). Never force-kill `battlezone98redux`; doing so with the fullscreen D3D device can hard-lock the workstation. Use `BZR_FORCE_WINDOWED=1` except for timing comparisons.
- The shared Lua and platform documents must remain byte-identical across OpenShim, EXU, CR, and bzfile; update all four in one workstream if either changes.

## Architecture guardrails

- Put build-specific sites and addresses in `scripts/patches.json`; do not scatter raw addresses through feature code. Native hooks must fail closed when identity or build assumptions are not satisfied.
- System DLLs such as `ws2_32.dll` and `gdiplus.dll` remain delay-loaded.
- Preserve ownership and lifetime boundaries. Consult the relevant architecture document for the subsystem rather than loading unrelated historical research.
- For Steam/GOG executable comparisons, allow SteamStub/runtime bytes to settle before declaring a mismatch. GOG remains valid for static reverse engineering unless concrete divergence is found.

## Working and validation style

- Inspect `git status -sb` and the relevant diff before editing. Preserve unrelated work.
- Use one `agent/<short-description>` branch per workstream, normally from current `origin/main`. Do not reuse finished branches or mix unrelated follow-ups.
- Start with the smallest implementation and targeted checks. Expand validation only when the change, a failure, or a release gate requires it. A green build does not replace the task-specific pre-build checks listed in `Docs/AGENT_PATCH_WORKFLOW.md`.
- Stage only task-owned files. Never blanket-stage, clean, restore, or overwrite unrelated changes. Do not rewrite shared history or force-push unless explicitly requested.
- Agents may commit and push coherent task-owned checkpoints. PR merges, releases/tags, Workshop publication, and public deployment require explicit user instruction.
- Do not commit secrets, credentials, transient build/runtime output, crash dumps, or scratch reverse-engineering artifacts.

## Publication routing

- `Docs/STEAM_ROADMAP_BBCODE.txt` is the canonical Roadmap source. Update it when roadmap-relevant OpenShim/EXU/runtime status changes.
- CR owns the complete Workshop publication checklist. A real CR Workshop upload is incomplete until the Roadmap discussion is synchronized; dry runs are exempt.
- Keep validated multiplayer map hop/refresh behavior separate from the disabled clean-room filter/sort port unless that subsystem is explicitly in scope.
