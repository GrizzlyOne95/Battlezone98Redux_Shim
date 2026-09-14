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

`0` or an absent key preserves stock behavior. The key is intentionally scoped
to the Building inheritance path; placing it on a non-Building ODF has no
effect.

The stock `abstor` special case is not removed or replaced. `abstor` remains
tuggable without the new key, preserving stock Strategy/CTF and legacy mission
behavior.

## Implementation

The extension uses Redux's own ODF/ParameterDB context rather than opening ODF
files independently:

1. The BuildingClass base constructor is observed while the current ODF is
   active.
2. OpenShim queries section hash `0x91E9360F` (`buildingclass`) and key hash
   `0x93392C60` (`tuggable`) through Redux's integer `ParameterDB::Get` path.
3. The result is associated with Redux's packed eight-character ODF identity.
4. After stock `Building::Building` runs, an opted-in ODF receives the exact
   same native state stock gives `abstor`: the already-created object handle at
   `+0xDC` is copied to `+0x220`.
5. Tug's own pickup scan is untouched, including its dying and already-attached
   rejection logic.

Using the engine's current ParameterDB context keeps addon search and ODF load
behavior aligned with Redux. The implementation also removes a cached opt-in
when the same packed ODF name is later constructed without the key, so an addon
shadowed in a subsequent mission does not inherit stale process-lifetime state.

## Compatibility contract

- Numeric `1` enables the extension; numeric `0` disables it.
- Missing key means no OpenShim opt-in.
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
