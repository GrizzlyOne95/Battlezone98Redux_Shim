# Native UI and network integration — 2026-10-09

`agent/gog-ui-network-catchup` is the single OpenShim integration branch for
the native UI redesign, reliable-send backlog repair, renderer recovery and
private co-op/network qualification tooling, reviewed in
[draft OpenShim PR #419](https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/pull/419).
Source branches are retained as
history; this branch contains all five tips below. Existing PRs #415, #417 and
#418 remain open and are included by ancestry. No PR was merged or release
published as part of this consolidation.

## Source map

| Work | Included source tip | Existing review |
|---|---|---|
| Native shell, category Settings hub and painted Keybind editor | `ui/native-screens` / `6ce2b8082afad252726614b476a1a7ef0f74bd9c` | Previously had no PR |
| Battle load, objectives, AI combat, beacons, powerups, scrap and cleanup tooling | `agent/network-battle-load` / `db3d2aa20221b830bd8daa8f838cb787c0ad67a7` | Previously had no PR |
| Private impairment/capture scoring, retry matrix and admission diagnostics | `agent/net-impairment-matrix` / `3d64c31fbd5ae20e83af4a201e68505a2abd9333` | [#417](https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/pull/417) |
| Reliable-send backlog repair and DX11 device-loss recovery | `agent/d3d11-device-loss-recovery` / `00ff38f144f2751074baef4b809ed7b9eb019c42` | [#415](https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/pull/415) |
| Two-to-four-client campaign mission qualification | `agent/four-client-coop` / `34a3b799e3bd1a03cc909ff3e9ac0e8fb1d3eadd` | [#418](https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/pull/418) |

Current main `5146f6b8` is included. The UI lineage also supplies its named
address-port/build-overlay dependencies. The CMake merge retains both the
reliable-send policy tests and Win32 last-error tests. Reordering and duplication
remain disabled in the real BZRNet transport.

Campaign source is consolidated in `agent/network-coop-integration` in the
canonical Campaign Reimagined repository,
[draft campaign PR #173](https://github.com/GrizzlyOne95/Battlezone98Redux_CampaignReimagined/pull/173):
current main `b3450f8`, admission
checkpoint `938ed92` and four-player mission work `2452730` (existing
[campaign PR #171](https://github.com/GrizzlyOne95/Battlezone98Redux_CampaignReimagined/pull/171)).
The guard finishes initialization after all comms/respawn/rally/lives setup,
before accepting admission messages. Campaign packaging includes all 17 native
UI images, generated suite metadata and current sibling binary caches.

Server source is consolidated in
[draft dedicated server PR #9](https://github.com/GrizzlyOne95/Battlezone98Redux_DedicatedServer/pull/9),
`agent/network-startup-observability`, tip `0e7400eb6b9fbb5c20e43f2d0968a7f192ec6d89`.
It includes existing PR #8, bounded relay port allocation, impairment, startup
diagnostics, protocol capture and native-health tooling. Supported authorization
fields `steamAppTicket` and `platformTicket` are now redacted in both capture
payloads and previews. Server source changes are separate from historical
capture provenance; old private evidence is retained unchanged.

## Correct UI provenance and GOG deployment

The intended redesign was on `ui/native-screens`, not main. Its original
commits are `a9b567aa` (shell screens), `3b3342fe` (category hub/pages) and
`6ce2b808` (painted keybinds and five-slot Options). Enabling SettingsUi and
CustomBindsUi on the previous network DLL exposed the earlier flat pages;
the flags alone could not load the missing implementation and assets.

The integrated Release x86 suite was deployed to the ordinary GOG install
through `scripts/Deploy-OpenShim.ps1`, including matching patch JSON, all 17
native UI images and renderer resources. An independent 42-file source/hash
audit passes after campaign deployment. Version remains 1.0.0.47, so use hashes
rather than the version resource to distinguish this build from the published
release and earlier network tests.

| Artifact | SHA256 |
|---|---|
| `plugins/openshim.dll` | `A1A3966EF25205634BF521485D700F75533076A5CEB8443FC4ADFA52763D6D4F` |
| `winmm.dll` | `CCD4E053567A284BAE033CA5B086D41098062CBFA87962E396758CF619E95267` |
| `bzloader.dll` | `92FEF23ED0BC47528D79A7C114DD46A72C63EFC1128F79466254D2BC554D174C` |
| `scripts/patches.json` | `5581D31F352B8791F8D62E67FF782A6CF01C8349392E1FFF496FEE20A9A40DF5` |

The local INI preserves user preferences, enables General/SettingsUi and
CustomBindsUi, and keeps Network/ReliableSendBacklogFix ON with stock retry
defaults 1000/2500. Both redesigned-page defaults were already ON in source;
the missing branch implementation and incomplete asset packaging caused the
old appearance.

Actual GOG menu smoke at 19:47–19:48 CDT verifies the five-slot Options layout,
nine-category Settings hub, Video category, Back navigation to the hub and
Options, and painted keybind editor (93 actions/five pages). The game exited
gracefully and temporary display/input configuration was restored. Runtime
verification passes with no stale patch configuration. This evidence does not
qualify FPS, multiplayer gameplay, Steam, Proton or Wine.

The campaign manager deploys the same suite metadata/cache and merged campaign
to the development mod. Its reviewed shipping lock adds 77 runtime entries:
13 UI images and 64 current-main authored mission/content files. Repository
test fixtures are excluded. No committed shipping entry is removed/remapped.
Final GOG verification: 3,789 files, zero missing/content differences/unexpected
managed files. Campaign admission source and suite payload hashes match source
and the root load chain, preventing the old same-version payload from replacing
the new local build.

## Validation and remaining qualification

- Combined native Release Win32 build passes; 82/82 Release CTest pass.
- INI policy/writer/migration checks pass (180 settings, 23 writer and 67
  migration cases); network baseline validation passes.
- P2P Python regression suite passes 41 tests.
- Combined campaign Lua 5.1 admission, registry, comms, PDA/HUD, rally,
  misn02b/03/04, misn05 presentation, PhysicsImpact and subtitle checks pass;
  Python misn02b/03/04/05 co-op contracts pass. Repository validation passes.
- Server smoke, stock protocol, parity, observability/redaction, impairment,
  fault injection, bounded/pair ports, capture, native-health and GUI checks pass.

The last four-client combat experiment predates this combined UI build. It
used plugin SHA256 `7C2D20C047CAAB54D1D01C608A405CCD374A28972DDEC65F057514A3FC8E9C22`
and an admission-only override on the immutable release campaign. Its stock
arm completed 80 fighting AI/60 steady simulation seconds, 16 beacons,
64 powerups, 23 natural deaths and 94 new observed scrap handles. Gameplay and
cleanup passed; native rejection-frequency health failed. The shorter-timer
arm stopped at lobby navigation before combat; rate/queue arms did not run.
No completed retry-timer comparison is qualified. Defaults remain stock.

Follow-up work must first requalify the combined client/campaign, including
native health during equal-population idle/moving/combat controls and longer
combat/scrap collection. Then complete matched retry/loss/bandwidth/queue
comparisons and cumulative ACK/byte/duplicate checks. Source admission guard
qualification covers fresh-module startup; reused-module mission epochs remain
open. WAN, Steam, Proton/Wine, display-transition stability and longer sessions
need independent evidence before release.

Detailed results remain in
[`p2p_retry_timing_validation_20261009.md`](../reverse_engineering/p2p_retry_timing_validation_20261009.md),
[`NET_IMPAIRMENT_TEST_PLAN.md`](../reverse_engineering/NET_IMPAIRMENT_TEST_PLAN.md)
and [`NETWORK_BATTLE_LOAD_HANDOFF_20261009.md`](../reverse_engineering/NETWORK_BATTLE_LOAD_HANDOFF_20261009.md).
Raw captures, identities, payloads, dumps, backups and screenshots remain
private under `C:\BZRCoop\runs`. The local checkpoint records branch heads,
review URLs, deployed hashes, recovery audits and the next qualification gates.
