# ODF-controlled tug capability

OpenShim can opt a building into or out of Tug pickup without requiring the ODF to be named `abstor`.

## Usage

Add the following to the object's own ODF:

```ini
[BuildingClass]
tugEnabled = true
```

Accepted true values are `1`, `true`, `yes`, `on`, and `enabled`. Accepted false values are `0`, `false`, `no`, `off`, and `disabled`.

The key is intentionally scoped to `[BuildingClass]`. A similarly named key in another section is ignored.

## Compatibility contract

The override is fail-open to stock behavior:

| ODF state | Result |
| --- | --- |
| no `tugEnabled` key | stock Redux behavior |
| `tugEnabled = true` | object reports its native handle as the tug capability |
| `tugEnabled = false` | object reports not tuggable |
| invalid value | warning + stock Redux behavior |

This means existing content does not change. Stock `abstor` remains tuggable because Redux's constructor still initializes its native tug field, and `Artifact` remains tuggable through its existing constructor behavior. OpenShim only overrides the result when the object's own ODF explicitly supplies the key.

The lookup uses the object's **own packed ODF name**, not `baseName`. For example, `azspow.odf` can now be a normal PowerPlant and independently opt in:

```ini
[GameObjectClass]
classLabel = "powerplant"

[BuildingClass]
tugEnabled = true
```

No `abstor.odf` shadow is required.

## Why this exists

Redux GOG v2.2.301 retains a legacy filename special-case in `Building::Building` (`0x0047E9C0`). The constructor compares `GameObjectClass + 0x30..0x37` against the packed filename `abstor` and, only on an exact match, copies the object's native handle from `GameObject + 0xDC` into `GameObject + 0x220`.

Tug pickup later calls the GameObject virtual at `0x0046D0C0`, whose complete behavior is to return `GameObject + 0x220`. `Artifact::Artifact` performs the same handle-to-`+0x220` assignment unconditionally.

OpenShim hooks that leaf getter rather than replacing Tug pickup logic. `true` reproduces the same `+0xDC -> +0x220` assignment that stock Building/Artifact construction uses; `false` masks the getter; and a missing key calls the original routine untouched.

The hook is byte-guarded against the known Redux getter instruction (`mov eax,[ecx+0x220]`) and fails closed on an unknown executable.

## Acceptance matrix

For live qualification, use distinct ODF names so the stock filename check cannot influence the custom cases:

1. `abstor.odf`, no key: Tug must still pick it up.
2. renamed Building-derived ODF, no key: Tug must not pick it up unless stock already makes that class tuggable.
3. renamed Building-derived ODF with `tugEnabled = true`: Tug must pick it up.
4. same ODF with `tugEnabled = false`: Tug must not pick it up.
5. `Artifact`, no key: Artifact must remain tuggable.
6. PowerPlant with `tugEnabled = true`: it must remain a functioning PowerPlant before, during, and after Tug attachment/detachment.
7. Repeat after mission reload to ensure the cached ODF decision does not depend on object lifetime.

For the AbsoZero battery use case, case 6 is the important regression: the battery can keep a unique ODF filename and PowerPlant semantics while gaining tug pickup through data rather than the `abstor` filename side effect.
