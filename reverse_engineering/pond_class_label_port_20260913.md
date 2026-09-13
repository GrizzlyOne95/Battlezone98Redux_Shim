# BzE `pond` class-label port

## Source evidence

The implementation was recovered from the unpacked BzE 1.34 executable at
`BzE1.34.unpacked.exe`. BzE 1.39 and 1.39.1 ODF collections in Google Drive
provide the content-side contract. Thirteen water ODFs use the label; the
minimal representative is `water.odf`:

```ini
[GameObjectClass]
baseName = "wat11pn1"
classLabel = "pond"
scrapCost = 0
scrapValue = 0
maxHealth = 0
maxAmmo = 0
unitName = "Water"
heatSignature = 0
imageSignature = 0
radarSignature = 0

[BuildingClass]
soundAmbient = "water.wav"
```

`PondClass` construction at BzE 1.34 address `0x004BE1B0` first runs the
ordinary `BuildingClass` constructor, then changes exactly these identity
fields:

- class signature: `POND` (`0x504F4E44`)
- class label: `pond`
- class rank/category: `5`

Its ODF constructor at `0x004BE2B0` likewise delegates to the BuildingClass ODF
constructor and reads `BuildingClass/soundAmbient`. Its runtime object at
`0x004BE0C0` is a Building with Pond vtables. Comparing those vtables to the
stock Building vtables found one behavioral override: the Building
`GetRank(float,float)` virtual is replaced by `0x004BE170`, which always returns
`-1.0f`.

## Redux adaptation

Redux already has the same class registry and construction model, but no Pond
descriptor. `GameObjectClass::Find` at `0x004E0F70` reads the class label and
compares it to every registered descriptor immediately before calling virtual
slot `BuildClass`.

OpenShim patches only that comparison call. When the requested label is `pond`
and the current registered descriptor is `i76building`, it reports a match.
The stock `BuildingClass::BuildClass` then constructs and parses the complete
class, preserving inherited building behavior and `soundAmbient`. A detour on
that constructor applies the three BzE Pond identity fields to the returned
class. A second detour on Redux `Building::GetRank` returns `-1.0f` only when
the object's class signature is `POND`; all ordinary and derived buildings use
the untouched trampoline.

The pending Pond match is thread-local and is cleared before stock class
construction. This matters because base ODF construction can recursively call
`GameObjectClass::Find`; those nested lookups must continue to recognize normal
`i76building` labels.

## Address identity

- `GameObjectClass::Find` class-label comparison: `0x004E1109`
- `BuildingClass::BuildClass`: `0x00480110`, descriptor vtable slot at
  `0x008766F4`, allocation size `0x160`
- `Building::GetRank`: `0x0047FB80`, secondary vtable slot at `0x008766AC`

All three are declared as named signature resolves in `scripts/patches.json`;
fallbacks record the exact GOG Redux 2.2.301 addresses. The signatures, not the
fallback constants, are preferred so the Steam image can settle and resolve
through the existing deferred-hook retry path.
