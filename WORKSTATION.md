# Workstation Guide — BZR-OpenShim

Canonical paths and tooling for **this** machine (the sole dev workstation as of
2026-07-16). Every path below was `Test-Path`-verified on this date. When a path
here disagrees with an older `reverse_engineering/*` note or a memory file,
**this file wins** — the RE notes were written under a two-machine setup and use
`<USER_HOME>` / `<GAME_ROOT>` / `<LLVM_ROOT>` placeholders that no longer map
cleanly.

Host: Windows 11 Pro, user `iestu`. Shell: PowerShell 7 (primary) + Git Bash.

---

## 1. Battlezone installs

### GOG — primary build + deploy target
`C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux`

- `battlezone98redux.exe` — live 2.2.301 GOG build (5,425,152 bytes). **All the
  VAs in `bzr_hooks.cpp` are valid against this exe at runtime.**
- `battlezone98redux.pdb` — 2016 *advisory* beta PDB. Good for class names,
  singletons, and RTTI; its public function VAs are drifted — re-derive statics
  by content. See memory `bzr-address-drift-rtti-rederivation`.
- Deployed shim artifacts: `winmm.dll`, `exu.dll`, `openshim.ini`, `net.ini`,
  `multi.ini`.
- **Live user config + key maps live HERE, in the install root** next to
  `winmm.dll`: `openshim.ini`, `input.map`, `gamekey.map`. OpenShim's
  `GetConfigModuleDirectory()` resolves to the winmm.dll directory, i.e. this
  folder. There is **no** `Documents\Battlezone 98 Redux` folder on this box —
  older notes that cite `Documents/Battlezone 98 Redux/input.map` are stale.

### Steam — secondary verification target
`C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux`

- `battlezone98redux.exe` — same build under SteamStub (5,554,832 bytes; `.text`
  decrypts in place at runtime, so GOG VAs are valid once running).
- Has `winmm.dll` + `openshim.ini` + `input.map` deployed, **no `exu.dll`**.
- Ships DXVK d3d dlls (`d3d11.dll`, `dxgi.dll`, etc.).
- Steam Workshop content (mods): `C:\Program Files (x86)\Steam\steamapps\workshop\content\301650`
  (BZR appid 301650; 19 items installed).

### Launcher / engine save state
`%LOCALAPPDATA%\Rebellion\Battlezone 98 Redux\` → `Launcher.ini`
(`C:\Users\iestu\AppData\Local\Rebellion\Battlezone 98 Redux`).

---

## 2. Repos

| Repo | Path | Origin / branch |
|------|------|-----------------|
| **BZR-OpenShim** (winmm.dll shim) | `C:\Users\iestu\Documents\GIT\BZR-OpenShim` | `github.com/GrizzlyOne95/Battlezone98Redux_Shim.git` / `main` |
| **ExtraUtilities** (exu.dll) | `C:\Users\iestu\Documents\ExtraUtilities` | `github.com/GrizzlyOne95/ExtraUtilities` / `main` |
| **CampaignReimagined** (mod suite) | `C:\Users\iestu\Documents\GIT\Battlezone98Redux_CampaignReimagined` | `.../Battlezone98Redux_CampaignReimagined.git` / `ai-base-economy-and-combat-fixes` |

Note: the EXU repo is at `Documents\ExtraUtilities`, **not** under `Documents\GIT`
and **not** named `ExtraUtilities-G1` (that alias in memory is stale). Other BZR
repos under `Documents\GIT\`: `Battlezone98Redux_DedicatedServer`,
`battlezone-netcode-patch`, `BZR-Subtitles`, `Battlezone_LobbyMonitor`, and
assorted tools (`_AudioTool`, `_BZN_Scanner`, `_TextureManager`,
`_WorldBuilder`, `_LocalizationTool`, etc.).

---

## 3. Build toolchain

- **Visual Studio 2022 Community 17.14** — `C:\Program Files\Microsoft Visual Studio\2022\Community`
- **MSBuild** — `C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe`
- **VC toolsets installed**: `14.38.33130` and `14.44.35207`. Force
  **`14.44.35207`** for both shim and EXU builds (per memory
  `bzr-exu-build-and-deploy`).

### Build BZR-OpenShim (winmm.dll → Win32)
```powershell
& "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" `
  "C:\Users\iestu\Documents\GIT\BZR-OpenShim\BZROpenShim.sln" `
  /p:Configuration=Release /p:Platform=Win32 /p:VCToolsVersion=14.44.35207 /m /v:m /nologo
