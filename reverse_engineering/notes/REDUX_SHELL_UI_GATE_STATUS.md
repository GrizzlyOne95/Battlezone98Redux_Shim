# Redux Shell UI — Implementation Gate Status

This file is the acceptance/gating companion to `REDUX_SHELL_UI_RE_MAP.md`.
It does not replace the detailed evidence map. Its purpose is to state exactly
which parts of the recovered shell contract are safe to build on now, which
parts still require live validation, and why OpenShim must not over-promote the
static RE into a public ABI.

## Evidence policy

The checked-in GOG `battlezone98redux.exe-6777ca` decompilation is the binary
ground truth. PDB names/types are semantic aids only and do not establish
retail addresses, layouts, vtable slots, or control flow by themselves.

Confidence terms:

- **CONFIRMED** — direct GOG decompile/bytes plus corroborating call or object evidence.
- **HIGH** — multiple mutually consistent GOG call paths; exact ABI may still need disassembly/live validation.
- **MEDIUM** — strong structural inference with a missing corroborating edge.
- **LOW** — heuristic/PDB-only evidence; not suitable for a runtime binding.

## Executive decision

The static shell RE is now far enough to make the architecture decision:

1. Redux has an integer-driven shell history/request mechanism and a closed
   compiled screen factory.
2. `FUN_007c7930` at `0x007C7930` is a **request/push seam**, not the routine
   that immediately destroys and creates screens.
3. The actual transition path runs through `FUN_007c7820` / `FUN_007c7070`,
   which releases the active screen and invokes the factory
   `FUN_007c7ad0` at `0x007C7AD0`.
4. Native Back is a distinct history-pop operation through `FUN_007c79a0`.
5. Main/title screen ID `0x01` creates `cUI_MainScreen`; the GOG singleton is
   `DAT_0094551c` (`0x0094551C`).
6. The title constructor creates exact child `MainScreen_Overlay`, and the
   central stock menu controls are parented to it.
7. The factory is a closed `switch`. No binary evidence currently shows a
   dynamic `RegisterScreen(id, ctor)` mechanism.
8. Redux itself already uses in-place MainScreen child modes for Credits and
   Intro. That is strong precedent for an OpenShim Career logical surface.

Therefore:

- **Do not patch/register a custom first-class root screen yet.**
- **Do not put an unknown custom integer into the native history container.**
- **Do not expose arbitrary raw Redux screen IDs or `cUI_*` pointers publicly.**
- **Do not add `OpenShimUiHost::MainMenu` as production-safe yet.** The static
  identity and parent are recovered, but the task's live input/lifetime gate
  has not been executed in-game.
- The intended first implementation after the live gate passes is a native
  Career button plus logical Career surfaces under `MainScreen_Overlay`.

## Acceptance matrix

| # | Required answer | Result | Confidence | Runtime implication |
|---:|---|---|---|---|
| 1 | What owns shell navigation? | Shell manager request/history path: request `FUN_007c7930`, transition `FUN_007c7820 -> FUN_007c7070`, factory `FUN_007c7ad0` | **HIGH** | Semantics are recovered; exact public-call ABI for request/back is still gated |
| 2 | Major native screen IDs? | Factory switch recovered for explicit IDs `0x01` through `0x2A`; detailed table is in `REDUX_SHELL_UI_RE_MAP.md` | **CONFIRMED** for listed factory cases | Safe as RE knowledge; do not expose arbitrary integers as API |
| 3 | Main-menu constructor? | Factory ID `0x01`: allocate `0x17C`, call `FUN_0078e670`; normal setup `FUN_0078d000` | **CONFIRMED** | MainScreen identity is reliable for this GOG build |
| 4 | Where are stock buttons attached? | Central controls are constructed with parent `MainScreen_Overlay`; ancillary top-corner controls are attached to MainScreen/root paths | **CONFIRMED** | `MainScreen_Overlay` is the candidate injection parent |
| 5 | What do callbacks do? | SP -> `0x02`; MP -> prechecks then `0x0E`; Options -> `0x03`; Mods -> `0x1C`; Credits/Intro use child movie overlays; Exit is application state/shutdown | **CONFIRMED/HIGH** | Preserve MP prechecks; do not pretend every button is a screen request |
| 6 | Safe parent for Career button? | Binary candidate is exact child `MainScreen_Overlay` | **HIGH static / UNVALIDATED live** | Production `MainMenu` host remains gated on live hit-test/order validation |
| 7 | How does Back work? | `FUN_007c79a0` pops native history when possible and marks transition pending | **CONFIRMED** semantics | Future `navigateBack()` must be distinct from `navigateTo(MainMenu)` |
| 8 | How are screens destroyed/recreated? | `FUN_007c7070` invokes current screen deleting/destruction path before factory creation; `cUI_MainScreen` destructor `FUN_0078eca0` clears `DAT_0094551c` | **CONFIRMED** | Never retain MainScreen/child pointers across transitions; generation fingerprint required |
| 9 | Can Redux safely accept a new first-class shell screen? | Not with the stock factory contract as currently recovered; factory is a closed switch and root-screen lifecycle/unknown-ID history behavior is not fully proven | **HIGH NO for unmodified factory** | No custom ID/factory patch in this phase |
| 10 | Safest native-looking fallback? | MainScreen Career button -> MainScreen-hosted logical Career surfaces -> restore stock controls on Career Back | **HIGH**, pending host live gate | This is the target first implementation |

