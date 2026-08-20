# Campaign-End, TRN, and Locale Runtime Investigation

Date: 2026-08-20
Scope: Battlezone 98 Redux 2.2.301 campaign-end shell flow, custom-campaign focus/minimize behavior, TRN newline/encoding handling, and German-locale resource/render failures.

## Executive summary

| Issue | Best traced root | Confidence | Candidate fix layer | Runtime validation needed |
|---|---|---:|---|---|
| Campaign mission-end screens | Mission result selects screen 19/20 before the bulk teardown; both stock and custom results enter the same factory, then success-screen metadata and final-mission logic diverge | HIGH | Redux executable patch via OpenShim, after the exact broken metadata branch is reproduced | One stock/custom, intermediate/final matrix |
| Custom-campaign focus/minimize | Redux explicitly executes `ShowWindow(hwnd, SW_MINIMIZE)` from its `WM_ACTIVATEAPP(false)` handler in fullscreen; no direct focus/window call was found in the custom `.ogv` result path | HIGH for the minimize mechanism; MEDIUM for the initiating focus loss | Redux executable patch via OpenShim only after the activating/deactivating window/process is captured | One fullscreen custom-final run with WndProc and Win32 API tracing |
| TRN newline/encoding corruption | Reader records are LF-delimited; writer raw-loads the old TRN, opens the destination in CRT text mode, and therefore grows CRLF into CRCRLF on every save | CONFIRMED | Redux parser/writer patch via OpenShim | Exercise one actual save/export action and byte-compare before/after |
| Non-English resource/render failure | Language initialization calls `setlocale(LC_ALL, "German")`; the exact Redux float getter then parses dot-decimal `0.8` as `0.0` | CONFIRMED for numeric corruption; HIGH for the reported render symptom | OpenShim-owned Redux compatibility behavior: retain German presentation categories but force data-format `LC_NUMERIC=C` | Visual German/English mission comparison and settled Steam trace |

The investigation found two upstream defects that do not belong in EXU or campaign content: the TRN serializer's text-mode rewrite and Redux's process-wide numeric-locale switch. This report was the pre-implementation baseline; the implementation continuation and validation record are appended below.

## Evidence and build identity

Evidence priority was current executable bytes/decompilation, live observations from that executable, current-binary cross references, existing OpenShim findings, and related repositories. Stored PDB names were used only as semantic hints. No PDB address, ABI, stack layout, or structure offset is treated as released-build fact.

### Exact builds

| Distribution | File size | SHA-256 | Notes |
|---|---:|---|---|
| GOG | 5,425,152 | `8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413` | PE32 x86, preferred base `0x00400000`; static and runtime target |
| Steam | 5,554,832 | `D298782FC9A13EDB0665DB934110440C45461031DB5F7FE1A76C8784B61CC90D` | Same timestamp/base and non-code section layout; on-disk SteamStub/`.bind` protection |

The GOG and Steam files have identical `.rdata`, `.data`, and `.rsrc` section hashes and the same relevant IAT addresses. Their on-disk `.text` bytes differ because of SteamStub. Existing OpenShim investigations have found settled Steam runtime code matching GOG at checked 2.2.301 sites, but the exact sites in this report were not all revalidated in a settled Steam process. Steam applicability is therefore reported as HIGH, not CONFIRMED.

Relevant shared IAT entries include `ShowWindow` `0x00869FEC`, `SetWindowPos` `0x00869FC0`, `SetForegroundWindow` `0x00869F68`, `SetFocus` `0x00869F70`, `BringWindowToTop` `0x00869F4C`, `fopen` `0x008694E0`, `fputs` `0x0086944C`, `sscanf` `0x0086950C`, `setlocale` `0x00869544`, `atof` `0x0086957C`, and `strtod` `0x008695F0`.

All addresses below are GOG virtual addresses unless labeled otherwise. With the preferred/live base `0x00400000`, `RVA = VA - 0x00400000`.

## 1. Campaign mission-end shell/state-transition audit

### Reconstructed control flow

```text
mission script/gameplay
    -> run-state setter FUN_00434170
    -> simulation finish controller FUN_00618370
       -> read run state FUN_00434160 / DAT_008E706C
       -> success (1): FUN_005D4DE0 -> screen ID 0x14
       -> failure (0 or 10): FUN_005D4CF0 -> screen ID 0x13
       -> FUN_005D5150 transition loop
          -> parent/shell screen construction FUN_007C6360, FUN_007C7930
          -> factory FUN_007C7AD0
             -> 0x13: cUI_MissionFailed ctor FUN_00792000
             -> 0x14: cUI_MissionSuccess ctor FUN_00793CA0
       -> bulk mission teardown in FUN_00618370
    -> outer simulation loop re-enters FUN_004341C0
       -> main shell/result wrapper FUN_005D42E0
          -> on successful normal progression, increment mission and call FUN_004897D0
          -> fixed stock campaign -> stock mission-browser screen
          -> custom campaign intermediate -> generic campaign screen 0x25
          -> archive/replay custom fallback -> screen 0x26
          -> completed campaign or explicit main-menu -> screen 1
```

The important ordering fact is that the modal mission-result screen is constructed and run before the long teardown sequence in `FUN_00618370`. Campaign progression is updated later by the outer shell wrapper. The evidence does not support a model where all mission state is destroyed before screen construction.

### Path matrix

| Path | Initial result screen | Screen-local branch | Exit/progression behavior |
|---|---:|---|---|
| Stock intermediate success | `0x14` | `Click_Next` sees `current + 1 != missionCount` | Closes result UI, advances shell/run state; outer wrapper increments successful progression |
| Stock final success | `0x14` | `Click_Next` sees final index | Prepares fullscreen video and starts `credits.ogv`; ctor also has stock outro metadata branches |
| Custom intermediate success | `0x14` | Same factory/constructor; depends on current campaign metadata and mission count | After teardown/progression, `FUN_00489230` falls back to generic custom screen `0x25`, which reloads mod/campaign context and constructs `cUI_Mission` |
| Custom final success | `0x14` | Generic mission `gift=*.ogv` uses the embedded Ogre Theora path; Next then plays common `credits.ogv` | Progress beyond count selects main shell ID 1; no separate custom end-screen ID/class exists |
| Failure | `0x13` | `cUI_MissionFailed` | No successful progression increment |
| Retry | `0x13` | `FUN_00791F50` | Set run state 6, clear screen, reinitialize, select loading screen `0x17` |
| Return to shell after failure | `0x13` | `FUN_00791FB0` | Set run state 2, set shell-return flag, clear screen |
| Return to shell after success | `0x14` | `FUN_00792A60` | Set run state 2, set shell-return flag, clear screen |
| Campaign completion | `0x14` | Final-index comparison in `FUN_00792AB0`; stock/custom media selected in `FUN_00793CA0` | Credits/outro or campaign result media, then return callback |

