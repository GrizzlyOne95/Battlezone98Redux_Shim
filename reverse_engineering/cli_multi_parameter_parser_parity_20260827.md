# Redux Command-Line Parser Multi-Parameter Argument Parity Investigation

**Author:** OpenShim Reverse Engineering Team
**Date:** 2026-08-27
**Branch:** `research/cli-multi-parameter-parser-parity-20260827`
**Status:** Findings Confirmed / Defect Proven / Mitigation Plan Formulated

---

## Executive Summary

This investigation proves Scott ("Herp")'s report: **Battlezone 98 Redux's command-line parser fails to parse multi-parameter arguments that rely on comma delimiters (e.g., `-shellmap:216,178`).**

The root cause is a regression introduced during the Redux engine overhaul:
1. In **Battlezone 1.5**, the command-line parser tokenized arguments using `strtok()` with whitespace delimiters (`" \t\r\n"`). Arguments containing commas passed intact to parameter handlers, allowing `sscanf(token, ":%d,%d", &w, &h)` to successfully extract multiple values.
2. In **Redux 2.2.301**, the delimiter string passed to `strtok()` in `FUN_007d5120` was modified to include comma: `", \t\r\n"` (`DAT_008f068c`).
3. As a direct result, `strtok()` destructively modifies the process command-line buffer in place, replacing `,` with `\0` before the option dispatch handler receives the token.
4. When `-shellmap:216,178` is passed:
   - Token 1 is truncated to `"-shellmap:216"`.
   - `sscanf("-shellmap:216" + 9, ":%d,%d", &w, &h)` matches only the first parameter (`216`), returning `1`.
   - The handler's fallback logic sets `height = width` (`216`), completely discarding the second parameter (`178`).
   - Token 2 (`"178"`) is returned on the next `strtok()` iteration; missing an option prefix (`/`, `-`, `+`), it falls into the positional map/savefile loader, failing `.sav` validation and triggering an invalid load state (`FUN_00434170(5)`).

---

## Phase 1 — Recovered Option Tables

### 1. Tokenizer Delimiter Comparison

| Engine Version | Tokenizer Function | Delimiter String (`strtok`) | Process Buffer Mutated? | Multi-Param Comma Handling |
| :--- | :--- | :--- | :--- | :--- |
| **Battlezone 1.5** | `strtok(buf, delims)` | `" \t\r\n"` | Yes (spaces converted to NUL) | **Intact** (`-shellmap:216,178` passed as single token) |
| **Redux 2.2.301** | `strtok(buf, delims)` | `", \t\r\n"` (`DAT_008f068c`) | Yes (spaces and commas converted to NUL) | **Broken** (split into `"-shellmap:216"` and `"178"`) |

---

### 2. Redux 2.2.301 Recovered Option Table

Below is the complete option table recovered from `FUN_007d5120` (RVA `0x3d5120` in `battlezone98redux.exe` / GOG 2.2.301 decompilation):

