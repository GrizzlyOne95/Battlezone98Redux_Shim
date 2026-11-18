# Scope: Discord Rich Presence in BZR-OpenShim

Native Discord Rich Presence (RPC) integration for Battlezone 98 Redux, surfacing live match state, campaign/mission names, planet environments, player vehicles, factions, multiplayer player counts, and elapsed mission timers.

---

## 1. Executive Summary & Architectural Decisions

1. **Lightweight Win32 Named Pipe Client (Zero Third-Party DLLs)**:
   - The integration communicates directly with Discord Desktop via its local named pipe (`\\.\pipe\discord-ipc-0` through `\\.\pipe\discord-ipc-9`).
   - **No Discord GameSDK or `discord-rpc.dll`**: Distributing a 32-bit external SDK DLL violates OpenShim's architecture guardrail (*"System DLLs remain delay-loaded. Preserve ownership and lifetime boundaries"*). The official Discord GameSDK is heavy and largely deprecated, while the old `discord-rpc` library was archived and was itself only a small wrapper around this exact named pipe.
   - Standard Win32 calls (`CreateFileA`, `ReadFile`, `WriteFile`, `CloseHandle`) live in `kernel32.dll`, which is already loaded by the process.

2. **Native Linux / Steam Deck / Proton / Wine Compatibility**:
   - Under Proton and modern Wine, Windows games opening `\\.\pipe\discord-ipc-*` have their requests automatically bridged by Wine's named-pipe subsystem to the Linux host's Unix domain socket (`$XDG_RUNTIME_DIR/discord-ipc-0` or `/tmp/discord-ipc-0`).
   - A standard Win32 named pipe client therefore works seamlessly across Windows 10/11 and Linux/Proton without requiring platform-specific branching or Unix sockets.

3. **Asynchronous & Fail-Closed**:
   - The Discord IPC client operates on an independent background worker thread (`discord_rpc_worker`).
   - If Discord is not running (`CreateFileA` fails with `ERROR_FILE_NOT_FOUND`), the worker sleeps and backs off with a quiet periodic retry timer (e.g. 15 seconds).
   - Discord connection drops, malformed responses, or closed pipes never block the engine render thread, simulation loop, or frame rate, and emit no user-facing error dialogues.

---

## 2. Engine Data Sources & Mapping

Battlezone 98 Redux exposes all relevant match and player state through globals and accessor thunks already mapped or resolvable in OpenShim:

| Presence Field | Engine Source | Mechanism & Resolves | Notes |
| :--- | :--- | :--- | :--- |
| **Run State** *(Menu / Sim)* | `TryReadBzrRunState()` / `BzrSetRunningHook` | `SetShellState` / `RunStateNameTable` rows in `src/patches/lifecycle_seams.cpp`. | State 5 (`kBzrRunStateStarted`) indicates active simulation; state changes trigger immediate RPC refreshes. |
| **Pause State** | `IsPauseMenuOpen()`, `IsSingleplayerPauseMenuOpen()` | Probes `MultiplayerPauseFlag`, `MultiplayerPauseRoot`, `SingleplayerPauseRoot`, `UiWrapperActive` (`include/game_state.h`). | Appends `"(Paused)"` to the state string or details when open. |
| **Loading State** | `ReadShellUiState()` | Checks `UiCurrentScreenType == kScreenTypeLoading` (`0x17`). | Reports `"Loading Mission..."`. |
| **Session Mode** *(SP vs MP)* | `IsSinglePlayerSession()` | `ReadLocalPlayerNetIdValue() == 0` (`src/patches/game_object_helpers.cpp`). | `netId == 0` is single player; `netId != 0` is multiplayer. |
| **Mission / Map Path** | `QueuedLoadPathBuffer` (`0x00945708`), `0x00915540`, `BznLoadTraceOnOpen` | `QueuedLoadPathBuffer` in `scripts/patches.json`; `BznLoadTraceOnOpen` in `include/bzn_load_trace.h`. | Captures active `.bzn` filename (e.g. `misn01.bzn`, `scav01.bzn`, `canyon.bzn`). |
| **World / Planet** | `PlanetEnvironment::LastTerrainWorldCode()` | World code extracted from terrain atlas in `src/patches/planet_environment.cpp`. | Maps two-letter codes (`ma` -> Mars, `mn` -> Moon, `ve` -> Venus, `io` -> Io, `eu` -> Europa, `ti` -> Titan, `ga` -> Ganymede, `ac` -> Achilles, `el` -> Elysium). |
| **Player Vehicle** | `g_BzrFn_GetPlayerHandle()`, `TryGetCraftOdfName()` | `GetPlayerHandle` -> `GameObjectFromHandle` -> `TryGetCraftOdfName` (`src/patches/odf_helpers.cpp`). | Resolves player craft object and ODF (e.g. `ivtank` -> *"Grizzly Tank"*, `svscav` -> *"Scavenger"*, `bvtank` -> *"Thunderhead"*, `ispilo` -> *"Pilot (On Foot)"*). |
| **Player Faction** | ODF prefix & `ObjectLayout::kGameObjectActualTeam` | ODF prefix check (`iv*` = NSDF, `sv*` = CCA / Soviet, `bv*` = Black Dogs, `cv*` = CRA / Chinese) and team offset `+0x174`. | Displays faction name and selects faction badge asset. |
| **Elapsed Time** | `g_BzrFn_GetGameTime()` & transition timestamp | `FnGetGameTime` (`0x00822D60`) or wall-clock anchor at `BzrSetRunningHook`. | Supplies Unix epoch start timestamp for Discord's native elapsed timer display. |
| **Multiplayer Party Size** | `P2PAdaptiveRetry::NextPlayer` | Peer map iteration (`0x00577B50`, `src/patches/lobby_drop_keeps_match.cpp`). | Counts active peers for `party.size: [current_players, max_players]`. |

