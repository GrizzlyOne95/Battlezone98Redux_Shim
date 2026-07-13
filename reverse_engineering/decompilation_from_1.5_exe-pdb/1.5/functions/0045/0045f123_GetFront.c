/*
 * Entry: 0045f123
 * Name: GetFront
 * Namespace: Global
 * Signature: VECTOR_3D * GetFront(VECTOR_3D * __return_storage_ptr__, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl GetFront(VECTOR_3D *__return_storage_ptr__,int param_1)

{
  GameObject *pGVar1;
  float *pfVar2;
  float local_10 [3];
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    pfVar2 = local_10;
    local_10[0] = 0.0;
    local_10[1] = 0.0;
    local_10[2] = 0.0;
  }
  else {
    pfVar2 = &(pGVar1->obj->transform).front_x;
  }
  __return_storage_ptr__->x = *pfVar2;
  __return_storage_ptr__->y = pfVar2[1];
  __return_storage_ptr__->z = pfVar2[2];
  return __return_storage_ptr__;
}
