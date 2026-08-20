# Redux Shell / UI Reverse-Engineering Map

**Target corpus:** `reverse_engineering/repo_corpora/bzr_gog_best_effort/`

**Primary binary:** GOG `battlezone98redux.exe` corpus (`battlezone98redux.exe-6777ca`)

**Status:** Binary-grounded RE map. PDB names are used only where corroborated by the GOG decompilation. Runtime ABI details called out as unresolved are not safe SDK contracts yet.

## Executive result

Redux has a real integer-driven shell screen manager. The GOG binary supports the following high-confidence pipeline:

```text
native button callback
        |
        v
request/push screen ID              FUN_007c7930
        |
        v
shell transition/update loop        FUN_007c7820 -> FUN_007c7070
        |
        | reads the back/history target ID
        | releases current active screen
        v
screen factory                      FUN_007c7ad0(this, screenId)
        |
        v
cUI_* constructor
        |
        v
active-screen slot + activation callback
```

Back navigation is a distinct operation:

```text
Back button -> FUN_007c79a0 -> history/pop path
```

This matters for OpenShim. `RequestScreen(id)` and `Back()` should not be represented as the same operation.

The factory is a compiled `switch`, not a dynamic registration table. There is currently no evidence of a native `RegisterScreen(id, constructor)` mechanism that can simply be extended at runtime.

## Corrections to earlier address labels

Two inherited labels were too strong and are corrected here.

### `0x007C7930` is the screen-request seam, not the factory

`FUN_007c7930` marks a transition pending and inserts the requested value into the shell's history/request container. Main-menu and Options callbacks call it with known screen IDs.

The Ghidra prototype is misleading around the implicit object pointer / stack argument. Do **not** expose the decompiler's apparent `__fastcall` signature as an SDK ABI until live/disassembly validation establishes the exact calling convention.

### `0x007C8600` is not a function entry

The function inventory has no `FUN_007c8600`. Address `0x007C8600` lies inside the much larger `FUN_007c7ad0`, which begins at `0x007C7AD0` and contains the screen factory switch.

Any older note calling `0x007C8600` the screen factory should be replaced by `FUN_007c7ad0` / `0x007C7AD0`.

## Native transition loop

`FUN_007c7820` is part of the shell update path. When a transition is pending and rendering/state conditions allow it, it calls `FUN_007c7070`.

`FUN_007c7070` is the decisive transition routine. In the normal transition path it:

1. reads the target ID from the back of the shell history/request container;
2. releases the current active screen if present;
3. clears/updates renderer and UI state;
4. clears the pending-transition byte;
5. invokes `FUN_007c7ad0(targetId)` using the shell manager as the implicit object;
6. stores the returned screen as the new active screen;
7. invokes manager/screen activation callbacks.

Special handling exists for screen ID `0x17` (`cUI_Loading`) and for renderer/game-state transitions, so a public OpenShim navigation API should queue native transitions rather than call arbitrary constructors directly.

## Back/history semantics

`FUN_007c79a0` is the native Back/history-pop seam. `cUI_OptionsParent`'s Back button reaches this path through `FUN_007b60d0 -> FUN_00788060 -> FUN_007c79a0`.

The implementation checks the history/container state, pops when appropriate, and marks a transition pending. It does not simply request MainScreen ID `1`.

**SDK implication:** expose separate operations conceptually equivalent to:

```cpp
RequestShellScreen(screenId);
BackShellScreen();
```

Do not implement Back as `RequestShellScreen(1)`.

## Screen factory

Factory: `FUN_007c7ad0`

Diagnostic string in the binary:

```text
Creating screen of type %d
```

The table below records every explicit case visible in the GOG factory. `Class / role` is marked binary-confirmed where the constructor itself assigns the named `cUI_*::vftable`.

