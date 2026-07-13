/*
 * Entry: 0040d418
 * Name: V3DL_GetPosition
 * Namespace: Global
 * Signature: VECTOR_3D_LONG * V3DL_GetPosition(VECTOR_3D_LONG * __return_storage_ptr__, MAT_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D_LONG * __cdecl V3DL_GetPosition(VECTOR_3D_LONG *__return_storage_ptr__,MAT_3D *param_1)

{
  __return_storage_ptr__->x = param_1->posit_x;
  __return_storage_ptr__->y = param_1->posit_y;
  __return_storage_ptr__->z = param_1->posit_z;
  return __return_storage_ptr__;
}
