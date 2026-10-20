# Remaining native HUD elements

Research checkpoint: 2026-10-19. The subsequent hull/ammo and cockpit-radar fade implementations
and their acceptance are tracked in [CONTEXTUAL_HUD.md](CONTEXTUAL_HUD.md); the
inventory below records the original research candidates. The map itself adds
no hooks, settings or enabled capabilities. Implemented fades now cover weapons,
scrap, pilots, commands, cockpit hull/ammo and radar; their acceptance remains separate
from the static candidates below.

## Evidence boundary

All addresses below refer to the released GOG 2.2.301 executable, SHA-256
`8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413`.
The installed file hash agrees with the Ghidra program
`/battlezone98redux.exe-007c64`. Ghidra decompilation, xrefs, released RTTI,
vtable bytes and independent PE/Capstone reads establish this static map.
No private PDB/corpus material or decompiler output is included here.
An independent PE check verifies all twelve listed dispatch slots, twenty-three
direct CALL targets and their document addresses. Local checks/output remain
ignored under `bin/hud-element-map/`.

These are research candidates, not qualified patch sites. No game was launched
for this investigation; no new live byte, ABI, input or visual acceptance is
claimed. Prior palette/feedback/fade captures qualify only the sites and
behaviors identified in their own documents. Steam, Wine/Proton, renderer
variants and lifecycle transitions remain separate qualification work.

Before implementing a candidate, capture its settled native bytes, establish
the exact calling convention and ownership, then add guarded named rows to
`scripts/patches.json`. Do not copy these addresses into feature code. Preserve
native rendering callbacks even at zero alpha: several also update gameplay
presentation state, inputs, timers, warnings or sounds.

## Inventory

Slots are zero-based, with a four-byte pointer stride. A vtable slot identifies
a candidate ownership boundary; it is not automatically an appropriate hook.

| Visible group | Released draw owner / entry | Dispatch evidence | Fade readiness |
| --- | --- | --- | --- |
| Player hull and ammo, labels, remaining shots and shot-cost marker; also weapon list | StatusDisplay `0x005DC300` | vtable `0x008882C8`, slot 6 at `0x008882E0` | Best next group; isolate hull/ammo submissions from the already independent weapon list. |
| Radar backdrop, terrain grid, contacts, alerts, command links and compass letters | CockpitRadar `0x00493EC0` | vtable `0x008770AC`, slot 6 at `0x008770C4` | Composite; grid has a direct geometry path beyond current fade helpers. |
| Target/selection/object brackets, names, range, offscreen carets and vertical health art | SelectionDisplay `0x00497AA0` | vtable `0x008772BC`, slot 6 at `0x008772D4` | Distinct from command rows and from the aiming reticle; some primitives bypass existing alpha helpers. |
| Objective text panel and object-information panel | InfoDisplay `0x004F31D0` | vtable `0x0087B014`, slot 6 at `0x0087B02C` | Separate semantic branches; native objective visibility already has a duration/toggle. |
| Mission timer title, digits, colons and plate | CockpitTimer `0x0049A3B0` | vtable `0x008773B8`, slot 6 at `0x008773D0` | Distinct 2D group; every second is a value change, so ordinary change-based idle policy would prevent fading. |
| Main aiming reticle and weapon-lock side markers | Reticle HUD callback `0x005BC170` | vtable `0x00886B28`, slot 9 at `0x00886B4C` | Main CALL already owned by feedback; compose with that adapter rather than redirect it again. |
| Projected/3D aiming and targeting geometry | Reticle `0x005BABB0` | same vtable, slot 8 at `0x00886B48` | Separate viewport-argument render path; 2D-only fading would leave it behind. |
| Target-camera inset: live scene, target label, frame and underlay | TargetCam `0x005DDE00` | vtable `0x008884B0`, slot 6 at `0x008884C8`; also called by `0x005DDDC0` | Requires scene/pane composition; fading only the frame/text would leave the live image visible. |
| Tactical/map radar | MapRadar `0x0050D6F0` | vtable `0x0087D604`, slot 6 at `0x0087D61C` | Separate from cockpit radar, with terrain polygons, pointer interaction and command links. |
| Chat and local DisplayMessage output | text-panel renderer `0x008216C0` | direct CALL `0x00617673` in `0x00617600` | Existing per-line lifetime/scroll behavior; must scope the specific chat panel rather than all panels. |
| Active chat entry and caret | text-entry renderer `0x00823D30` | direct CALL `0x00617678` in the same overlay pass | Separate from expiring message lines; keep visible while typing. |
| Multiplayer table overlay | `0x00627B80`, row builder `0x00626BE0` | direct CALL `0x0061767D` in the same overlay pass | Tabulated header/colored rows mapped; exact score/player-list mode coverage still needs live identification. |
| Native FPS/debug readout and plate | `0x00617E70`, measurement/formatting `0x00617B20` | direct CALL `0x0061766E` in the same overlay pass | Diagnostic display, independent of player status/reticle; measurement also logs performance transitions. |
| Construction preview | ConstructionDisplay `0x0049C3E0` | vtable `0x00877900`, slot 8 at `0x00877920` | Projected/3D path, viewport argument; consumes/reset preview state while drawing. |
| World flag markers | FlagDisplay `0x004D1C80` | vtable `0x00879984`, slot 8 at `0x008799A4` | World-projected sprite submission; separate multiplayer/visibility acceptance needed. |
| Tactical/editor paths and overlays | PathDisplay `0x00594CA0` | vtable `0x00885540`, slot 6 at `0x00885558` | Composite editor/tactical output; subordinate draws need further separation. |

