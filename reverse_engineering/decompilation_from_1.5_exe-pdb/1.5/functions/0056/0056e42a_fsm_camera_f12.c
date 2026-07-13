/*
 * Entry: 0056e42a
 * Name: fsm_camera_f12
 * Namespace: Global
 * Signature: void fsm_camera_f12(_OBJ76 * param_1, _OBJ76 * param_2, int * param_3, int * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl fsm_camera_f12(_OBJ76 *param_1,_OBJ76 *param_2,int *param_3,int *param_4)

{
  MAT_3D *pMVar1;
  int iVar2;
  int iVar3;
  VECTOR_3D *unaff_ESI;
  VECTOR_3D *unaff_EDI;
  MAT_3D *pMVar4;
  float fVar5;
  double dVar6;
  MAT_3D local_e0;
  MAT_3D local_a0;
  MAT_3D local_60;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_14 = (float)*param_3 * 0.01;
  iVar3 = *param_4;
  local_20 = (float)(param_1->transform).posit_x;
  local_1c = (float)(param_1->transform).posit_y + (float)iVar3 * 0.01;
  local_18 = (float)(param_1->transform).posit_z;
  local_10 = (float)((float10)(param_2->transform).posit_x - (float10)(param_1->transform).posit_x);
  local_c = (float)(((float10)(param_2->transform).posit_y - (float10)(param_1->transform).posit_y)
                   - (float10)2.0);
  local_8 = (float)((float10)(param_2->transform).posit_z - (float10)(param_1->transform).posit_z);
  dVar6 = rsqrt((double)(local_10 * local_10 + local_c * local_c + local_8 * local_8));
  fVar5 = (float)dVar6;
  local_10 = local_10 * fVar5;
  local_c = local_c * fVar5;
  local_8 = fVar5 * local_8;
  local_20 = local_20 - local_10 * local_14;
  local_1c = local_1c - local_c * local_14;
  local_18 = local_18 - local_8 * local_14;
  pMVar1 = Build_Directinal_Matrix(&local_e0,unaff_EDI,unaff_ESI);
  pMVar4 = &local_60;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar4->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
  }
  if (0.03 < fVar5) {
    param_3 = (int *)((fVar5 - 0.03) * 5.0);
    if (!NAN((float)param_3) && 0.5235988 < (float)param_3 != ((float)param_3 == 0.5235988)) {
      param_3 = (int *)0x3f060a92;
    }
    dVar6 = rsqrt((double)(local_10 * local_10 + local_8 * local_8));
    pMVar1 = Build_Axis_Rotation_Matrix
                       (&local_e0,-(float)param_3,(float)dVar6 * local_8,0.0,
                        -(local_10 * (float)dVar6));
    fVar5 = local_10 * local_14;
    pMVar4 = &local_a0;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      pMVar4->right_x = pMVar1->right_x;
      pMVar1 = (MAT_3D *)&pMVar1->right_y;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
    }
    local_60.posit_x = (double)-fVar5;
    local_60.posit_y = (double)-(local_c * local_14);
    local_60.posit_z = (double)-(local_8 * local_14);
    local_a0.posit_x = (param_1->transform).posit_x;
    local_a0.posit_y = (double)((float)iVar3 * 0.01 + (float)(param_1->transform).posit_y);
    local_a0.posit_z = (param_1->transform).posit_z;
    pMVar1 = Matrix_Multiply(&local_e0,&local_60,&local_a0);
    pMVar4 = &local_60;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      pMVar4->right_x = pMVar1->right_x;
      pMVar1 = (MAT_3D *)&pMVar1->right_y;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
    }
  }
  fVar5 = Terrain_FindFloor(local_60.posit_x,local_60.posit_z);
  if ((float)local_60.posit_y < fVar5 + 0.5) {
    local_60.posit_y = (double)(fVar5 + 0.5);
  }
  Camera_Set_Matrix(&View_Record.MainCam,&local_60);
  Camera_Record.End_Path = 0;
  Camera_Record.Last_Path = (void *)0x0;
  Camera_Record.Last_Fnct = fsm_camera_f12;
  return;
}
