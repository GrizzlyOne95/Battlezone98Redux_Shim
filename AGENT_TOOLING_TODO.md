# OpenShim Agent RE Tooling Roadmap

This file is the implementation backlog for agent-facing reverse-engineering tooling. It is **not** a startup checklist. For normal RE work, use `AGENT_TOOLING.md`; for installation/repair, use `AGENT_TOOLING_SETUP.md`.

The goal is to turn recurring OpenShim reverse-engineering work into deterministic, scriptable workflows rather than continuing to add standalone tools without integration.

## Current State

Already integrated through `scripts/install_agent_re_tooling.ps1` and/or the stable `bzr-*` command surface:

- Ghidra MCP and the persistent local Ghidra service
- Redux debugger bridge and WinDbg/cdb runtime-byte capture
- Frida / `frida-trace`
- x32dbg
- angr
- ghidriff
- Qiling
- Rizin / Cutter
- Detect It Easy
- Process Monitor / Process Explorer
- Retoolkit, including wrappers for CAPA, FLOSS, YARA, UPX, PE-sieve, entropy, GoReSym, and Redress where available
- MSVC/LLVM, CMake, Ninja, and archive/build wrappers

Do not re-add these as TODO items unless a concrete missing workflow or reliability problem is identified.

## Verified Baseline — 2026-08-20

This host has the configured GOG executable, Ghidra MCP wrapper/service launcher, Redux debugger bridge, x86 cdb, Frida process listing, ghidriff, Qiling, Rizin, DIE, Retoolkit (CAPA, FLOSS, YARA, entropy, PE-sieve, GoReSym, and Redress wrappers), CMake, Ninja, and MSVC wrappers on `PATH`. `bzr-redux-debug.cmd doctor` resolved the expected GOG install and debugger paths. The local Ghidra MCP endpoint was listening; a bare HTTP GET returned its expected protocol-level `406 Not Acceptable` response.

The live validation used:

```powershell
bzr-redux-debug.cmd launch --backend native --wait-seconds 15
bzr-redux-debug.cmd read 0x00400000 --length 64
bzr-redux-debug.cmd read 0x00577290 --length 16
bzr-redux-debug.cmd terminate
```

It read the active process (rather than a relaunch): the image base began with the expected `MZ` header and the active `0x00577290` site began `E9 9B 9D 77 6E`, consistent with the installed career-hook trampoline. Frida also enumerated `battlezone98redux.exe` during the session. The process was terminated after verification.

The ignored offline smoke pipeline also completed successfully for DIE, Rizin information/imports/sections, `dumpbin` headers/imports, and entropy against the same executable. CAPA, FLOSS, and YARA returned their installed version surfaces; a future feature-specific task should run the potentially longer CAPA/FLOSS analyses instead of assuming their output is useful for every binary.

### Confirmed Reliability Gap — Redux cdb sessions

**Status:** Must be corrected or constrained before claiming persistent cdb live capture.

During the same scan, `launch --backend cdb` reached game/shim initialization but encountered a first-chance access violation in `WINMM!wod32Message`; its target/controller were no longer alive after the wait. Further, `read` without `--pid` on a saved cdb/windbg state uses the bridge's deliberate `cdb_relaunch` fallback. That supplies a reproducible startup/base-image probe, not bytes from the earlier running game.

Until the bridge changes, agents must use `--backend native` plus saved/explicit PID for persistent live memory reads. Treat the cdb path as one-shot and preserve its raw debugger output when it is used. Follow-up implementation/validation should determine whether cdb can remain attached through expected first-chance exceptions and should make stale-session detection explicit.

## Priority 0 — Make Runtime Capture Semantics Explicit and Reliable

**Status:** Documentation constrained; bridge hardening pending.

### Goal

Make the debugger bridge distinguish a one-shot cdb startup probe from a persistent live session, reject stale saved state, and provide an evidence-preserving capture path for hook bytes.

### Required work

1. Add an `alive`/stale-state indication to `status`; clear or reject a state whose target is gone.
2. Make `read` report a relaunch only when the caller explicitly opts into a one-shot probe, rather than silently treating it like a session read.
3. Add a named `probe`/`capture` mode with returned process lifetime, debugger return code, and a short raw-output artifact path.
4. Investigate the cdb first-chance `WINMM!wod32Message` stop: classify it as expected/handled versus a debugger-launch regression before using cdb for settled capture.
5. Add automated tests for native saved-PID reads, stale state, explicit cdb one-shot reads, and termination cleanup.

### Acceptance criteria

- A command cannot label relaunch bytes as an active-session read.
- Stale saved state is visible and does not cause an implicit semantic switch.
- Native capture records PID and reads the same process after settling.
- cdb behavior is either proven persistent through relevant first-chance exceptions or is exposed solely as a one-shot probe.

## Priority 1 — Automated Patch Signature Pipeline

**Status:** Next implementation target.

### Goal

Replace manual prologue copying and ad-hoc wildcard placement with a repo-owned pipeline that can generate, test, and explain OpenShim scan patterns.

