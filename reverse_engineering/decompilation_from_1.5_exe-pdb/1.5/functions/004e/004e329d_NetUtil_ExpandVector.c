/*
 * Entry: 004e329d
 * Name: NetUtil_ExpandVector
 * Namespace: Global
 * Signature: VECTOR_3D * NetUtil_ExpandVector(VECTOR_3D * __return_storage_ptr__, REDUCED_VEC param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl NetUtil_ExpandVector(VECTOR_3D *__return_storage_ptr__,REDUCED_VEC param_1)

{
  __return_storage_ptr__->x = (float)(int)(short)param_1.x * 0.00390625;
  __return_storage_ptr__->y = (float)(int)(short)param_1.y * 0.00390625;
  __return_storage_ptr__->z = (float)(int)(short)param_1.z * 0.00390625;
  return __return_storage_ptr__;
}
