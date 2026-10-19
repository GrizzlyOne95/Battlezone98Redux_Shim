# Contextual HUD fading

Default-off local presentation controls for the released GOG 2.2.301 game.
OpenShim Options → HUD → HUD Fading contains independent controls for the
weapon list, scrap meter, pilot meter and command interface. The separate
HUD -> Meter Fading page adds cockpit hull and ammo controls. HUD -> Radar
Fading adds complete cockpit-radar fading and an option to keep the compass visible.
Existing colors,
Stock/Legacy layout, native scaling, text, alignment, backplates and gameplay
remain as selected.

## Controls and behavior

All twenty-nine fade keys are in `[Display]` and apply live. For each prefix
`WeaponList`, `ScrapHud`, `PilotHud`, `CommandHud`, `HullHud`, `AmmoHud` and
`RadarHud`:

| Suffix | Default | Menu | INI range |
| --- | --- | --- | --- |
| `Fade` | 0 | Off / On | boolean |
| `IdleOpacity` | 25 | Hidden / 25% / 50% / 75% | 0–100 percent |
| `FadeDelay` | 2500 | 1 / 2.5 / 5 seconds | 0–30000 ms |
| `FadeDuration` | 500 | Instant / Fast / Normal / Slow | 0–5000 ms |

Fast/Normal/Slow are 200/500/1000 ms. Invalid values use the defaults.
`CommandHudIdleOpacity` defaults to 0 (Hidden), rather than 25. All seven Fade
switches still default Off. Compact Cmd rows describe the command controls.
`RadarCompassAlwaysVisible` defaults to 0; On keeps the four native compass
letters visible while the rest of the radar fades.
Opacity multiplies native alpha; existing dimming/transparency and RGB are preserved.
Disabled groups remain fully native. A fresh all-Off launch installs no new
adapters. Once installed, Off forwards native colors without removing detours.

Each group starts fully visible, holds for its own delay and eases smoothly
toward its own idle opacity. Relevant changes restore full opacity immediately:

- Weapons: selected mask, available/linkable mask, hardpoint loadout, or ammo.
  Firing, spending or replenishing ammo therefore keeps/reveals the list.
- Scrap: current scrap or maximum capacity.
- Pilots: current available pilots or maximum capacity.
- Hull: current health or maximum health changes. Health below the native
  strict 25% threshold stays visible; repairs start a fresh hold.
- Ammo: spending/refill, capacity, weapon selection/loadout or ammo-cost changes.
  The native all-available-weapons-unaffordable warning keeps the group visible.
  The group includes label/fill, remaining-shot text and all three cost-marker
  rectangles. Zero-cost weapons do not create an empty-ammo warning.
- Radar: native range/compact-mode and target changes, active command contexts,
  ping animation, newly native-visible contacts, and recent-hit alerts on native
  visible contacts. Contact movement and draw order do not refresh the hold.
- Commands: the native row/group actions, command-menu activation, or a native
  pointer action hitting a command row. An active unit selection, category,
  menu navigation or nested build page stays fully visible until it closes.
  The idle hold begins again after the final interaction. Walking, aiming and
  firing alone do not count as command activity.

Unchanged readings do not restart the hold, and changing one group does not
reveal the others. A player/team change, mission reset or config apply starts
a new hold. Shell/pause/unreadable snapshot state fails fully visible and
discards fade history. Geometry is still submitted with alpha zero for Hidden;
native status rendering and its warning/audio side effects always execute.
Reticle, tactical MapRadar, target camera and objectives remain outside the fade scopes.
The remaining native draw owners, incomplete alpha paths and suggested reveal
policies are mapped in [HUD_ELEMENT_MAP.md](HUD_ELEMENT_MAP.md). That research
does not enable additional fading or qualify new hooks.

## Native adapter

All new code sites and callable getters live in `scripts/patches.json` under
`HudFade*`. The complete set binds before installation. Unsupported executables
or any guard failure stand down; partial installs keep opacity at one.
Configuration/state use an SRW lock; draw scopes read atomic opacity snapshots.
There are no INI reads, allocations or logging in draw hooks.

The safe-frame driver samples the game's existing current-player and local-team
getters. The player full handle must round-trip, and resource values must be
bounded. Four released team accessors provide current/capacity values. Released
carrier accessors provide selection/availability and five hardpoint class
identities, with ammo read through the native complete-object getter. Loadout
identities are hashed immediately; no object pointer is retained for later use.
All reads are guarded. No simulation values are written.

