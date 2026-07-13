/*
 * Entry: 0056db3c
 * Name: fsm_camera_obj_pnt
 * Namespace: Global
 * Signature: void fsm_camera_obj_pnt(_OBJ76 * param_1, int * param_2, int * param_3, int * param_4, float param_5, float param_6, float param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
fsm_camera_obj_pnt(_OBJ76 *param_1,int *param_2,int *param_3,int *param_4,float param_5,
                  float param_6,float param_7)

{
  MAT_3D *pMVar1;
  int iVar2;
  VECTOR_3D *unaff_ESI;
  VECTOR_3D *unaff_EDI;
  MAT_3D *pMVar3;
  MAT_3D local_9c;
  MAT_3D local_5c;
  float local_1c;
  float local_18;
  float local_14;
  VECTOR_3D local_10;
  
  local_10.x = (float)*param_2 * 0.01;
  local_10.y = (float)*param_3 * 0.01;
  local_10.z = (float)*param_4 * 0.01;
  Vector_Transform(&local_10,&local_10,1,&param_1->transform);
  local_1c = param_5 - local_10.x;
  local_18 = param_6 - local_10.y;
  local_14 = param_7 - local_10.z;
  pMVar1 = Build_Directinal_Matrix(&local_9c,unaff_EDI,unaff_ESI);
  pMVar3 = &local_5c;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar3->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  Camera_Set_Matrix(&View_Record.MainCam,&local_5c);
  Camera_Record.End_Path = 0;
  Camera_Record.Last_Path = (void *)0x0;
  Camera_Record.Last_Fnct = fsm_camera_obj_pnt;
  return;
}
