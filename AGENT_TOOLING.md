# OpenShim RE Tool Selection

Read this only for reverse-engineering, binary-analysis, runtime-probing, signature, PDB, or native-hook work. Ordinary docs/API/build tasks do not need it.

Prefer the stable `bzr-*` wrappers on `PATH` instead of package-specific install paths. If a wrapper is missing/broken or the toolchain must be installed on another PC, use `AGENT_TOOLING_SETUP.md`.

## Choose the Smallest Useful Tool
- **Ghidra MCP (`ghidra`) / `bzr-ghidra-mcp.cmd`** — first choice for functions, symbols, xrefs, entry bytes, disassembly, decompiler output, and project-backed static analysis.
- **Redux debugger (`redux_debug`) / `bzr-redux-debug.cmd`** — launch/settle/read/terminate workflows and runtime-byte verification. Use `--backend native` for a persistent live target, then read from the saved PID (or pass `--pid` explicitly). The `cdb` backend is useful for an isolated startup probe, but an unsupplied-PID read intentionally relaunches the game and is not evidence from a previously launched live session.
- **`bzr-cdb32.cmd`** — direct 32-bit WinDbg CLI work when the debugger bridge is insufficient.
- **Frida (`bzr-frida*.cmd`)** — fast live instrumentation, argument/value logging, API tracing, and hook experiments without rebuilding OpenShim.
- **`bzr-ghidriff.cmd`** — build-to-build binary diffing; use when determining whether executable revisions actually changed a subsystem.
- **Rizin (`bzr-rizin.cmd`, `bzr-rz-bin.cmd`, `bzr-rz-asm.cmd`)** — fast shell-side PE/section/import/export/string/disassembly triage.
- **Detect It Easy (`bzr-diec.cmd`)** — compiler/packer/signature triage before heavier analysis.
- **Retoolkit triage (`bzr-capa.cmd`, `bzr-floss.cmd`, `bzr-yara.cmd`, `bzr-entropy.cmd`, `bzr-pe-sieve.cmd`, `bzr-goresym.cmd`, `bzr-redress.cmd`)** — use a bounded, relevant subset for capabilities, recovered strings, rule matches, entropy/packing, or process/in-memory inspection. Keep raw output on disk; summarize only decision-relevant evidence.
- **angr / Qiling (`bzr-angr.cmd`, `bzr-qiling.cmd`)** — symbolic/path exploration or offline/emulated execution when static/dynamic inspection is insufficient.
- **ProcMon (`bzr-procmon.cmd`)** — startup/load-path, file, registry, and DLL activity. Scripted capture/export is agent-friendly; interactive filter tuning may need human help.
- **x32dbg, Cutter, Process Explorer, ReClass.NET, API Monitor** — primarily human-assisted surfaces; use only when they add value beyond the autonomous tools above.

## Useful Repo Surfaces
Before writing one-off tooling, check whether these already cover the task:
- `scripts/ghidra_mcp_bz98.py` — Battlezone Ghidra/MCP wrapper.
- `scripts/redux_debug_bridge.py` — debugger launch/read/probe/terminate + MCP bridge.
- `scripts/qiling_cli.py` — Qiling CLI bridge.
- `reverse_engineering/capture_runtime_layout.ps1` — runtime-layout capture.
- `reverse_engineering/run_best_effort_pipeline.py` — reusable RE pipeline.
- Subsystem-specific `reverse_engineering/run_*_probe.*` scripts — prefer an existing probe when it matches the target.
- `reverse_engineering/tooling_smoke_pipeline.ps1` — bounded offline triage that writes a compact report plus raw artifacts under ignored `reverse_engineering/tooling_smoke/`.

## Practical Workflows

- **Before a new patch/signature:** qualify the PE with static triage, locate semantics with Ghidra, then run a native live launch and capture the target bytes from its PID. Compare expected bytes/build facts before writing a patch.
- **For a one-shot startup/base-image check:** use `bzr-redux-debug.cmd probe --backend cdb ...`. It terminates after the dump; do not describe it as a settled live-runtime capture.
- **For a behavior/argument question:** begin with a small Frida trace or existing subsystem probe; graduate to cdb/x32dbg only when a breakpoint or exception context is necessary.
- **For executable-version drift:** first compare PE identity, then use ghidriff; confirm any candidate correlation with bytes and runtime behavior before reusing it.
- **For loading/filesystem/environment issues:** use ProcMon. Do not use static disassembly to infer a load path when a filtered capture can answer it directly.

## Runtime / Safety Rules
- Static addresses, decompiler output, leaked-PDB hints, and runtime bytes are different evidence classes; corroborate them rather than treating one as authoritative for all builds.
- For leaked/private PDB work, follow `reverse_engineering/private_pdb_semantic_ranking.md`; same-RVA equality alone is not identity evidence.
- For Steam runtime bytes, allow SteamStub/runtime settling before comparing against the GOG/static baseline.
- A native patch must fail closed when the expected build, signature, bytes, or object lifetime cannot be validated.
- Record the command, executable hash/build identity, process PID (for live work), addresses read, and tool/backend in the task evidence. Never promote a one-shot probe, static address, or unvalidated PDB hint to live-runtime proof.
- Prefer existing catalog/pattern infrastructure over scattering raw addresses through feature code.

## Tool Availability
The installed toolchain normally includes Ghidra/pyghidra, the Redux debugger bridge, WinDbg/cdb, Frida, angr, ghidriff, Qiling, Rizin/Cutter, Detect It Easy, Sysinternals, LLVM/MSVC utilities, and `bzr-*` build/archive/triage wrappers. Do not load or enumerate the full installation inventory unless a setup/repair task requires it; `AGENT_TOOLING_SETUP.md` is authoritative for installation and environment overrides.
