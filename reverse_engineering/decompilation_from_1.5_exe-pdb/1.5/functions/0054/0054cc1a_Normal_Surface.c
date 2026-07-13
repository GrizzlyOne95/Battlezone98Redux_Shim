/*
 * Entry: 0054cc1a
 * Name: Normal_Surface
 * Namespace: Global
 * Signature: VECTOR_3D * Normal_Surface(VECTOR_3D * __return_storage_ptr__, VECTOR_3D * param_1, VECTOR_3D * param_2, VECTOR_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
Normal_Surface(VECTOR_3D *__return_storage_ptr__,VECTOR_3D *param_1,VECTOR_3D *param_2,
              VECTOR_3D *param_3)

{
  VECTOR_3D *pVVar1;
  VECTOR_3D local_28;
  VECTOR_3D local_1c;
  VECTOR_3D local_10;
  
  local_1c.x = param_2->x - param_1->x;
  local_1c.y = param_2->y - param_1->y;
  local_1c.z = param_2->z - param_1->z;
  local_10.x = param_3->x - param_1->x;
  local_10.y = param_3->y - param_1->y;
  local_10.z = param_3->z - param_1->z;
  pVVar1 = Cross_Product(&local_28,&local_1c,&local_10);
  __return_storage_ptr__->x = pVVar1->x;
  __return_storage_ptr__->y = pVVar1->y;
  __return_storage_ptr__->z = pVVar1->z;
  pVVar1 = Normalize_Vector(&local_28,__return_storage_ptr__);
  __return_storage_ptr__->x = pVVar1->x;
  __return_storage_ptr__->y = pVVar1->y;
  __return_storage_ptr__->z = pVVar1->z;
  return __return_storage_ptr__;
}
