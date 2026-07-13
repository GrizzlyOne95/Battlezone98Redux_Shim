/*
 * Entry: 004ecdb6
 * Name: get_obj_loc
 * Namespace: Global
 * Signature: VECTOR_3D * get_obj_loc(VECTOR_3D * __return_storage_ptr__, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl get_obj_loc(VECTOR_3D *__return_storage_ptr__,_OBJ76 *param_1)

{
  __return_storage_ptr__->x = (float)(param_1->transform).posit_x;
  __return_storage_ptr__->y = (float)(param_1->transform).posit_y;
  __return_storage_ptr__->z = (float)(param_1->transform).posit_z;
  return __return_storage_ptr__;
}
