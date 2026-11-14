# Next render-optimization target: evidence-driven triage (2026-08-22)

Baseline: `main` at `c0bcf0ab`. Runtime: GOG 2.2.301, DX11, `lcbench`.
Captured from the repaired contributor profiler on the live-render branch head
`0ad135fd` after the generic chunk batch landed.

This document exists so the next optimization is chosen from measurement rather
than from whichever counter happened to look largest.

## The measurement

Two independent workloads, aggregated from `render_contributors.csv`.

### 80 tanks, continuous firing, batch enabled

| Group | Submissions/f | % sub | CPU ms/f | % ms | D3D draws/f |
|---|---:|---:|---:|---:|---:|
| Vehicle **shadow** (3 PSSM cameras x 3 submeshes) | 731.0 | 47.2% | 1.238 | 27.2% | 638.6 |
| Vehicle **main** (`high-pssm` + `glow`, 3 materials) | 486.8 | 31.4% | 2.192 | **48.1%** | 270.5 |
| DynamicGeometry effects | 268.6 | 17.3% | 0.706 | 15.5% | 122.4 |
| Ordnance main | 47.4 | 3.1% | 0.401 | 8.8% | 25.6 |
| Ordnance shadow | 15.9 | 1.0% | 0.019 | 0.4% | 11.8 |
| **Total** | **1,549.6** | | **4.558** | | |

### 40 tanks, idle, swept by distance

| Distance | Vehicle shadow | Vehicle main | Other | Total sub/f | Total CPU ms/f |
|---:|---|---|---|---:|---:|
| 50 m | 368.9 sub / 0.351 ms | 246.0 sub / 0.670 ms | 58.9 sub / 0.253 ms | 673.8 | 1.274 |
| 250 m | 368.9 sub / 0.318 ms | 246.0 sub / 0.518 ms | 76.0 sub / 0.197 ms | 690.9 | 1.033 |
| 1000 m | 368.9 sub / 0.317 ms | 246.0 sub / 0.447 ms | 48.0 sub / 0.154 ms | 662.9 | 0.918 |

## What the numbers actually say

**1. Distance reduces nothing.** Vehicle submissions are *exactly* constant —
368.9 shadow and 246.0 main at 50 m, 250 m, and 1000 m. Not approximately: the
same numbers. Battlezone stops animation and software skinning past roughly
250 m (animation CPU falls from 1.261 to 0.106 ms/frame) but keeps submitting
LOD-0 geometry and every attachment to every camera. Total frame CPU only
falls because the deformation work stopped, not because anything was culled.

**2. Submission count and CPU time rank differently, and this is the whole
point.** Vehicle shadow traversal has the *most* submissions (47-56%) but only
27-35% of the CPU. Vehicle main-view passes have *fewer* submissions (31-37%)
but 48-53% of the CPU. Per submission that is roughly 4.50 us for a main-view
pass against 1.69 us for a shadow pass — about 2.7x — because the depth-only
shadow pass skips the material, technique, and scheme setup that a main-view
pass performs.

Ranking by the counter alone would pick shadow traversal. Ranking by measured
frame-time contribution picks main-view passes. The ratio is stable across both
workloads and all three distances, so this is not sampling noise.

**3. The GPU is not the constraint.** Profiler-disabled PresentMon measured
GPU-active time essentially unchanged (3.789 ms batched versus 3.606 ms legacy)
while CPU frame time moved by 42%. This is a CPU submission problem.

## Ranked remaining costs

| Rank | Item | Frame-time | Submissions | Gameplay frequency | Headroom | Correctness risk | Mod risk |
|---:|---|---|---|---|---|---|---|
| 1 | Vehicle main-view `high-pssm` + `glow`, LOD 0 | **48-53%** | 31-37% | universal | high | **high** | **high** |
| 2 | Vehicle PSSM shadow-caster traversal | 27-35% | **47-56%** | universal | high | medium | low-medium |
| 3 | DynamicGeometry effect materials | 15-20% | 17% | firing only | low | medium | medium |
| 4 | Ordnance meshes | ~9% | ~4% | firing only | low | medium | medium |
| 5 | DX9 backend/state overhead | DX9 only | none | DX9 users | unknown | high | low |
| 6 | GPU skinning | sub-ms | none | universal | very low | high | high |

Items 1 and 2 are not really separate candidates. They are the same object —
a vehicle submitting LOD-0 geometry that distance never reduces — split by
which camera consumes it.

## Recommendation

**The next target is distant-unit render submissions.** No other contributor
comes close on the combination of measured cost and gameplay frequency, so the
default assumption survives the triage.

But the ordering *within* that target changes, and this is the actionable
finding: attack the boundaries that can be **proven** before the one with the
largest raw number.

**First experiment — glow-scheme participation.** Three vehicle materials
(`avtank00`, `avtank01`, `avheadlight00`) each submit through both `high-pssm`
and `glow`. The three glow rows alone are 243 submissions/f and roughly 1.1 ms
at 80 tanks — comparable to the entire shadow traversal. Whether a material
actually contributes visible glow is a **static, offline-provable property of
the material**, not a per-frame guess. A headlight plausibly emits; a hull
plausibly does not. If a material's glow pass provably writes nothing, skipping
it is invisible by construction. This has the best ratio of measured saving to
correctness risk of anything on the list.

*This is a hypothesis, not a finding.* Nothing yet establishes that any of
those three materials is non-emissive. Establishing it is step one.

**Second experiment — per-cascade distant shadow-caster culling.** Shadow
traversal is the largest submission count and the largest D3D draw count
(638.6/f), and the boundary is bounded and testable: does this caster
contribute any texels to this cascade at this distance? A distant tank's
shadow occupies very few pixels in the far cascade. Shadow participation is a
policy rather than asset geometry, so an opt-out is straightforward and mod
risk is lower than touching vehicle materials.

**Explicitly deferred — reducing main-view LOD-0 geometry itself.** It is the
single largest time cost, but it changes visible silhouettes and materials, and
mods ship their own vehicle meshes. It needs the measurement infrastructure the
first two experiments will build before it is safe to attempt.

## Expected ROI, stated honestly

Do not expect another 40%. The generic chunk batch removed roughly 3.0 ms/frame
at 20 tanks. Total *contributor* CPU at 80 tanks is 4.558 ms, of which shadow
traversal is 1.238 ms and the glow half of main-view passes is roughly 1.1 ms.

Both ceilings are near 1 ms, and only the fraction of units far enough away to
qualify is addressable at all. In `lcbench` every tank sits at 50 m, so the
harness understates the real-gameplay benefit on large maps with distant
formations — and equally, the harness cannot currently demonstrate that
benefit. Building a workload that can is part of the work.

## First tasks

1. Extend `lcbench` with a mixed-distance formation so a distance-gated policy
   has a workload that can actually show a difference.
2. Determine, offline and from the material definitions, whether
   `avtank00`/`avtank01`/`avheadlight00` contribute anything through the `glow`
   scheme. Only then consider gating participation.
3. Instrument per-cascade shadow-caster contribution so a distance/size
   threshold can be justified from texel coverage rather than chosen.
4. Re-measure with the profiler disabled. Profiler-enabled frame times were
   demonstrably load-sensitive during this capture and must not be the basis
   for an optimization decision.
