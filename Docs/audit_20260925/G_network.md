<!-- Reviewer worksheet from the 2026-09-25 repository audit. Line numbers refer to commit 17e40c0f (main before the audit branch); bzr_hooks.cpp line numbers shift by up to ~530 lines after the dead-code removal in the same PR. See Docs/CODE_AUDIT_20260925.md for the consolidated, prioritized view. -->

# Networking and multiplayer

Scope read end-to-end: `src/patches/net_optimizer.cpp` (5102 lines), `netcode_hooks.cpp`,
`bzrnet_protocol.cpp`, `bzrnet_instrumentation.cpp`, `bzrnet_trace.cpp`, `mp_faction_restrict.cpp`,
`mp_ready_diagnostic.cpp`, `mp_vehicle_preview_fix.cpp`, their headers in `include/`,
`tests/bzrnet_protocol_tests.cpp`, `tools/validate-network-baseline.ps1`, `net.ini`,
`netcode_manifest.json`; skimmed `Docs/NETCODE_UPSTREAM_PARITY.md` and
`Docs/MULTIPLAYER_BUG_SOURCE_INVESTIGATION.md`. Build settings checked in `Plugin_OpenShim.vcxproj`
and `BZROpenShim.vcxproj`.

## Summary

Overall health is good for a hook layer of this size: every attacker-facing parser (WebSocket
framing, BZR UDP control markers, reorder sequence extraction, sockaddr decoding) bounds-checks
before reading, copy sizes are clamped to fixed-size destinations, build-specific writes are
signature/byte-guarded and fail closed, and nothing in scope mutates simulation state (so no
desync vector was found). `ws2_32.dll` is linked via `/DELAYLOAD` in both projects and every
Winsock call is either through a `GetProcAddress`-resolved pointer or a delay-load thunk; nothing
forces an early static import. The baseline script's invariants (reorder/dup default off, gated
worker creation, warnings present) all hold in the current source.

Top three issues:
1. `Hook_sendto` / `Hook_WSASendTo` clobber `WSAGetLastError()` on the failure path (the
   route-logging helper calls `getpeername` on an unconnected UDP socket before the error is
   read or restored), so the game sees `WSAENOTCONN` instead of the real send error.
2. Per-datagram hot-path overhead: every UDP send performs ~4 syscalls and ~10 heap allocations
   (address refresh, `SocketState` copies, string formatting) before the sampling check that
   discards 127/128 of the log lines; every send/recv copies a three-string `SocketState` just to
   test the `optimized` flag.
3. With `RelayLogging=1`, `bz_relay_control.jsonl` receives the raw `Authorization` message,
   including the Steam/GOG app ticket and lobby passwords, while a Linux-tested redaction helper
   (`SanitizeBzrNetJson`) already exists and is used by the structured trace next to it.

## Findings

### [Medium][High] sendto/WSASendTo failure paths return a clobbered WSA error to the game — src/patches/net_optimizer.cpp:4042, :3974

```cpp
    else
    {
        LogRouteEvent("sendto", s, to, toLen, false, err, true);   // 4042
    }
    LogSocketError("sendto", s, rc, &SocketState::lastSendToError);  // 4044
    return rc;
```
`LogRouteEvent` (2217) begins with `RefreshSocketAddresses(s)` (2222), which calls
`g_RealGetPeerName` (1626). On an unconnected UDP socket that fails and sets the thread's Winsock
error to `WSAENOTCONN`. `LogSocketError` (3694) then reads `g_RealWSAGetLastError()` (3699) and
either returns without restoring (when `logSocketErrors` is off or the read value is
`WSAEWOULDBLOCK`) or logs the wrong code and restores the wrong code (3721). Unlike
`Hook_send`/`Hook_recv`/`Hook_connect`/`Hook_WSASend`, neither `Hook_sendto` (4010-4045) nor
`Hook_WSASendTo` (3940-3978) ends with `g_RealWSASetLastError(err)`. The game therefore cannot
distinguish `WSAEWOULDBLOCK` (retry) from a real failure on its UDP send path, and the shim's own
"sendto failed err=" line reports 10057 instead of the actual error.
Fix: pass the captured `err` into `LogSocketError` (or add an `int err` overload) instead of
re-reading it, and end both hooks with `if (rc == SOCKET_ERROR && g_RealWSASetLastError)
g_RealWSASetLastError(err);` exactly as `Hook_WSASend` does at 3893-3894.
Verifiable: Windows only.

