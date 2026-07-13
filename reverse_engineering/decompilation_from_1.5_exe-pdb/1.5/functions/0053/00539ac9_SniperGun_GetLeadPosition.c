/*
 * Entry: 00539ac9
 * Name: SniperGun::GetLeadPosition
 * Namespace: SniperGun
 * Signature: VECTOR_3D * GetLeadPosition(SniperGun * this, VECTOR_3D * __return_storage_ptr__, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __thiscall
SniperGun::GetLeadPosition(SniperGun *this,VECTOR_3D *__return_storage_ptr__,GameObject *param_1)

{
  char cVar1;
  VECTOR_3D *pVVar2;
  VECTOR_3D local_10;
  
  cVar1 = (**(code **)(param_1->_padding_ + 0x14))();
  if (cVar1 == '\0') {
    pVVar2 = (VECTOR_3D *)(**(code **)(param_1->_padding_ + 0xc))();
  }
  else {
    pVVar2 = obj_get_world_position(&local_10,*(_OBJ76 **)(param_1[1]._padding_ + 0xf4));
  }
  __return_storage_ptr__->x = pVVar2->x;
  __return_storage_ptr__->y = pVVar2->y;
  __return_storage_ptr__->z = pVVar2->z;
  return __return_storage_ptr__;
}
