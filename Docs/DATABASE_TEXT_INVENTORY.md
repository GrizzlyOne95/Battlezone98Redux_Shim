# BZ98R Database text inventory (stock base game vs Red Odyssey)

Read-only research. No lore written, no repo edited. Addon\ packs excluded.

Sources used
- SL = `C:\Users\iestu\Documents\BZR_moved_out_20261112\docs_reference\stock_lore` (AGENT_GUIDE.md, records.jsonl for scope tags, archive_inventory.json)
- SO = `C:\Users\iestu\Documents\BZR_moved_out_20261112\StockODFFiles` (6081 files: 1889 wav, 1615 geo, 796 odf, 502 inf, 354 des, 184 otf, 15 ios, no images)
- GB = `C:\Users\iestu\Documents\GIT\Campaign-Reimagined\Tools\TranscriptSources\GoombaBZ\campaigns.csv` (778 rows) and `units.csv` (766 rows). Line numbers below are physical file lines. SL\transcript_sources\GoombaBZ holds a verbatim copy.

## Key findings first
1. The stock text that names units is the .inf header (e.g. `GRIZZLY - MEDIUM TANK:`), NOT the ODF `unitName`. ODF unitName is a generic class word ("Tank", "Scout", "Turret", "Walker"). The only other name source in SO is netveh.odf, a tab-separated list (odf, des, x, display name; e.g. `avtump  avtump.des  x  Badger`, `bvtump ... BDog Badger`). It has no [section] header and covers about 40 multiplayer vehicles.
2. A full designator + model name exists for exactly one unit family, the Badger turret: `M173 Badger` at SO\tran02.des:1 and SO\misn03.des:7 (`M173 Badger Turrets`). The VO transcripts CONFLICT with that: `T-4 Badger Turret` (GB campaigns.csv:57, misn0117.wav, Combat Driving) and `T-7 Badger turret` (GB campaigns.csv:64 tran0201.wav, and :76 tran0213.wav). Regex sweeps of all .des/.inf/.otf and both CSVs for designator patterns (`[A-Z]{1,4}-?\d{2,4}`) found nothing else (only an unrelated RX-7 in mikea.des:13, a credits file). A designator written some other way would be missed by the regex: UNVERIFIED for that case.
3. Scope quirk: in SL records.jsonl all `bd*` (Black Dogs) and `ch*` (Chinese) mission text and all `cv*`/`cs*`/`cb*` ODFs are scope `red_odyssey`, but the Black Dog unit ODFs `bv*`, `bs*` and buildings `bb*` are tagged `base` (they are on the build lists b_misns4-6 / b_misn14 used by base-game CCA/NSDF missions). SL's own guide says the classification is by archive and filename family, not a byte comparison with a retail disc. Treat `bv*` scope as UNVERIFIED.
4. No per-mission images exist in stock sources. SO has zero png/bmp/jpg, and archive_inventory.json (6224 entries across bzone.zfs, bzone_en.zfs, tro_cam.zfs) lists no image extension. Only image hits in the GOG install: `BZ_ASSETS\...\bd_load.bmp` and `bd_load2.bmp` (Black Dogs loading screens; whether stock or per-mission UNVERIFIED). Loose `misn03.BMP` in the install root (216x178) and `mods\3686673790\misn*cr.bmp` are Campaign Reimagined content, excluded; origin of the root misn03.BMP UNVERIFIED.

## A. Vehicle/unit ODFs (68 player-buildable via b_* lists)

