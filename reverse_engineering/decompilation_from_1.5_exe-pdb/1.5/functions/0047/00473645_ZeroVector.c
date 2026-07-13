/*
 * Entry: 00473645
 * Name: ZeroVector
 * Namespace: Global
 * Signature: int ZeroVector(VECTOR_3D param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ZeroVector(VECTOR_3D param_1)

{
  if (((param_1.x * param_1.x < 9.999999e-09) && (param_1.y * param_1.y < 9.999999e-09)) &&
     (param_1.z * param_1.z < 9.999999e-09)) {
    return 1;
  }
  return 0;
}
