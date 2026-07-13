/*
 * Entry: 00401877
 * Name: Vec2D_Subtract
 * Namespace: Global
 * Signature: VECTOR_2D Vec2D_Subtract(VECTOR_2D param_1, VECTOR_2D param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_2D __cdecl Vec2D_Subtract(VECTOR_2D param_1,VECTOR_2D param_2)

{
  VECTOR_2D VVar1;
  
  VVar1.z = param_1.z - param_2.z;
  VVar1.x = param_1.x - param_2.x;
  return VVar1;
}