Four resource text CALLs forward the original twelve cdecl arguments and
retain native/custom colors and layout. Three weapon-list CALLs forward native
backdrop, icon and font submissions. The existing scrap/pilot plate adapters
are shared with Legacy mode: they stay installed when resource fading is on,
and their scope covers either the stock artwork or the reconstructed plate.
There is no competing redirect at those plate CALLs.

Each submission pushes a thread-local opacity and restores it with `__finally`.
The native sprite and fill mode-to-ARGB helpers calculate their original colors;
their return alpha is multiplied only while a selected draw scope is active.
Outside a scope the return value is byte-identical. The font, sprite tint,
palette globals, pane, geometry, clipping, UVs, mode flags and native warning
branches are not rewritten to implement fading. Original status callbacks are
never skipped. Normal startup/teardown clears the fade history.

The command extension replaces only the native ControlPanel render slot (6).
Its renderer entry, slot ownership and thirteen row-action pointer bindings
qualify before shared helpers are installed for a command-only configuration.
Existing producer build-menu lifecycle hooks in slots 4/7 are preserved. The
native renderer always executes, including selection, command dispatch and menu
sounds while alpha is zero. One draw scope covers its frame, icons, labels,
unit bars and command connectors; only the return alpha changes.

Command input uses the game's resolved action bytes, so it follows native
rebinding and controllers. A pointer action must hit a native command row;
generic pointer/world activity does not reveal the panel. The active sample
and selected full handles are copied/hashed while the renderer owns its class
instance. The instance address is an identity token, never dereferenced later.
Unreadable data, invalid fields or an unexpected class fail fully visible.
The touch/alternate command layout stays fully visible pending qualification.
The other three groups remain independently available if command guards fail.

The initial adapter is gated to GOG 2.2.301. Steam is disabled; Steam, Wine,
Proton and other renderers require qualification before release. There are no
new dependencies, paths, asset files, SDK APIs or mission overrides.

The hull/ammo extension scopes two hull sprite CALLs, ammo shots text and
three cost-marker filled rectangles. The two ammo sprite CALLs retain a single
owner in HudPalette, shared by color and fade. Cached binding/installation
allows either feature to initialize first without guarding or redirecting the
other feature's wrapper as though it were stock. Palette guards still qualify
before palette installation. Idle fade multiplies final alpha after tint.

Meter activity samples the released current/max-health and max-ammo accessors,
plus copied weapon costs and selection/loadout state. Displayed interpolation
is not an activity source. The existing owner round-trip and mission reset
rules apply; unreadable samples fail visible. Native pane clipping, UVs,
warning sounds and status updates always execute. A partial/refused meter
installation keeps both meter opacities at one and does not stop other enabled
fade groups. All new addresses/guards are named catalog rows; the existing
outline helper is distinct from the filled-rectangle cost-marker helper.

## Qualification

Released executable SHA-256:
`8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413`.
Ghidra and Capstone inspection of the released game established getter fields,
call arities, caller cleanup and draw boundaries. Native `ReadProcessMemory`
PID 21984 matched all 22 candidate guard windows before authoring the adapters.
No leaked PDB or decompiler output is committed.

The new portable policy test covers holds, smooth/instant fades, Hidden,
independent activity, clock reversal, identity/reset behavior and alpha/RGB
preservation, repeated command activity and separate safe-frame/render samples.
All 118 Windows CTest tests and INI completeness (262 settings),
conservative defaults, writer (23) and migration (67) checks pass. The new
policy test passes GCC under WSL with C++17 and warnings as errors.

The Release Win32 build passes. A fresh all-Off launch (PID 44144) retained
all 22 original guard windows. The enabled Stock run (PID 24748, DX11) observed
native weapon, scrap and pilot submissions independently reveal on ammo/scrap/
pilot changes, smoothly fade and settle at 25% native alpha. Custom Amber scrap
and Cyan pilot RGB stayed unchanged. All 1,388,097 color-helper calls outside
those scopes matched native results exactly during the 36-second probe.

The enabled Legacy run (PID 43564, DX11) passed the same independent activity
checks, including the reconstructed plates and native text. All 172,200
out-of-scope color calls matched native output, while Amber/Cyan text retained
its RGB. A deliberate `HudFadeWeaponText` expected-byte mismatch (PID 41576)
logged that Contextual HUD stood down; native reads confirmed all 22 new guard
windows remained original, including both helper entrypoints and all draw CALLs.
An earlier Legacy probe attached before initialization due to a stale readiness
line and was discarded; the accepted probes wait for the current PID's readiness.

Menu navigation and weapon Fade Off/On apply/save passed in PID 30056. At the
small test window, long row labels clipped; the final labels use compact names
such as Weapon Idle, Weapon Delay and Weapon Speed. The rebuilt HUD category
and all twelve fading rows fit without clipping in PID 30612. The right-column
Pilot Idle control changed 25% to 50%, reported Applied and saved the correct
INI key. The Release build, all 118 tests and INI checks pass after the label fix.

