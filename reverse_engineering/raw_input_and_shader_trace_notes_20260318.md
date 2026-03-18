Date: 2026-03-18

## Scope

Trace two areas relevant to OpenShim patch work:

1. the EXE-side raw-input registration and window-message path
2. the shader compile path from material or program creation to D3D9 compile calls

This note separates:

- corpus-backed findings
- matching-source findings
- what still needs live runtime confirmation before a shipping hook

## Raw Input Trace

### High-confidence findings

- `battlezone98redux.exe` imports the Win32 raw-input and message-pump APIs directly:
  - `GetRawInputData`
  - `RegisterRawInputDevices`
  - `DispatchMessageA`
  - `PeekMessageA`
  - `TranslateMessage`
  - `GetMessageA`
  - `ClipCursor`
- local evidence:
  - `reverse_engineering/module_dumps/2026-03-18/battlezone98redux.exe.imports.txt`
  - lines found:
    - `130` `GetRawInputData`
    - `137` `RegisterRawInputDevices`
    - `146` `DispatchMessageA`
    - `148` `PeekMessageA`
    - `149` `TranslateMessage`
    - `151` `GetMessageA`
    - `152` `ClipCursor`

- `OIS.dll` is not the raw-input path in this build. It imports `DirectInput8Create`, not the raw-input APIs.
- local evidence:
  - `reverse_engineering/module_dumps/2026-03-18/OIS.dll.imports.txt`
  - line found:
    - `50` `DirectInput8Create`

- The promoted Redux PDB corpus names the exact EXE-side input functions that matter:
  - `ProcessInput()`
  - `ProcessKeyboardMessages(unsigned int uMsg, unsigned int wParam, long lParam)`
  - `ProcessMouseMessages(unsigned int uMsg, unsigned int wParam, long lParam)`
  - `ProcessMouseRawInput(tagRAWMOUSE* raw)`
  - `LockMouse()`
  - `UnlockMouse()`
  - `cUI_Parent::HandleWindowsMessages()`
  - `cUI_Parent::mouseMoved(...)`
  - `cUI_Parent::mousePressed(...)`
  - `cUI_Parent::mouseReleased(...)`
- local evidence:
  - `reverse_engineering/workshop/global_decompile/bzr_gog_best_effort/pdb_reference/llvm/pretty_funcs.txt`
  - relevant lines:
    - `3862` `ProcessInput`
    - `3863` `ProcessKeyboardMessages`
    - `3864` `ProcessMouseMessages`
    - `3865` `ProcessMouseRawInput`
    - `2667` `LockMouse`
    - `5260` `UnlockMouse`
    - `6716` `cUI_Parent::HandleWindowsMessages`
    - `6730` `mouseMoved`
    - `6731` `mousePressed`
    - `6732` `mouseReleased`

- The same corpus ties the code to the expected object files:
  - `Input.obj`
  - `UI_OptionsInput.obj`
  - `tinput.obj`
- local evidence:
  - `reverse_engineering/workshop/global_decompile/bzr_gog_best_effort/pdb_reference/modules.csv`
  - relevant lines:
    - `358` `Input.obj`
    - `479` `UI_OptionsInput.obj`
    - `530` `tinput.obj`

- The binary strings also contain a raw-input-specific diagnostic:
  - `GetRawInputData does not return correct size !`
- local evidence:
  - `reverse_engineering/workshop/global_decompile/bzr_gog_best_effort/binary_strings/ascii_strings.csv`
  - relevant line:
    - `8984`

### Practical call-path model

The available evidence supports this path:

1. the EXE owns the Win32 message pump and message dispatch
2. UI and shell message handling route through `cUI_Parent::HandleWindowsMessages()`
3. keyboard and mouse messages are split in the input subsystem
4. raw mouse deltas are handled in `ProcessMouseRawInput(tagRAWMOUSE* raw)`
5. cursor grab or release behavior likely sits near `LockMouse()` and `UnlockMouse()`

In other words:

- raw input belongs to the EXE and the native input layer
- OIS is still present for higher-level input plumbing, but it is not the registration site for `RegisterRawInputDevices`

### Useful RVAs from the promoted corpus

These are the main candidate RVAs for GOG-style tracing and likely hook-site scouting:

