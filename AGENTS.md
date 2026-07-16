# BZR-OpenShim

This repo is part of the local Battlezone workspace opened via
`<USER_HOME>\Documents\Battlezone98Redux_Shim.code-workspace`.

## Workspace Layout
- Sibling repos normally live under `<USER_HOME>\Documents\GIT\...`.
- The primary local game install is typically `<USER_HOME>\Documents\Battlezone 98 Redux`.
- Some machines also keep a baseline install at `<GAME_ROOT>`.
- Prefer the workspace file and these conventions over hardcoded profile-specific paths.


## Refactored Architecture (2025)
- The project has been decoupled into a generic Hooking Engine and Battlezone-specific Patch Logic.
- ****: Contains the C++ SDK () and internal engine headers.
- ****: The core  handles memory I/O and IDA-style pattern scanning.
- ****: Battlezone-specific trampolines and hooks.
- ****: External configuration for all memory patterns and offsets. This is the primary file to update for game patches.
- **Delay-Loading**: System dependencies like  and  are delay-loaded for robustness.


- The project has been decoupled into a generic Hooking Engine and Battlezone-specific Patch Logic.
- **include/**: Contains the C++ SDK (BZROpenShim.h) and internal engine headers.
- **src/engine/**: The core HookEngine handles memory I/O and IDA-style pattern scanning.
- **src/patches/**: Battlezone-specific trampolines and hooks.
- **scripts/patches.json**: External configuration for all memory patterns and offsets. This is the primary file to update for game patches.
- **Delay-Loading**: System dependencies like ws2_32.dll and gdiplus.dll are delay-loaded for robustness.

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
- Addon-side consumers and Lua integration points live in the deployed campaign addon under the workspace game install, usually `<USER_HOME>\Documents\Battlezone 98 Redux\addon\campaignReimagined`.
- Subtitle integration work may involve `<USER_HOME>\Documents\GIT\BZR-Subtitles`.
- Rendering-adjacent work may involve the deployed shader addon under the workspace game install, `<USER_HOME>\Documents\GIT\Battlezone98Redux_EnhancedShaders`, or `<USER_HOME>\Documents\GIT\ogre-1.10.0`.

Open `<USER_HOME>\Documents\Battlezone98Redux_Shim.code-workspace` when a task may span repos.

## Agent Tooling
- Read `AGENT_TOOLING.md` at repo start for the current local RE/tooling inventory.
- Read `AGENT_TOOLING_SETUP.md` when reproducing the toolchain on another PC.
- Prefer the stable `bzr-*` wrappers from `<USER_HOME>\bin` over package-specific install paths.
- The `ghidra` MCP server is expected to come from the persistent localhost service documented in `AGENT_TOOLING.md`, not a fresh per-request Ghidra launch.

## Default Private-PDB Workflow
- Read `reverse_engineering/private_pdb_semantic_ranking.md` before transferring
  any name or local from the leaked Redux PDB to a released executable.
- Never use leaked-PDB same-RVA equality as identity evidence. The independent
  audit corroborated `0` of `1254` raw same-RVA rows.
- Refresh and validate the semantic queues before a new naming or hook task:
  `python reverse_engineering\rank_private_pdb_matches.py`, then
  `python reverse_engineering\validate_semantic_apply.py`.
- Search the validated data through `build_re_brief.py --supplemental-pdb
  reverse_engineering\workshop\private_pdb_index` before starting a fresh
  disassembly pass.
- `semantic_ranking\binary_validation\safe_new_apply.tsv` is the only queue
  eligible for automatic rename. `high_confidence_review.tsv` is comment/review
  material, and `medium_hold.tsv` must remain unapplied without new evidence.
- Use `reverse_engineering/ghidra_scripts/ApplySemanticPdbHints.java` for Ghidra
  import. It rechecks function-start bytes and refuses unsafe replacement names.
- Private-PDB local/parameter names are semantic hints only. Their stack or
  register locations belong to the leaked build and are not transferable.
- The static validator is pinned to the exact analyzed GOG SHA-256. For Steam,
  validate the corresponding bytes in process only after SteamStub has settled.