The Windows deployment verifier confirms the source catalog and absence of
stale patch configuration. Its overall result fails the existing version
precedence check: the development build and installed mod bundle both report
1.0.0.53. No release version was changed for this feature; test launches deploy
the complete current DLL/catalog set, with final artifact hashes checked.

Required follow-up includes weapon selection/loadout,
long missions, save/load, eject/re-enter, resolutions/scales and the full
renderer/store/platform matrix. Multiplayer presentation is unqualified.

Command extension qualification remains partial. Released constructor inspection
establishes ControlPanel's vtable at `0x00877E50`, with render slot 6. Native
ReadProcessMemory PID 34640 matches the full renderer entry, original render
pointer and thirteen-pointer action table. The broader vtable also contains
existing OpenShim lifecycle hooks, so it must not be guarded as a single stock
block.

An enabled command-only GOG DX11 smoke run (PID 43660) installed both the
shared alpha adapters and command render-slot wrapper, and ran the native
command renderer for approximately 30 seconds with two fixture units. The game
exited normally after a separate co-op runner's unscoped foreground watchdog
posted WM_CLOSE. This establishes startup/ABI smoke coverage only; command
alpha values and visual fade/reveal behavior were not observed. The tracing
backend could not attach (VirtualAllocEx access denied).

A fresh command-only guard-refusal run (PID 46716) deliberately mismatched the
deployed renderer guard. OpenShim logged the refusal; native memory reads
matched all three command regions and all 22 shared fade guard windows,
including the original render-slot pointer and both color-helper entrypoints.
The runner restored the original INI, fixture, catalog and window settings.
The final deployed three DLLs and catalog match the current build/source hashes.

Interactive command fade/reveal, Hidden input handling, selection/submenu
pinning and the final sixteen-row Options fit/apply/save checks remain pending
at the user's request. The shared launch harness is occupied by separate co-op
tests, whose watchdog also interferes with foreground validation. No visual
acceptance is inferred from the successful build or smoke run.
Local fixture/probe output is under ignored `bin/command-hud/`.

Local probes/fixtures/logs are ignored under `bin/contextual-hud/`.

## Hull/ammo extension qualification

Released GOG DX11, 2026-10-19: native ReadProcessMemory PID 31232 matched the
meter renderer, six new draw CALLs, two shared ammo sprite CALLs and four value/
weapon accessors before patch authoring. The distinct filled-rect helper was
also inspected statically and matched live PID 48744. An initial installation
attempt used the existing outline-helper alias for cost markers; native CALL
ownership refused those redirects and both meters stayed visible. That run is
not accepted fade evidence. The final catalog binds the actual filled helper.

The final Release Win32 build, all 118 Windows tests, INI completeness (257),
conservative defaults, writer (23), migration (67), and portable policy tests
under WSL GCC C++17 with warnings as errors pass. New policy checks cover
warning thresholds, zero-cost weapons, independent histories and warning-clear
holds. Local fixtures/traces are ignored under `bin/hull-ammo/`.

PID 24852: enabled independent hull/ammo fades reached 25% alpha through smooth
intermediate steps. Current-health and ammo changes revealed their respective
groups; critical hull health stayed visible. Cyan hull and Yellow ammo RGB
remained fixed; ammo count/cost-marker RGB remained native. Weapon draws stayed
at 100% and all 1,200,276 sampled color-helper calls outside the meter scopes
matched native output. The full native renderer continued executing.

PID 48028: Hidden reached zero alpha for hull artwork and all ammo submissions.
At steady critical health, hull remained at 100% while ammo stayed hidden;
setting ammo to zero restored all ammo submissions to 100%. Repair/refill
cleared the warning holds and both groups faded again. The weapon list stayed
at 100%; all 2,167,900 out-of-scope color-helper calls matched native output.

PID 34176: a deliberately mismatched hull-label guard refused the meter group.
Native reads matched all 38 checked fade/shared-ammo source regions, including
both color-helper entrypoints and every new meter CALL. Fresh Off PID 44788
matched the same 38 regions. The test configuration, fixture, catalog and
window settings were restored after each run.

Interactive appearance, final Meter Fading page fit/navigation/apply/
save, warning audio, faction/view/lifecycle variants, multiplayer and the full
store/renderer/platform matrix remain unverified. Previously deferred command
visual checks remain pending as requested. No interactive game test was added
for this extension.

## Cockpit radar extension

