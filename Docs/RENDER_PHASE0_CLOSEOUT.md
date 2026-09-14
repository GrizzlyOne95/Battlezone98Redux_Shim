# Renderer roadmap, Phase 0: closeout

Phase 0 is "finish and stabilize today's renderer" before any new rendering
work starts: close out the terrain/lighting changes, finish the ownership
migration, and establish a repeatable visual benchmark.

This records what is finished, what is deliberately left to a human, and what
Phase 0 turned up that was not in the plan.

---

## 1. What was wrong, and is now fixed

### The canonical payload was a snapshot (the significant one)

Every terrain and lighting fix of the preceding weeks landed on Campaign
Reimagined's `CR_*` shader fork. The payload OpenShim actually deploys —
`resources/renderer/enhanced/` — had not moved since before that work, so the
generic Enhanced renderer still carried:

| Superseded behaviour still shipping | Fixed in CR by |
| --- | --- |
| Diffuse gated on `N.V` — the confirmed cause of the black pools on grazing terrain | `fe3e5ee` |
| Unclamped detail-map multiply, which annihilates terrain colour where `mn_detail.dds` runs to 0.0 | `fe3e5ee` |
| Unbiased PCF, no comparison sampler, no cascade blending, no receiver normal offset, no terminal fade | `a11d925` |
| No detail-derived normals | `5a607fd` |

Two consequences. Anyone running Enhanced **without** CR installed got the
superseded renderer, black pools included. And
`OPENSHIM_RENDER_PROFILE_ARCHITECTURE.md` §3 described "modern PSSM behavior
(cascade blending, comparison PCF, receiver normal offset, terminal fade)" as
part of DX11 Enhanced — describing a payload that did not exist.

CR's authored sources are now ported across mechanically. The transform is
total and dumb: file references map to their payload names, every remaining
`CR_` identifier becomes `OSE_`, bytes are otherwise untouched (CRLF
included). The base/terrain GLSL delegates and the whole `terrain_glow` family
were already at parity and come through byte-identical, which is a useful
check on the transform itself.

### Smaller things found on the way

- **A dangling payload reference.** OpenShim's `.program` files had prefixed
  the `.glsles` source names (`openshim_enhanced_base-vertex.glsles`) but ship
  no `.glsles` payload. CR correctly points at the stock engine files. Now
  restored to the unprefixed names.
- **The resources.version marker could match a prefix.** The validator
  compared with `strncmp` over the number of bytes it had just *read*, so any
  marker that is a strict prefix of the compiled expectation matched: a stale
  `"1"` deployment would validate against a `"12"` DLL and render the
  superseded payload with `resources.compatible=yes`. Now compared in full,
  with the comparison split out so it can be tested with multi-character
  versions rather than only the single character that ships today.
- **The benchmark launched the game inside the caller's job object.**
  `run_live_combat_benchmark.ps1` used `Start-Process`, so under an agent
  session the game was torn down partway through the run (observed 7–28s),
  arriving as an orderly `WM_CLOSE`. The run then reads as a short session
  that quit on its own, and whatever frames landed first get analysed as the
  measurement. Now created through `Win32_Process.Create`, which gives it no
  parent job — verified by checking the launched process's parent is
  `WmiPrvSE`, not the session.

### Ownership migration

- The Enhanced payload is canonical (above).
- `scripts/Compare-EnhancedShaderParity.ps1` is the binary half of the gate
  the roadmap puts in front of deleting CR's duplicate: it re-namespaces every
  CR source and compares byte-for-byte, so drift cannot hide behind the
  prefix. **All 14 files pass.** Seeded a one-constant edit to confirm it
  detects, names, and exits non-zero rather than passing quietly.
- The in-flight diagnostic/shader edits that were sitting uncommitted on the
  unrelated `agent/pilot-flashlight-scene-light-flip` worktree are carried onto
  this branch as their own commit, so the two workstreams are separated.

### Benchmark

`scripts/Get-RenderEvidence.ps1` parses a run's `openshim.log` and Ogre log
into one record carrying what the roadmap asks each capture to be labelled
with: effective backend, resolved profile and its source, capability bits,
deployed `resources.version`, sRGB conversion state, the `.program` scripts
Ogre actually parsed, and the scheme rewrites that prove the profile reached a
viewport. It exits non-zero when the run cannot be read as a capture at all.

