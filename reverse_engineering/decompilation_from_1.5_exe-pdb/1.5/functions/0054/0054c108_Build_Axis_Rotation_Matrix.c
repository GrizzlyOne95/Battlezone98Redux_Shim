/*
 * Entry: 0054c108
 * Name: Build_Axis_Rotation_Matrix
 * Namespace: Global
 * Signature: MAT_3D * Build_Axis_Rotation_Matrix(MAT_3D * __return_storage_ptr__, float param_1, float param_2, float param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __cdecl
Build_Axis_Rotation_Matrix
          (MAT_3D *__return_storage_ptr__,float param_1,float param_2,float param_3,float param_4)

{
  MAT_3D *pMVar1;
  int iVar2;
  QUAT *unaff_EDI;
  MAT_3D *pMVar3;
  MAT_3D local_5c;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  SINCOS local_c;
  
  local_c = SinCos(param_1 * 0.5);
  local_10 = local_c.Cos;
  local_1c = local_c.Sin * param_2;
  local_18 = local_c.Sin * param_3;
  local_14 = local_c.Sin * param_4;
  pMVar1 = Quaternion_to_Matrix(&local_5c,unaff_EDI);
  pMVar3 = __return_storage_ptr__;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar3->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  return __return_storage_ptr__;
}
