# Campaign Reimagined suite release candidate, 2026-09-29

OpenShim 1.0.0.34 pairs with bzfile 1.1.0 and Campaign Reimagined's format-3
manifest. The Workshop folder carries `winmm.dll`, `bzloader.dll` and
`openshim.dll` beside bzfile; the installed chain is game-root `winmm.dll`,
`bzloader.dll`, and `plugins/openshim.dll`.

The native updater replaces all three DLLs, `net.ini` and
`scripts/patches.json` through `--suite-v3`. It checks each payload's hash,
size and x86 PE identity, all DLL versions, and the attested helper before
staging. The helper verifies staged bytes before and after waiting for game
exit, backs up all existing targets, and rolls back every promoted target on
failure. Format 2 is deliberately rejected by this updater; it cannot
describe the complete split load chain. Campaign's updated Lua installer and
bzfile entry point provide the migration from older installed shims.

Windows Release build and 64 CTest checks pass. Windows deployment verifier
fixtures, INI policy and network baseline pass. bzfile's real Lua host installs
the exact candidate chain into both a fresh fixture and an existing fixture.
Its helper also passes legacy three-file transactions and five-file rollback
with the final destination locked. Campaign Lua tests reject missing
components, old staging APIs and a changed helper.

The primary checkout's uncommitted LensFlare shutdown investigation is
preserved outside this candidate. It has not been qualified for this release.
The verifier fix is recovered into this branch with its fixture tests.

Final package identities, runtime results and publication handoff are recorded
in [Campaign Reimagined's preparation follow-up](https://github.com/GrizzlyOne95/Battlezone98Redux_CampaignReimagined/pull/112),
with the complete suite source merged in OpenShim #382, bzfile #25 and
[CR #111](https://github.com/GrizzlyOne95/Battlezone98Redux_CampaignReimagined/pull/111).
The local manager now builds/checks the native dependencies, deploys/tests GOG
and creates all five verified archives; its 59-step run passed with DX9, DX11
and Setup. The final rc5 handoff carries the same runtime payload with corrected
manual installation instructions. Steam's local candidate is enumerated under
`packaged_mods`, but direct CLI mission starts did not activate its native DLLs.
Menu-start attempts with `/nointro` remain unqualified because desktop control
was disconnected. All Steam backups and saves were restored.
Public tags, releases,
Workshop upload and Roadmap synchronization are separate authorized actions.
