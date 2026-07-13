/*
 * Entry: 00459f5e
 * Name: CombineVectors
 * Namespace: Global
 * Signature: VECTOR_3D * CombineVectors(VECTOR_3D * __return_storage_ptr__, float param_1, VECTOR_3D param_2, float param_3, VECTOR_3D param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
CombineVectors(VECTOR_3D *__return_storage_ptr__,float param_1,VECTOR_3D param_2,float param_3,
              VECTOR_3D param_4)

{
  __return_storage_ptr__->x = param_4.x * param_3 + param_2.x * param_1;
  __return_storage_ptr__->y = param_4.y * param_3 + param_2.y * param_1;
  __return_storage_ptr__->z = param_4.z * param_3 + param_2.z * param_1;
  return __return_storage_ptr__;
}