# Output: C:\Users\iestu\Documents\GIT\BZR-OpenShim\bin\Release\winmm.dll
```

### Build ExtraUtilities (exu.dll → x86)
```powershell
& "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" `
  "C:\Users\iestu\Documents\ExtraUtilities\ExtraUtilities.sln" `
  /p:Configuration=Release /p:Platform=x86 /p:VCToolsVersion=14.44.35207 /m /v:m /nologo
# Output: C:\Users\iestu\Documents\ExtraUtilities\Release\exu.dll
```

### Deploy (game must be closed — the running exe locks winmm.dll)
```powershell
# check + kill
Get-Process battlezone98redux -ErrorAction SilentlyContinue | Stop-Process -Force
# GOG (primary)
Copy-Item "C:\Users\iestu\Documents\GIT\BZR-OpenShim\bin\Release\winmm.dll" `
  "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\winmm.dll" -Force
# Steam (winmm only; no exu there)
Copy-Item "C:\Users\iestu\Documents\GIT\BZR-OpenShim\bin\Release\winmm.dll" `
  "C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux\winmm.dll" -Force
```
Runtime log after launch: `winmm_shim.log` in the install root.

---

## 4. Reverse-engineering tooling

- **llvm-pdbutil** (VS-bundled, on PATH):
  `C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\x64\bin\llvm-pdbutil.exe`
  — use against `battlezone98redux.pdb` for class names / globals / RTTI.
- **Python 3.12.10** — `C:\Users\iestu\AppData\Local\Programs\Python\Python312\python.exe`
  (on PATH as `python`). RE packages: **pefile 2024.8.26**, **capstone 5.0.6**.
  Use for byte dumps + disassembly at a VA (see the `dump_*` pattern used to
  verify hook prologues).
- **Ghidra**: `C:\Users\iestu\Tools\ghidra_12.1.2_PUBLIC` (also `ghidra_12.0.4_PUBLIC`).
  Existing project for the exe: `C:\Users\iestu\Documents\GIT\BZR-OpenShim\battlezone98redux.exe-ghidra`.

### In-repo RE corpora (search these before disassembling)
Under `C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\`:

- `decompilation_from_1.5_exe-pdb/` — symbolized 1.5 + Redux decompiles, and the
  legacy→Redux map. **Grep here first** for engine internals (memory
  `bzr-15-decompilation-data`). Redux raw C is under
  `decompilation_from_1.5_exe-pdb/Redux/Raw .C/FUN_<va>-<va>.c`.
- `repo_corpora/bzr_gog_best_effort/pdb_reference/` — `public_functions.csv`,
  `module_files.csv`, symbol tables.
- `repo_corpora/bzr_gog_best_effort/binary_strings/` — `ascii_strings.csv`
  (string→VA for xref-based static recovery).
- `repo_corpora/bzr_gog_best_effort/merged/` — `legacy_symbol_enriched_functions.csv`,
  `function_matches_by_rva.csv`.

---

## 5. Quick verify

Re-run the path check any time with:
```powershell
# from repo root
Get-Content .\WORKSTATION.md | Select-String -Pattern 'C:\\[^`"|]+\.(exe|dll|pdb|sln|ini|map|bat)' -AllMatches |
  ForEach-Object { $_.Matches.Value } | Sort-Object -Unique |
  ForEach-Object { if (Test-Path -LiteralPath $_) { "OK   $_" } else { "MISS $_" } }
```
All 26 tracked paths verified present on 2026-07-16.
