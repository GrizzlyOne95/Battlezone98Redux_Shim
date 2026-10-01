# Nav Beacon Contact Netcode Storm — Research / TODO

**Date:** 2026-10-01  
**Status:** Research backlog; no native patch is claimed by this document.  
**Scope:** Battlezone 98 Redux multiplayer, nav beacon collision/contact handling, replication, and network traffic.  
**Target:** Root-cause and patch the behavior natively in OpenShim rather than relying on Lua beacon replacement/workarounds.

## Problem statement

Community multiplayer testing reports a severe network traffic storm when a nav beacon remains in physical contact with another object. A particularly reliable case is landing a pod on a nav beacon and leaving it there.

The reported behavior is:

- While sustained contact exists, the nav appears to generate network activity continuously.
- The activity is reported as occurring once per frame, per connected player.
- Higher client FPS therefore makes the storm materially worse.
- More players multiply the impact.
- Deleting the affected nav ends the storm.
- Recreating a nav at the same position can immediately reproduce the storm if the same contact/placement condition remains.
- Existing gameplay workarounds remove/rebuild or transfer beacons, but do not address the native defect.

These observations are currently **community reports, not yet independently proven in OpenShim instrumentation**. The first task is to capture the packet/event behavior and identify the exact native path responsible.

## Why this belongs in OpenShim

This is not fundamentally a scripting problem if the engine is emitting redundant replication traffic from a native collision/contact path.

A Lua workaround can hide the symptom by deleting/rebuilding nav beacons, but it has undesirable properties:

- mission/mod authors must opt in;
- it changes object identity and potentially team/ownership state;
- replacement at the same location may immediately recreate the triggering contact;
- it cannot reliably fix an engine path whose emission rate scales with frame rate.

OpenShim already owns native engine hooks, packet instrumentation, network optimization, and multiplayer reverse engineering. A narrow engine-side correction is preferable if the behavior is confirmed.

## Existing OpenShim surfaces to reuse

Relevant existing work includes:

- `src/patches/net_optimizer.cpp`
- `src/patches/bzrnet_instrumentation.cpp`
- `include/bzrnet_instrumentation.h`
- `Docs/NETCODE_UPSTREAM_PARITY.md`
- `Docs/MULTIPLAYER_BUG_SOURCE_INVESTIGATION.md`
- `Docs/audit_20260925/G_network.md`
- `reverse_engineering/bsim/` tooling and object-model work

Do not create a parallel packet-capture stack for this investigation. Extend/reuse the current instrumentation where practical.

## Primary research questions

1. **What packet/event actually explodes under sustained nav contact?**
   - object permanent-state update;
   - collision/contact notification;
   - ownership/team update;
   - transform/position correction;
   - command/status update;
   - another packet family.

2. **Which peer originates the repeated traffic?**
   - nav owner only;
   - object touching the nav;
   - host;
   - every peer;
   - some replicated callback causing each peer to rebroadcast.

3. **Does the emission rate truly track simulation/render FPS?**
   - Verify with capped FPS rather than relying on subjective lag.
   - Distinguish simulation tick rate from render frame rate if they differ.

4. **Why does player count amplify it?**
   - one send broadcast to N peers;
   - N peers independently resend;
   - echo/rebroadcast loop;
   - recipient-specific state packets.

5. **What state is being marked dirty every frame?**
   - collision contact;
   - transform;
   - nav physics state;
   - ownership;
   - team;
   - perceived team;
   - deployed/grounded state;
   - another bit/field.

6. **Is this inherited from legacy Battlezone code or introduced/changed in Redux?**
   - Compare available 1.4/1.5 source/decomp behavior.
   - Compare Redux released binary path.
   - If BZP-T's partial fix is available for inspection, identify exactly what it suppresses and whether it is safe to port conceptually.

## Reproduction matrix

Create the smallest deterministic MP test map possible with one nav beacon in open terrain.

Test at minimum:

| Dimension | Cases |
|---|---|
| Players | 2, 3, 4 |
| FPS cap | 30, 60, 120, 240 where supported |
| Contact object | landed pod first; then vehicle / other simple object as useful |
| Contact duration | 0 s, 5 s, 30 s sustained |
| Nav lifecycle | original nav, deleted nav, rebuilt same location, rebuilt clear of contact |
| Authority | host-owned vs remote-player-owned where controllable |

Capture:

- packets/sec per peer;
- bytes/sec per peer;
- packet/event type;
- sender/receiver;
- relevant distributed-object IDs;
- traffic before contact, during sustained contact, and after separation/deletion;
- exact FPS during each sample.

The important result is not just “lag happened.” Produce a table showing whether packet rate has a linear or near-linear relationship to FPS and/or player count.

## Instrumentation TODO

- [ ] Add a temporary, opt-in diagnostic that can aggregate packet counts by packet/event discriminator without dumping every packet to disk.
- [ ] Include sender/recipient and object/network ID where safely decodable.
- [ ] Add per-second counters so a 240 FPS repro does not create unusable logs.
- [ ] Record current FPS/tick timing alongside the counters.
- [ ] Capture the first transition into sustained contact and the first frame after separation.
- [ ] Verify whether packet contents are identical or contain a changing field.
- [ ] Verify whether traffic is generated before the socket layer by tracing the likely native send call where possible.
- [ ] Keep diagnostics disabled by default and avoid adding release hot-path overhead when not enabled.

