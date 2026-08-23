# Generic chunk batch: why it rebuilt three times per frame, and what replaced that

Branch: `agent/generic-chunk-batch-rebuild`
Baseline: `agent/distant-unit-submissions` @ `074d04d5`
Build: Release Win32, VC 14.44.35207
Game: BZR 2.2.301 GOG, `lcbench` benchmark mission

---

## 1. Measured root cause

The generic chunk batch is a single Ogre `ManualObject` built and submitted by
`RebuildAndSubmitGenericChunkBatch()` (`src/patches/bzr_hooks.cpp`). That
function is reached from `SubmitChunkProxiesToRenderQueue()`, which is called
from OpenShim's hook on the game's own world `_updateRenderQueue` override
(`0x00679570`) -- the only exe-side path that feeds Ogre's `RenderQueue`.

The previously reported ~3.02 rebuilds per rendered frame was real, but its
cause had only been inferred. Per-request material-scheme attribution now
measures it directly. On DX11, `dispersed`, 20 tanks:

| Material scheme | Requests/s | Rebuilds/s before | Rebuilds/s after |
|---|---:|---:|---:|
| `high-pssm` | 53 | 53 | 53 |
| `glow` | 53 | 53 | 0 |
| `ShaderGeneratorDefaultScheme` | 53 | 53 | 0 |
| **total** | **159** | **159** | **53** |

159 requests/s at ~53 fps is **3.01 requests per rendered frame**, reproducing
the 3.02-3.03 figure recorded in `live_render_optimization_20260822.md`.

**The multiplicity is one world camera render path visited once per active
material scheme.** It is *not* three PSSM shadow cameras, *not* multiple Ogre
queue traversals, and *not* repeated `prepareForSubmit` calls. Each of the three
schemes drives the world `_updateRenderQueue` override once, and the pre-fix
code tore down and re-emitted the entire vertex set on every one of them.

At ~250 live chunklets that is roughly 4,500 vertices re-transformed and
re-emitted through per-vertex virtual Ogre calls three times per frame, to
produce three byte-identical results.

## 2. Original call architecture

```
Ogre traversal (scheme = high-pssm)
Ogre traversal (scheme = glow)                 -- three per rendered frame
Ogre traversal (scheme = ShaderGeneratorDefaultScheme)
    |
    +-> game world _updateRenderQueue override (0x00679570)
          |
          +-> OpenShim hook
                |
                +-> SubmitChunkProxiesToRenderQueue(renderQueue)
                      |
                      +-> RebuildAndSubmitGenericChunkBatch(renderQueue)
                            scan slots for eligibility          (cheap)
                            begin/beginUpdate                   \
                            per chunk: transform + emit vertices | REDUNDANT
                            end                                 /  x3
                            _updateRenderQueue(manualObject)    (needed x3)
```

Rebuild and submit were fused. Only the final submission actually needs to
happen once per traversal; everything above it depends solely on the slot state.

## 3. Source state that requires a rebuild

The emitted geometry is a pure function of, for each active slot with
`genericBatchTransformReady`:

* `genericBatchKind` -- selects the `kChunk1Vertices` or `kChunk2Vertices` table;
* `genericBatchTransform.{x,y,z}` -- chunk origin;
* `genericBatchTransform.orientation` -- quaternion applied to position, normal
  and tangent;
* `genericBatchTransform.scale`;
* the set and emission order of those slots (index order follows emission
  order);

plus the identity of the `ManualObject`/`SceneManager` and the batch material.

Nothing else feeds it. Camera, viewport, material scheme, frame number and
render queue do **not** change the geometry -- which is exactly why the three
per-frame traversals produced identical output.

## 4. Invalidation model chosen, and why

`include/chunk_batch_invalidation.h` derives a 64-bit FNV-1a **state version**
from precisely the fields listed above, accumulated *inside the eligibility scan
`RebuildAndSubmitGenericChunkBatch()` already performed*. There is no additional
pass over the slots and no hash table. Reuse is granted only when the version
matches and the object, section, identity and material are all intact.

The obvious alternative -- bumping a generation counter at each mutation site --
was rejected on evidence, not taste:

* `UpdateChunkProxySlotPosition()` unconditionally clears `genericBatchKind` and
  `genericBatchTransformReady` at the top of **every** slot update and re-sets
  them further down. A slot that has not moved still performs a
  clear-then-restore every simulation tick, so a mutation-site counter would
  fire for every slot every tick and deduplicate nothing.
