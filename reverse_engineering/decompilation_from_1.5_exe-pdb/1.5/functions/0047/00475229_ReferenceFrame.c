/*
 * Entry: 00475229
 * Name: ReferenceFrame
 * Namespace: Global
 * Signature: MAT_3D * ReferenceFrame(MAT_3D * __return_storage_ptr__, _OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __cdecl ReferenceFrame(MAT_3D *__return_storage_ptr__,_OBJ76 *param_1,_OBJ76 *param_2)

{
  MAT_3D *pMVar1;
  int iVar2;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar3;
  MAT_3D local_c4;
  MAT_3D local_84;
  MAT_3D local_44;
  
  pMVar1 = obj_rel_parent_matrix(&local_44,param_1,(_OBJ76 *)0x0);
  pMVar3 = &local_c4;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar3->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  pMVar1 = obj_rel_parent_matrix(&local_44,param_2,(_OBJ76 *)0x0);
  pMVar3 = &local_84;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar3->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  pMVar1 = Matrix_Inverse(&local_44,unaff_EDI);
  pMVar3 = &local_84;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar3->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  pMVar1 = Matrix_Multiply(&local_44,&local_c4,&local_84);
  pMVar3 = __return_storage_ptr__;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar3->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  return __return_storage_ptr__;
}