No evidence was found that custom campaigns select a different top-level mission-success screen ID. The high-value divergence is metadata/media handling inside `cUI_MissionSuccess` and the later campaign-selection logic in `FUN_005D42E0`.

### Finding 1A: mission result screen selection and teardown order

**Finding:** Run state 1 always selects screen `0x14`; failure states 0 and 10 select `0x13`. Both run through the same shell screen loop and factory before bulk mission teardown.

**Confidence:** CONFIRMED.

**Executable/build:** Exact GOG build above.

**Function:** `FUN_00618370` (mission finish controller), `FUN_005D4DE0` (success wrapper), `FUN_005D4CF0` (failure wrapper), `FUN_005D5150` (transition loop), `FUN_007C7AD0` (screen factory).

**RVA:** `0x00218370`, `0x001D4DE0`, `0x001D4CF0`, `0x001D5150`, `0x003C7AD0` respectively.

**Callers:** `FUN_00618970` calls the mission finish controller. The transition wrappers call the common screen loop, which reaches the factory through the parent screen machinery.

**Callees:** Run-state getter `FUN_00434160`; result wrappers; constructors `FUN_00792000` and `FUN_00793CA0`; the teardown list begins after the wrappers return.

**Relevant globals:** `DAT_008E706C` run state; `DAT_00918328` requested screen; `DAT_0091830C` result marker; `DAT_00918314` normal (`0`) versus archive/replay (`1`) flag; `DAT_0091831C` mission index; `DAT_00918330` shell/progression state.

**Relevant strings:** `SetRunning: was ..., now ...`; mission-failed/restart/main-menu and mission-success/main-menu logging strings; current-binary vftable names for the two result screens.

**Relevant Win32/CRT/Ogre APIs:** None at the initial result selection. UI and Ogre video APIs appear in the success constructor's later media branch.

**Working path:** A valid intermediate result enters screen `0x14`, obtains valid campaign/mission metadata, and advances.

**Broken path:** Not yet reproduced headlessly; suspected custom paths still enter `0x14` but have missing/inconsistent metadata or choose a special media branch.

**Divergence point:** Within `FUN_00793CA0`/`FUN_00792AB0` or later `FUN_005D42E0`, not the success/failure screen-ID wrapper.

**Root-cause hypothesis:** The broken campaign paths are caused by state/metadata consumed by the shared success screen, or by the final-media branch, rather than by selection of an unregistered custom screen.

**Supporting evidence:** Exact branch values, factory mappings, constructor data dependencies, and progression ordering in current executable bytes.

**Contradicting evidence:** The exact reported campaign and metadata were unavailable, so one invalid-state producer has not been proven.

**Best candidate fix point:** The earliest metadata/state producer shown to differ in a failing runtime capture. If only final custom media is broken, correct its branch inputs before the constructor creates the clip.

**Why this is upstream enough:** It preserves the common, working screen factory and fixes the state supplied to it.

**Why this is not merely symptom suppression:** It does not bypass teardown, force a screen visible, or ignore a failed media/resource lookup.

**GOG applicability:** CONFIRMED for the traced control flow.

**Steam applicability:** HIGH after SteamStub settles; exact bytes must be checked.

**Evidence that implementations differ:** Only the protected on-disk Steam wrapper is demonstrated to differ.

**OpenShim patch/signature requirements:** No patch should be installed until the failing campaign supplies a reproducible divergent field. Any eventual hook must verify exact build identity or a stable unique signature and fail closed.

**Regression risks:** Progression corruption, skipping credits/outros, retry loops, retaining torn-down mission state, or changing stock campaign completion.

**Runtime validation still required:** The six success/failure/intermediate/final stock/custom cases in the checklist below.

Additional exact path details:

- `FUN_00618A40` (RVA `0x00218A40`) owns the simulation/shell loop; mission start is `FUN_006185F0` and finish wrapper is `FUN_00618970`.
- Script-side result bodies `FUN_0045C870`/`FUN_0045C8B0` (RVAs `0x0005C870`/`0x0005C8B0`) set success/failure. Game-key handler `FUN_0061DC10` can set failure, success, or quit for gated single-player tests.
- `FUN_007932C0` sets result marker 2. Progression happens only after end UI and teardown when `FUN_005D42E0` re-fetches campaign/index, increments success, and calls `FUN_004897D0`.
- Fixed stock campaigns map to mission-browser IDs 7, 8, 9, `0x21`, and `0x22`; custom normal progression falls back to `0x25`. The `0x25` factory branch reloads active mod/campaign context and constructs generic `cUI_Mission` at `FUN_0078F030` (RVA `0x0038F030`).
- Archive/replay bypasses normal progression and maps fixed campaigns to `0x18`, `0x1A`, `0x19`, `0x23`, and `0x24`; custom fallback is `0x26`.
- An invalid current mission index is treated as non-final by `FUN_00792AB0`, then later clamped to zero and incremented by the post-teardown progression path. This internally inconsistent fallback is a concrete candidate for broken custom metadata cases.

### Finding 1B: final-success and custom-media branch

**Finding:** `cUI_MissionSuccess` has distinct stock outro and generic campaign-result-media branches. Generic `.ogv` media is created inside the process with Ogre Theora; it does not launch a browser or external player.

**Confidence:** HIGH.

**Executable/build:** Exact GOG build above.

**Function:** Success constructor `FUN_00793CA0`; next/final handler `FUN_00792AB0`; video preparation `FUN_00793070`; result display `FUN_007932C0`; clip creation `FUN_007D3850`; clip play `FUN_007D3DD0`.

**RVA:** `0x00393CA0`, `0x00392AB0`, `0x00393070`, `0x003932C0`, `0x003D3850`, `0x003D3DD0`.

**Callers:** Screen factory for constructor; success-screen UI callbacks for next/return/video flow.

**Callees:** Campaign index/count getters `FUN_004888B0`/`FUN_004885D0`; embedded Ogre Theora texture/clip creation and playback.

**Relevant globals:** Current campaign string `DAT_0094FEE0`; built-in campaign strings `DAT_0094FFE0` (`usa`), `DAT_0094FEA8` (`ussr`), `DAT_0094FE78` (`blackdogs`), `DAT_0094FE90` (`chinese`), `DAT_0094FEF8` (`training`); mission index/result globals above.

