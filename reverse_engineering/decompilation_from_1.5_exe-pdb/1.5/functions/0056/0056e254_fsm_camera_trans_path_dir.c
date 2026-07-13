/*
 * Entry: 0056e254
 * Name: fsm_camera_trans_path_dir
 * Namespace: Global
 * Signature: void fsm_camera_trans_path_dir(AiPath * param_1, int * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl fsm_camera_trans_path_dir(AiPath *param_1,int *param_2,int *param_3)

{
  double dVar1;
  AiPath *unaff_ESI;
  AiPath *pAVar2;
  long unaff_EDI;
  float fVar3;
  float fVar4;
  double dVar5;
  double dVar6;
  
  if ((Camera_Record.Last_Fnct != fsm_camera_trans_path_dir) || (Camera_Record.Last_Path != param_1)
     ) {
    Init_Segmet(0.0,unaff_EDI,unaff_ESI);
    Camera_Record.x0 = Camera_Record.xt;
    Camera_Record.z0 = Camera_Record.zt;
  }
  fVar4 = 0.0;
  if (param_3 != (int *)0x0) {
    fVar4 = (float)*param_3 * 0.01;
  }
  fVar3 = TimeStepLocal();
  dVar1 = (double)(fVar3 * (float)Camera_Record.dl * fVar4);
  if (1.0 < (float)Camera_Record.l) {
    if (param_1->pointCount <= Camera_Record.segment + 2) {
      Camera_Record.End_Path = 1;
      Camera_Record.Last_Path = (void *)0x0;
      Camera_Record.Last_Fnct = (void *)0x0;
      return;
    }
    fVar4 = Fmod1((float)Camera_Record.l,1.0);
    Init_Segmet(fVar4,unaff_EDI,unaff_ESI);
  }
  Camera_Record.End_Path = 0;
  pAVar2 = (AiPath *)(Camera_Record.segment + 1);
  dVar6 = (double)(float)Camera_Record.z0;
  Camera_Record.Last_Fnct = fsm_camera_trans_path_dir;
  Camera_Record.Last_Path = param_1;
  dVar5 = (double)(float)Camera_Record.x0;
  Terrain_FindFloor(dVar5,dVar6);
  Set_Camera_to_Path(pAVar2,SUB84(dVar5,0),(int *)((ulonglong)dVar5 >> 0x20),SUB84(dVar6,0));
  fVar4 = lpfilter((float)Camera_Record.x0,(float)Camera_Record.xt,0.3);
  Camera_Record.x0 = (double)fVar4;
  fVar4 = lpfilter((float)Camera_Record.z0,(float)Camera_Record.zt,0.3);
  Camera_Record.z0 = (double)fVar4;
  Camera_Record.zt = Camera_Record.dz * dVar1 + Camera_Record.zt;
  Camera_Record.xt = Camera_Record.dx * dVar1 + Camera_Record.xt;
  Camera_Record.l = Camera_Record.l + dVar1;
  return;
}
