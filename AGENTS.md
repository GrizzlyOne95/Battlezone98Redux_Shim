# BZR-OpenShim

This repo is part of the local Battlezone workspace opened via
`C:\Users\iestu\Documents\GIT\BZR-Workspace\Battlezone98.code-workspace`.

## Workspace Layout
- Campaign Reimagined canonical source: `C:\Users\iestu\Documents\Google Drive\Ian Files\Battlezone Files\Redux Maps\Open Patch - CampaignReimagined`.
- Working game/test copy: `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux`.
- Working Campaign Reimagined runtime: `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\mods\3686673790`.
- Sibling Battlezone Git repos live under `C:\Users\iestu\Documents\GIT`.
- Steam is the final post-upload verification environment, not the development deploy target. Upload the validated mod to Workshop first, let Steam download item `3686673790`, then test the subscribed payload.
- Never deploy development files directly into Steam's Workshop download cache.


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

## Git Checkpoint and Publishing Workflow
- At the start of any task that may modify the repo, inspect `git status -sb` and the relevant diff before editing. Treat pre-existing local changes as user-owned unless they are clearly part of the active task.
- Do not work directly on `main`, `master`, or another protected/default branch for normal feature, fix, RE, or documentation work. Create or use a task branch, normally named `agent/<short-description>`.
- Agents are pre-authorized to create coherent checkpoint commits and push task-owned changes to the current task branch without asking for permission after every checkpoint.
- Create checkpoints at meaningful engineering boundaries: after a coherent implementation slice, an important RE discovery, a known-good build/test state, or before beginning a riskier follow-on change. Do not create a commit for every trivial edit.
- Prefer checkpoints that build or pass the most relevant available validation. If valuable investigative work must be preserved before validation, a clearly labeled `WIP:` commit is acceptable on a task branch; keep unvalidated WIP out of the default branch.
- Push the task branch after meaningful checkpoints and before ending a substantial work session so the remote branch serves as a durable recovery point.
- Stage only task-owned files. On a mixed or pre-dirty worktree, do not use `git add -A`, `git add .`, blanket restore/clean commands, or other operations that can silently absorb or destroy unrelated workstation changes.
- If task changes overlap pre-existing user changes, preserve both where safely possible. Ask for direction only when the overlap cannot be isolated without risking user work.
- Use concise, descriptive commit subjects. For reverse-engineering assumptions, native hooks, offsets, ABI/lifetime findings, or in-game fixes, prefer a commit body that records the important evidence, assumptions, and validation performed.
- Documentation, roadmap, changelog, or release-note updates that are part of the same logical task should normally travel with the implementation checkpoints rather than being left only in the workstation tree.
- Do not amend, rebase, reset, rewrite, delete, or force-push shared history unless explicitly requested. Never use a force push as routine checkpoint behavior.
- Do not merge pull requests, push task work directly to the protected/default branch, create release tags/releases, publish Workshop content, or perform other external release/deployment actions unless the user explicitly requests that action.
- Do not commit secrets, machine-specific credentials, transient build output, runtime deployment copies, crash dumps, scratch RE artifacts, or generated files that the repository does not intentionally track.

## Current Steam Notes
- The multiplayer map-list refresh-position fix is active in OpenShim and has
  been validated against the Steam build.
- The experimental clean-room map filter/sort hook set is intentionally
  disabled for now because the partial port did not reproduce the stock Steam
  filter UI correctly.
- If future work returns to map filters, keep the core hop-fix and manual
  refresh preservation behavior separate from the filter/sort port.

## Steam Roadmap / Forum Post Source
- `Docs/STEAM_ROADMAP_BBCODE.txt` is the canonical source for the public Steam
  Community roadmap/forum post.
- When a roadmap-relevant fix, feature, research status, or completed item changes,
  update this BBCode source alongside the normal patch notes/changelog/release notes.
- Keep engine/runtime work in this roadmap; stock asset/content corrections belong
  in Campaign Reimagined rather than being mixed into the OpenShim/EXU bug list.

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
- Addon-side consumers and Lua integration points live in the Campaign Reimagined canonical source tree above.
- Deploy active test builds to the GOG runtime folder above, preferably through the canonical repo's `Manage-CampaignFiles.ps1`.
- Rendering-adjacent engine reference work may involve `C:\Users\iestu\Documents\GIT\ogre-1.10.0`.
- Discover any additional Battlezone repos beneath `C:\Users\iestu\Documents\GIT`; do not invent or reuse retired paths.

Open `C:\Users\iestu\Documents\GIT\BZR-Workspace\Battlezone98.code-workspace` when a task may span repos.

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