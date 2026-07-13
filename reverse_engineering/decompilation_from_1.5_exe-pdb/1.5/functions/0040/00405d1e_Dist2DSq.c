/*
 * Entry: 00405d1e
 * Name: Dist2DSq
 * Namespace: Global
 * Signature: float Dist2DSq(VECTOR_3D * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Dist2DSq(VECTOR_3D *param_1,VECTOR_3D *param_2)

{
  float fVar1;
  float fVar2;
  
  fVar1 = param_1->x - param_2->x;
  fVar2 = param_1->z - param_2->z;
  return fVar2 * fVar2 + fVar1 * fVar1;
}
