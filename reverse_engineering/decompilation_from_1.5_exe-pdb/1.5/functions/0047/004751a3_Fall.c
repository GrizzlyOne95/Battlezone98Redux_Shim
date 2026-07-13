/*
 * Entry: 004751a3
 * Name: Fall
 * Namespace: Global
 * Signature: void Fall(VECTOR_3D * param_1, VECTOR_3D * param_2, float param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Fall(VECTOR_3D *param_1,VECTOR_3D *param_2,float param_3,float param_4)

{
  param_1->x = param_2->x * param_4 + param_1->x;
  param_1->z = param_2->z * param_4 + param_1->z;
  param_1->y = (param_3 * param_4 * 0.5 + param_2->y) * param_4 + param_1->y;
  param_2->y = param_3 * param_4 + param_2->y;
  return;
}
