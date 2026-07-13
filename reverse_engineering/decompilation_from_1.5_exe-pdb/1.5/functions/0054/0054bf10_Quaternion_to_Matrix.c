/*
 * Entry: 0054bf10
 * Name: Quaternion_to_Matrix
 * Namespace: Global
 * Signature: MAT_3D * Quaternion_to_Matrix(MAT_3D * __return_storage_ptr__, QUAT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __cdecl Quaternion_to_Matrix(MAT_3D *__return_storage_ptr__,QUAT *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float *in_ECX;
  
  fVar1 = *in_ECX;
  fVar2 = in_ECX[1] * in_ECX[1] * 2.0;
  fVar3 = in_ECX[2] * in_ECX[2] * 2.0;
  fVar4 = *in_ECX * in_ECX[1] * 2.0;
  fVar5 = in_ECX[2] * *in_ECX * 2.0;
  fVar6 = in_ECX[3] * *in_ECX * 2.0;
  fVar7 = in_ECX[2] * in_ECX[1] * 2.0;
  fVar8 = in_ECX[3] * in_ECX[1] * 2.0;
  fVar9 = in_ECX[3] * in_ECX[2] * 2.0;
  __return_storage_ptr__->posit_x = 0.0;
  __return_storage_ptr__->posit_y = 0.0;
  __return_storage_ptr__->posit_z = 0.0;
  __return_storage_ptr__->right_x = (1.0 - fVar2) - fVar3;
  __return_storage_ptr__->right_y = fVar4 - fVar9;
  __return_storage_ptr__->right_z = fVar8 + fVar5;
  __return_storage_ptr__->up_x = fVar9 + fVar4;
  fVar1 = 1.0 - fVar1 * fVar1 * 2.0;
  __return_storage_ptr__->up_y = fVar1 - fVar3;
  __return_storage_ptr__->up_z = fVar7 - fVar6;
  __return_storage_ptr__->front_x = fVar5 - fVar8;
  __return_storage_ptr__->front_y = fVar7 + fVar6;
  __return_storage_ptr__->front_z = fVar1 - fVar2;
  return __return_storage_ptr__;
}
