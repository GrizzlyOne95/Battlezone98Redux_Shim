/*
 * Entry: 0054c9f6
 * Name: Build_Orthogonal_Matrix
 * Namespace: Global
 * Signature: MAT_3D * Build_Orthogonal_Matrix(MAT_3D * __return_storage_ptr__, VECTOR_3D * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __cdecl
Build_Orthogonal_Matrix(MAT_3D *__return_storage_ptr__,VECTOR_3D *param_1,VECTOR_3D *param_2)

{
  VECTOR_3D *pVVar1;
  VECTOR_3D *in_ECX;
  VECTOR_3D *in_EDX;
  VECTOR_3D local_14;
  VECTOR_3D *local_8;
  
  __return_storage_ptr__->posit_x = 0.0;
  __return_storage_ptr__->posit_y = 0.0;
  __return_storage_ptr__->posit_z = 0.0;
  local_8 = in_EDX;
  pVVar1 = Normalize_Vector(&local_14,in_ECX);
  __return_storage_ptr__->up_x = pVVar1->x;
  __return_storage_ptr__->up_y = pVVar1->y;
  __return_storage_ptr__->up_z = pVVar1->z;
  pVVar1 = Cross_Product(&local_14,(VECTOR_3D *)&__return_storage_ptr__->up_x,local_8);
  __return_storage_ptr__->right_x = pVVar1->x;
  __return_storage_ptr__->right_y = pVVar1->y;
  __return_storage_ptr__->right_z = pVVar1->z;
  pVVar1 = Normalize_Vector(&local_14,(VECTOR_3D *)__return_storage_ptr__);
  __return_storage_ptr__->right_x = pVVar1->x;
  __return_storage_ptr__->right_y = pVVar1->y;
  __return_storage_ptr__->right_z = pVVar1->z;
  pVVar1 = Cross_Product(&local_14,(VECTOR_3D *)__return_storage_ptr__,
                         (VECTOR_3D *)&__return_storage_ptr__->up_x);
  __return_storage_ptr__->front_x = pVVar1->x;
  __return_storage_ptr__->front_y = pVVar1->y;
  __return_storage_ptr__->front_z = pVVar1->z;
  return __return_storage_ptr__;
}