| ID | Allocation | Constructor | Class / role | Confidence / notes |
|---:|---:|---|---|---|
| `0x01` | `0x17C` | `FUN_0078e670` | `cUI_MainScreen` | **Binary confirmed** |
| `0x02` | `0x180` | `FUN_007bf440` | `cUI_SinglePlayer` | **Binary confirmed** |
| `0x03` | `0x1A8` | `FUN_007abee0` | `cUI_OptionsAudio` | **Binary confirmed conditional branch** when `FUN_004344a0()==2` |
| `0x03` | `0x144` | `FUN_007b61a0` | `cUI_OptionsParent` | **Binary confirmed conditional branch** otherwise; this is the current live-validated PC/OpenShim host |
| `0x04` | `0x168` | `FUN_007b6b90` | `cUI_OptionsPlay` | **Binary confirmed** |
| `0x05` | `0x1B0` | `FUN_007af4a0` | `cUI_OptionsGraphics` | **Binary confirmed** |
| `0x06` | `0x1A8` | `FUN_007abee0` | `cUI_OptionsAudio` | **Binary confirmed** |
| `0x07` | `0x164` | `FUN_0078f030` | `cUI_Mission` | **Binary confirmed class**, mission selector variant from factory-supplied string |
| `0x08` | `0x164` | `FUN_0078f030` | `cUI_Mission` | **Binary confirmed class**, alternate mission selector variant |
| `0x09` | `0x164` | `FUN_0078f030` | `cUI_Mission` | **Binary confirmed class**, alternate mission selector variant |
| `0x0A` | — | — | — | No explicit factory case |
| `0x0B` | `0x148` | `FUN_00789030` | `cUI_Esc` | **Binary confirmed conditional branch** when `FUN_00572a70()==0` |
| `0x0B` | `0x1A8` | `FUN_007a4b60` | `cUI_Multiplayer_Status` | **Binary confirmed conditional branch** otherwise |
| `0x0C` | — | — | — | No explicit factory case |
| `0x0D` | — | — | — | No explicit factory case |
| `0x0E` | `0x388` | `FUN_0079ea90` | `cUI_MultiPlayer_Lobby` | **Binary confirmed** |
| `0x0F` | `0x1D8` | `FUN_00796880` | `cUI_Multiplayer_Create` | **Binary confirmed**; factory also sets manager flag at `+0x18` |
| `0x10` | — | — | — | No explicit factory case |
| `0x11` | `0x2F8` | `FUN_007ba6f0` | `cUI_Save` | **Binary confirmed** |
| `0x12` | `0x16C` | `FUN_0078b1f0` | `cUI_Load` | **Binary confirmed** |
| `0x13` | `0x144` | `FUN_00792000` | `cUI_MissionFailed` | **Binary confirmed** |
| `0x14` | `0x160` | `FUN_00793ca0` | `cUI_MissionSuccess` | **Binary confirmed** |
| `0x15` | `0x18C` | `FUN_007b25b0` | `cUI_OptionsInput` | **Binary confirmed** |
| `0x16` | `0x14C` | `FUN_007b5990` | `cUI_OptionsJoystick` | **Binary confirmed** |
| `0x17` | `0x158` | `FUN_0078bba0` | `cUI_Loading` | **Binary confirmed**; factory sets manager flag at `+0x18`; transition loop treats ID specially |
| `0x18` | `0x16C` | `FUN_00790fe0` | `cUI_MissionArchives` | **Binary confirmed class**, factory-supplied campaign/faction string |
| `0x19` | `0x16C` | `FUN_00790fe0` | `cUI_MissionArchives` | **Binary confirmed class**, alternate variant |
| `0x1A` | `0x16C` | `FUN_00790fe0` | `cUI_MissionArchives` | **Binary confirmed class**, alternate variant |
| `0x1B` | `0x158` | `FUN_00789c20` | `cUI_InstantAction` | **Binary confirmed** |
| `0x1C` | `0x160` | `FUN_00794810` | `cUI_Mods` | **Binary confirmed** |
| `0x1D` | `0x144` | `FUN_00787c10` | `cUI_AlertDlgBox` | **Binary confirmed**; excluded from one common post-create branch |
| `0x1E` | `0x144` | `FUN_007a4620` | `cUI_Multiplayer_Refresh` | **Binary confirmed**; constructor immediately participates in Back/history behavior |
| `0x1F` | `0x148` | `FUN_0078a9f0` | `cUI_Invite` | **Binary confirmed** |
| `0x20` | `0x158` | `FUN_00788300` | `cUI_Campaign` | **Binary confirmed** |
| `0x21` | `0x164` | `FUN_0078f030` | `cUI_Mission` | **Binary confirmed class**, additional campaign/faction variant |
| `0x22` | `0x164` | `FUN_0078f030` | `cUI_Mission` | **Binary confirmed class**, additional campaign/faction variant |
| `0x23` | `0x16C` | `FUN_00790fe0` | `cUI_MissionArchives` | **Binary confirmed class**, additional variant |
| `0x24` | `0x16C` | `FUN_00790fe0` | `cUI_MissionArchives` | **Binary confirmed class**, additional variant |
| `0x25` | `0x164` | `FUN_0078f030` | `cUI_Mission` | **Binary confirmed class**; dynamic string/config setup before construction |
| `0x26` | `0x16C` | `FUN_00790fe0` | `cUI_MissionArchives` | **Binary confirmed class**; dynamic string/config setup before construction |
| `0x27` | `0x154` | `FUN_007bc1e0` | `cUI_SaveLoadEdit` | **Binary confirmed**; constructor receives factory context/variant |
| `0x28` | `0x154` | `FUN_007bc1e0` | `cUI_SaveLoadEdit` | **Binary confirmed**; alternate variant |
| `0x29` | `0x15C` | `FUN_007aab70` | `cUI_ObjectSettings` | **Binary confirmed** |
| `0x2A` | `0x16C` | `FUN_007b84b0` | `cUI_PathSettings` | **Binary confirmed** |