* Restructuring those writes into a single commit point means threading a
  commit through several early-return paths. Missing one fails in the worst
  direction: stale geometry drawn as if current.
* A derived version reads the same fields the rebuild reads, so it cannot miss a
  mutation site by construction.

Deliberate properties:

* **Not a once-per-frame gate.** The frame number is not part of the version. If
  chunks legitimately move twice within one frame, the batch rebuilds twice. If
  debris is unchanged across several frames, it rebuilds zero times.
* **Fails toward rebuilding.** `DecideRebuild()` returns a rebuild reason for a
  destroyed object, an unstable identity, a changed material, a missing section,
  a never-built version, or any version mismatch. The opt-out short-circuits to
  `ForcedByCaller`.
* **Float bits, not float values.** Transforms are mixed by exact bit pattern, so
  a one-ULP drift rebuilds. `-0.0f` is normalised to `+0.0f` so it does not force
  a needless rebuild.
* **Order-sensitive.** The slot ordinal is mixed in, so two slots exchanging
  content is not mistaken for no change.

## 5. Implementation

| File | Change |
|---|---|
| `include/chunk_batch_invalidation.h` | New. Version accumulation, reuse policy, reason enum, bounded telemetry. |
| `src/patches/bzr_hooks.cpp` | Version folded into the existing eligibility scan; reuse path; version stamping on successful emit; invalidation on SceneManager change, scene teardown and shutdown; empty-batch hide; telemetry and pass attribution. |
| `tests/chunk_batch_invalidation_tests.cpp` | New. 10 cases. |
| `reverse_engineering/run_chunk_batch_reuse_matrix.ps1` | New. observe/reuse/opt-out matrix runner. |
| `reverse_engineering/analyze_chunk_batch_reuse.py` | New. Derives per-frame rates by pairing batch telemetry with the profiler's fps line over the same interval. |
| `reverse_engineering/capture_chunk_batch_visuals.ps1` | New. Frame capture during *active* destruction. |

Three modes share one binary so comparisons cannot drift on build differences:

| Mode | Gate | Behaviour |
|---|---|---|
| reuse (default) | -- | Re-emit only on a source-state change. |
| opt-out | `OPENSHIM_DISABLE_CHUNK_BATCH_REUSE=1`, or `[Diagnostics] ChunkBatchReuse=0` | Re-emit on every traversal (pre-fix behaviour). |
| observe | `OPENSHIM_CHUNK_BATCH_REUSE_OBSERVE=1`, or `[Diagnostics] ChunkBatchReuseObserve=1` | Take the decision, count it, rebuild anyway. Measures the baseline *and* the dedup opportunity at once. |

Telemetry (`OPENSHIM_CHUNK_BATCH_RATE_DIAGNOSTICS=1`) reports requests, actual
rebuilds, reuses, empty skips, dedup percentage, vertices and indices rebuilt,
rebuild CPU time and per-scheme attribution. Note that in **observe** mode the
per-scheme `rebuilds` column reports the *decision* (what reuse would have done),
while the top-line `rebuilds` counter reports what actually happened -- that is
what makes one observe run yield both the baseline and the opportunity.

Hot-path cost added: a few integer mixes per eligible chunk inside a scan that
already ran, plus a handful of counter increments. The pass-attribution lookup
(two virtual Ogre calls plus a short string walk) is gated behind the
diagnostics flag and does not run in shipping configuration.

### Visibility is written only on a transition

`setVisible` was previously pushed to the batch on every traversal. It is now
recorded and written only when it changes, and the record is reset at all seven
sites that drop the `ManualObject` so a stale record can never describe an
object that no longer exists. Without this the empty path below would call
`setVisible(false)` three times per frame for as long as there is no debris,
which is most of a normal mission.

### Pre-existing hazard found and fixed

Nothing ever hid the batch `ManualObject`. It is attached to a child of the root
scene node with `setVisible(true)` left on, so when the last chunklet expired the
object still held the previous geometry and remained eligible for Ogre's own
traversal. `HideGenericChunkBatchIfBuilt()` now hides it on the
`chunkCount == 0` path, so the frame the last chunk expires is the frame the
batch stops drawing -- independent of reuse. The built version is deliberately
*not* cleared there, so returning debris reuses the same object and section.

