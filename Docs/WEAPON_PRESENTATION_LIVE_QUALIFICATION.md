# Weapon presentation: Windows evidence collection

The implementation and original guide are on `main` through PR #389.
`kNativePresentationLiveQualified` remains false. Neither tool in this document
changes that gate or implements an in-game effect. This is the next evidence
collection step for a Windows agent before the remaining renderer, model and
scene qualification in [the implementation guide](WEAPON_PRESENTATION_IMPLEMENTATION.md).

## Exact target and prerequisites

Use the GOG 2.2.301 executable with SHA-256
`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`.
Steam and other builds are rejected. The process must already be running;
the collector requires its explicit positive PID. It does not select a process
by name, spawn, resume, terminate or change the game installation/configuration.

Use a Python environment containing `pefile`, `capstone`, and `psutil`. The
optional trace also needs the Python `frida` package. Follow `AGENT_TOOLING.md`
and `AGENT_TOOLING_SETUP.md` for the installed toolchain. A system `python`
may differ from the Python environment used by a `bzr-*` wrapper; verify the
imports in the interpreter that runs the command.

For every agent-controlled launch, use `reverse_engineering/BZRHarness.ps1`,
its launch mutex and `BZR_FORCE_WINDOWED=1`; shut down through `Stop-BZRGame -Id`
and release the mutex in `finally`. The collector deliberately leaves process
ownership with that harness. Use the test installation, never a Workshop cache.

Read the private evidence repository's `AGENTS.md` before writing there. All
generated reports contain native instruction bytes and must remain private.
The public repository contains tooling and hand-written guides only.

## Read-only byte capture

After a harness launch, record the process's PID as `$BzrProcessId`. Use a new
report filename for each run. Example from the OpenShim repository root:

```powershell
$EvidenceRoot = Join-Path $env:USERPROFILE 'Documents\GIT\Battlezone_Source\BZ1\Redux\openshim_re_corpus\qualification\weapon_presentation_live'
python .\reverse_engineering\capture_weapon_presentation_live.py `
  --pid $BzrProcessId --settle-seconds 2 `
  --output (Join-Path $EvidenceRoot 'gog-dx11-sites-01.json')
```

The default mode requests only query/read access to the process. It:

1. Verifies the PID's process name, exact executable path, creation timestamp,
   disk SHA-256, PE architecture/base, and live module size.
2. Reproduces the existing static qualification using `scripts/patches.json`.
3. Reads executable sections from that PID, proves fourteen unique signatures
   at the expected addresses, and re-reads their complete guarded windows.
4. Checks three original CALL destinations and five complete detour ranges.
   Already-patched prologues, partial reads, moved or duplicate signatures fail.
5. Repeats the capture after the requested settling interval, checks that the
   same process still exists, and requires identical target records.

Success sets `byte_verification_passed=true`. The report always retains
`activation_qualified=false` and `behavior_qualified=false`. A nonzero exit
records the rejection; matching static bytes alone cannot qualify behavior.
Existing reports are never overwritten. This captures an already-running PID;
it is not proof that the adapter observes every startup class constructor.

## Bounded call observation

Run a separate short capture when investigating actual calls. Attach at the
menu before loading the test mission if constructor/class coverage is needed.
An attachment after mission loading can miss lifetimes: the trace explicitly
uses `observed_generation=null` when its constructor was not seen.

```powershell
python .\reverse_engineering\capture_weapon_presentation_live.py `
  --pid $BzrProcessId --settle-seconds 2 --trace-seconds 10 `
  --max-events 4096 --model-id barrel `
  --output (Join-Path $EvidenceRoot 'gog-dx11-cannon-01.json')
