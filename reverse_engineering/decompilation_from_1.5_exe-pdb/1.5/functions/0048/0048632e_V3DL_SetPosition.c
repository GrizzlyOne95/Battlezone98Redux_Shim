/*
 * Entry: 0048632e
 * Name: V3DL_SetPosition
 * Namespace: Global
 * Signature: void V3DL_SetPosition(MAT_3D * param_1, VECTOR_3D_LONG * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl V3DL_SetPosition(MAT_3D *param_1,VECTOR_3D_LONG *param_2)

{
  param_1->posit_x = param_2->x;
  param_1->posit_y = param_2->y;
  param_1->posit_z = param_2->z;
  return;
}
