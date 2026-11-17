# Producer badges

`[Gameplay] RtsProducerBadges` (Options > Controls > RTS Commands > Producer Badges, default **off**). While on, every own-team producer that is building something gets a small HUD badge about 40 px above its projected position: the unit name of the item being built (ODF `unitName`, as the rally label shows it) followed by the stock build progress in whole percent, for example `Tank 45%` (rounded down, so 100% shows only on completion). Text rather than a bar, because the command menu already shows a bar for the selected producer. Same panel, colour and HUD text as the producer "Rally" label. Read-only: it writes nothing the game reads, so it also runs in multiplayer. Source: `src/patches/producer_badges.cpp`; pure rules: `include/producer_badges_policy.h` (tests: `tests/producer_badges_policy_tests.cpp`).

## Engine facts (GOG Redux 2.2.301, Ghidra)

- Producer vtables (patches.json rows): `RecyclerVtable` 0x00886454, `FactoryVtable` 0x00879388, `ArmoryVtable` 0x00875CB0, `ConstructionRigVtable` 0x00877994.
- Vtable slot 7 (+0x1C) is the stock build-progress getter, `float __thiscall(this)`, result on x87. `Producer::GetBuildProgress` 0x005AFA10 (Recycler, Factory, Armory) = `buildClass(+0x300) ? 1 - remaining(+0x304) / buildClass->buildTime(class+0x54) : 0`. `ConstructionRig` overrides it with 0x0049CCF0: with `+0x3BC != 0` it uses the class at `+0x370` instead. The badge calls the slot virtually (SEH guarded), clamps to [0, 1] and treats a non-finite value as 0.
- Building: a producer has `*(void**)(obj+0x300) != 0`. A rig has `+0x3BC != 0` (class at +0x370) or `+0x300 != 0` (class at +0x300).
- The class being built is a `GameObjectClass*`; its ODF name is char[8] at class +0x30, not necessarily NUL-terminated. The display name is `KillTicker::LookupUnitName(odf)`, else the ODF name.
- `StartBuild` 0x005AECB0 sets +0x300 and +0x304. Nothing is hooked; the feature polls.
- Object scan: `GameObject::objectList`, as `rts_commands.cpp`. A producer qualifies when its vtable is one of the four, its team (+0x174) is the user object's, its byte +0x80 is not 2 (network replica) and its obj76 (+0xF4) flags (+0x14) lack 0x200 (dead).

## Threading

The scan (about 5 Hz) and the name lookup (reads files, allocates) run on the frame/game thread from the world render tick, into a table of at most 16 badges (handles, ODF, cached label) published under an SRW lock. The HUD painter (`HudGaugeOverlay::Slot::ProducerBadges`, same thread, inside the HUD pass) copies the table, then per frame re-reads the object by handle, its build state, progress and world position under SEH, projects with the camera record, and draws. A badge whose object vanished or went idle is skipped at once and dropped by the next scan. The camera read is a small copy of `producer_rally_points.cpp` ReadCameraProjection (that module binds its camera rows only while it is installed).

## Limits

- At most 16 badges per scan; producers past that show none.
- Needs a gameplay HUD context (user object, no pause menu, no shell screen). A table older than 1 s is not drawn.
- The badge sits a fixed 40 px above the projected object centre, not at the model top.
- Live (2026-11-17): names showed over a building factory and recycler, none over an idle or enemy factory. Progress advanced on a deployed recycler and the badge cleared on completion. A drawn bar was tried first: it rendered but was hard to read on dark hulls, so the percent text replaced it.

## Log lines

`[BADGES] enabled=yes|no` (config load and on change), `[BADGES] installed (attempt N)`, `[BADGES] badge on handle=0x%08X odf=%hs` / `badge off ...`, `[BADGES] progress handle=0x%08X pct=N` (each new quarter; budget 64 per mission, shared), `[BADGES] engine rows did not bind after N attempts; badges inert`, `[BADGES] GetHandle or object list unresolved; badges inert`, `[BADGES] HUD overlay unavailable; badges inert`.
