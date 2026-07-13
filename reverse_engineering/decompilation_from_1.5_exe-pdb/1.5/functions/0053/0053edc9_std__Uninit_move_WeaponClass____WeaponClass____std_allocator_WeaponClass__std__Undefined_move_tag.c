/*
 * Entry: 0053edc9
 * Name: std::_Uninit_move<WeaponClass_*_*,WeaponClass_*_*,std::allocator<WeaponClass_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: WeaponClass * * _Uninit_move<WeaponClass_*_*,WeaponClass_*_*,std::allocator<WeaponClass_*>,std::_Undefined_move_tag>(WeaponClass * * param_1, WeaponClass * * param_2, WeaponClass * * param_3, allocator<WeaponClass_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass ** __cdecl
std::
_Uninit_move<WeaponClass_*_*,WeaponClass_*_*,std::allocator<WeaponClass_*>,std::_Undefined_move_tag>
          (WeaponClass **param_1,WeaponClass **param_2,WeaponClass **param_3,
          allocator<WeaponClass_*> *param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  WeaponClass **ppWVar1;
  
  ppWVar1 = stdext::
            unchecked_uninitialized_copy<WeaponClass_*_*,WeaponClass_*_*,std::allocator<WeaponClass_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppWVar1;
}
