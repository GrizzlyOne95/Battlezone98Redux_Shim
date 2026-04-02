# Chunk Fragment Path Validation

Date: March 26, 2026

## Goal

Confirm whether legacy Battlezone still uses a real craft-fragment path for
vehicle death, so Steam Redux traces can be judged against a known-good
baseline.

## Legacy Runtime Setup

- EXE: `C:\Program Files (x86)\Battlezone\bzone.exe`
- PDB: `C:\Program Files (x86)\Battlezone\bzint.pdb`
- Match status: exact legacy EXE/PDB match confirmed in
  [`reference.json`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\badlands\legacy_bz1_exact_full\pdb_reference\reference.json)
- Live trace helper:
  [`legacy_bzone_chunk_trace.js`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\legacy_bzone_chunk_trace.js)

The Frida helper attached to the live legacy process and traced:

- `Craft::Explode`
- `ChunkEffect::PartialFragmentObject`
- `ChunkEffect::FullFragmentObject`
- `ChunkEffect::CreateChunk`
- `ChunkEffect::CreateChunklet`

## Observed Legacy Death Path

Live `avtank` destruction produced:

- repeated `CreateChunklet` bursts before and during the final explosion
- `PartialFragmentObject` calls that immediately fed `CreateChunk`
- a later `Craft::Explode` event that then called `FullFragmentObject`
- additional `CreateChunk` and `CreateChunklet` calls from that same death

Representative trace lines from
[`tmp_legacy_frida.log`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\tmp_legacy_frida.log):

- `[Craft::Explode] this=0xb01988 obj=0x44dac000`
- `[FullFragmentObject] this=0xb1a788 obj=0x136d5f70`
- `[CreateChunk] this=0xb1a788 obj=0x136d5a98`
- `[CreateChunklet] this=0xb1a788`

## Conclusion

Legacy `avtank` death does use the real craft-fragment path:

`Craft::Explode -> FullFragmentObject / PartialFragmentObject -> CreateChunk`

Generic `CreateChunklet` debris still appears around the same death event, but
it does not replace the real fragment-object path.

## OpenShim Implication

The Steam-side question is no longer "does the legacy game really fragment real
craft pieces?" That is now confirmed.

The remaining Steam-side question is:

- does Steam Redux still call the equivalent fragment-stage functions before
  `CreateChunk`, or
- does the tested death path collapse directly into generic `CreateChunklet`
  debris before OpenShim sees any recoverable craft-piece source object?

To support that investigation, OpenShim now logs `caller` and `callerRva` on
`[CHUNKSPAWN] CreateChunk ...` and `CreateChunklet ...` lines, plus a short
`[CHUNKSPAWN]   bt ...` native backtrace line for the same event. Newer builds
also add conservative `callerTag` and `path` labels for recurring observed
Steam chains, so each chunk creation event has an upstream callsite fingerprint
even when the fragment function itself is not hooked yet.

As of the later March 26 Steam Redux traces, OpenShim also recognizes the
recurring real fragment-create chain:

`0x00492565 <- 0x004924F5 <- 0x004AC5E0 <- 0x004EE768 <- 0x004DF34A`

For `CreateChunk` specifically, the shim now logs a raw native stack snapshot
and best-effort decoded `stackObj` candidates alongside the normal
`[CHUNKSPAWN]` line, so the next Steam repro can show which live fragment
object pointers survive on the stack before the created chunk object is fully
mutated.

## April 2, 2026 Repro Update

### Goal

Close the loop between the legacy Frida trace and the Steam Redux `winmm.dll`
 telemetry so the shim can reliably drive Ogre chunk mesh bridging from the
 same per-instance fragment owner data that Frida sees.

### Redux Automated Repro

- Game: `C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux`
- Packaged mod target:
  `C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux\packaged_mods\3686673790`
- Mission launch:
  `battlezone98redux misn06.bzn /edit`
- Cutscene skip timing:
  send `SPACE` during load, `150ms` after the first main window appears
- Automation helper:
  [`run_misn06_auto_capture.ps1`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\run_misn06_auto_capture.ps1)
- Current validated shim hash:
  `9303CBA2DF99AA09AF4A9936770DB2FDEB82F544AD5BCB5E65FD31BB5A216C01`

### Current Shim/Frida Parity

The legacy Frida trace still proves the canonical fragment path:

- `Craft::Explode`
- `PartialFragmentObject` / `FullFragmentObject`
- `CreateChunk`
- surrounding `CreateChunklet`

The Steam Redux Frida owner trace confirms the same live craft root identity is
present in the fragment walker:

- Frida saw `_svtank` at `gameObj=0x029E5320` during
  `CreateChunkParent` / `FragmentParentA` in
  [`frida.log`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\snapshots\misn06_auto_20260402_090250\delay_0150ms\frida.log)

The clean Redux shim run now mirrors that same identity without Frida:

- `selectedOdf=svtank`
- `rootOdf=svtank`
- `ownerBase=svtank`
- `ownerMesh=svtank.mesh`
- stable per-instance root tuple
  `root=0x4025E678 rootGameObj=0x029E5320 ownerObj=0x3B3C58F8`

Representative clean lines from
[`openshim.log`](C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux\openshim.log):

- `CreateChunk ... callerRva=0x00092565`
- `srcTree ... selectedOdf=svtank ... rootOdf=svtank ... ownerBase=svtank`
- `tracking ... rootGameObj=0x029E5320 ... mesh=svtank/scz11rad.mesh`
- `tracking ... geomName=SCZ11BGB ... mesh=svtank/scz11bgb.mesh`
- `assigned ... mesh=svtank/scz11bga.mesh`

This is the important parity milestone:

- Frida and the shim now agree on the dying craft root game object
- the shim no longer falls back to the old bogus `RocketTankFriend` owner path
- Ogre payload selection is already using that root-bound identity for real
  piece meshes like `scz11rad`, `scz11bga`, `scz11bgb`, and `scz11bda`

### Practical Outcome

For the current Steam Redux `misn06` repro, OpenShim is now reliable enough to
key fragment rendering from:

- `root`
- `rootGameObj`
- `ownerObj`
- per-piece VDF / geo tokens

instead of guessing from whole-craft mesh matches alone.

That is the required foundation for handling many identical craft instances in
the same mission while still attaching the right Ogre mesh chunk to the right
death batch.

### Remaining Caveat

The game still has a native crash in the same Redux code path:

- `battlezone98redux+0x1e0bc6`

That crash predates the latest owner-token fix and still appears in the
automated runs. The clear chunk-tracing repro, however, now exists on both:

- legacy BZ via Frida
- Steam Redux via clean shim logs and Frida cross-check
