/*
 * Entry: 004ca370
 * Name: EditTerrain_GetCameraMatrix
 * Namespace: Global
 * Signature: MAT_3D * EditTerrain_GetCameraMatrix(MAT_3D * __return_storage_ptr__)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __cdecl EditTerrain_GetCameraMatrix(MAT_3D *__return_storage_ptr__)

{
  MAT_3D *pMVar1;
  int iVar2;
  MAT_3D *pMVar3;
  MAT_3D local_44;
  
  pMVar1 = EditTerrain::GetCameraMatrix(&editTerrain,&local_44);
  pMVar3 = __return_storage_ptr__;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar3->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  return __return_storage_ptr__;
}
