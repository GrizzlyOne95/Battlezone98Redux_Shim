# Configurable Building tugging (`abstor` compatibility)

## Stock behavior

Redux 2.2.301 does not model Building tuggability as an ODF property.
`Building::Building` (`0x0047E9C0` in the exact GOG 2.2.301 image) compares the
owning `GameObjectClass` packed ODF name at `+0x30/+0x34` against the six-byte
name `abstor`. Only on that exact match does it copy the object's handle into
`Building +0x220`.

The Tug pickup scan consumes that field through the existing GameObject virtual
predicate. The normal stock checks for dying objects and already-attached
objects remain downstream of the predicate.

This makes a filename an undocumented capability bit: a PowerPlant, Factory,
Recycler, Armory, or other Building-derived object can acquire the stock tug
predicate if its own ODF name is `abstor`, while a different ODF name cannot
request the same behavior through data.

## OpenShim extension

OpenShim adds one opt-in integer key:

```ini
[BuildingClass]
tuggable = 1
```

Numeric `0` disables the OpenShim opt-in, and an absent key is off. Redux has
no ODF-to-ODF class inheritance for the key to follow (see "No ODF
inheritance" below). The key is intentionally
scoped to the Building inheritance path, so placing it on a non-Building ODF
has no effect.

The stock `abstor` special case is not removed or replaced. `abstor` remains
tuggable without the new key, preserving stock Strategy/CTF and legacy mission
behavior. The legacy filename special case applies only to the exact name
`abstor`.

## Implementation

The extension uses Redux's own active ODF/ParameterDB scope rather than opening
ODF files independently:

1. `BuildingClass::BuildingClass` opens the current ODF and then invokes the
   shared string16 ParameterDB reader for its `soundAmbient` field.
2. OpenShim intercepts only that exact
   `BuildingClass/soundAmbient` reader call. At this point the native
   ParameterDB scope is proven active.
3. The hook queries section hash `0x91E9360F` (`buildingclass`) and key hash
   `0x93392C60` (`tuggable`) through Redux's integer `ParameterDB::Get` path,
   defaulting to off.
4. The resolved value is associated with Redux's packed eight-character ODF
   identity.
5. After stock `Building::Building` runs, an opted-in ODF receives the exact
   same native state stock gives `abstor`: the value of GetHandle on the `+0x18`
   interface (complete-object `+0xF4`) is copied to `+0x220`.
6. Tug's own pickup scan is untouched, including its dying and already-attached
   rejection logic.

Hooking inside the existing BuildingClass read window is important: the
GameObjectClass and BuildingClass constructors each open and close their own
ParameterDB scope, so querying before the constructor would read the wrong
context. The implementation deliberately reuses the live native scope instead.

The cache is keyed by packed ODF name rather than class pointers, avoiding stale
native pointers across mission teardown. An explicit `tuggable = 0`, or an
absent key, removes any earlier opt-in for the
same packed name; this prevents addon shadowing from leaking state across
missions.

## No ODF inheritance (GOG 2.2.301, verified 2026-09-26)

The first draft of this note promised `baseName`-style inheritance. Redux has
none. In `[GameObjectClass]`, `basename` names the geometry (AbsoZero's battery
sets `basename = "abstor"` for the mesh). `GameObjectClass::Find` (`0x004E0F70`):

1. returns an already-built class whose packed name at `+0x30/+0x34` matches;
2. otherwise opens `%.8s.odf`, reads `[GameObjectClass] classLabel` (through
   the same String16 wrapper, a section the hook ignores), walks the
   *registered descriptor* vector, and calls the matching descriptor's
   `BuildClass` (vtable `+8`);
3. logs an error and returns null when no descriptor label matches.

`BuildingClass::BuildClass` (`0x00480110`) passes its own `this`, the
descriptor, to the constructor as the parent. So the `default` argument at the
soundAmbient read always points into a registered descriptor, never into
another ODF's class. The hook still looks the parent up in the opt-in cache,
but that lookup can only produce off.

## Calling conventions and offsets (GOG 2.2.301, verified 2026-09-26)

The first implementation never installed on this build: it declared both
ParameterDB readers `__cdecl`, and its prologue guard (`55 8B EC 8B 45 14`)
did not match, so the detour refused and the key was silently inert.

- `BuildingClass::String16` (`0x0047B6C0`) is `__thiscall`:
  `55 8B EC 51 89 4D FC` (push ebp; mov ebp,esp; push ecx; mov [ebp-4],ecx),
  forwards (section, key, out, default) plus its own ecx to `0x00589A10`, and
  returns with `ret 0x10`. At the soundAmbient call (`0x0048004F`) ecx is the
  BuildingClass constructor's local ParameterDB scope (`lea ecx,[ebp-0x14]`,
  built by `0x00589430`). The hook is a `__fastcall` shim
  (`this, edx, section, key, out, default`) with a 7-byte steal, guarded on
  those seven bytes; `tests/x86_length_tests.cpp` pins the decoder's verdict.
- `ParameterDB::GetInt` (`0x005896C0`) is `__thiscall` on that same scope,
  returns found/not-found in AL, and pops four arguments (`ret 0x10`). The hook
  passes the wrapper's ecx through as its `this`.
- `Building::Building` (`0x0047E9C0`, `ret 8`) stores into `+0x220` the result
  of the virtual GetHandle (`0x0046CFE0`, `mov eax,[ecx+0xDC]`) called on the
  `+0x18` interface, i.e. complete-object `+0xF4`, which the GameObject
  constructor fills from its first argument (`0x004DA14B`). The first
  implementation copied complete-object `+0xDC` instead; the hook now reads
  `+0x18+0xDC` like stock.

Live check: `reverse_engineering/run_lctug.ps1` (fixture in
`reverse_engineering/test_missions/lcbench_tug/`).

## Compatibility contract

- Numeric `1` enables the extension.
- Numeric `0` disables the OpenShim opt-in.
- Missing key is off.
- Exact stock `abstor` behavior remains active regardless of the new key.
- The extension changes only Building-derived objects and only the native
  tuggability field already consumed by Tug.
- It does not make `Artifact` behavior generic and does not alter Tug radius,
  attachment rules, death checks, towing physics, or network authority.

## Qualification matrix

| Case | Expected result |
|---|---|
| Stock `abstor`, no key | Tuggable exactly as Redux stock |
| Custom PowerPlant `azspow`, `tuggable = 1` | Tuggable and still a PowerPlant |
| Same `azspow`, key absent | Not tuggable |
| Same `azspow`, `tuggable = 0` | Not tuggable |
| Non-Building ODF with `tuggable = 1` | No effect |
| Mission/addon transition: same ODF name changes `1 -> 0/absent` | New class load is not tuggable |

The high-value live acceptance case is the AbsoZero battery gimmick: give the
custom PowerPlant ODF its own filename plus `[BuildingClass] tuggable = 1`, tow
it with a Tug, verify it still contributes PowerPlant behavior, and confirm the
mission no longer needs to shadow `abstor.odf` solely to acquire the hidden
predicate.
