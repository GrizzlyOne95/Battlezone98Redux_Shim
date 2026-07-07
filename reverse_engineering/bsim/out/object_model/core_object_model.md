# Battlezone 1.5 object model (from bzint.pdb)

Reconstructed from the exact-match 1.5 PDB: **6290 structs, 552 enums, 1124 classes with methods**. This is the authoritative schema the HoverZone UE port mirrors.

Full machine-readable detail (all 1014 game types): `object_model.json`. Every struct/size: `all_types_index.csv`.

## Core classes

Jump: [GameObject](#gameobject) · [GameObjectClass](#gameobjectclass) · [Craft](#craft) · [CraftClass](#craftclass) · [HoverCraft](#hovercraft) · [HoverCraftClass](#hovercraftclass) · [Walker](#walker) · [Ordnance](#ordnance) · [OrdnanceClass](#ordnanceclass) · [Weapon](#weapon) · [WeaponClass](#weaponclass) · [Building](#building) · [BuildingClass](#buildingclass) · [AnimBuilding](#animbuilding) · [AmmoPowerup](#ammopowerup) · [HealthPowerup](#healthpowerup) · [FlareMine](#flaremine) · [AIController](#aicontroller) · [AiMission](#aimission) · [AiMissionClass](#aimissionclass) · [Team](#team) · [GamePlayerList](#gameplayerlist) · [DistributedObject](#distributedobject)

### `GameObject`  — 544 bytes
_base (inferred): `Crater` / `IDirectDrawSurface3Vtbl` / `Scheduler` / `vtshape41703` · 96 fields · 138 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 160 bytes)* | |
| `+0x00a0` | `OrdnanceClass *` | hitOrdClass |
| `+0x00a4` | `bool` | isCargo |
| `+0x00a8` | `GameObject *` | tug |
| `+0x00ac` | `AiCmdInfo` | curCmd |
| `+0x00c4` | `AiCmdInfo` | nextCmd |
| `+0x00dc` | `float` | illumination |
| `+0x00e0` | `GameObjectClass *` | curPilot |
| `+0x00e4` | `tagENTITY *` | ent |
| `+0x00e8` | `_OBJ76 *` | obj |
| `+0x00ec` | `GameObjectClass *` | objClass |
| `+0x00f0` | `AiProcess *` | aiProcess |
| `+0x00f4` | `char *` | label |
| `+0x00f8` | `int` | independence |
| `+0x00fc` | `VECTOR_3D` | pos |
| `+0x0108` | `EULER` | euler |
| `+0x0150` | `int` | seqNo |
| `+0x0154` | `int` | indexNo |
| `+0x0158` | `float` | collisionRadius |
| `+0x015c` | `ulong` | createTime |
| `+0x0160` | `long` | liveColor |
| `+0x0164` | `long` | deadColor |
| `+0x0168` | `int` | teamNumber |
| `+0x016c` | `int` | teamSlot |
| `+0x0170` | `Team *` | teamList |
| `+0x0174` | `int` | perceivedTeam |
| `+0x0178` | `int` | nameIndex |
| `+0x017c` | `char *` | name |
| `+0x0180` | `bool` | isObjective |
| `+0x0181` | `bool` | isSelected |
| `+0x0184` | `ulong` | isVisible |
| `+0x0188` | `ulong` | seen |
| `+0x018c` | `ulong` | locked |
| `+0x0190` | `Scanner *` | scanner |
| `+0x0194` | `Jammer *` | jammer |
| `+0x0198` | `Carrier *` | carrier |
| `+0x019c` | `ModeList` | modeList |
| `+0x01d0` | `float` | playerShot |
| `+0x01d4` | `float` | playerCollide |
| `+0x01d8` | `float` | friendShot |
| `+0x01dc` | `float` | friendCollide |
| `+0x01e0` | `float` | enemyShot |
| `+0x01e4` | `float` | enemyCollide |
| `+0x01e8` | `float` | groundCollide |
| `+0x01ec` | `int` | who_shot_JR |
| `+0x01f0` | `int` | who_i_shot |
| `+0x01f4` | `float` | when_i_shot |
| `+0x01f8` | `float` | healthRatio |
| `+0x01fc` | `float` | curHealth |
| `+0x0200` | `float` | maxHealth |
| `+0x0204` | `float` | ammoRatio |
| `+0x0208` | `long` | curAmmo |
| `+0x020c` | `long` | maxAmmo |
| `+0x0210` | `long` | weaponMask |
| `+0x0214` | `int` | targetHandle |
| `+0x0218` | `_OBJ76 *` | hitch |
| `+0x021c` | `int` | ownerHandle |