```

Replace `barrel` with the fixture's exact native mesh ID; it is case-sensitive,
printable ASCII, and at most eight bytes. Repeat `--model-id` for up to sixteen
IDs. With no filter, all observed model writes compete for the event budget.
Use short, focused captures or increase `--max-events` up to 20000. A capped
capture is incomplete and returns failure. Missing events never prove absence.

This optional mode injects Frida observers. **It is instrumentation, not a
read-only memory capture or performance benchmark.** It rechecks every full
signature inside the target before attaching any listener. Calls, arguments,
registers, return values and game data are left to stock code. No engine
function is called by the observer, and no renderer is created by it.

| Event | What is recorded |
|---|---|
| `weapon_ctor`, `weapon_ctor_return`, `weapon_dtor` | ECX/native result, constructor arguments and a trace-only generation; never a substitute for the game's owner identity |
| `cannon_factory`, `cannon_factory_return` | Only calls returning to the qualified cannon site; caller `[EBP-190]`, ECX class, stack Matrix/owner, copied entry/return matrices and actual native result |
| `weapon_scope_pop`, `craft_scope_pop` | Live scope ECX and caller-frame class before the original scope pop; unrelated callers are ignored |
| `simulation_begin`, `simulation_end` | Actual float dt, thread, sequence and observed pass number; rendered frames do not supply dt |
| `set_weapon` | Carrier, slot, old pointer before stock replacement and new pointer |
| `model_pose` | Filtered native node ID/parent and copied incoming local pose; the observer never writes the matrix |
| `render_update`, `render_detach` and their returns | Stable slot, native renderer, renderer back-reference, pose/time arguments and slot contents afterward |

The factory observer attaches to the **callee entry**, filters by return
address, and reads the untouched caller EBP. It does not interpret generic
Frida `args` at a mid-function CALL. Its 64-byte matrix decoding uses nine
floats, skips four padding bytes, then reads three doubles. These contracts
are exercised by the synthetic host harness and still need real-game checks.
See the [Frida Interceptor API](https://frida.re/docs/javascript-api/#interceptor)
for entry/return callbacks, register contexts and instrumentation overhead.

Events are batched to a sibling `.events.jsonl` file. Both files are private.
The agent bounds total events, live tracked weapons, thread/kind counters and
queue size. Read faults, event exhaustion, message errors, missed delivery or
premature process/session departure mark the trace incomplete. Installation
failure detaches every listener already installed. Normal completion detaches
the observers and verifies stock target bytes again through ReadProcessMemory.
The report records Frida version and observer source SHA-256.

## Assess the evidence before changing native code

Check chronological `sequence` and `thread_id`; wall time includes observer
overhead. Preserve negative results and incomplete captures rather than
filtering them out. Check the return Matrix against the entry Matrix, native
factory result against accepted fire, and constructor coverage for each weapon.
Inspect invalid slot indices, mismatched back-references and unreadable data.
`complete=true` means the trace finished without known loss; it is not a feature
acceptance verdict and does not imply that every event family occurred.

This observer does **not** trace Ogre queue/scene seams, renderer factory or
destructor overrides/self-expiry, native model generation/reload, SP/MP state,
or visible behavior. The native adapter is still disabled, so a stock-renderer
update is not evidence that the proposed muzzle renderer is correctly owned.
Record these gaps as UNKNOWN. Do not enable the native candidate on the basis
of byte capture or this observer alone.

Continue the five activation checks in the implementation guide. In particular,
qualify renderer creation/expiry/detach and resource ownership; render queue
ordering; rotated, offset barrels and descendants; unchanged projectile aim;
same-owner model reload/address reuse; pause, replacement, save load and nested
teardown; and SP departure/reentry. Add separately qualified seam probes when
those investigations identify the actual native functions. Preserve existing
convergence and SP/MP gates. A Windows agent must record actual PID/build/tool
evidence privately before proposing a gate change.

## Tooling verification

Host tests use synthetic memory and mock Frida sessions; they require no game
or private binary. Run both directly, or through CTest when Python and Node are
available:

```text
python reverse_engineering/test_weapon_presentation_live.py
node reverse_engineering/test_weapon_presentation_probe.js
```

They check signature drift/duplication, racing/partial reads, call/steal guards,
capture bounds, output preservation, bounded errors, delivery and cleanup;
the production observer's argument/frame/matrix reads, unrelated caller
filtering, native null results, registration rollback and event exhaustion.
These checks qualify the tooling's host behavior, not its live integration.

On 2026-10-01, all 60 Linux CTests passed, including the 17 Python cases and
the production JavaScript observer harness. The collector's validation seam
also passed an offline check against the hash-verified private GOG executable
(fourteen sites, three calls and five steals). The unsupported-platform CLI
check records failure with every qualification flag false. No Windows game
PID, successful live capture or feature acceptance is claimed by these results.