### [Medium][High] Relay control log writes raw auth tickets and passwords despite an available redactor — src/patches/net_optimizer.cpp:1857-1874, :1195

```cpp
        std::string compact = message;                       // 1861
        ...
            compact.c_str());                                // 1874
```
`WriteRelayControlMessage` writes the full WebSocket text frame to `bz_relay_control.jsonl`.
`LoadConfig` turns `RelayLogAllControl` on whenever the user-facing `RelayLogging` master switch
is set (1195: `g_Config.relayLogAllControl = true;`), and `IsRelayControlMessageType` (1809) then
admits every message, including `Authorization`, whose body carries `steamAppTicket` /
`gogAppTicket` / `authTicket` (see `reverse_engineering/BZRNET_NATIVE_INSTRUMENTATION.md:132`).
`bzrnet_protocol.cpp:186` (`SanitizeBzrNetJson`) already redacts exactly those keys plus
`password`, and the structured trace beside this log uses it; `openshim.ini.example:1089` tells
the user tickets "remain redacted from the structured trace" but only says raw logs "still contain
private data" in general terms. A tester following the documented "set RelayLogging=1 and send the
logs" flow therefore ships a reusable platform ticket.
Fix: in `ProcessWebSocketMessage` (1880) replace `WriteRelayControlMessage(s, outbound, type, json)`
with the `.json` of `SanitizeBzrNetJson(json, /*privateForensic=*/true)` (keeps identities and
endpoints for the replacement-service use case, redacts only secrets). Optionally reuse
`ExtractBzrNetMessageType` instead of the naive `ExtractJsonMessageType` (1836).
Verifiable: the redactor is covered by `tests/bzrnet_protocol_tests.cpp` on Linux; the call-site
change itself compiles only on Windows.

### [Medium][High] Partial faction-restrict install leaves one call site pointing at an interceptor with no original — src/patches/mp_faction_restrict.cpp:407-414

```cpp
    if (!patchCallSite(netvehCall) || !patchCallSite(missionCall))
    {
        ...
        g_OrigLoad = nullptr;
        g_ClearBucket = nullptr;
        return;
    }
```
If the `netveh` site patches and the `mission` site fails (`ApplyPatch` returns false on an
`expected_original` mismatch or `VirtualProtect` failure; `src/engine/hook_engine.cpp:65-69`),
the first site now calls `LoadVehicleListIntercept`, which does `if (g_OrigLoad) g_OrigLoad(...)`
(328) and otherwise returns without loading anything. Result: the Create Game vehicle list is
empty on that build. This is the one place in scope that fails open rather than closed.
Fix: patch the second site first into a local, and on failure restore the first site's original
bytes (the `original[5]` buffer is already in hand) before clearing `g_OrigLoad`; or keep
`g_OrigLoad` set so the interceptor still delegates even when pruning is disabled.
Verifiable: Windows only.

### [Medium][High] Build-specific .data/.text addresses live in feature code instead of `scripts/patches.json` — src/patches/net_optimizer.cpp:88, :167-179; src/patches/mp_ready_diagnostic.cpp:45-51, :123-133, :517, :534; src/patches/mp_faction_restrict.cpp:119; src/patches/mp_vehicle_preview_fix.cpp:29

