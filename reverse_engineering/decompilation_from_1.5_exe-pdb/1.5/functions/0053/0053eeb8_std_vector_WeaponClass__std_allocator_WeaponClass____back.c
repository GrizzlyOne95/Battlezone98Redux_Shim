/*
 * Entry: 0053eeb8
 * Name: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::back
 * Namespace: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: WeaponClass * * back(vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass ** __thiscall
std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::back
          (vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *this)

{
  WeaponClass **ppWVar1;
  _Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> _Var2;
  undefined1 local_14 [8];
  _Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> local_c;
  
  _Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>::
  _Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>
            (&local_c,this->_Mylast,(_Container_base_aux *)this);
  _Var2 = _Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>::operator-
                    ((_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> *)&local_c,
                     (int)local_14);
  ppWVar1 = _Vector_const_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>::operator*
                      (_Var2._0_4_);
  return ppWVar1;
}
