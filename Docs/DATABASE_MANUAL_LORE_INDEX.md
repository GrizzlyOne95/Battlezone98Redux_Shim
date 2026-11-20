# Battlezone lore/fact index (paraphrased facts only)

Sources and citation keys
- **M pN** = BZ98 Redux manual PDF, PDF page index N (printed page numbers in brackets). Text extracted with pdftotext to `lore_manual_paged.txt` (same folder).
- **G Lnnnn** = 1998 Brady guide OCR text file, line number nnnn (`2913c44b-manual-text.txt`). OCR is noisy.
- ODF mappings are all UNVERIFIED (neither source states ODF names).
- Faction note: Manual calls the American side "NSDF / Stars and Stripes" and the Soviet side "CCA / Red Brigade". "Black Dogs" are an American sub-force in the Soviet campaign. No "Chinese" or "Red Odyssey" content in either source (grep 0 hits).

## 1. Key finding: Badger designation
| Source | Designation | Cite |
|---|---|---|
| Manual unit card | **NSDF M173 Turret, code name Badger** ("The M173 Badger") | M p11 [18-19] |
| Manual commander memo | "M173 Badger", "M173 turret" (several times) | M p25 [46-47] |
| Manual Longbow card | "M183 Longbow ... much the same as the M173 Badger" | M p13 [22-23] |
| Guide unit chapter | "NSDF M173 Turret, Code Name: Badger" | G L2251-2253 |
| Guide Longbow text | OCR "Ml 73 Badger" (= M173) | G L2505 |
| Guide training mission 4 text | **"T7 Badger turret"** | G L3571-3572 |
| Guide mission engineering report | **"T7 Badger Turrets"; "The T7 is an excellent defensive unit ... dual machine guns ... defends 150 meter radius when deployed"** | G L4003-4010 |
| Guide index | "T7 Badger" p55, "T7 Badger Turrets" p65, 85; "M173 Turret, see Badger" (OCR "Ml 73 Turret") | G L9074, 9337, 9622, 10218, 10370 |

- CONFLICT: Guide uses both M173 (unit stats chapter) and "T7" (mission text/index, 5+ places). The "T7" reading is consistent across index and body, so it is likely real, not OCR (OCR could mangle "T-7" to "T7" but not to a different number). Manual uses only M173. Stock files tran02.des / misn03.des use "M173 Badger" = matches both sources' unit-chapter designation.
- VO values "T-4 Badger" / "T-7 Badger": no "T-4" anywhere in either source (grep). "T7"/"T-7" appears only in the guide (above). The guide's "dual machine guns" vs the unit card "Minigun" (one weapon) is a further small inconsistency.
- UNVERIFIED: "T-4" has no source support in either document.

## 2. NSDF (Stars and Stripes) units
Stat key: Fwd/Rev/Strafe speed in m/s; "Scrap" = guide's Cost/Value; HP = guide "Health"; Manual has no HP or scrap values. Armour "EDD" = Equally Distributed Damage bio-metal armour (M p10).