**Relevant strings:** `credits.ogv`, `outro.ogv`, `01TRO_OutroV1.ogv`, `.ogv`, and the `movie` material/resource name.

**Relevant Win32/CRT/Ogre APIs:** `Ogre::ExternalTextureSourceManager`; `OgreTheoraVideoManager::createClip`; material clone and texture-state operations. No direct `ShellExecute`, process creation, focus, or window-state call is present.

**Working path:** Stock final mission chooses known stock media; valid generic `.ogv` gift metadata creates an embedded clip. Installed packaged custom campaign `819834262` has mission 52 `gift="outro.ogv"`, demonstrating a concrete custom-final double-video path: gift, then common credits.

**Broken path:** Candidate: custom final metadata is absent, stale, malformed, or enters the generic media/UI branch with inconsistent campaign state.

**Divergence point:** Campaign/media selection in `FUN_00793CA0` and final-index comparison in `FUN_00792AB0`.

**Root-cause hypothesis:** Custom final failures are metadata/state or embedded-video lifecycle defects, not a distinct screen ID or external-launch path.

**Supporting evidence:** Exact strings, calls, and lack of process/window API calls in the branch.

**Contradicting evidence:** No unattended transition reached the specific reported custom end screen.

**Best candidate fix point:** Campaign media/state validation immediately before the branch that prepares/creates the clip, once the failing field is captured.

**Why this is upstream enough:** It prevents an invalid screen/media lifecycle rather than repairing focus after the fact.

**Why this is not merely symptom suppression:** It leaves normal stock and valid custom video behavior intact.

**GOG applicability:** HIGH; exact code is present.

**Steam applicability:** HIGH after settled-byte verification.

**Evidence that implementations differ:** No core implementation difference demonstrated; only the protected Steam on-disk wrapper differs.

**OpenShim patch/signature requirements:** Verify constructor and media-branch bytes plus campaign metadata layout; do not use PDB offsets.

**Regression risks:** Breaking credits, stock outros, non-video result screens, or full-screen-video return callbacks.

**Runtime validation still required:** Log campaign string/index/count/result-media just before this branch for one failing custom final mission.

## 2. Custom-campaign focus/minimize extension

### Finding 2A: explicit fullscreen minimization mechanism

**Finding:** Redux explicitly minimizes its own window when it receives `WM_ACTIVATEAPP` with `wParam == FALSE` and its fullscreen flag is set. It restores with `SW_RESTORE` when reactivated.

**Confidence:** CONFIRMED for the mechanism; MEDIUM for the cause of the custom-screen activation loss.

**Executable/build:** Exact GOG build above.

**Function:** Main WndProc `FUN_00619340`.

**RVA:** `0x00219340`; exact `ShowWindow(SW_MINIMIZE)` call VA/RVA `0x0061994E`/`0x0021994E`; restore call `0x006199B0`/`0x002199B0`.

**Callers:** Registered/subclassed Redux window procedure.

**Callees:** `ShowWindow`; activation-dependent input/audio helpers; previous window procedure.

**Relevant globals:** `DAT_009183B8` fullscreen flag; `DAT_008EAAA4` active/inactive state; `DAT_008FE240` application/input mode; `DAT_00918400` previous WndProc.

**Relevant strings:** Activation/focus message names are also recognized by the input-message drain at `FUN_00619BE0`.

**Relevant Win32/CRT/Ogre APIs:** `WM_ACTIVATEAPP`, `WM_ACTIVATE`, `WM_SETFOCUS`, `WM_KILLFOCUS`, `ShowWindow(SW_MINIMIZE/SW_RESTORE)`, `CallWindowProcA`.

**Working path:** The app remains active through result-screen/video setup, so the minimize branch is never entered.

**Broken path:** Something deactivates the app during the custom end transition; fullscreen Redux then explicitly converts that deactivation into a minimize.

**Divergence point:** The first `WM_ACTIVATEAPP(FALSE)` preceding call VA `0x0061994E`. The upstream sender/new foreground owner remains unobserved.

**Root-cause hypothesis:** Minimize is secondary to an activation loss, possibly in custom video/plugin lifecycle or invalid campaign-state fallout. The direct success/media branch itself contains no focus-changing call.

**Supporting evidence:** Current-binary WndProc branch and complete static xrefs for the requested window APIs.

**Contradicting evidence:** The only unattended live shell capture was windowed and did not reach the reported custom transition.

**Best candidate fix point:** First capture the activation-loss origin. If it is a spurious transient inside embedded video setup, correct that lifecycle; only if the message is legitimate but minimizing is undesirable should the WndProc policy be changed.

**Why this is upstream enough:** It targets either the focus-loss producer or the exact minimize policy rather than blindly restoring the window later.

**Why this is not merely symptom suppression:** A restore timer or unconditional `SetForegroundWindow` would hide the symptom, steal focus, and create focus fights.

**GOG applicability:** CONFIRMED for the explicit WndProc policy.

**Steam applicability:** HIGH after settled-byte verification.

**Evidence that implementations differ:** No core implementation difference demonstrated.

**OpenShim patch/signature requirements:** Instrument WndProc message, fullscreen/active globals, foreground HWND/PID, and `ShowWindow` return address first. A patch must distinguish this exact build/policy and fail closed.

**Regression risks:** Alt-tab behavior, multi-monitor fullscreen, audio/input suspension, focus stealing, and renderer recovery.

**Runtime validation still required:** One fullscreen custom-final transition with API/message timestamps and the foreground process/window identity.

### Window-activity caller inventory

| API/action | Redux call sites (VA) | Context |
|---|---|---|
| `ShowWindow` | `0x004375FB` | Normal window show |
| `ShowWindow` | `0x00618B92` | Existing Redux instance restore |
| `ShowWindow` | `0x0061994E`, `0x006199B0` | WndProc activation minimize/restore |
| `ShowWindow` | `0x006837C0`, `0x006837CF` | Explicit renderer/fullscreen-mode hide/restore |
| `ShowWindow` | `0x007D600B` | Console HWND, `SW_SHOWNOACTIVATE`; not the mission video window |
| `SetWindowPos` | `0x004361A9`, `0x00436246` | Window-style/position update in `FUN_00435EF0` |
| `SetForegroundWindow` | `0x0043746B`, `0x00618EF1`, `0x00618F5C` | General helper and startup activation |
| `SetFocus` | `0x004375D9` | General helper |
| `BringWindowToTop` | `0x00618F7F` | Startup fallback |

