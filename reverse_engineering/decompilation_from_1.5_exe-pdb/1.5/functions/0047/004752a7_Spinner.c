/*
 * Entry: 004752a7
 * Name: Spinner
 * Namespace: Global
 * Signature: MAT_3D * Spinner(MAT_3D * __return_storage_ptr__, MAT_3D * param_1, VECTOR_3D param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __cdecl
Spinner(MAT_3D *__return_storage_ptr__,MAT_3D *param_1,VECTOR_3D param_2,float param_3)

{
  MAT_3D *pMVar1;
  int iVar2;
  MAT_3D *pMVar3;
  MAT_3D local_44;
  
  pMVar1 = Build_Position_Rotation_Matrix
                     (&local_44,-(param_2.x * param_3),-(param_2.y * param_3),-(param_2.z * param_3)
                      ,0.0,0.0,0.0);
  pMVar3 = __return_storage_ptr__;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar3->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  pMVar1 = Matrix_Multiply(&local_44,__return_storage_ptr__,param_1);
  pMVar3 = __return_storage_ptr__;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar3->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  return __return_storage_ptr__;
}
