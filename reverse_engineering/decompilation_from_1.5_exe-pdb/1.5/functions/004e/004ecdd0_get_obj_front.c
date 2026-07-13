/*
 * Entry: 004ecdd0
 * Name: get_obj_front
 * Namespace: Global
 * Signature: VECTOR_3D * get_obj_front(VECTOR_3D * __return_storage_ptr__, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl get_obj_front(VECTOR_3D *__return_storage_ptr__,_OBJ76 *param_1)

{
  __return_storage_ptr__->x = (param_1->transform).front_x;
  __return_storage_ptr__->y = (param_1->transform).front_y;
  __return_storage_ptr__->z = (param_1->transform).front_z;
  return __return_storage_ptr__;
}
