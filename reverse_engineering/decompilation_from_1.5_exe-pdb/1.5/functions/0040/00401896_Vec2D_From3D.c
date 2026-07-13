/*
 * Entry: 00401896
 * Name: Vec2D_From3D
 * Namespace: Global
 * Signature: VECTOR_2D Vec2D_From3D(VECTOR_3D param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_2D __cdecl Vec2D_From3D(VECTOR_3D param_1)

{
  VECTOR_2D VVar1;
  
  VVar1.z = param_1.z;
  VVar1.x = param_1.x;
  return VVar1;
}
