# Loadout Presets Research

Status: research only. GOG Redux 2.2.301 is primary; unchecked claims
are marked UNVERIFIED.

## Executive conclusion

A first preset feature is feasible without a new weapon native hook:

- Read five installed weapon classes with stock `GetWeaponClass(h, slot)`.
- Save each slot and weapon ODF.
- Reapply through `Build`/`Dropoff` at an Armory, preserving scrap cost
  and Armory availability.
- Reject missing Armory, incompatibility, or insufficient payment.

The native part can add UI and queue integration. It does not need an
engine-level weapon installer. Lua can own a preset table and Armory queue.

## 1. How weapons change today

### Armory power-ups

The GOG 2.2.301 `Armory::` constructor `0x00472460` scans attached
children for kinds `0x414d4d4f` ("AMMO") and `0x524b4954` ("KIT"), then
stores matching pointers. `FUN_00473330` initializes Armory class kind
`"armory"` and the Armory vtable.

Sources:

- `.../BZ1/Redux/openshim_re_corpus/bzr_gog_best_effort/.../FUN_00472460-00472460.c`
- `.../FUN_00473330-00473330.c`

Stock Lua reaches an Armory with `GetArmoryHandle(team)`. Queue
`Build(armory, "weapon_odf")`, then `Dropoff(armory, vehicle)` on a later
update. Same-frame calls are unsafe
(`Docs/BZR_LUA_AGENT_REFERENCE.md`, Build/Dropoff section).

### Recycler/Factory vehicle slots

Producer menu code confirms active Recycler and Factory category pages
and Armory-specific behavior
(`src/patches/producer_build_menu.cpp:461-465,1040-1042`).

The exact Redux mapping between Factory/Recycler UI rows and ODF
`weaponName0..4` fields is **UNVERIFIED**. Historical Doxygen/ODF data
does not prove Redux 2.2.301 UI or save format.

Assume the built vehicle exposes five current slots, not UI category
positions or texture order.

### Lua GiveWeapon

Stock Lua `GiveWeapon(handle, weaponname?, slot?)` is live:

- Lua wrapper `FUN_00503520` reads handle, optional name and slot.
- Missing/negative slot calls `FUN_005cb050`; explicit slot calls
  `FUN_005cb0d0`.
- Both reach `FUN_00612f10`, which removes/replaces a slot, updates weapon
  masks and calls an object virtual method.

Sources: GOG decompile files for `00503520`, `005cb050`, `005cb0d0`,
and `00612f10`. Lua slots are 0-4; mask bits are 1/2/4/8/16
(`Docs/BZR_LUA_AGENT_REFERENCE.md`, weapons section).

`GiveWeapon(h, nil, slot)` removes one slot. An ODF plus compatible slot
installs/replaces it. SetWeaponMask only changes selection; it is not
proof that a hardpoint contains that weapon class.

### EXU and OpenShim

EXU exports:

- `exu.GetSelectedWeaponMask(h)`
- `exu.GetWeaponSelectionInfo(h)`

It also exports stock `GetWeaponMask`, but no Lua weapon setter was found.
The implementations read stored/mode/carrier masks; they do not install
weapons. Sources: `ExtraUtils/Definitions/ExtraUtils.lua` and
`ExtraUtilities/src/Game/GameObject.cpp`.

Conclusion: stock `GiveWeapon` and `GetWeaponClass` support Lua preset
experiments. EXU is not required for the primitive. UI/persistence
still need design.

## 2. Applying presets

Candidate paths:

1. **Armory queue**: build and drop each weapon powerup. It preserves
   scrap, Armory availability and stock economics. Cross-team targeting
   is hazardous (`BZR_LUA_AGENT_REFERENCE.md`, cross-team section).
2. **Stock GiveWeapon**: instant Lua implementation, but no cost, no
   Armory, and unknown MP replication.
3. **Native Armory/drop hook**: queue and validate weapons. Likely
   unnecessary when Lua and native UI can queue existing APIs.

Recommended v1: Armory queue plus Lua slot/name records. After each drop,
read `GetWeaponClass(h, slot)` and mark success only on a match.
Removal policy needs live Redux qualification or a separate stock call.

## 3. State and persistence

Store preset name, vehicle ODF/class, five optional slot/weapon entries,
queue order, optional selected mask, schema/revision and mod identifier.

Store slot plus weapon ODF, not only a mask. A mask cannot identify the
class or distinguish variants.

Persistence choices:

- **Per-ODF**: campaign/mod defaults; defer until a parser contract exists.
- **Player INI**: personal named presets and save/load. Use
  `[LoadoutPresets]` plus an existing preset revision marker.
- **Campaign Lua**: mission-authored temporary presets; not persistent
  across launches.

Smallest v1: one named preset per selected vehicle, persisted in a player
INI section. No new ODF format. Global defaults are later work.

## 4. Multiplayer and authority

Default to single-player implementation. Stock Lua documentation says
`GiveWeapon` needs `Send`/`Receive` when peers must match. The project
replication probe records it as a local mutation; weapon class vs ammo,
mask and remote firing remain unknown
(`Docs/MP_LUA_REPLICATION_QUALIFICATION.md`, Weapons/loadout).

An Armory is a networked producer, but live proof is lacking for cost,
drop authority, late join, owner transfer and remote loadout state.

Safe MP rules:

- Vehicle owner executes build/drop and mutation.
- Peers receive preset identity/slot records, not independent spend/spawn.
- Owner checks scrap and Armory.
- Every peer verifies vehicle/weapon compatibility.
- Reject remote/non-local vehicles and cancel lost Armory/vehicle queues.
- Require every peer to run the same mod/OpenShim build.
- Without live qualification, keep the feature SP-only.

## 5. Smallest useful version

V1 UX:

1. Add one key or native menu action.
2. With one compatible vehicle selected, show five slots.
3. Save vehicle ODF plus `Weapon0..Weapon4`.
4. Apply one named preset to one owned compatible vehicle.
5. Queue Armory builds/drops one update at a time.
6. Report success/failure per slot; stop on scrap, Armory, compatibility
   or ownership failure.

No free-cost bypass. Multiplayer remains gated until live authority tests.

## Risks

- Direct `GiveWeapon` can become an economy bypass.
- Cross-team Armory targeting is unsafe.
- A mask is not a weapon class identity.
- Replication of ammo, active mask and firing is unproved.
- Removing the active weapon is historically risky.
- Redux 2.2.301 Factory/Recycler slot mapping is UNVERIFIED.
- Vehicle/Armory loss or zone change requires queue cancellation.