Legend: netveh = display name in SO\netveh.odf. inf header = line 1 of `<odf>.inf` (the unit name is the text before " - "). Builder = which b_* build list offers the unit (b_am*=NSDF, b_so*=CCA, b_bd*=Black Dogs, b_ch*=Chinese). Narrative hits = SO .des/.otf lines (excluding unit stat sheets) that name the unit; name-based, so same-name hits repeat across av/bv/sv rows. csv = count of GB campaigns.csv rows containing the name (callsign collisions in section C). "Full model name" (designator + name) exists only for the Badger family, rows avturr/bvturr: misn03.des:7, tran02.des:1 (`M173 Badger`), campaigns.csv:57/64/76 (`T-4`/`T-7 Badger`). Every other row has NO designator. VO folder is blank for APC/Constructor/Factory/Armory rows only because folder stems differ (see D). Mission-specific variants (avrec3-8, svapcc-s, cvtnka-d, avcns7-9, ...) are the other 178 of 246 scanned ODFs; they mostly share their parent's .inf by hash. All ODFs have a `.inf` except where section C lists them. Stat `.des` = `HULL:/AMMO:/weapon names` only (e.g. avtank.des).

| ODF | scope | class | ODF unitName | netveh.odf name | .inf header (line 1) | stat .des | builder lists | VO folder (GoombaBZ label) | narrative hits (des/otf file:line) ; campaigns.csv rows |
|---|---|---|---|---|---|---|---|---|---|
| avapc | base | apc | APC |  | RAT PACK - APC: | - | b_amcmbt |  | ; csv:0 |
| avartl | base | howitzer | Howitzer |  | LONGBOW - ARTILLERY: | - | b_amcmbt | Longbow (Howitzer) | ; csv:0 |
| avcnst | base | constructionrig | Constructor |  | CONSTRUCTION UNIT: | - | b_amprod |  | ; csv:0 |
| avfigh | base | wingman | Scout |  | RAZOR - LIGHT ATTACK VEHICLE: | - | b_amcmbt | Razor (Scout) | bdmisn04.des:4; csv:5 |
| avhaul | base | tug | Tug |  | HAULER - CARGO TUG: | - | b_amprod | Hauler (Tug) | ; csv:0 |
| avhraz | base | wingman | Bomber |  | THUNDERBOLT - HEAVY BOMBER: | Y | b_amcmbt | Thunderbolt (Bomber) | ; csv:0 |
| avltnk | base | wingman | Light Tank | Bobcat | BOBCAT - LIGHT TANK: | Y | b_amcmbt | Bobcat (Light Tank) | ; csv:0 |
| avmine | base | minelayer | Minelayer |  | MINE LAYER: | - | b_amcmbt | Unabomber (Minelayer) | ; csv:0 |
| avmuf | base | factory | Factory |  | MOBILE UNIT FACTORY: | - | b_amprod |  | ; csv:0 |
| avrckt | base | wingman | Rocket Tank | Wolverine | WOLVERINE - ROCKET TANK: | Y | b_amcmbt | Wolverine (Rocket Tank) | misn07.des:8; csv:0 |
| avrecy | base | recycler | Recycler |  | RECYCLER: | - | b_amprod | Recycler | ; csv:0 |
| avscav | base | scavenger | Scavenger |  | SCAVENGER - SCRAP GATHERER: | - | b_amprod | Scavenger | bd04001.otf:1, bd04lsea.des:1, bd06lsea.des:1, bdmisn01.des:1 (+16); csv:19 |
| avslf | base | armory | Armory |  | ARMORY: | - | b_amprod |  | ; csv:0 |
| avtank | base | wingman | Tank | Grizzly | GRIZZLY - MEDIUM TANK: | Y | b_amcmbt | Grizzly (Tank) | ; csv:85 |
| avturr | base | turrettank | Turret |  | BADGER - TURRET TANK: | - | b_amcmbt | Badger (Turret) | misn03.des:7, misn03.des:9, tran02.des:1; csv:2 |
| avwalk | base | walker | Walker | Sasquatch | SASQUATCH - ASSAULT WALKER: | Y | b_amcmbt | Sasquatch (Walker) | ; csv:1 |
| bvapc | base | apc | APC |  | RAT PACK - APC: | - | b_bdcmbt |  | ; csv:0 |
| bvartl | base | howitzer | Howitzer |  | LONGBOW - ARTILLERY: | - | b_bdcmbt |  | ; csv:0 |
| bvcnst | base | constructionrig | Constructor |  | CONSTRUCTION UNIT: | - | b_bdprod |  | ; csv:0 |
| bvhaul | base | tug | Tug |  | HAULER - CARGO TUG: | - | b_bdprod |  | ; csv:0 |
| bvhraz | base | wingman | Bomber | BDog Bomber | THUNDERBOLT - HEAVY BOMBER: | Y | b_bdcmbt |  | bdmisn04.des:1, misns3.des:9; csv:0 |
| bvltnk | base | wingman | Light Tank | BDog Bobcat | BOBCAT - LIGHT TANK: | Y | b_bdcmbt |  | ; csv:0 |
| bvmine | base | minelayer | Minelayer |  | UNABOMBER - MINE LAYER: | - | b_bdcmbt |  | ; csv:0 |
| bvmru | base | minelayer | Mobile Repair Unit |  | NIGHTINGALE - MOBILE REPAIR UNIT: | - | b_bdextr |  | ; csv:0 |
| bvmuf | base | factory | Factory |  | MOBILE UNIT FACTORY: | - | b_bdprod |  | ; csv:0 |
| bvraz | base | wingman | Scout | BDog Razor | RAZOR - LIGHT ATTACK VEHICLE: | Y | b_bdcmbt |  | bdmisn04.des:4; csv:5 |
| bvrckt | base | wingman | Rocket Tank |  | WOLVERINE - ROCKET TANK: | - | b_bdcmbt |  | misn07.des:8; csv:0 |
| bvrdev | base | wingman | Red Devil | Red Devil | BLACK DOG RED DEVIL: | Y | b_bdextr | Red Devil | bdmisn04.des:4, bdmisn05.des:11, bdmisn06.des:8; csv:1 |
| bvrecy | base | recycler | Recycler |  | RECYCLER: | - | b_bdprod |  | ; csv:0 |
| bvscav | base | scavenger | Scavenger |  | SCAVENGER - SCRAP GATHERER: | - | b_bdprod |  | bd04001.otf:1, bd04lsea.des:1, bd06lsea.des:1, bdmisn01.des:1 (+16); csv:19 |
| bvslf | base | armory | Armory |  | SUPPLY LAUNCH FACILITY: | - | b_bdprod |  | ; csv:0 |
| bvtank | base | wingman | Tank | BDog Grizzly | GRIZZLY - MEDIUM TANK: | Y | b_bdcmbt |  | ; csv:85 |
| bvturr | base | turrettank | Turret |  | BADGER - TURRET TANK: | - | b_bdcmbt |  | misn03.des:7, misn03.des:9, tran02.des:1; csv:2 |
| bvwalk | base | walker | Walker |  | SASQUACH - ASSAULT WALKER: | - | b_bdcmbt |  | ; csv:0 |
| cvapc | red_odyssey | apc | APC |  | PANDA - APC: | - | b_chcmbt |  | ; csv:0 |
| cvartl | red_odyssey | howitzer | Howitzer |  | ARCHER - ARTILLERY: | - | b_chcmbt | Archer (Howitzer) | ; csv:0 |
| cvcnst | red_odyssey | constructionrig | Constructor |  | ERECTOR - CONSTRUCTION UNIT: | - | b_chprod |  | ; csv:0 |
| cvfigh | red_odyssey | wingman | Fighter | Mongoose | MONGOOSE - LIGHT ATTACK VEHICLE: | Y | b_chcmbt | Mongoose (Fighter) | ; csv:0 |
| cvhaul | red_odyssey | tug | Tug |  | OX - CARGO TUG: | - | b_chprod | Ox (Tug) | ; csv:0 |
| cvhraz | red_odyssey | wingman | Bomber | Phoenix | PHOENIX - HEAVY BOMBER: | Y | b_chcmbt | Phoenix (Bomber) | ; csv:0 |
| cvhtnk | red_odyssey | wingman | Heavy Tank | Emperor | EMPEROR - HEAVY TANK: | Y | b_chextr |  | ; csv:0 |
| cvltnk | red_odyssey | wingman | Light Tank | Naga | NAGA - LIGHT TANK: | Y | b_chcmbt | Naga (Light Tank) | waring.des:20; csv:0 |
| cvmine | red_odyssey | minelayer | Minelayer |  | KHAN - MINE LAYER: | - | b_chcmbt | Khan (Minelayer) | ; csv:0 |
| cvmuf | red_odyssey | factory | Factory |  | MOBILE UNIT FACTORY: | - | b_chprod |  | ; csv:0 |
| cvrckt | red_odyssey | wingman | Rocket Tank | Dragon | DRAGON - ROCKET TANK: | Y | b_chcmbt | Dragon (Rocket Tank) | ; csv:0 |
| cvrecy | red_odyssey | recycler | Recycler |  | RECYCLER: | - | b_chprod | Recycler | ; csv:0 |
| cvscav | red_odyssey | scavenger | Scavenger |  | MONKEY - SCRAP GATHERER: | - | b_chprod | Monkey (Scavenger) | ; csv:0 |
| cvslf | red_odyssey | armory | Armory |  | SUPPLY LAUNCH FACILITY: | - | b_chprod |  | ; csv:0 |
| cvtank | red_odyssey | wingman | Tank |  | YETI - MEDIUM TANK: | - | b_chcmbt | Yeti (Tank) | ; csv:0 |
| cvturr | red_odyssey | turrettank | Turret | Adder | ADDER - TURRET TANK: | Y | b_chcmbt | Adder (Turret) | ; csv:0 |
| cvwalk | red_odyssey | walker | Walker |  | YEREN - ASSAULT WALKER: | Y | b_chcmbt | Mongo : Yeren (Walker) | ; csv:0 |
| svapc | base | apc | APC |  | PERSONNEL CARRIER - APC: | - | b_socmbt |  | misn08.des:7; csv:0 |
| svartl | base | howitzer | Howitzer |  | CANNONEER - ARTILLERY: | - | b_socmbt | Cannoneer (Howitzer) | ; csv:0 |
| svcnst | base | constructionrig | Constructor |  | ERECTOR - CONSTRUCTION UNIT: | - | b_soprod |  | ; csv:0 |
| svfigh | base | wingman | Fighter |  | FLANKER - LIGHT ATTACK VEHICLE: | - | b_socmbt | Flanker (Fighter) | misns2.des:7; csv:0 |
| svhaul | base | tug | Tug |  | TRACTOR - CARGO TUG: | - | b_soprod | Tractor (Tug) | ; csv:0 |
| svhraz | base | wingman | Bomber | Grendel | GRENDEL - HEAVY BOMBER: | Y | b_socmbt | Grendel (Bomber) | misns3.des:9; csv:0 |
| svltnk | base | wingman | Light Tank | Stoli | STOLI - LIGHT TANK: | Y | b_socmbt | Stoli (Light Tank) | ; csv:0 |
| svmine | base | minelayer | Minelayer |  | MOLOTOV - MINE LAYER: | - | b_socmbt | Molotov (Minelayer) | ; csv:0 |
| svmuf | base | factory | Factory |  | MOBILE UNIT FACTORY: | - | b_soprod |  | ; csv:0 |
| svrckt | base | wingman | Rocket Tank | Tusker | TUSKER - ROCKET TANK: | Y | b_socmbt | Rocket Tank (Unused) | ; csv:0 |
| svrecy | base | recycler | Recycler |  | RECYCLER: | - | b_soprod | Recycler | ; csv:0 |
| svsav | base | sav | Fury |  | Name: Fury Hybrid | - | b_soextr |  | ; csv:0 |
| svscav | base | scavenger | Scavenger |  | SCAVENGER - SCRAP GATHERER: | - | b_soprod | Scavenger | bd04001.otf:1, bd04lsea.des:1, bd06lsea.des:1, bdmisn01.des:1 (+16); csv:19 |
| svslf | base | armory | Armory |  | SUPPLY LAUNCH FACILITY: | - | b_soprod |  | ; csv:0 |
| svtank | base | wingman | Tank | Czar | CZAR - MEDIUM TANK: | Y | b_socmbt | Czar (Tank) | misns2.des:7; csv:0 |
| svturr | base | turrettank | Turret |  | PAK - TURRET TANK: | - | b_socmbt | Pak (Turret) | ; csv:1 |
| svwalk | base | walker | Walker |  | GOLEM - ASSAULT WALKER: | Y | b_socmbt | Golem (Walker) | misns1.des:8; csv:4 |

