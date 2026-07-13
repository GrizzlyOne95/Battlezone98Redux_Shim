/*
 * Entry: 0053e003
 * Name: Weapon::GetLeadPosition
 * Namespace: Weapon
 * Signature: VECTOR_3D * GetLeadPosition(Weapon * this, VECTOR_3D * __return_storage_ptr__, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __thiscall
Weapon::GetLeadPosition(Weapon *this,VECTOR_3D *__return_storage_ptr__,GameObject *param_1)

{
  float *pfVar1;
  
  pfVar1 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  __return_storage_ptr__->x = *pfVar1;
  __return_storage_ptr__->y = pfVar1[1];
  __return_storage_ptr__->z = pfVar1[2];
  return __return_storage_ptr__;
}
