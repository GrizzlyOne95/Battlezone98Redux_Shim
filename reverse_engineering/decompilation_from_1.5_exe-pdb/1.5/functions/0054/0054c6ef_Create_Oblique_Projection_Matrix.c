/*
 * Entry: 0054c6ef
 * Name: Create_Oblique_Projection_Matrix
 * Namespace: Global
 * Signature: int Create_Oblique_Projection_Matrix(MAT_3D * param_1, PLANE * param_2, VECTOR_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Create_Oblique_Projection_Matrix(MAT_3D *param_1,PLANE *param_2,VECTOR_3D *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  MAT_3D *pMVar5;
  MAT_3D *pMVar6;
  MAT_3D local_9c;
  MAT_3D local_5c;
  float local_1c;
  double local_18;
  float local_10;
  float local_c;
  float local_8;
  
  local_10 = (param_2->surf_normal).x;
  local_c = (param_2->surf_normal).y;
  local_8 = (param_2->surf_normal).z;
  fVar1 = param_3->x;
  fVar2 = param_3->y;
  fVar3 = param_3->z;
  local_5c.front_z = local_10 * fVar1 + local_c * fVar2 + local_8 * fVar3;
  if (0.1 <= local_5c.front_z) {
    local_5c.front_z = -1.0 / local_5c.front_z;
    pMVar5 = &Identity_Matrix;
    pMVar6 = &local_5c;
    local_1c = fVar1;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      pMVar6->right_x = pMVar5->right_x;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
      pMVar6 = (MAT_3D *)&pMVar6->right_y;
    }
    local_18 = (double)local_5c.front_z;
    local_5c.right_x = local_10 * local_5c.front_z;
    local_5c.up_y = local_c * local_5c.front_z;
    local_5c.front_z = local_5c.front_z * local_8;
    param_1->right_x = fVar1;
    param_1->up_x = fVar1;
    param_1->front_x = fVar1;
    param_1->posit_x = (double)fVar1;
    param_1->right_y = fVar2;
    param_1->up_y = fVar2;
    param_1->front_y = fVar2;
    param_1->posit_y = (double)fVar2;
    param_1->right_z = fVar3;
    param_1->up_z = fVar3;
    param_1->front_z = fVar3;
    param_1->posit_z = (double)fVar3;
    pMVar5 = Matrix_Multiply(&local_9c,&local_5c,param_1);
    pMVar6 = param_1;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      pMVar6->right_x = pMVar5->right_x;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
      pMVar6 = (MAT_3D *)&pMVar6->right_y;
    }
    fVar1 = param_2->dist * (float)local_18;
    param_1->posit_x = (double)((float)param_1->posit_x * fVar1);
    param_1->posit_y = (double)((float)param_1->posit_y * fVar1);
    iVar4 = 1;
    param_1->posit_z = (double)(fVar1 * (float)param_1->posit_z);
    param_1->right_x = param_1->right_x + 1.0;
    param_1->up_y = param_1->up_y + 1.0;
    param_1->front_z = param_1->front_z + 1.0;
  }
  else {
    iVar4 = 0;
  }
  return iVar4;
}
