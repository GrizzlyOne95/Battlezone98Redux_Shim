/*
 * Entry: 0053ede2
 * Name: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::~vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Namespace: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: void ~vector<WeaponClass_*,std::allocator<WeaponClass_*>_>(vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::
~vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
          (vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
