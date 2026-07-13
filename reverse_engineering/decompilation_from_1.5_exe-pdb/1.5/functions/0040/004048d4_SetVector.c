/*
 * Entry: 004048d4
 * Name: SetVector
 * Namespace: Global
 * Signature: VECTOR_3D * SetVector(VECTOR_3D * __return_storage_ptr__, float param_1, float param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
SetVector(VECTOR_3D *__return_storage_ptr__,float param_1,float param_2,float param_3)

{
  __return_storage_ptr__->x = param_1;
  __return_storage_ptr__->y = param_2;
  __return_storage_ptr__->z = param_3;
  return __return_storage_ptr__;
}
