/*
 * Entry: 004ecfe8
 * Name: get_obj_radius
 * Namespace: Global
 * Signature: float get_obj_radius(_OBJ76 * param_1, VECTOR_3D param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl get_obj_radius(_OBJ76 *param_1,VECTOR_3D param_2)

{
  MAT_3D *pMVar1;
  int iVar2;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar3;
  float fVar4;
  MAT_3D local_84;
  MAT_3D local_44;
  
  pMVar1 = Matrix_Inverse(&local_84,unaff_EDI);
  pMVar3 = &local_44;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar3->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  local_44.posit_x = (double)((float)local_44.posit_x - param_2.x);
  local_44.posit_y = (double)((float)local_44.posit_y - param_2.y);
  local_44.posit_z = (double)((float)local_44.posit_z - param_2.z);
  fVar4 = Obj76_Get_Radius(param_1,&local_44,0.0);
  return SQRT(fVar4);
}
