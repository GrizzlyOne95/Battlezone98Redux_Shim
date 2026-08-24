# IAT patching raced the Windows loader (2026-08-22)

Starting commit: `8cf4e2ee` (`main`). Branch: `agent/iat-patch-hardening`.
Runtime: GOG Battlezone 98 Redux 2.2.301.

## The defect

Two unhandled write access violations were captured across 22 game launches
(~9%):

```text
[CRASH] 2026-08-22 12:25:36 unhandled code=0xC0000005 eip=0x6DFDA917 (WINMM.dll+0x0007A917) write=0x6B5F6FF4 tid=41188
[CRASH] 2026-08-22 15:09:12 unhandled code=0xC0000005 eip=0x6DFDA9F7 (WINMM.dll+0x0007A9F7) write=0x6C176FF4 tid=41804
```

Both symbolize (llvm-symbolizer against the matching `winmm.pdb`) to
`PatchIatFunction` in `src/patches/dx11_colorspace_diagnostic.cpp`, reached from
`DiscoveryThreadProc`.

### Attribution, confirmed rather than assumed

The stack-scan frames in a crash record are a heuristic, so the attribution was
checked against the run logs before any code was changed:

- **Thread identity.** The crashing thread in the first record is `tid=41188`.
  The run log for that process (pid 39200) shows
  `[dx11-colorspace] [DX11 Observer] opt-in diagnostics enabled` on
  **`tid:41188`** — the same thread.
- **Timing.** The log records `found RenderSystem_Direct3D11.dll module=0x6B520000`
  at `17:25:36.849Z` and **never** records the `installed=` line that follows it.
  The crash timestamp is that same second.
- **Address.** `write=0x6B5F6FF4` is module base `0x6B520000` + `0xD6FF4`, i.e.
  an IAT slot in the last four bytes of its page, inside the module being
  patched.
- **Reachability.** The discovery thread only starts when
  `OPENSHIM_TRACE_DX11_COLORSPACE` or `OPENSHIM_TERRAIN_RENDER_PROBE` is set.
  The installed `openshim.ini` on this machine has `[Diagnostics]
  TraceDX11ColorSpace=1`, so it starts on every launch here.

**Correction to the original report:** these did *not* crash ~100 ms into
startup. The first crashed about six seconds in, at the moment
`RenderSystem_Direct3D11.dll` appeared. The consequence is the same — no mission
had loaded — but the trigger is renderer load, not process start.

## Root cause

`GetModuleHandleW`/`GetModuleHandleA` report a module as soon as the loader has
put it in the module list. That happens **before** the loader has snapped the
module's imports and re-applied its final section protections. The discovery
thread polls for the module and patches its IAT the instant it answers, so:

1. our thread calls `VirtualProtect(entry, 4, PAGE_READWRITE)` — succeeds;
2. the loader concurrently re-protects the IAT page as part of finishing the
   load;
3. our `*entry = replacement;` store faults.

This is a genuine race with the loader, not a bad pointer.

## Three sites, not two

The original task asked whether a shared hardened helper was the right factoring
rather than fixing two sites independently. Surveying the codebase found
**three** IAT patchers with materially different exposure:

| Site | Thread | Target | Races the loader? |
|---|---|---|---|
| `dx11_colorspace_diagnostic.cpp` `PatchIatFunction` | discovery thread | `RenderSystem_Direct3D11.dll` | **yes — crashed twice** |
| `ogre_animation_profiler/patch_scopes.inl` `PatchIatFunctionByName` | profiler worker thread | **the same module, the same way** | **yes — same exposure** |
| `file_io_hooks.cpp` `PatchIATByFuncName` | patcher, main thread | the main executable | no concurrent load of the exe |

The first two share the hazard exactly: both poll `GetModuleHandle` for
`RenderSystem_Direct3D11.dll` from their own background thread and patch it
immediately. That is what justifies the shared helper — it is now an
evidence-based factoring rather than a speculative one.

The third is left alone deliberately. Its hazard profile is different, and
`file_io_hooks.cpp` is being rewritten by open PR #42; refactoring it now would
create merge friction for no crash-reduction benefit. (PR #42 does not itself
touch `PatchIATByFuncName` — 0 diff lines mention it.)

## The fix

New `include/iat_patch.h`:

