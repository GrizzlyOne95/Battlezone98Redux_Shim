/*
 * Entry: 0053ee97
 * Name: stdext::_Unchecked_uninitialized_move<WeaponClass_*_*,WeaponClass_*_*,std::allocator<WeaponClass_*>_>
 * Namespace: stdext
 * Signature: WeaponClass * * _Unchecked_uninitialized_move<WeaponClass_*_*,WeaponClass_*_*,std::allocator<WeaponClass_*>_>(WeaponClass * * param_1, WeaponClass * * param_2, WeaponClass * * param_3, allocator<WeaponClass_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass ** __cdecl
stdext::
_Unchecked_uninitialized_move<WeaponClass_*_*,WeaponClass_*_*,std::allocator<WeaponClass_*>_>
          (WeaponClass **param_1,WeaponClass **param_2,WeaponClass **param_3,
          allocator<WeaponClass_*> *param_4)

{
  WeaponClass **ppWVar1;
  
  ppWVar1 = std::_Uninit_copy<WeaponClass_*_*,WeaponClass_*_*,std::allocator<WeaponClass_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppWVar1;
}