**Methods (138):** `GetUser`, `GetAIProcess`, `GetEuler`, `GetUserTeam`, `GetUserTeamList`, `GetHandle`, `GetLabel`, `GetSphere`, `GetFlags`, `GetSeqNo`, `GetCollisionRadius`, `GetFrontVector`, `GetTransform`, `GetVelocity`, `GetSpeed`, `GetMaxHealth`, `GetWeaponMask`, `GetWhoTheHellShotMe`, `GetWhoIShot`, `GetWhenIShot`, `GetTeamSlot`, `GetTeamList`, `GetPerceivedTeam`, `IsVisibleTo`, `IsLocked`, `IsCargo`, `GetCarrier`, `GetTarget`, `PeekWhat`, `GetLastEnemyShot`, `SetLabel`, `UpdatePosition`, `SetTransform`, `GetCurHealth`, `SetLocked`, `UnSetLocked`, `GetScanner`, `HasBenSeen`, `SetTarget`, `GetLastPlayerShot`, `GetOrigin`, `SetOrigin`, `SetVelocity`, `SetCurHealth`, `SetMaxHealth`, `GetAmmo`, `GetCurAmmo`, `GetMaxAmmo`, `SetMaxAmmo`, `SetWeaponMask`, `GetLastFriendShot`, `GetName`, `SetName`, `SetObjective`, `IsSelected`, `SetOwner`, `GetOwner`, `SetCurAmmo`, `SetIndependence`, `GetIndexNo`, `GetOBJ76`, `GetEntity`, `IsSnipable`, `GetPosition`, `GetHealth`, `GetAmmoGauge`, `GetClass`, `GetTeam`, `Select`, `Deselect`, `GetHitch`, `SetActiveMode`, `GetCommand`, `GetCommand`, `DoesSpecialCollision`, `UpdateModeList`, `PostSimulate`, `IsObjective`, `GetActiveMode`, `AddVelocity`, `FullVisibility`, `GetSeqCount`, `SetSeqCount`, `InitHandles`, `operator_delete`, `GetObj`, `Init`, `Remove`, `SetTeamSlot`, `SetTeam`, `SetPerceivedTeam`, `FriendP`, `EnemyP`, `Cleanup`, `AssignColor`, `SetAIProcess`, `SetAsUser`, `SetAsNotUser`, `SetCommand`, `GetWhat`, `ClearCommand`, `CanCommand`, `SetCommand`, `SetCommand`, `SetCommand`, `SetCommand`, `SetCommand`, `GetWhere`, `Simulate`, `AddHealth`, `SetWhoIShot`, `AdjustDamageValues`, `LoadAll`, `PostLoad`, `Save`, `FriendP`, `EnemyP`, `Init`, `GetWho`, `AddAmmo`, `SetDamageFlags`, `Load`, `PostLoadAll`, `SaveAll`, `~GameObject`, `RegCollision`, `DamageAlloc`, `operator_new`, ``scalar_deleting_destructor'`, `GameObject`, `SetVisibility`, `ClearVisibility`, `GetJammer`, `GetColor`, `GetNameIndex`, `SetSelected`, `GetModes`, `SetFrontVector`


---

