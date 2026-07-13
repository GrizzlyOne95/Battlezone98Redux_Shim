/*
 * Entry: 0054ca6b
 * Name: Build_Directinal_Matrix
 * Namespace: Global
 * Signature: MAT_3D * Build_Directinal_Matrix(MAT_3D * __return_storage_ptr__, VECTOR_3D * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __cdecl
Build_Directinal_Matrix(MAT_3D *__return_storage_ptr__,VECTOR_3D *param_1,VECTOR_3D *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  VECTOR_3D *pVVar4;
  float *in_ECX;
  float *in_EDX;
  VECTOR_3D local_34;
  VECTOR_3D local_28;
  VECTOR_3D local_1c;
  VECTOR_3D local_10;
  
  __return_storage_ptr__->posit_x = (double)*in_ECX;
  __return_storage_ptr__->posit_y = (double)in_ECX[1];
  __return_storage_ptr__->posit_z = (double)in_ECX[2];
  local_10.x = *in_EDX;
  local_10.y = in_EDX[1];
  local_10.z = in_EDX[2];
  pVVar4 = Normalize_Vector(&local_28,&local_10);
  local_10.x = pVVar4->x;
  local_10.y = pVVar4->y;
  local_10.z = pVVar4->z;
  if (0.02 <= local_10.x * local_10.x + local_10.z * local_10.z) {
    local_28.x = 0.0;
    local_28.y = 1.0;
    local_28.z = 0.0;
    pVVar4 = Cross_Product(&local_34,&local_28,&local_10);
    local_1c.x = pVVar4->x;
    local_1c.y = pVVar4->y;
    local_1c.z = pVVar4->z;
    pVVar4 = Normalize_Vector(&local_34,&local_1c);
    local_1c.x = pVVar4->x;
    local_1c.y = pVVar4->y;
    local_1c.z = pVVar4->z;
  }
  else {
    local_1c.x = 1.0;
    local_1c.y = 0.0;
    local_1c.z = 0.0;
  }
  pVVar4 = Cross_Product(&local_34,&local_10,&local_1c);
  __return_storage_ptr__->right_x = local_1c.x;
  __return_storage_ptr__->right_y = local_1c.y;
  fVar1 = pVVar4->x;
  __return_storage_ptr__->right_z = local_1c.z;
  fVar2 = pVVar4->y;
  fVar3 = pVVar4->z;
  __return_storage_ptr__->up_x = fVar1;
  __return_storage_ptr__->up_y = fVar2;
  __return_storage_ptr__->up_z = fVar3;
  __return_storage_ptr__->front_x = local_10.x;
  __return_storage_ptr__->front_y = local_10.y;
  __return_storage_ptr__->front_z = local_10.z;
  return __return_storage_ptr__;
}
