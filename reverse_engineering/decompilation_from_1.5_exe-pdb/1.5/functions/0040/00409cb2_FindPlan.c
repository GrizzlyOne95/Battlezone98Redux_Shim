/*
 * Entry: 00409cb2
 * Name: FindPlan
 * Namespace: Global
 * Signature: AiPath * FindPlan(GameObject * param_1, float param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiPath * __cdecl FindPlan(GameObject *param_1,float param_2,float param_3)

{
  float *pfVar1;
  int iVar2;
  AiPath *pAVar3;
  
  pfVar1 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  iVar2 = (**(code **)(param_1->_padding_ + 4))();
  pAVar3 = FindPlan(*pfVar1,pfVar1[2],param_2,param_3,param_1[1]._padding_,iVar2);
  return pAVar3;
}
