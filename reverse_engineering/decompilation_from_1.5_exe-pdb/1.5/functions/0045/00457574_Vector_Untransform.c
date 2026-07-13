/*
 * Entry: 00457574
 * Name: Vector_Untransform
 * Namespace: Global
 * Signature: VECTOR_3D * Vector_Untransform(VECTOR_3D * __return_storage_ptr__, VECTOR_3D * param_1, MAT_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
Vector_Untransform(VECTOR_3D *__return_storage_ptr__,VECTOR_3D *param_1,MAT_3D *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar1 = param_1->x - (float)param_2->posit_x;
  fVar2 = param_1->y - (float)param_2->posit_y;
  fVar3 = param_1->z - (float)param_2->posit_z;
  __return_storage_ptr__->x =
       param_2->right_x * fVar1 + param_2->right_y * fVar2 + param_2->right_z * fVar3;
  __return_storage_ptr__->y = param_2->up_x * fVar1 + param_2->up_y * fVar2 + param_2->up_z * fVar3;
  __return_storage_ptr__->z =
       fVar3 * param_2->front_z + param_2->front_y * fVar2 + param_2->front_x * fVar1;
  return __return_storage_ptr__;
}
