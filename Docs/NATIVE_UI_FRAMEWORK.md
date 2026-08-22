# OpenShim Native UI Framework

OpenShim Native UI v1 is a small, versioned wrapper around the Redux `cUI` ABI that lets OpenShim consumers create native-looking UI without receiving or dereferencing Redux UI pointers.

It is intentionally conservative. The first public surface wraps only behavior whose constructor, ownership, input ordering, and lifetime have already been exercised by OpenShim's native Options/Input UI work.

The GOG shell reverse-engineering pass now also has a binary-grounded MainScreen/navigation map. See `reverse_engineering/REDUX_SHELL_UI_RE_MAP.md`. That evidence is strong enough to define the intended MainMenu host and shell-navigation architecture, but the MainMenu host remains **not public in Native UI v1 until its child hierarchy/input behavior is live-validated**.

## Goals

- Keep Redux-specific allocation sizes, constructors, callbacks, and ownership inside OpenShim.
- Give consumers opaque handles rather than `cUI_*` pointers.
- Keep Redux responsible for destroying its screen child objects.
- Never call EXU/Lua/consumer callbacks directly from Redux mouse dispatch.
- Make a future `Career`, mod settings, developer tools, custom multiplayer rules, progression, or other menu workflow possible without duplicating the `cUI` reverse engineering in every feature.
- Fail closed when the expected host screen cannot be identified safely.

## SDK discovery

Native UI is exposed as a versioned sub-API of SDK v2:

```cpp
const auto* shim = BZROpenShim::OpenShimGetApi(BZROpenShim::SDK_API_V2);
if (!shim || !(shim->capabilities & BZROpenShim::OPENSHIM_CAP_NATIVE_UI))
    return;

const auto* ui = shim->getNativeUiApi(BZROpenShim::NATIVE_UI_API_V1);
if (!ui || !ui->isAvailable())
    return;
```

`OPENSHIM_CAP_NATIVE_UI` means this build contains the native UI API. `isAvailable()` additionally checks the live compatible-game gate and the required resolved Redux UI bindings.

## Thread/context rule

All native UI creation and mutation calls must run on the foreground Battlezone UI/window thread.

The v1 API rejects mutation from an arbitrary worker thread. This is deliberate: Redux owns the `cUI` tree and its shell/input dispatch, and OpenShim does not marshal UI operations across engine threads.

A companion should therefore perform UI work from a known-safe engine/update or shell callback that runs on the game UI thread.

## Hosts

### `OpenShimUiHost::OptionsParent`

Native UI v1 currently exposes one public host:

```text
cUI_OptionsParent
    |
    `-- Middle_Overlay   <-- validated native-ui parent
```

The host resolver:

1. reads the live Options-parent singleton;
2. validates its bounded child vector;
3. finds the child named `Middle_Overlay`;
4. fails if that exact host cannot be found.

There is intentionally no fallback to another screen child. OpenShim's existing Options work proved that adding children to a full-bleed frame view can alter `cUI_View` mouse-dispatch ordering and starve stock controls such as Back.

### Recovered MainMenu host (binary-confirmed, not public yet)

The GOG corpus now confirms the MainScreen side well enough to define the next host precisely:

```text
cUI_MainScreen                         screen ID 0x01
    singleton DAT_0094551c
    |
    `-- MainScreen_Overlay             intended native-ui parent
            |
            +-- SinglePlayer_MainScreen
            +-- MultiPlayer_MainScreen
            +-- ViewCredits_MainScreen
            +-- Replay Intro_MainScreen
            `-- other stock shell children