## 6. Before/after measurements

All runs `lcbench`, profiler enabled, 1920x1080 windowed, VSync off.
`observe` is the pre-optimization baseline; `opt-out` is
`OPENSHIM_DISABLE_CHUNK_BATCH_REUSE=1`. Per-frame rates are derived by pairing
the batch telemetry with the profiler's fps line over the same one-second
window.

### Rebuilds per rendered frame

| Backend | Scenario | Units | observe | opt-out | reuse |
|---|---|---:|---:|---:|---:|
| DX11 | dispersed | 20 | 3.01 | 3.01 | **1.00** |
| DX11 | firing | 20 | 3.01 | 3.01 | **1.01** |
| DX11 | dispersed | 80 | 3.04 | -- | **1.01** |
| DX11 | firing | 80 | 3.05 | -- | **1.01** |
| DX9 | dispersed | 20 | 3.02 | 3.00 | **1.00** |
| DX9 | firing | 20 | 3.00 | 3.01 | **1.00** |
| DX9 | dispersed | 80 | 3.02 | -- | **1.01** |
| DX9 | firing | 80 | 3.04 | -- | **1.02** |

Requests per frame stayed at 2.99-3.06 in every run, confirming the traversal
count itself is unchanged -- only the emission is deduplicated. The opt-out
reproduces the baseline in all four cases where both were run.

### Rebuild CPU

| Backend | Scenario | Units | observe (ms/s) | reuse (ms/s) | Delta |
|---|---|---:|---:|---:|---:|
| DX11 | dispersed | 20 | 20.53 | 7.26 | -65% |
| DX11 | firing | 20 | 25.28 | 9.54 | -62% |
| DX11 | dispersed | 80 | 30.96 | 10.90 | -65% |
| DX11 | firing | 80 | 22.78 | 8.11 | -64% |
| DX9 | dispersed | 20 | 23.15 | 8.31 | -64% |
| DX9 | firing | 20 | 29.69 | 10.85 | -63% |
| DX9 | dispersed | 80 | 32.20 | 11.58 | -64% |
| DX9 | firing | 80 | 23.71 | 9.03 | -62% |

### Submissions and draw calls per frame

Unchanged, as required -- reuse removes CPU emission work, not submissions.

| Run | observe submit/f | reuse submit/f | observe draw/f | reuse draw/f |
|---|---:|---:|---:|---:|
| DX11 dispersed 20 | 304.2 | 301.7 | 282.7 | 280.8 |
| DX11 firing 80 | 1475.6 | 1478.2 | 991.8 | 988.3 |
| DX9 dispersed 20 | 299.0 | 300.2 | 299.0 | 300.2 |
| DX9 firing 80 | 1464.4 | 1454.8 | 1464.4 | 1454.8 |

Residual differences are chunk-population noise between runs, not a change in
what is drawn.

### Frame time (indicative only)

Frame means moved -1.8% to -2.9% at 20 units and -0.9% to -3.2% at 80. **These
runs all have the profiler attached, which perturbs frame time, so they do not
support a frame-rate claim.** The profiler-disabled PresentMon A/B that would
support one has not been run -- see section 7.

### Worst-case single rebuild

DX9 recorded 1.72-2.15 ms worst-case rebuilds under observe/opt-out versus
0.39-0.43 ms under reuse, consistent with the dynamic buffer lock occasionally
contending with the D3D9 driver. Treat as suggestive only: `maxRebuildMs` is a
running process-wide maximum, so a third as many rebuilds means a third as many
chances to sample a slow one, which explains part of the gap on its own.

### Idle

The `idle` runs produced no batch telemetry at all on either backend. With no
debris the slot vector is empty and `SubmitChunkProxiesToRenderQueue()` returns
before reaching the batch, so the feature is completely inert in scenes without
chunklets and adds nothing to them.

## 7. Visual and runtime validation

### Validated

**Lifecycle: populated -> empty -> populated.** A `combat` run with 6 units
(808 chunklets spawned over 60 s) reached the empty path 190 times, including
both mixed windows (`requests=645 rebuilds=52 emptySkips=449`) and fully drained
ones (`requests=0 rebuilds=0 emptySkips=1092`). A fully drained window submits
nothing at all, confirming the batch stops drawing the frame its last chunklet
expires rather than one frame later. Because visibility is written only on a
transition, that window issues one `setVisible(false)`, not 1092.

