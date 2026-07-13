/*
 * Entry: 0047032d
 * Name: ScoutProcess::ChooseAttackTarget
 * Namespace: ScoutProcess
 * Signature: GameObject * ChooseAttackTarget(ScoutProcess * this, float * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall ScoutProcess::ChooseAttackTarget(ScoutProcess *this,float *param_1)

{
  GameObject *pGVar1;
  
  pGVar1 = GetClosestEnemyOrMineWithin(*(GameObject **)&this->field_0x2c,param_1);
  return pGVar1;
}