---

## 3. Presence Visual Layouts

### A. Singleplayer Campaign
- **State**: `Piloting Grizzly Tank (NSDF)` *(or `Piloting Czar Heavy Tank (CCA)`)*
- **Details**: `Campaign: Mars - Mission 01` *(or friendly title parsed from `.des`)*
- **Elapsed Time**: `12:45 elapsed`
- **Large Image**: `planet_mars` (Hover: `Mars`)
- **Small Image**: `faction_nsdf` (Hover: `NSDF`)

### B. Singleplayer Instant Action
- **State**: `Piloting Bobcat Scout (NSDF)`
- **Details**: `Instant Action: Dune (Mars)`
- **Elapsed Time**: `05:20 elapsed`
- **Large Image**: `planet_mars` (Hover: `Mars`)
- **Small Image**: `faction_nsdf` (Hover: `NSDF`)

### C. Multiplayer Match
- **State**: `Piloting Thunderhead (Black Dogs)`
- **Details**: `Strategy - Death Valley (Host)` *(or `(Guest)`)*
- **Party**: `(4 of 8 Players)`
- **Elapsed Time**: `18:10 elapsed`
- **Large Image**: `planet_moon` (Hover: `The Moon`)
- **Small Image**: `faction_blackdogs` (Hover: `Black Dogs`)

### D. Main Menu / Pre-Game Shell
- **State**: `In Menus`
- **Details**: `Battlezone 98 Redux`
- **Large Image**: `bzr_main` (Hover: `Battlezone 98 Redux`)

---

## 4. Discord IPC Wire Protocol

Communication with Discord takes place over `\\\\.\\pipe\\discord-ipc-0` (falling back up to `discord-ipc-9`).

### Packet Header
Every frame begins with an 8-byte little-endian header:
```cpp
#pragma pack(push, 1)
struct DiscordIpcHeader
{
    uint32_t opcode; // 0 = HANDSHAKE, 1 = FRAME, 2 = CLOSE, 3 = PING, 4 = PONG
    uint32_t length; // Length of JSON payload in bytes
};
#pragma pack(pop)
```

### Handshake (Opcode 0)
Sent immediately upon connecting:
```json
{
  "v": 1,
  "client_id": "<APPLICATION_ID>"
}
```
Discord replies with an Opcode 1 `READY` dispatch containing user/app details.