| Code name | Designation / type (manual) | Built by | Manual stats | Guide stats | ODF (UNVERIFIED) |
|---|---|---|---|---|---|
| Razor | M580A2 Scout; Armoured Reconnaissance (M p10 [16-17]) | Recycler | 25/25/20, turn 150/s, armour 25mm EDD, ammo 600, 2x Minigun | Same speeds, scrap 8/3, HP 1800, radar range 300, burst speed "GO"(=60?) m/s OCR; G L2086-2120 | avfigh |
| Grizzly | M60A7 MBT Tank; Armoured Assault Tank (M p10) | Unit Factory | 20/15/20, 90/s, 30mm EDD, ammo 1200; AT-Stabber, Minigun, Manual Detonation Mortar, Thumper; 2000 hp thrusters | scrap 8/5, HP 3000, radar 400; G L2138-2193 | avtank |
| Wolverine | M60A8 Rocket Tank; Mid-Range Armoured Assault Tank (M p11 [18-19]) | Unit Factory | 20/15/20, 90/s, 25mm EDD, ammo 1000; Hornet Missile, Shadow Missile, Proximity Mine | Guide calls it "NSDF M60A8 Missile Tank"; scrap 8/5, HP 2500, radar 300; G L2197-2233 | avrckt |
| Badger | M173 Turret; Self-Propelled Defensive Turret (M p11) | Recycler | 15/15/15, 60/s, 20mm EDD, ammo 2000, Minigun; deploys STAB hooks (Stabilised Terrain Adapting Base), cannot fire undeployed | scrap 8/3, HP 2000, radar 200, armour "20mm"; G L2251-2297 | avturr |
| Bobcat | M47A9 Light Tank; Armoured Assault Tank (M p12 [20-21]) | Unit Factory (M) / Recycler (G) | 20/15/20, 120/s, 25mm EDD, ammo 1200; AT-Stabber, Hornet, Solar Flare | Guide weapons: AT-Stabber, Splinter Mortar; scrap 8/5, HP 3000; G L2309-2363 | avltnk |
| Thunderbolt | B74CT Bomber; Heavy Strike Cruiser | Unit Factory | 25/15/10, 60/s, 20mm EDD, ammo 1900, 2x Rocket Bomb (BFE9 "Fire-and-Forget") | Fwd 15.5 (OCR), scrap 11/5, HP 3000, radar 400; G L2366-2409 | avbomb |
| Tracker | AAV6A4 APC Transport; Armoured Personnel Carrier (M p13 [22-23]) | Unit Factory | 8/8/8, 90/s, 50mm EDD, unarmed; carries 5 infantry that can deploy to attack | scrap 6/5, HP 5000, radar 200; G L2415-2441 | avapc |
| Longbow | M183A1 Howitzer; Self-Propelled Long-Range Artillery Turret | Unit Factory | 15/10/15, 90/s, 30mm EDD, ammo 2000; STAB deployed, shells up to **750 m** | Guide says **1000 m** (OCR "1 000"); scrap 7/5, HP 3000; G L2465-2510 | avartl |
| Sasquatch | AT9 Walker; Mobile Assault Turret (M p14 [24-25]) | Unit Factory | 5.5/5.5/2, 90/s, 40mm EDD, ammo 2000, 2x AT-Stabber + Pop Gun; leg propulsion "no more than 8 m/s"; alien-origin | scrap 15/5, HP 4000; G L2519-2560 | avwalk |
| Unabomber | LMA6 Minelayer (guide OCR "LMAE"); Mine Deployment and Recovery | Unit Factory | 15/10/15, 90/s, 30mm EDD, ammo 2000, Proximity Mine; smart mines ignore friendlies | scrap 4/2, HP 3000; G L2563-2604 | avmine |
| Scavenger | VS3E Reclamation Unit; Remote Extraction (M p15 [26-27]) | Recycler | 15/10/15, 90/s, 30mm EDD, unarmed | scrap 4/2, HP 3000; G L2623-2660 | avscav |
| Tug | NSDF Cargo Utility; Cargo Propulsion Cab | Unit Factory | 8/8/15, 90/s, 50mm EDD, unarmed; hauls immobile objects/alien artefacts | HP 5000 (OCR); G L2663-2705 | avtug |
| Recycler | TU11 Mobile Bio-Metal Fabricator; Mobile Unit Factory (M p16 [28-29]) | - | 15/15/15, 100mm armour, unarmed; deploys over geyser; primary builder | Fwd 15/Rev 10, scrap 0/10, HP 10000, radar 1000; G L2708-2757 | avrecy |
| Heaval | TU15 Construction Rig; Pre-Fabricated Building Assembler | Recycler | 8/8/8, 90/s, 20mm, unarmed; builds whole base | scrap 10/B(=8?) , HP 2000, radar 400; code name OCR "Haaval"; G L2854-2896 | avcnst |
| SLF / Armoury | Guide: NSDF TU8 Supply Launch Facility (Supply Factory); manual calls the same function "Armoury" (M p24 [45], p38 command text) | Recycler | not in manual unit cards | 15/10/10, 100mm, scrap 8/6, HP 10000, radar 1000, geyser-powered, catapults supplies; G L2764-2807 | avslf |
| MUF | Guide: NSDF TU12 Advanced Bio-Metal Fabricator (OCR "TUI 2") | Recycler | Manual p24: builds specialised vehicles, geyser-powered | scrap 12/9, HP 10000, radar 1000; G L2810-2851 | avmuf |

