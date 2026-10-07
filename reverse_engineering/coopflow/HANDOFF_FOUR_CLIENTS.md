# Four-client misn05 qualification

Resumed at the user's request on 2026-10-07. Full nine-case suite
`C:\BZRCoop\runs\suite-20261007-183449` is in progress, with new native
sequence-rejection and subtitle-overlay health gates. Final qualification
is pending. Earlier checkpoint results below predate these gates.

The user's observed team-4 100% loss is real: the host screenshot in the win
run at 181309 shows 55 ms / 100%. Reliable ACKs still advance while newer
unreliable packets are rejected, consistent with a native reliable backlog.
The precise initial cause remains unproven. `#0 expected` does not prove a
sequence reset, and zero relay drops do not prove native acceptance.

The traced retry `cr-misn05-net-trace-4p-20261007-183555` passed 14 steps /
23 checks and the separate native analyzer passed all four clients. Team 4
has zero post-loading unreliable rejections; its host closing screenshot shows
15 ms / 0% loss. Team 2 shows intermittent loss (10% in that screenshot,
worst five-second rejection window 17): do not claim measured zero loss on
every peer. Relay code is unchanged. The arbitrary run suffix differs from
the actual start time; timestamps in the evidence record the real time.

CR dc0163c fixes the independently reproduced subtitle notice: consecutive
Play calls destroyed/recreated the renderer within its creation throttle.
Replacement now reuses the renderer; explicit Stop still destroys it. Its
nine-check regression fails the old source and passes the fix. All four
subtitle health checks pass in the traced retry. The win harness now checks
alliances before the ten-second film and validates skipping before captures;
the retry had 8.525 seconds remaining before input. The authored film is unchanged.

Server 3424853 adds native_network_health.py and ten tested fixtures. It
rejects sustained post-loading unreliable sequence rejection; this is a
diagnostic heuristic, not measured zero packet loss. The harness uses it as
a hard final gate on complete archived logs, saves relay-trace.jsonl, hashes
the analyzer, and requires it in the server checkout. Participant fixture
now passes 12 checks, including subtitle fallback failure.

## Proven checkpoint

`C:\BZRCoop\runs\cr-misn05-first-4p-20261007-171015` passed **15 steps / 19
checks**, with four native clients on teams 1–4, full registries, correct local
craft ownership, directional alliances and host-only campaign authority.
All four received 40 scrap / 10 pilots with sufficient native capacity and
spawned within 75 m of the leader. Full waves, defense/weather, surviving-enemy
victory gates, team-7 friendly fleet, a team-2 local skip and the commander
reveal completed. Every client called SucceedMission exactly once; all three
guest presentation streams matched the host. No Lua/script errors or audio
warnings. Assists accelerate timers/combat and act on each object's owner.

## Source state

- Dedicated server: `agent/four-client-relay`, committed/pushed **3420021**.
  `--relay-pair-ports` allocates a stable opaque UDP relay socket per pair;
  the native four-client mesh uses six ports. Real UDP three/four-peer,
  compatibility 45/45, impairment 5/5 and CLI smoke 6/6 passed. Public relay
  association parity remains unqualified.
- Canonical Campaign-Reimagined: `agent/misn05-four-player`, committed/pushed
  **1c7640c**. Fixes distant team-3/4 spawn buoys and copied motion vectors,
  reserves local resource capacity before starting resources. Lua 5.1
  presentation/capacity 22, early flow 117, map contract, source audit 501 and
  repository validator passed before the live win. Existing shipping entries
  suffice. Changes were tested through generated overrides; this workstream
  has not deployed them to the main GOG installation or Workshop.
- Harness: `agent/four-client-coop`, task changes **uncommitted**. Adds variable
  2–4 participants, native limit selection, complete roster/ownership checks,
  all-participant parity/error checks, exact-one-result checks, run input hashes,
  four-player scenarios and `Run-BZRCoopFour.ps1` (nine cases, stop on failure).
  Participant regression passed 11 checks; ten scripts parsed before the latest
  session-file change. Preserve the preexisting, unowned
  `coopflow/TEXT_ENTRY_STATE.md` diff; never stage it with this work.

Generated `coopflow/overrides/misn05-coop` was rebuilt from CR 1c7640c with the
current EXU Release DLL. `flow-inputs.json` records exact hashes and arguments.
Main-install native binaries and Steam Workshop cache were not changed.

## Next work after an explicit resume

1. Validate the **latest, untested** `Write-SessionFile` change in
   `BZRCoopSession.ps1`: write to a sidecar, atomically replace the destination,
   retry IOException for up to five seconds, remove the sidecar on failure.
   A Windows reader/writer contention test is still needed. It was added just
   before the pause; no checks or launches followed it.
2. Restart `Run-BZRCoopFour.ps1`. The services case was moved first to qualify
   the new fixture before repeating the win matrix. The suite
   `C:\BZRCoop\runs\suite-20261007-171604` stopped **NO RUN** at services because
   the old Set-Content session writer collided with a polling reader before
   mission load. No services assertion has run live yet.
3. Complete all-to-all terrain/object pings, every owner's teammate respawn,
   four pilot rescue requests/responses/cancellations, scheduled simultaneous
   Lemnos fallback, team-4 fifth-death failure; then wins with teams 2/3/4 and
   host skipping, natural films, both objective losses and host departure.
4. Fix any real failure; update harness/CR evidence docs and commit/push only
   task-owned changes. Consider local deployment through the established CR
   manager after qualification; no public publication is authorized here.

Retain earlier failed attempts as evidence: native lobby cap defaults to 2
even on a four-player map; gameSettings member limit is index 9; Wait-Until's
Name parameter must not shadow the guest display name. The original shared
relay port caused third-player ambiguity. First four-player mission attempt
`cr-misn05-first-4p-20261007-170003` then exposed genuine resource clamping
(host 35 capacity; guests zero) and distant team-3/4 starts, fixed in CR.

Stock destruction messages remain unsuppressed. Four-player screenshots also
show the existing PDA per-player readiness label can say Syncing on guests
despite a ready native/CR session; that display behavior was observed but not
changed. Real four-player PDA key workflows, other missions, Steam/Wine/Proton,
WAN/firewall behavior, combat balance and offline save/reload are unqualified.

Always launch through BZRHarness's machine-wide lock, with
`BZR_FORCE_WINDOWED=1`, and stop each native game via Stop-BZRGame -NoForce /
WM_CLOSE. Clear inherited PSModulePath before Windows PowerShell 5.1 runs.
