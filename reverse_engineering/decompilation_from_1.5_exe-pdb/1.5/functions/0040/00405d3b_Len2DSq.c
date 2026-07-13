/*
 * Entry: 00405d3b
 * Name: Len2DSq
 * Namespace: Global
 * Signature: float Len2DSq(VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Len2DSq(VECTOR_3D *param_1)

{
  return param_1->x * param_1->x + param_1->z * param_1->z;
}
