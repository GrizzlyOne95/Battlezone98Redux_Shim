/*
 * Entry: 0053eb83
 * Name: std::_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>::operator++
 * Namespace: std::_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: _Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> * operator++(_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> * __thiscall
std::_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>::operator++
          (_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> *this)

{
  _Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>::operator++
            ((_Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> *)this);
  return this;
}