`FUN_00683620` performs renderer/fullscreen-mode hide/reconfigure/restore, but no direct call from the mission-success/custom `.ogv` functions was found. No direct imports were found for `SetActiveWindow`, `SwitchToThisWindow`, `OpenIcon`, or `CloseWindow`. Static evidence therefore weighs against an external browser/player launch or render-window recreation as the direct custom-result path.

## 3. TRN newline and encoding corruption

### Reader pipeline

```text
FUN_007800C0: select terrain name / append .trn
    -> FUN_00780160 main terrain property load
    -> FUN_00786340 dimensions and .hg2/.mat setup
FUN_00829130 raw file load
    -> FUN_00828DC0: fopen("rb") + fread
    -> FUN_00787370: normalize/comments/case
       - LF is the only preserved record delimiter
       - other bytes below '!' are discarded
       - unquoted bytes are uppercased with CRT toupper
       - ;, //, and /* ... */ comments are stripped
    -> FUN_00787660: section/key scan and copy through LF
    -> typed getters
       string FUN_00787A30
       integer FUN_00787AC0
       float FUN_00787B60 -> sscanf("%f")
```

### Representation matrix

| Representation | Reader result | Writer consequence |
|---|---|---|
| LF | Accepted | Text-mode save expands LF to CRLF |
| CRLF | Accepted | Existing CR is retained, LF expands: output becomes CRCRLF |
| CR-only | Not a record delimiter; records collapse | Unsupported/corrupting |
| CRCRLF | Accepted; extra CR bytes are discarded by reader | Next save adds yet another CR |
| No final newline | Accepted for the last key/value | Save behavior depends on source buffer |
| UTF-8, no BOM, ASCII subset | Accepted bytewise | Non-ASCII interpretation is code-page dependent |
| UTF-8 BOM | No BOM decoding; BOM bytes remain, though later ASCII substring searches often still find sections | BOM retained and CRCRLF created |
| Windows ANSI/CP1252 | ASCII syntax works; quoted high bytes are preserved | Not Unicode-safe |
| UTF-16 LE/BE | No decoding; apparent ASCII success can be accidental because control/NUL bytes are discarded | Unsupported/corrupting |
| Trailing CR before LF/EOF | Discarded by normalizer | Raw writer retains it and may grow it |

### Finding 3A: LF-only logical records

**Finding:** Redux opens TRNs in binary and performs its own normalization, but only LF survives as a record delimiter. CR is whitespace, not a delimiter.

**Confidence:** CONFIRMED statically and by the actual MSVCR120 byte matrix.

**Executable/build:** Exact GOG build above; MSVCR120 12.00.40664 for writer translation probes.

**Function:** Terrain-name setup `FUN_007800C0`; main property load `FUN_00780160`; dimension/companion setup `FUN_00786340`; raw load `FUN_00829130` -> `FUN_00828DC0`; normalizer `FUN_00787370`; lookup `FUN_00787660`; typed getters `FUN_00787A30`, `FUN_00787AC0`, `FUN_00787B60`.

**RVA:** `0x003800C0`, `0x00380160`, `0x00386340`, `0x00429130`, `0x00428DC0`, `0x00387370`, `0x00387660`, `0x00387A30`, `0x00387AC0`, `0x00387B60`.

**Callers:** The normalizer is called by the three typed INI/TRN getters. Terrain lighting, clouds, stars, and height readers call the float getter.

**Callees:** `fopen("rb")`, `fread`, `toupper`, comment stripping, LF-delimited section/key lookup, and numeric `sscanf`.

**Relevant globals:** Current TRN filename `DAT_02CC40C0`; normalized static buffer `DAT_02C319E8`; cached filename `DAT_02C419E8`; normalized length/pointer `DAT_009454D0`/`DAT_009454D4`. Output is capped at approximately 64 KiB.

**Relevant strings:** File mode `rb`; section/key names such as `Sun_Ambient`, `Clouds`, `Stars`, `Height`.

**Relevant Win32/CRT/Ogre APIs:** CRT `fopen`, `fread`, `toupper`, `sscanf`; Ogre consumers occur after typed parsing.

**Working path:** CRLF, LF, or CRCRLF containing LF record separators; absent final newline.

**Broken path:** CR-only collapses logical records. BOM/Unicode inputs are not decoded. Numeric getters may appear to succeed by consuming a prefix from collapsed content.

**Divergence point:** `FUN_00787370` retains only byte `0x0A` as a record separator.

**Root-cause hypothesis:** Historical representations are handled accidentally rather than through an explicit byte-decoding/newline-normalization contract.

**Supporting evidence:** Exact byte predicates and the lookup's LF scan.

**Contradicting evidence:** UTF-16 ASCII-looking files can appear partially readable because NUL/control bytes are stripped; that is not actual UTF-16 support.

**Best candidate fix point:** Immediately after raw load: reject/identify unsupported Unicode encodings, remove a compatible UTF-8 BOM, normalize CRLF/LF/CR to one internal LF representation, then parse.

**Why this is upstream enough:** Every typed consumer receives the same normalized representation.

**Why this is not merely symptom suppression:** It defines reader compatibility rather than modifying particular terrain values after parsing.

**GOG applicability:** CONFIRMED.

**Steam applicability:** HIGH after settled-byte validation.

**Evidence that implementations differ:** No core implementation difference demonstrated; only the protected Steam on-disk wrapper differs.

**OpenShim patch/signature requirements:** Verify the load/normalizer entry and unique byte sequence; allocate/resize safely and preserve parser ownership/lifetime. Candidate entry bytes begin `55 8B EC 83 EC 1C 83 3D D4 54 94 00 00 74 29 83 3D D0 54 94 00 00`; uniqueness must be proven before use.

**Regression risks:** Comment semantics, quoted whitespace, binary garbage previously tolerated, long-file allocation, and mods depending on accidental byte stripping.

**Runtime validation still required:** Load the complete byte corpus through a visible minimal terrain and compare all parsed key values.

### Finding 3B: text-mode writer grows carriage returns

**Finding:** `FUN_00786C80` raw-loads the existing TRN, opens the destination with `fopen(..., "w")`, and writes the raw bytes with `fwrite`. MSVCR120 text mode expands every LF to CRLF, so existing CRLF becomes CRCRLF and each repeated save adds another CR. The same function uses `wb` for `.mat`/height outputs.

**Confidence:** CONFIRMED.

**Executable/build:** Exact GOG build above plus direct MSVCR120 12.00.40664 translation test.

**Function:** Writer `FUN_00786C80`; direct save-game caller `FUN_004FD190`.