## B. Briefings, debriefs, images per campaign (SO; text from bzone_en.zfs, Red Odyssey data from tro_cam.zfs)

No `_2.des` style files exist. Scheme: `<mission>.des` = briefing; `l#`/`lse?` = lose debrief; `w#`/`win` = win debrief; `f#` = further outcome variants (meaning UNVERIFIED); `.otf` = objective text.

| Campaign | Briefing pattern | .des files | .otf files | SL scope | Notes |
|---|---|---|---|---|---|
| NSDF | misn01..misn18 (+ misn02b, misn15b, misn16b) with l#, w#, f# | 80 (`misn[0-9][0-9]*`) | 71 `misn*.otf` (NSDF; some may be shared) | base | misn03.des (Recycler Montana, M173 Badger), misn07.des:8 (Wolverine) |
| CCA | misns1..misns8 (+ misnsw1) with l#, w#, f# | 29 (`misns*`) | 24 `misns*.otf` | base | misns2.des:7 Czar and Flanker, misns3.des:9 Grendel, misns1.des:8 Golem |
| Training | tran02, tran03, tran04, each with l1 and w1 | 9 | 6 `tran*.otf` | base | tran02.des:1 `M173 Badger` |
| Black Dogs | bdmisn01..bdmisn15 | 15 briefings + 51 debriefs (bdNNwin/lose/lsea-lsee) = 66 | 46 `bd*.otf` | red_odyssey | bdmisn04/05/06.des name Red Devil |
| Chinese (Red Odyssey) | chmisn01..chmisn08 | 8 briefings + 36 debriefs = 44 | 35 `ch*.otf` | red_odyssey | |
| Multiplayer/demo | mult*.des, play01, demo01 | 38 | - | base | map blurbs, not campaign |
| Planets | mars, venus, moon, io, europa, ganymede, elysium, titan | 8 | - | mixed | location text |
| Credits | achilles ... waring, evolve_1-5 | 30 | - | base | developer credits |
| Unit stat sheets | `<odf>.des` for 50 unit/pilot ODFs | 50 | - | base + red_odyssey | HULL/AMMO/weapons only |

