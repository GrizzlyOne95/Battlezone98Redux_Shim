/*
 * Entry: 0056dad7
 * Name: fsm_camera_obj_obj
 * Namespace: Global
 * Signature: void fsm_camera_obj_obj(_OBJ76 * param_1, int * param_2, int * param_3, int * param_4, _OBJ76 * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
fsm_camera_obj_obj(_OBJ76 *param_1,int *param_2,int *param_3,int *param_4,_OBJ76 *param_5)

{
  _OBJ76 *p_Var1;
  VECTOR_3D *pVVar2;
  
  p_Var1 = (_OBJ76 *)((float)*param_2 * 0.01);
  pVVar2 = (VECTOR_3D *)((float)*param_3 * 0.01);
  Vector_Transform((VECTOR_3D *)&stack0xfffffff0,(VECTOR_3D *)&stack0xfffffff0,1,&param_1->transform
                  );
  Set_Camera_to_Target(p_Var1,pVVar2);
  Camera_Record.End_Path = 0;
  Camera_Record.Last_Path = (void *)0x0;
  Camera_Record.Last_Fnct = fsm_camera_obj_obj;
  return;
}
