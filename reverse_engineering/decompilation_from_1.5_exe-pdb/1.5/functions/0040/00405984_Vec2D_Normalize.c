/*
 * Entry: 00405984
 * Name: Vec2D_Normalize
 * Namespace: Global
 * Signature: VECTOR_2D Vec2D_Normalize(VECTOR_2D param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_2D __cdecl Vec2D_Normalize(VECTOR_2D param_1)

{
  float fVar1;
  VECTOR_2D VVar2;
  double dVar3;
  undefined4 local_c;
  undefined4 local_8;
  
  fVar1 = param_1.x * param_1.x + param_1.z * param_1.z;
  if (fVar1 <= 0.0) {
    local_8 = 0.0;
    local_c = 0.0;
  }
  else {
    dVar3 = rsqrt((double)fVar1);
    local_c = param_1.x * (float)dVar3;
    local_8 = (float)dVar3 * param_1.z;
  }
  VVar2.z = local_8;
  VVar2.x = local_c;
  return VVar2;
}