Other .otf: defend.otf, recon.otf. Mission images: 0 per campaign (finding 4). Campaign VO: GB campaigns.csv (778 rows, 53 flagged unused per AGENT_GUIDE); NSDF `misnNNxx.wav`, CCA `misns...`, training `tranNNxx`, Chinese `ch0xxxx.wav`.

## C. Gaps (246 vehicle/pilot-class ODFs `[abcs]v*`/`*s(user|pilo)` scanned)

- No .inf and no stat .des (nothing to cite): avdemo, avremp, avsav, bvltnka, bvremp, cvmump, cvremp, svarmp, svhrmp, svmfs8, svremp, svtnk7, svwatm. Purpose of `*remp`/`*mump` UNVERIFIED.
- Stat .des but no .inf: cvwamp (netveh name "Yeren").
- netveh name but .inf header carries a different name: avtamp "Stealth Tank" (inf: GRIZZLY), avwamp "Sasquatch AG" (inf: "SASQUACH" typo), cvhmpa "Chancellor" / cvhmpb "Regent" (inf: EMPEROR), cvhzmp "Unix" (inf: PHOENIX), cvtmpa "Kaksha" (inf: YETI), bvrmpa "Crimson Bastard" / bvrmpb "Scarlet Git" (own infs exist: BLACK DOG CRIMSON BASTARD / SCARLET GIT).
- Buildable units whose .inf header has only a generic label (no name): avcnst/bvcnst `CONSTRUCTION UNIT:`, avmine `MINE LAYER:`, avslf `ARMORY:`, all *muf `MOBILE UNIT FACTORY:`, avrecy/svrecy/cvrecy `RECYCLER:`. svsav (Fury) inf starts `Name: Fury Hybrid` (different format).
- Orphan .inf with no ODF (7): aprckb, avart8, bvlntk, gwaspmsl, npscr100, sprckb, svlntk (avart8/bvlntk/svlntk look like legacy spellings of avartl/bvltnk/svltnk: UNVERIFIED).
- Units whose name appears in NO .des/.otf and NO campaign VO (only .inf and netveh): Bobcat, Longbow, Hauler, Stoli, Tusker, Capitan, Emperor, Chancellor, Regent, Dragon, Yeti, Adder, Yeren, Panda, Archer, Erector, Ox, Monkey, Kaksha, Unix, Weasel, Crimson Bastard, Scarlet Git, Thunderbolt (only in bvhraza.inf:3). Case-insensitive word search; false positives removed.
- Name collisions: `Grizzly One` (85 rows) and `Razor One` (misn0701-0703), `Sasquatch One` (misn0910), `Pak 1` (misns721) are callsigns, not unit citations. Scavenger/Recycler hits are generic.