### `GameObjectClass`  — 336 bytes
_42 fields · 12 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 32 bytes)* | |
| `+0x0020` | `ulong` | sig |
| `+0x0024` | `char *` | label |
| `+0x0028` | `OBJECT_CLASS_T` | class_id |
| `+0x002c` | `GameObjectClass *` | proto |
| `+0x0030` | `long64` | base |
| `+0x0038` | `long64` | cfg |
| `+0x0040` | `char[16]` | odf |
| `+0x0050` | `long` | scrapCost |
| `+0x0054` | `long` | scrapValue |
| `+0x0058` | `long` | pilotCost |
| `+0x005c` | `float` | buildTime |
| `+0x0060` | `long` | maxHealth |
| `+0x0064` | `long` | maxAmmo |
| `+0x0068` | `int` | unitNameIndex |
| `+0x006c` | `char[32]` | unitName |
| `+0x008c` | `char[32]` | aiName |
| `+0x00ac` | `char[32]` | aiName2 |
| `+0x00cc` | `long` | weaponMask |
| `+0x00d0` | `float` | collisionRadius |
| `+0x00d4` | `char` | nation |
| `+0x00d8` | `GameObjectClass *` | pilotClass |
| `+0x00dc` | `GameObjectClass *` | userClass |
| `+0x00e0` | `float` | imageSignature |
| `+0x00e4` | `float` | radarSignature |
| `+0x00e8` | `float` | heatSignature |
| `+0x00ec` | `char[5][4]` | weaponHard |
| `+0x0100` | `WeaponClass *[5]` | weaponClass |
| `+0x0114` | `BBOX` | bBox |
| `+0x012c` | `SPHERE` | bSphere |
| `+0x013c` | `float` | boundingWidth |
| `+0x0140` | `float` | boundingHeight |
| `+0x0144` | `int` | categoryMin |
| `+0x0148` | `int` | categoryMax |
| `+0x014c` | `char *` | infoText |

**Methods (12):** `GetBoundingSphere`, `Find`, `GetBoundingBox`, `~GameObjectClass`, `Build`, `InitBoundingData`, ``scalar_deleting_destructor'`, `GetProtoList`, `Find`, `Clean`, `GameObjectClass`, `GameObjectClass`


---

### `Craft`  — 616 bytes
_147 fields · 46 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 544 bytes)* | |
| `+0x0220` | `VEHICLE_STATE` | state |
| `+0x0224` | `int` | abandoned |
| `+0x0228` | `VEHICLE *` | vhcl |
| `+0x022c` | `int` | pathingType |
| `+0x0230` | `SmokeEmitter *` | smokeEmitter |
| `+0x0234` | `float` | smokeTimer |
| `+0x0238` | `_OBJ76 *[8]` | smokeList |
| `+0x0258` | `long` | smokeCount |
| `+0x025c` | `float` | pitchAng |
| `+0x0260` | `ulong` | lastCollideTime |
| `+0x0264` | `float` | fPersonEjectRatio |

**Methods (46):** `IsSnipable`, `SetRecycle`, `GetRecycle`, `FindSmokeSource`, `Init`, `Cleanup`, `Load`, `PostLoad`, `Save`, `Remove`, `SetActiveMode`, `AddHealth`, `UpdateTemperature`, `PostSimulate`, `SetSmoke`, `BuildPilot`, `Deploy`, `IsDeployed`, `Packup`, `IsUnDeployed`, `Init`, `ControlHeading`, `RegCollision`, `DoCollision`, `GroundCheck`, `DamageAlloc`, `UpdateWeaponAim`, `Simulate`, `Explode`, `ExplodePilot`, `RemovePilot`, `EjectPilot`, `AbandonPilot`, `GetCommand`, `GetCommand`, `PackTempState`, `UnPackTempState`, `~Craft`, `GetThrottle`, `GetAirborne`, `ControlSpeed`, `MaxTurningSpeed`, `ControlForward`, ``scalar_deleting_destructor'`, `Craft`, `GetPitchAngle`


---

### `CraftClass`  — 768 bytes
_114 fields · 6 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 336 bytes)* | |
| `+0x0150` | `float` | rangeScan |
| `+0x0154` | `float` | periodScan |
| `+0x0158` | `float` | velocJam |
| `+0x015c` | `float` | fPersonEjectRatio |
| `+0x0160` | `char[16]` | selectWaitMsg |
| `+0x0170` | `char[16]` | selectGoMsg |
| `+0x0180` | `char[16]` | selectFollowMsg |
| `+0x0190` | `char[16]` | selectAttackMsg |
| `+0x01a0` | `char[16]` | selectPickupMsg |
| `+0x01b0` | `char[16]` | selectDropoffMsg |
| `+0x01c0` | `char[16]` | selectDeployMsg |
| `+0x01d0` | `char[16]` | selectUser1Msg |
| `+0x01e0` | `char[16]` | selectUser2Msg |
| `+0x01f0` | `char[16]` | selectOtherMsg |
| `+0x0200` | `char[16]` | goMsg |
| `+0x0210` | `char[16]` | goObjectMsg |
| `+0x0220` | `char[16]` | followMsg |
| `+0x0230` | `char[16]` | followMeMsg |
| `+0x0240` | `char[16]` | attackMsg |
| `+0x0250` | `char[16]` | repairMsg |
| `+0x0260` | `char[16]` | reloadMsg |
| `+0x0270` | `char[16]` | rescueMsg |
| `+0x0280` | `char[16]` | recycleMsg |
| `+0x0290` | `char[16]` | user1Msg |
| `+0x02a0` | `char[16]` | user2Msg |
| `+0x02b0` | `char[16]` | otherMsg |
| `+0x02c0` | `char[16]` | deployedMsg |
| `+0x02d0` | `char[16]` | packedMsg |
| `+0x02e0` | `char[16]` | killedMsg |
| `+0x02f0` | `char[16]` | diedMsg |

