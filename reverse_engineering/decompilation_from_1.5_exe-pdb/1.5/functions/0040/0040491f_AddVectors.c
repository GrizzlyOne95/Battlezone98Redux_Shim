/*
 * Entry: 0040491f
 * Name: AddVectors
 * Namespace: Global
 * Signature: VECTOR_3D * AddVectors(VECTOR_3D * __return_storage_ptr__, VECTOR_3D param_1, VECTOR_3D param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
AddVectors(VECTOR_3D *__return_storage_ptr__,VECTOR_3D param_1,VECTOR_3D param_2)

{
  __return_storage_ptr__->x = param_2.x + param_1.x;
  __return_storage_ptr__->y = param_2.y + param_1.y;
  __return_storage_ptr__->z = param_2.z + param_1.z;
  return __return_storage_ptr__;
}