### Dependencies

- Add `iced-x86` to the Python packages installed by `scripts/install_agent_re_tooling.ps1`.
- Keep the implementation x86-aware; Redux is a 32-bit target.

### Planned command surface

Add:

- `scripts/generate_patch_signature.py`
- `bzr-signature.cmd`

Initial command forms should support:

```powershell
bzr-signature --address 0x004EAD78
bzr-signature --address 0x004EAD78 --instructions 8
bzr-signature --address 0x004EAD78 --json
bzr-signature --validate-patches scripts\patches.json
```

Allow an explicit `--binary` override; otherwise use the normal BZR executable resolution/environment conventions.

### Generation algorithm

1. Resolve the executable and map the requested VA/RVA to file bytes.
2. Decode whole x86 instructions with iced-x86; never cut a signature in the middle of an instruction.
3. Mark relocation-sensitive operand bytes as wildcards where appropriate, especially relative call/jump displacements and image-address-dependent operands.
4. Preserve stable opcode/modrm/sib and genuinely structural constant bytes rather than wildcarding every immediate indiscriminately.
5. Grow the signature by whole instructions until it is unique in the intended executable section, normally `.text`.
6. Report the signature start address and the offset from that start to the requested patch address.
7. Capture the expected original bytes at the patch site.
8. Emit both human-readable output and a machine-readable JSON representation suitable for `scripts/patches.json` review.
9. Fail closed if decoding fails, address mapping is invalid, the pattern has zero matches, remains ambiguous, or the requested patch span crosses an invalid boundary.

The initial generator should be **advisory**: it proposes a pattern and evidence but does not edit `patches.json` or source automatically. A generated signature becomes patch-ready only after the existing OpenShim byte/build checks and, where relevant, runtime validation confirm the target semantics.

### Validation mode

`--validate-patches scripts\patches.json` should audit existing pattern-backed entries and report at minimum:

- match count
- resolved address
- configured offset
- expected-size coverage
- expected/fallback consistency where applicable
- ambiguous or zero-match patterns

It must not silently rewrite `patches.json`. Automatic rewriting can be considered only after the validator is proven reliable.

### Acceptance criteria

- Deterministic output for the same binary/address/options.
- Generated patterns consist only of whole decoded instructions.
- Known existing OpenShim pattern entries can be reproduced or validated against the current reference executable.
- A successful generated pattern resolves exactly once in its intended section.
- Failure cases are explicit and non-destructive.
- Unit tests cover instruction-relative branches/calls, absolute/image-relative operands, stable immediates, ambiguous patterns, and invalid addresses.
- `AGENT_TOOLING.md` documents `bzr-signature` only after the workflow passes these checks.

## Priority 2 — PE Identity and Qualification Tooling

**Status:** Planned after signature generation.

### Goal

Provide one compact command for the PE/build facts agents repeatedly need before static analysis, PDB comparison, or patch qualification.

### Dependencies

- Add `lief` to the installer.
- Use LIEF read-only initially even though it supports PE mutation. Production tooling should not rewrite the game executable.

### Planned command surface

Add:

- `scripts/pe_info.py`
- `bzr-pe-info.cmd`

Suggested forms:

```powershell
bzr-pe-info battlezone98redux.exe
bzr-pe-info battlezone98redux.exe --json
bzr-pe-info old.exe --compare new.exe
```

### Report fields

At minimum:

- SHA-256
- architecture/machine
- image base
- entry point
- PE timestamp
- section RVA/size/characteristics
- import/export summary
- debug-directory / CodeView information
- PDB path/name when present
- PDB GUID and age when present

`--compare` should emphasize identity/qualification differences rather than dump every PE field.

### Acceptance criteria

- Results agree with independent `dumpbin`, `llvm-*`, or existing static evidence for representative BZR binaries.
- JSON output is stable enough to be consumed by later scripts.
- Missing debug/PDB data is reported as absent, not treated as an error.
- No executable mutation path is exposed by the normal wrapper.

## Priority 3 — Queryable PDB / Symbol Index

**Status:** Planned; validate library compatibility before committing to a parser.

### Goal

Stop repeatedly producing enormous raw symbol dumps. Build a compact queryable index for public symbols, types, and PDB identity information while preserving the existing private-PDB evidence rules.

### Candidate backends

1. `llvm-pdbutil` — already available through LLVM and should remain the dependable fallback/reference implementation.
2. `pdbparse` — add only if it works reliably with the supported local Python environment and the PDB variants in the corpus.
3. `cvdump` — evaluate later only if it exposes information not practically available through the first two.

### Planned command surface

Prefer a repo script/wrapper such as:

```powershell
bzr-pdb-info redux.pdb
bzr-pdb-find redux.pdb "Person::Simulate"
bzr-pdb-types redux.pdb "Person"
bzr-pdb-index redux.pdb --output reverse_engineering\workshop\pdb_index
```

The persisted index may use SQLite plus compact JSON metadata if that improves query speed and provenance tracking.

