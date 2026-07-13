/*
 * Entry: 0040167f
 * Name: VecLen
 * Namespace: Global
 * Signature: float VecLen(VECTOR_3D param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl VecLen(VECTOR_3D param_1)

{
  return SQRT(param_1.x * param_1.x + param_1.y * param_1.y + param_1.z * param_1.z);
}