### Known stock request IDs from callbacks

The callback chains independently validate important factory IDs:

| Source UI | Callback path | Native request |
|---|---|---:|
| Main: Single Player | `FUN_0078c520 -> FUN_0078c6a0` | `0x02` |
| Main: Multiplayer | `FUN_0078c550 -> FUN_0078c6c0` after network/lobby checks | `0x0E` |
| Main: Options | `FUN_0078c5e0 -> FUN_00788250` | `0x03` |
| Main: Mods | `FUN_0078c640 -> FUN_0078c830` | `0x1C` |
| Options: Play | `FUN_007b6110 -> FUN_007b6180` | `0x04` |
| Options: Graphics | `FUN_007b60f0 -> FUN_007b6140` | `0x05` |
| Options: Audio | `FUN_007b60e0 -> FUN_007b6120` | `0x06` |
| Options: Input | `FUN_007b6100 -> FUN_007b6160` | `0x15` |
| Options: Back | `FUN_007b60d0 -> FUN_00788060` | history pop via `FUN_007c79a0`, **not an ID request** |

## Main screen (`cUI_MainScreen`)

### Construction and lifetime

Screen ID `1` allocates `0x17C` bytes and calls `FUN_0078e670`.

The constructor:

- assigns `cUI_MainScreen::vftable`;
- stores the singleton in `DAT_0094551c` (`0x0094551C` in this GOG build);
- initializes main-screen-specific fields;
- enters setup through `FUN_0078d000` in the normal path.

The class destructor is `FUN_0078eca0` and explicitly clears:

```text
DAT_0094551c = 0
```

The scalar-deleting destructor path `FUN_0078e8c0` invokes that destructor and then `operator_delete` when requested.

**OpenShim lifecycle invariant:** the MainScreen singleton should only be treated as usable while the binary-confirmed singleton is non-null and the resolved child hierarchy validates. Do not retain raw child pointers across a screen transition.

### Main menu hierarchy

`FUN_0078d000` constructs the stock title menu.

The central visual parent is:

```text
MainScreen_Overlay
```

It is created with the 1920x1080 shell presentation and uses `mainCenterPanel.png`. In the current GOG layout, the pointer is stored at MainScreen offset `+0x158`, but an OpenShim resolver should prefer bounded child discovery by exact name rather than expose this offset as an ABI guarantee.

Stock central children include:

```text
SinglePlayer_MainScreen
MultiPlayer_MainScreen
ViewCredits_MainScreen
Replay Intro_MainScreen
MPStatus
VersionString
```

Top-corner / ancillary controls include:

```text
ExitGame_MainScreen
Options_MainScreen
openAchievements
Mods
```

The important integration point is that the stock Single Player, Multiplayer, Credits, and Replay Intro controls are explicitly parented under `MainScreen_Overlay`.

### Main menu callback behavior

The title menu mixes several different action types.

#### Factory-backed shell screens

- Single Player -> screen `0x02`
- Multiplayer -> screen `0x0E`, but only after native network/lobby readiness logic succeeds
- Options -> screen `0x03`
- Mods -> screen `0x1C`

#### In-place/full-screen media overlays

Credits and Replay Intro do **not** request shell screen IDs.

Both create/use a `movie1` child overlay under the existing `cUI_MainScreen` and play:

```text
credits.ogv
intro.ogv
```

This is useful precedent: Redux already allows the MainScreen object to temporarily present a page-like/full-screen child mode without replacing the root shell screen.

#### Platform/service action

Achievements goes through platform/service validation and a dedicated action path rather than the screen factory.

#### Exit action

Exit logs the main-screen exit action, changes game/application state, clears state, and invokes the shell/application shutdown path. It is not a screen transition.

## Options parent (`cUI_OptionsParent`)

The existing OpenShim Native UI work is corroborated by the corpus.