- Guide multiplayer text calls Bobcat the "NSDF Light Tank" (G L8597). Guide mission text names Recyclers "Montana" (G L4003), "Texas" (G L6719) (instance names, not models).
- Manual M p36: units that can be commandeered when pilot killed include APC, Minelayer, Scavenger, Artillery, Razor, Tank, Heavy, Rocket Tank, Turret.

## 3. CCA / Soviet units (all known only by "Western nicknames", M p17 [31])
| Name | Manual (M p17-18 [30-33]) | Guide stats (G L2903-3096; no designations given) | ODF (UNVERIFIED) |
|---|---|---|---|
| Flanker | Wing-like appendages; about a Razor, probably better armoured | Fwd 30, scrap 6/3, HP 1800, ammo 600 | svfigh |
| Czar | Similar to Grizzly, better armoured, more nano-ammo; "likely to dominate" outer-space battlefield | Fwd 24, scrap 8/5, radar 400 (HP missing in OCR) | svtank |
| Tusker | Missile tank; more nano-ammo than Wolverine, more vulnerable | Fwd 45(?), scrap 8/5, HP 2500, ammo 1000 | svrckt |
| Stoli | Light tank like Bobcat, smaller, more experimental weapons | Fwd 20, scrap 8/5, HP 3000, ammo 1200 | svltnk |
| Grendel | Fast-strike; slower but slightly more agile than Thunderbolt | Fwd 15.5, Rev 18(?), scrap 11/5, HP 3000, ammo 1900 | svbomb |
| Golem | Most alien-influenced; weapons on head and shoulders, strongest weapons of any unit | Fwd 5.5, scrap 15/5, HP 4000, ammo 2000 | svwalk |
| CCA support | Transport, defence, mobile-construction units "roughly equivalent" to NSDF (no names) | same (G L3092) | svapc/svturr etc. |
- Guide mission text: "Golum"/"Galum" = Golem OCR variants (G L7028-7032). Czar escorts "Armored Personnel Transports (APCs)" carry scientists (G L7244-7247). Guide mentions "Hydra units" (Nexus facility), "SAVs" (G L5856, 8095), "Fury" units (see section 7); none have stats here.
- Black Dogs: American sub-force in Red Brigade campaign, own Recycler/MUF/silo/outpost/gun towers (G L7180-7182, 7481, 8106). No unit models listed for them.
- Redux manual: Red Brigade = Soviet forces vs "American Black Dog Brigade" (M p28 [53]). Guide: Red Brigade = 8 missions; Stars and Stripes = 17; 4 training missions (G L726-732).

## 4. Buildings (manual M p22-23 [40-42]; guide has no building stat table)
All power-needing buildings must be within 100 m of a power plant (M p22). Built by Construction Rig.
| Building | Function | Stats (cost / hit points) |
|---|---|---|
| Solar Power Plant | Power on all planets except Venus | 4 / 1500 |
| Lightning Power Plant | Power on Venus and Titan | 7 / 4000 |
| Wind Power Plant | Power on Titan, Venus, Mars | 6 / 2000 |
| Gun Tower (needs power) | Defensive weapon, range over 200 m | 6 / 5000 |
| Coms Tower (needs power) | Satellite uplink; user becomes radar-visible | 6 / 2000 |
| Barracks | +5 pilots | 8 / 1500 |
| Scrap Silo | Stores scrap; Scavenger drop-off (nearest of silo/Recycler) | 4 / 3000 |
| Supply Depot | Closest vehicle within 50 m regains 100 nano-ammo/s | 5 / 2000 |
| Hangar | Repair; closest vehicle within 50 m repaired | 7 / 4000 |
- Guide mission text adds: Armory/SLF builds Day Wrecker bomb, Solar Flare mine (G L4715-4718); Rig builds armories, hangars, comm towers, "long range radar arrays", gun towers, power supplies (G L4720-4722); the manual does not list "long range radar array".
- Guide: Comm Tower links to satellite "Skyeye" (manual, M p26 [48]); guide spells "Sky Eye" (G L6851).
- Geysers power Recycler, MUF, Armoury (M p40 [77]). Pre-built enemy structures named in guide: "Lerna" weapons facility on Io (G L5548), Lemnos bio-metal factory (G L4646).