## Native code-path investigation TODO

Start from both ends and meet in the middle.

### From the network emission side

- [ ] Identify the packet family whose rate spikes.
- [ ] Trace its native producer back from `Net::Send` / distributed-object state emission.
- [ ] Determine whether the same object is queued/serialized every frame.
- [ ] Determine whether recipients rebroadcast the event.
- [ ] Identify the dirty/update flag or callback that causes repeated sends.

### From the nav/contact side

- [ ] Identify the Redux nav beacon class/vtable and collision/contact callbacks.
- [ ] Trace sustained-contact execution, not just first-contact execution.
- [ ] Determine whether the nav or touching object mutates replicated state every frame.
- [ ] Compare first contact, continued contact, separation, and re-contact.
- [ ] Check whether local/remote authority guards are present and correct.
- [ ] Check whether a contact callback invokes a generic distributed-object update path that assumes state changed.
- [ ] Check whether object settling/penetration correction continually changes a replicated transform or status bit.

### Legacy comparison

- [ ] Locate the closest 1.4/1.5 nav/contact path available in Battlezone source/decomp material.
- [ ] Compare dirty-state and send semantics with Redux.
- [ ] Record any Redux-only divergence before proposing a patch.
- [ ] Do not copy addresses/register layouts from another build as released Redux proof.

## Candidate root-cause classes

These are hypotheses only. Do not implement one until instrumentation identifies the actual path.

### A. Redundant dirty-state marking

A sustained collision callback may mark the nav or touching object dirty every simulation frame even when the serialized state is unchanged.

Possible fix shape: make the state transition edge-triggered or only mark dirty when the replicated value actually changes.

### B. Missing authority guard

A contact callback may run on both authoritative and remote replicas, with each peer producing a network-visible update.

Possible fix shape: limit the network-producing side effect to the correct object owner/authority while preserving local presentation/physics behavior.

### C. Identical packet re-emission

The object may legitimately enter the update path every frame, but the serializer may emit an identical state packet each time.

Possible fix shape: suppress only demonstrably redundant, identical state emission for this semantic path rather than applying a generic socket-layer rate limit.

### D. Contact/penetration feedback loop

Physics correction may slightly move or toggle the nav each frame, making the engine believe state genuinely changed.

Possible fix shape: correct the underlying nav contact-state transition or epsilon/settling behavior rather than dropping packets downstream.

### E. Echo/rebroadcast loop

A received contact/state event may cause remote peers to re-mark the object dirty and transmit it again.

Possible fix shape: distinguish replicated application from authoritative local mutation so received state cannot re-enter the send path.

## Patch design constraints

The final fix should be as high in the causal chain as possible.

Preferred order:

1. fix incorrect nav/contact state transition;
2. fix incorrect authority/dirty-state behavior;
3. suppress a known redundant object-state emission;
4. use packet-layer filtering/rate limiting only if the engine producer cannot be patched safely.

Avoid a generic “drop excess packets” workaround. That risks hiding legitimate state changes and producing multiplayer desync.

All build-specific sites must follow existing OpenShim policy:

- register/resolve through the normal patch infrastructure;
- use signatures / expected bytes / build identity where applicable;
- fail closed on unknown builds;
- do not scatter raw addresses through feature code.

## Acceptance criteria for an implementation PR

A future implementation is not complete until the following are demonstrated.

- [ ] Sustained pod-on-nav contact no longer causes traffic to scale with FPS.
- [ ] Traffic under the repro remains bounded at 30/60/120/240 FPS.
- [ ] Increasing player count does not create the previous multiplicative storm.
- [ ] Nav beacons still replicate ordinary placement, movement/state, team/ownership changes, destruction, and recreation correctly.
- [ ] Passing a nav between allied players does not create stale ownership or identity state.
- [ ] Deleting and rebuilding navs works normally.
- [ ] Separating the contact object does not leave latent network spam.
- [ ] No observed desync between host and clients after several minutes of play.
- [ ] No regression in unrelated distributed objects.
- [ ] Patch fails closed when the target binary/signature does not match.
- [ ] Diagnostic instrumentation can remain available behind an explicit opt-in switch, or is removed cleanly if it has no continuing value.

## Useful validation experiment: transfer/rebuild workaround

The reported Lua workaround is useful as a diagnostic even though it is not the desired fix:

1. create a nav and trigger the sustained-contact storm;
2. transfer/delete/rebuild the nav;
3. rebuild once in the same triggering placement;
4. rebuild once in a clear placement;
5. compare packet counters.

If same-position rebuild immediately restores the same traffic profile while a clear-placement rebuild does not, that strongly points to contact geometry/state rather than “corrupted nav identity” as the persistent cause.

## Deliverables from this research item

The next substantive PR should contain, at minimum:

- a packet-rate reproduction table;
- identified packet/event family;
- originating native function/callback;
- authority/dirty-state explanation;
- Redux address/signature evidence appropriate to OpenShim's patch workflow;
- comparison against legacy behavior where available;
- proposed minimal native patch;
- before/after MP captures at multiple FPS values and player counts.

Until those are present, treat this as an open research problem rather than a solved netcode defect.
