/*
 * Entry: 004ed042
 * Name: get_obj_bounding_box
 * Namespace: Global
 * Signature: void get_obj_bounding_box(_OBJ76 * param_1, VECTOR_3D * param_2, VECTOR_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl get_obj_bounding_box(_OBJ76 *param_1,VECTOR_3D *param_2,VECTOR_3D *param_3)

{
  MAT_3D *pMVar1;
  int iVar2;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar3;
  MAT_3D local_84;
  MAT_3D local_44;
  
  pMVar1 = Matrix_Inverse(&local_84,unaff_EDI);
  pMVar3 = &local_44;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar3->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  param_2->x = 1e+07;
  param_2->y = 1e+07;
  param_2->z = 1e+07;
  param_3->x = -1e+07;
  param_3->y = -1e+07;
  param_3->z = -1e+07;
  Obj76_Bounding_Box(param_1,&local_44,param_2,param_3);
  return;
}
