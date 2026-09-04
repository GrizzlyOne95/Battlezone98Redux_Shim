# Live BZRNet nickname qualification — 2026-09-04

## Verdict

**FAILED — the current implementation is not qualified for live nickname updates.**

On Steam Redux 2.2.301, both `/nickname` and `/name` reached OpenShim's authoritative operation with `LiveNicknameKeys=1` and `ReauthOnNicknameChange=0`. The native `BZRNetLobby::SetPlayerData("name", value)` call returned and OpenShim logged `applied-live`, but neither a direct Rebellion WebSocket observer nor BZ1 GameWatcher observed an in-place rename. Each in-match attempt then crashed the game in the stale lobby route-label refresh path.

Persistence is working: after the first crash, restarting the process authenticated the same Steam identity as the persisted nickname, and both independent observers saw it.

## Environment and observers

- Steam and GOG executable version: 2.2.301.
- Deployed OpenShim `winmm.dll` SHA-256: `3EC5E403A03E08F7EA4FEDDB01BEB31F230243CD79D1C0779D2A79F72A430430`.
- Steam live-name configuration: `LiveNicknameKeys=1`, `ReauthOnNicknameChange=0`.
- Primary observer: a read-only connection to the real Rebellion BZRNet WebSocket, authenticated as a web observer. It recorded lobby membership and user identity changes without exposing IP addresses.
- Secondary observer: BZ1 GameWatcher through its Tailscale endpoint. GameWatcher is useful as an independent service view, but it does not consume `OnUserDataChanged`; therefore the direct observer is authoritative for live-update events.
- Stable Steam identity: `S76561198241259700`.

## Evidence

| Test | Store/client | Observer | Start → requested | Change time | Observer result | Reconnect | Result |
|---|---|---|---|---|---|---|---|
| Baseline host lobby | Steam 2.2.301, lobby `1383` | Direct Rebellion observer | `GrizzlyOne95` | Lobby created `2026-09-04 13:36:55Z` | Same stable ID present as `GrizzlyOne95` | No | PASS baseline |
| Native lobby UI | Steam 2.2.301 | Game window plus hook log | `GrizzlyOne95` → not entered | `2026-09-04 13:35:47Z` panel asset creation | Host/client integration hooks installed and panel PNG created, but the nickname panel and controls were not visible in either lobby screen, so the required UI edit/OK flow could not be performed | No | FAIL UI availability |
| `/nickname osq1` in pre-launch lobby chat | Steam 2.2.301, lobby `1383` | Direct observer and local config/log | `GrizzlyOne95` → `osq1` | About `2026-09-04 13:40Z` | Redux displayed the text as ordinary chat; no nickname operation log, config write, or observer change | No | FAIL command availability in lobby |
| `/nickname osq1` in launched match | Steam 2.2.301, lobby `1383` | Direct Rebellion observer | `GrizzlyOne95` → `osq1` | `2026-09-04 13:43:21.380Z` | OpenShim logged persistence at `13:43:21.387Z` and `applied-live` at `13:43:21.389Z`. Observer never showed `osq1`; it removed lobby `1383` at `13:43:24Z` after the process faulted | No rename-time reconnect; process crashed afterward | FAIL |
| Process restart persistence | Steam 2.2.301, default chat lobby `1000` | Direct observer and Tailscale GameWatcher | Persisted `osq1` | New auth visible `2026-09-04 13:45:18Z` | Both observers showed the same stable Steam ID as `osq1` | Process restart occurred | PASS persistence only |
| `/name osq2` alias in launched match | Steam 2.2.301, lobby `1384` | Direct Rebellion observer | `osq1` → `osq2` | `2026-09-04 13:47:03.286Z` | OpenShim logged persistence at `13:47:03.296Z` and `applied-live` at `13:47:03.297Z`. Observer never showed `osq2`; it removed lobby `1384` at `13:47:05Z` after the same fault | No rename-time reconnect; process crashed afterward | FAIL |
| Leave/re-enter and same-process BZRNet reconnect | Steam 2.2.301 | — | — | — | Could not be reached because both accepted in-match rename attempts terminated the process | — | BLOCKED by reproduced crash |
| GOG baseline without Galaxy | GOG 2.2.301 | Game main menu | No BZRNet identity | `2026-09-04 13:50Z` | Multiplayer entry read `Not Ready` | N/A | Expected readiness failure |
| GOG Galaxy recovery attempt | GOG Galaxy client/service | Galaxy UI and game main menu | — | `2026-09-04 13:50–13:51Z` | Galaxy repeatedly reported `Connection to Communication Service was lost and could not be restored` and shut down, including after the Windows service was started. The game remained `Not Ready` | N/A | BLOCKED before BZRNet/nickname testing |

No observer ever showed a temporary duplicate identity. In both Steam live attempts the old name remained attached to the same stable identity until the lobby disappeared with the crash.

## Failure localization

The first four layers are distinguishable as follows:

1. The in-match command parser invoked the authoritative nickname operation for both command spellings.
2. Persistence and the fixed connection-time nickname buffer updated successfully.
3. The guarded native `SetPlayerData("name", value)` call returned without an exception. `applied-live` currently means only that this native call returned; it is not a service acknowledgement.
4. No independent observer saw an update. Existing socket logging did not prove that a corresponding logical BZRNet request left the process, so this run cannot distinguish “native method did not enqueue/transmit the expected request” from “Rebellion accepted the request transport but ignored the post-authorization `name` mutation.”

There is also a separately proven crash after the nickname operation. Both runs faulted at `0x007C2967`, inside the function OpenShim binds as `g_BzrFn_SetButtonLabel` (`0x007C2950`). `HandleCommandHelpBan` logs the nickname result and then calls `NetRouteRefreshHost()` and `NetRouteRefreshClient()` without checking whether the cached lobby route-label widgets survived the transition from the lobby screen into the match. The faulting instruction dereferences the stale button's `+0x144` render-object pointer.

## GOG readiness finding

GOG multiplayer requires a healthy, authenticated Galaxy client/session. With Galaxy absent, `Not Ready` is a platform-authentication readiness state, not evidence about nickname mutation. This machine could not establish the positive control because Galaxy's communication service failed and Galaxy shut itself down; consequently no valid GOG BZRNet nickname test was performed. OpenShim should not bypass this prerequisite.

## Recommendation

Roadmap status: **Active / Open**.

The narrow next patch should:

1. Stop touching cached host/client route-label widgets unless each label is still a live child of its cached parent; clear the cached nickname/readout pointers when their lobby parent is torn down. Apply the same guard to chat-command and `OpenShimSetBZRNetNickname` refreshes. This directly fixes the reproduced crash.
2. Make the local outcome wording truthful: `applied-live`/`Applied live` should mean `live call attempted` until an observer-visible update or protocol acknowledgement exists.
3. Add one narrowly scoped diagnostic around the native SetPlayerData send/queue boundary to prove whether the logical `name` request is actually transmitted. After the crash guard, repeat the test while holding the same identity and lobby.
4. If the request is proven on the wire and Rebellion still leaves the observer name unchanged, then investigate the required server operation or the opt-in reauthorization fallback. Do not enable reauthorization by default without measuring its disconnect, duplication, and lobby-state effects.
5. Repair the lobby nickname controls' visibility before claiming the native UI path; the hooks and generated artwork alone do not satisfy the UI acceptance case.

No broad networking redesign is justified by this run.
