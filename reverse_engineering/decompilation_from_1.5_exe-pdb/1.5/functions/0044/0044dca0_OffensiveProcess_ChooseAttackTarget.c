/*
 * Entry: 0044dca0
 * Name: OffensiveProcess::ChooseAttackTarget
 * Namespace: OffensiveProcess
 * Signature: GameObject * ChooseAttackTarget(OffensiveProcess * this, float * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall OffensiveProcess::ChooseAttackTarget(OffensiveProcess *this,float *param_1)

{
  GameObject *pGVar1;
  
  pGVar1 = GetClosestEnemyWithin((GameObject *)this->_padding_,param_1);
  return pGVar1;
}
