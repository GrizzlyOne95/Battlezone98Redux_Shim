# Menu image colors

OpenShim Options > Video > Menu Colors previews RGB (0–255), saturation
(0–100%) and white level (0–200%). Red, Blue and Amber presets keep the
current saturation and white level. Stock previews the original materials.
Apply saves the six settings together; Back or Escape discards unsaved edits.
The feature defaults off.

The shader replaces green-dominant detail in an explicit list of stock and
OpenShim menu images. At full saturation it uses the artwork's peak intensity
with the selected RGB, avoiding the pink highlights produced by retaining a
neutral base. Lower saturation adds neutral white; white level adjusts image
brightness independently. Native texture alpha and widget color remain intact.
Fonts, HUD sprites, map previews, flags, movies and unknown image names are
excluded. Replacements using the same listed filenames are eligible only if
their material still uses the recognized native UI programs.

## Implementation and limits

The existing guarded UI image-material owner notifies the adapter after native
material creation. There is no competing image-builder detour. The adapter
retains native Ogre shared references to eligible materials and original GPU
parameters, and restores both the program and parameter block on Stock/cancel.
Collection is bounded to 512 materials. Preset and Apply callbacks queue work
for the screen update; persistence uses one lossless atomic INI write.

The optional menu shader is registered independently of the selected scene
render profile. The adapter requires the recognized GOG 2.2.301 executable,
DX11, the qualified Ogre exports and the native slider bindings. Unsupported
renderers/builds retain their native materials and show an unavailable message.
Missing shaders or constants restore the affected material. Steam, DX9,
Proton/Wine and other builds remain unqualified.

`scripts/patches.json` owns the three slider bindings. Released executable
constructor/call-site analysis and live prologue checks preceded their addition.
The page uses native sliders, including their arrow-step behavior.

The accompanying options navigation repair guards null-key action rows (the
System page's Reset Career Stats action) before color-key comparisons and
creates category navigation before formatting the page contents. Menu Colors
Back is a child of its full-screen panel, matching the working category-page
input hierarchy; a sibling button could draw while the panel intercepted input.

## Validation

Win32 Release builds, all 119 CTests, INI completeness/default/writer/migration
checks, GCC policy checks and the shader's ps_4_0 compilation pass. Local GOG
DX11 captures show red and blue menu art with unchanged green font/movie
content; all five controls fit a 960×540 render surface. Physical input checks
cover blue/Stock presets, an arrow step, grouped Apply persistence and the
System page's four rows and Back navigation. With the final rebuilt DLL,
physical clicks through Options > OpenShim > Video > Menu Colors > Apply > Back
return to Video, System > Back returns to the hub, and Escape returns from Video
to the hub. Broader resolution, lifecycle and platform acceptance remain pending.
Continuous drag behavior is not claimed by these checks.
