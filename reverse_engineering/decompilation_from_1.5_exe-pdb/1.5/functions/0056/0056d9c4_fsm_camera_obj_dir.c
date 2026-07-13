/*
 * Entry: 0056d9c4
 * Name: fsm_camera_obj_dir
 * Namespace: Global
 * Signature: void fsm_camera_obj_dir(_OBJ76 * param_1, int * param_2, int * param_3, int * param_4, int * param_5, int * param_6, int * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
fsm_camera_obj_dir(_OBJ76 *param_1,int *param_2,int *param_3,int *param_4,int *param_5,int *param_6,
                  int *param_7)

{
  MAT_3D *pMVar1;
  int iVar2;
  MAT_3D *pMVar3;
  float fVar4;
  MAT_3D local_84;
  MAT_3D local_44;
  
  pMVar1 = Build_Position_Rotation_Matrix
                     (&local_84,(float)(*param_5 % 36000) * 0.00017453292,
                      (float)(*param_7 % 36000) * 0.00017453292,
                      (float)(*param_6 % 36000) * 0.00017453292,(float)*param_2 * 0.01,
                      (float)*param_3 * 0.01,(float)*param_4 * 0.01);
  pMVar3 = &local_44;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar3->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  pMVar1 = Matrix_Multiply(&local_84,&local_44,&param_1->transform);
  pMVar3 = &local_44;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar3->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  fVar4 = Terrain_FindFloor(local_44.posit_x,local_44.posit_z);
  if ((float)local_44.posit_y < fVar4 + 0.5) {
    local_44.posit_y = (double)(fVar4 + 0.5);
  }
  Camera_Set_Matrix(&View_Record.MainCam,&local_44);
  Camera_Record.End_Path = 0;
  Camera_Record.Last_Path = (void *)0x0;
  Camera_Record.Last_Fnct = fsm_camera_obj_dir;
  return;
}
