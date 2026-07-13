/*
 * Entry: 0040778e
 * Name: ClosestApproach
 * Namespace: Global
 * Signature: float ClosestApproach(GameObject * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl ClosestApproach(GameObject *param_1,GameObject *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  
  pfVar8 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  fVar1 = *pfVar8;
  fVar2 = pfVar8[1];
  fVar3 = pfVar8[2];
  pfVar8 = (float *)(**(code **)(param_2->_padding_ + 0xc))();
  fVar7 = (param_2->euler).v.x - (param_1->euler).v.x;
  fVar5 = (param_2->euler).v.y - (param_1->euler).v.y;
  fVar6 = (param_2->euler).v.z - (param_1->euler).v.z;
  fVar4 = fVar7 * fVar7 + fVar5 * fVar5 + fVar6 * fVar6;
  if (ABS(fVar4) < 0.01) {
    return 1e+30;
  }
  return (fVar6 * (fVar3 - pfVar8[2]) + fVar5 * (fVar2 - pfVar8[1]) + fVar7 * (fVar1 - *pfVar8)) /
         fVar4;
}