```cpp
    static uint32_t* const kGovRateAddr = reinterpret_cast<uint32_t*>(0x008e8d14);   // net_optimizer 88
    { 0x008e8cf4, "MinBandwidth",  500,  100000 },                                    // net_optimizer 168
    getter.address = 0x00753810;                                                      // mp_ready 534
```
AGENTS.md: "Put build-specific sites and addresses in `scripts/patches.json`; do not scatter raw
addresses through feature code", and `Docs/AGENT_PATCH_WORKFLOW.md:19` names the `globals`
section for direct addresses. Eleven `.data` globals (governor rate + ten `[Net]` tunables), nine
byte-guarded code addresses plus six data addresses in `mp_ready_diagnostic.cpp`, the `0x158`
call-offset in the faction loader, and the render-globals address in the preview fix are all
literals. The runtime guards (governor signature + per-global plausibility gate; byte guards;
loader-body check) mean these do fail closed today, but the Steam build variant story that
`patches.json` already handles (`fallback_gog` / `fallback_steam`, see `scripts/patches.json:494`)
is unavailable to them, and `verify_windows.ps1` / `patch_registration_tests` cannot see them.
Fix: register each as a `globals` entry with `expected_original` (for code) or a plausibility
range comment (for data), resolve through `HookEngine::ResolveNamedAddress`, and keep the
existing runtime gates. Do not change the addresses themselves.
Verifiable: `tests/patch_registration_tests.cpp` on Linux covers registration parity.

### [Low][High] Reorder path drops any datagram larger than 1500 bytes — src/patches/net_optimizer.cpp:4227-4245

