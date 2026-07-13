/*
 * Entry: 0041070e
 * Name: Vec3D_From2D
 * Namespace: Global
 * Signature: VECTOR_3D * Vec3D_From2D(VECTOR_3D * __return_storage_ptr__, VECTOR_2D param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl Vec3D_From2D(VECTOR_3D *__return_storage_ptr__,VECTOR_2D param_1)

{
  __return_storage_ptr__->x = param_1.x;
  __return_storage_ptr__->y = 0.0;
  __return_storage_ptr__->z = param_1.z;
  return __return_storage_ptr__;
}
