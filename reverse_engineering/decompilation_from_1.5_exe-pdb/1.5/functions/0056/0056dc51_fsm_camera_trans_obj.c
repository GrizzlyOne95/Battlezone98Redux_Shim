/*
 * Entry: 0056dc51
 * Name: fsm_camera_trans_obj
 * Namespace: Global
 * Signature: void fsm_camera_trans_obj(AiPath * param_1, int * param_2, int * param_3, _OBJ76 * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl fsm_camera_trans_obj(AiPath *param_1,int *param_2,int *param_3,_OBJ76 *param_4)

{
  double dVar1;
  long unaff_EBX;
  AiPath *unaff_ESI;
  AiPath *unaff_EDI;
  float fVar2;
  float fVar3;
  double dVar4;
  
  if ((Camera_Record.Last_Fnct != fsm_camera_trans_obj) || (Camera_Record.Last_Path != param_1)) {
    Init_Segmet(0.0,(long)unaff_EDI,unaff_ESI);
    Camera_Record.x0 = Camera_Record.xt;
    Camera_Record.z0 = Camera_Record.zt;
  }
  fVar3 = 0.0;
  if (param_3 != (int *)0x0) {
    fVar3 = (float)*param_3 * 0.01;
  }
  fVar2 = TimeStepLocal();
  dVar1 = (double)(fVar2 * (float)Camera_Record.dl * fVar3);
  if (1.0 < (float)Camera_Record.l) {
    if (param_1->pointCount <= Camera_Record.segment + 2) {
      Camera_Record.End_Path = 1;
      Camera_Record.Last_Path = (void *)0x0;
      Camera_Record.Last_Fnct = (void *)0x0;
      return;
    }
    fVar3 = Fmod1((float)Camera_Record.l,1.0);
    Init_Segmet(fVar3,unaff_EBX,unaff_EDI);
  }
  Camera_Record.End_Path = 0;
  Camera_Record.Last_Fnct = fsm_camera_trans_obj;
  Camera_Record.Last_Path = param_1;
  dVar4 = (double)(float)Camera_Record.x0;
  Terrain_FindFloor(dVar4,(double)(float)Camera_Record.z0);
  Set_Camera_to_Target(SUB84(dVar4,0),(VECTOR_3D *)((ulonglong)dVar4 >> 0x20));
  fVar3 = lpfilter((float)Camera_Record.x0,(float)Camera_Record.xt,0.3);
  Camera_Record.x0 = (double)fVar3;
  fVar3 = lpfilter((float)Camera_Record.z0,(float)Camera_Record.zt,0.3);
  Camera_Record.z0 = (double)fVar3;
  Camera_Record.zt = Camera_Record.dz * dVar1 + Camera_Record.zt;
  Camera_Record.xt = Camera_Record.dx * dVar1 + Camera_Record.xt;
  Camera_Record.l = Camera_Record.l + dVar1;
  return;
}
