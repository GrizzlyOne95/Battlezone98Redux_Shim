/*
 * Entry: 004809be
 * Name: TooFar
 * Namespace: Global
 * Signature: bool TooFar(VECTOR_3D param_1, VECTOR_3D param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl TooFar(VECTOR_3D param_1,VECTOR_3D param_2)

{
  float fVar1;
  
  fVar1 = (param_2.x - param_1.x) * (param_2.x - param_1.x);
  if (((fVar1 <= 22500.0) &&
      (fVar1 = (param_2.z - param_1.z) * (param_2.z - param_1.z) + fVar1, fVar1 <= 22500.0)) &&
     ((param_2.y - param_1.y) * (param_2.y - param_1.y) + fVar1 <= 22500.0)) {
    return false;
  }
  return true;
}
