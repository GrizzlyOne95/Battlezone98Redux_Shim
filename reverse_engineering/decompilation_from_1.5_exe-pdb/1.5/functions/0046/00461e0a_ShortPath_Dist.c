/*
 * Entry: 00461e0a
 * Name: ShortPath::Dist
 * Namespace: ShortPath
 * Signature: float Dist(VECTOR_2D * param_1, VECTOR_2D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl ShortPath::Dist(VECTOR_2D *param_1,VECTOR_2D *param_2)

{
  float fVar1;
  float fVar2;
  
  fVar1 = param_1->x - param_2->x;
  fVar2 = param_1->z - param_2->z;
  return SQRT(fVar2 * fVar2 + fVar1 * fVar1);
}