- `ProcessInput`: `0x00156580`
- `ProcessKeyboardMessages`: `0x0015A2D0`
- `ProcessMouseMessages`: `0x0015AE50`
- `ProcessMouseRawInput`: `0x0015B050`
- `LockMouse`: `0x0015AC70`
- `UnlockMouse`: `0x0015ADA0`
- `cUI_Parent::HandleWindowsMessages`: `0x001F1380`

### What is not yet validated

Two things are still missing:

1. the exact EXE function that calls `RegisterRawInputDevices`
2. the exact branch conditions that choose raw-input handling versus the older mouse-message path

That last step needs either:

- live runtime disassembly
- or a trustworthy Steam-target Ghidra export after the runtime image is stable

### Raw-input launch flag status

The launch flag is real.

Local binary-string evidence shows both of these command-line tokens in the EXE:

- `rawinput`
- `norawinput`

Local evidence:

- `reverse_engineering/workshop/global_decompile/bzr_gog_best_effort/binary_strings/ascii_strings.csv`
  - `4846844,4852988,.rdata,norawinput`
  - `4846856,4853000,.rdata,rawinput`

That means the executable at least recognizes a raw-input toggle at command-line parse time.

What this does not prove by itself:

- that the flag still reaches the runtime branch that selects `ProcessMouseRawInput(...)`
- that it correctly suppresses or bypasses the older `ProcessMouseMessages(...)` path
- that focus loss / regain re-registers raw devices correctly

So the right current answer is:

- the flag definitely exists
- whether it works properly in the current game build is still unvalidated

### Best-effort static anchor from the older baseline install

A best-effort PE scan against the older local GOG install at:

- `C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe`

found one direct `RegisterRawInputDevices` IAT call and two direct `GetRawInputData` IAT calls:

- `RegisterRawInputDevices` callsite: `0x00618EC2`
- `GetRawInputData` callsites:
  - `0x00619502`
  - `0x0061952C`

The surrounding register callsite code clearly builds a single `RAWINPUTDEVICE` entry with:

- usage page `0x01`
- usage `0x02`
- flags `0x00000000`
- target hwnd `0`

This strongly looks like stock mouse raw-input registration.

Important limitation:

- this older executable is not the current workspace install and does not line up with the promoted corpus RVAs used elsewhere in this note
- treat those three VAs as semantic breadcrumbs only
- do not ship an OpenShim patch against those exact addresses

The current workspace install at:

- `C:\Users\istuart\Documents\Battlezone 98 Redux\battlezone98redux.exe`

still contains the `rawinput` / `norawinput` strings, but the same quick IAT scan did not recover direct callsites cleanly there, so the current-build registration site remains unvalidated.

### Concrete OpenShim hook plan

The cleanest implementation path is a staged diagnostic-first pass.

Stage 1: prove what the launch flag actually does

- add an env-gated probe at `ProcessMouseRawInput(tagRAWMOUSE* raw)`
- add an env-gated probe at `ProcessMouseMessages(unsigned int uMsg, unsigned int wParam, long lParam)`
- add an env-gated probe at `LockMouse()` and `UnlockMouse()`
- add an env-gated probe at `cUI_Parent::HandleWindowsMessages()`

Recommended env flag names:

- `OPENSHIM_TRACE_RAW_INPUT`
- optional alias: `OPENSHIM_TRACE_MOUSE_INPUT`

What to log:

- whether `ProcessMouseRawInput(...)` fires at all
- whether `ProcessMouseMessages(...)` is still driving movement while raw input is enabled
- raw mouse fields:
  - `usFlags`
  - `lLastX`
  - `lLastY`
  - `usButtonFlags`
- selected message ids on the message side:
  - `WM_INPUT`
  - `WM_MOUSEMOVE`
  - `WM_LBUTTONDOWN`
  - `WM_LBUTTONUP`
  - `WM_RBUTTONDOWN`
  - `WM_RBUTTONUP`
- lock / unlock timing around focus changes, alt-tab, and shell-to-game transitions

Stage 2: decide the actual fault layer

If `rawinput` is present on the command line but `ProcessMouseRawInput(...)` never fires:

- the fault is probably raw-device registration or a disabled branch before the raw handler

If both raw and old mouse-message look paths fire in gameplay:

- the fault is probably double-feeding
- patch direction should be to gate or suppress the legacy movement path while raw mode is active

If raw works once but stops after alt-tab or shell transitions:

- the fault is probably near `LockMouse()` / `UnlockMouse()`
- patch direction should be re-registration or recapture during focus regain

