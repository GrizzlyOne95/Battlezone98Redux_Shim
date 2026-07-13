/*
 * Entry: 005258ad
 * Name: File_Matrix_To_I76_Matrix
 * Namespace: Global
 * Signature: void File_Matrix_To_I76_Matrix(MAT_3D * param_1, MAT_3D_FILE * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl File_Matrix_To_I76_Matrix(MAT_3D *param_1,MAT_3D_FILE *param_2)

{
  param_1->right_x = param_2->right_x;
  param_1->right_y = param_2->right_y;
  param_1->right_z = param_2->right_z;
  param_1->up_x = param_2->up_x;
  param_1->up_y = param_2->up_y;
  param_1->up_z = param_2->up_z;
  param_1->front_x = param_2->front_x;
  param_1->front_y = param_2->front_y;
  param_1->front_z = param_2->front_z;
  param_1->posit_x = (double)param_2->posit_x;
  param_1->posit_y = (double)param_2->posit_y;
  param_1->posit_z = (double)param_2->posit_z;
  return;
}
