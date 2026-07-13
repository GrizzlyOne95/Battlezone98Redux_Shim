/*
 * Entry: 0053eef6
 * Name: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::_Umove<WeaponClass_*_*>
 * Namespace: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: WeaponClass * * _Umove<WeaponClass_*_*>(vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * this, WeaponClass * * param_1, WeaponClass * * param_2, WeaponClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass ** __thiscall
std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::_Umove<WeaponClass_*_*>
          (vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *this,WeaponClass **param_1,
          WeaponClass **param_2,WeaponClass **param_3)

{
  WeaponClass **ppWVar1;
  
  ppWVar1 = stdext::
            unchecked_uninitialized_copy<WeaponClass_*_*,WeaponClass_*_*,std::allocator<WeaponClass_*>_>
                      (param_1,param_2,param_3,(allocator<WeaponClass_*> *)&this->_padding_);
  return ppWVar1;
}
