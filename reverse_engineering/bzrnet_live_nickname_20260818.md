# Live BZRNet nickname implementation (2026-08-18)

This note supersedes the earlier experimental assumption that `BZRNetLobby::SetPlayerData`
slot 7 takes a lobby/stable ID and that a rename should emit both `name` and
`playerName`.

## Settled Redux 2.2.301 ABI

- Active `BZRNetLobby` vtable anchor: `0x0089ADDC`.
- Stock lobby getter: `0x00764760` (published lobby global at `0x00945470`).
- `BZRNetLobby` slot **14**, address `0x0074B670`, returns the local player's
  native BZRNet identity into a 16-byte output object. OpenShim treats this as an
  opaque blob; no semantic field names are inferred.
- `BZRNetLobby` slot **7**, address `0x0074BF60`, is `SetPlayerData`. Its first
  explicit argument is that native self identity, followed by native Redux
  24-byte string objects for key and value.
- Redux native string constructor/destructor used at this ABI boundary are
  `0x00416EF0` / `0x00416F30`.
- Live nickname mutation sends **exactly** `SetPlayerData("name", value)`.
  `playerName` is not emitted by this path.
- The startup/re-auth nickname source remains the fixed 0x80-byte buffer at
  `0x009453E0`; it must be updated together with `[Network] Nickname` so a later
  connection in the same process or a later launch cannot revert the value.

## Safety rules

Addresses above are validation anchors, not blind calls. The implementation resolves slot 7
and slot 14 from the live lobby vtable, verifies the known 2.2.301 targets and executable
image mapping, validates the lobby/native-client back-pointer (`client+0xC38 == lobby`),
and wraps native boundary calls in SEH. If any qualifier fails, the live operation stands
down while the persisted/configured nickname remains available for a later connection.

## Front ends

The OpenShim lobby nickname widget, the multiplayer chat command (`/nickname`, with `/name`
kept as a compatibility alias), and the exported `OpenShimSetBZRNetNickname` bridge all
route through the same authoritative operation. The UI only calls it on Apply/Enter, never
for intermediate keystrokes.

EXU should consume only the exported status-returning bridge through `GetModuleHandleA`
and `GetProcAddress`; it should not duplicate BZRNet pointers, vtable slots, native string
ABI, or fixed process addresses.

## Validation scope

Source/build validation can prove ABI declarations, export linkage, and Win32 compilation.
It cannot prove server-side propagation. The two-client acceptance test remains manual:
rename from the UI and `/nickname`, verify the second client updates without reconnecting,
then verify lobby recreation, BZRNet reconnect, process restart, offline change, and guarded
failure behavior.
