/*
 * Entry: 004ecb70
 * Name: get_directional_vector
 * Namespace: Global
 * Signature: VECTOR_3D * get_directional_vector(VECTOR_3D * __return_storage_ptr__, _OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
get_directional_vector(VECTOR_3D *__return_storage_ptr__,_OBJ76 *param_1,_OBJ76 *param_2)

{
  VECTOR_3D *pVVar1;
  VECTOR_3D local_10;
  
  pVVar1 = ObjDB_GetDirectionalVector(&local_10,param_1,param_2);
  __return_storage_ptr__->x = pVVar1->x;
  __return_storage_ptr__->y = pVVar1->y;
  __return_storage_ptr__->z = pVVar1->z;
  return __return_storage_ptr__;
}
