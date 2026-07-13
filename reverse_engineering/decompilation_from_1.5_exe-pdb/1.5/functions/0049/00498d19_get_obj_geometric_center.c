/*
 * Entry: 00498d19
 * Name: get_obj_geometric_center
 * Namespace: Global
 * Signature: VECTOR_3D * get_obj_geometric_center(VECTOR_3D * __return_storage_ptr__, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl get_obj_geometric_center(VECTOR_3D *__return_storage_ptr__,_OBJ76 *param_1)

{
  VECTOR_3D local_10;
  
  get_obj_bounding_box(param_1,__return_storage_ptr__,&local_10);
  __return_storage_ptr__->x = (__return_storage_ptr__->x + local_10.x) * 0.5;
  __return_storage_ptr__->y = (__return_storage_ptr__->y + local_10.y) * 0.5;
  __return_storage_ptr__->z = (__return_storage_ptr__->z + local_10.z) * 0.5;
  return __return_storage_ptr__;
}