On the normal PC path for factory screen `0x03`, `FUN_007b61a0`:

- assigns `cUI_OptionsParent::vftable`;
- stores singleton `DAT_009455c4` (`0x009455C4`);
- creates exact child `Middle_Overlay`;
- attaches Play / Graphics / Audio / Input buttons beneath that UI hierarchy.

This validates the current `OpenShimUiHost::OptionsParent` strategy.

Note that factory ID `0x03` is conditional in the binary: when `FUN_004344a0()==2`, it constructs `cUI_OptionsAudio` directly instead. The meaning of that mode predicate should remain opaque until separately proven.

## Recommended `OpenShimUiHost::MainMenu`

The corpus now supports adding an **experimental MainMenu host resolver**, but it should use the same defensive principles as OptionsParent.

Recommended resolution strategy:

1. resolve the GOG-build MainScreen singleton (`DAT_0094551c` / `0x0094551C`) through the existing build-gated address/signature mechanism;
2. reject null or obviously invalid singleton pointers;
3. traverse the bounded cUI child vector using the already validated `cUI_View` child-layout logic;
4. find exact child name `MainScreen_Overlay`;
5. optionally fingerprint known stock children before exposing the host;
6. invalidate all OpenShim handles and child pointers when the singleton changes or becomes null.

Do **not** make `+0x158` the public contract even though it is binary-confirmed in this GOG build. Exact-name child discovery is more robust and matches the established Native UI architecture.

Suggested enum extension:

```cpp
enum class OpenShimUiHost : uint32_t {
    OptionsParent = 1,
    MainMenu      = 2,
};
```

This should remain experimental/build-gated until live validation confirms the child-vector traversal and input ordering on MainScreen.

## Career: safest implementation path

### Phase 1 recommendation: native MainScreen-hosted logical surface

Implement the first Career UI as:

```text
stock cUI_MainScreen
    |
    +-- MainScreen_Overlay
            |
            +-- stock main-menu controls
            +-- OpenShim Career button
            +-- OpenShim Career logical surface (hidden by default)
```

On Career click:

1. queue the action through OpenShim's existing safe callback queue;
2. deactivate/hide the stock main-menu interactive controls that would overlap or consume input;
3. show the Career surface's native cUI controls under `MainScreen_Overlay`;
4. give Career an explicit Back control;
5. Back hides/destroys Career controls and restores the stock title controls without destroying `cUI_MainScreen`.

Why this is the preferred first implementation:

- the MainScreen lifetime is now mapped;
- `MainScreen_Overlay` is a binary-confirmed stock parent;
- Redux itself already presents Credits and Intro as in-place child modes of MainScreen;
- no arbitrary root-screen ABI needs to be fabricated;
- no factory switch patch is required;
- stock shell background, focus, and presentation remain intact;
- failure can be isolated to an experimental OpenShim feature flag.

### Phase 2: native shell navigation API for stock IDs

Once ABI/live validation is complete, expose internal/SDK-safe wrappers for the native navigation semantics:

```text
Request stock screen ID
Back/pop shell history
```

Important constraints:

- calls must run/queue on the correct UI/game thread;
- the calling convention/object pointer for `FUN_007c7930` and `FUN_007c79a0` must be resolved from executable signatures/disassembly, not copied from Ghidra's inferred prototype;
- Multiplayer must continue using its stock callback path if native network preconditions are required; blindly requesting `0x0E` bypasses useful checks;
- custom IDs must not be sent to the unmodified stock factory.

### Phase 3: true custom first-class root screen only after more RE

A true custom screen ID remains possible in principle, but is **not** ready for implementation merely because the factory is understood.

The stock factory is a closed switch. To support a custom ID such as `CAREER_ID`, OpenShim would need to intercept the request/factory transition and either:

1. hook `FUN_007c7ad0` and construct a compatible root screen for custom IDs; or
2. intercept before factory dispatch and substitute an OpenShim-owned root-screen lifecycle.

That requires fully validating:

- root `cUI_Parent` / `cUI_View` object layout;
- required vtable slots;
- manager ownership and scalar-deleting destructor semantics;
- activation/deactivation callbacks;
- input dispatch and focus behavior;
- render/update callbacks;
- history behavior when a custom ID is on the native stack;
- what happens when stock code assumes every history ID is handled by the compiled factory.

Until those are proven, adding a custom integer to the native history risks a later Back/forward transition reaching the stock switch and receiving a null screen.

**Decision:** Phase 1 should use the MainScreen host. Do not patch the factory switch yet.

