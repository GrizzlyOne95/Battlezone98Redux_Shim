/*
 * Entry: 0040498e
 * Name: Dot_Product
 * Namespace: Global
 * Signature: float Dot_Product(VECTOR_3D * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Dot_Product(VECTOR_3D *param_1,VECTOR_3D *param_2)

{
  return param_1->x * param_2->x + param_1->y * param_2->y + param_1->z * param_2->z;
}
