/*
 * Entry: 0046cf87
 * Name: UnitTask::UpdateSpecial
 * Namespace: UnitTask
 * Signature: void UpdateSpecial(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::UpdateSpecial(UnitTask *this)

{
  float fVar1;
  ulong uVar2;
  char cVar3;
  int iVar4;
  float fVar5;
  
  if (this->special != (Weapon *)0x0) {
    uVar2 = this->special->weaponClass->sig;
    if (uVar2 == 0x49524546) {
      fVar1 = (float)this->me->_padding_;
      fVar5 = Get_Time();
      if (10.0 <= fVar5 - fVar1) {
        return;
      }
      if ((float)this->me->_padding_ != (float)this->me->_padding_) {
        iVar4 = this->me->_padding_;
        if (iVar4 == 0) {
          return;
        }
        iVar4 = *(int *)(iVar4 + 0xc);
        if ((iVar4 != 0x494d474d) && (iVar4 != 0x54484d4d)) {
          return;
        }
      }
    }
    else {
      if (uVar2 != 0x52444d50) {
        return;
      }
      if ((this->avoidObj == (GameObject *)0x0) ||
         (iVar4 = (**(code **)this->avoidObj->_padding_)(), *(int *)(iVar4 + 0x20) != 0x544f5250)) {
        fVar1 = (float)this->me->_padding_;
        fVar5 = Get_Time();
        if (10.0 <= fVar5 - fVar1) {
          return;
        }
        if ((float)this->me->_padding_ != (float)this->me->_padding_) {
          return;
        }
      }
    }
    cVar3 = (**(code **)(this->special->_padding_ + 0x10))();
    if (cVar3 == '\0') {
      (**(code **)(this->special->_padding_ + 8))();
    }
  }
  return;
}