## 5. Weapons
Manual (M p19-21 [34-39]) has text only; guide (G L1044-1755) has stat blocks. Values listed are guide unless noted.
| Weapon | Class | Key facts |
|---|---|---|
| "187 SMG" / Minigun (Standard Mini Gun; OCR may be "1S7"/"IS7": UNVERIFIED, raw "187 SMG" in both sources) | Cannon | 5 shots/s, range 300 m, 50 dmg, 20 nano-ammo (G L1046-1066) |
| AT-Stabber (guide: "T-Stabber, Tank Stabber") | Cannon | 1/s, 350 m, 80 dmg, 40 nano-ammo (G L1073-1107). Manual name expands "Anti-Tank" vs guide "Tank": CONFLICT |
| AT-Super Stabber | Cannon | 1 per 2 s, 400 m, 120 dmg, blast **1.5 m** (G) vs **5 m** (M p19 [35]): CONFLICT |
| MAG (Magnetic Acceleration Gun) | Cannon | Charge weapon: quick tap 6 balls x75, half charge 2 x150, full (4 s) 1 x400; range 250 m (M and G agree on range) |
| Flash Cannon "Hot Foot" | Cannon | Microwave, 200 m, heats engine; manual says "v-thruster", guide says "Mag Lev engine": minor CONFLICT |
| Blast Cannon | Cannon | Short laser burst, heavy nano-ammo; best on Gun Towers (no stat block) |
| TAG Cannon (Automated Targeting Gun) | Cannon | Leader round then homing "Swammer" round salvo; 200 dmg swarm rounds, 100 nano-ammo |
| Standard Mortar | Mortar | Range 500 m (G L1321); manual's text for it duplicates the Blast Cannon text (error in M p19) |
| Manual Detonation Mortar (MDM) | Mortar | Blast 15 m, 30 s life, bounces until detonated (G L1355) |
| Splinter / Death Wheel | Mortar | Spins and fires .72mm AP rounds for 5 s; guide "blast radius 600 meters in diameter" is suspect OCR |
| Day Wrecker | Mortar (Armoury-fired) | Range 1500 m, 750 dmg at epicentre, blast 20 m, 1000 nano-ammo; M p20 says shock wave 50 m diameter: partial conflict |
| Pop Gun | Mortar | 200 m altitude then homes; 75 dmg, blast 10 m, range 200 (G L1469-1491) |
| Thermal Hornet | Missile | Range 2000 m, 500 dmg, blast **1.5 m** (G) vs **5 m** (M p20): CONFLICT |
| Rocket Bomb | Missile | Hornet casing with more explosive; slow, heavy (M p20) |
| Image Locking Shadower (ILS) | Missile | 1000 m, 200 dmg, 60 nano-ammo |
| Comet Cruise Missile | Missile | Radar-guided, 1000 m, 100 dmg, 50 nano-ammo |
| Sand Bag Missile | Missile | Non-locking; slows target (+10% friction per hit), 10 s duration |
| RED-Field Generator | Special | Hides from radar 30 s (G L1781), 100 nano-ammo |
| M-Curtain Mine | Special | Magnetic dome 20 m dia x 3 m, blocks projectiles 30 s, 75 nano-ammo |
| Solar Flare | Special | Fire plume 5 m dia x 20 m high, 60 s, 100 dmg/tick, decoys heat seekers within 200 m |
| MITS | Special | Inverse of M-Curtain; traps vehicles, attracts radar-guided within 200 m, 30% lightning chance per 5 s |
| Proximity Mine | Special | Arms after 2 s, trigger radius 7 m (both sources agree) |
| SITE Camera | Special | X-ray through terrain, 100 m, 10 nano-ammo/s |
| Thumper | Special | Seismic shock wave from nano-ammo (M p21); no guide stat block found |
| Phantom-VIR | Special | False image 10 m north, 15 s, 200 nano-ammo (G L1723-1760; manual only names it in Options M p29) |
| Masgrenade | Special | Holographic imprint, makes target look like enemy for 15 s, 100 m range (G L2025-2049); not in manual weapons chapter |
- Pilot on-foot gear: plasma sidearm and Sniper Rifle (M p35).

