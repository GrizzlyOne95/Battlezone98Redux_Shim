/*
 * Entry: 004179ee
 * Name: Matrix_Set
 * Namespace: Global
 * Signature: void Matrix_Set(MAT_3D * param_1, VECTOR_3D param_2, VECTOR_3D param_3, VECTOR_3D param_4, VECTOR_3D param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Matrix_Set(MAT_3D *param_1,VECTOR_3D param_2,VECTOR_3D param_3,VECTOR_3D param_4,VECTOR_3D param_5)

{
  param_1->up_x = param_2.x;
  param_1->up_y = param_2.y;
  param_1->up_z = param_2.z;
  param_1->right_x = param_3.x;
  param_1->right_y = param_3.y;
  param_1->right_z = param_3.z;
  param_1->front_x = param_4.x;
  param_1->front_y = param_4.y;
  param_1->front_z = param_4.z;
  param_1->posit_x = (double)param_5.x;
  param_1->posit_y = (double)param_5.y;
  param_1->posit_z = (double)param_5.z;
  return;
}
