# Options UI localization

The OpenShim options screens follow the game's selected language, the same
way the stock menus do. The text is in
`resources/localization/openshim_localization.csv`. That file is built into
the plugin DLL. English always comes from the C++ source, and any missing
translation shows English, never a blank.

## For translators

1. Open `resources/localization/openshim_localization.csv` in an editor that
   can save **ANSI**, such as Notepad++ (Encoding → Character sets) or VS
   Code ("Save with Encoding"):
   - Western European columns use **Windows-1252**.
   - The **Russian** column uses **Windows-1251**. This matches the stock
     `localization_table.csv`: the game loads the Cyrillic font sheet
     (`bzfont_ru.st`) only in Russian, and it draws cp1251 bytes.
   - Do not save the file as UTF-8. The game would show UTF-8 as mojibake.
   - Spreadsheet programs re-encode and re-quote the file, so avoid them.
2. Each line is `Key~English~French~German~Spanish~Italian~Russian~Portuguese`.
   Fill the cell for your language and leave the others alone.
   - Never use a `~` inside text.
   - Keep each entry on one line.
   - Keep `%s` where the English has it; OpenShim puts a name or a reason
     there.
3. To test without rebuilding, copy the edited file next to `openshim.ini` as
   `openshim_localization.csv`, then restart the game. A loose copy replaces
   the built-in one entirely. Remove the copy when you are done.
4. Choose the language in the game's own options. OpenShim follows that
   choice; if none is set, it follows the system language, as the engine
   does. The options log in `openshim.log` shows which language is in use:
   `[SETTINGSUI] Options text language 7 (Russian)` and
   `[SETTINGSUI] Localization table (...): N keys`.
5. Send the file back as a pull request or attachment. Only the translated
   cells need to change.

A cell left empty shows English. There is no need to copy the English into
it.

## Keys

The C++ code names every string; translators never invent keys.

| Key | Text |
| --- | --- |
| `openshim_opt:<IniKey>:label` / `:desc` | A settings row's label and hover description. The row is named by its `openshim.ini` key, which is never renamed. A row without a key (an action row) is named by the letters and digits of its English label, for example `ResetCareerStats`. |
| `openshim_value:<English>` | Shared wording for value labels such as `On`, `Stock` or `50%`. One translation covers every row that uses that wording. |
| `openshim_opt:<IniKey>:value:<iniValue>` | Optional: one row's own wording for one value, named by the ini value it writes. It overrides the shared key for that row only. Add it by hand when a language needs different wording in one place; the sync script keeps it. |
| `openshim_cat:<Name>:name` / `:title` / `:blurb` | A category tile name, its page title and its hub description. |
| `openshim_ui:row:<Label>:label` / `:desc` | Rows that open a sub-page, such as Key Bindings or HUD Colors. |
| `openshim_ui:<name>` | Every other string on the screens: Back, status messages, preview captions and the OpenShim Options button. |

## For developers

- The English text stays in C++:
  - `src/patches/bzr_options_registry.inc`: the settings rows and value
    labels.
  - `src/patches/bzr_options_categories.inc`: categories and sub-page rows.
  - `ShimText("openshim_ui:<name>", "English")` and
    `ShimFormat(...)` calls in `bzr_options_ui.cpp`: other strings.
- After changing any of that, run `python scripts/sync_options_localization.py`.
  It rewrites the English column, keeps every translation whose key still
  exists, and drops keys that no longer exist (it prints each one it drops).
- CTest runs two checks:
  - `options_ui_l10n_sync_check` fails when the table is stale.
  - `options_ui_l10n_tests` parses the shipped table, checks every row,
    value, category and sub-page key, and checks the fallback rules.
- Write each `ShimText` or `ShimFormat` call with its key and English on one
  line, as string literals. The script finds strings by searching for those
  literals.
- Lookups by English text stay English:
  - matching category rows by label (`FindShimSettingByLabel`),
  - ini writes,
  - log lines.

  Only the displayed text is translated.
- `.gitattributes` marks the table `-text`, so Git never converts its line
  endings or encoding.

### Not covered yet

- The key-binding editor's command names (`kFriendlyLabels` and labels
  title-cased from `input.map`).
- "Unavailable" reasons reported by other modules (HUD feedback, contextual
  HUD, palette, assets).
- Updater status text and the runtime summary line.
- CR's `PersistentConfig.lua` pages.

## Why OpenShim keeps its own table

The engine has a localization lookup, but it is a poor fit for addon text:

- Its loader (`FUN_0081C650` in the GOG exe) reads a single
  `localization_table.csv`. An addon that ships its own copy replaces the
  stock table instead of extending it.
- Its lookup (`FUN_0081CB40(namespace, key)`) hashes `namespace:key` with
  FNV-1a and indexes the row by language. A miss stores and returns
  `{ namespace | key }`, so missing text would show as braces rather than
  English.

So OpenShim reads its own table in the same format and only asks the engine
for the language. The engine's getter `FUN_0081DEE0` is a cdecl `int()`:

- It returns 1–7 in the order English, French, German, Spanish, Italian,
  Portuguese, Russian.
- It reads the `play_options` language at `[0x0094672C]+0x4C`. When that is
  unset, it maps the system LCID through `FUN_00437380`.
- The loader swaps the file's last two columns, which is why the file order
  (Russian, then Portuguese) differs from the numbering.

The getter is bound through the `GameLanguageGet` row in
`scripts/patches.json`. That row checks the function's prologue bytes. If
they do not match, the bind fails closed and the screens stay in English.

OpenShim reads the language on every draw, so a change in the game's options
takes effect the next time the page is built. It loads the table once per
process, so the cell pointers stay valid; edits to a loose file need a
restart. The text is drawn with the game's global UI font, so Russian uses
the same cp1251 font sheet as the stock menus.
