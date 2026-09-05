# BZRNet nickname: why re-auth, and what is actually proven — 2026-09-05

Companion to [`bzrnet_live_nickname_qualification_20260904.md`](bzrnet_live_nickname_qualification_20260904.md).
That document records the failed run; this one records the static finding that
explains it and the design that follows from it.

Written because these findings existed only in the commit message of
`agent/live-nickname-force-lounge` (`d622bb3e`). A PR description is not a
durable home for reverse-engineering results.

## The static finding

The fixed nickname buffer at `0x009453E0` is read at exactly one point: while
the Authorization body is being built.

```
0x006C7D84  -->  0x006C6E60  -->  0x006C83F0
                                  reads 0x009453E0
```

It is process state consumed at connect time, not a live remote-player record.
Writing it after the connection is established therefore cannot, on its own,
change what any peer or observer sees. Nothing re-reads it until the next
Authorization.

This is what makes the 09-04 result unsurprising in hindsight: persistence
worked and the restart test passed precisely *because* a restart is what forces
a fresh Authorization.

## What follows for the design

Two consequences, and the second is the whole of this feature:

1. `SetPlayerData("name")` (`0x006C4F70`, thunk `0x0074BF60`) is generic lobby
   metadata. Even on a path that completes, it does not drive a rename.
2. The only mutation reachable in-process that *is* proven to produce a renamed
   identity is a **second Authorization on the existing WebSocket** —
   `SendAuthorization` at `0x006C6DF0`. The same stable Steam/GOG identity
   re-appears carrying the new name, without restarting the process.

So the feature queues a re-auth rather than sending player data.

## Boundaries, and why they are where they are

- **Lounge/lobby only.** Requires `ValidateBzrNetLobbyState` to pass and
  `netId == 0`. In-match re-auth is not attempted: renegotiating identity while
  a match session is live has effects on the session that have not been
  measured.
- **Opt-in, default off.** `[Network] ReauthOnNicknameChange = 0`. The absent-key
  default is also `false`, so the shipped ini and the code agree.
- **In-match or no lobby** reports `LiveSendUnavailable` — "saved; live update
  unavailable until reconnect/rejoin". No automatic reconnect ever happens.

## One claim deliberately not made

`d622bb3e`'s commit message states that `SetPlayerData("name")` "completes on
the wire but Rebellion ignores the post-auth mutation."

**The qualification run does not support the first half of that.** Its own
failure localization is explicit:

> Existing socket logging did not prove that a corresponding logical BZRNet
> request left the process, so this run cannot distinguish "native method did
> not enqueue/transmit the expected request" from "Rebellion accepted the
> request transport but ignored the post-authorization `name` mutation."

What is established is narrower, and sufficient: **no observer saw a rename from
that path.** Whether the request reached the service is still open.

The distinction does not change the design — the static finding above justifies
re-auth on its own — but it does change what we may write down. The code
comments and ini documentation state the narrow version.

The `SetPlayerData` machinery is therefore retained in `bzr_hooks.cpp` though no
longer called: settling the open question needs exactly that ABI. It costs a
C4505 on an unreferenced static, as several other retained probes in that file
already do.

## Still owed

- The narrowly scoped send/queue-boundary diagnostic (qualification
  recommendation 3), which would close the question above.
- Observer-proven re-auth stability across Steam, GOG and Galaxy before this
  key could reasonably default on. The 09-04 run never reached a positive GOG
  control — Galaxy's communication service failed and Galaxy shut itself down.
- The lobby nickname controls' visibility (recommendation 5) is unrelated to
  this work and still unfixed.
