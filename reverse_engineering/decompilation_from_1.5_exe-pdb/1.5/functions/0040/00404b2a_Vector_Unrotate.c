/*
 * Entry: 00404b2a
 * Name: Vector_Unrotate
 * Namespace: Global
 * Signature: VECTOR_3D * Vector_Unrotate(VECTOR_3D * __return_storage_ptr__, VECTOR_3D * param_1, MAT_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
Vector_Unrotate(VECTOR_3D *__return_storage_ptr__,VECTOR_3D *param_1,MAT_3D *param_2)

{
  __return_storage_ptr__->x =
       param_1->x * param_2->right_x + param_2->right_z * param_1->z + param_2->right_y * param_1->y
  ;
  __return_storage_ptr__->y =
       param_2->up_z * param_1->z + param_2->up_x * param_1->x + param_2->up_y * param_1->y;
  __return_storage_ptr__->z =
       param_2->front_z * param_1->z + param_2->front_x * param_1->x + param_2->front_y * param_1->y
  ;
  return __return_storage_ptr__;
}
