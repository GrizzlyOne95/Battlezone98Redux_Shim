/*
 * Entry: 0046ce31
 * Name: UnitTask::FindSpecial
 * Namespace: UnitTask
 * Signature: int FindSpecial(UnitTask * this, Weapon * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall UnitTask::FindSpecial(UnitTask *this,Weapon **param_1)

{
  Carrier *this_00;
  ulong uVar1;
  float fVar2;
  char cVar3;
  Weapon *pWVar4;
  int iVar5;
  
  this_00 = (Carrier *)this->me->_padding_;
  if (this_00 != (Carrier *)0x0) {
    iVar5 = 0;
    do {
      pWVar4 = Carrier::GetWeapon(this_00,iVar5);
      if (pWVar4 != (Weapon *)0x0) {
        uVar1 = pWVar4->weaponClass->sig;
        if ((uVar1 == 0x49524546) || (uVar1 == 0x52444d50)) {
          fVar2 = (float)pWVar4->weaponClass[1]._padding_;
          if (fVar2 < 0.0 == (fVar2 == 0.0)) {
            *param_1 = pWVar4;
            return iVar5;
          }
          cVar3 = (**(code **)(pWVar4->_padding_ + 0x10))();
          if (cVar3 == '\0') {
            (**(code **)(pWVar4->_padding_ + 8))();
          }
        }
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < 5);
  }
  *param_1 = (Weapon *)0x0;
  return -1;
}