It exists because the label cannot come from the ini written beforehand:

- `Ogre.cfg`'s `Render System=` line is not authoritative — the shim rewrites
  the backend at `ConfigFile::load`.
- An arm that never engaged is indistinguishable from a null result unless
  something counts what it actually did.
- A shader edit that renders nothing is usually an edit to a payload the
  engine did not load.

Run against the current install it reports **`parsed=both`,
`rendering=CampaignReimagined`**. Both payloads load — that is what the
disjoint namespaces are for — but CR ships the `en-*` techniques on the
stock-named materials, so CR's programs are what the scheme resolves to and
the `OSE_` programs are compiled and then referenced by no material. Parsed
and rendering are therefore separate fields in the record.

---

## 2. What is deliberately NOT done here

**The visual validation itself.** Phase 0 item 1 is "visually validate the
N·V diffuse correction, detail-normal derivation, and shadow bias changes" and
"resolve the remaining terrain dark-region/cotangent-frame question". Those are
judgements about what the screen looks like; automating around them would
produce confident-looking evidence of nothing. The checklist is §3, and it was
**signed off on 2026-09-13**. The cotangent-frame question in §3.4 was
therefore never opened: the dark regions did not survive the two lighting
fixes, so there was nothing left for the debug modes to attribute.
`OSE_TERRAIN_NORMAL_BASIS_MODE` stays at 0.

**A dense-base-battle fixture.** The roadmap's fifth scene is not one of the
four worlds and is not built here. `lcbench`'s `fourteam` scenarios already
put two opposing fronts of up to 80 craft in a single frustum, which is the
closest existing thing; a real base battle needs buildings and production,
which is a content fixture rather than a terrain one.

**Deployment.** `resources.version` is now `2`, so the payload and the DLL
must be deployed **together** — a v2 payload beside the installed v1-expecting
DLL will fail the pairing and stand Enhanced down (which is the marker working
as intended, not a regression). The install was left untouched: it currently
runs `resources.version=1`.

---

## 3. Manual verification

**Status: passed 2026-09-13.** Kept here as the procedure to re-run against
any future change to the terrain or lighting path, not as an open action.
§3.6 is the exception — the Steam and Proton/Wine lanes are still unverified.

### 3.1 Before anything else — deploy both halves together

```
powershell -ExecutionPolicy Bypass -File scripts\Deploy-OpenShim.ps1
```

Then confirm the pairing took:

```
powershell -ExecutionPolicy Bypass -File scripts\Get-RenderEvidence.ps1
```

Expect `deployed: resources.version=2` and
`enhanced: supported=yes resources.compatible=yes`. If it says
`resources.compatible=no`, the two halves are mismatched — that is the whole
point of the bump, so fix the deployment rather than the marker.

### 3.2 The one that actually matters: is the payload reachable?

On a CR install, `rendering=CampaignReimagined` is expected and correct, and
it means **every visual check below is testing CR's shaders, not the ported
OpenShim copy.** Since they are now byte-identical modulo namespace, the
result transfers — but only because the parity script says so. Re-run it
whenever either side changes:

```
powershell -ExecutionPolicy Bypass -File scripts\Compare-EnhancedShaderParity.ps1
```