## 6. Worlds (manual M p6-8 [8-13], all dated 1958 memo by Andrew Goldman)
| World | Stated facts |
|---|---|
| Luna | 3476 km dia, gravity 0.166, no atmosphere; light side 107 C, dark side -153 C; three bases proposed: far-side mining, near-side transport, north-pole power; possible south-pole ice (M p6 [8]) |
| Mars | 6794 km dia, gravity 0.377, avg -23 C; Olympus Mons 550 km wide, 27 km high; second choice for colonisation; cratering suggests bio-metal (M p6 [9]) |
| Venus | 0.7 AU, gravity 0.907, 460 C, 92 bar; sulphuric-acid cloud; lightning power; 12,103.6 km dia (M p7 [10]) |
| Europa | Water ice, gravity 0.135, -171 C, 3138 km dia; possible liquid water below (M p7 [11]) |
| Io | 3630 km dia, gravity 0.183, -163 C; sulphur volcanoes; tidal flex up to 100 m, base far from equator (M p8 [12]) |
| Titan | 5150 km dia, gravity 0.14, 1.5 bar, -180 C; lightning, wind and methane power; most Earth-like atmosphere (M p8 [13]) |
| Achilles | Guide only: small moon of Uranus; Furies' factory; core-power backlash risks moon exploding; full evacuation ordered (G L6686-6689, 6855-6863) |
| Other guide places | Lemnos bio-metal factory, Omega Star Port, Styx (Venus), Lerna (Io), Icarus (G L4646-4659, 5536-5548, 6414) |
- Mercury eliminated as a target; outer planets rejected (M p5 [7]).

## 7. Factions, people, story
- NSDF: secret force created June 1958 by President Eisenhower, led by Gen. George Collins, funded via NSA, cap 1000 personnel, first base on the dark side of the Moon; recruits under NASA cover (M p4 [4-5]).
- Bio-metal: found in 1952 Bering Strait meteor debris; has shape-memory; Arkin Industries chief Dr. Wilhelm Arkin designs vehicles (M p4, p9). In-game manual says Arkin's memo is dated Jan 3, 1956 (M p9 [15]).
- CCA: Cosmic Colonist Army (inferred by Western spy), run by "Big Bear"; Soviet ships for interplanetary travel at Workers Space Construction plant, Kinostan, Siberia; operative "Kino" (M p17 [30]). Guide gives "Alexi Doyestevski, CCA" as narrator (G L576), "Kamov" as the CCA general, "Professor Chestikov" the scientist (G L7229-7235), "General Smirnovitch" ("Smimovitch" OCR, UNVERIFIED) fired (G L7938).
- NSDF side characters: guide narrator "Jason Davies(?), NSDF" (G L494: OCR "JASON 13 a\ TIES" UNVERIFIED); "Commander William Stahl" memo July 3, 1959 on Arkin's designs (M p23 [43-50]); Case Officer Chico, CIA Director Allen Dulles (M p17).
- Cthonians: ancient alien race behind bio-metal; named from Greek myth; factions: Olympian Council (leader Paternus) vs Hadean Crown (ruler Nexus V); Nexus built the "Fury" weapon via aggression-laced bio-metal; Hercules Brigade, Hydra units; Hephaestus transport (G L4646-4670, 5522-5545, 5694-5701, 5856). Arkin is called a traitor in the guide (G L5846-5850).
- Ships: American destroyers Freedom, Justice, Liberty (G L6048, 6073, 8073).
- Command/Radar mechanics from Stahl memo: pulsing radar misses stationary vehicles; single nano-ammo pool; mobile factories need geysers (M p24 [44-45]).

