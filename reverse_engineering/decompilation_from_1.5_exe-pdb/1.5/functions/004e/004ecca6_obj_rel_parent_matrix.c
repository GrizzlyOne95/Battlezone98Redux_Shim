/*
 * Entry: 004ecca6
 * Name: obj_rel_parent_matrix
 * Namespace: Global
 * Signature: MAT_3D * obj_rel_parent_matrix(MAT_3D * __return_storage_ptr__, _OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __cdecl
obj_rel_parent_matrix(MAT_3D *__return_storage_ptr__,_OBJ76 *param_1,_OBJ76 *param_2)

{
  int iVar1;
  _OBJ76 *p_Var2;
  MAT_3D *pMVar3;
  MAT_3D *pMVar4;
  MAT_3D local_84;
  MAT_3D local_44;
  
  if (param_1 == param_2) {
    pMVar3 = &Identity_Matrix;
  }
  else {
    p_Var2 = param_1->parent;
    pMVar3 = &param_1->transform;
    pMVar4 = &local_44;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      pMVar4->right_x = pMVar3->right_x;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
    }
    for (; (p_Var2 != (_OBJ76 *)0x0 && (p_Var2 != param_2)); p_Var2 = p_Var2->parent) {
      pMVar3 = Matrix_Multiply(&local_84,&local_44,&p_Var2->transform);
      pMVar4 = &local_44;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        pMVar4->right_x = pMVar3->right_x;
        pMVar3 = (MAT_3D *)&pMVar3->right_y;
        pMVar4 = (MAT_3D *)&pMVar4->right_y;
      }
    }
    pMVar3 = &local_44;
  }
  pMVar4 = __return_storage_ptr__;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    pMVar4->right_x = pMVar3->right_x;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
  }
  return __return_storage_ptr__;
}
