# Workshop asset-set sync

The in-game updater and Campaign Reimagined's Setup install only the DLL and
ini suite from the CR Workshop item (Steam app 301650, item 3686673790). The
Enhanced renderer resources and the custom UI images live in the same item at
the same relative paths as in the game folder, but nothing copied them, so the
game-folder copies went stale after an auto-update.

OpenShim now syncs those two **asset sets** itself. At startup a worker thread
(`src/patches/openshim_asset_sync.cpp`, log component `assetsync`) compares the
Workshop item with the game folder and installs what differs. Both update routes
restart the game afterwards, so both are covered with no change to the
replacement helper or its `--suite-v3` arguments.

## Manifest contract

`OpenShimManifest.lua` (still `formatVersion = 3`) may carry two extra
top-level sections after `payloads`. Every entry is on one line; `\\` is one
backslash.

```lua
    assetSets = {
        renderer = { source = "openshim\\renderer\\enhanced", destination = "openshim\\renderer\\enhanced", sha256 = "<64 hex>", files = 21 },
        customWidgets = { source = "BZ_ASSETS_CORE\\common\\ui\\CustomWidgets", destination = "BZ_ASSETS_CORE\\common\\ui\\CustomWidgets", sha256 = "<64 hex>", files = 18 },
    },
    assetFiles = {
        { set = "renderer", path = "resources.version", sha256 = "<64 hex>", size = 2 },
        ...
    },
```

- `source` is relative to the Workshop item directory, `destination` to the game
  directory, `path` to the set. All are backslash-separated, use only
  `A-Za-z0-9_.-` and `\`, have no `..`, no empty component, no leading
  separator and no drive or colon. A bad path rejects the whole asset section.
- Only `renderer` and `customWidgets` are recognised. Unknown set names (and
  their file entries) and unknown sections are ignored; the sync logs them.
- `files` must equal the number of `assetFiles` entries for the set.
- Sections absent means no sync and no error. Older packages work unchanged, and
  older OpenShim builds ignore the sections (the manifest parser only looks for
  the fields it knows; `openshim_update_manifest_tests` pins this).

### Set hash

Lowercase hex SHA-256 of the ASCII text made, for each file of the set sorted by
lowercased path (ordinal byte order), of the line

```
<lowercased path>|<lowercase sha256>|<decimal size>\n
```

## Markers

Each destination holds a marker whose content is the set hash plus `\n`:

| Set | Marker |
| --- | --- |
| `renderer` | `openshim\renderer\enhanced\openshim_set.sha256` |
| `customWidgets` | `BZ_ASSETS_CORE\common\ui\CustomWidgets\openshim_widgets.sha256` |

If the marker equals the manifest's set hash the set is skipped without hashing
any game file. `install_windows.ps1` deletes the matching marker whenever it
deploys those files, and `uninstall_windows.ps1` removes both markers (and any
`enhanced.pending` / `enhanced.old` leftovers), so a marker never vouches for
files it did not describe.

## Gating

The sync runs only when all of these hold:

1. A Workshop item directory with `OpenShimManifest.lua` is found (same lookup
   as the updater).
2. The manifest parses with the normal update-manifest parser.
3. `manifest.version` equals the file version of the **running** `openshim.dll`.
   This avoids a downgrade when the Workshop item lags a newer installer build,
   and avoids installing assets for a DLL that has not been swapped in yet.
4. The marker differs from the set hash.

Then, per set, every source file must exist with the declared size and SHA-256
and the recomputed set hash must equal the declared one; otherwise the set is
refused and the game folder is left untouched. `renderer` must also pass
`RenderProfiles::ValidateDeployedResourceSetAt` on the Workshop copy (resource
version compatible with this DLL).

Log lines, one per set: `already current`, `installed N files`,
`refused (reason)`, `deferred, will retry next start`. No Workshop item or no
asset sections is a single Info line.

## Atomicity

`renderer` is replaced at directory level. Files are copied into a fresh sibling
`enhanced.pending` (a stale one is deleted first), re-verified, given the marker
and validated with `ValidateDeployedResourceSetAt`. Then `enhanced` is renamed
to `enhanced.old` (a stale one removed first), `enhanced.pending` is renamed to
`enhanced`, and `enhanced.old` is deleted best-effort. Files in the old folder
that are not in the set disappear with it. If the live directory cannot be
renamed (locked) the pending copy is removed, the set is `deferred` and the next
start retries. If the live directory does not exist the pending directory is
just renamed into place.

`customWidgets` shares its folder with the game's and the player's own widgets,
so the directory is never swapped or deleted. Each file is copied to
`<name>.tmp` in the same folder, verified, and renamed over the target. A file
that already matches is left alone. The marker is written last, only if every
file succeeded; any failure is `deferred` and retried next start.

## Known race

The sync runs concurrently with game startup. The directory-level swap keeps the
renderer set internally consistent (the game sees the old folder or the new one,
never a mix), but a session that has already read resources keeps using the
previous copy. Worst case, one session runs on the previous assets and the next
start is correct. Individual widget images may likewise be picked up a start
late.

## Not covered

GOG and addon installs have no Workshop item, so nothing is synced there, same
as the updater. They keep using the installer (`install_windows.ps1`).

## Retiring Campaign Reimagined's runtime copy (plan, not done)

The Workshop item stays the delivery channel: the in-game updater and CR's
Setup only ever read files from it, so CR cannot stop *shipping* these bytes.
What it can stop doing is shipping them on its content root, where the game
and OpenShim's renderer probe use them directly. Because the sync reads each
set's `source` from the manifest, moving them needs no OpenShim change.

1. Ship the OpenShim build that contains this sync through CR (bundled suite
   plus the `assetSets` sections). From then on every player who restarts
   after Setup or an auto-update gets game-folder copies with markers.
2. Fallback period: keep `openshim\renderer\enhanced` and
   `BZ_ASSETS_CORE\common\ui\CustomWidgets` on the content root for at least
   one more CR release and until CR's minimum bundled OpenShim is a sync-capable
   build. CR's Inspect report (`ASSET_*` lines) shows whether a player's game
   folder is current, which is the signal to look at in bug reports.
3. Move the files to a non-content directory in the item (for example
   `OpenShimPayload\renderer\enhanced` and `OpenShimPayload\ui\CustomWidgets`)
   and point the manifest `source` fields there. Only the destination keeps
   the game-relative path.
4. Remaining exposure after the move: a player whose running OpenShim
   differs from the Workshop manifest version (sync is gated off) and who has
   no game-folder copy loses Enhanced resources and the custom tiles until
   versions match again. Setup stages the bundled suite whenever it is older,
   so this is limited to players running a *newer* OpenShim than CR bundles,
   who got it from the installer, which deploys both sets itself.