```

`FUN_0078e670` constructs `cUI_MainScreen` and stores the singleton in `DAT_0094551c`. `FUN_0078eca0` is the class destructor and explicitly clears that singleton. `FUN_0078d000` constructs `MainScreen_Overlay` and the stock title-menu controls.

For OpenShim, the intended resolver is therefore:

1. resolve the build-gated MainScreen singleton;
2. reject null/invalid state;
3. traverse the bounded cUI child vector;
4. find exact child `MainScreen_Overlay`;
5. optionally fingerprint expected stock children;
6. invalidate handles whenever the singleton/child fingerprint changes.

The current GOG object also stores the overlay at MainScreen offset `+0x158`, but that offset should **not** become a public/native-ui contract. Exact-name child discovery is safer and matches the OptionsParent strategy.

A future enum extension can therefore be:

```cpp
enum class OpenShimUiHost : uint32_t
{
    None          = 0,
    OptionsParent = 1,
    MainMenu      = 2, // only after live acceptance
};
```

Do not expose `MainMenu` from `createSurface()` until the runtime acceptance checks at the end of this document pass.

## Native shell navigation recovered by RE

The title/menu RE pass also separated the native shell operations that were previously conflated.

### Push/request a stock screen

Known stock callbacks reach `FUN_007c7930`, which marks a transition pending and pushes/inserts a requested screen ID into the shell history/request container.

The transition loop is:

```text
FUN_007c7820
    -> FUN_007c7070
        -> read target ID from history/request container
        -> release current active screen
        -> FUN_007c7ad0(targetId)       // factory
        -> store/activate new screen
```

`FUN_007c7ad0` is the actual integer screen factory. Earlier notes that treated `0x007C8600` as a function/factory entry were incorrect: that address lies inside `FUN_007c7ad0`.

### Back/pop history

Back is a different operation. Stock Options Back reaches `FUN_007c79a0`, which performs history/pop semantics and requests the resulting transition. It does **not** simply request MainScreen ID `1`.

A future OpenShim navigation abstraction should therefore preserve two separate operations conceptually:

```cpp
RequestShellScreen(stockScreen);
BackShellScreen();
```

Do not expose the raw Ghidra-inferred calling convention for `FUN_007c7930` or `FUN_007c79a0` yet. The decompiler prototype around the implicit manager/object pointer is not trustworthy enough for a public ABI. Resolve/validate the exact call ABI first.

Known callback-derived IDs include:

```text
0x02  cUI_SinglePlayer
0x03  cUI_OptionsParent / conditional cUI_OptionsAudio path
0x04  cUI_OptionsPlay
0x05  cUI_OptionsGraphics
0x06  cUI_OptionsAudio
0x0E  cUI_MultiPlayer_Lobby
0x15  cUI_OptionsInput
0x1C  cUI_Mods
```

The full `0x01..0x2A` factory map, constructor addresses, allocation sizes, holes, and conditional cases are documented in `reverse_engineering/REDUX_SHELL_UI_RE_MAP.md`.

## Main-menu `Career` direction

The corpus answers the architecture question more clearly than the older Options-only work could.

A true title menu such as:

```text
Single Player
Multiplayer
Career
Options
Credits
Quit
```

is feasible, but the safest first implementation is **not** to invent a new native screen ID.

Redux's stock factory is a compiled switch, not a dynamic screen-registration table. There is no binary evidence of a simple `RegisterScreen(id, constructor)` facility.

The preferred first Career layout is therefore:

```text
cUI_MainScreen
    |
    `-- MainScreen_Overlay
            |
            +-- stock main-menu controls
            +-- OpenShim Career button
            `-- OpenShim Career logical surfaces (hidden by default)
```

When Career opens, the integration should temporarily deactivate/hide the overlapping stock interactive controls, show the Career-native controls, and provide a Career Back action that restores the stock title controls without destroying `cUI_MainScreen`.

This is consistent with Redux's own MainScreen behavior: Credits and Replay Intro do not create new factory screens; they temporarily create/use a `movie1` overlay under the existing `cUI_MainScreen` and play `credits.ogv` / `intro.ogv`.

A true custom `CAREER_ID` remains a later RE target. It would require intercepting the stock request/factory path and fully owning a compatible root-screen lifecycle, including destructor/vtable/input/history semantics. Sending an arbitrary custom ID to the unmodified stock factory is not safe.

## Logical surfaces

A surface is a logical page/group, not a new active `cUI_View` container.

That distinction is intentional. A large active `cUI_View` can consume mouse input inside its rectangle even when none of its children handle the click. Instead, v1 mounts each native widget directly under the already-trusted host and lets a logical surface control their effective visibility as a group.

Create a surface:

```cpp
BZROpenShim::OpenShimUiSurfaceDesc page = {};
page.host = static_cast<uint32_t>(BZROpenShim::OpenShimUiHost::OptionsParent);
strcpy_s(page.name, "CareerRoot");

