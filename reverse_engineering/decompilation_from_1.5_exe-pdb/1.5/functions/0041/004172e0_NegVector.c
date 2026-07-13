/*
 * Entry: 004172e0
 * Name: NegVector
 * Namespace: Global
 * Signature: VECTOR_3D * NegVector(VECTOR_3D * __return_storage_ptr__, VECTOR_3D param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl NegVector(VECTOR_3D *__return_storage_ptr__,VECTOR_3D param_1)

{
  __return_storage_ptr__->x = -param_1.x;
  __return_storage_ptr__->y = -param_1.y;
  __return_storage_ptr__->z = -param_1.z;
  return __return_storage_ptr__;
}
