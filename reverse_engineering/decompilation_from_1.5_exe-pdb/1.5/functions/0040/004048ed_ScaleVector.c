/*
 * Entry: 004048ed
 * Name: ScaleVector
 * Namespace: Global
 * Signature: VECTOR_3D * ScaleVector(VECTOR_3D * __return_storage_ptr__, float param_1, VECTOR_3D param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl ScaleVector(VECTOR_3D *__return_storage_ptr__,float param_1,VECTOR_3D param_2)

{
  __return_storage_ptr__->x = param_2.x * param_1;
  __return_storage_ptr__->y = param_2.y * param_1;
  __return_storage_ptr__->z = param_2.z * param_1;
  return __return_storage_ptr__;
}