**RVA:** Writer `0x00386C80`; `fopen("w")` call RVA `0x00386E6B`; `fwrite` call RVA `0x00386E9A`; save caller `0x000FD190`, call site `0x000FD31A`.

**Callers:** One direct current-binary call from the save-game path.

**Callees:** Raw loader, `fopen`, `fwrite`; binary modes for the companion terrain outputs.

**Relevant globals:** Source/current terrain state and save destination passed to the function.

**Relevant strings:** `w`, `wb`, and companion terrain extensions.

**Relevant Win32/CRT/Ogre APIs:** MSVCR120 text/binary stream translation.

**Working path:** A pristine LF input is converted once to CRLF and appears canonical.

**Broken path:** A canonical CRLF source is rewritten as CRCRLF; repeated saves grow CR runs deterministically.

**Divergence point:** Destination mode `"w"` while writing an already newline-encoded raw buffer.

**Root-cause hypothesis:** The serializer mixes raw input preservation with CRT logical-text output.

**Supporting evidence:** Exact file modes and direct byte matrix. The `.mat`/height `wb` branches demonstrate that binary output was available in the same function.

**Contradicting evidence:** Reader stripping hides extra CRs during many loads, which can mask rather than refute the corruption.

**Best candidate fix point:** Build a canonical serialized buffer with one internal LF per logical record, emit deterministic compatible bytes with CRLF, and write in binary mode.

**Why this is upstream enough:** It prevents malformed bytes from being produced.

**Why this is not merely symptom suppression:** Merely changing `"w"` to `"wb"` stops growth but preserves arbitrary old bytes; merely fixing the reader leaves the writer corrupting files.

**GOG applicability:** CONFIRMED.

**Steam applicability:** HIGH after settled-byte validation.

**Evidence that implementations differ:** No core implementation difference demonstrated; only the protected Steam on-disk wrapper differs.

**OpenShim patch/signature requirements:** Hook/signature the writer and verify the `"w"`/`fwrite` call context. Do not normalize arbitrary handles globally.

**Regression risks:** Exact comment/format preservation, source/destination aliasing, error handling, long lines, final-newline policy, save-game compatibility, and partial-write cleanup.

**Runtime validation still required:** Trigger an actual Redux save twice from identical CRLF input and confirm both outputs are byte-identical canonical CRLF.

**OpenShim note:** The current CloseHandle normalizer is downstream compatibility behavior. Its CRCRLF handling can map to two CRLF records, so it is not an exact repair of the producer and should not be considered the architectural fix.

The precise writer mode site is VA `0x00786E5F` (`push "w"`), followed by `fopen` at `0x00786E6B`. Candidate surrounding bytes are `68 5C 67 87 00 8D 85 7C EF FF FF 50 FF 15 E0 94 86 00`. A minimal operand redirect to the existing `"wb"` string stops CR growth but intentionally is not the complete canonical serializer described above.

### Existing compatibility hook boundary

`src/patches/file_io_hooks.cpp` already tracks TRN writes through file APIs and normalizes on close. It remains useful as a safety net, but it is not the primary correction point:

- It cannot make Redux accept a historical file before any tracked write.
- Its current CRCRLF algorithm can turn one corrupted terminator into two CRLF records/one blank record.
- UTF-8 without BOM is not decoded; conversion to `CP_ACP` is machine-dependent and can be lossy.
- It runs downstream of the exact `FUN_00786C80` producer defect.

If retained, the compatibility normalizer needs a regression test that collapses a contiguous CR run followed by LF to one logical newline. EXU's unrelated atlas reader uses `std::getline` and strips a trailing CR; it is not the owner of the core terrain parser/writer.

### Recommended TRN byte contract

The current writer performs no character-encoding conversion: it preserves source bytes and only lets CRT text mode transform every `0x0A`. A deterministic replacement should make the contract explicit:

1. Reader: recognize UTF-8 BOM and UTF-16 BOM forms explicitly; for unmarked input, accept valid UTF-8 or fall back to Windows-1252 for historical ANSI content; normalize CRLF, LF, and CR to internal LF before the existing grammar.
2. Internal representation: parse logical Unicode/text values with locale-independent ASCII syntax and dot-decimal numbers.
3. Writer: emit strict Windows-1252 without BOM where representable, exactly CRLF, and one documented final newline, using binary I/O. Windows-1252 is the closest deterministic form of Redux's known-compatible historical ANSI contract; an unrepresentable value should be reported, not silently substituted.
4. Corpus tests: require semantic equality for compatible inputs and byte-for-byte equality across repeated saves.

If broader Unicode TRNs are desired later, that is a versioned format decision; silently switching the writer to UTF-8 would not be compatible with the released bytewise parser.

## 4. German locale/resource/render failures

### Confirmed producer-to-symptom chain

```text
startup FUN_00618C10 call 0x00618E41
    -> language initializer FUN_0081DF00
       -> setlocale(LC_ALL, "English")
       -> resolve game/system language
       -> German enum 2: setlocale(LC_ALL, "German")
          -> LC_NUMERIC becomes German_Germany.1252
    -> data parser FUN_00787B60
       -> section/key lookup into a 16-byte buffer
       -> sscanf(buffer, "%f", &value)
          "0.8" -> success with 0.0
          "1.25" -> success with 1.0
    -> terrain/Ogre consumers receive the wrong value
```

### Finding 4A: process-wide language/numeric-locale conflation

**Finding:** Redux maps its language choice to process-wide `LC_ALL`. German selection therefore changes the numeric parser/formatter contract for data files authored with dot decimals.

**Confidence:** CONFIRMED.

**Executable/build:** Exact GOG build above; runtime PID 13992, module base `0x00400000`, command line `/nointro`.

**Function:** Language initializer `FUN_0081DF00`; language resolver `FUN_0081DEE0`; system-language mapper `FUN_00437380`; startup caller `FUN_00618C10`.

**RVA:** `0x0041DF00`, `0x0041DEE0`, `0x00037380`, `0x00218C10`; startup call site RVA `0x00218E41`, post-call RVA `0x00218E46`; German `setlocale` call VA `0x0081DFA6`.

**Callers:** Startup path `FUN_00618C10`.

**Callees:** `setlocale`; config/system language resolution; `GetSystemDefaultLCID` with primary-language masking.

**Relevant globals:** `DAT_02CC40A4` language enum; config pointer `DAT_0094672C` and language override at `+0x4C`; `PTR_DAT_008FE1B8`; `DAT_02CC40A0`; `DAT_00946728`.

**Relevant strings:** `English`, `German`, `Spanish`, `Game Language Is: %s - %s\n`.

