# BZR-OpenShim

This repo is part of the local Battlezone workspace opened via
`%USERPROFILE%\Documents\Battlezone98Redux_Shim.code-workspace`.

## Workspace Layout
- Sibling repos normally live under `%USERPROFILE%\Documents\GIT\...`.
- The primary local game install is typically `%USERPROFILE%\Documents\Battlezone 98 Redux`.
- Some machines also keep a baseline install at `C:\GOG Games\Battlezone 98 Redux`.
- Prefer the workspace file and these conventions over hardcoded profile-specific paths.

## Local Role
- Native shim, patching, and reverse-engineering repo.
- Owns `winmm.dll`, patch trampolines, and native save or loader investigations.

## Current Steam Notes
- The multiplayer map-list refresh-position fix is active in OpenShim and has
  been validated against the Steam build.
- The experimental clean-room map filter/sort hook set is intentionally
  disabled for now because the partial port did not reproduce the stock Steam
  filter UI correctly.
- If future work returns to map filters, keep the core hop-fix and manual
  refresh preservation behavior separate from the filter/sort port.

## Executable Baseline Notes
- For the Battlezone 98 Redux builds checked so far, the Steam executable has
  matched the GOG executable byte-for-byte once the game has launched and the
  runtime bytes have settled.
- For static analysis, reverse-engineering, and best-effort decompilation, it
  is acceptable to use the GOG executable as the baseline reference unless a
  concrete mismatch is observed.
- When validating Steam behavior, account for the post-launch settle delay
  before treating a byte difference as a real build difference.
- If future investigation finds a divergence, prefer documenting the exact
  offset or subsystem mismatch rather than assuming the full executable differs.

## Cross-Repo Pointers
- Addon-side consumers and Lua integration points live in the deployed campaign addon under the workspace game install, usually `%USERPROFILE%\Documents\Battlezone 98 Redux\addon\campaignReimagined`.
- Subtitle integration work may involve `%USERPROFILE%\Documents\GIT\BZR-Subtitles`.
- Rendering-adjacent work may involve the deployed shader addon under the workspace game install, `%USERPROFILE%\Documents\GIT\Battlezone98Redux_EnhancedShaders`, or `%USERPROFILE%\Documents\GIT\ogre-1.10.0`.

Open `%USERPROFILE%\Documents\Battlezone98Redux_Shim.code-workspace` when a task may span repos.

## Agent Tooling
- Read `AGENT_TOOLING.md` at repo start for the current local RE/tooling inventory.
- Read `AGENT_TOOLING_SETUP.md` when reproducing the toolchain on another PC.
- Prefer the stable `bzr-*` wrappers from `C:\Users\istuart\bin` over package-specific install paths.
- The `ghidra` MCP server is expected to come from the persistent localhost service documented in `AGENT_TOOLING.md`, not a fresh per-request Ghidra launch.
