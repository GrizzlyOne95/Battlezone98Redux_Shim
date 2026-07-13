/*
 * Entry: 0054bd7f
 * Name: Build_Roll_Matrix
 * Namespace: Global
 * Signature: MAT_3D * Build_Roll_Matrix(MAT_3D * __return_storage_ptr__, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __cdecl Build_Roll_Matrix(MAT_3D *__return_storage_ptr__,float param_1)

{
  int iVar1;
  MAT_3D *pMVar2;
  MAT_3D *pMVar3;
  SINCOS SVar4;
  
  pMVar2 = &Identity_Matrix;
  pMVar3 = __return_storage_ptr__;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    pMVar3->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  SVar4 = SinCos(param_1);
  __return_storage_ptr__->right_x = SVar4.Cos;
  __return_storage_ptr__->up_y = SVar4.Cos;
  __return_storage_ptr__->up_x = -SVar4.Sin;
  __return_storage_ptr__->right_y = SVar4.Sin;
  return __return_storage_ptr__;
}
