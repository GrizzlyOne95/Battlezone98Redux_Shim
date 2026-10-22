# Per-planet IBL bake

`bake_planet_env.py` writes a prefiltered-specular and an irradiance cubemap for each of the 9 worlds:

    resources/renderer/enhanced/openshim_env_<code>_prefilter.dds    128px cube, 8 GGX mips, BC1
    resources/renderer/enhanced/openshim_env_<code>_irradiance.dds    32px cube, full mip chain, BC1

Codes: `mn` Moon, `ma` Mars, `ve` Venus, `io` Io, `eu` Europa, `ti` Titan, `ga` Ganymede, `ac` Achilles, `el` Elysium.

## Run

    py -3 tools/ibl/bake_planet_env.py --game-dir "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux"

Optional: `--preview-dir <dir>` (equirect PNG per world plus `contact_sheet.png`, sRGB-encoded mip 0),
`--worlds mn,ma`, `--output <dir>`, `--samples N`. Needs numpy and Pillow. Takes about a minute and is
deterministic. The game directory is only read. After writing, the tool checks that every output's
128-byte DDS header and total size equal the neutral `openshim_ibl_neutral_*.dds` in the output directory.

## Inputs (all under the game dir)

- `Edit/trn/<world>.trn`: `[Sky]` SkyTexture/SkyType/SkyHeight, `[Clouds]`, `[Stars]`.
- `BZ_ASSETS/pc/textures/sky`, `pc/textures/TRO/TERRAIN/SKY`, `common/textures/sky`: sky, cloud and planet sprite textures.
- `BZ_ASSETS/pc/textures/TerrainTextures/BZ_TERRAIN_ATLASES_DIFF_DDS/<WORLD>_ATLAS_D.dds`: ground colour.

Sky model: atmospheric worlds tile the sky texture on a plane (uv = dir.xz/dir.y) and fade to its mean
colour toward the horizon, with the first three cloud layers lightly composited. Airless worlds
(and Io) are about 0.003 linear black plus a flat disc of the primary planet billboard. The lower
hemisphere is the mean linear terrain-atlas colour times 0.6, blended across +-10 degrees of the
horizon. There is no sun. Io's disc placement is a guess (see constants at the top of the script).

## Output format

Legacy DDS, DXT1 cube, caps 0x401008, caps2 0xFE00, faces +X -X +Y -Y +Z -Z with all mips per face.
Values are LINEAR radiance in 8-bit BC1 (the shader samples with no decode), so very dark values
quantise coarsely. Each pair is 68,944 bytes; 9 worlds total about 620 KB.
