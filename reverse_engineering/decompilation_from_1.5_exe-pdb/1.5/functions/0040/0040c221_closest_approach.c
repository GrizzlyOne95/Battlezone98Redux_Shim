/*
 * Entry: 0040c221
 * Name: closest_approach
 * Namespace: Global
 * Signature: float closest_approach(VECTOR_3D * param_1, VECTOR_3D * param_2, VECTOR_3D * param_3, VECTOR_3D * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl
closest_approach(VECTOR_3D *param_1,VECTOR_3D *param_2,VECTOR_3D *param_3,VECTOR_3D *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar4 = param_4->x - param_2->x;
  fVar2 = param_4->y - param_2->y;
  fVar3 = param_4->z - param_2->z;
  fVar1 = fVar4 * fVar4 + fVar2 * fVar2 + fVar3 * fVar3;
  if (ABS(fVar1) < 0.01) {
    return 1e+07;
  }
  return (fVar3 * (param_1->z - param_3->z) + fVar2 * (param_1->y - param_3->y) +
         fVar4 * (param_1->x - param_3->x)) / fVar1;
}
