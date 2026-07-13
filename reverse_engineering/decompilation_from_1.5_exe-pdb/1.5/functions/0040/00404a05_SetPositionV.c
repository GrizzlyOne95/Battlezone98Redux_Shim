/*
 * Entry: 00404a05
 * Name: SetPositionV
 * Namespace: Global
 * Signature: void SetPositionV(MAT_3D * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetPositionV(MAT_3D *param_1,VECTOR_3D *param_2)

{
  param_1->posit_x = (double)param_2->x;
  param_1->posit_y = (double)param_2->y;
  param_1->posit_z = (double)param_2->z;
  return;
}
