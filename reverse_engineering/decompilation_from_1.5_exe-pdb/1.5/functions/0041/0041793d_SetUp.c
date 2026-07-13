/*
 * Entry: 0041793d
 * Name: SetUp
 * Namespace: Global
 * Signature: void SetUp(MAT_3D * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetUp(MAT_3D *param_1,VECTOR_3D *param_2)

{
  param_1->up_x = param_2->x;
  param_1->up_y = param_2->y;
  param_1->up_z = param_2->z;
  return;
}
