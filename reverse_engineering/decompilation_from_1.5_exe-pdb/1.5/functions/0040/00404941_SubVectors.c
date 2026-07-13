/*
 * Entry: 00404941
 * Name: SubVectors
 * Namespace: Global
 * Signature: VECTOR_3D * SubVectors(VECTOR_3D * __return_storage_ptr__, VECTOR_3D param_1, VECTOR_3D param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
SubVectors(VECTOR_3D *__return_storage_ptr__,VECTOR_3D param_1,VECTOR_3D param_2)

{
  __return_storage_ptr__->x = param_1.x - param_2.x;
  __return_storage_ptr__->y = param_1.y - param_2.y;
  __return_storage_ptr__->z = param_1.z - param_2.z;
  return __return_storage_ptr__;
}
