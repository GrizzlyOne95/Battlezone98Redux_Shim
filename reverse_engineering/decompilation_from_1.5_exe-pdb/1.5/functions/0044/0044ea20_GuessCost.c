/*
 * Entry: 0044ea20
 * Name: GuessCost
 * Namespace: Global
 * Signature: float GuessCost(Strip * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl GuessCost(Strip *param_1)

{
  float fVar1;
  float fVar2;
  Strip *pSVar3;
  
  pSVar3 = startNode;
  if (param_1->backward == false) {
    pSVar3 = goalNode;
  }
  fVar1 = pSVar3->x - param_1->x;
  fVar2 = pSVar3->z - param_1->z;
  return SQRT(fVar2 * fVar2 + fVar1 * fVar1) + 0.0001;
}
