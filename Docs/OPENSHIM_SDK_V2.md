# OpenShim SDK v2 and developer inspector

## Scope

SDK v2 is an additive public ABI for companion DLLs such as Extra Utilities. It does not replace the original `GetShimVersion`, `IsCompatibleGameVersion`, `IsPatchingComplete`, `GetAppliedPatchCount`, `Initialize`, or `Shutdown` exports.

The first v2 capabilities are deliberately small and high-confidence:

- stable versioned function-table discovery through `OpenShimGetApi`
- a bounded copied native-event queue
- a read-only developer snapshot

No SDK v2 record exposes a raw Battlezone, Ogre, STL, or CRT-owned pointer.

## Discovery

```cpp
using GetApiFn = const BZROpenShim::OpenShimApiV2* (__cdecl*)(uint32_t);

HMODULE shim = GetModuleHandleA("winmm.dll");
auto getApi = reinterpret_cast<GetApiFn>(GetProcAddress(shim, "OpenShimGetApi"));
const auto* api = getApi ? getApi(BZROpenShim::SDK_API_V2) : nullptr;

if (!api || api->apiVersion != BZROpenShim::SDK_API_V2 ||
    api->structSize < sizeof(BZROpenShim::OpenShimApiV2))
{
    // v2 unavailable; use legacy exports or stand down.
}
```

`OpenShimGetApi(0)` asks for the newest table supported by the loaded shim. An explicit unsupported version returns `nullptr` rather than a partially compatible table.

## Capabilities

The v2 table publishes a bit mask so consumers can probe features instead of inferring them from the shim version.

Current bits:

```text
OPENSHIM_CAP_STATUS
OPENSHIM_CAP_EVENT_QUEUE
OPENSHIM_CAP_DEVELOPER_INSPECTOR
```

A companion should test a capability before calling the corresponding optional function pointer.

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

The v2 structure reserves expansion space, but future object/Ogre/AI inspection should be added through a new SDK revision or an appended versioned record after its native ownership has been validated. The developer inspector should not turn uncertain reverse-engineering offsets into a public contract.

## Lifecycle integration

SDK initialization happens immediately after the shim logger initializes and does not require a supported Battlezone build. This lets a companion inspect failure state on a future executable.

The core patcher publishes compatibility and patch-completion transitions through the queue. Shutdown publishes `ShutdownStarted` before the subsystem teardown begins.

## Validation checklist

Automated/build validation should confirm:

1. `Release|Win32` links with the new SDK module.
2. `winmm.dll` exports `OpenShimGetApi`, `OpenShimCaptureDeveloperSnapshot`, and `OpenShimLogDeveloperSnapshot` by those undecorated names.
3. Existing feature-bridge exports remain present.
4. Existing network-safety validation still passes.

Live Redux validation should confirm:

1. `OpenShimGetApi(2)` returns a table with the expected size/version/capability bits.
2. Startup events appear in monotonic sequence.
3. A snapshot in the shell reports `localPlayerResolved=0` without faulting.
4. A snapshot in a mission reports a plausible player position.
5. An unsupported build can still query SDK status while version-specific player inspection stands down.
6. Repeated polling/snapshot calls do not alter gameplay or renderer state.