**Relevant Win32/CRT/Ogre APIs:** `setlocale(LC_ALL, ...)`, `GetSystemDefaultLCID`. The app does not enable per-thread CRT locales; `_configthreadlocale` is only in compiler runtime startup.

**Working path:** English locale leaves decimal point `.` and dot-decimal data parses fully.

**Broken path:** German locale changes decimal point to `,` while TRN/ODF/config content remains dot-decimal.

**Divergence point:** Full-locale switch in `FUN_0081DF00`.

**Root-cause hypothesis:** Redux incorrectly treats data serialization locale as UI language.

**Supporting evidence:** Exact startup branch and runtime `LC_NUMERIC` values.

**Contradicting evidence:** Some individual parsers temporarily switch `LC_NUMERIC` to `C`, so not every numeric path fails.

**Best candidate fix point:** Immediately after the language initializer returns, enforce `setlocale(LC_NUMERIC, "C")` while retaining German `LC_CTYPE`, `LC_TIME`, and other desired presentation categories.

**Why this is upstream enough:** It fixes all later data readers and writers that correctly assume locale-independent interchange data.

**Why this is not merely symptom suppression:** It prevents bad values before terrain/resources reach Ogre.

**GOG applicability:** CONFIRMED statically and at runtime.

**Steam applicability:** HIGH; requires settled-runtime validation at the initializer, caller, parser, and IAT target.

**Evidence that implementations differ:** SteamStub/on-disk wrapper only; no settled core divergence shown.

**OpenShim patch/signature requirements:** Exact build/hash or stable unique signature for `FUN_0081DF00`/post-call site; install after SteamStub settlement; verify expected bytes and fail closed.

**Regression risks:** German user-facing number formatting changes to dot; historical comma-decimal mod inputs still need reader compatibility; process-global `setlocale` remains thread-racy.

**Runtime validation still required:** Confirm no later language reload resets `LC_NUMERIC`; run the visible terrain differential and settled Steam trace.

### Finding 4B: exact Redux float-parser failure

**Finding:** `FUN_00787B60` calls `sscanf(buffer, "%f", &float)` without a locale guard and accepts return value 1 after only an integer-prefix parse.

**Confidence:** CONFIRMED.

**Executable/build:** Exact GOG build above.

**Function:** Float getter `FUN_00787B60`; `sscanf` call VA/RVA `0x00787BEA`/`0x00387BEA`.

**RVA:** `0x00387B60`.

**Callers:** `FUN_0067DD60` (TRN Sun ambient/diffuse/specular RGB); `FUN_00775E80` (cloud sizes/heights); `FUN_00776690` (stars geometry/orientation); `FUN_0077E490` and `FUN_007859D0` (terrain height paths).

**Callees:** Normalizer `FUN_00787370`; key lookup `FUN_00787660`; MSVCR120 `sscanf` IAT `0x0086950C`.

**Relevant globals:** Current TRN `DAT_02CC40C0`; render/config state around `0x008F0620`.

**Relevant strings:** `%f`; `Sun_Ambient`, `Sun_Diffuse`, `Sun_Specular`, `Clouds`, `Stars`, `Height`.

**Relevant Win32/CRT/Ogre APIs:** `sscanf`; then Ogre SceneManager ambient light and Light color calls.

**Working path:** Exact enabled-mod file `abbar7.odf`, `[GameObjectClass] heatSignature=0.8`, returns `0.8000000119` under English.

**Broken path:** The same in-process exact function/file/key returns `0.0` under `German_Germany.1252`. `1.25` similarly returns `1.0` in CRT tests.

**Divergence point:** Unguarded `%f` conversion at RVA `0x00387BEA`.

**Root-cause hypothesis:** Silent prefix parse propagates plausible but wrong terrain/config values into renderer/resource construction.

**Supporting evidence:** Direct in-process call to VA `0x00787B60`; same bytes and file, only locale varied; locale restored after each probe.

**Contradicting evidence:** The exact real-world reporter asset is unavailable. Sampled CR/BZ1 TRNs lacked decimal literals, so another custom TRN/config may have triggered the report.

**Best candidate fix point:** Global numeric-data contract after language initialization, plus tolerant reader normalization if historical comma-decimal content must be supported.

**Why this is upstream enough:** It corrects parser inputs/results before Ogre calls.

**Why this is not merely symptom suppression:** No missing texture, bad light, or terrain value is patched downstream.

**GOG applicability:** CONFIRMED.

**Steam applicability:** HIGH pending settled runtime.

**Evidence that implementations differ:** No settled parser implementation difference demonstrated; only the protected Steam on-disk wrapper differs.

**OpenShim patch/signature requirements:** Prefer the startup locale seam; a narrow float-getter detour misses `atof`, formatting, and other unguarded consumers.

**Regression risks:** Dual-decimal acceptance ambiguity and malformed inputs that currently prefix-parse.

**Runtime validation still required:** Correlate the bad parsed value to the exact visible failing mission/resource report.

### Existing guarded parsers and race bound

`FUN_00589800` (RVA `0x00189800`), `FUN_00589CA0` (`0x00189CA0`), `FUN_00589DF0` (`0x00189DF0`), and terrain tile color/resource parser `FUN_0077AA50` (`0x0037AA50`) save `LC_NUMERIC`, set it to `C`, parse floats/vectors/colors, and restore it. These functions corroborate that data is intended to be dot-decimal. They also show that Redux's defense is incomplete. Because locale is process-wide, temporary save/set/restore guards can race other threads.

### Code-page/path/case audit

No direct resource-path encoding defect was confirmed.

- The binary imports `WideCharToMultiByte`, `MultiByteToWideChar`, `CreateFileW`, and several wide filesystem APIs, but not direct `GetACP`, `GetOEMCP`, `GetUserDefaultLCID`, `GetThreadLocale`, `GetSystemDefaultLocaleName`, or `CreateFileA`.
- Direct app conversion callers `FUN_00759940` and `FUN_006AFBA0` are Winsock address conversions, not Ogre resource paths.
- CRT codecvt/file helpers at `0x00843B10`/`0x00843B70` choose ACP/OEMCP but were not tied to resource loading.
- Redux's English and German locales are both Windows-1252, so `ä ö ü ß` are representable; this makes a German-only code-page explanation less likely than the confirmed numeric failure.
- `FUN_00787370` applies locale-sensitive `toupper` to unquoted config bytes while preserving quoted bytes. This is a secondary, SPECULATIVE resource-name/case risk, not a demonstrated de-DE divergence.

### Finding 4C: code-page/path and case handling remain bounded secondary candidates

