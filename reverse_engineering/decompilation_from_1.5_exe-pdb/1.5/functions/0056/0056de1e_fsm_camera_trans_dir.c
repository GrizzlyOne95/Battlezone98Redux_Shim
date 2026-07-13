/*
 * Entry: 0056de1e
 * Name: fsm_camera_trans_dir
 * Namespace: Global
 * Signature: void fsm_camera_trans_dir(AiPath * param_1, int * param_2, int * param_3, int * param_4, int * param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
fsm_camera_trans_dir
          (AiPath *param_1,int *param_2,int *param_3,int *param_4,int *param_5,int *param_6)

{
  int iVar1;
  MAT_3D *pMVar2;
  int iVar3;
  AiPath *unaff_ESI;
  long unaff_EDI;
  MAT_3D *pMVar4;
  float fVar5;
  float fVar6;
  MAT_3D local_94;
  MAT_3D local_54;
  float local_14;
  float local_10;
  double local_c;
  
  if ((Camera_Record.Last_Fnct != fsm_camera_trans_dir) || (Camera_Record.Last_Path != param_1)) {
    Init_Segmet(0.0,unaff_EDI,unaff_ESI);
    Camera_Record.x0 = Camera_Record.xt;
    Camera_Record.z0 = Camera_Record.zt;
  }
  iVar3 = *param_5;
  local_10 = (float)*param_2 * 0.01;
  iVar1 = *param_6;
  local_14 = (float)(*param_4 % 36000) * 0.00017453292;
  param_2 = (int *)0x0;
  if (param_3 != (int *)0x0) {
    param_2 = (int *)((float)*param_3 * 0.01);
  }
  fVar5 = TimeStepLocal();
  local_c = (double)(fVar5 * (float)param_2 * (float)Camera_Record.dl);
  if (1.0 < (float)Camera_Record.l) {
    if (param_1->pointCount <= Camera_Record.segment + 2) {
      Camera_Record.End_Path = 1;
      Camera_Record.Last_Path = (void *)0x0;
      Camera_Record.Last_Fnct = (void *)0x0;
      return;
    }
    fVar5 = Fmod1((float)Camera_Record.l,1.0);
    Init_Segmet(fVar5,unaff_EDI,unaff_ESI);
  }
  Camera_Record.End_Path = 0;
  Camera_Record.Last_Fnct = fsm_camera_trans_dir;
  Camera_Record.Last_Path = param_1;
  fVar6 = Terrain_FindFloor(Camera_Record.x0,Camera_Record.z0);
  fVar5 = local_10 + fVar6;
  if (fVar5 < fVar6 + 0.5) {
    fVar5 = fVar6 + 0.5;
  }
  pMVar2 = Build_Position_Rotation_Matrix
                     (&local_94,local_14,(float)(iVar1 % 36000) * 0.00017453292,
                      (float)(iVar3 % 36000) * 0.00017453292,(float)Camera_Record.x0,fVar5,
                      (float)Camera_Record.z0);
  pMVar4 = &local_54;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    pMVar4->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
  }
  Camera_Set_Matrix(&View_Record.MainCam,&local_54);
  fVar5 = lpfilter((float)Camera_Record.x0,(float)Camera_Record.xt,0.3);
  Camera_Record.x0 = (double)fVar5;
  fVar5 = lpfilter((float)Camera_Record.z0,(float)Camera_Record.zt,0.3);
  Camera_Record.z0 = (double)fVar5;
  Camera_Record.zt = Camera_Record.dz * local_c + Camera_Record.zt;
  Camera_Record.xt = Camera_Record.dx * local_c + Camera_Record.xt;
  Camera_Record.l = Camera_Record.l + local_c;
  return;
}
