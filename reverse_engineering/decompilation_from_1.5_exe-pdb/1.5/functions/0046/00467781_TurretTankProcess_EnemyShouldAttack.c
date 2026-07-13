/*
 * Entry: 00467781
 * Name: TurretTankProcess::EnemyShouldAttack
 * Namespace: TurretTankProcess
 * Signature: bool EnemyShouldAttack(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TurretTankProcess::EnemyShouldAttack(TurretTankProcess *this)

{
  float fVar1;
  char cVar2;
  bool bVar3;
  float *pfVar4;
  float *pfVar5;
  float fVar6;
  
  fVar1 = *(float *)(this->_padding_ + 0x1e0);
  fVar6 = Get_Time();
  if (fVar6 - fVar1 < 15.0) {
LAB_004677f6:
    bVar3 = true;
  }
  else {
    cVar2 = (**(code **)(*(int *)this->_padding_ + 100))();
    if (cVar2 != '\0') {
      pfVar4 = (float *)(**(code **)(this->who2->_padding_ + 0xc))();
      pfVar5 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      if ((pfVar5[2] - pfVar4[2]) * (pfVar5[2] - pfVar4[2]) +
          (*pfVar5 - *pfVar4) * (*pfVar5 - *pfVar4) < this->rangeSquared) goto LAB_004677f6;
    }
    bVar3 = FriendShouldAttack(this);
  }
  return bVar3;
}
