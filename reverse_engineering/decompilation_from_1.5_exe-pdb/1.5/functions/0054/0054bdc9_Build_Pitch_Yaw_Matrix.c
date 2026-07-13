/*
 * Entry: 0054bdc9
 * Name: Build_Pitch_Yaw_Matrix
 * Namespace: Global
 * Signature: MAT_3D * Build_Pitch_Yaw_Matrix(MAT_3D * __return_storage_ptr__, float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __cdecl Build_Pitch_Yaw_Matrix(MAT_3D *__return_storage_ptr__,float param_1,float param_2)

{
  float fVar1;
  float fVar2;
  SINCOS SVar3;
  SINCOS SVar4;
  float local_14;
  float local_10;
  
  SVar3 = SinCos(param_2);
  SVar4 = SinCos(param_1);
  local_10 = SVar3.Cos;
  local_14 = SVar3.Sin;
  fVar2 = SVar4.Cos;
  fVar1 = SVar4.Sin;
  __return_storage_ptr__->right_x = local_10;
  __return_storage_ptr__->right_y = 0.0;
  __return_storage_ptr__->right_z = -local_14;
  __return_storage_ptr__->up_x = fVar1 * local_14;
  __return_storage_ptr__->up_y = fVar2;
  __return_storage_ptr__->up_z = fVar1 * local_10;
  __return_storage_ptr__->front_x = fVar2 * local_14;
  __return_storage_ptr__->front_y = -fVar1;
  __return_storage_ptr__->front_z = fVar2 * local_10;
  __return_storage_ptr__->posit_x = 0.0;
  __return_storage_ptr__->posit_y = 0.0;
  __return_storage_ptr__->posit_z = 0.0;
  return __return_storage_ptr__;
}