```cpp
        uint8_t packetBuffer[kReorderMaxPacketBytes] = {};   // 1500
        ...
        int rc = g_RealWSARecvFrom(s, &packetWsabuf, 1, &firstBytes, &firstFlags, ...);
        if (rc != 0) { ... return rc; }
```
When `EnablePacketReorder=1`, the hook receives into its own 1500-byte buffer regardless of the
size of the caller's buffers. A datagram larger than that completes with `WSAEMSGSIZE` and the
tail is discarded by the kernel, so the game (which may have supplied a larger buffer) loses the
packet outright; the same happens in the drain loop (4352-4372). `ScatterCopy` (2296) likewise
silently truncates when the caller's buffers are smaller than the buffered packet, returning 0
with `*flags = 0` instead of `WSAEMSGSIZE`/`MSG_PARTIAL`. Experimental and off by default
(the baseline script enforces that), but anyone enabling it for the documented "controlled
testing" gets a silent semantic change.
Fix: size `packetBuffer` to `max(1500, GetRequestedWsabufBytes(buffers, bufferCount))` capped
at 65535 (or bypass reorder when the caller's request exceeds `kReorderMaxPacketBytes`), and
propagate `WSAEMSGSIZE` from `CopyPacketToCaller` when `copied < dataLength`.
Verifiable: Windows only.

### [Low][Med] Buffer-log capture reads past `buffers[0]` when the caller scatters — src/patches/net_optimizer.cpp:4221, :4273, :4303, :4339, :4410, :4436

```cpp
                buffers && bufferCount > 0 && buffers[0].buf
                    ? reinterpret_cast<const uint8_t*>(buffers[0].buf)
                    : nullptr);
```
`CaptureRecvPathEvent` (4060) copies `min(delivered, bufferLogPayloadBytes)` bytes (up to 2048
under relay capture) from `buffers[0].buf`, but `delivered` was scattered across all WSABUFs by
`ScatterCopy`. If the game ever passes more than one WSABUF with `buffers[0].len < delivered`,
this over-reads the first buffer. Read-only and only reachable with reorder + buffer log both on.
Fix: gather via `GatherWsabufPayload(buffers, bufferCount, tmp, payloadLength)` (already used on
the send side) instead of pointing at `buffers[0]`.
Verifiable: Windows only.

### [Low][Med] Pending-IO maps can accumulate stale entries with dangling buffer pointers — src/patches/net_optimizer.cpp:2779; src/patches/bzrnet_instrumentation.cpp:478

```cpp
        g_PendingCaptureIo[overlapped] = std::move(pending);
```
Both capture layers remember the game's `WSABUF` array and `from`/`fromLen` pointers keyed by the
`OVERLAPPED*` and consume them from `GetQueuedCompletionStatus` or a wrapped completion routine.
Completions retrieved by any other route (`WSAGetOverlappedResult`, event-based waits,
`GetQueuedCompletionStatusEx` — none are hooked; `grep` finds no `GetQueuedCompletionStatusEx`
hook) leave the entry in the map. If the OVERLAPPED memory is later freed and a different
completion is posted at the same address, `CaptureCompletedIo` (2830) / `CapturePending` (502)
read through the stale WSABUF pointers. Only reachable with relay capture / BZRNet trace on.
Fix: bound the maps (drop the oldest entry beyond N, or evict entries older than a few seconds
in the completion hook) and re-validate `pending.socket` is still tracked before gathering.
Verifiable: Windows only.

### [Low][High] `ShutdownBzrNetTrace` can wait forever on a producer-fed queue — src/patches/bzrnet_trace.cpp:394

```cpp
            wait = WaitForSingleObject(g_WriterThread, INFINITE);
```
The writer exits only when `stopping && empty` (219-221), but producers stay enabled until
`g_Initialized` is cleared at the very end (428). If the exit path (`HookExit`,
`bzrnet_instrumentation.cpp:717`) runs while other game threads are still sending on a traced
UDP socket with `allUdp`, the queue can be refilled indefinitely. The comment says "bounded queue
drain" but nothing bounds the number of drain rounds.
Fix: clear `g_Initialized` (or a separate `g_AcceptingRecords` flag) before signalling `g_Stop`
so producers drop immediately, then wait; keep the 5 s first wait and make the second one bounded
(e.g. 30 s) with the existing unclean-shutdown fallback.
Verifiable: Windows only.

### [Low][High] `mp_ready` explainer replaces a localized string with English-only text and patches with no version gate beyond byte guards — src/patches/mp_ready_diagnostic.cpp:534-573

Documented and deliberate, so not a defect, but note for maintainers: `InstallExplainer` applies
two code patches (getter JMP5 at `0x00753810`, REL32 at `0x0078EC38`) from a worker thread 3 s
after startup, outside `RunPatcher`, with `PatchType::REL32` but without a `patches.json` entry
(see the maintainability finding above). The byte guards make it fail closed on other builds.
Fix: none required; fold into the patcher registration when the addresses move to `patches.json`.

## Dead or unused code (list with evidence)

- `ApplyNetcodeHooks()` and all of `src/patches/netcode_hooks.cpp` (18 lines): no callers
  (`grep -rn ApplyNetcodeHooks src include tests` hits only its own definition and header).
  `include/netcode_hooks.h` survives only for `DEFAULT_SEND_BUFFER` / `DEFAULT_RECV_BUFFER`,
  used at `net_optimizer.cpp:224-225`, `:825-833`, `:1224-1225`. Move those two constants into
  `net_optimizer.cpp`, delete both files and their `Plugin_OpenShim.vcxproj:160` /
  `BZROpenShim.vcxproj:219` entries.
- `BzrNetTraceSocketGeneration()` (`bzrnet_trace.cpp:464`), `GetBzrNetCaptureId()` (`:441`),
  `IsBzrNetPrivateForensicTrace()` (`:436`): declared in `include/bzrnet_trace.h`, no callers
  outside their definitions.
- `SanitizeBzrNetIdentity()` (`bzrnet_protocol.cpp:213`): referenced only by
  `tests/bzrnet_protocol_tests.cpp`; production callers use `SanitizeBzrNetJson`/`SanitizeBzrNetEndpoint`.
- `kBufferLogEventWSARecvCompletion = 7` (`net_optimizer.cpp:206`): declared and advertised in
  the `.meta.txt` event list (1522) but never emitted; `CaptureCompletedIo` only emits event 8.
- `err == WSA_IO_PENDING || err == ERROR_IO_PENDING` (`net_optimizer.cpp:3700`): both are 997;
  one term is redundant.
- Duplicated helpers (copy-paste, should be shared or moved into the Linux-testable
  `bzrnet_protocol.cpp`): the WebSocket frame parser exists twice
  (`net_optimizer.cpp:1903-2032 ProcessWebSocketDirection` and
  `bzrnet_instrumentation.cpp:395-454 ProcessWsDirection`, byte-for-byte the same algorithm), as do
  `FindHttpHeaderEnd`/`HeaderEnd`, `GatherWsabufPayload`/`Gather`, `GetRequestedWsabufBytes`/`Requested`,
  `FormatSockaddr`/`EndpointOf`, `IsUdpSocket` (two implementations with different lookup
  strategies), `GetGameDir`/`GameDir`/`GameDirectory` (three), `JoinPath` (two), and `JsonEscape`
  (`bzrnet_trace.cpp:66` emits `\u00xx`, `bzrnet_instrumentation.cpp:260` emits `?` for the same
  control bytes). The two env parsers also disagree: `EnvValueEnabled` (`net_optimizer.cpp:540`)
  treats anything but `0/false/no/off` as on, `EnvBool` (`bzrnet_instrumentation.cpp:123`) treats
  only `1/true/yes/on` as on, so `BZ_RELAY_CAPTURE=2` enables the optimizer capture but not the
  structured trace.

## Performance notes

- `LogPacketActivity` (`net_optimizer.cpp:2110-2170`) runs on every successful
  send/recv/sendto/recvfrom/WSASendTo/WSARecvFrom. Before the sampling check at 2154 it takes
  `g_SocketLock` exclusively, formats the peer with `InetNtopA` into a `std::string`, copies the
  full `SocketState` (three `std::string`s), calls `RefreshSocketAddresses` (2148: `getsockname` +
  `getpeername` syscalls, two more `FormatSockaddr`, another exclusive lock) and `LookupSocket`
  (another three-string copy). For the default `PacketLogInterval=128` this is wasted for 127 of
  128 packets, and it still runs when `EnableLogging=0` because only the final `Logf` checks
  `g_Config.logging`. Hoist `if (!g_Config.logging || !g_Config.logSocketPackets) return;` to the
  top, and only call `RefreshSocketAddresses`/`FormatSockaddr` after `IsPacketLogSample` passes
  (the counters can be bumped under the lock without copying the state).
- `LogRouteEvent` (2217-2274) repeats the same pattern on every `sendto`/`WSASendTo`:
  `RefreshSocketAddresses` at 2222 and again at 2250, `FormatSockaddr`, a `routeKey` string
  build, and `RememberRouteKey` (exclusive lock + string compare/assign + full state copy),
  all before the `IsPacketLogSample` check at 2246. Net cost per UDP datagram sent: roughly four
  syscalls and ten heap allocations at the default settings. Same fix: sample first.
- `EnsureSocketOptions` (3659-3665) is the first statement of every hook and does
  `LookupSocket(s, state)` which copies a `SocketState` including three `std::string`s (1677)
  just to test `state.optimized`. Add a lock-only `IsSocketOptimized(SOCKET)` that returns the
  flag without copying; keep the copying path for the one-time optimize branch.
- `Hook_WSASendTo` (3967-3970) zero-initialises a 1500-byte `dupData` array and gathers the
  whole payload into it on every successful send even though `DupEnqueue` (3040) immediately
  returns when `sendDup` is false (the shipped default). Test `g_Config.sendDup` before
  gathering. `IsUdpSocket(s)` is also evaluated twice per call (3945, 3947).
- Reorder path (experimental): `LogReorderf` (26 call sites) writes to the shim log while
  `g_ReorderLock` is held in `InsertPacketLocked`/`TryDeliverBufferedPacket`/`FindOrCreatePeerBufLocked`,
  and `SocketHasQueuedReceiveData` logs on every drain iteration; with `LogPacketReorder=1`
  (the shipped default in `net.ini`) enabling reorder means one `FIONREAD` ioctl plus one log line
  per drained datagram. Move the log calls outside the lock and sample them.
- `bzrnet_instrumentation.cpp`: `IsWsSocket` (`getpeername`) runs on every `send`/`recv`/
  `WSASend`/`WSARecv` while the trace is on (opt-in only, acceptable), and `TraceWire` builds a
  hex string of the full payload (up to 65507*2 bytes) per datagram under `fullNetworkCapture`.
  Consider caching the WS classification per socket in `g_Sockets` at first sight.
- `NetGlobalsPatchThread` / `GovernorPatchThread` poll ten dwords every 100 ms for the process
  lifetime; negligible, and the aligned 32-bit stores are atomic as the comment says.

## Positive notes (things done well that later work should keep doing)

- Every attacker-facing parser checks length before reading: WebSocket framing (2 / 4 / 10 byte
  headers, mask, 1 MiB cap, fragment cap, 64 KiB pre-handshake cap), `DecodeBzrUdpControl`
  (`length >= 22/14/10` guards), reorder sequence (`packetLength < 17` bypass before the offset-13
  read), `TryGetSockaddrPort`/`TryGetSockaddrIpv4HostOrder` (family + length checks),
  `CopyPacketToCaller` (`min(*fromLen, sizeof)`), `ScatterCopy`/`GatherWsabufPayload` (bounded by
  both sides). `BufferLogEvent` clamps payload to the configured stride, so the ring can never be
  overrun by an attacker-chosen datagram size.
- Build-specific writes are gated twice: the governor/net-globals threads require exactly one
  match of the 15-byte signature and then veto each global whose live value is implausible;
  `mp_faction_restrict` requires both named call sites to resolve to the same loader and
  byte-checks the derived `clear` body; `mp_ready_diagnostic` byte-guards every instruction that
  names a global and stands down entirely on mismatch. Nothing writes `.text` on Steam-protected
  pages (the DRM-safe `.data` approach is documented in-line).
- No simulation-affecting mutation anywhere in scope: governor rate, `[Net]` tunables, auto-kick,
  DSCP, socket buffers and reorder/dup are all transport-side; faction pruning is local UI state
  and documented as such. No desync vector identified.
- `ws2_32.dll` stays delay-loaded (`Plugin_OpenShim.vcxproj:83`, `BZROpenShim.vcxproj:84`);
  `LoadWinsockExports` resolves every hooked export by `GetProcAddress` and refuses to install if
  any is missing, and the observation layer chains through whatever the IAT already held rather
  than assuming the raw export.
- WSA error preservation is done correctly in most hooks (`Hook_send`, `Hook_recv`, `Hook_connect`,
  `Hook_WSAConnect`, `Hook_bind`, `Hook_WSASend`, `Hook_WSARecv`, `Hook_ioctlsocket`,
  `Hook_WSAIoctl`, `Hook_GetQueuedCompletionStatus`), which is why the two missing restores stand out.
- Shutdown discipline: workers are joined with a bounded wait and shared buffers are leaked rather
  than freed under a live thread; the wake sender is closed only after its owning thread is
  joined; `RecycleBzrNetWebSocket` re-checks socket identity under the table lock before closing
  a handle the game owns. `HookExit` moves capture teardown out of `DLL_PROCESS_DETACH`.
- The baseline script (`tools/validate-network-baseline.ps1`) pins the dangerous defaults with
  regexes that match the current source exactly; `bzrnet_protocol.cpp` is engine-independent and
  has a real Linux test.
- SEH-guarded reads in the diagnostics keep `__try` frames free of unwindable objects (C2712),
  and `mp_vehicle_preview_fix` only writes a material scheme after reading back a recognised
  scheme name, which doubles as an identity check on the viewport pointer.