## Proposed OpenShim API split

Keep UI construction and shell navigation separate.

```cpp
// Host discovery / native child controls
OpenShimUiHost::OptionsParent
OpenShimUiHost::MainMenu

// Native stock-shell navigation, once ABI validated
OpenShimRequestShellScreen(uint32_t stockScreenId);
OpenShimBackShellScreen();
```

Do not expose raw Redux constructor addresses or arbitrary screen IDs as a general-purpose public API.

A higher-level future API can name the stable stock pages instead:

```cpp
enum class OpenShimShellScreen {
    MainMenu,
    SinglePlayer,
    Options,
    OptionsPlay,
    OptionsGraphics,
    OptionsAudio,
    OptionsInput,
    MultiplayerLobby,
    Mods,
    // ...only binary/live-validated entries
};
```

The implementation can map this enum to build-specific native IDs.

## Runtime validation checklist before enabling MainMenu host by default

- [ ] MainScreen singleton resolves to the active `cUI_MainScreen` during title-menu display.
- [ ] Singleton becomes null or changes exactly when MainScreen is destroyed/reconstructed.
- [ ] Exact child `MainScreen_Overlay` resolves through bounded child traversal.
- [ ] Known stock child names are present beneath the expected hierarchy.
- [ ] An injected test button receives mouse input without blocking stock buttons.
- [ ] A hidden Career surface does not consume input.
- [ ] Showing Career and disabling stock interactive children produces no double activation.
- [ ] Career Back restores stock controls and focus.
- [ ] Leaving MainScreen while Career is open invalidates OpenShim handles safely.
- [ ] Returning to MainScreen after another stock page reconstructs/re-resolves cleanly.
- [ ] Repeated Main -> Options -> Back -> Career cycles do not retain stale pointers.
- [ ] GOG/Steam build signatures or build gates prevent use of unvalidated absolute addresses.

## Evidence index

Primary GOG decomp files used for this map:

```text
FUN_007c7820-007c7820.c   shell update / pending transition check
FUN_007c7930-007c7930.c   request/push seam
FUN_007c79a0-007c79a0.c   Back/history-pop seam
FUN_007c7070-007c7070.c   shell transition/dispatch loop
FUN_007c7ad0-007c7ad0.c   integer screen factory

FUN_0078e670-0078e670.c   cUI_MainScreen constructor
FUN_0078d000-0078d000.c   main-menu setup/hierarchy
FUN_0078eca0-0078eca0.c   cUI_MainScreen destructor
FUN_0078e8c0-0078e8c0.c   cUI_MainScreen scalar deleting destructor

FUN_007bf440-007bf440.c   cUI_SinglePlayer
FUN_007b61a0-007b61a0.c   cUI_OptionsParent
FUN_007b6b90-007b6b90.c   cUI_OptionsPlay
FUN_007af4a0-007af4a0.c   cUI_OptionsGraphics
FUN_007abee0-007abee0.c   cUI_OptionsAudio
FUN_007b25b0-007b25b0.c   cUI_OptionsInput
FUN_007b5990-007b5990.c   cUI_OptionsJoystick

FUN_0079ea90-0079ea90.c   cUI_MultiPlayer_Lobby
FUN_00796880-00796880.c   cUI_Multiplayer_Create
FUN_007a4b60-007a4b60.c   cUI_Multiplayer_Status
FUN_007a4620-007a4620.c   cUI_Multiplayer_Refresh
FUN_0078a9f0-0078a9f0.c   cUI_Invite

FUN_0078f030-0078f030.c   cUI_Mission
FUN_00790fe0-00790fe0.c   cUI_MissionArchives
FUN_00788300-00788300.c   cUI_Campaign
FUN_00789c20-00789c20.c   cUI_InstantAction
FUN_00794810-00794810.c   cUI_Mods
FUN_007ba6f0-007ba6f0.c   cUI_Save
FUN_0078b1f0-0078b1f0.c   cUI_Load
FUN_007bc1e0-007bc1e0.c   cUI_SaveLoadEdit
FUN_00792000-00792000.c   cUI_MissionFailed
FUN_00793ca0-00793ca0.c   cUI_MissionSuccess
FUN_0078bba0-0078bba0.c   cUI_Loading
FUN_00787c10-00787c10.c   cUI_AlertDlgBox
FUN_007aab70-007aab70.c   cUI_ObjectSettings
FUN_007b84b0-007b84b0.c   cUI_PathSettings
```

PDB reference data remains semantic support only and must not override contradictory GOG binary evidence.
