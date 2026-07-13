/*
 * Entry: 0056dbe4
 * Name: fsm_camera_obj_path_pnt
 * Namespace: Global
 * Signature: void fsm_camera_obj_path_pnt(_OBJ76 * param_1, int * param_2, int * param_3, int * param_4, AiPath * param_5, int * param_6, long param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
fsm_camera_obj_path_pnt
          (_OBJ76 *param_1,int *param_2,int *param_3,int *param_4,AiPath *param_5,int *param_6,
          long param_7)

{
  VECTOR_3D *pVVar1;
  VECTOR_3D *pVVar2;
  VECTOR_3D *pVVar3;
  VECTOR_3D local_10;
  
  local_10.x = (float)*param_2 * 0.01;
  local_10.y = (float)*param_3 * 0.01;
  local_10.z = (float)*param_4 * 0.01;
  pVVar1 = &local_10;
  pVVar3 = (VECTOR_3D *)0x1;
  pVVar2 = pVVar1;
  Vector_Transform(pVVar1,pVVar1,1,&param_1->transform);
  Set_Camera_to_Path((AiPath *)param_7,(long)pVVar1,(int *)pVVar2,pVVar3);
  Camera_Record.End_Path = 0;
  Camera_Record.Last_Path = (void *)0x0;
  Camera_Record.Last_Fnct = fsm_camera_obj_pnt;
  return;
}