**Methods (6):** `CraftClass`, `~CraftClass`, `Build`, ``scalar_deleting_destructor'`, `CraftClass`, `BuildClass`


---

### `HoverCraft`  — 704 bytes
_base (inferred): `Craft` · 173 fields · 24 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 616 bytes)* | |
| `+0x0268` | `HoverInterface *` | hi |
| `+0x026c` | `float` | dustTimer |
| `+0x0270` | `float` | thrustRatio |
| `+0x0274` | `float` | throttle |
| `+0x0278` | `float` | airBorne |
| `+0x027c` | `float` | lastThrot |
| `+0x0280` | `_gas_object *` | soundThrust |
| `+0x0284` | `_gas_object *` | soundTurbo |
| `+0x0288` | `float` | lastFly |
| `+0x028c` | `_gas_object *` | soundFly |
| `+0x0290` | `VECTOR_3D` | omegaEye |
| `+0x029c` | `float` | last_strafe |
| `+0x02a0` | `float` | last_steer |
| `+0x02a4` | `float` | last_pitch |
| `+0x02a8` | `float` | last_braccel |
| `+0x02ac` | `float` | last_reverse |
| `+0x02b0` | `long` | last_xa_brake |
| `+0x02b4` | `long` | last_e_brake |
| `+0x02b8` | `long` | last_start_engine |

**Methods (24):** `GetThrottle`, `GetAirborne`, `~HoverCraft`, `Load`, `Save`, `InitSound`, `CleanupSound`, `UpdateSound`, `MaxTurningSpeed`, `UnPackTempState`, `PackTempState`, `HoverCraft`, ``scalar_deleting_destructor'`, `SetAsUser`, `SetAsNotUser`, `UpdateGimbals`, `UpdateWeaponAim`, `UpdateEyepoint`, `UpdateModeList`, `Simulate`, `PostSimulate`, `ControlSpeed`, `ControlForward`, `GetRank`


---

### `HoverCraftClass`  — 952 bytes
_base (inferred): `CraftClass` / `ZIX_CD_TYPE` · 219 fields · 6 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 768 bytes)* | |
| `+0x0300` | `float` | velocForward |
| `+0x0304` | `float` | velocReverse |
| `+0x0308` | `float` | velocStrafe |
| `+0x030c` | `float` | accelThrust |
| `+0x0310` | `float` | accelBrake |
| `+0x0314` | `float` | omegaSpin |
| `+0x0318` | `float` | omegaTurn |
| `+0x031c` | `float` | alphaSteer |
| `+0x0320` | `float` | accelJump |
| `+0x0324` | `float` | setAltitude |
| `+0x0328` | `float` | accelDragStop |
| `+0x032c` | `float` | accelDragFull |
| `+0x0330` | `float` | alphaTrack |
| `+0x0334` | `float` | alphaDamp |
| `+0x0338` | `float` | pitchPitch |
| `+0x033c` | `float` | pitchThrust |
| `+0x0340` | `float` | rollStrafe |
| `+0x0344` | `float` | rollSteer |
| `+0x0348` | `float[2]` | rollStrafRotator |
| `+0x0350` | `float[2]` | rollSteerFin |
| `+0x0358` | `float[2]` | pitchThrotNacelle |
| `+0x0360` | `float[2]` | pitchSteerNacelle |
| `+0x0368` | `char[16]` | soundThrust |
| `+0x0378` | `char[16]` | soundTurbo |
| `+0x0388` | `char[16]` | soundFly |
| `+0x0398` | `char[16]` | soundDeploy |
| `+0x03a8` | `char[16]` | soundUndeploy |

**Methods (6):** `HoverCraftClass`, `~HoverCraftClass`, `Build`, ``scalar_deleting_destructor'`, `HoverCraftClass`, `BuildClass`


