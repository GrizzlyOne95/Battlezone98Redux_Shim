/*
 * Entry: 00417989
 * Name: SetRight
 * Namespace: Global
 * Signature: void SetRight(MAT_3D * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetRight(MAT_3D *param_1,VECTOR_3D *param_2)

{
  param_1->right_x = param_2->x;
  param_1->right_y = param_2->y;
  param_1->right_z = param_2->z;
  return;
}
