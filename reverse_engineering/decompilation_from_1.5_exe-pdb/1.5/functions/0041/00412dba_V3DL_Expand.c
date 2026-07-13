/*
 * Entry: 00412dba
 * Name: V3DL_Expand
 * Namespace: Global
 * Signature: VECTOR_3D_LONG * V3DL_Expand(VECTOR_3D_LONG * __return_storage_ptr__, VECTOR_3D param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D_LONG * __cdecl V3DL_Expand(VECTOR_3D_LONG *__return_storage_ptr__,VECTOR_3D param_1)

{
  __return_storage_ptr__->x = (double)param_1.x;
  __return_storage_ptr__->y = (double)param_1.y;
  __return_storage_ptr__->z = (double)param_1.z;
  return __return_storage_ptr__;
}
