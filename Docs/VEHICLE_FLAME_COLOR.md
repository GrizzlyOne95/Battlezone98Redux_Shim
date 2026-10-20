# Vehicle engine flame color

Set an explicit flame texture color in the vehicle ODF:

```ini
[HoverCraftClass]
flameColor = "green"
```

`[HoverCraft]` is also accepted as shorthand for `[HoverCraftClass]`.

Supported values (case-insensitive, quotes optional): `default`, `blue`, `red`,
`green`, `orange`, `blackdog`. `blackdog` selects the Black Dog blood-red texture.
These names select existing flame textures. Orange and
Black Dog require compatible addon textures; unavailable textures keep stock
flames, as they do for faction coloring.

For a custom color, supply three RGB components in the range 0 through 1:

```ini
[HoverCraftClass]
flameColor = "1.0 0.2 0.6"  // pink
```

`"1 0 1"` is magenta, `"0 1 1"` cyan, `"1 1 1"` white, and `"0 0 0"`
suppresses visible flames. Invalid component counts, non-finite values, and
components outside 0..1 leave the faction fallback intact.

RGB uses three additive passes over the stock red/green/blue flame textures,
isolating each requested channel in the sprite vertex color while retaining
native alpha, animation and geometry. Queues are shared by craft requesting
the same RGB color, with a maximum of 64 distinct RGB colors per mission.
RGB requires the three stock flame textures and the verified sprite-color
hook; unavailable resources or a full cache keep stock flames. Named presets
continue to use their existing single texture pass.

Selection priority:

1. Explicit EXU per-team blue/red/green setting.
2. `[HoverCraftClass] flameColor` in the vehicle ODF.
3. Faction color when `openshim.ini [Display] JetFlames` is enabled.
4. Stock flames.

An explicit `default` selects stock flames even with faction coloring enabled.
A missing or invalid key leaves the faction fallback intact. The ODF override
also applies when `JetFlames` is disabled. Keys in other sections are ignored.

OpenShim reads the ODF through the game's verified item-loader interface,
including archive content, and caches results by ODF name until the mission
ends. Restart the mission after editing an ODF. When that loader interface is
unavailable for an executable build, the ODF override fails closed and existing
EXU/faction/stock routing continues. RGB installs its guarded sprite-color
hook only when a craft requests RGB; named colors do not require this hook.

Runtime implementation: `src/patches/engine_flames.cpp`.
`OPENSHIM_TRACE_JET_FLAMES=1` adds routing diagnostics (`odfColor=-1` means no
valid ODF override); valid ODF choices also log once per vehicle type.
