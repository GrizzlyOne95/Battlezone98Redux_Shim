# OpenShim SDK v2 and developer inspector

## Scope

SDK v2 is an additive public ABI for companion DLLs such as Extra Utilities. It does not replace the original `GetShimVersion`, `IsCompatibleGameVersion`, `IsPatchingComplete`, `GetAppliedPatchCount`, `Initialize`, or `Shutdown` exports.

The current v2 capabilities are deliberately small and high-confidence:

- stable versioned function-table discovery through `OpenShimGetApi`
- a bounded copied native-event queue
- a read-only developer snapshot
- qualified Battlezone distribution identity (`Unknown`, `GOG`, `Steam`)

No SDK v2 record exposes a raw Battlezone, Ogre, STL, or CRT-owned pointer.

## Discovery and append-only sizing

```cpp
using GetApiFn = const BZROpenShim::OpenShimApiV2* (__cdecl*)(uint32_t);

HMODULE shim = GetModuleHandleA("winmm.dll");
auto getApi = reinterpret_cast<GetApiFn>(GetProcAddress(shim, "OpenShimGetApi"));
const auto* api = getApi ? getApi(BZROpenShim::SDK_API_V2) : nullptr;

if (!api || api->apiVersion != BZROpenShim::SDK_API_V2)
{
    // v2 unavailable; use legacy exports or stand down.
}
```

`OpenShimGetApi(0)` asks for the newest table supported by the loaded shim. An explicit unsupported version returns `nullptr` rather than a partially compatible table.

SDK v2 is append-only. A consumer must check `structSize` before reading or calling a field that may have been appended after the consumer's minimum supported v2 layout. Do not require `structSize >= sizeof(OpenShimApiV2)` merely to use older v2 fields, because a newer header can be larger than an older but otherwise compatible v2 provider.

For an appended field, use the field boundary itself:

```cpp
const size_t distributionEnd =
    offsetof(BZROpenShim::OpenShimApiV2, getGameDistribution) +
    sizeof(api->getGameDistribution);

if (api->structSize >= distributionEnd && api->getGameDistribution)
{
    // This provider implements the appended field.
}
```

## Capabilities

The v2 table publishes a bit mask so consumers can probe features instead of inferring them from the shim version.

Current bits:

```text
OPENSHIM_CAP_STATUS
OPENSHIM_CAP_EVENT_QUEUE
OPENSHIM_CAP_DEVELOPER_INSPECTOR
OPENSHIM_CAP_GAME_DISTRIBUTION
```

A companion should test a capability and the corresponding function-table size before calling an optional appended function pointer.

## Qualified game distribution

`getGameDistribution()` returns `OpenShimGameDistribution` as a `uint32_t`:

```text
0 = Unknown
1 = GOG
2 = Steam
```

The value is intentionally tri-state. OpenShim uses the executable's SteamStub `.bind` PE section as the Steam structural signal, but it does **not** publish `GOG` merely because `.bind` is absent. The patcher first passes its supported Battlezone version gate; only then is the executable classified as `Steam` or `GOG`. Unsupported or not-yet-qualified executables remain `Unknown`.

```cpp
BZROpenShim::OpenShimGameDistribution distribution =
    BZROpenShim::OpenShimGameDistribution::Unknown;

const size_t fieldEnd =
    offsetof(BZROpenShim::OpenShimApiV2, getGameDistribution) +
    sizeof(api->getGameDistribution);

if ((api->capabilities & BZROpenShim::OPENSHIM_CAP_GAME_DISTRIBUTION) != 0 &&
    api->structSize >= fieldEnd && api->getGameDistribution)
{
    distribution = static_cast<BZROpenShim::OpenShimGameDistribution>(
        api->getGameDistribution());
}
```

Storefront-specific invasive features should fail closed on `Unknown`.

The developer snapshot exposes the same value in `gameDistribution`. That field consumes one previously reserved `uint32_t`, preserving the snapshot's total v2 size.

## Distribution-aware patch metadata

Patch definitions may constrain themselves to one or more qualified storefronts:

```json
{
  "name": "Example Steam-only patch",
  "platforms": ["steam"],
  "pattern": "..."
}
```

Supported keys are `steam` and `gog`. An omitted `platforms` property means the patch is storefront-neutral. A constrained patch is removed from the active patch set before pattern scanning, resolution, and application. `Unknown` never satisfies a storefront constraint.

