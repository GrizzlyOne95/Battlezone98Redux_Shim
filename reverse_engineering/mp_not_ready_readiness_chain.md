# Main menu "Not Ready" multiplayer entry — readiness chain — 2026-09-08

## Verdict

The multiplayer button's `Not Ready` caption carries **no reason by design flaw,
not by omission**: the shell has code to explain two specific causes, but the
getter feeding it can never return either code. Every distinct root cause —
platform sign-in, service transport, Authorization rejection — collapses into
one indistinguishable bit before it reaches the UI.

That is why unrelated-sounding triggers (an unusual platform username, IPv6 on
the adapter) all present as the same symptom with nothing in the log.

## Where the caption is written

`FUN_0078EB50` is the main menu's per-frame multiplayer-entry refresh, tail-called
by the menu update `FUN_0078E8F0`. Decompiled:

```c
if (screen->mpButton && screen->mpTooltip) {
    friends = GetNetFriends();                 // 0x007647A0 -> [0x00945474]
    code    = friends->vtbl[0x20]();           // readiness code
    SetTooltip(screen->mpTooltip, "");
    if (code == 3) {
        SetButtonLabel(Localize(<default>, "multi_player"));   // 0x007C2950
        SetButtonEnabled(1);                                   // 0x007C3040
    } else {
        SetButtonLabel(Localize("multi_common", "not ready"));
        SetButtonEnabled(0);
        if (code == 1) SetTooltip(Localize("multi_message", "no inet"));
        else if (code == 2) SetTooltip(Localize("multi_message", "no auth"));
    }
}
```

`0x007C2950` is independently confirmed as the button-label setter: OpenShim
already binds it as `g_BzrFn_SetButtonLabel`, and
[`bzrnet_live_nickname_qualification_20260904.md`](bzrnet_live_nickname_qualification_20260904.md)
records two crashes inside it. `bzr_options_ui.cpp` separately notes that this
caption is "live status text, rewritten by the shell after the page opens",
which matches the per-frame call site.

## Why the tooltips are dead code

Vtable slot `+0x20` resolves to **`FUN_00753810` in all three vtables** —
`cNetFriends` (`0x0089B474`), `cNetFriendsGog` (`0x0089B4C8`) and
`cNetFriendsSteam` (`0x0089B6E8`). It is not overridden, so there is exactly
one implementation:

```c
undefined4 __fastcall GetReadyState(void *this) {
    if (PlatformReady() && GetBzrNetLobby()) return 3;
    return 0;
}
```

It returns **only 3 or 0**. Codes 1 (`no inet`) and 2 (`no auth`) are
unreachable, so both tooltip branches in `FUN_0078EB50` are dead and the player
receives a bare `Not Ready`.

## The full chain

| Term | Address | Test |
|---|---|---|
| `GetReadyState` | `0x00753810` | `PlatformReady() && GetBzrNetLobby() ? 3 : 0` |
| `PlatformReady` | `0x00764870` | switch on mode, below |
| `SteamOk` | `0x007647F0` | `movzx eax, byte [0x00945463]` — the `SteamAPI_Init()` result |
| `GalaxyOk` | `0x00764810` | `[0x00945490] != 0 && *(int*)(galaxy+8) >= 3` |
| `BzrNetAuthOk` | `0x00764840` | `[0x00945484] != 0 && *(int*)(client+4) == 3` |
| `GetBzrNetLobby` | `0x00764760` | `return [0x00945470]` |

Platform mode is `[0x008F0470]`, set once in `FUN_00764D80`:

| Mode | Requirement |
|---|---|
| 1 (Steam) | `SteamOk` |
| 2 (GOG) | `GalaxyOk` |
| 3 (Steam+GOG) | `GalaxyOk && SteamOk` |
| 4 (auto — **shipped default**) | `(SteamOk \|\| GalaxyOk) && BzrNetAuthOk` |

`FUN_00764D80` defaults the mode to 4 and only leaves it elsewhere when
`[0x0094546C]` overrides it and validates.

`[0x00945484]` and `[0x00945470]` are already identified in OpenShim's own
`bzr_hooks.cpp`: the former holds the address of the BZRNet client's
`shared_ptr` (client is its first dword), the latter is the `BZRNetLobby`
published on construction (vftable `0x0089ADDC`) and zeroed on teardown.

## Why this explains both reported triggers

On a default install the deciding term is `BzrNetAuthOk` — the BZRNet websocket
client reaching state 3. The client's state at `+4` is therefore the single
most diagnostic value in the process:

| State | Meaning | Implicated |
|---|---|---|
| 0 / 1 | never reached the service | transport — DNS, firewall, or an IPv6 route the service does not answer on |
| 2 | connected, never authorized | the `Authorization` body was refused |
| 3 | authorized | ready |

The `Authorization` message is the one place the player's platform name is sent
(`SendAuthorization` `0x006C6DF0`, name sourced from the buffer at
`0x009453E0`), and it is sent exactly once per connection. A name the service
rejects therefore parks the client at state 2 forever, while a transport
failure parks it at 0/1 — **the state value discriminates between the two
hypotheses directly**, which is what the diagnostic below exists to capture.

Neither hypothesis is confirmed here. This document establishes the mechanism
and the observable; it does not claim a cause.

## What was added

`src/patches/mp_ready_diagnostic.cpp` recomputes the chain above from the same
globals and logs one `[MPREADY]` line per state change, naming the failing
term. It patches nothing. Each of the nine addresses is byte-guarded against
the instruction that references its global, verified against
GOG/Redux 2.2.301 (`0x00764760` matches the guard `bzr_hooks.cpp` already
relies on), and any mismatch stands the diagnostic down rather than reporting a
value it cannot vouch for. Default on;
`[Diagnostics] LogMultiplayerReadiness=0` or
`OPENSHIM_NO_MP_READY_DIAGNOSTIC` disables it.

Sample line:

```
[MPREADY] code=0 button="Not Ready" mode=4(auto) steam-api=ok galaxy=absent(state=0)
          bzrnet-client=present(state=2:connected-unauthorized) bzrnet-lobby=null
          blocked-by=bzrnet-authorization,bzrnet-lobby-absent
[MPREADY] Authorization name shape: len=31 non-ascii=6 control=0 unterminated=no
```

The name is reported as a shape (length, non-ASCII count, control count) rather
than as text, so a session log stays shareable.

## If a patch is wanted later

Two independent options, in order of cost:

1. **Report the reason in the UI.** The tooltip strings and both branches
   already exist in `FUN_0078EB50`; they only need a getter that returns 1 and
   2. Hooking `0x00753810` to return 1 for a transport failure and 2 for an
   authorization failure revives the stock UI path with no new assets or
   localization work. This is a display fix only.
2. **Address a confirmed cause** — only after the diagnostic identifies one.
   A name the service rejects would be handled in the Authorization body; an
   IPv6 route would be handled at the websocket connect. Do not pre-empt this:
   the log has to say which first.
