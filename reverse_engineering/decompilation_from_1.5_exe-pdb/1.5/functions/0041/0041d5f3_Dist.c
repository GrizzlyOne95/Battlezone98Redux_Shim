/*
 * Entry: 0041d5f3
 * Name: Dist
 * Namespace: Global
 * Signature: float Dist(VECTOR_2D param_1, VECTOR_2D param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Dist(VECTOR_2D param_1,VECTOR_2D param_2)

{
  float in_ECX;
  VECTOR_2D VVar1;
  undefined4 local_8;
  
  VVar1 = Vec2D_Subtract(param_1,param_2);
  local_8 = VVar1.z;
  return SQRT(local_8 * local_8 + in_ECX * in_ECX);
}
