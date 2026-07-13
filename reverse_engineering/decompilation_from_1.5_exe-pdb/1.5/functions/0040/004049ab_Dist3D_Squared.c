/*
 * Entry: 004049ab
 * Name: Dist3D_Squared
 * Namespace: Global
 * Signature: float Dist3D_Squared(VECTOR_3D param_1, VECTOR_3D param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Dist3D_Squared(VECTOR_3D param_1,VECTOR_3D param_2)

{
  return (param_1.y - param_2.y) * (param_1.y - param_2.y) +
         (param_1.z - param_2.z) * (param_1.z - param_2.z) +
         (param_1.x - param_2.x) * (param_1.x - param_2.x);
}
