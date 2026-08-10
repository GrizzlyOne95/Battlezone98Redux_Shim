# OpenShim OGRE Plugin Probe

This experiment answers one narrow question before any Direct3D 12 renderer work: can Battlezone 98 Redux's shipped OGRE 1.10 runtime load and execute an independently built plugin DLL from the OpenShim repository?

The probe intentionally does **not** link `OgreMain.dll`, create a renderer, or call Direct3D 12. It only exports the two entry points OGRE's dynamic plugin loader expects and writes lifecycle markers to `OpenShimOgreProbe.log`.

## Build

Build this project explicitly; it is not enabled in the solution's default build set.

```bat
msbuild experiments\ogre_plugin_probe\Plugin_OpenShimOgreProbe.vcxproj /p:Configuration=Release /p:Platform=Win32
```

Expected output:

```text
bin\Release\Plugin_OpenShimOgreProbe.dll
```

## Test

1. Copy `Plugin_OpenShimOgreProbe.dll` beside `battlezone98redux.exe`.
2. Back up `bz_plugins.cfg`.
3. Add this line to the plugin list:

   ```text
   Plugin=Plugin_OpenShimOgreProbe
   ```

4. Launch Battlezone 98 Redux normally.
5. Check the game directory for `OpenShimOgreProbe.log`.

A successful load should contain at least:

```text
[OpenShimOgreProbe] DLL_PROCESS_ATTACH
[OpenShimOgreProbe] dllStartPlugin called
```

A normal shutdown should additionally contain:

```text
[OpenShimOgreProbe] dllStopPlugin called
[OpenShimOgreProbe] DLL_PROCESS_DETACH
```

`BZOgreLogfile.log` should also report that OGRE loaded `Plugin_OpenShimOgreProbe`.

## Interpretation

PASS proves the game's live OGRE plugin loader can load and execute an independently built x86 DLL with the expected exported plugin entry points. It does **not** yet prove C++ ABI compatibility with `OgreMain.dll`; that is the next probe, where this project can be extended to register a minimal `Ogre::Plugin` against the exact Redux OGRE build.

FAIL should be investigated as a loader/export/configuration problem before attempting any Direct3D 12 work.
