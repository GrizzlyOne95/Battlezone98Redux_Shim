/*
 * Entry: 00404963
 * Name: AddMultVectors
 * Namespace: Global
 * Signature: VECTOR_3D * AddMultVectors(VECTOR_3D * __return_storage_ptr__, VECTOR_3D param_1, float param_2, VECTOR_3D param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
AddMultVectors(VECTOR_3D *__return_storage_ptr__,VECTOR_3D param_1,float param_2,VECTOR_3D param_3)

{
  __return_storage_ptr__->x = param_3.x * param_2 + param_1.x;
  __return_storage_ptr__->y = param_3.y * param_2 + param_1.y;
  __return_storage_ptr__->z = param_3.z * param_2 + param_1.z;
  return __return_storage_ptr__;
}
