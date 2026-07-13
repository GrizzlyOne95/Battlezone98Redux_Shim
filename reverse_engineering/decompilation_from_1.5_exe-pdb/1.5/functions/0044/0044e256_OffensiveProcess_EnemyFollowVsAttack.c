/*
 * Entry: 0044e256
 * Name: OffensiveProcess::EnemyFollowVsAttack
 * Namespace: OffensiveProcess
 * Signature: bool EnemyFollowVsAttack(OffensiveProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall OffensiveProcess::EnemyFollowVsAttack(OffensiveProcess *this)

{
  float *pfVar1;
  float *pfVar2;
  
  if (this->who1 != (GameObject *)0x0) {
    pfVar1 = (float *)(**(code **)(this->who1->_padding_ + 0xc))();
    pfVar2 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
    if ((pfVar2[2] - pfVar1[2]) * (pfVar2[2] - pfVar1[2]) +
        (*pfVar2 - *pfVar1) * (*pfVar2 - *pfVar1) < this->followRange) {
      pfVar1 = (float *)(**(code **)(this->who2->_padding_ + 0xc))();
      pfVar2 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      if ((pfVar2[2] - pfVar1[2]) * (pfVar2[2] - pfVar1[2]) +
          (*pfVar2 - *pfVar1) * (*pfVar2 - *pfVar1) < this->engageRange) {
        return true;
      }
    }
  }
  return false;
}
