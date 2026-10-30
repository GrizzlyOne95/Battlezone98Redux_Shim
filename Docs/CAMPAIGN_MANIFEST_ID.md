# Multiple campaigns in one addon

An optional `[WORKSHOP] campaignID` gives a campaign manifest its own mission
list and progress identity while its content remains in the same addon folder.

```ini
[DESCRIPTION]
missionName = "BZ64: Rise of the Black Dogs (Pilot Mode)"

[WORKSHOP]
mapType = "campaign"
campaignID = "bz64pilot"

[MISSION1]
missionName = "Grab the Scientists"
missionBZN = "n64bd01p.bzn"
```

Use a unique ID across installed campaigns. IDs contain 1–63 ASCII letters,
digits, underscores or hyphens, beginning with a letter or digit. They are
case-sensitive registry identities, not paths. Keep an ID stable after shipping:
changing it selects a different progress record. Do not reuse another campaign's
folder key or explicit ID.

Without this field, or with an invalid field, the original folder identity is
retained. Existing campaigns and saves therefore keep their existing behavior.
For an existing combined addon, its primary campaign can keep the implicit
folder identity while alternate modes opt into unique IDs.

The stock custom campaign parser keys mission lists by directory. Two manifests
in a directory can add missions to one shared list or update matching BZN
entries in that list. Unique BZN filenames avoid overwriting entries but do
not make the two campaign menu choices independent.

This hook replaces one guarded engine string assignment in the campaign-only
parser branch. It reads the current manifest's optional ID, then uses the
original engine copy-assignment routine. Resource paths, map filenames and
allocation ownership remain with the engine. A signature or caller mismatch
leaves the stock parser untouched. No new `openshim.ini` setting is needed:
content authors opt in per manifest.

Qualification: Release Win32 build and 155 CTests pass. Windows/GOG Redux
2.2.301 native registry inspection confirms two ten-entry BZ64 lists from one
addon. Native menu launches select `bz64port/n64bd01p.bzn` for Pilot and
`bz64port/n64bd01.bzn` for Commander, including a same-process mode change.
Native Pilot startup confirms Follow orders targeting the player on both tanks
and the bomber, with all three moving. The hook is currently restricted to GOG;
Windows/Steam, Proton and Wine
remain unverified and require separate qualification before release. Campaigns
using this field need a compatible OpenShim build; stock Redux ignores it.
