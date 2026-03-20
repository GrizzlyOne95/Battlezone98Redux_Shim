# UploaderApp Workshop Pipeline Notes (2026-03-20)

## Scope

Focused reverse-engineering pass over the legacy Steam uploader tool:

- `C:\steamcmd\steamapps\content\app_450970\depot_450971\UploaderApp.exe`
- `C:\steamcmd\steamapps\content\app_450970\depot_450971\odfHeaderList.txt`
- `C:\Users\istuart\Documents\Battlezone 98 Redux\Edit\sample.ini`

Tooling used:

- `bzr-rizin.cmd`
- local string/xref inspection

Main question of interest:

- Can Workshop tags be set without `UploaderApp.exe`?

Short answer:

- Yes. The legacy uploader is not using a magic private path for tags. It calls the normal Steam UGC update path and explicitly sets tags before final submit.
- If you do not want to use `UploaderApp.exe`, the clean options are:
  - call the Steamworks UGC equivalent of `SetItemTags` during an item update flow, or
  - do a normal SteamCMD upload and then patch tags with `IPublishedFileService/Update/v1/`

I did **not** find evidence here that the plain SteamCMD `workshop_build_item` VDF used in this workspace is already setting tags directly.

## Binary Anchors

Useful fixed strings and their xrefs:

- `0x00411a00` `mapType`
- `0x00411a14` `customtags`
- `0x00411ce4` `gameType`
- `0x00412034` `missionName`
- `0x00411d48` multiplayer `gameType` validation error
- `0x00411e68` invalid ODF header error
- `0x00411f4c` uploaded-items query message
- `0x00411fe0` name-collision query message
- `0x00412068` duplicate base-name collision message
- `0x004122b4` problem setting Workshop tags
- `0x004122d4` problem removing `missionName`
- `0x004122f8` problem adding `missionName` metadata
- `0x0041231c` upload submit message

Important functions:

- `0x00401c10` main content and INI validation pass
- `0x00403923` resolves and loads `odfHeaderList.txt`
- `0x00403cc9` begins query for current user's uploaded items
- `0x00403d13` creates the Steam query handle and callback
- `0x00403fda` checks uploaded items for `missionName` collisions
- `0x00404413` create/update handoff
- `0x0040468a` final item setup, tags, metadata, and submit

## Expected INI Schema

The bundled sample file at `C:\Users\istuart\Documents\Battlezone 98 Redux\Edit\sample.ini` matches the strings and branches recovered from `UploaderApp.exe`.

### Required top-level sections

`[DESCRIPTION]`

- `missionName = "..."`  
  This is the canonical workshop-side mission/base name.

`[WORKSHOP]`

- `mapType = "instant_action"`
- `mapType = "multiplayer"`
- `mapType = "mod"`
- `mapType = "campaign"`
- `customtags = "tag1, tag2, tag3"` appears optional

`[MULTIPLAYER]`

- used when `mapType = "multiplayer"`
- `minPlayers`
- `maxPlayers`
- `gameType`

### Multiplayer `gameType` validation

Recovered error string:

- `Your ini file is multiplayer but you do not have a proper gameType. Valid options are : D, S, A, M, and K`

So the accepted multiplayer codes are:

- `D`
- `S`
- `A`
- `M`
- `K`

### Campaign mission sections

The sample file and code both support numbered sections:

- `[MISSION1]`
- `[MISSION2]`
- etc.

Observed campaign mission keys from sample/schema:

- `missionName`
- `missionBZN`
- `missionBG`
- `planet`
- `planetDisplay`
- `planetDesc`
- `descColor`
- `voice`
- `gift`
- `loadingBG`

Observed campaign notes from the sample:

- `planetDisplay` and `planetDesc` are required when `planet = "custom"`
- `missionBG`, `descColor`, `voice`, `gift`, and `loadingBG` are optional

### Other schema observations

The validation pass also carries strings for:

- missing or invalid `mapType`
- multiple mod types being mixed
- multiple campaign types being mixed
- mixed mod/map/campaign packaging being invalid

So the uploader is not just reading these values, it is using them to classify the content folder and reject conflicting pack layouts.

## ODF Validation Logic

This part is much clearer than the old app's UI suggests.

### Header allowlist source

`0x00403923` constructs the path to:

- `\odfHeaderList.txt`

relative to the directory containing `UploaderApp.exe`, then loads it into memory before the content validation pass continues.

The local file contains the allowlist actually used by the app, including examples like:

- `GameObjectClass`
- `CraftClass`
- `BuildingClass`
- `WeaponClass`
- `ScavengerClass`
- `ProducerClass`
- `RecyclerClass`
- `WalkerClass`

and many more.

### Scan behavior

In `0x00401c10` the tool:

1. Recursively walks the selected content folder with `FindFirstFileA` / `FindNextFileA`
2. Skips `.` and `..`
3. Skips directories
4. Filters files by extension using a case-insensitive `.odf` check
5. Opens each `.odf`
6. Extracts the ODF header/class token
7. Compares that token against the loaded `odfHeaderList.txt` entries

