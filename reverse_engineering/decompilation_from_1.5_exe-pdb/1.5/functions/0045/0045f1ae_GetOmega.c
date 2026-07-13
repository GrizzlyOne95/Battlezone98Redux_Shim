/*
 * Entry: 0045f1ae
 * Name: GetOmega
 * Namespace: Global
 * Signature: VECTOR_3D * GetOmega(VECTOR_3D * __return_storage_ptr__, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl GetOmega(VECTOR_3D *__return_storage_ptr__,int param_1)

{
  GameObject *pGVar1;
  VECTOR_3D *pVVar2;
  VECTOR_3D local_10;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    pVVar2 = &local_10;
    local_10.x = 0.0;
    local_10.y = 0.0;
    local_10.z = 0.0;
  }
  else {
    pVVar2 = &(pGVar1->euler).omega;
  }
  __return_storage_ptr__->x = pVVar2->x;
  __return_storage_ptr__->y = pVVar2->y;
  __return_storage_ptr__->z = pVVar2->z;
  return __return_storage_ptr__;
}