To see the OpenShim payload render, the mod folder has to leave `mods\`
entirely — renaming it does not disable it, Redux scans by content.

### 3.3 Visual checks (DX11, Enhanced, windowed)

Set `Full Screen=No` in `Ogre.cfg` first if you want capturable screenshots;
fullscreen DXGI defeats screen capture.

1. **Black pools / the N·V correction.** Drive a ground vehicle on an airless
   map (Moon is the harshest — the IBL floor makes "no direct light" a deeper
   hole there than under an atmosphere). Look at ground at a grazing angle
   close to the cockpit, and **move the camera**. What must be gone:
   hard-edged pools of near-black with flat interiors that *slide across static
   ground as you move*. The motion is the tell — a Lambert terminator cannot
   move with the camera.
2. **Detail-map annihilation.** Same view, near field. Terrain detail should
   read as grain, not as contiguous black patches. This is a separate fix from
   (1) and can be checked independently by looking at whether the dark areas
   are *textured* (detail grain, fine) or *flat* (annihilated, bad).
3. **Shadow bias / PCF.** Look along a low sun angle at terrain with relief.
   Check for shadow acne on lit slopes (bias too low) and for shadows
   detaching from their casters — peter-panning (bias too high). Then check
   the cascade seams: pan slowly outward and look for a visible band where
   shadow quality steps. It should blend, not jump.
4. **Cascade far fade.** Keep panning to the shadow terminus. Distant shadows
   should fade out rather than end on a hard line. This is the deferred "PSSM
   terrain cutoff" question — if the line is still hard, it is a real finding,
   and it is the first thing Phase 1 should look at.
5. **Detail-derived normals.** Compare near-field ground relief against the
   previous build. More surface texture is expected; shading that *swims* as
   you move is not.
6. **The LOD boundary.** Approach and retreat past the 250/300-unit
   boundaries watching a vehicle or building. Expect a lighting/reflection pop
   — Enhanced currently falls back to compatibility shading at medium/low LOD,
   and that is the known gap Phase 1 item 1 is scoped to close. Confirm it is
   still a pop and not something worse, then leave it.

### 3.4 The cotangent-frame question

If (1) and (2) look clean and the ground still has dark regions, the shader
already carries the instrumentation to settle it without guessing. Set these
in a temporary `preprocessor_defines` entry on the Enhanced terrain fragment
program and restore to zero afterwards:

- `OSE_TERRAIN_NORMAL_DEBUG_MODE=9` — TBN pairwise orthogonality error, RGB,
  black is ideal. Any bright region is a genuinely skewed frame.
- `OSE_TERRAIN_NORMAL_DEBUG_MODE=10` — T length, B length, basis determinant.
  White is ideal; a dark blue channel means a flipped or degenerate basis.
- `OSE_TERRAIN_NORMAL_DEBUG_MODE=11` — mapped-normal deviation from the
  geometry normal. Tells you whether the map or the frame is responsible.

If (9) and (10) come back clean, the stock derivative frame is not the
problem and `OSE_TERRAIN_NORMAL_BASIS_MODE` should stay at 0 — modes 1 and 2
are diagnostic and should not be shipped on a hunch.

### 3.5 Sanity on the other profiles

Cycle Enhanced → Retro → Redux → Enhanced in one process and confirm each
takes. `Get-RenderEvidence.ps1` will refuse the capture if a profile never
reached a viewport, which is the failure mode that otherwise reads as "the
change did nothing".

### 3.6 Lanes

Validated on GOG. Windows/Steam and the Proton/Wine lanes were **accepted on
the maintainer's judgement on 2026-09-13** rather than measured: nothing in
this pass is platform-specific in principle, and the deployment path is the
only part that changed. Recorded as a decision, not as evidence — if a lane
regresses later, the payload/DLL pairing and the `resources.version` marker
are the first things to check, because they are what this pass altered.

---

## 4. The world benchmark set

The roadmap asks the benchmark for fixed scenes on Moon, Mars, Venus and
Titan. The set covers all nine worlds the game ships — those four plus
Achilles, Io, Europa, Ganymede and Elysium. They install as `addon\lcbworld\`
and are **lcbench**: the same heightfield, material grid, lightmap, mission
script and spawn point, with only the `.trn` swapped.

Holding the geometry fixed is the point. The same ridge and the same tank
formation appear in all nine captures, so a difference between two of them is
the planet — its atlas, palette, sky, fog and sun — and not the terrain under
it. Building nine unrelated scenes would have made the set prettier and
useless for attribution.

Three of the five added worlds pull their weight beyond coverage. Io sets
`Lava=1` and `wave=1` and carries by far the brightest emissive in the set, so
it is the glow path's stress case. Europa is near-white high-albedo ice at a
1500 sun, the lowest angle of the nine, which is where highlight clipping and
shadow contrast surface first. Achilles is the only vegetated world, and green
albedo under an overcast sky is where a colour-space error is most visible.

**Ganymede and Elysium need Campaign Reimagined installed.** Stock ships their
atlas CSV and atlas DDS but no `ga_detail_atlas.material` /
`el_detail_atlas.material` to bind them — so the stock `evolve_*` maps naming
those atlases have nothing to resolve either. That is a gap in the stock
install rather than something these fixtures introduce.
`Test-RenderWorldMaps.ps1` reports each world's atlas material as `stock`,
`mod` or `ABSENT` instead of failing on it.

```
powershell -ExecutionPolicy Bypass -File scripts\Install-RenderWorldMaps.ps1
powershell -ExecutionPolicy Bypass -File reverse_engineering\run_live_combat_benchmark.ps1 -World venus
```

`-World` is recorded in each run's `metadata.json`. `-SunTime 0300` at install
time rewrites the sun in every world to the grazing angle the `N.V` repair and
the shadow bias were fixed for; without it each world keeps its own authored
time (Moon 0900, Mars 0900, Venus 1200, Titan 1100).

Two things about these files fail **silently**, so both are checked by
`scripts\Test-RenderWorldMaps.ps1` rather than left to review:

- The texture-type index set has to be `{0,3,4,5,6}`, because `lcbench.mat` is
  a Moon-authored grid and names exactly those. Mars, Venus and Titan re-map
  their own tiles onto Moon's indices instead of using their stock sets.
- Every `.map` name has to appear in that world's `<xx>_detail_atlas.csv`. The
  name is a key into the atlas, not a file on disk, so a name outside the CSV
  resolves to the default tile and the terrain renders — wrong, and only where
  that tile was used. Some names in stock `.trn` files are not in the matching
  CSV (`ma03ca0.map`), so "a stock map uses it" proves nothing. Seeded exactly
  that substitution to confirm the check names the offender and exits non-zero.

All nine were launched on the GOG install under DX11 Enhanced and render their
own planet, with `Get-RenderEvidence.ps1` reporting a coherent capture and no
missing material or texture in the Ogre log.

Venus's stock `[LightningBolt]` block is deliberately omitted: it fires on a
random 5-30 s timer and adds a dynamic light, which is authentic Venus and
poison for a frame-time capture. It is one paste from `Edit\trn\venus.trn`
when a capture is specifically about that effect.

---

## 5. State

| Phase 0 item | State |
| --- | --- |
| Close out terrain/lighting work | Code side done and shipping; **visual sign-off given 2026-09-13** |
| Terrain dark-region / cotangent frame | Not pursued: the dark regions did not survive the two fixes, so the §3.4 debug modes were never needed. `BASIS_MODE` stays 0. |
| Renderer ownership migration | Payload canonical, parity gate automated and passing |
| Remove CR/OpenShim duplication | **Done** — CR PR #65 deletes the 14 duplicated files, repoints its materials at `OSE_*`, and moves the shader toolchain with them |
| Repeatable visual benchmark | Evidence/labelling, launch reliability and the nine-world fixture set all done (§4) |
| Dense base battle fixture | Not built — `fourteam` is the nearest existing scene (§2) |
| DXBC-identical for unchanged paths | Not attempted this pass — the payload deliberately changed |

**Phase 0 is closed.** The Steam / Proton-Wine lanes were accepted on the
maintainer's judgement (§3.6) rather than measured; everything else was
verified.

The CR-side removal is
[CampaignReimagined#65](https://github.com/GrizzlyOne95/Battlezone98Redux_CampaignReimagined/pull/65).
It deletes the 14 duplicated files, repoints CR's two big materials and its
static-IBL wrapper at `OSE_*`, and moves CR's DX11 shader toolchain onto the
payload rather than deleting 1400 lines of guards along with their subject. A
new `Tools/Test-ProgramReferences.ps1` resolves all 1021 owned program
references against the union of CR's and the payload's declarations, because
Ogre does not error on a material naming a program nothing declares — it drops
the technique and the map renders anyway, darker or unlit or stock.

One ordering constraint for whoever publishes CR next: staging copies the
payload out of `BZR_OPENSHIM_REPO` on every publish, so the build must be
staged against OpenShim at `main` or later.
