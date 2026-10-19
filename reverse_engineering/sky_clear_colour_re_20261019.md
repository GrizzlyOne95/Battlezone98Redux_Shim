# Sky clear colour: where the pale band under a custom sky comes from (2026-10-19)

## Question

Under a custom sky (for example CR misn18's `CR18/StormSwirl` sky plane with the
stock dome hidden), a hard pale band shows at or below the horizon wherever no
sky geometry draws. What paints it, and what is the supported way for a mission
to change it?

## Answer

The band is the game viewports' **clear colour**. The per-frame sky pass sets
it every frame from the terrain's stored **TRN fog colour**: three bytes the TRN
loader writes from `[Color] FogColor`, falling back to a palette/luma default.
`exu.SetFog` stubs the engine's own fog setter and moves only the Ogre fog, so
after a scripted fog change the clear still shows the TRN colour. That mismatch
is the band.

Two supported fixes:

- **Static, no code:** set `[Color] FogColor = "r g b"` (0..255) in the mission's
  TRN to the custom sky's horizon colour.
- **Scripted:** `exu.SetSkyClearColor(r, g, b)` / `exu.GetSkyClearColor()` /
  `exu.ResetSkyClearColor()` (EXU, see "Implementation"). The call writes the same
  three bytes the TRN key would. Call it next to `exu.SetFog` with the same colour.

Recommendation: use the EXU API for missions that change sky or fog from Lua;
use the TRN key for maps whose sky is fixed. A skybox bottom face or a
downward-facing second sky surface also hides the band, but each needs its own
material and assets. Either one draws inside the fog volume, so its colour still
has to match the fog. The clear colour costs three bytes and covers every case.

## Build identity

GOG `battlezone98redux.exe`, sha256
`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`.
In `.text`, file offset + 0x400C00 = VA. Every address below was read from this
exe. The leaked PDB was not used as evidence.

## Storage (written by the TRN loader)

| Global | VA | Layout | Source |
|---|---|---|---|
| TRN fog colour | `0x02CD9120` | 3 bytes R, G, B | `[Color] FogColor`, else palette/luma default |
| TRN sky colour | `0x02CD5108` | 3 bytes R, G, B | `[Color] SkyColor`, else palette entry 223 |
| Sky texture name | `0x02A13D94` | char buffer | TRN sky texture; empty = untextured sky |

How the TRN loader `0x00780160` fills these:

- It is reached from the terrain-load paths `0x004FC020` and `0x004FC490`, on every
  terrain load.
- It zeroes both colours, then fills them from the palette:
  - With `FogDirection == 0`, both take palette entry 0.
  - Otherwise SkyColor takes palette byte offset 0x29D (entry 223). FogColor takes
    the palette entry the luma table's byte 0xDF selects, falling back to SkyColor.
- Finally it applies the `FogColor` / `SkyColor` "r g b" keys when present.

Because every terrain load rewrites these bytes, an override never outlives the
mission.

## Per-frame consumers

- **Sky pass `0x00616500`** (called from the main view `0x006176A0` and the PIP
  view `0x005DDE00`):
  - `0x00616521..0x0061656C` reads the three fog-colour bytes, divides each by
    255.0, and calls the clear-colour setter `0x0067CA70`. That setter calls
    `Ogre::Viewport::setBackgroundColour` on the game viewports held at
    `[0x00920EA0]+0x1C/+0x20/+0x24`.
  - When the sky texture name is empty and SkyColor differs from FogColor, the
    pass also draws SkyColor bands that fade to the fog colour (`0x00615C30` /
    `0x00615830` → `0x00685740`).
- **Cloud/sky-band vertex fade** `0x00685740` / `0x00685A40` blends vertex
  colours toward the fog colour.
- **PIP view** `0x005DDE00` fills a rectangle with the fog colour.

## Other clear-colour writers (none override the sky pass in normal play)

- `0x0067CA70(0,0,0)` (black) from `0x004341C0`, `0x005D4690`, `0x00617110` and
  `0x00618370`: shell, transition and special views.
- `0x007C76D0` and `0x007C7820` use a 0.1 grey.
- `0x0067CB10` sets the main viewport only. `0x006176A0` calls it in view modes
  3, 9 and 10.
