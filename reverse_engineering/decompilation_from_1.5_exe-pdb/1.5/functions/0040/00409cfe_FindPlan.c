/*
 * Entry: 00409cfe
 * Name: FindPlan
 * Namespace: Global
 * Signature: AiPath * FindPlan(GameObject * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiPath * __cdecl FindPlan(GameObject *param_1,GameObject *param_2)

{
  float *pfVar1;
  AiPath *pAVar2;
  
  pfVar1 = (float *)(**(code **)(param_2->_padding_ + 0xc))();
  pAVar2 = FindPlan(param_1,*pfVar1,pfVar1[2]);
  return pAVar2;
}