---

### `Walker`  — 664 bytes
_base (inferred): `Craft` · 165 fields · 13 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 616 bytes)* | |
| `+0x0268` | `long` | curAnim |
| `+0x026c` | `int` | animHandle |
| `+0x0270` | `bool` | cycleState |
| `+0x0274` | `float` | last_strafe |
| `+0x0278` | `float` | last_steer |
| `+0x027c` | `float` | last_pitch |
| `+0x0280` | `float` | last_braccel |
| `+0x0284` | `float` | last_reverse |
| `+0x0288` | `long` | last_xa_brake |
| `+0x028c` | `long` | last_e_brake |
| `+0x0290` | `long` | last_start_engine |

**Methods (13):** `Walker`, `IsSnipable`, `~Walker`, `Load`, `Save`, `UnPackTempState`, `PackTempState`, ``scalar_deleting_destructor'`, `Simulate`, `RegCollision`, `UpdateModeList`, `UpdateWeaponAim`, `GetRank`


---

### `Ordnance`  — 216 bytes
_17 fields · 19 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 8 bytes)* | |
| `+0x0008` | `_Iterator<1>` | me |
| `+0x0010` | `OrdnanceClass *` | ordnanceClass |
| `+0x0014` | `float` | dt |
| `+0x0018` | `_OBJ76 *` | obj |
| `+0x001c` | `EULER` | euler |
| `+0x0064` | `DAMAGE` | damage |
| `+0x0074` | `_gas_object *` | go |
| `+0x0078` | `float` | lifeTimer |
| `+0x007c` | `ushort` | source |
| `+0x007e` | `ushort` | ordid |
| `+0x0080` | `int` | bSend |
| `+0x0088` | `MAT_3D` | initMat |
| `+0x00c8` | `float` | initTime |
| `+0x00cc` | `_OBJ76 *` | owner |
| `+0x00d0` | `int` | ownerHandle |

**Methods (19):** `GetEuler`, `Control`, `Submit`, `GetFromObj`, `Expired`, `WasLocalHit`, `GetOwner`, `GetDamage`, `Remove`, `Pack`, `UnPack`, `OrientToVelocity`, `Ordnance`, `Simulate`, `Hit`, `Cleanup`, `~Ordnance`, `Init`, ``scalar_deleting_destructor'`


---

### `OrdnanceClass`  — 112 bytes
_20 fields · 10 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 8 bytes)* | |
| `+0x0008` | `OrdnanceClass *` | proto |
| `+0x000c` | `ulong` | sig |
| `+0x0010` | `char *` | label |
| `+0x0018` | `long64` | cfg |
| `+0x0020` | `char[16]` | odf |
| `+0x0030` | `_OBJ76 *` | ord |
| `+0x0034` | `tagENTITY *` | ent |
| `+0x0038` | `_OBJ76 *` | freeOrd |
| `+0x003c` | `ExplosionClass *` | xplGround |
| `+0x0040` | `ExplosionClass *` | xplVehicle |
| `+0x0044` | `ExplosionClass *` | xplBuilding |
| `+0x0048` | `long` | ammoCost |
| `+0x004c` | `float` | lifeSpan |
| `+0x0050` | `float` | shotSpeed |
| `+0x0054` | `float` | damageValue |
| `+0x0058` | `ushort` | damageTypes |
| `+0x005a` | `bool` | notifyRemote |
| `+0x005b` | `char[16]` | shotSound |

**Methods (10):** `~OrdnanceClass`, `Build`, `Build`, ``scalar_deleting_destructor'`, `GetProtoList`, `Find`, `Clean`, `OrdnanceClass`, `OrdnanceClass`, `BuildClass`


---

### `Weapon`  — 168 bytes
_11 fields · 19 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 8 bytes)* | |
| `+0x0008` | `WeaponClass *` | weaponClass |
| `+0x000c` | `OrdnanceClass *` | ordnanceClass |
| `+0x0010` | `_OBJ76 *` | obj |
| `+0x0014` | `_OBJ76 *` | hard |
| `+0x0018` | `_OBJ76 *` | owner |
| `+0x0020` | `MAT_3D` | M |
| `+0x0060` | `MAT_3D` | I |
| `+0x00a0` | `int` | wpnReticle |
| `+0x00a4` | `float` | fLastTriggered |