- **`WaitForModuleLoadToFinish()` closes the race.** Taking a real reference by
  full path (`GetModuleFileNameW` then `LoadLibraryExW`) serialises on the loader
  lock, so it returns only once any in-flight load of that exact file has
  completed. The reference is deliberately never released: the observers'
  function pointers live in that module's IAT for the rest of the process, so
  pinning it also removes any chance of an unload racing the patched entries.
- **`PatchImport()` is the second line of defence.** Every RVA is bounds-checked
  against `SizeOfImage` through a `MappedImageView`; the descriptor walk is
  bounded by the import directory's declared `Size` rather than a NUL terminator
  that may not be written yet; the thunk walk is bounded by containment; import
  name strings are scanned without leaving the image; and the whole walk runs
  under structured exception handling so a fault returns `Result::Faulted`
  instead of killing the process.
- **`Result` is tri-state.** `NotFound` is distinguished from `Faulted`, which
  matters: the released renderer imports `D3D11CreateDevice` but creates its
  swap chain through the DXGI factory, so `D3D11CreateDeviceAndSwapChain` is
  legitimately absent. Conflating the two would have made every launch retry and
  then log a spurious failure.

Applied at the two racing sites:

- `dx11_colorspace_diagnostic.cpp` now waits for the loader, then retries a
  bounded 8 times on a fault before giving up with a warning. Giving up costs
  only optional diagnostics; rendering is unaffected either way.
- `ogre_animation_profiler` takes the same loader wait before
  `InstallDx11CreationObservers`, and its `WritePointer` — used by both the IAT
  patcher and the COM vtable patcher, and carrying the identical
  protect-then-store pattern — now performs its store under SEH so a lost race
  fails the patch instead of the process. Its own mutex and patch-restore
  bookkeeping are untouched.

## Validation

Static, on the final head: Release Win32 MSBuild clean (no new warnings beyond
the pre-existing `C4505`/`STL4038` set); Ogre profiler algorithm tests passed;
INI/config tests 23 checks / 0 failures; network-safety baseline passed;
`git diff --check` clean.

Runtime, 24 consecutive launches on the final head (plus 20 on a functionally
equivalent intermediate build, 44 total):

| Outcome | Count |
|---|---:|
| Colorspace observer installed | 24 / 24 |
| Profiler observer installed | 23 / 24 |
| Patch faults | 0 |
| Retries exhausted ("gave up") | 0 |
| Loader-wait failures | 0 |
| New unhandled access violations | **0** |

Log scan across all 24: zero `[ERROR]`, unhandled AVs, `Ogre::Exception`,
`faulted`, `gave up`, or `without a loader wait`.

`installed=1` rather than `2` is **pre-existing and correct**, not a regression:
the same value appears in benchmark logs captured before this change. It is the
`NotFound` case described above.

The one run without a profiler install is a harness artifact: that log ends at
the exact millisecond the colorspace site logged `installed=`, and the harness
kills the process on that line, so the profiler thread had not reached its patch
yet.

### How strong is the evidence

Stated plainly rather than overclaimed. Against a 2/22 (9.1%) baseline, seeing
0 failures in 44 launches has probability ~1.5% if the rate were unchanged, so
the runs are good evidence but not proof. The stronger argument is mechanical:
the race is closed by construction by the loader wait, and any residual fault is
now caught and retried rather than fatal.

## Known limitations

1. **The profiler site's walk is still unbounded.** Its loader race is closed and
   its store is guarded, but `PatchIatFunctionByName` has not been moved onto the
   shared `MappedImageView`. It keeps its own mutex and restore bookkeeping, so
   that is a larger change than this fix warranted. Recommended follow-up.
2. **`file_io_hooks.cpp` is untouched**, pending PR #42. Once that lands,
   `PatchIATByFuncName` should adopt the same bounds-checked walk; the
   previously documented crash at `file_io_hooks.cpp:236` is the same class of
   defect.
3. **The crash was never reproduced on demand.** It is a timing race with the
   loader; there is no diagnostic seam that forces the dangerous window. The
   before/after evidence is launch-count based.
4. **Threads are still created from `DllMain`.** `InitializeDx11ColorSpaceDiagnostic`
   is called from `src/dllmain.cpp:44`. That is a separate, pre-existing
   hazard and is not addressed here.