## Recovered shell state relevant to implementation

The transition decompile provides useful structural evidence for the manager:

- pending-transition byte: manager `+0x27`;
- active-screen pointer: manager `+0x14` (`param_1[5]` in the decompile);
- history/request container is accessed around manager `+0x2C`
  (`param_1 + 0x0B` in the decompiler's `int*` view);
- `FUN_007c7070` reads the back target, releases the active screen, clears the
  pending flag, calls `FUN_007c7ad0(target)`, stores the returned screen, and
  performs activation/update callbacks;
- screen ID `0x17` (`cUI_Loading`) receives special transition treatment.

These offsets are RE notes, not a proposed public ABI.

## MainScreen lifetime and identity

For this GOG build:

- factory ID: `0x01`;
- allocation: `0x17C`;
- constructor: `FUN_0078e670`;
- normal title setup: `FUN_0078d000`;
- destructor: `FUN_0078eca0`;
- scalar deleting destructor: `FUN_0078e8c0`;
- singleton: `DAT_0094551c` / `0x0094551C`;
- candidate host child: exact name `MainScreen_Overlay`.

The constructor writes the singleton. The destructor explicitly zeroes it.
That gives OpenShim a stronger generation anchor than pointer equality alone:
if the singleton becomes null or changes, every logical handle tied to the old
MainScreen generation must be invalidated.

The resolver should still fingerprint the resolved child hierarchy because
allocator address reuse can make a newly constructed screen occupy the same
address as the previous generation.

## Input-dispatch findings

The currently recovered cUI ABI confirms:

- `cUI_View` has an input-active byte at `+0xE9` in this build;
- an active `cUI_View` can report clicks inside its own rectangle as handled
  even without a useful callback;
- therefore a giant full-screen active logical `cUI_View` is not a safe way to
  group OpenShim widgets;
- Native UI's current logical-surface design — direct native child widgets plus
  OpenShim-side grouping/visibility — must remain unchanged.

What static RE has **not** yet promoted to production confidence is the exact
sibling visitation/z-order behavior for an OpenShim-appended child under
`MainScreen_Overlay`, especially when stock siblings overlap it. That is a
runtime acceptance item, not something to guess from Options behavior.

## `OpenShimUiHost::MainMenu` gate

The following are statically satisfied:

- [x] reliable GOG MainScreen singleton identity;
- [x] exact candidate injection parent `MainScreen_Overlay`;
- [x] existing bounded `cUI_View` child-vector traversal strategy is available;
- [x] constructor/destructor singleton behavior is recovered;
- [x] OpenShim already has opaque handles, bounded registries, queued actions,
      UI-thread gating, independent visibility, and fail-closed host resolution;
- [x] active full-area views are known unsafe and are not required.

The following remain live-only acceptance checks:

- [ ] verify `0x0094551C` is the active `cUI_MainScreen` singleton in the exact
      supported runtime build and becomes null/changes across transitions;
- [ ] verify exact child `MainScreen_Overlay` is found with the same bounded
      `+0x12C/+0x130` child-vector layout used by the validated Options host;
- [ ] verify an appended test button receives hover/click without starving or
      double-activating stock title controls;
- [ ] verify hiding/deactivating the probe removes it from hit testing;
- [ ] verify Main -> Options -> Back rebuild/reuse invalidates stale handles;
- [ ] verify repeated transitions do not leave Redux-owned injected children
      dangling or cause double destruction.

**Gate result:** do not add the public `MainMenu` enum value until these checks
pass. A diagnostic-only, fail-closed probe is acceptable if needed to execute
the checks.

## First-class custom-screen gate

Current result: **HOLD / do not implement**.

The factory at `0x007C7AD0` is a compiled switch. Understanding its cases does
not create an extension seam. A custom root screen would require interception
of the transition/factory path plus a compatible root-screen object whose
allocation, vtable, destruction, activation, input/focus, rendering/update,
and history semantics all satisfy assumptions currently made by stock code.

In particular, putting an unknown ID into native history is unsafe because a
later native Back/forward transition can send that ID to the unmodified stock
factory and receive no valid stock screen.

A future custom-screen implementation should be a separate versioned shell
capability (for example `OpenShimShellApiV1`), not a silent expansion of Native
UI v1.

## Stock-shell navigation API gate

The semantic distinction is recovered:

```text
request stock screen: FUN_007c7930
back/history pop:     FUN_007c79a0
```

However, Ghidra's prototypes around these tiny wrappers are misleading because
implicit object/stack arguments have been reconstructed poorly. Before an SDK
wrapper calls them directly, validate the exact machine-code calling
convention, shell-manager object source, argument placement, and supported
build signature.

Also preserve stock callback-specific preconditions. The Multiplayer button,
for example, performs network/lobby checks before requesting screen `0x0E`.
A high-level `OpenShimShellScreen::Multiplayer` operation should either route
through equivalent native policy or explicitly document that it is a lower
level request and is not a substitute for the stock button callback.

## Minimal in-game validation sequence

When the diagnostic MainScreen probe is available, the shortest useful test is:

1. Launch to the title menu and record MainScreen singleton, resolved
   `MainScreen_Overlay`, child count, and a fingerprint of stock child names.
2. Add one small probe button in a non-overlapping area of
   `MainScreen_Overlay`. Confirm hover/click produces exactly one queued
   `NativeUiAction`.
3. Exercise every stock MainScreen button before and after probe creation.
   Confirm no stock hover/click path is starved.
4. Hide/deactivate the probe and confirm the same region no longer receives
   probe input.
5. Navigate Main -> Options -> Back. Confirm the old generation is invalidated
   and the returning MainScreen is resolved/fingerprinted again even if the
   allocator reuses an address.
6. Repeat the transition at least ten times, including opening/closing Credits
   (the native `movie1` child mode), to catch child-count/fingerprint mistakes.
7. Only after those checks pass, add `OpenShimUiHost::MainMenu` and expose it to
   normal Native UI consumers.

## Implementation target after the MainMenu gate passes

```text
cUI_MainScreen
    |
    +-- MainScreen_Overlay
            |
            +-- stock controls
            +-- OpenShim Career button
            +-- Career logical widgets (hidden by default)
```

Career click should queue through the existing Native UI action mechanism,
hide/deactivate only the stock controls that can overlap or consume input, and
show direct child widgets for the Career logical surface. Career Back should
restore the stock title controls without destroying `cUI_MainScreen`.

This keeps Redux as owner of the real shell screen and its native children,
while OpenShim owns only opaque logical handles and visibility/navigation
state.

## Bottom line

The main shell is no longer an unknown subsystem. The dispatcher/history,
factory, screen IDs, MainScreen identity/lifetime, candidate injection parent,
major callbacks, and Back semantics are recovered well enough to choose the
architecture.

What is intentionally *not* being claimed is equally important: static RE has
not proved that an injected MainScreen sibling is input-safe in the live build,
and the closed factory does not provide a clean custom-screen registration
contract.

Accordingly, this branch should stop before public runtime expansion, execute
the narrow MainScreen live probe, then implement the MainMenu-hosted Career
surface if that probe passes. True first-class custom shell screens remain a
separate later RE/hooking project.