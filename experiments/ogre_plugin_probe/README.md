# OpenShim OGRE Plugin Probe

This experiment answers one narrow question before any Direct3D 12 renderer work: can Battlezone 98 Redux's shipped OGRE 1.10 runtime load and execute an independently built plugin DLL from the OpenShim repository?

The probe intentionally does **not** link `OgreMain.dll`, create an `Ogre::Plugin`, create a renderer, or call Direct3D 12. It only exports the two entry points OGRE's dynamic plugin loader expects and writes lifecycle markers to `OpenShimOgreProbe.log` from those entry points.

## Build

This is a separate Win32 DLL target. It is included in `BZROpenShim.sln` for convenience but deliberately omitted from the solution's default `Build.0` set, so normal OpenShim builds continue to produce only `winmm.dll` unless the probe project is explicitly built.

From a Visual Studio developer command prompt:

```bat
msbuild experiments\ogre_plugin_probe\Plugin_OpenShimOgreProbe.vcxproj /p:Configuration=Release /p:Platform=Win32
```

Expected output:

```text
bin\Release\Plugin_OpenShimOgreProbe.dll
```

You can also open `BZROpenShim.sln`, right-click `Plugin_OpenShimOgreProbe`, and build that project directly.

## Test

1. Copy `Plugin_OpenShimOgreProbe.dll` beside `battlezone98redux.exe`.
2. Back up `bz_plugins.cfg`.
3. Add this line to the plugin list:

   ```text
   Plugin=Plugin_OpenShimOgreProbe
   ```

4. Launch Battlezone 98 Redux normally.
5. Check the game directory for `OpenShimOgreProbe.log`.

A successful load should contain:

```text
[OpenShimOgreProbe] dllStartPlugin called
```

A normal shutdown should additionally contain:

```text
[OpenShimOgreProbe] dllStopPlugin called
```

`BZOgreLogfile.log` should also report that OGRE loaded `Plugin_OpenShimOgreProbe`.

## Interpretation

PASS proves the game's live OGRE plugin loader can load and execute an independently built x86 DLL with the expected exported plugin entry points.

It does **not** yet prove C++ ABI compatibility with `OgreMain.dll`. The next probe should link against the exact Redux OGRE build and register a minimal `Ogre::Plugin`, then enumerate the live `Ogre::RenderSystem` list.

FAIL should be investigated as a loader/export/configuration problem before attempting any Direct3D 12 work.

## Safety

The test is intentionally isolated from the shipping OpenShim DLL:

- no changes to `winmm.dll` behavior;
- no hooks or fixed-address patches;
- no OGRE calls from the probe;
- no Direct3D calls;
- no file I/O from `DllMain`;
- removing the probe DLL and restoring `bz_plugins.cfg` fully removes the experiment.
