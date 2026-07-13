/*
 * Entry: 004033fa
 * Name: Vec2D_Len
 * Namespace: Global
 * Signature: float Vec2D_Len(VECTOR_2D param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Vec2D_Len(VECTOR_2D param_1)

{
  return SQRT(param_1.x * param_1.x + param_1.z * param_1.z);
}
