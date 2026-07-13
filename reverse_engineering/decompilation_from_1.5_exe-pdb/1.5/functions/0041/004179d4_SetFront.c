/*
 * Entry: 004179d4
 * Name: SetFront
 * Namespace: Global
 * Signature: void SetFront(MAT_3D * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetFront(MAT_3D *param_1,VECTOR_3D *param_2)

{
  param_1->front_x = param_2->x;
  param_1->front_y = param_2->y;
  param_1->front_z = param_2->z;
  return;
}
