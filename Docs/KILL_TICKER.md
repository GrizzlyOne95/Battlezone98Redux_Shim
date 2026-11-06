# Kill ticker

Opt-in, visual-only HUD feed. When **your** hit is the one that destroys a
non-allied unit or building, a short line such as `-Tank` or `-Scout` appears
above the weapon list in the lower right. Nothing is recorded, sent or scored.

OpenShim Options → HUD → **Kill Ticker** (On/Off). INI: `[Display] KillTicker`,
default `0`. Applies live. Reset to Stock writes `0`.

## What counts

A line is added only for a verified kill. All of these must hold:

- The damage came from the local player's own object (craft or pilot),
  sampled when the damage landed.
- That damage application took the victim from alive (`healthRatio >= 0`) to
  dead (`healthRatio < 0`, the engine's own strictly-negative death test)
  inside the original `DamageAlloc` call. The credit goes to whoever lands the
  killing blow. Hits on an already-dead object earn nothing, so a later splash
  cannot steal a kill.
- The same full handle still names the same object after the call (no
  recycled slot).
- The victim is not on your team or an allied team (`GameObject::FriendP`, or
  same-team only if that row does not bind). Neutral (team 0) victims count.
  An unreadable team suppresses the line.
- The victim is a craft, building or person. Powerups (crates, daywreckers)
  are depleted, not killed, and never appear.
- Collisions do not count (the shared wrappers already exclude damage whose
  source and damager are the same object).

Not counted by design: kills by your AI wingmen, kills of your own or allied
units, objects removed by scripts, and anything the rules above cannot prove.
The ticker would rather miss a line than show a wrong one.

### Network games

The ticker is not gated to single player, but it never trusts guesses. Craft
and Building `DamageAlloc` only change health when the victim is not remote
(`Docs/MP_EXPLOSIVE_AUTHORITY_QUALIFICATION.md`), so there are two cases:

- **Victims this peer simulates** (for example, AI on the host): the exact
  rule above applies unchanged.
- **Victims another peer owns**: every peer still runs the wrappers for every
  hit, so this peer knows whose hit landed last. A candidate is credited only
  when your hit was the most recent hit by anyone, the victim was alive here
  when it landed, no hit on it changed health locally (otherwise the exact
  rule owns it), and its replicated health is then seen below zero within
  1.5 s. A victim that just disappears (removed, entered a craft, recycled) is
  never credited. The object-state `0x200` bit is deliberately not used as a
  death signal here, because `RemoteDelete` sets it (`0x280`) for plain
  removals.

Because the victim's owner decides the real killing blow, the network-only
path is best effort: lag can make this peer see a different last hit than the
owner did. **Unvalidated:** whether Redux replicates negative health before it
deletes a remote object. If it does not, remote kills simply never show; no
false lines result.

## Display

- Up to four lines. The newest sits directly above the weapon list; older
  lines stack upward.
- Each line shows for 3 s and fades over the last 0.6 s. The clock starts on
  the first frame it actually draws, so a kill just before the pause menu is
  still shown afterwards; an undrawn line is dropped after 5 s.
- A second kill of the same unit type within 2 s of the newest line becomes
  `-Tank x2` (up to `x99`) instead of another line.
- Warm amber text (`0xFFFFD27A`) on the autosave notice's translucent black
  backing, in the stock HUD font. The backing fade uses `HudFillRect` mode 0,
  which keeps alpha. Text alpha goes through the stock text path; if that path
  ignores alpha, text stays solid until the line expires.
- Text is right-aligned to the right edge of the stock weapon-list backdrop,
  measured with `UiTextMeasure`. If the backdrop has not been drawn within
  500 ms, or its rectangle is not on screen in the lower-right quadrant, the
  feed uses a fixed position: 2% from the right edge, lowest line ending at
  70% of the viewport height.

### Names

The name is `[GameObjectClass] unitName` from the victim's ODF (`Tank`,
`Scout`, `Gun Tower`). The ODF is read through the engine's own file read
(the `PathBlock::ReadFile` resolve), so addon, mod and packed ODFs resolve
exactly as the game loaded them. If there is no `unitName`, the ODF name
itself is shown (`-avtank`), so a unit is never reported as something it is
not. Names are cached per mission and read on the frame thread, never inside
a damage wrapper.

## Native boundaries

| Piece | File |
| --- | --- |
| Verification, network candidates, feed timing, placement, ODF parsing (pure, host-tested) | `include/kill_ticker_policy.h`, `tests/kill_ticker_policy_tests.cpp` |
| Damage sampling (shared with hit markers and damage indicators) | `src/patches/hud_feedback.cpp` |
| Queue, name lookup, painter | `src/patches/kill_ticker.cpp` |
| Gauge-draw paint point, shared with the autosave notice | `src/patches/hud_gauge_overlay.cpp` |
| Weapon-list rectangle observer | `src/patches/contextual_hud.cpp` (`InstallWeaponListAnchor`) |

No new engine addresses. Every site is an existing qualified row:

- The four `HudFeedback*Damage` `DamageAlloc` entries, installed when the
  ticker, hit markers or damage indicators are on. Hit markers and arcs stay
  single player because the wrappers pass the real session type through to
  their checks.
- `HudPaletteFriendTeam` / `HudPaletteEnemyTeam` for the allied filter
  (optional).
- `AutoSaveNoticeHudGauge` plus the HUD text, measure, fill, viewport, depth,
  style and pane rows. These move from `autosave_notice.cpp` to the shared
  overlay. That overlay owns the single detour and calls a fixed painter table
  (autosave notice, kill ticker) after the stock gauge returns. A painter that
  faults is disabled for the run and logged once.
- `HudFadeWeaponPlate`, the stock weapon-list backdrop `HudSpriteSubmit` call,
  redirected to contextual HUD's existing `WeaponPlate` adapter.
  `RedirectCallTarget` is idempotent for the same target, so the ticker and
  the HUD fade can both install it. With fading off, the adapter forwards the
  stock call unchanged and only records the rectangle.
- `PathBlock::ReadFile` (resolve) for ODF text. If it is unavailable, lines
  use ODF names.

Like the rest of the HUD feedback family, the ticker requires the qualified
GOG 2.2.301 build (`IsCompatibleGameVersion`); otherwise the row reports the
shared unavailable reason and nothing installs.

Log tags: `[killticker]` (enable/disable, first 16 verified kills per mission
with `path=exact|network`) and `[hudoverlay]` (detour install, painter fault).

## Validation status

- Host: `kill_ticker_policy_tests` covers the exact rule, the network
  candidate rules, feed coalescing/expiry/fade, placement and `unitName`
  parsing. The options localization table is regenerated and current.
- Live evidence carried over from `Docs/HUD_FEEDBACK.md`: a GOG DX11 run
  observed a lethal health transition inside the Craft `DamageAlloc` wrapper,
  with the same handle still resolving afterwards.
- **Not yet run in game.** Still needed:
  - a Windows build;
  - single-player kills of craft, buildings and pilots (sniped and run over);
  - autosave notice regression through the shared overlay;
  - placement at several resolutions and UI scales, with HUD fading on and off
    and with EXU HUD ownership;
  - a two-peer network session (host and client) to confirm the remote path;
  - Steam/Proton/Wine.
- Possible gap: a victim whose object is freed inside the lethal
  `DamageAlloc` call (suspected for some person deaths) fails the
  same-lifetime check and shows no line.