### Activity Update (Opcode 1)
Sent every 5–10 seconds or on state change:
```json
{
  "cmd": "SET_ACTIVITY",
  "args": {
    "pid": 12345,
    "activity": {
      "state": "Piloting Grizzly Tank (NSDF)",
      "details": "Campaign: Mars - Welcome to Mars",
      "timestamps": {
        "start": 1700000000
      },
      "assets": {
        "large_image": "planet_mars",
        "large_text": "Mars",
        "small_image": "faction_nsdf",
        "small_text": "NSDF"
      },
      "party": {
        "id": "match_session_id",
        "size": [4, 8]
      }
    }
  },
  "nonce": "1"
}
```

---

## 5. Configuration & INI Settings (`openshim.ini`)

A new `[Discord]` section allows players to disable presence or selectively hide vehicle, mission, or time details:

```ini
[Discord]
Enabled = 1                            ; 1 = enable Discord Rich Presence, 0 = disabled
ApplicationId = 123456789012345678     ; Discord Application Client ID
ShowVehicle = 1                        ; 1 = show current craft/vehicle name, 0 = hide
ShowMission = 1                        ; 1 = show mission/map name, 0 = generic "In Game"
ShowTime = 1                           ; 1 = display elapsed mission timer, 0 = hide
ShowParty = 1                          ; 1 = display player count in multiplayer
```

---

## 6. Implementation Plan & Work Breakdown

### Phase 1: IPC Transport & Background Worker
- Implement `src/engine/discord_ipc.cpp` and `include/discord_ipc.h`.
- Worker thread lifecycle: non-blocking pipe connection, exponential backoff on disconnect, and clean pipe teardown.
- Lightweight, zero-allocation JSON formatting for the handshake and activity payloads.

### Phase 2: Game State Sampler & Friendly Mapping
- Implement `src/patches/discord_presence.cpp`.
- Read and sanitize engine globals:
  - `BzrRunState` & `IsPauseMenuOpen`
  - `QueuedLoadPathBuffer` & `PlanetEnvironment::LastTerrainWorldCode`
  - Player craft resolution via `GetPlayerHandle` -> `GameObjectFromHandle` -> `TryGetCraftOdfName`
  - Peer count via `NextPlayer` walk
- Provide clean name translation tables for stock missions (`misn01` -> *"Welcome to Mars"*, `scav01` -> *"A Little Scrap"*), stock vehicles (`ivtank` -> *"Grizzly Tank"*, `ivscout` -> *"Bobcat Scout"*), and planets (`ma` -> *"Mars"*).

### Phase 3: Lifecycle Integration
- Hook `BzrSetRunningHook` in `src/patches/lifecycle_seams.cpp`:
  - Mission entered (`previous != kBzrRunStateStarted && current == kBzrRunStateStarted`): signal worker, anchor start timestamp, trigger immediate RPC frame.
  - Mission exited (`previous == kBzrRunStateStarted && current != kBzrRunStateStarted`): signal worker, switch activity back to `"In Menus"`.
- Clean shutdown in `src/dllmain.cpp` on `DLL_PROCESS_DETACH`.

### Phase 4: Discord Developer Portal Assets
- Register the Battlezone 98 Redux community application ID on the Discord Developer Portal.
- Upload standard image assets:
  - Default: `bzr_main` (app logo)
  - Planets: `planet_mars`, `planet_moon`, `planet_venus`, `planet_io`, `planet_europa`, `planet_titan`, `planet_ganymede`, `planet_achilles`, `planet_elysium`, `planet_earth`
  - Factions: `faction_nsdf`, `faction_cca`, `faction_blackdogs`, `faction_chinese`

### Phase 5: Test & Qualification Matrix
1. **Windows 10/11 (GOG & Steam)**:
   - Validate live activity updates in single player campaign, Instant Action, and multiplayer lobby/match.
   - Verify quiet fail-closed behavior when Discord Desktop is not launched.
2. **Linux / Steam Deck / Proton**:
   - Verify Wine named-pipe bridging to host Discord socket.
3. **Edge Cases**:
   - Mission pause / unpause toggling `(Paused)`.
   - In-game vehicle switching (e.g. ejecting to pilot, hopping into scavenger/turret).
   - Instant restart / mission quit / mission failure transitions.