const BZROpenShim::OpenShimUiHandle careerPage = ui->createSurface(&page);
if (careerPage == BZROpenShim::OPENSHIM_UI_INVALID_HANDLE)
    return;
```

## Labels

```cpp
BZROpenShim::OpenShimUiLabelDesc title = {};
title.surface = careerPage;
title.rect = { 420.0f, 220.0f, 600.0f, 40.0f };
strcpy_s(title.name, "CareerTitle");
strcpy_s(title.text, "CAREER");

const auto titleHandle = ui->addLabel(&title);
```

The implementation currently uses the validated Redux `cUI_Text` allocation/constructor path and the same native text mutation path already used by OpenShim's injected Options/Input pages.

## Buttons and safe actions

```cpp
constexpr uint64_t kCareerStatistics = 0x1001;

BZROpenShim::OpenShimUiButtonDesc stats = {};
stats.surface = careerPage;
stats.rect = { 500.0f, 320.0f, 440.0f, 58.0f };
stats.actionId = kCareerStatistics;
strcpy_s(stats.name, "CareerStatistics");
strcpy_s(stats.text, "Statistics");

const auto statsButton = ui->addButton(&stats);
```

The button does **not** retain a consumer callback.

Redux invokes the OpenShim-owned native callback thunk, and that thunk publishes a copied SDK event:

```text
OpenShimEventType::NativeUiAction
arg0 = application actionId
arg1 = control value (0 for v1 buttons)
text = logical widget name
```

A consumer drains the normal SDK queue later from its own safe context:

```cpp
BZROpenShim::OpenShimEvent event = {};
while (shim->pollEvent(&event))
{
    if (event.type != static_cast<uint32_t>(BZROpenShim::OpenShimEventType::NativeUiAction))
        continue;

    if (event.arg0 == kCareerStatistics)
    {
        // Safe consumer-side action here.
    }
}
```

This preserves the event-bus rule: native engine/input hooks copy data; external/Lua behavior runs later from a context controlled by the consumer.

## Page navigation

A Career-style flow can be represented by multiple logical surfaces mounted to the same host. The example below still uses the currently public `OptionsParent` host; after MainMenu acceptance, Career would use `OpenShimUiHost::MainMenu` instead.

```cpp
OpenShimUiSurfaceDesc rootDesc = {};
rootDesc.host = static_cast<uint32_t>(OpenShimUiHost::OptionsParent);
strcpy_s(rootDesc.name, "CareerRoot");
const auto root = ui->createSurface(&rootDesc);

OpenShimUiSurfaceDesc statsDesc = {};
statsDesc.host = static_cast<uint32_t>(OpenShimUiHost::OptionsParent);
strcpy_s(statsDesc.name, "CareerStats");
const auto statistics = ui->createSurface(&statsDesc);