**Methods (19):** `Select`, `Deselect`, `GetEffect`, `GetEffect`, `ReadyToFire`, `EnoughAmmo`, `GetFromObj`, `Remove`, `Init`, `Control`, `GetLeadPosition`, `PermissionToFire`, `Weapon`, `Trigger`, `UnTrigger`, `IsTriggered`, `Simulate`, `~Weapon`, ``scalar_deleting_destructor'`


---

### `WeaponClass`  — 120 bytes
_15 fields · 11 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 8 bytes)* | |
| `+0x0008` | `WeaponClass *` | proto |
| `+0x000c` | `ulong` | sig |
| `+0x0010` | `char *` | label |
| `+0x0018` | `long64` | cfg |
| `+0x0020` | `char[16]` | odf |
| `+0x0030` | `OrdnanceClass *` | ordnanceClass |
| `+0x0034` | `int` | wpnNameIndex |
| `+0x0038` | `char[32]` | wpnName |
| `+0x0058` | `char[16]` | fireSound |
| `+0x0068` | `int` | wpnReticle |
| `+0x006c` | `int` | wpnLadder |
| `+0x0070` | `long` | wpnPriority |
| `+0x0074` | `OBJECT_CLASS_T` | wpnCategory |

**Methods (11):** `Find`, `~WeaponClass`, `Build`, `Build`, ``scalar_deleting_destructor'`, `GetProtoList`, `Find`, `Clean`, `WeaponClass`, `WeaponClass`, `BuildClass`


---

### `Building`  — 560 bytes
_140 fields · 20 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 544 bytes)* | |
| `+0x0220` | `_OBJ76 *` | root |
| `+0x0224` | `float` | fLastSentHealthRatio |
| `+0x0228` | `_gas_object *` | soundAmbient |
| `+0x022c` | `bool` | tempBuilding |

**Methods (20):** `Getroot`, `~Building`, `Init`, `Cleanup`, `Save`, `PackTempState`, `PackPermState`, `UnPackTempState`, `UnPackPermState`, `GetRank`, `PermStateChanged`, `ExpireRemoteObject`, `Building`, ``scalar_deleting_destructor'`, `Load`, `Init`, `RegCollision`, `DamageAlloc`, `Explode`, `Simulate`


---

### `BuildingClass`  — 352 bytes
_85 fields · 7 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 336 bytes)* | |
| `+0x0150` | `char[16]` | soundAmbient |

**Methods (7):** `~BuildingClass`, `BuildingClass`, ``scalar_deleting_destructor'`, `BuildingClass`, `Build`, `BuildingClass`, `BuildClass`


---

### `AnimBuilding`  — 568 bytes
_141 fields · 4 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 560 bytes)* | |
| `+0x0230` | `int` | animHandle |

**Methods (4):** `AnimBuilding`, `~AnimBuilding`, `Simulate`, ``scalar_deleting_destructor'`


---

### `AmmoPowerup`  — 552 bytes
_552 fields · 4 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 552 bytes)* | |

**Methods (4):** `AmmoPowerup`, `~AmmoPowerup`, ``scalar_deleting_destructor'`, `GivePower`


---

### `HealthPowerup`  — 552 bytes
_552 fields · 4 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 552 bytes)* | |

**Methods (4):** `HealthPowerup`, `~HealthPowerup`, ``scalar_deleting_destructor'`, `GivePower`


---

### `FlareMine`  — 576 bytes
_144 fields · 4 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 568 bytes)* | |
| `+0x0238` | `_OBJ76 *` | owner |
| `+0x023c` | `float` | shotTimer |

**Methods (4):** `FlareMine`, `~FlareMine`, `Simulate`, ``scalar_deleting_destructor'`


---

### `AIController`  — 1 bytes
_1 fields · 0 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 1 bytes)* | |

---

### `AiMission`  — 64 bytes
_8 fields · 35 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 8 bytes)* | |
| `+0x0008` | `list<AiProcess_*,std::allocator<AiProcess_*>_>` | processes |
| `+0x0024` | `bool` | done |
| `+0x0028` | `float` | shutdownTime |
| `+0x002c` | `bool` | failed |
| `+0x002d` | `char[14]` | resultName |
| `+0x003c` | `AiMissionClass *` | missionClass |

