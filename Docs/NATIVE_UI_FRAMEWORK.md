# OpenShim Native UI Framework

OpenShim Native UI v1 is a small, versioned wrapper around the Redux `cUI` ABI that lets OpenShim consumers create native-looking UI without receiving or dereferencing Redux UI pointers.

It is intentionally conservative. The first public surface wraps only behavior whose constructor, ownership, input ordering, and lifetime have already been exercised by OpenShim's native Options/Input UI work.

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

Native UI v1 exposes one host:

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

### Main-menu `Career` button

A true top-level button such as:

```text
Single Player
Multiplayer
Career
Options
Credits
Quit
```

requires a separately validated main-menu host and navigation seam. Native UI v1 does **not** guess that layout or silently reuse an unrelated screen.

Once that host is recovered, it can be added as another `OpenShimUiHost` without changing the opaque widget model or exposing Redux pointers.

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

A Career-style flow can be represented by multiple logical surfaces mounted to the same host:

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

Handles are valid only for the lifetime of the host screen on which they were created. Consumers must recreate their UI when the Options screen is reconstructed.

Redux can recycle the same heap address for a later screen instance. Pointer equality is therefore not treated as sufficient proof of identity. Native UI tracks the validated parent child-count baseline plus the number of children it has injected. If a screen is destroyed/reconstructed at the same addresses, the child-tree fingerprint returns to the stock baseline and stale logical records are discarded.

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

## Acceptance test

The first live acceptance should be minimal and run on the supported Redux build:

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

Only after that acceptance should another shell host (especially the main menu) be added.

## Intended evolution

The framework is designed to grow approximately along this path:

```text
Native UI v1
  labels + buttons + surfaces + queued actions
          |
          +-- validated Main Menu host
          |      `-- first-class Career / Mods / Developer buttons
          |
          +-- TextEntry / Selectlist
          |      `-- profiles, browsers, settings, save/load flows
          |
          +-- checklist / slider / setting-row wrappers
          |      `-- mod and multiplayer configuration
          |
          +-- dialog/screen navigation abstraction
                 `-- complete custom Redux-native front ends
```

OpenShim remains responsible for Redux ABI, allocation, native ownership, host validation, and safe event production. Higher-level features decide what those controls mean.