## 8. Conflicts and uncertainties (summary)
1. **Badger designation**: M173 (manual, guide unit chapter, stock) vs "T7" (guide mission text and index) vs "T-4/T-7" (VO, not in either source). Section 1.
2. Wolverine type: Rocket Tank (manual) vs Missile Tank (guide).
3. Bobcat builder: Unit Factory (manual) vs Recycler (guide). Guide mission text says Recycler builds "Tanks" in other spots, so factory assignments differ by mission/version.
4. Longbow range: 750 m (manual) vs 1000 m (guide).
5. Grizzly top speed: 20 m/s (manual) vs OCR "50 meters per second" (G L2185, UNVERIFIED; may be "20" or "60"). Razor "GO m/s" (OCR) matches manual's 60.
6. Hornet and Super Stabber blast radius: 5 m (manual) vs 1.5 m (guide).
7. AT-Stabber expansion: Anti-Tank (manual) vs Tank Stabber/T-Stabber (guide).
8. Flash Cannon: v-thruster (manual) vs Mag Lev (guide).
9. Day Wrecker: 50 m shock wave (manual) vs 20 m blast radius (guide).
10. Thunderbolt forward speed: 25 (manual) vs OCR "15.5" (guide, same as Grendel row; UNVERIFIED).
11. Wolverine weapons: manual adds Proximity Mine; guide list shows only Hornet/Shadow (OCR may have dropped it).
12. Bobcat weapons: manual AT-Stabber, Hornet, Solar Flare vs guide AT-Stabber, Splinter Mortar.
13. Armoury vs SLF naming (Armoury = Supply Launch Facility, same function).
14. Pilot/Black Dogs: manual calls Red Brigade vs "American Black Dog Brigade"; guide has Black Dogs as NSDF secondary force on Io (G L7455-7457).
15. OCR-uncertain raw readings (UNVERIFIED): "187 SMG" (maybe 1S7), "Haaval" (Heaval), "Racyclar" (Recycler), "Ml 73" (M173), "LMAE" (LMA6), "TUI 2"/"TUI 5" (TU12/TU15), "Smimovitch", "Golum/Galum", "Sasguatch", "Slobber/Slabber" (Stabber), "Scrap Cost/Value: 10/B".
16. Manual says Heaval's code name; the guide's Scout/Razor "Scout" in mission text is the Razor.

## Resolved against stock ODFs (2026-11-20)

Stock ODF values win over both books. The Database reads stats live from the ODF.

- **Longbow range:** about 560 m in stock (user). `avartl.odf:16` fires `ghartill` (class mortar, ordnance `shell`); `shell.odf:15` sets `shotSpeed = 75.0`. A ballistic arc at 75 m/s and 9.8 m/s² peaks at about 574 m, which agrees. The manual (750 m) and the guide (1000 m) are both wrong for stock.
- **Hornet blast radius:** 5 m. `ghornet.odf` fires `heatmsl`, whose explosions `xmslcar.odf:9`, `xmslgnd.odf:9` and `xmslbld.odf:9` all set `damageRadius = 5.0` (50 concussion damage); `heatmsl.odf` sets `damageBallistic = 900`. This matches the manual; the guide's 1.5 m is wrong.
- **Bobcat producer:** the Factory. `avmuf.odf:71` has `buildItem2 = "avltnk"` (user confirmed). The guide's "Recycler" is wrong.