Default-off `[Display] RadarHudFade`, `RadarHudIdleOpacity=25`,
`RadarHudFadeDelay=2500`, `RadarHudFadeDuration=500` and
`RadarCompassAlwaysVisible=0` apply live from the five-row Radar Fading page.
The nine-tile hub and existing subpage IDs retain their order. Full cockpit
radar scope includes backdrop, terrain grid, compass, contacts, ping/alert
artwork, native command links and raw diamond markers. Tactical MapRadar and
world target/camera overlays retain their own native rendering.

The released CockpitRadar vtable render slot 6 is independently verified to
point to the guarded renderer before shared helpers install and again before
replacement. The original callback always executes: native eligibility/range
filtering, ping refresh, command presentation, sounds and drawing are retained.
Grid/backdrop/contact palette CALLs have a single cached owner shared by tint
and fade, so either feature may initialize first. The grid multiplies alpha
after tint and restores its original packed color on every exit. Direct diamond
geometry has its own scoped packed-alpha adapter; other sprites and lines use
the existing color helpers. Compass exceptions restore only the surrounding
scope's opacity for that one sprite loop, then restore radar opacity.

Activity reads native presentation state and the current player's explicit
target/radar state, with owner and class checks. It does not sample contact
positions, disclose hidden teams or add an object enumeration. A dedicated
radar CALL after native visibility/range filtering forwards the original
last-hit getter and copies that contact's full handle. A fixed 256-handle
history detects additions independent of order; disappearing contacts do not
restart the hold. Overflow or invalid identities request full visibility.
A native-visible contact's recent-hit window conservatively keeps the radar
visible, including enemy contacts, without reclassifying hidden actual teams.

The whole radar uses one opacity per native render. Contact additions and
recent-hit alerts discovered during drawing reveal the complete next frame,
with at most one render of latency; earlier layers are not left at a different
opacity within that render. Explicit range/mode/target changes and ping state
are sampled before drawing. Active command contexts keep their links visible.
Unreadable fields, missing owner and alternate/touch layout stay fully visible.
Owner, mission, config, native-radar-disable and instance changes clear history.

Released GOG SHA256 and baseline ReadProcessMemory PID 5780, 2026-10-19,
matched the renderer, slot pointer, compass/contact-time/diamond CALLs and
native accessors before authoring patches. Ghidra/xrefs and Capstone establish
ECX self, original float-return conventions and caller cleanup. One raw diamond
CALL belongs to cockpit radar; its caller supplies six stack slots (0x18 cleanup),
which are all forwarded even though the helper uses only five. No private PDB
or decompiler output is committed.

Release Win32 build, all 118 Windows CTest cases, INI completeness (262),
conservative defaults, writer/migration checks, and WSL GCC policy tests pass.
Policy checks cover contact arrival/reappearance, reorder/duplicate/removal
stability, bounded overflow and owner/mission history reset.

Local GOG/DX11 native acceptance on 2026-10-19:

- PID 20856: all observed radar layers reached 25% of their native alpha:
  backdrop, cyan-tinted terrain grid, contacts/lines, compass and 330 raw
  target-diamond draws. Grid packed colors were restored after every draw.
  New native-visible contacts and target changes restored the whole group;
  contact movement alone did not refresh it. Periodic native ping animation
  also revealed the radar, as intended.
- PID 37356: Hidden reached zero alpha on the same paths, including 330 raw
  target-diamond draws. Keep Compass retained native compass alpha throughout.
  No grid-restore mismatches occurred. Across both traces, 760,807 color-helper
  calls outside the radar scope retained their original complete color.
- PID 45552: a deliberately mismatched renderer guard refused radar setup
  before installing shared fade helpers. All 50 checked fade/shared-radar
  code windows plus the native radar slot pointer remained original. The
  deployed catalog was restored after the run.
- PID 38356: fresh all-Off mission startup leaves the same 50 code windows
  plus radar dispatch pointer original. No radar/fade adapters are logged.
  This checks startup behavior, not a long-session or lifecycle qualification.

All four runs shut down through the harness. Temporary INI, Lua and catalog
bytes were restored; all three deployed DLLs and the catalog match this build's
SHA256 hashes, and the harness Ogre backup is removed.

The fixture's script Damage call did not independently qualify recent-hit
alert revelation; native combat-alert timing/appearance and active-command,
range/compact-mode changes remain acceptance work.
Interactive appearance and Radar Fading fit/navigation/apply/save remain pending
under the user's earlier interactive-validation deferral, as do command/meter
visual checks and the broader renderer, store, lifecycle and multiplayer matrix.
Local probes/fixtures/logs are ignored under `bin/radar-fade/`.
