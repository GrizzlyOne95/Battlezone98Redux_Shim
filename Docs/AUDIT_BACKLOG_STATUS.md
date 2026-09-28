# CodebaseAudit recovery and stopping point

Updated 2026-09-28. This is the committed, combined OpenShim/EXU handoff. It
supersedes the untracked working tracker in the older primary OpenShim checkout.
The detailed findings remain in [OpenShim's audit](CODE_AUDIT_20260925.md) and
[EXU's audit](https://github.com/GrizzlyOne95/ExtraUtilities/blob/main/Docs/CODE_AUDIT_20260927.md).
Historical "resolved" entries can retain explicitly deferred follow-ups; they
are not a claim that every release qualification lane has run.

## Recovered sessions

Claude's `CodebaseAudit` title belongs to session
`54aebd64-816f-4611-8c7c-c5475b2c81fa`. Its continuing coordinator was
`55a215e5-9a9b-497b-ad3a-0365f1a33af6`, which contains the supplied handoff.
Both transcripts are under:

```text
%USERPROFILE%\.claude\projects\C--Users-iestu-Documents-GIT-BZR-OpenShim\
```

The interrupted workers were `agent-a6ace82d21c220721` (EXU boundary safety)
and `agent-a849c950b822cdff4` (OpenShim split), under the coordinator's
`subagents` directory. Their final tool calls and repository states were
checked directly; the pasted handoff was older than the remote state.

## Workstream status

| Work | Verified stopping point | Next action |
|---|---|---|
| Tuggable thiscall hooks | [OpenShim #278](https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/pull/278) merged on September 26 | No recovery work remains on this feature |
| OpenShim P2-1 split finish | [#374](https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/pull/374) is pushed and merged; head `6da82eaa`, merge `8fe41543`. CI passed, with the existing 64/64 CTest, export, and function-inventory evidence in its PR | Complete; do not reopen the finished branch |
| EXU address catalog / engine save directory | [#71](https://github.com/GrizzlyOne95/ExtraUtilities/pull/71) merged as `839acbd` | Complete |
| EXU P1-15 / P2-2 boundary safety | [#72](https://github.com/GrizzlyOne95/ExtraUtilities/pull/72), head `19be9fc`, is fully committed and pushed. The two interrupted merges are complete, the worktree is clean, and local/static/GOG validation passes | Review final-head CI, then obtain the owner's merge instruction for this session |
| Map Filters+ search / dropdown completion | [OpenShim #365](https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/pull/365) remains open; head `3d8ac727` already incorporates current main | Owner's Create Game screen test and merge decision; checklist is in the PR |
| Repository history cleanup | PDB/corpus untracking and private archival are merged (#281, #373; private corpus PRs #5/#6). The history rewrite was only dry-run | Follow [the preserved history plan](AUDIT_HISTORY_REWRITE_HANDOFF.md); force-push/protection changes remain unapproved |

The September 27 coordinator's automatic-merge permission explicitly said to
confirm again in a new session. This recovery therefore finishes and pushes
the reviewable work without merging #72 or #365, rewriting history, tagging,
releasing, or publishing Workshop content.

## EXU recovery evidence

The worktree initially had `ef72685` committed locally and nine unstaged merge
resolutions. Those resolutions preserved both #70's shared helpers and #71's
catalog/save-directory changes. The completed merge is `e78a04a`; `19be9fc`
adds durable validation and the targeted runtime fixture.

- Fresh Release x86 rebuild: no warnings or errors; HardeningSmoke passes.
- All 13 MSVC host suites and 12 qualification-tool tests pass; generated
  headers and hardening checks pass. Eight DLL exports and 397 Lua names
  match a separate main build.
- GOG/DX11, main versus candidate: 113 successful broad calls and the same
  expected argument error; 8/8 targeted boundary checks; all three real save
  paths succeed. The log changes only from a swallowed Ogre C++ exception to
  the intended caught-exception diagnostic, apart from volatile output.
- Completed comparison runs: no new crash dumps, renderer errors, or Lua
  Update errors. An initial baseline-only attempt exposed a wrong test return
  type assumption and a visible font-overlay shader failure; the corrected
  comparison keeps that test overlay hidden. Visual font acceptance was not
  claimed.
- EXU, the test mission script, both save destinations, and configuration were
  restored. The original slot-10 save hash matched its backup; the installed
  OpenShim load chain and `patches.json` did not change.

Full commands, artifact hashes, platform limits, and the targeted fixture are
recorded in [EXU's validation note](https://github.com/GrizzlyOne95/ExtraUtilities/blob/agent/p1-15-p2-2-lua-boundary-safety/Docs/LUA_BOUNDARY_VALIDATION_20260928.md).
Windows/Steam and Proton/Wine runtime validation remain release gates; Linux
host CI is not a substitute for those lanes.

## Deliberate follow-ups

- #365 still needs the actual Create Game screen pass. Preserve the working
  stock-filter extension and map hop/refresh behavior. The deleted clean-room
  filter/sort port stays deleted.
- EXU's native naked-thunk callbacks still need C++ barriers (H-12), and
  allocation-only Lua failures with live C++ objects remain outside #72.
- EXU `LuaHelpers::PushMatrix` and ContinuityApi `PushNativeMatrix` disagree
  about right/up vector order. The coordinator created a separate task titled
  "Fix EXU matrix up/right vector order mismatch"; no dedicated PR was found
  during this recovery. It still needs runtime proof before a fix.
- OpenShim P0-7's non-chunk Ogre SEH follow-up remains documented in the audit;
  the EXU change does not implement that separate OpenShim work.
- OpenShim P0-8's package authenticity/signing decision remains open; manifest
  self-consistency and helper attestation are already implemented.
- The EXU P2-8 follow-up on OpenShim unavailable sentinels, especially the
  nickname API under mixed-version load-chain files, remains separate.
- Low-value remaining helper duplication, retained diagnostic tools, visual /
  multiplayer acceptance cases, and the first real tag publication of the
  shared release action retain the limits recorded in the detailed audits.
- bzfile consolidation was explicitly deferred. Runtime chunk splitting was
  assessed but not started. Neither is part of this recovery.

Other open work at recovery time is separately owned: OpenShim #165 (fog),
#290 (DX11 fixed-function compatibility), #367 (turbo sound); EXU #73-#76
(first-person/animation APIs). No edits were made to those branches.

## Local repository state

Normal root: `%USERPROFILE%\Documents\GIT`. Origins were verified before use.

| Checkout | State preserved / produced |
|---|---|
| `BZR-OpenShim` | `agent/tuggable-thiscall-hook`, local `45ca0b65`, 87 commits behind its remote; no tracked edits. Untracked nested worktree, `pluto-test.png`, and historical tracker are retained. Do not update this older checkout casually: moving past #373 removes its tracked local corpus until the restore script is run |
| `BZR-OpenShim-splitend` | Clean and fully pushed at `6da82eaa`; finished branch |
| `BZR-OpenShim-audit-handoff` | `agent/codebase-audit-handoff`; this committed tracker, history-plan preservation, and Roadmap status |
| `ExtraUtilities` | `agent/release-1-3-0-prep`; only its pre-existing untracked `.claude/` directory |
| `ExtraUtilities-luasafety` | Clean, pushed `agent/p1-15-p2-2-lua-boundary-safety`, `19be9fc` |
| `ExtraUtilities-audit-baseline` | Detached `839acbd`; temporary baseline build used only for comparison |
| `Campaign-Reimagined` | Clean `agent/bzfile-hardening-followup`; no edits |
| `bzfile` | Clean `main`, locally two commits behind the last fetched `origin/main`; no edits |
| `Battlezone_Source` | Clean `research/bzcc-decompile-name-transfer-bzr-map`; no edits |

Older unrelated local-only OpenShim commits were inventoried, not silently
published: `1c2a0774` (`agent/bzn-load-failure-context`, September 24),
`8a1f601c` / `d7ab3821` (`agent/normal-save-state` /
`agent/save-state-followups`, September 21), `445446cf`
(`agent/save-load-format-reference`), and `e9e0a072`
(`agent/agent-workflow-doc-fixes`). They are not reachable from any fetched
remote branch and are not patch-equivalent to main. Local integration-only
merge commits also remain in `BZR-OpenShim-int` and EXU's validation worktree.

Unrelated tracked changes remain in `BZR-OpenShim-dx11test` (four renderer/test
files), `BZR-OpenShim-ff2unit` (renderer source and its design note), and
`ExtraUtilities-validation` (`lib/Lua5.1-BZR.lib`). Existing stashes were
preserved: three in OpenShim, one in CR. These are not evidence of unfinished
CodebaseAudit recovery work and must not be blanket-staged or cleaned.

## Local evidence locations

- Recovery build/runtime logs and pre-test backups:
  `%TEMP%\codex-codebase-audit-20260928`.
- Original coordinator scratch material:
  `%TEMP%\claude\C--Users-iestu-Documents-GIT-BZR-OpenShim\55a215e5-9a9b-497b-ad3a-0365f1a33af6\scratchpad`.
- Preserved original tracker, original history draft, and removal-path list:
  `%USERPROFILE%\Documents\GIT\.research-archive\CodebaseAudit-20260928`.

Do not commit crash dumps, save backups, DLLs, the private corpus, or old-history
bundles. The committed notes carry the conclusions needed to resume without
depending on temporary logs.
