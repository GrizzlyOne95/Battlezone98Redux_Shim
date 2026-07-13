/*
 * Entry: 00413b60
 * Name: FrontVector
 * Namespace: Global
 * Signature: VECTOR_3D * FrontVector(VECTOR_3D * __return_storage_ptr__, MAT_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl FrontVector(VECTOR_3D *__return_storage_ptr__,MAT_3D *param_1)

{
  __return_storage_ptr__->x = param_1->front_x;
  __return_storage_ptr__->y = param_1->front_y;
  __return_storage_ptr__->z = param_1->front_z;
  return __return_storage_ptr__;
}