**Finding:** No app-level German-specific filesystem conversion failure was found. Locale-sensitive bytewise uppercasing remains a possible non-ASCII resource/config hazard.

**Confidence:** SPECULATIVE.

**Executable/build:** Exact GOG build above.

**Function:** Network-only direct conversion callers `FUN_00759940` and `FUN_006AFBA0`; CRT file-codecvt helpers at VA `0x00843B10`/`0x00843B70`; config normalizer `FUN_00787370`.

**RVA:** `0x00359940`, `0x002AFBA0`, `0x00443B10`, `0x00443B70`, `0x00387370`.

**Callers:** Winsock address conversion paths for the first two; CRT/library callers for the codecvt helpers; the three typed getters for the config normalizer.

**Callees:** `MultiByteToWideChar(CP_ACP)`, `WideCharToMultiByte`, `AreFileApisANSI`, and locale-sensitive `toupper`.

**Relevant globals:** Current TRN/cache globals listed above.

**Relevant strings:** Quoted values are preserved; unquoted key/section bytes are uppercased. No failing resource path string was captured.

**Relevant Win32/CRT/Ogre APIs:** The conversion and CRT APIs above. No failing Ogre resource-path caller was connected to these sites.

**Working path:** CP1252-representable `ä ö ü ß`, especially inside quoted values, under both Redux English and German selections.

**Broken path:** Candidate only: UTF-8 bytes or characters outside the active ACP pass through byte-oriented CRT/resource APIs and may be changed, rejected, or miscompared.

**Divergence point:** Not established. The first exact differing requested/opened resource name must be captured before proposing a path hook.

**Root-cause hypothesis:** A separate non-ACP or bytewise case-normalization defect may exist, but it does not explain the already reproduced dot-decimal failure.

**Supporting evidence:** ANSI CRT/resource usage and locale-sensitive `toupper`.

**Contradicting evidence:** Both tested language locales are Windows-1252, target German characters are representable, and direct app conversion xrefs are networking-only.

**Best candidate fix point:** None yet. If a differential is captured, fix the earliest path decode/normalization boundary rather than Ogre's missing-resource result.

**Why this is upstream enough:** The required evidence would identify the malformed requested path before resource lookup.

**Why this is not merely symptom suppression:** Texture fallback or catch-and-ignore behavior is explicitly rejected.

**GOG applicability:** SPECULATIVE.

**Steam applicability:** SPECULATIVE; no implementation difference demonstrated beyond SteamStub.

**Evidence that implementations differ:** None beyond the protected Steam on-disk wrapper.

**OpenShim patch/signature requirements:** Do not install a path/code-page hook without exact caller/RVA/string evidence and build gating.

**Regression risks:** Breaking archive names, mod compatibility, ACP systems, case-insensitive lookup, or network conversions.

**Runtime validation still required:** Identical mod under ASCII, CP1252 German, and non-CP1252 paths while tracing exact filesystem/Ogre requested names.

## Ownership and candidate correction layers

| Finding | Owner | Rationale |
|---|---|---|
| Numeric-locale/data-format contract | OpenShim-owned compatibility behavior implemented as a guarded Redux executable hook | Core startup/parser state; cannot be correctly owned by EXU or content |
| TRN reader normalization | Redux executable patch via OpenShim | Core parser contract shared by terrain/config consumers |
| TRN canonical writer | Redux executable patch via OpenShim | Core serializer producer; global handle cleanup is too downstream |
| Campaign result metadata divergence | Redux executable patch via OpenShim if runtime proves core mishandling; campaign/content only if metadata itself is invalid | Ownership follows the earliest proven bad producer |
| Focus/minimize policy | Redux executable patch via OpenShim only after activation origin is known | Native WndProc/window lifecycle |
| EXU | None currently | No traced defect belongs to EXU |
| Tooling/data migration | Optional diagnostics only | Mass conversion is not the primary fix |

## OpenShim implementation constraints

1. Do not use raw PDB addresses or copied leaked-build layouts.
2. Gate GOG/Steam by executable fingerprint and expected settled code bytes, not filename alone.
3. For Steam, wait for SteamStub settlement before scanning or installing; fail closed on mismatch instead of treating signature failure as normal flow.
4. Prefer external patterns/signatures in `scripts/patches.json` over hard-coded feature RVAs.
5. Preserve stock English/German UI behavior, stock campaign videos, retries, shell returns, and alt-tab/fullscreen behavior.
6. Add runtime logging sufficient to correlate process VA -> module base -> RVA -> current decomp function.

## Minimal remaining validation

### Campaign and focus

1. Launch exact GOG 2.2.301 in fullscreen with WndProc, `ShowWindow`, foreground-window, process-launch, and video-clip tracing enabled. The unattended startup trace at `C:\Users\iestu\AppData\Local\Temp\bzr_campaign_window_startup_trace.log` already confirms base `0x00400000` and static/runtime correlation for the startup window call sites, but used windowed D3D11.
2. Run one stock intermediate success, stock final success, custom intermediate success, custom final success, failure/retry, and failure/return-to-shell.
3. At result entry, record run state, screen ID, result marker, campaign string, mission index/count, archive/replay flag, and result-media filename.
4. For the custom final transition, record every `WM_ACTIVATEAPP`, `WM_ACTIVATE`, `WM_SETFOCUS`, `WM_KILLFOCUS`, `WM_SIZE`, and `WM_SYSCOMMAND`, plus foreground HWND/PID.
5. If `WM_ACTIVATEAPP(FALSE)` occurs, confirm the next Redux call is `0x0061994E` and identify the new foreground owner. This single observation separates the focus-loss producer from the confirmed minimize policy.

### TRN

1. Use equivalent minimal TRNs encoded as LF, CRLF, CR-only, CRCRLF, no-final-newline, UTF-8/no-BOM, UTF-8/BOM, CP1252, and UTF-16LE/BE.
2. Load each and record normalized section/key/value results at `FUN_00787660` and the typed getters.
3. Starting with canonical CRLF, invoke the actual Redux save twice.
4. Confirm the current build produces successively longer CR runs; after a fix, require byte-identical CP1252/ASCII-compatible output with exactly CRLF and a documented final-newline policy.

The bounded unattended probe used a copied CR-only `misn04.trn` (3,141 bytes, 161 CR, 0 LF, SHA-256 `0291B10C2E7B7D76AB227447BD9CB0C67E4BF36B36A5411B090503CCA6D563C6`). It launched PID 22320 at base `0x00400000` with hooks on `0x00787370` and `0x00787660`, but remained behind the unattended shell/loading popup for 20 seconds; neither parser hook was reached and the process was terminated. This is explicitly `NOT_REACHED`, not negative parser evidence. Durable ignored artifacts, including the byte matrix and launch record, are under `reverse_engineering/tooling_smoke/trn_trace_20260820/`.