If raw only fails in menus or only in shell views:

- the fault is probably above the native mouse functions in `cUI_Parent::HandleWindowsMessages()`

Stage 3: shipping patch order

1. diagnostics only
2. force the runtime raw-input enable branch if the launch flag parse is broken
3. fix registration / re-registration near `LockMouse()` and `UnlockMouse()`
4. only if needed, suppress the legacy look-delta path in `ProcessMouseMessages(...)` while raw mode is active

### Recommended first hook targets

For OpenShim, the best first concrete targets are still:

- `ProcessMouseRawInput`: prove raw deltas are present and well-formed
- `ProcessMouseMessages`: prove whether legacy mouse movement still feeds look while raw mode is on
- `LockMouse` / `UnlockMouse`: prove whether focus recapture breaks raw registration
- `cUI_Parent::HandleWindowsMessages`: prove whether `WM_INPUT` even reaches the native UI / shell message layer

### Validation checklist for the launch flag

`rawinput` should be treated as working only if all of these are true in one live session:

1. launching with the raw-input flag causes `ProcessMouseRawInput(...)` hits during gameplay
2. launching with `norawinput` removes those hits or keeps the game on the older message path
3. camera look is driven by raw deltas without duplicate message-path movement
4. alt-tab away and back preserves or restores raw-input handling
5. menus and shell clicks still behave correctly

If any of those fail, the fix should target the EXE-side native input layer above, not `OIS.dll`.

### Patch direction

For an OpenShim raw-mouse patch, the evidence points at the EXE-side native input path, not `OIS.dll`.

The best candidates to investigate first are:

- input initialization or focus-capture code near `LockMouse()` and `UnlockMouse()`
- the split between `ProcessMouseMessages(...)` and `ProcessMouseRawInput(...)`
- UI and shell message routing in `cUI_Parent::HandleWindowsMessages()`

## Shader Compile Trace

### EXE-side anchors

The promoted Redux corpus exposes several useful render-adjacent entry points that bridge game code to Ogre materials and render work:

- `MatListener::handleSchemeNotFound(...)`
- `DynamicGeometry::_initBatch(...)`
- `DynamicGeometry::begin(...)`
- `DynamicGeometry::beginOcclusionQuery(...)`
- `OgreRenderPass()`

Local evidence:

- `reverse_engineering/workshop/global_decompile/bzr_gog_best_effort/pdb_reference/public_functions.csv`
  - `5319` `handleSchemeNotFound@MatListener`
  - `5587` `beginOcclusionQuery@DynamicGeometry`
  - `5588` `begin@DynamicGeometry`
  - `5590` `_initBatch@DynamicGeometry`
  - `5626` `_OgreRenderPass`
- `reverse_engineering/workshop/global_decompile/bzr_gog_best_effort/pdb_reference/llvm/pretty_funcs.txt`
  - `2765` `MatListener::handleSchemeNotFound`
  - `1541` `DynamicGeometry::_initBatch`
  - `1545` `DynamicGeometry::begin(const char* ...)`
  - `1546` `DynamicGeometry::begin(SharedPtr<Material>& ...)`
  - `1547` `DynamicGeometry::beginOcclusionQuery(...)`
  - `3448` `OgreRenderPass()`

These are the right native places to patch if the goal is to alter how BZR selects material schemes, creates dynamic render batches, or routes passes into Ogre.

### RTShaderSystem path

When BZR uses Ogre RTShaderSystem-generated shaders, the matching OGRE 1.10 source shows this path:

1. `TargetRenderState::createCpuPrograms()` creates CPU-side vertex and fragment programs and a `ProgramSet`
2. `ProgramManager::acquirePrograms(...)` asks RTSS to create GPU programs
3. `ProgramManager::createGpuPrograms(...)` writes source code and creates Ogre high-level GPU programs
4. `ProgramManager::createGpuProgram(...)` calls `HighLevelGpuProgramManager::createProgram(...)`
5. the resulting program is bound to the pass with `pass->setVertexProgram(...)` and `pass->setFragmentProgram(...)`

Local source anchors:

- `C:\Users\istuart\Documents\GIT\ogre-1.10.0\Components\RTShaderSystem\src\OgreShaderRenderState.cpp`
  - `TargetRenderState::createCpuPrograms()`
