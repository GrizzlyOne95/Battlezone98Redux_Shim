# Multi-page briefings on the pre-launch briefing screen (2026-11-10)

Build: GOG Redux 2.2.301. `D/` = the decomps dir
`Battlezone_Source/BZ1/Redux/openshim_re_corpus/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/`.
`asm 0x...` = disassembly of the shipping GOG exe. Claims without either are
marked UNVERIFIED. Not live-tested. Feature code: `src/patches/briefing_pages.cpp`,
policy `include/briefing_pages_policy.h`, guide `docs/BRIEFING_PAGES.md`.

## The screen

- cUI_Mission ctor is `FUN_0078f030`, thiscall(this, manager, std::string by
  value), `ret 0x1C` (asm 0x0078F030 epilogue). It stores `this` in
  `0x0094552C` (`D/FUN_0078f030:57`, asm 0x0078F131); the dtor body
  `FUN_00790a20` clears it (`D/FUN_00790a20:17`, asm 0x00790A5E). The shim treats
  "singleton == the screen we built" as the liveness test instead of hooking
  the dtor.
- Mission text: the ctor loads it with the description loader `FUN_004889c0`
  (`D/FUN_0078f030:251`, asm 0x0078FB8A), builds the scrolling Mission block
  `FUN_007cd8d0` (`D/FUN_0078f030:303`) and keeps it at this+0x15C and
  `0x00945530` (`D/FUN_0078f030:307`, asm 0x0078FDD1..0x0078FDE3). Rect
  904,119,416,837 (asm 0x0078FD5A..0x0078FD91 float constants).
- Planet sidebar: second and last direct loader call (`D/FUN_0078f030:339`,
  asm 0x0078FEE7), text block `FUN_007ccb70` named "Planet" (`D/FUN_0078f030:349`),
  held only in a local and added to Middle_Overlay (asm 0x00790005). The shim
  finds it by name under Middle_Overlay.
- Colour: the ctor sets the text through SetText(text, colourIndex) and then,
  for custom campaign colours, `FUN_007ccd20(rgb)` (`D/FUN_0078f030:382-384`,
  asm 0x00790081..0x007900CA).
- Media: the stock "movie" cUI_View (`D/FUN_0078f030:391`; rect 100,95,700,515,
  flags 0x20, asm before 0x00790996) is set either by `FUN_007d3850(ogv, audio)`
  plus `FUN_007d3dd0(true)` (`D/FUN_0078f030:672-673`) or by SetTextureOff
  0x007D2870 for a png (asm, default branch). Added to the overlay at the end
  of the ctor (`D/FUN_0078f030:677`).
- Sound: `FUN_0078ef60(wav)` stops the handle at +0x160 and starts a new one
  (`D/FUN_0078ef60:11-17`); all callers are inside the ctor (`D/FUN_0078f030:406`
  .. `:662`). `FUN_0078efe0` stops and zeroes it (`D/FUN_0078efe0:5-8`).
- Keys: `FUN_00790aa0` handles only Escape (`D/FUN_00790aa0:5-8`), so
  Left/Right/PgUp/PgDn are free on this screen. That the key argument is a
  Win32 VK code: UNVERIFIED beyond 0x1B = VK_ESCAPE and the 0x26/0x28 compares
  in the sibling handler 0x0079CD40 (asm). Whether slot 5 fires on press or
  release, and on auto-repeat: UNVERIFIED.

## Text blocks

- `FUN_007ccd50` (TextBlock SetText) writes `"%<colourIndex><text>"` into
  this+0x144 with a 0x2800 cap (`D/FUN_007ccd50:5`). That cap is the ~10 KB
  per-page limit in the guide. The colour index comes from `FUN_00489670`,
  which returns 0..4 (asm 0x00489670..0x004897BA), so the prefix is one digit.
- `FUN_007ce0b0` (ScrollingTextBlock SetText) zeroes the scroll at +0x2958
  then calls `FUN_007ccd50` (`D/FUN_007ce0b0:5`, asm 0x007CE0BA..0x007CE0CF).
