/*
 * Entry: 0044e25b
 * Name: OffensiveProcess::AttackVsAttack
 * Namespace: OffensiveProcess
 * Signature: bool AttackVsAttack(OffensiveProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall OffensiveProcess::AttackVsAttack(OffensiveProcess *this)

{
  float fVar1;
  GameObject *pGVar2;
  float *pfVar3;
  float *pfVar4;
  float fVar5;
  
  pGVar2 = this->who1;
  if ((pGVar2 != (GameObject *)0x0) && (this->who2 != pGVar2)) {
    pfVar3 = (float *)(**(code **)(pGVar2->_padding_ + 0xc))();
    pfVar4 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
    if ((this->weaponRange <
         (pfVar4[2] - pfVar3[2]) * (pfVar4[2] - pfVar3[2]) +
         (*pfVar4 - *pfVar3) * (*pfVar4 - *pfVar3)) &&
       (fVar1 = *(float *)(this->_padding_ + 0x1e0), fVar5 = Get_Time(),
       fVar5 - fVar1 < this->madTime)) {
      return true;
    }
  }
  return false;
}
