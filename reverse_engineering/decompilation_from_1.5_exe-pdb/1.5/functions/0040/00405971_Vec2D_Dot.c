/*
 * Entry: 00405971
 * Name: Vec2D_Dot
 * Namespace: Global
 * Signature: float Vec2D_Dot(VECTOR_2D param_1, VECTOR_2D param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Vec2D_Dot(VECTOR_2D param_1,VECTOR_2D param_2)

{
  return param_2.x * param_1.x + param_2.z * param_1.z;
}