## D. Surprises
- Duplicate .inf: 101 groups, 292 of 502 .inf files are byte-identical (after CRLF normalisation) to at least one other. Largest: 13 factory infs (avmu7, avmu8, avmuf, avmuf4-6, cvmuf, cvmufa-c, savmf, svmuf, svmuf13); 9 Mongoose (cvfigh..cvfighh); 8 Recycler (avrec2-8, avret3); 7 Yeti (cvtank, cvtmpa, cvtnk, cvtnka-d). Black Dog units mostly reuse NSDF names in the inf (bvtank/bvturr/bvraz say GRIZZLY/BADGER/RAZOR) while netveh calls them "BDog Grizzly" etc.
- Stock typos preserved: svdemo.inf:1 "LIGHT ATTACH VEHICLE", avwamp.inf/bvwalk.inf "SASQUACH".
- .inf files that are not unit descriptions: buildings (ab/bb/cb/sb/hb/ob ~135), powerups and weapons (ap/cp/sp, e.g. `apammo.inf` AMMO POWER-UP, `apbolt.inf` BOLT BUDDY 2000, `apcmet.inf` COMET CRUISE MISSILE), nav beacons, `hbfacta.inf` (joke placeholder, "Well, it's yo Mama!"), svtas8.inf (body is the single word "Romeski", a named unit, not a description), svapcc..svapcs (`TRANSPORT CARRYING:` mission cargo notes), svapcq (`GENERAL'S APC`), svapca (`ALIEN RELIC TRANSPORT`). hvsat.inf:5,7 says "Fury Tank" while svsav.inf says "Fury Hybrid".
- Encoding: all .inf and .otf are pure 7-bit ASCII; only briand.des has a high byte (0xE1, Latin-1; a credits file). No BOM. Line endings are mixed (inf 484 CRLF / 18 LF-only; des 215/139; otf 151/33) so split on both. GB CSVs are UTF-8 but some cells contain replacement characters (e.g. campaigns.csv misn0818 row).
- GB units.csv directory labels (`NSDF/Rat Pak (APC)`, `CRA/Mongo : Yeren (Walker)`, `CCA/Rocket Tank (Unused)`, `CRA/Tank (Unused)`) are transcriber folder names, not stock text ("Rat Pak" vs inf "RAT PACK"). Black Dogs have only one VO folder (`Black Dogs/Red Devil`, bvrdevv*); whether other bv* reuse NSDF VO is UNVERIFIED. VO stems differ from ODF names: avapcv->avapc, avcons->avcnst, avmufv->avmuf, avslfv->avslf, svapcv->svapc, cvtnkv = "Tank (Unused)".
- netveh.odf names exist for multiplayer `*mp*` variants whose own .inf headers reuse the base unit name.
- Process note: the scratchpad dir is shared; my helper scripts overwrote same-named files an.py, b.py, c.py, rows.json there. Harmless to the repo but may have clobbered earlier scratch.
