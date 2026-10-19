# Contextual HUD fading

Default-off local presentation controls for the released GOG 2.2.301 game.
OpenShim Options → HUD → HUD Fading contains independent controls for the
weapon list, scrap meter, pilot meter and command interface. Existing colors,
Stock/Legacy layout, native scaling, text, alignment, backplates and gameplay
remain as selected.

## Controls and behavior

All sixteen keys are in `[Display]` and apply live. For each prefix
`WeaponList`, `ScrapHud`, `PilotHud` and `CommandHud`:

| Suffix | Default | Menu | INI range |
| --- | --- | --- | --- |
| `Fade` | 0 | Off / On | boolean |
| `IdleOpacity` | 25 | Hidden / 25% / 50% / 75% | 0–100 percent |
| `FadeDelay` | 2500 | 1 / 2.5 / 5 seconds | 0–30000 ms |
| `FadeDuration` | 500 | Instant / Fast / Normal / Slow | 0–5000 ms |

Fast/Normal/Slow are 200/500/1000 ms. Invalid values use the defaults.
`CommandHudIdleOpacity` defaults to 0 (Hidden), rather than 25. All four Fade
switches still default Off. Compact Cmd rows describe the command controls.
Opacity multiplies native alpha; existing dimming/transparency and RGB are preserved.
Disabled groups remain fully native. A fresh all-Off launch installs no new
adapters. Once installed, Off forwards native colors without removing detours.

Each group starts fully visible, holds for its own delay and eases smoothly
toward its own idle opacity. Relevant changes restore full opacity immediately:

- Weapons: selected mask, available/linkable mask, hardpoint loadout, or ammo.
  Firing, spending or replenishing ammo therefore keeps/reveals the list.
- Scrap: current scrap or maximum capacity.
- Pilots: current available pilots or maximum capacity.
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
Hull/ammo bars, reticle, radar and objectives are outside the scopes.
This initial batch does not add fading for those groups.

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
All 118 Windows CTest tests and INI completeness (249 settings),
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
