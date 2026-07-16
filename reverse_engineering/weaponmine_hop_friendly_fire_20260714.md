# WeaponMine hop-out friendly-fire investigation (2026-07-14)

## Finding

Redux `WeaponMine::Simulate` is at GOG VA `0x00612950` (RVA `0x00212950`).
The function scans the global craft list and calls
`GameObject::FriendP(mine, candidate)` at `0x00612A51` before considering range,
line of sight, aim, and firing.

The 1.5 PDB corpus shows the same behavior at `0x0053F9CF`. It also shows that
`Craft::AbandonPilot` calls `GameObject::SetPerceivedTeam(craft, 0)` after
building the pilot. `GameObject::FriendP(GameObject*)` obtains the other
object's team through virtual slot 1, which is the perceived-team getter in
Redux (`return [this+0x15C]`). Therefore the mine's one-way friendship check
temporarily sees an allied, just-abandoned ship as team zero and accepts it as
a target.

## Patch

Patch the rel32 operand of the WeaponMine-only call at `0x00612A52`. The shim
replacement preserves the stock result first. Only when that result is false
and the candidate's perceived team is zero does it check the reciprocal
relation, `candidate->FriendP(mine)`.

The reciprocal check uses the candidate's persistent Team object, which is not
cleared by `Craft::AbandonPilot`:

- Allied abandoned ship: reciprocal friendship is true, so the mine skips it.
- Enemy abandoned ship: reciprocal friendship is false, so it remains a valid
  target.
- Any non-neutral craft: behavior is exactly stock.

This is narrower than suppressing all neutral targets and avoids changing
`Craft::AbandonPilot`, team ownership, AI adoption, or global relation logic.

## Under-attack beep

`GameObject::SetDamageFlags` invokes `BettyVoice::AttackWarning` only after it
classifies incoming shot damage as enemy damage. The WeaponMine guard prevents
the shot entirely when the reported beep is downstream of this mine bug.

There is not enough static evidence to claim that every one-shot beep observed
while hopping has the same cause. If the beep reproduces with no WeaponMine in
range, trace `GameObject::SetDamageFlags` and log victim, damage source,
damager, and their perceived/actual teams during `Craft::AbandonPilot`.

## Validation checklist

1. Place an allied WeaponMine near the player's ship and hop out/re-enter.
2. Confirm the mine neither rotates/fires nor damages the ship during team zero.
3. Repeat with an enemy ship abandoned in range; confirm it remains targetable.
4. Repeat in multiplayer as host and client; WeaponMine simulation is skipped
   for remote instances, so the authoritative side must install the patch.
5. Re-test the one-shot under-attack beep both with and without a WeaponMine in
   range to separate the downstream symptom from a general hop alert bug.