**Methods (35):** `Done`, `Fail`, `Succeed`, `GetRtimeClass`, `GetCurrent`, `CreateObject`, `AddObject`, `DeleteObject`, `CreatePlayer`, `AddPlayer`, `DeletePlayer`, `Start`, `LoadMission`, `PostLoadMission`, `SaveMission`, `Respawn`, `EjectCraftCreate`, `Command`, `End`, `PostLoad`, `Save`, `Create`, `AddProcess`, `RemoveProcess`, `Load`, `Register`, `Create`, `AiMission`, `Init`, `SetMostRecentKilled`, `AiMission`, `~AiMission`, `Update`, `CreateObject`, ``scalar_deleting_destructor'`


---

### `AiMissionClass`  — 8 bytes
_2 fields · 2 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 4 bytes)* | |
| `+0x0004` | `char *` | name |

**Methods (2):** `Matches`, `AiMissionClass`


---

### `Team`  — 384 bytes
_7 fields · 24 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | `GameObject *[90]` | teamSlot |
| `+0x0168` | `long` | curScrap |
| `+0x016c` | `long` | maxScrap |
| `+0x0170` | `long` | curPilot |
| `+0x0174` | `long` | maxPilot |
| `+0x0178` | `ulong` | dwAllies |
| `+0x017c` | `int` | teamNumber |

**Methods (24):** `Cleanup`, `GetTeam`, `PostLoadAll`, `SetSlot`, `GetSlot`, `FirstEmptySlot`, `FirstFilledSlot`, `GetScrap`, `SetScrap`, `GetMaxScrap`, `GetPilot`, `GetMaxPilot`, `Ally`, `UnAlly`, `FriendP`, `EnemyP`, `GetAllies`, `Init`, `LoadAll`, `SaveAll`, `AddScrap`, `AddMaxScrap`, `AddPilot`, `AddMaxPilot`


---

### `GamePlayerList`  — 60 bytes
_60 fields · 5 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 60 bytes)* | |

**Methods (5):** `IsHost`, `GamePlayerList`, `FormatItem`, `~GamePlayerList`, ``scalar_deleting_destructor'`


---

### `DistributedObject`  — 128 bytes
_18 fields · 55 methods_

| Offset | Type | Field |
|---|---|---|
| `+0x0000` | *(unmapped 8 bytes)* | |
| `+0x0008` | `bool` | create_new_craft |
| `+0x0010` | `MAT_3D` | true_transform |
| `+0x0050` | `float` | iter |
| `+0x0054` | `float` | last_count |
| `+0x0058` | `float` | count |
| `+0x005c` | `float` | net_dt |
| `+0x0060` | `bool` | net_user |
| `+0x0061` | `bool` | recycle |
| `+0x0062` | `ushort` | activnet_id |
| `+0x0064` | `ulong` | dwLocalID |
| `+0x0068` | `uchar` | object_type |
| `+0x006c` | `float` | last_send_time |
| `+0x0070` | `bool` | dirty |
| `+0x0074` | `float` | last_health_ratio |
| `+0x0078` | `float` | flast_received_time |
| `+0x007c` | `ulong` | dwlast_received_time |

**Methods (55):** `GetLastSendTime`, `GetRecycle`, `SetRecycle`, `Getroot`, `SetTeam`, `GetHealth`, `AddHealth`, `GetEntity`, `GetOBJ76`, `DamageAlloc`, `SendCommand`, `TempStateReceive`, `PermStateRead`, `SetPlayerID`, `ReceiveCommand`, `RemoveOldObjects`, `PackTempState`, `UnPackTempState`, `PackPermState`, `UnPackPermState`, `SetDirty`, `PermStateChanged`, `ExpireRemoteObject`, `GetPlayerID`, `GetPlayerName`, `SetGlobalPlayerID`, `IsRemote`, `IsLocal`, `GetID`, `RecordDeath`, `RecordDeath`, `SendBuf`, `GetRank`, `SetDP`, `BroadCastGrabObject`, `UpdatePermState`, `GetGameObject`, `ReceiveDamage`, `~DistributedObject`, `TempStateSendAll`, `SetRemote`, `Create`, `GlobalSetLocal`, `GlobalSetRemote`, `DistributedObject`, `Cleanup`, `Destroy`, `SetLocal`, `ReceiveTempState`, `ReadPermState`, `AllBuildingsSetLocal`, `Explode`, `RemoteDelete`, `TakeOwnershipFromPlayer`, `Remove`


---