## Player hull and ammo

`0x005DC300` renders weapons first, then hull, ammo, remaining-shot text and
the small shot-cost marker. Wrapping its entire callback would merge three
independent groups. Keep the existing weapon scope and add separate hull/ammo
submission scopes, restoring the pane after each native clipped fill.

Released direct CALLs inside this renderer:

| CALL address | Submission |
| --- | --- |
| `0x005DC843` | Weapon plate; already scoped by weapon fading. |
| `0x005DCAB5` / `0x005DCB37` | Weapon icon / name; already scoped. |
| `0x005DCDF4` / `0x005DCEF5` | Hull label / pane-clipped hull fill. |
| `0x005DD0C4` / `0x005DD1C5` | Ammo label / pane-clipped ammo fill; already owned by palette wrappers. |
| `0x005DD2F8` | Remaining-shot count text. |
| `0x005DD3EE`, `0x005DD41E`, `0x005DD44E` | Three small filled rectangles composing the shot-cost marker. |

The sized-sprite target is `0x0068CA30`, font target `0x00689D10` and filled
rectangle target `0x0068AF70`. Native art initialization includes `hull_bar`,
`ammo_bar`, `hulltext`, `shulltext`, `ammotext` and `sammotext`.
StatusDisplay's update callback `0x005DBEA0` smooths displayed hull/ammo ratios
into instance fields `+0x18` / `+0x24`. Its render callback also triggers native
low-hull and insufficient-ammo warnings. Those callbacks must keep executing.

Recommended follow-up: reveal hull on confirmed health/capacity change and
ammo on spending/refill/capacity or weapon-selection change. Pin warnings
visible at the native critical thresholds. Sample semantic values rather than
resetting the hold on every interpolation step. Keep font color, native
smoothing, marker position, Stock/faction art and palette preferences intact.
The dormant geometry provider in [NATIVE_HUD_LAYOUT.md](NATIVE_HUD_LAYOUT.md)
does not become qualified merely because these draw calls are mapped.

## Radar and compass

The actual CockpitRadar render entry is `0x00493EC0`; `0x0049405B`, mentioned
in older layout notes, is a CALL inside it to the layout builder.
The renderer calls backdrop `0x00493D40` at `0x00494069` and terrain-grid draw
`0x00493E60` at `0x00494074`. The latter calls grid submitter `0x0043FB30`
at the existing palette site `0x00493E9C`.

Compass E/N/W/S sprites are part of this same radar callback, not a separate
compass class. Initialization `0x004930E0` resolves `compas_E`, `compas_N`,
`compas_W`, `compas_S` through the table at `0x008E7734`; the draw loop reads
the resolved IDs at `0x008E7738` with stride eight. Its shared sprite CALL is
`0x004944D0`. This provides a narrow candidate for independent compass tint
or opacity without affecting contacts.

The terrain-grid submitter consumes its packed color directly at grid
`+0x20018` and calls line-strip submitter `0x00687340`. This bypasses the
mode-to-color helpers used by current fades. A complete radar fade must
compose opacity with the existing grid palette scope as well as backdrop,
contacts, lines, ping/alert icons and compass. Never skip the renderer: it
updates ping animation and emits `ping.wav` / under-attack growls.

Possible reveal events are explicit radar interaction/mode change, a newly
visible contact, target change and native alerts. Using moving contact
positions or the rotating compass as an activity fingerprint would keep the
radar permanently awake. Preserve the native visibility/disguise policy;
activity detection must not discover hidden objects or actual hidden teams.
Whether alerts pin the entire radar or only their own layer is a policy choice
still to be made. Tactical MapRadar is a separate lane, not covered by this
cockpit boundary.

## Targeting, objectives and messages