If no allowlist match is found, it jumps into the error path at `0x0040377d` and emits:

- `You have an odf file with an invalid header`
- `Found in `
- the offending file path

### Practical meaning

“Invalid header” here means:

- the parsed ODF class/header token is not in `odfHeaderList.txt`

It is not a loose warning. This is a hard allowlist check driven by that external text file.

## Workshop Item Query Flow

### Step 1: query the user's uploaded items

`0x00403cc9` shows:

- `Querying steam for the list of items you have uploaded`

and then calls `0x00403d13`.

`0x00403d13`:

- initializes the Steam API context
- resolves the active app id
- creates a UGC query handle via a vtable call at offset `+0x8`
- stores query state on the uploader object around `+0xe8` / `+0xec`
- registers an async callback helper at `+0x178`

The shape strongly matches a “query the workshop items uploaded by the current user for this app” flow.

### Step 2: collision-check on `missionName`

`0x00403fda` shows:

- `Looking for Workshop items with name collisions...`

It then:

- iterates the query results stored at object field `+0x108`
- treats each result entry as a `0x18`-byte record
- skips the currently selected item by comparing against the object's `+0x120` area
- creates a metadata query using the key `missionName`
- registers another async callback helper at `+0x198`

If a collision is found, the app reports:

- `There is already a Workshop item with this base name.`
- `You will need to rename your mission to something else (.bzn, .ini, etc)`

### Practical meaning

The collision-check is not title-only. The app is using `missionName` as explicit item metadata and checking uploaded items against that value before it proceeds.

## Workshop Tag and Metadata Handling

This is the key section for replacing the old uploader.

### Final update flow

Inside `0x0040468a`, the uploader performs the item-update setup in this order:

1. set item name
2. set preview image
3. set Workshop tags
4. remove existing `missionName` key
5. add new `missionName` metadata
6. submit the item update

### Observed update calls

These method names are inferred from call placement and adjacent error strings, but the behavior is very strong:

- vtable `+0x84`  
  item name update  
  failure string: `Problem setting item name`

- vtable `+0xa0`  
  preview image update  
  failure string: `Problem setting item preview`

- vtable `+0x98`  
  Workshop tag update  
  failure string: `Problem setting workshop tags`

- vtable `+0xa4`  
  remove metadata key  
  called with key `missionName`  
  failure string: `Problem removing key missionName`

- vtable `+0xa8`  
  add metadata key/value  
  called with key `missionName` and the parsed value  
  failure string: `Problem adding missionName metadata`

- vtable `+0xc0`  
  final submit/update call  
  immediately followed by callback registration and the message  
  `Uploading item, please wait...`

## Can Tags Be Set Without `UploaderApp.exe`?

Yes.

### What the legacy binary proves

The old uploader is not relying on hidden uploader-only behavior. It explicitly issues a Steam UGC tag-setting call before submit.

That means the relevant capability exists outside the GUI itself.

### Most practical replacements

#### Option 1: Steamworks UGC path

Use the normal item-update flow:

1. start/update item
2. set title/preview/content as needed
3. set tags
4. submit item update

The equivalent high-level method is the Steamworks `SetItemTags` style call. The local Steam API export inventory in this workspace already shows:

- `SteamAPI_ISteamUGC_SetItemTags`

in:

- `reverse_engineering/module_dumps/2026-03-18/steam_api.dll.exports.txt`

#### Option 2: Steam Web API after SteamCMD upload

There is already local proof-of-concept code for this in the separate repo:

- `C:\Users\istuart\Documents\GIT\Battlezone98Redux_WorkshopUploader\uploader.py`

That uploader does a normal SteamCMD-style upload, then calls:

- `https://api.steampowered.com/IPublishedFileService/Update/v1/`

with:

- `key`
- `publishedfileid`
- `appid`
- `tags[0]`
- `tags[1]`
- etc.

So if the goal is “set tags without the legacy uploader app,” the easiest currently demonstrated path in this workspace is:

1. upload with SteamCMD
2. POST tag updates through `IPublishedFileService/Update/v1/`

### What I did not find

I did **not** find local evidence that your current SteamCMD upload VDF path is setting tags directly.

The current generated VDF in:

- `C:\steamcmd\campaignReimagined_update.vdf`

contains:

- `appid`
- `publishedfileid`
- `contentfolder`
- `previewfile`
- `visibility`
- `title`
- `description`
- `changenote`

but no tags field.

So the safest current conclusion is:

- tags are definitely settable without `UploaderApp.exe`
- the old uploader proves the capability exists in the normal Steam UGC update path
- your current non-legacy path for doing this is the post-upload Web API update, not plain VDF generation alone

## Practical Recommendation

If the immediate goal is reliability rather than purity:

1. keep using SteamCMD for upload payloads
2. update tags after upload with `IPublishedFileService/Update/v1/`
3. if needed later, replace that with a direct Steamworks UGC client call

That avoids dependency on the legacy GUI while still matching the behavior that `UploaderApp.exe` was trying to provide.
