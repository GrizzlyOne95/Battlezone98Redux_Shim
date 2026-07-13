/*
 * Entry: 00417734
 * Name: UpVector
 * Namespace: Global
 * Signature: VECTOR_3D * UpVector(VECTOR_3D * __return_storage_ptr__, MAT_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl UpVector(VECTOR_3D *__return_storage_ptr__,MAT_3D *param_1)

{
  __return_storage_ptr__->x = param_1->up_x;
  __return_storage_ptr__->y = param_1->up_y;
  __return_storage_ptr__->z = param_1->up_z;
  return __return_storage_ptr__;
}