### German differential

1. Use the same executable, command line, assets, and configuration; vary only Redux language/numeric locale.
2. Load a minimal visible TRN with decimal lighting values such as `Sun_Ambient Red/Green/Blue=0.8`.
3. Record the string and result at `FUN_00787B60`/`0x00787BEA` and the values delivered to Ogre.
4. Apply only the candidate `LC_NUMERIC=C` behavior and repeat; require identical English/German parsed and Ogre values.
5. If a failure remains, move the same mod under a CP1252 path containing `ä ö ü ß` and trace exact resource/open requests. Test non-CP1252 names separately rather than labeling both tests "German Windows."
6. Repeat on Steam only after its code has settled and verify the four exact locale sites before installing any hook.

## Reproduction notes

The live GOG capture used PID 13992, module base `0x00400000`, image size 43,053,056, and command line `battlezone98redux.exe /nointro`. Initial `LC_NUMERIC` was `English_United States.1252`; the test restored locale after each transient Frida call. The ignored diagnostic capture is under `reverse_engineering/tooling_smoke/campaign_trn_locale_20260820/gog_runtime_capture/gog_live/runtime_capture_20260820_085804`; it is not intended for source control.

Static correlation used the current GOG decompilation corpus under `reverse_engineering/repo_corpora/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps`, Rizin xrefs, exact import/section inspection, and the repository's stable `bzr-*` wrappers.

## Implementation continuation (2026-08-20)

### Numeric-locale compatibility patch

OpenShim now replaces only the exact startup call at VA `0x00618E41` with a
call to a shim wrapper. The wrapper first calls the original language
initializer at `0x0081DF00`, then calls `setlocale(LC_NUMERIC, "C")` through
Redux's own MSVCR120 IAT function. It does not call `setlocale(LC_ALL, "C")`.
Runtime diagnostics record the language result, numeric locale before/after,
and the composite category state.

The site is described by a unique external signature in
`scripts/patches.json`, requires the exact five expected call bytes, and has no
fallback-address path. Patch installation additionally requires one of the two
pinned executable SHA-256 values above and the exact settled context bytes.
Steam performs a bounded settlement wait and retries only this three-signature
compatibility group if SteamStub rewrites a page between the settlement sample
and scan; each retry still requires exactly one match.

The local automated CRT probe produced:

```text
English probe: LC_NUMERIC=C parses 0.8 exactly
German probe: decimal-before=, LC_NUMERIC=C presentation-categories-preserved=yes
```

The live GOG run logged English presentation categories unchanged with
`LC_NUMERIC=C`. The visible German terrain differential remains an unlocked
workstation validation item; the German CRT behavior and compatibility result
are automated.

### TRN producer correction and safety layer

The exact writer's `push "w"` at `0x00786E5F` is redirected to shim-owned
`"wb"`, and only the writer's indirect `fwrite` at `0x00786E9A` is redirected
to the canonical serializer. Both sites must resolve uniquely and pass exact
expected-byte/MSVCR120 ownership checks before the two-site group is written.
If the second write fails, the first site is rolled back.

The shared codec performs this deterministic pipeline:

```text
raw bytes
    -> explicit UTF-8/CP1252 classification (UTF-16 is unsupported)
    -> CRLF/LF/CR and corrupt CR-run normalization
    -> one logical LF representation with one final newline for non-empty input
    -> CP1252-compatible CRLF serialization
    -> MSVCR120 fwrite on a binary stream
```

UTF-8 with or without BOM is converted strictly to Windows-1252 when
representable. Historical invalid-UTF-8 byte streams are treated as CP1252.
UTF-16, invalid BOM-marked UTF-8, or unrepresentable Unicode is reported and
preserved byte-for-byte through the now-binary writer rather than guessed or
silently substituted.

`file_io_hooks.cpp` remains as a compatibility/safety layer for TRN writes
outside the corrected Redux producer. It uses the same codec and no longer
maps one `CRCRLF` terminator to a blank logical record. It also no longer
silently converts UTF-16 through the machine ACP.

`trn_codec_tests` covers LF, CRLF, CR-only, CRCRLF, no final newline, UTF-8
with/without BOM, CP1252, UTF-16LE/BE/unmarked rejection, logical-record
preservation, and repeated byte-identical serialization. The actual in-game
save action still needs one unlocked invocation to confirm the end-to-end
caller/UI error path and resulting file bytes.

### Settled Steam runtime validation

Steam Redux was launched without desktop input by setting app identity
environment values (`SteamAppId`, `SteamGameId`, and `SteamOverlayGameId` to
`301650`) and starting the executable directly. The settled capture used PID
`33120`, module base `0x00400000`, module size `43,184,128`, and executable
SHA-256 `D298782FC9A13EDB0665DB934110440C45461031DB5F7FE1A76C8784B61CC90D`.

The settled Steam bytes matched GOG at all checked candidates:

- startup/language call context `0x00618E38`;
- language initializer `0x0081DF00` and German `setlocale` branch
  `0x0081DF98`;
- float getter `0x00787B60`;
- TRN writer mode/`fwrite` context `0x00786E4F`;
- TRN reader normalizer `0x00787370`;
- fullscreen minimize site `0x00619940`.

A final implementation run used Steam PID `30692`. All three external
signatures resolved exactly once at `0x00618E41`, `0x00786E5F`, and
`0x00786E9A`; the hash and settled-byte gates passed; live reads showed the
three call/immediate redirects installed; and the post-language diagnostic
reported `LC_NUMERIC=C` with the other English categories unchanged. No
Steam-specific signatures were required.

### Prepared custom-final instrumentation

`campaign_focus_final_trace.js` and
`run_campaign_focus_final_trace.ps1` provide the remaining one-run trace. A
locked-workstation smoke run verified the byte gates, Frida hooks, foreground
HWND/PID/process lookup, state capture, and Theora create/play events. During
that smoke run the foreground owner was correctly identified as Windows
`LockApp.exe`; no campaign-final claim is inferred from it.

The later manual sequence is now only: run the wrapper, complete or force the
affected custom final mission, observe the transition, and exit. The trace
records run state, selected screen, campaign string, mission index/count,
result marker, archive/replay flag, result-media filename, all requested
window messages, every `ShowWindow` call/caller, foreground identity, and
Theora creation/playback. The fullscreen minimize call remains unpatched.