- `FUN_007ccd20` replaces the low 24 bits of +0x100 (`D/FUN_007ccd20:5`).
- So page 1's colour is restored by reading the one-digit index from
  this+0x144 and the RGB from this+0x100 after the ctor, calling SetText with
  that index and then `FUN_007ccd20(rgb)`. That the reflow `0x007CCFC0` leaves
  +0x144 unmodified: UNVERIFIED beyond asm 0x007CD13A..0x007CD143 (it copies
  +0x144 into a std::string).
- Scroll arrows: `FUN_007cd8d0` builds 30x35 buttons (`D/FUN_007cd8d0:41`,
  sizes at 0x008A293C/0x008A2950) with `operator_new(0x1ec)`
  (`D/FUN_007cd8d0:46,82`) and the uparr*/dnarr* textures
  (`D/FUN_007cd8d0:66-68,102-104`). The page buttons reuse that art and size.

## Description loader

- `FUN_004889c0(name, buffer)`, cdecl: cuts the name at the first '.' and
  appends ".des" (asm 0x00488AD2), caps the copy at 0x1F400 bytes
  (`D/FUN_004889c0:62-63,83-84`), or writes "NO DESCRIPTION"
  (`D/FUN_004889c0:93`). Buffers passed by the shim are 0x1F401 bytes. Reads up
  to 0xF6 bytes of the name (asm); the shim passes a zeroed 256-byte copy.
- Language-variant lookup when `0x004344A0()==2` (asm): page files inherit it.
  Whether translators can ship `<m>_N` variants the same way: UNVERIFIED.

## Resource existence

- `.des`/`.wav`: `FUN_00481a60` (resolve `Music::ResourceSize`) returns 0 when
  absent (asm 0x00481A80, 0x0082919F). Its fallback copies the name into a
  0x14-byte local (asm 0x00829163..0x0082916B); the 15-character name limit is
  a conservative reading of that. Exact limit: UNVERIFIED.
- `.png`/`.ogv`: Ogre `ResourceGroupManager::resourceExistsInAnyGroup`, since
  both are loaded through Ogre. That every place the game's index finds a
  file is also an Ogre group (and the reverse): UNVERIFIED.

## Hooks (patches.json engine_addresses)

| Row | Address | Patch |
| --- | --- | --- |
| BriefingScreenCtor | 0x0078F030 | 10-byte entry detour |
| DescriptionFileLoad | 0x004889C0 | 10-byte entry detour |
| BriefingScreenPlayWav | 0x0078EF60 | 11-byte entry detour |
| BriefingScreenOnKey | 0x00790AA0 | 11-byte entry detour |
| BriefingScreenStopWav, ScrollingTextBlockSetText, TextBlockSetText, UiTextBlockSetColour, UiViewLoadMovie, UiViewPlayMovie | | called only |
| BriefingScreenSingleton | 0x0094552C | data |

`PlanetVideo::MissionIntroSound` scans for the stock prologue of 0x0078EF60;
the installer resolves it (cached) before patching that prologue.

## Page-1 capture

While the ctor runs (between entry and return of the ctor detour):
loader call 0 = mission text and mission base name, call 1 = planet text;
the last play-wav call on this screen = page 1's wav. If a future build
inserted another loader call between them, call 1 would be wrong: the rows'
guard bytes cover the entries only, not the call order (UNVERIFIED for any
build but 2.2.301).

## Widgets

Two cUI_Views (`BriefPgImage`, `BriefPgMovie`, same rect as "movie") and two
buttons (`BriefPgPrev`, `BriefPgNext` at 805,540 and 805,575) are allocated
with MSVCR120 `operator new` and added to Middle_Overlay, like the stock
widgets. That the overlay frees its children on teardown is assumed from the
stock pattern (stock arrows/movie are never deleted by the ctor's owner):
UNVERIFIED. A video left playing in the hidden `BriefPgMovie` view keeps
decoding until the screen closes (UNVERIFIED cost). It is opened with a null audio name, as the stock default
branch does; whether embedded Theora audio would play: UNVERIFIED.

## Follow-up

- Mission archive screen `FUN_00790fe0`: same blocks, separate function; not
  covered.