- `0x0067CB70` sets viewport +0x24, called from `0x007AA000`.
- Some viewports get a fixed colour when created: black at `0x006658B0`, white at
  `0x00682540`, and the black scope viewport at `0x007A9590`.

## Fog (why `exu.SetFog` leaves the band)

The engine's fog applier is `0x00780800(viewMode)`:

- It calls `0x00683370(fogColour/255, start, end*1.5)`, which calls
  `SceneManager::setFog` and caches the colour at `0x025F8EA8`.
- It runs only when the view mode changes: `0x00780C70` compares `0x008EAAD8`
  with `0x009454BC`.
- It is also called from `0x00618370`, `0x0077EA10` and `0x004C82D0(10)`.

`exu.SetFog` sets Ogre fog directly and patches `0x00683370` to `RET`, so a
view-mode change cannot undo the script's fog. Nothing writes `0x02CD9120`, so
the sky pass keeps clearing to the TRN colour.

## Signatures

- **Sky-pass clear site**, `0x00616521`, 80 bytes, unique in `.text`. It covers
  everything from the first fog-byte read to the setter call:

  ```
  0F B6 05 22 91 CD 02 F3 0F 2A C0 F3 0F 5E 05 00 2B 8A 00 51 F3 0F 11 04 24
  0F B6 0D 21 91 CD 02 F3 0F 2A C1 F3 0F 5E 05 00 2B 8A 00 51 F3 0F 11 04 24
  0F B6 15 20 91 CD 02 F3 0F 2A C2 F3 0F 5E 05 00 2B 8A 00 51 F3 0F 11 04 24
  E8 FF 64 06 00
  ```

  The three `movzx` reads also appear on their own in the fog applier at
  `0x0078096F`. The trailing `call 0x0067CA70` is what makes the 80-byte form
  unique.
- **Reference pattern**, 30 bytes at `0x00616553`, unique. EXU's catalog records
  it for `TrnFogColor`.

## Implementation (EXU)

In EXU `src/Game/EnvironmentSky.cpp`, catalog entries `Environment.TrnFogColor`
and `Environment.SkyPassClearColour`:

- **Fail closed.** `RuntimeGate::IsSupported()` must pass and the 80-byte pattern
  must match at `0x00616521`. Otherwise `SetSkyClearColor` returns `false`, and
  `GetSkyClearColor` returns `nil`. Reads and writes are SEH-guarded.
- **Set** takes `r, g, b` or a colour table, each channel in 0..1. It stores the
  colour as bytes (1/255 steps), keeps the first original value, and returns
  `true`.
- **Reset**, and closing the Lua state, put the original back, but only while
  the bytes still hold the written value. After a terrain load the bytes belong
  to the new TRN.
- No OpenShim code patch is needed, and nothing in the engine's code is
  modified.

Side effects, identical to the TRN key:

- The engine's cloud and sky-band fade blends toward the new colour.
- Unless `exu.SetFog` has taken over fog, the next view-mode change applies the
  new colour to Ogre fog.

Scripts should re-apply the colour from `Load()`: loading a save reloads the
terrain, which restores the TRN value.

## Live check

2026-10-19, GOG install, windowed. The harness took the launch lock and used no
focus input. The test ran the lcbench world with a fixture that loaded the EXU
branch's own `exu.dll` through `package.cpath`.

| Step | Lua result | `GetSkyClearColor` | bytes at `0x02CD9120` (ReadProcessMemory) |
|---|---|---|---|
| start, then sky dome/plane/box disabled | - | 0,0,0 | 0 0 0 |
| `SetSkyClearColor(1,0,0)` | `true` | 1,0,0 | 255 0 0 |
| `SetSkyClearColor(2,0,0)` | error "requires r, g, b in 0..1" | unchanged | - |
| `ResetSkyClearColor()` | - | 0,0,0 | 0 0 0 |
| `SetSkyClearColor({r=0,g=0.25,b=1})` | `true` | 0,0.251,1 | 0 64 255 |

Pixels:

- The sky visible at the left edge of the client area turned red. Its average
  R rose from 12 at baseline to 71 under the red override; it sits behind the
  translucent HUD panel.
- A terrain control patch in the same frames stayed at 24/27/25.
- The red background was also confirmed by eye during the run.

Every step was SEH-clean, and the game shut down through `Stop-BZRGame`.