ui->setSurfaceVisible(statistics, 0);
```

After receiving the `Statistics` action in a safe consumer context:

```cpp
ui->setSurfaceVisible(root, 0);
ui->setSurfaceVisible(statistics, 1);
```

A Back action simply performs the reverse operation.

This is enough to model arbitrary page stacks without making Redux's screen pointers part of the public ABI.

## Visibility semantics

Widget visibility and surface visibility are separate state:

```cpp
ui->setVisible(someWidget, 0);       // widget wants to stay hidden
ui->setSurfaceVisible(page, 0);      // entire page is hidden
ui->setSurfaceVisible(page, 1);      // someWidget remains hidden
```

Effective visibility is:

```text
surface visible AND widget requested visible
```

This prevents page navigation from accidentally reviving an individually hidden/conditional control.

## Lifetime and ownership

Redux owns native child objects once OpenShim adds them to the screen tree.

OpenShim therefore does **not** directly delete a native label/button on `releaseSurface()` or process shutdown. `releaseSurface()` retires the logical surface and hides its widgets; Redux destroys the children when it destroys the owning screen.

Handles are valid only for the lifetime of the host screen on which they were created. Consumers must recreate their UI when the host screen is reconstructed.

Redux can recycle the same heap address for a later screen instance. Pointer equality is therefore not treated as sufficient proof of identity. Native UI tracks the validated parent child-count baseline plus the number of children it has injected. If a screen is destroyed/reconstructed at the same addresses, the child-tree fingerprint returns to the stock baseline and stale logical records are discarded.

When MainMenu becomes a public host, host identity must also participate in that generation fingerprint so an Options -> MainMenu transition cannot preserve records merely because allocator reuse produces matching addresses.

Action/widget slots are not recycled while one host lifetime remains active. A retired hidden button therefore cannot accidentally inherit a later button's action ID.

## v1 limits

Per host lifetime, v1 currently bounds itself to:

- 16 logical surfaces;
- 128 native widgets;
- 64 clickable button/action slots.

The bounds are intentional. This is shell UI, not an unbounded retained-mode UI system.

## Intentionally deferred controls

Redux bindings for additional controls are already known, but they are not part of Native UI v1 yet:

- `cUI_TextEntry`;
- `cUI_Selectlist`;
- overlays/decorative views;
- sliders/checklists;
- arbitrary dialogs/root screens.

Text entry and select-list need their edit/selection/scroll callback semantics wrapped behind the same safe queued-action model before becoming public API. Arbitrary active overlays require additional input-order safeguards because an active view can consume clicks itself.

The v1 contract is deliberately smaller than the reverse-engineered surface.

## Current OptionsParent acceptance test

The existing public host acceptance remains:

1. Open the normal Options parent screen.
2. From a known-safe UI-thread integration point, obtain SDK v2 and Native UI v1.
3. Create one `OptionsParent` surface.
4. Add one label and one button in unused space.
5. Confirm stock Back and the stock Options controls still receive clicks normally.
6. Click the injected button and confirm exactly one `NativeUiAction` is received with the expected `actionId` and name.
7. Hide/show the surface repeatedly and confirm the controls stop/start receiving input with their visibility.
8. Hide one widget, hide/show its surface, and confirm the widget remains individually hidden.
9. Leave Options, reopen it, and confirm the old handles fail closed rather than touching the reconstructed screen.
10. Recreate the surface/widgets on the new host and repeat the click test.
11. Exit the game normally and confirm no shutdown fault.

## MainMenu host acceptance gate

Before `OpenShimUiHost::MainMenu` becomes public/default-enabled:

1. Reach the normal title menu and verify the resolved singleton is the active `cUI_MainScreen`.
2. Verify exact child `MainScreen_Overlay` resolves through bounded child traversal.
3. Verify the expected stock child set/fingerprint is present.
4. Inject one test label and one test button into unused title-menu space.
5. Confirm Single Player, Multiplayer, Options, Credits, Mods, and Exit continue to receive input normally.
6. Verify the injected button produces exactly one queued `NativeUiAction`.
7. Hide the injected logical surface and verify it consumes no input.
8. Leave MainScreen for Options or Single Player and verify old handles fail closed.
9. Use stock Back to return and verify the reconstructed/reused MainScreen is re-resolved as a new host lifetime.
10. Repeat Main -> Options -> Back -> Main several times to exercise address reuse.
11. Open a temporary Career test surface, deactivate overlapping stock title controls, then restore them and verify focus/input returns correctly.
12. Exit the game with the test surface both hidden and visible and confirm no shutdown fault.

Only after this acceptance should the enum/API expose `MainMenu` as a supported host.

## Intended evolution

The framework is designed to grow approximately along this path:

```text
Native UI v1
  labels + buttons + surfaces + queued actions
          |
          +-- validated Main Menu host
          |      `-- native Career / Developer buttons + logical pages
          |
          +-- validated stock shell navigation
          |      +-- request/push stock screen
          |      `-- Back/history pop
          |
          +-- TextEntry / Selectlist
          |      `-- profiles, browsers, settings, save/load flows
          |
          +-- checklist / slider / setting-row wrappers
          |      `-- mod and multiplayer configuration
          |
          +-- custom root-screen interception (later, optional)
                 `-- true custom first-class Redux shell screens
```

OpenShim remains responsible for Redux ABI, allocation, native ownership, host validation, and safe event production. Higher-level features decide what those controls mean.