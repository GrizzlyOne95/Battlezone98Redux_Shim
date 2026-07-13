/*
 * Entry: 0054be47
 * Name: Build_Position_Rotation_Matrix
 * Namespace: Global
 * Signature: MAT_3D * Build_Position_Rotation_Matrix(MAT_3D * __return_storage_ptr__, float param_1, float param_2, float param_3, float param_4, float param_5, float param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __cdecl
Build_Position_Rotation_Matrix
          (MAT_3D *__return_storage_ptr__,float param_1,float param_2,float param_3,float param_4,
          float param_5,float param_6)

{
  SINCOS SVar1;
  SINCOS SVar2;
  SINCOS SVar3;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  
  SVar1 = SinCos(param_3);
  SVar2 = SinCos(param_1);
  SVar3 = SinCos(param_2);
  local_14 = SVar1.Cos;
  local_18 = SVar1.Sin;
  local_20 = SVar2.Sin;
  local_10 = SVar3.Sin;
  __return_storage_ptr__->right_x = local_20 * local_10 * local_18 + local_c * local_14;
  local_1c = SVar2.Cos;
  __return_storage_ptr__->right_y = local_1c * local_18;
  __return_storage_ptr__->right_z = local_c * local_20 * local_18 - local_14 * local_10;
  __return_storage_ptr__->up_x = local_14 * local_20 * local_10 - local_c * local_18;
  __return_storage_ptr__->up_y = local_1c * local_14;
  __return_storage_ptr__->up_z = local_c * local_14 * local_20 + local_10 * local_18;
  __return_storage_ptr__->front_x = local_1c * local_10;
  __return_storage_ptr__->front_y = -local_20;
  __return_storage_ptr__->front_z = local_1c * local_c;
  __return_storage_ptr__->posit_x = (double)param_4;
  __return_storage_ptr__->posit_y = (double)param_5;
  __return_storage_ptr__->posit_z = (double)param_6;
  return __return_storage_ptr__;
}
