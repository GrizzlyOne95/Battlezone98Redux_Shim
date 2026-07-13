/*
 * Entry: 004175f7
 * Name: Dist3D
 * Namespace: Global
 * Signature: float Dist3D(VECTOR_3D param_1, VECTOR_3D param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Dist3D(VECTOR_3D param_1,VECTOR_3D param_2)

{
  return SQRT((param_2.z - param_1.z) * (param_2.z - param_1.z) +
              (param_2.y - param_1.y) * (param_2.y - param_1.y) +
              (param_2.x - param_1.x) * (param_2.x - param_1.x));
}
