/*
 * Entry: 0046d84d
 * Name: UnitTask::Execute
 * Namespace: UnitTask
 * Signature: void Execute(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::Execute(UnitTask *this)

{
  float *pfVar1;
  Craft *pCVar2;
  float fVar3;
  long lVar4;
  int iVar5;
  ulong uVar6;
  SPHERE *pSVar7;
  GameObject *this_00;
  UnitTask *local_c;
  UnitTask *local_8;
  
  if (this->curState == 0xd) {
    return;
  }
  local_c = this;
  local_8 = this;
  iVar5 = Net_IsNetGame();
  lVar4 = GameObject::userTeamNumber;
  if ((iVar5 == 0) && (iVar5 = (**(code **)(this->me->_padding_ + 4))(), iVar5 != lVar4)) {
    fVar3 = (float)difficultySetting;
  }
  else {
    fVar3 = 4.0;
  }
  pCVar2 = this->me;
  this->skill = fVar3;
  uVar6 = WeaponCheck(pCVar2);
  if (uVar6 != this->weaponCheck) {
    this->weaponCheck = uVar6;
    pfVar1 = &this->time;
    CalcRange(pCVar2,(float *)&local_8,(float *)&local_c,pfVar1,&this->weapon);
    pSVar7 = GameObject::GetSphere((GameObject *)this->me);
    local_8 = (UnitTask *)(pSVar7->radius + (float)local_8);
    this_00 = GameObjectHandle::GetObj(this->himHandle);
    if (this_00 != (GameObject *)0x0) {
      pSVar7 = GameObject::GetSphere(this_00);
      local_8 = (UnitTask *)(pSVar7->radius + (float)local_8);
    }
    this->shotSpeed = (float)local_c / *pfVar1;
    this->shotSpeedInv = *pfVar1 / (float)local_c;
    this->closeSq = (float)local_8 * (float)local_8;
    this->rangeSq = (float)local_c * (float)local_c;
    this->closeAdjust = 1.0;
    iVar5 = FindSpecial(this,&this->special);
    this->specialSlot = iVar5;
  }
  if (this->nextState != -1) {
    (**(code **)(this->_padding_ + 0x28))();
    iVar5 = this->nextState;
    this->nextState = -1;
    this->curState = iVar5;
    (**(code **)(this->_padding_ + 0x24))();
    if (this->nextState != -1) {
      return;
    }
    if (this->curState == 0xd) {
      return;
    }
  }
  (**(code **)(this->_padding_ + 0x2c))();
  return;
}
