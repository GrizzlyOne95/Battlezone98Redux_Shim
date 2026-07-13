/*
 * Entry: 0053ec84
 * Name: std::_Vector_val<WeaponClass_*,std::allocator<WeaponClass_*>_>::~_Vector_val<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Namespace: std::_Vector_val<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: void ~_Vector_val<WeaponClass_*,std::allocator<WeaponClass_*>_>(_Vector_val<WeaponClass_*,std::allocator<WeaponClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<WeaponClass_*,std::allocator<WeaponClass_*>_>::
~_Vector_val<WeaponClass_*,std::allocator<WeaponClass_*>_>
          (_Vector_val<WeaponClass_*,std::allocator<WeaponClass_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