| Option Name | Prefix / Separator | Expected Param Count | Expected Delimiters | Conversion Format | Destination Global / State | Handler / Logic Summary |
| :--- | :--- | :---: | :--- | :--- | :--- | :--- |
| **`multi`** | `-`, `/`, `+` | 0 | N/A | Flag | `_DAT_00920ed4 = 1` | Force multiplayer mode enabled |
| **`nomulti`** | `-`, `/`, `+` | 0 | N/A | Flag | `_DAT_00920ed4 = 0xffffffff` | Force multiplayer mode disabled |
| **`win`** | `-`, `/`, `+` | 0 | N/A | Flag | `FUN_00663d10(0)` | Windowed mode toggle |
| **`fullscreen`** | `-`, `/`, `+` | 0 | N/A | Flag | `FUN_00663d10(1)` | Fullscreen mode toggle |
| **`rawinput`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_00918424 = 1` | Enable raw mouse/keyboard input |
| **`norawinput`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_00918424 = 0` | Disable raw input |
| **`noshell`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_0091556c = 1` | Bypass shell UI on launch |
| **`flagfile:`** | `:` | 1 | String | Copy | `DAT_00918404` | Copies filename string to flagfile buffer |
| **`net:`, `net=`** | `:`, `=` | 1 | String | Token match | Subsystem Network Provider | Matches `steam`, `gog`, `cp`, `bzr` network modes |
| **`renderer:`, `renderer=`** | `:`, `=` | 1 | String | Token match | Ogre Subsystem Selection | Controlled by OpenShim backend selection (`dx9`, `dx11`, `gl`) |
| **`platform:`, `platform=`** | `:`, `=` | 1 | String | Token match | OS target override | Matches `win`, `osx`, `ios` |
| **`resave`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_009183b4 = 1` | Resave map/mission file |
| **`asciisave`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_008eaab4 = 0` | Force ASCII save format |
| **`binarysave`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_008eaab4 = 1` | Force binary save format |
| **🔥 `shellmap`** | `:`, `,` | **2** | **Comma `,`** | **`:%d,%d`** | `DAT_009183d4 = 1`<br>`_DAT_009183c4 = (H<<16) \| W` | **BROKEN IN REDUX.** Default W=108 (0x6c), H=89 (0x59). Uses `sscanf(token+9, ":%d,%d", &w, &h)`. |
| **`largemap`** | `:` | 1 | N/A | `:%d` | `DAT_009183d4 = 2`<br>`_DAT_009183c4 = val` (default 8) | Sets largemap mode and dimension |
| **`nobodyhome`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_0091836c = 1` | Spawn no player vehicle |
| **`nointro`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_008eaab8 = 0` | Skip opening intro movies |
| **`exitafterload`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_009183e8 = 1` | Benchmark / test auto-exit after load |
| **`saveafterload`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_009183bc = 1` | Save mission immediately after loading |
| **`edit`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_009454b8 = 1` | Launch built-in map editor |
| **`startedit`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_009183f4 = 1`<br>`DAT_009454b8 = 1` | Auto-start map editor |
| **`console`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_009183cc = 1` | Enable developer console |
| **`develop`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_009183c8 = 1` | Enable developer mode features |
| **`showunloc`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_00946724 = 1` | Show localized string keys |
| **`connect_lobby`** | `=` | 1 | String | URL / ID | `DAT_009183ec = 1` | Triggers lobby join via `FUN_00765a20` or `FUN_00765ae0` |
| **`connect-galaxy-lobby`**| `=` | 1 | String | GOG Lobby ID | `DAT_009183ec = 1` | Triggers GOG Galaxy lobby join |
| **`netpktlog`** | `-`, `/`, `+` | 0 | N/A | Flag | Network Packet Log | Enable packet logging |
| **`nonetpktlog`** | `-`, `/`, `+` | 0 | N/A | Flag | Network Packet Log | Disable packet logging |
| **`nobzrnetlog`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_008eda28 = 0` | Disable BZRNet logging |
| **`netlog`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_009180d8 = 1` | Enable general network logging |
| **`netlog=`** | `=` | 1 | String/Int | `=atoi()` | `DAT_009180d8 = val` | Set netlog verbosity level |
| **`nonetlog`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_009180d8 = 0` | Disable netlog |
| **`nohgtsmoothing`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_009454cc = 1` | Disable heightfield smoothing |
| **`dohgtsmoothing`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_009454cc = 0` | Enable heightfield smoothing |
| **`enablerenderselection`**|`-`, `/`, `+` | 0 | N/A | Flag | `DAT_008e7068 = 0` | Renderer selection toggle |
| **`disablerenderselection`**|`-`, `/`, `+`| 0 | N/A | Flag | `DAT_008e7068 = 0` | Renderer selection toggle |
| **`disablemods`** | `-`, `/`, `+` | 0 | N/A | Control Case | `DAT_00915568 = 1` | Disable Steam Workshop / addon mods |
| **`iprelay`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_00946708 = 1` | Force IP relay networking |
| **`ipdirect`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_00946708 = 0` | Force direct IP networking |
| **`bzrserver=`** | `=` | 1 | String | Copy | Server IP Buffer | Target server IP for direct connect |
| **`bzrnetport=`** | `=` | 1 | String/Int | `=atoi()` | `DAT_00945704 = port` | Override network port |
| **`datadir=`** | `=` | 1 | String | Path | Data Dir Override | Custom data directory |
| **`zixlogindex`** | `-`, `/`, `+` | 0 | N/A | Flag | `DAT_009467bc = 1` | Enable index logging |

---

## Phase 2 — Tracing Tokenization Defect

### Stock Redux Execution Flow (`FUN_007d5120`)

```
GetCommandLineA()
     │
     ▼
[Pristine Buffer: "battlezone98redux.exe -shellmap:216,178 -disablemods"]
     │
     ▼
strtok(buf, ", \t\r\n")  <-- DESTRUCTIVE MUTATION HERE!
     │
     ├─► Token 1: "-shellmap:216"  (Buffer modified: '-shellmap:216\0178\0-disablemods\0')
     │     │
     │     ├─► Matches _strnicmp(token + 1, "shellmap", 8) == 0
     │     ├─► sscanf("-shellmap:216" + 9, ":%d,%d", &w, &h)
     │     │     └─► Reads w = 216, returns 1 (comma & second number truncated!)
     │     ├─► Stock fallback code: if (sscanf_ret == 1) { h = w; }  => h = 216!
     │     └─► State set: _DAT_009183c4 = (216 << 16) | 216  (EXPECTED: 178 << 16 | 216)
     │
     ├─► Token 2: "178"
     │     │
     │     ├─► Prefix check: starts with '/', '-', '+'? NO ('1').
     │     └─► Falls through to positional map/savefile loader branch:
     │           strncpy(&DAT_00945708, "178", 0x1000)
     │           Checks for ".sav" extension -> FAILS
     │           Calls FUN_00434170(5) -> CRASH / FAILED MISSION LOAD!
     │
     └─► Token 3: "-disablemods"
           └─► Processed (if process survived Token 2 error state)
```

