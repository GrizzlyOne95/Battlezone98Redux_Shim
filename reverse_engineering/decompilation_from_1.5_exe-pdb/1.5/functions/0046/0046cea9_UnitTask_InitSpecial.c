/*
 * Entry: 0046cea9
 * Name: UnitTask::InitSpecial
 * Namespace: UnitTask
 * Signature: void InitSpecial(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::InitSpecial(UnitTask *this)

{
  ulong uVar1;
  Carrier *pCVar2;
  char cVar3;
  GameObject *pGVar4;
  int iVar5;
  Weapon *pWVar6;
  
  if (this->special == (Weapon *)0x0) {
    return;
  }
  pGVar4 = GameObjectHandle::GetObj(this->himHandle);
  if (pGVar4 == (GameObject *)0x0) {
    return;
  }
  uVar1 = this->special->weaponClass->sig;
  if (uVar1 == 0x49524546) {
    if ((pGVar4->obj->flags & 0x30) == 0) {
      pCVar2 = pGVar4->carrier;
      if (pCVar2 == (Carrier *)0x0) {
        return;
      }
      iVar5 = 0;
      while ((pWVar6 = Carrier::GetWeapon(pCVar2,iVar5), pWVar6 == (Weapon *)0x0 ||
             ((uVar1 = pWVar6->weaponClass->sig, uVar1 != 0x494d474c && (uVar1 != 0x54484d4c))))) {
        iVar5 = iVar5 + 1;
        if (4 < iVar5) {
          return;
        }
      }
    }
  }
  else {
    if (uVar1 != 0x52444d50) {
      return;
    }
    if (((pGVar4->obj->flags & 0x30) == 0) &&
       (iVar5 = (**(code **)pGVar4->_padding_)(), *(int *)(iVar5 + 0x20) != 0x544f5250)) {
      pCVar2 = pGVar4->carrier;
      if (pCVar2 == (Carrier *)0x0) {
        return;
      }
      iVar5 = 0;
      while ((pWVar6 = Carrier::GetWeapon(pCVar2,iVar5), pWVar6 == (Weapon *)0x0 ||
             (pWVar6->weaponClass->sig != 0x5244524c))) {
        iVar5 = iVar5 + 1;
        if (4 < iVar5) {
          return;
        }
      }
    }
  }
  cVar3 = (**(code **)(this->special->_padding_ + 0x10))();
  if (cVar3 != '\0') {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0046cf84. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(this->special->_padding_ + 8))();
  return;
}
