/*
 * Entry: 0046192d
 * Name: ShortPath::DistSq
 * Namespace: ShortPath
 * Signature: float DistSq(VECTOR_2D * param_1, VECTOR_2D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl ShortPath::DistSq(VECTOR_2D *param_1,VECTOR_2D *param_2)

{
  float fVar1;
  float fVar2;
  
  fVar1 = param_1->x - param_2->x;
  fVar2 = param_1->z - param_2->z;
  return fVar2 * fVar2 + fVar1 * fVar1;
}