SelectionDisplay initialization `0x004979A0` resolves `object.W`, `select.W`,
`target.W`, four `caret_*.W` sprites and the baked `grnbar`/`yelbar`/`redbar`
health art. Its renderer distinguishes explicit target, native selection and
recent-player-hit visibility (a two-second window from `0x00497890`). Native
visibility remains authoritative. Screen position/range changes are poor idle
triggers because normal movement changes them continuously. A future target
fade should distinguish explicit targeting, recent hit and passive labels.

Not all selection drawing reaches current fade helpers: circle generation
`0x0068AD00` submits direct colored vertices via `0x00687550`. A callback-wide
alpha scope alone therefore cannot be assumed to hide every bracket/circle.
Baked RGB health sprites can still have alpha multiplied; recoloring their
painted green/yellow/red art is a separate problem already tracked in
[HUD_PALETTE.md](HUD_PALETTE.md).

InfoDisplay owns both the objective list and object-information text, with
separate branches for instance `+0x120` (current object) and objective expiry
at `+0xFC`. Native objective add/clear wrappers `0x004F6AB0` / `0x004F6AA0`
lead to `0x004F39B0` / `0x004F3920`. Addition updates the expiry from the
supplied duration. The renderer also calls tutorial-text path `0x004F47C0`,
which can preempt the normal panel. Fade policies must separate these uses;
the native objective toggle and durations should remain effective. The
existing ten-objective capacity limit is unchanged.

DisplayMessage reaches formatted output `0x0056FCB0`, then message routing
`0x00624550`. That appends to the native panel at `0x00920168` through
`0x00821390` / `0x00821450`, and also to the newer UI chat history through
`0x007A47B0`. Native initialization `0x00624210` sets a 30-second panel-line
lifetime. Renderer `0x008216C0` traverses all text panels, updates scrolling
and line expiry, and draws shadow/foreground at `0x008219AA` / `0x008219EB`.
Fading every call to this shared renderer would affect unrelated panels;
identify the chat panel and preserve the separate history/entry UI. New lines
and active typing are sensible reveal/pin events. Reducing message duration is
already distinct from smoothly fading its final alpha.

The same overlay pass calls the independent text-entry renderer, multiplayer
table and FPS readout listed above. Text entry traverses a different panel
list and draws its own caret. The multiplayer builder supplies a tab-separated
header at `0x00920C08` and rows counted by `0x00920178`; exact modes and live
appearance are still unqualified. These are not children of InfoDisplay.

## Reticle, inset and transient output

The main aiming sprite CALL `0x005BC339` is already redirected by
`hud_feedback.cpp`. That wrapper also draws hit markers and incoming-damage
arcs. A fade applied around the entire wrapper would inadvertently fade those
warnings too. Scope a future main-reticle preference to the intended native or
custom reticle primitives and decide weapon-lock visibility independently.
Reticle slot 8 (`0x005BABB0`) submits projected/3D sprites and geometry through
different helpers; slot 9 (`0x005BC170`) draws the screen HUD sprite and lock
side markers. Do not treat those two callbacks as interchangeable.

TargetCam switches camera/pane state, clears and renders a separate scene,
draws a target name, then its frame and `targetunderlay`/`stargetunderlay`.
The direct clear/scene output will not fade with sprite/text alpha. A complete
inset fade needs a qualified composition layer; simply reducing frame alpha
is incomplete. Construction previews likewise use projected/3D helpers and
reset their pending preview after rendering, so their callback cannot be
skipped to hide visuals.

Hit-marker pulses and incoming-damage arcs already expire independently.
CockpitTimer should remain visible when mission-critical or deliberately
shown; its ticking number is not meaningful user activity. Physical cockpit
meshes, sniper-camera overlays, detailed score/player-list modes, newer UI widgets
and mission-owned EXU/Ogre overlays need their own ownership investigation;
this stock-display map does not claim their complete draw coverage.

## Suggested implementation order and acceptance

1. Hull/ammo: finish the two narrow groups within the existing status adapter,
   retaining warnings, palette scopes, pane restoration and weapon independence.
2. Compass: one narrow native sprite loop; optional separate tint/opacity can
   precede a complete radar fade.
3. Radar: qualify the direct grid path and all contact/alert layers before
   promising that the whole widget fades together.
4. Optional target labels/objectives/chat: establish separate visibility
   policies and per-panel ownership first; retain native controls and expiry.
5. Target-camera/3D overlays: investigate composition and render-state lifetime
   before exposing controls.

Each implementation needs fresh Off-byte preservation, guard refusal, scoped
alpha/RGB preservation and unrelated-draw checks, plus live input/reveal,
warning pinning, faction/layout variants, UI scales, camera/vehicle changes,
save/load and mission reset. Existing command fade/reveal and final sixteen-row
Options acceptance remain pending as requested; this static investigation does
not resolve them. Additional options should use another compact page instead
of overfilling the current sixteen-row Fading page.
