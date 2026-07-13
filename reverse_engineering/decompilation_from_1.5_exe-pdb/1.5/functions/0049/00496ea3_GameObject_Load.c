/*
 * Entry: 00496ea3
 * Name: GameObject::Load
 * Namespace: GameObject
 * Signature: bool Load(GameObject * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool __thiscall GameObject::Load(GameObject *this,_iobuf *param_1)

{
  Carrier *pCVar1;
  float fVar2;
  bool bVar3;
  GameObjectClass *pGVar4;
  WeaponClass *this_00;
  Weapon *pWVar5;
  int iVar6;
  bool local_5c [4];
  long local_58;
  int local_54;
  long local_50;
  int local_4c;
  bool local_45;
  _iobuf *local_44;
  int local_40;
  int local_3c;
  ulong local_38;
  ulong local_34;
  float local_30;
  bool local_2b;
  bool local_2a;
  bool local_29;
  char local_28 [32];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_44 = param_1;
  bVar3 = ::in(param_1,&this->illumination,4);
  if ((((bVar3) && (bVar3 = ::in(param_1,&this->pos,0xc), bVar3)) &&
      (bVar3 = ::in(param_1,&this->euler,0x48), bVar3)) &&
     (bVar3 = ::in(param_1,&this->seqNo,4), bVar3)) {
    bVar3 = true;
  }
  else {
    bVar3 = false;
  }
  if (missionSave != false) {
    (this->euler).omega.x = 0.0;
    (this->euler).omega.y = 0.0;
    (this->euler).omega.z = 0.0;
  }
  if (version < 0x3fa) {
    if (((bVar3) && (bVar3 = ::in(param_1,(long *)&local_38,4), bVar3)) &&
       ((bVar3 = ::in(param_1,(long *)&local_34,4), bVar3 &&
        ((bVar3 = ::in(param_1,(int *)&local_30,4), bVar3 &&
         (bVar3 = ::in(param_1,&local_3c,4), bVar3)))))) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
  }
  if (0x406 < version) {
    if ((bVar3) && (bVar3 = ::in(param_1,local_28,0x20), bVar3)) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if (local_28[0] != '\0') {
      SetName(this,local_28);
    }
  }
  if ((((bVar3) && (bVar3 = ::in(param_1,local_5c,1), bVar3)) &&
      (bVar3 = ::in(param_1,&local_45,1), bVar3)) &&
     ((bVar3 = ::in(param_1,&this->isVisible,4), bVar3 &&
      (bVar3 = ::in(param_1,&this->seen,4), bVar3)))) {
    bVar3 = true;
  }
  else {
    bVar3 = false;
  }
  if (missionSave == false) {
LAB_0049705c:
    if (((bVar3 != false) && (bVar3 = ::in(param_1,&this->playerShot,4), bVar3)) &&
       ((bVar3 = ::in(param_1,&this->playerCollide,4), bVar3 &&
        (((bVar3 = ::in(param_1,&this->friendShot,4), bVar3 &&
          (bVar3 = ::in(param_1,&this->friendCollide,4), bVar3)) &&
         (bVar3 = ::in(param_1,&this->enemyShot,4), bVar3)))))) {
      bVar3 = ::in(param_1,&this->groundCollide,4);
LAB_004970e6:
      if (bVar3 != false) goto LAB_004970ea;
    }
LAB_00497127:
    local_29 = false;
  }
  else {
    this->isVisible = 0;
    this->seen = 0;
    if (missionSave == false) goto LAB_0049705c;
    if (0x408 < version) goto LAB_004970e6;
    if (((bVar3 == false) || (bVar3 = ::in(param_1,&local_30,4), !bVar3)) ||
       ((((bVar3 = ::in(param_1,&local_30,4), !bVar3 ||
          ((bVar3 = ::in(param_1,&local_30,4), !bVar3 || (bVar3 = ::in(param_1,&local_30,4), !bVar3)
           ))) || (bVar3 = ::in(param_1,&local_30,4), !bVar3)) ||
        (bVar3 = ::in(param_1,&local_30,4), !bVar3)))) {
      bVar3 = false;
      goto LAB_004970e6;
    }
LAB_004970ea:
    bVar3 = ::in(param_1,&this->healthRatio,4);
    if ((!bVar3) || (bVar3 = ::in(param_1,&local_4c,4), !bVar3)) goto LAB_00497127;
    bVar3 = ::in(param_1,&local_54,4);
    local_29 = true;
    if (!bVar3) goto LAB_00497127;
  }
  this->maxHealth = (float)local_54;
  SetCurHealth(this,(float)local_4c);
  if (this->maxHealth <= 0.0) {
    fVar2 = 1.0;
  }
  else {
    fVar2 = this->curHealth / this->maxHealth;
  }
  this->healthRatio = fVar2;
  SetObjective(this,local_5c[0]);
  if (missionSave != false) {
    local_30 = (float)AdjustedMaxHealth(*(ushort *)((int)&this->obj->flags + 2) & 0xf,this->objClass
                                       );
    this->maxHealth = (float)(int)local_30;
    SetCurHealth(this,(float)(int)local_30 * this->healthRatio);
  }
  if (version < 0x3f7) {
    local_34 = 0;
    local_38 = 0;
    local_30 = 0.0;
    if ((((local_29 == false) || (bVar3 = ::in(param_1,&local_30,4), !bVar3)) ||
        (bVar3 = ::in(param_1,(long *)&local_34,4), !bVar3)) ||
       (bVar3 = ::in(param_1,(long *)&local_38,4), !bVar3)) {
      local_29 = false;
      goto LAB_0049729d;
    }
LAB_004972a3:
    bVar3 = ::in(param_1,&this->ammoRatio,4);
    if (((!bVar3) || (bVar3 = ::in(param_1,&local_58,4), !bVar3)) ||
       (bVar3 = ::in(param_1,&local_50,4), !bVar3)) goto LAB_004972e0;
    bVar3 = true;
  }
  else {
LAB_0049729d:
    if (local_29 != false) goto LAB_004972a3;
LAB_004972e0:
    bVar3 = false;
  }
  SetCurAmmo(this,local_58);
  SetMaxAmmo(this,local_50);
  if (missionSave == false) {
    if (((bVar3) && (bVar3 = AiCmdInfo::in(&this->curCmd,param_1), bVar3)) &&
       (bVar3 = AiCmdInfo::in(&this->nextCmd,param_1), bVar3)) {
      bVar3 = in_ptr(param_1,&this->aiProcess,4,"GameObject:aiProcess",this);
LAB_0049737a:
      local_29 = true;
      if (bVar3 != false) goto LAB_00497386;
    }
LAB_00497382:
    local_29 = false;
  }
  else {
    if (bVar3) {
      bVar3 = AiCmdInfo::in(&this->nextCmd,param_1);
      local_29 = true;
      if (!bVar3) goto LAB_00497317;
    }
    else {
LAB_00497317:
      local_29 = false;
    }
    if (0x3fd < version) {
      if (local_29 != false) {
        bVar3 = ::in(param_1,&local_2b,1);
        goto LAB_0049737a;
      }
      goto LAB_00497382;
    }
  }
LAB_00497386:
  if ((0x3ef < version) && (local_29 != false)) {
    local_29 = ::in(param_1,&this->isCargo,1);
  }
  if (0x3f8 < version) {
    if ((local_29 == false) || (bVar3 = ::in(param_1,&this->independence,4), !bVar3)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    if (version < 0x406) {
      if (bVar3) {
        bVar3 = ::in(param_1,&local_2a,1);
        local_29 = true;
        if (!bVar3) goto LAB_00497406;
      }
      else {
LAB_00497406:
        local_29 = false;
      }
      if (local_2a == false) {
        this->curPilot = (GameObjectClass *)0x0;
        goto LAB_0049746f;
      }
      if (this == userObject) {
        pGVar4 = this->objClass->userClass;
      }
      else {
        pGVar4 = this->objClass->pilotClass;
      }
    }
    else {
      if (bVar3) {
        bVar3 = ::in(param_1,(long64 *)&local_40,8);
        local_29 = true;
        if (!bVar3) goto LAB_00497452;
      }
      else {
LAB_00497452:
        local_29 = false;
      }
      pGVar4 = GameObjectClass::Find(CONCAT44(local_3c,local_40));
      local_2a = pGVar4 != (GameObjectClass *)0x0;
    }
    this->curPilot = pGVar4;
  }
LAB_0049746f:
  if (0x407 < version) {
    if (local_29 != false) {
      bVar3 = ::in(param_1,&this->perceivedTeam,4);
      local_29 = true;
      if (bVar3) goto LAB_0049749f;
    }
    local_29 = false;
  }
LAB_0049749f:
  if (version < 0x409) {
LAB_004975a7:
    if (missionSave == false) goto LAB_004975df;
  }
  else if (missionSave == false) {
    iVar6 = 0;
    do {
      if (local_29 == false) {
LAB_004974dd:
        local_29 = false;
      }
      else {
        bVar3 = ::in(local_44,(long64 *)&local_40,8);
        local_29 = true;
        if (!bVar3) goto LAB_004974dd;
      }
      if (((local_40 != 0 || local_3c != 0) &&
          (this_00 = WeaponClass::Find(CONCAT44(local_3c,local_40)), this_00 != (WeaponClass *)0x0))
         && (this->carrier != (Carrier *)0x0)) {
        pWVar5 = Carrier::GetWeapon(this->carrier,iVar6);
        if (pWVar5 != (Weapon *)0x0) {
          if (this_00 != pWVar5->weaponClass) {
            Weapon::Remove(pWVar5);
            pWVar5 = (Weapon *)0x0;
          }
          if (pWVar5 != (Weapon *)0x0) goto LAB_00497546;
        }
        pWVar5 = WeaponClass::Build(this_00,this->obj,this->carrier->hardpoint[iVar6]);
        Carrier::SetWeapon(this->carrier,iVar6,pWVar5);
      }
LAB_00497546:
      iVar6 = iVar6 + 1;
    } while (iVar6 < 5);
    if ((local_29 == false) || (bVar3 = ::in(local_44,&local_38,4), !bVar3)) {
LAB_00497584:
      local_29 = false;
    }
    else {
      bVar3 = ::in(local_44,&local_34,4);
      local_29 = true;
      if (!bVar3) goto LAB_00497584;
    }
    pCVar1 = this->carrier;
    if (pCVar1 != (Carrier *)0x0) {
      pCVar1->enabled = pCVar1->existant & local_38;
      Carrier::SetSelected(this->carrier,local_34);
    }
    goto LAB_004975a7;
  }
  if (version < 0x3fe) {
    local_2b = local_2a;
  }
  else if (local_2b == false) {
    this->curPilot = (GameObjectClass *)0x0;
  }
  this->aiProcess = (AiProcess *)(uint)(local_2b != false);
LAB_004975df:
  AssignColor(this);
  return local_29;
}
