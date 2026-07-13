/*
 * Entry: 0046d785
 * Name: UnitTask::Init
 * Namespace: UnitTask
 * Signature: void Init(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::Init(UnitTask *this)

{
  Craft *pCVar1;
  ulong uVar2;
  int iVar3;
  UnitTask *local_c;
  UnitTask *local_8;
  
  pCVar1 = this->me;
  this->weaponCheck = 0;
  if ((pCVar1 == (Craft *)0x0) || (pCVar1->_padding_ == 0)) {
    this->specialSlot = -1;
    local_8 = (UnitTask *)0x0;
    this->weapon = (Weapon *)0x0;
    this->special = (Weapon *)0x0;
    this->time = 0.5;
    local_c = (UnitTask *)0x41200000;
  }
  else {
    local_c = this;
    local_8 = this;
    uVar2 = WeaponCheck(pCVar1);
    this->weaponCheck = uVar2;
    CalcRange(pCVar1,(float *)&local_8,(float *)&local_c,&this->time,&this->weapon);
    iVar3 = FindSpecial(this,&this->special);
    this->specialSlot = iVar3;
  }
  this->shotSpeed = (float)local_c / this->time;
  this->shotSpeedInv = this->time / (float)local_c;
  this->closeSq = (float)local_8 * (float)local_8;
  this->rangeSq = (float)local_c * (float)local_c;
  this->closeAdjust = 1.0;
  return;
}