### Key Differences: 1.5 vs Redux 2.2.301

In **Battlezone 1.5**:
- Delimiters were `" \t\r\n"`.
- `strtok` returned `"-shellmap:216,178"` as a single token.
- `sscanf("-shellmap:216,178" + 9, ":%d,%d", &w, &h)` returned `2`, setting `w = 216` and `h = 178`.

In **Redux 2.2.301**:
- Delimiters were expanded to `", \t\r\n"`.
- `strtok` splits `"-shellmap:216,178"` into `"-shellmap:216"` and `"178"`.
- This causes both **incorrect state initialization** (`height` overwritten with `width`) and **spurious secondary token parsing errors**.

---

## Phase 3 — Runtime Validation & Case Analysis Matrix

| Case | Command Line Input | Stock Redux Behavior | Expected Correct Behavior | Status |
| :--- | :--- | :--- | :--- | :---: |
| **1. Valid 2-value syntax** | `-shellmap:216,178` | Splits into `"-shellmap:216"` and `"178"`. Width=216, Height=216. "178" triggers load failure. | Width=216, Height=178. Clean execution. | **FAILED IN STOCK** |
| **2. Reversed separator** | `-shellmap=216,178` | Splits into `"-shellmap=216"` and `"178"`. `sscanf` expects `:` so fails or sets W=216, H=216. | Width=216, Height=178. | **FAILED IN STOCK** |
| **3. Whitespace variants** | `-shellmap: 216, 178` | Splits into `"-shellmap:"`, `"216"`, `"178"`. `sscanf` fails completely. | Handled gracefully or sanitized. | **FAILED IN STOCK** |
| **4. Quoted values** | `-shellmap:"216,178"` | `strtok` ignores quotes and splits on comma inside quotes. | Preserves quotes and parses 216, 178. | **FAILED IN STOCK** |
| **5. Multiple CLI options** | `-shellmap:216,178 -disablemods` | `strtok` breaks `shellmap`, sets `DAT_00915568 = 1` for `disablemods` if process survives. | Both `shellmap` (216,178) and `disablemods` apply. | **FAILED IN STOCK** |
| **6. Duplicate options** | `-shellmap:100,100 -shellmap:216,178` | Stock last-wins logic executes twice on truncated tokens. Ends with W=216, H=216. | Last option wins with W=216, H=178. | **FAILED IN STOCK** |
| **7. Missing 2nd param** | `-shellmap:216` | Token is `"-shellmap:216"`. `sscanf` returns 1. W=216, H=216. | W=216, H=216 (Stock fallback intentional for 1-param form). | **PASS** |
| **8. Control: Single-param** | `-largemap:16` | Token is `"-largemap:16"`. No comma. `sscanf` reads 16 correctly. | `DAT_009183d4 = 2`, `_DAT_009183c4 = 16`. | **PASS** |
| **9. Control: Flag** | `-disablemods` | Token is `"-disablemods"`. `DAT_00915568 = 1`. | `DAT_00915568 = 1`. | **PASS** |

---

## OpenShim Preferred Fix Architecture

### Implementation Strategy
1. **Zero Replacement Risk:** Do not replace Redux's global command-line parser.
2. **Pristine Snapshot Read:** OpenShim already captures a pristine immutable command-line snapshot in `DllMain` via `BZROpenShim::RenderProfiles::CaptureCommandLineSnapshot()`.
3. **Targeted State Fixup:** Post-process the pristine snapshot to locate multi-parameter arguments like `shellmap`.
4. **State Patching:** Overwrite the target stock globals:
   - `DAT_009183d4` (RVA `0x5183d4` / `0x009183d4`): set to `1` (shellmap mode).
   - `_DAT_009183c4` (RVA `0x5183c4` / `0x009183c4`): set to `(height << 16) | width`.
5. **Preserve Stock Behavior:** All single-value options, `-disablemods`, renderer-selection (`/renderer:dx11`), option ordering, Steam/GOG startup, and quoted paths remain untouched.

### Recommended OpenShim Seam Location
Add `BZROpenShim::RepairMultiParameterCommandLineArguments()` in `src/patches/bzr_hooks.cpp` (or dedicated CLI patch unit) and invoke it immediately after stock option initialization or via resolved address post-patching.

---

## Offline Test Suite (`tests/cli_parser_tests.cpp`)

To validate stock tokenization behavior vs pristine snapshot parsing without requiring Windows DLL execution or external dependencies, an offline C++ test harness is provided in `tests/cli_parser_tests.cpp`.

### Verification Steps
Run the offline test suite using `g++`:
```bash
g++ -std=c++20 tests/cli_parser_tests.cpp -Iinclude -o /tmp/cli_parser_tests && /tmp/cli_parser_tests
```
Output:
```
Running CLI Parser Parity Tests...
[PASS] TestStockParserDefect (Confirmed stock defect: -shellmap:216,178 -> W=216 H=216, orphaned token '178' detected)
[PASS] TestPristineSnapshotRepair (All pristine snapshot repair test cases passed)
All CLI parser parity tests completed successfully!
```
