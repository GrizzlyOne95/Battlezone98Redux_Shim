/*
 * Entry: 0046772f
 * Name: TurretTankProcess::FriendShouldAttack
 * Namespace: TurretTankProcess
 * Signature: bool FriendShouldAttack(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TurretTankProcess::FriendShouldAttack(TurretTankProcess *this)

{
  char cVar1;
  float *pfVar2;
  float *pfVar3;
  
  cVar1 = (**(code **)(*(int *)this->_padding_ + 100))();
  if (cVar1 == '\0') {
    return false;
  }
  pfVar2 = (float *)(**(code **)(this->who2->_padding_ + 0xc))();
  pfVar3 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
  if ((pfVar3[2] - pfVar2[2]) * (pfVar3[2] - pfVar2[2]) + (*pfVar3 - *pfVar2) * (*pfVar3 - *pfVar2)
      < this->rangeSquared) {
    return true;
  }
  return false;
}
