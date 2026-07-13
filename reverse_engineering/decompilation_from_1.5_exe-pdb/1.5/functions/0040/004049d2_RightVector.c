/*
 * Entry: 004049d2
 * Name: RightVector
 * Namespace: Global
 * Signature: VECTOR_3D * RightVector(VECTOR_3D * __return_storage_ptr__, MAT_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl RightVector(VECTOR_3D *__return_storage_ptr__,MAT_3D *param_1)

{
  __return_storage_ptr__->x = param_1->right_x;
  __return_storage_ptr__->y = param_1->right_y;
  __return_storage_ptr__->z = param_1->right_z;
  return __return_storage_ptr__;
}