The map-list Hop-Fix rewrite patches are Steam-only; universal map sorting/list support remains active on GOG.

## Event queue

The initial event family is lifecycle/status oriented:

```text
ShimInitialized
CompatibilityChanged
PatchingCompleted
ShutdownStarted
DeveloperSnapshotCaptured
```

The producer path copies compact values into a 256-record process queue. It never calls consumer code from an engine hook. Consumers poll later through `pollEvent`, which is the architectural pattern intended for future gameplay events such as damage, kills, weapon fire, commands, joins/leaves, and object lifecycle notifications.

Each record contains:

- ABI size/version
- event type
- process-wide monotonic sequence
- producer thread ID
- QPC timestamp
- `GetTickCount64` timestamp
- two generic 64-bit arguments
- a bounded 63-character diagnostic string

When the queue is full, the oldest event is discarded and `droppedEventCount` increments. This keeps the newest runtime state bounded without hiding overflow.

Example:

```cpp
BZROpenShim::OpenShimEvent event{};
while (api->pollEvent(&event))
{
    switch (static_cast<BZROpenShim::OpenShimEventType>(event.type))
    {
    case BZROpenShim::OpenShimEventType::PatchingCompleted:
        // event.arg0 = completed (0/1)
        // event.arg1 = applied patch count at publication
        break;
    default:
        break;
    }
}
```

## Developer inspector v1

The first inspector is intentionally a **read-only snapshot API**, not a new native screen and not a raw-memory viewer.

```cpp
BZROpenShim::OpenShimDeveloperSnapshot snapshot{};
if (api->captureDeveloperSnapshot(&snapshot))
{
    // snapshot.compatibleGameVersion
    // snapshot.gameDistribution
    // snapshot.patchingComplete
    // snapshot.appliedPatchCount
    // snapshot.pendingEventCount
    // snapshot.droppedEventCount

    if (snapshot.localPlayerResolved)
    {
        // snapshot.localPlayerX/Y/Z
    }
}
```

The same snapshot can be written to `openshim.log` using:

```cpp
api->logDeveloperSnapshot();
```

or the direct convenience export:

```text
OpenShimLogDeveloperSnapshot
```

Log records use the `dev_inspector` component.

### Why the first snapshot is narrow

Only already-proven ownership paths belong in the stable ABI. The local-player position comes from OpenShim's existing verified player-handle -> GameObject -> world-transform helper. If that path is unavailable or the executable is not compatible, `localPlayerResolved` remains zero.

The v2 structure reserves expansion space, but future object/Ogre/AI inspection should be added through an appended versioned record after its native ownership has been validated. The developer inspector should not turn uncertain reverse-engineering offsets into a public contract.

## Lifecycle integration

SDK initialization happens immediately after the shim logger initializes and does not require a supported Battlezone build. This lets a companion inspect failure state on a future executable. Distribution begins as `Unknown` and returns to `Unknown` during SDK shutdown.

The core patcher publishes compatibility and patch-completion transitions through the queue. Shutdown publishes `ShutdownStarted` before the subsystem teardown begins.

## Validation checklist

Automated/build validation should confirm:

1. `Release|Win32` links with the extended SDK module.
2. Existing `OpenShimGetApi`, `OpenShimCaptureDeveloperSnapshot`, and `OpenShimLogDeveloperSnapshot` exports remain unchanged.
3. An older v2 consumer can still use the original table prefix without requiring the new larger `sizeof(OpenShimApiV2)`.
4. A new consumer checks `structSize` before using `getGameDistribution`.
5. Existing network-safety validation still passes.
6. `patches.json` remains valid JSON and Steam-only patch constraints are honored before scanning.

Live Redux validation should confirm:

1. Supported GOG reports `GOG`; supported Steam reports `Steam`; an unsupported executable reports `Unknown`.
2. The three Steam map-list Hop-Fix rewrite signatures are not scanned or applied on GOG.
3. Universal map sorting/list support remains active on GOG.
4. Startup events appear in monotonic sequence.
5. A snapshot in the shell reports `localPlayerResolved=0` without faulting.
6. A snapshot in a mission reports a plausible player position.
7. Repeated polling/snapshot/distribution calls do not alter gameplay or renderer state.
