/*
 * Entry: 004705ea
 * Name: WingmanProcess::AttackWaitVsAttack
 * Namespace: WingmanProcess
 * Signature: bool AttackWaitVsAttack(WingmanProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall WingmanProcess::AttackWaitVsAttack(WingmanProcess *this)

{
  float fVar1;
  float *pfVar2;
  float *pfVar3;
  float fVar4;
  
  pfVar2 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x60 + 0x20) + 0xc))();
  pfVar3 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x2c + 0x20) + 0xc))();
  if (((pfVar3[2] - pfVar2[2]) * (pfVar3[2] - pfVar2[2]) + (*pfVar3 - *pfVar2) * (*pfVar3 - *pfVar2)
       < *(float *)&this->field_0x64) &&
     (fVar1 = *(float *)(*(int *)&this->field_0x2c + 0x1e0), fVar4 = Get_Time(),
     fVar4 - fVar1 < 15.0)) {
    return true;
  }
  return false;
}
