/*
 * Entry: 00495dec
 * Name: GameObject::Save
 * Namespace: GameObject
 * Signature: bool Save(GameObject * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool __thiscall GameObject::Save(GameObject *this,_iobuf *param_1)

{
  GameObjectClass *pGVar1;
  Carrier *pCVar2;
  _iobuf *p_Var3;
  bool bVar4;
  Weapon *pWVar5;
  int iVar6;
  AiCmdInfo *this_00;
  char *pcVar7;
  uint local_58;
  long local_54;
  uint local_50;
  long local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  ulong local_38;
  ulong local_34;
  bool local_2d;
  _iobuf *local_2c;
  char local_28 [32];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_2c = param_1;
  if ((this->nextCmd).what != CMD_GO) {
    (this->nextCmd).where = (AiPath *)0x0;
  }
  pcVar7 = local_28;
  for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
    pcVar7[0] = '\0';
    pcVar7[1] = '\0';
    pcVar7[2] = '\0';
    pcVar7[3] = '\0';
    pcVar7 = pcVar7 + 4;
  }
  iVar6 = strncmp(this->name,this->objClass->unitName,0x20);
  if (iVar6 != 0) {
    strncpy(local_28,this->name,0x20);
  }
  bVar4 = ::out(param_1,&this->illumination,4,"illumination");
  if (((((bVar4) && (bVar4 = ::out(param_1,&this->pos,0xc,"pos"), bVar4)) &&
       (bVar4 = ::out(param_1,&this->euler,0x48,"euler"), bVar4)) &&
      (((bVar4 = ::out(param_1,&this->seqNo,4,"seqNo"), bVar4 &&
        (bVar4 = ::out(param_1,local_28,0x20,"name"), bVar4)) &&
       ((bVar4 = ::out(param_1,&this->isObjective,1,"isObjective"), bVar4 &&
        ((bVar4 = ::out(param_1,&this->isSelected,1,"isSelected"), bVar4 &&
         (bVar4 = ::out(param_1,&this->isVisible,4,"isVisible"), bVar4)))))))) &&
     (bVar4 = ::out(param_1,&this->seen,4,"seen"), bVar4)) {
    bVar4 = true;
  }
  else {
    bVar4 = false;
  }
  p_Var3 = local_2c;
  if (missionSave == false) {
    if ((((bVar4) && (bVar4 = ::out(local_2c,&this->playerShot,4,"playerShot"), bVar4)) &&
        (bVar4 = ::out(p_Var3,&this->playerCollide,4,"playerCollide"), bVar4)) &&
       (((bVar4 = ::out(p_Var3,&this->friendShot,4,"friendShot"), bVar4 &&
         (bVar4 = ::out(p_Var3,&this->friendCollide,4,"friendCollide"), bVar4)) &&
        ((bVar4 = ::out(p_Var3,&this->enemyShot,4,"enemyShot"), bVar4 &&
         (bVar4 = ::out(p_Var3,&this->groundCollide,4,"groundCollide"), bVar4)))))) {
      bVar4 = true;
    }
    else {
      bVar4 = false;
    }
  }
  _ftol2_sse();
  _ftol2_sse();
  local_50 = this->curAmmo ^ 0x33333333;
  local_58 = this->maxAmmo ^ 0x33333333;
  if (((bVar4) && (bVar4 = ::out(p_Var3,&this->healthRatio,4,"healthRatio"), bVar4)) &&
     ((bVar4 = ::out(p_Var3,&local_54,4,"curHealth"), bVar4 &&
      ((((bVar4 = ::out(p_Var3,&local_4c,4,"maxHealth"), bVar4 &&
         (bVar4 = ::out(p_Var3,&this->ammoRatio,4,"ammoRatio"), bVar4)) &&
        (bVar4 = ::out(p_Var3,(long *)&local_50,4,"curAmmo"), bVar4)) &&
       (bVar4 = ::out(p_Var3,(long *)&local_58,4,"maxAmmo"), bVar4)))))) {
    bVar4 = true;
  }
  else {
    bVar4 = false;
  }
  if (missionSave == false) {
    if (((bVar4) && (bVar4 = AiCmdInfo::out(&this->curCmd,p_Var3), bVar4)) &&
       (bVar4 = AiCmdInfo::out(&this->nextCmd,p_Var3), bVar4)) {
      bVar4 = out_ptr(p_Var3,&this->aiProcess,4,"undefptr");
      goto LAB_00496158;
    }
  }
  else {
    if ((this->nextCmd).what == CMD_NONE) {
      if (!bVar4) goto LAB_00496134;
      this_00 = &this->curCmd;
LAB_00496126:
      bVar4 = AiCmdInfo::out(this_00,p_Var3);
      if (!bVar4) goto LAB_00496134;
      bVar4 = true;
    }
    else {
      if (bVar4) {
        this_00 = &this->nextCmd;
        goto LAB_00496126;
      }
LAB_00496134:
      bVar4 = false;
    }
    local_2d = this->aiProcess != (AiProcess *)0x0;
    if (bVar4) {
      bVar4 = ::out(p_Var3,&local_2d,1,"aiProcess");
LAB_00496158:
      if (((bVar4 != false) && (bVar4 = ::out(p_Var3,&this->isCargo,1,"isCargo"), bVar4)) &&
         (bVar4 = ::out(p_Var3,&this->independence,4,"independence"), bVar4)) {
        bVar4 = true;
        goto LAB_00496161;
      }
    }
  }
  bVar4 = false;
LAB_00496161:
  pGVar1 = this->curPilot;
  if (pGVar1 == (GameObjectClass *)0x0) {
    local_40 = 0;
    local_3c = 0;
  }
  else {
    local_40 = (undefined4)pGVar1->cfg;
    local_3c = *(undefined4 *)((int)&pGVar1->cfg + 4);
  }
  if (((bVar4) && (bVar4 = ::out(p_Var3,(long64 *)&local_40,8,"curPilot"), bVar4)) &&
     (bVar4 = ::out(p_Var3,&this->perceivedTeam,4,"perceivedTeam"), bVar4)) {
    bVar4 = true;
  }
  else {
    bVar4 = false;
  }
  if (missionSave == false) {
    local_2c = (_iobuf *)0x0;
    do {
      local_48 = 0;
      local_44 = 0;
      if ((this->carrier != (Carrier *)0x0) &&
         (pWVar5 = Carrier::GetWeapon(this->carrier,(int)local_2c), pWVar5 != (Weapon *)0x0)) {
        local_48 = (undefined4)pWVar5->weaponClass->cfg;
        local_44 = *(undefined4 *)((int)&pWVar5->weaponClass->cfg + 4);
      }
      if ((bVar4 == false) || (bVar4 = ::out(p_Var3,(long64 *)&local_48,8,"wpnID"), !bVar4)) {
        bVar4 = false;
      }
      else {
        bVar4 = true;
      }
      local_2c = (_iobuf *)((int)local_2c + 1);
    } while ((int)local_2c < 5);
    pCVar2 = this->carrier;
    local_38 = 0;
    local_34 = 0;
    if (pCVar2 != (Carrier *)0x0) {
      local_38 = pCVar2->enabled;
      local_34 = pCVar2->selected;
    }
    if (((bVar4 == false) || (bVar4 = ::out(p_Var3,&local_38,4,"enabled"), !bVar4)) ||
       (bVar4 = ::out(p_Var3,&local_34,4,"selected"), !bVar4)) {
      bVar4 = false;
    }
    else {
      bVar4 = true;
    }
  }
  return bVar4;
}
