/*
 * Entry: 004049eb
 * Name: GetPositionV
 * Namespace: Global
 * Signature: VECTOR_3D * GetPositionV(VECTOR_3D * __return_storage_ptr__, MAT_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl GetPositionV(VECTOR_3D *__return_storage_ptr__,MAT_3D *param_1)

{
  __return_storage_ptr__->x = (float)param_1->posit_x;
  __return_storage_ptr__->y = (float)param_1->posit_y;
  __return_storage_ptr__->z = (float)param_1->posit_z;
  return __return_storage_ptr__;
}