- `C:\Users\istuart\Documents\GIT\ogre-1.10.0\Components\RTShaderSystem\src\OgreShaderProgramManager.cpp`
  - `ProgramManager::acquirePrograms(...)`
  - `ProgramManager::createGpuPrograms(...)`
  - `ProgramManager::createGpuProgram(...)`

Important behavior from those files:

- RTSS explicitly binds the generated GPU program names to the Ogre `Pass`
- RTSS uses `HighLevelGpuProgramManager::createProgram(...)`, so it feeds the normal Ogre high-level shader backend rather than bypassing it

### Cg plugin path

When the path uses the Cg plugin, the matching source is:

1. `CgFxScriptLoader` creates an Ogre GPU program, sets source, entry point, and profiles
2. it calls `ogreProgram->load()` and `ogreProgram->createParameters()`
3. it binds the resulting program to the pass with `setVertexProgram(...)` or `setFragmentProgram(...)`
4. `CgProgram::loadFromSource()` selects the profile and either uses cache or calls `compileMicrocode()`
5. `CgProgram::compileMicrocode()` calls `cgCreateProgram(...)`

Local source anchors:

- `C:\Users\istuart\Documents\GIT\ogre-1.10.0\PlugIns\CgProgramManager\src\OgreCgFxScriptLoader.cpp`
- `C:\Users\istuart\Documents\GIT\ogre-1.10.0\PlugIns\CgProgramManager\src\OgreCgProgram.cpp`

The local module dump matches that source:

- `reverse_engineering/module_dumps/2026-03-18/Plugin_CgProgramManager.dll.imports.txt`
  - line `248` `cg.dll`
  - line `269` `cgCreateProgram`

### D3D9 backend compile path

Once the pass has a bound program, the matching D3D9 backend source shows two important compile paths:

- low-level D3D9 assembly path:
  - `D3D9GpuProgram::loadFromSource(...)`
  - `D3D9GpuProgram::compileMicrocode(...)`
  - `D3DXAssembleShader(...)`

- high-level HLSL path:
  - `D3D9HLSLProgram::loadFromSource()`
  - `D3D9HLSLProgram::compileMicrocode()`
  - `D3DXCompileShader(...)`

Local source anchors:

- `C:\Users\istuart\Documents\GIT\ogre-1.10.0\RenderSystems\Direct3D9\src\OgreD3D9GpuProgram.cpp`
- `C:\Users\istuart\Documents\GIT\ogre-1.10.0\RenderSystems\Direct3D9\src\OgreD3D9HLSLProgram.cpp`

The local module dump confirms those backend imports:

- `reverse_engineering/module_dumps/2026-03-18/RenderSystem_Direct3D9.dll.imports.txt`
  - line `771` `D3DXAssembleShader`
  - line `779` `D3DXCompileShader`

### End-to-end shader model

The practical shader flow is:

1. BZR chooses or creates an Ogre material or render pass
2. `MatListener::handleSchemeNotFound(...)` is a likely native hook point for scheme fallback or generated-technique selection
3. RTSS or Cg creates an Ogre `HighLevelGpuProgram`
4. the pass binds program names with `setVertexProgram(...)` and `setFragmentProgram(...)`
5. the D3D9 backend compiles source into microcode through:
   - `D3DXCompileShader` for HLSL
   - `D3DXAssembleShader` for low-level assembled shaders

### What this means for patch work

Yes, these modules are useful for custom shader work.

What they can realistically help with:

- better HLSL authoring and compile behavior inside the D3D9 renderer
- custom scheme selection and fallback through the native `MatListener` path
- RTShaderSystem language or profile changes if BZR is using RTSS-generated programs
- stronger parameter binding and material integration work at the Ogre layer

What they do not automatically give you:

- shader-model features beyond what Ogre 1.10 plus the D3D9 backend support
- arbitrary modern rendering features without corresponding material, pass, and backend support

## Current Recommendation

If the next patch effort is raw input:

- focus on the EXE-side input path
- do not spend time patching `OIS.dll` for raw registration
- revalidate the exact `RegisterRawInputDevices` call site in a live runtime before shipping

If the next patch effort is shader capability:

- start at `MatListener::handleSchemeNotFound(...)` and the RTSS or Cg program creation path
- treat `RenderSystem_Direct3D9.dll` as the backend compiler and binder, not the first policy hook
- use the matching OGRE source as the main authority for compile-path behavior
