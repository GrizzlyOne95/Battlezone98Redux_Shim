/*
 * Entry: 0053ecf5
 * Name: std::_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>::_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Namespace: std::_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: _Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> * _Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>(_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> * this, WeaponClass * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> * __thiscall
std::_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>::
_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>
          (_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> *this,
          WeaponClass **param_1,_Container_base_aux *param_2)

{
  _Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>::
  _Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>
            ((_Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> *)this,param_1,
             param_2);
  return this;
}