**Deduplication is stable across workloads.** `dedupPct` held at 66.6-66.7% in
every dense run -- exactly the 2-of-3 traversals the mechanism predicts -- and
rose to 91.9% in sparse-debris windows where the source state also stops
changing every frame.

**Log hygiene.** Across all 25 runs: zero `OGRE EXCEPTION`, zero batch-update
throws, zero reuse-submit throws, zero hide throws, zero rehydrations, zero
forced failures, zero layout mismatches, zero access violations. The reason
histogram contains only `reused` and `source-changed` after startup -- the cache
never thrashes through `object-recreated` or `section-missing`.

### NOT validated

**Visual A/B during active destruction: not obtained.** Four capture runs
(DX11/DX9 x reuse/opt-out) were attempted and every frame recorded the Windows
lock screen instead of the game. `query session` reported the session as
`Active` throughout, which it does even when locked. The captures were discarded
rather than kept. The game itself continued rendering behind the lock (fps
99-110 in those runs' own logs), so their telemetry is sound, but no visual
claim is made from them.

**Profiler-disabled PresentMon frame-time A/B: not run.** Deferred rather than
attempted, because the locked session measurably changes rendering behaviour --
the same DX11 dispersed-20 workload reported ~99 fps locked versus ~91 fps
unlocked -- so any frame-time result taken in that state would be unsound.

**Scene teardown and mission transition: code inspection only.** The benchmark
harness force-kills the process at the end of every run, so no log in this set
reaches a clean shutdown. The cached version is cleared at every site that
already nulled the `ManualObject` pointer (scene teardown, SceneManager change,
process shutdown, and each failure path), which is the same lifetime the object
itself has -- but that is an argument, not a test.

## 8. Remaining risks

**Hash collision.** Reuse is granted on a 64-bit FNV-1a match. A collision draws
the previous frame's debris positions. FNV-1a is not a cryptographic hash and
the inputs are adversary-free floats, so the practical risk is negligible, but
it is a real failure mode rather than a theoretical one and it degrades silently
rather than loudly. Mitigation if it ever matters: widen to a 128-bit mix, or
compare the raw slot bytes on a match.

**Counters are not atomic.** The telemetry counters are plain `uint64_t`, matching
the file's existing practice for `g_GenericChunkBatchSubmitCalls`. All observed
traffic is on one thread, but nothing enforces that. A second render thread
would corrupt the counters -- not the reuse decision, which reads only
render-thread state.

**Version stamped from a scan taken before the emit.** The source version is
computed at the top of the function and stamped after `end()` succeeds. Nothing
mutates slot state between those points today, because the whole body runs
inside one render-queue callback, but a future change that touched slots
mid-emit would stamp a version that does not describe what was emitted.

**Observer mode reports two different things in one record.** The top-line
`rebuilds` counter is what happened; the per-scheme `rebuilds` column is what
reuse would have decided. That is deliberate and is what lets one run yield both
the baseline and the opportunity, but it is a trap for anyone reading the log
without this note.

**`materialStable` is currently vestigial.** The batch material is a compile-time
constant, so the check can never fail today. It is retained so the policy states
its own requirement rather than depending on a fact that a later change could
quietly invalidate.

## 9. Next optimization target

This optimization is worth roughly 20 ms/s of CPU at 80 units, against frame
times of 48-49 ms. It removes pure waste and should be kept, but it is not what
makes large battles slow.

The same matrix reproduced the large-battle collapse directly. At 80 units
firing:

| Backend | frame mean | p95 | p99 | submissions/f | draws/f |
|---|---:|---:|---:|---:|---:|
| DX11 | 48.2 ms (~21 fps) | 52.5 | 53.6 | 1478 | 988 |
| DX9 | 47.5 ms (~21 fps) | 52.6 | 53.3 | 1455 | 1455 |

Against 20 units at 14 ms and ~445 submissions/frame, quadrupling the unit count
roughly tripled submissions and tripled frame time. **The next target is the
~1,475 submissions per frame, not further chunk work.** The batch rebuild this
PR removed was about 2-3% of wall time at that load; the submission count is the
dominant term and is where the distant-combat profiling work should start.

Note also that DX11 issues 988 draws for 1478 submissions while DX9 issues 1455
for 1455 -- worth understanding before attributing cost to either backend.
