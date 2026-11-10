# Multi-page mission briefings

OpenShim can show a mission briefing as several pages on the pre-launch
briefing screen (the screen with the mission text, the planet sidebar, the
planet picture or video, and the Launch button). Page 1 is the stock briefing.
For pages 2 and up, add files next to the mission's own `.des`. No Lua, no
mission INI keys and no new asset types are involved.

Setting: `[Features] BriefingPages = 1` in `openshim.ini` (on by default).
The environment variable `OPENSHIM_DISABLE_BRIEFING_PAGES=1` turns it off.
Players without OpenShim, or with the setting off, see page 1 only.

## File names

For a mission whose briefing is `<m>.des` (for example `misn04.des`), page N
(2 to 9) uses:

| File | Required | What it does | If missing |
| --- | --- | --- | --- |
| `<m>_N.des` | yes | Main briefing text for page N | Page N and every later page do not exist |
| `<m>_Np.des` | no | Sidebar text (the planet box under the picture) | Page 1's sidebar stays |
| `<m>_N.ogv` | no | Video in the picture panel; preferred over `.png` | Page 1's picture/video stays |
| `<m>_N.png` | no | Still image in the picture panel | Page 1's picture/video stays |
| `<m>_N.wav` | no | Voice/sound played when the page opens | The page is silent |

Example for `misn04`: `misn04_2.des`, `misn04_2p.des`, `misn04_2.png`,
`misn04_2.wav`, then `misn04_3.des`, and so on.

## Rules and limits

- Pages are counted from 2 upward and stop at the first missing `<m>_N.des`.
  `misn04_2.des` + `misn04_4.des` gives two pages; `_4` is ignored.
- At most 9 pages (`_2` to `_9`).
- Every generated name must fit in 15 characters, so the mission base name
  `<m>` can be at most 8 characters (`<m>_9p.des` is the longest). Longer
  missions stay single-page and the log says why once.
- Text per page: the text box keeps about 10 KB (10,240 bytes, less a 2-byte
  colour prefix and the terminator, so 10,237 characters). Longer text is cut off, as in stock. Lines wrap and
  the box's own scroll arrows still work within a page.
- Text uses the same colour as page 1's text, including a custom mission
  colour from the campaign INI.
- Images and videos fill the same 700x515 panel as the stock planet picture.
  Use the formats the stock panel uses: Theora `.ogv` or `.png`. Put a page's
  voice in `<m>_N.wav`, not in the video (the shim opens the video with no
  separate audio track, like the stock panel). A page video loops or stops the way the stock panel
  treats a video (not checked in game yet).
- Sounds are `.wav`, played on the same channel as the stock briefing sound.
  Changing page stops the current sound first.
- Going back to page 1 restores page 1's text, sidebar and picture, and
  restarts page 1's sound (the last sound the stock screen started, which
  is the planet video's intro sound when one is configured).
- A mission without `<m>_2.des` behaves exactly as before: no buttons, and
  no keys are taken.

## Where the files go

In the same place as the mission's own `.des`: the mod or campaign folder
that the game already loads mission files from (for example the addon
folder of a custom campaign). Keep names flat (no subfolders) and
lower-case like the stock files.

## Controls

- Up-arrow / down-arrow buttons to the right of the picture panel go to the
  previous / next page. The previous button is hidden on page 1 and the next
  button on the last page; there is no wraparound.
- Left or Page Up: previous page. Right or Page Down: next page.

## Not covered yet

- The mission archive screen (Single Player > Archive) still shows page 1
  only. That screen is a separate function in the game and is a follow-up.
- No "page i of n" label.

## Troubleshooting

`openshim.log` lines start with `[BRIEFPAGES]`:

- `<m>: N pages` - the extra pages were found.
- `<m>: name too long ...` - shorten the mission name to 8 characters.
- `briefing pages hooks installed` / `... detour failed ...` - whether the
  feature could attach to this game build. Unknown builds stay stock.