### Safety / evidence rules

- PDB names/types are semantic evidence, not proof of released-build address identity.
- Never auto-transfer a symbol because an RVA happens to match.
- Never transfer leaked-build stack/register locations as released-build facts.
- Preserve source PDB identity, GUID/age, tool/backend, source hash, and extraction time in index metadata.
- Private/leaked-PDB application remains governed by `reverse_engineering/private_pdb_semantic_ranking.md`.

### Acceptance criteria

- Fast exact/substring symbol lookup without loading a full PDB dump into agent context.
- Reproducible index metadata tied to the source PDB hash/identity.
- Cross-check a representative sample against `llvm-pdbutil` output.
- No automatic Ghidra renaming from unvalidated/private symbols.

## Priority 4 — Standard Cross-Build Function Correlation

**Status:** Planned after the signature/identity layers are stable.

### Goal

Turn existing ghidriff/Ghidra capability into a repeatable build-to-build correlation workflow with compact machine-readable output.

### First backend

Use the tooling already installed:

- Ghidra project/corpus
- ghidriff
- existing source/PDB semantic evidence

Add a stable command such as:

```powershell
bzr-diff-builds old.exe new.exe --output reverse_engineering\workshop\diffs\old_to_new
```

Expected outputs:

- `function_matches.json`
- `function_matches.csv`
- `diff_report.md`
- provenance/command metadata

Each match should preserve the backend score/evidence instead of collapsing fuzzy correlation into a boolean identity claim.

### BinDiff evaluation gate

Evaluate Google BinDiff **after** the ghidriff baseline exists. Add it to the supported toolchain only if a representative unresolved-function set shows materially better correlation or useful independent corroboration.

If adopted, prefer parsing/exporting its results into the same normalized correlation schema rather than creating a separate agent workflow.

### Diaphora evaluation gate

Do not install by default. Evaluate only if unresolved cases remain after Ghidra/ghidriff and, if adopted, BinDiff. Keep it only if it contributes unique useful matches or independent evidence.

### Acceptance criteria

- One command produces repeatable correlation artifacts.
- Output records source/target binary hashes and analysis backend/version.
- Exact, high-confidence fuzzy, low-confidence, and unmatched functions remain distinguishable.
- No fuzzy match is automatically promoted to a patch target without byte/runtime validation.

## Priority 5 — Compact Automated RE Triage

**Status:** Nice-to-have after core patch workflows.

Retoolkit/CAPA/FLOSS/Rizin/Detect It Easy are already installed. The remaining opportunity is orchestration, not more installation.

Consider a command such as:

```powershell
bzr-re-triage battlezone98redux.exe --output reverse_engineering\workshop\triage
```

It could run a bounded subset of existing tools and produce one compact report containing:

- PE identity
- compiler/packer/signature classification
- imports/exports/sections
- CAPA capability summary
- FLOSS notable decoded strings
- selected Rizin metadata
- tool versions and hashes

Do not dump every tool's full output into normal agent context; retain raw artifacts on disk and make the summary point to them.

## Evaluate Later / Human-Assisted Tools

### x32dbg SigMaker / PatternFinder

Useful as a human cross-check, but **not** the primary signature workflow. A repo-owned iced-x86 generator is preferable because it is deterministic, testable, and agent-accessible. Install/document SigMaker only if interactive validation remains useful after Priority 1.

### cvdump

Low priority while `llvm-pdbutil` covers the needed records. Add only for a demonstrated PDB record/layout gap.

### Additional binary-diff engines

Do not accumulate diff engines for completeness. Any new backend must demonstrate additional useful coverage on the BZR corpus and feed the normalized correlation output.

## Implementation Order

1. Add iced-x86 and implement `bzr-signature` generation.
2. Add signature uniqueness/audit mode for `scripts/patches.json`.
3. Add LIEF and implement `bzr-pe-info`.
4. Build the compact PDB query/index workflow, using `llvm-pdbutil` as the validation baseline and `pdbparse` only if reliable.
5. Standardize ghidriff cross-build correlation and artifact output.
6. Evaluate BinDiff against unresolved cases; adopt only if it materially improves coverage.
7. Add compact Retoolkit/CAPA/FLOSS/Rizin orchestration if repeated manual triage justifies it.
8. Evaluate SigMaker, Diaphora, cvdump, or other adjuncts only against concrete remaining gaps.

## Roadmap Maintenance

When a phase is implemented:

- change its status to **Implemented**;
- link the actual script/wrapper/tests instead of retaining speculative installation prose;
- update `scripts/install_agent_re_tooling.ps1` and `AGENT_TOOLING_SETUP.md` if dependencies changed;
- add only the concise task-selection guidance needed in `AGENT_TOOLING.md`;
- record validation and known limitations;
- remove superseded recommendations rather than keeping historical shopping-list text.

The desired end state is a small set of dependable commands that answer recurring OpenShim RE questions with provenance and fail-closed validation—not the largest possible collection of reverse-engineering software.
