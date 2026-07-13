/*
 * Entry: 0053eb04
 * Name: std::_Uninit_copy<WeaponClass_*_*,WeaponClass_*_*,std::allocator<WeaponClass_*>_>
 * Namespace: std
 * Signature: WeaponClass * * _Uninit_copy<WeaponClass_*_*,WeaponClass_*_*,std::allocator<WeaponClass_*>_>(WeaponClass * * param_1, WeaponClass * * param_2, WeaponClass * * param_3, allocator<WeaponClass_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass ** __cdecl
std::_Uninit_copy<WeaponClass_*_*,WeaponClass_*_*,std::allocator<WeaponClass_*>_>
          (WeaponClass **param_1,WeaponClass **param_2,WeaponClass **param_3,
          allocator<WeaponClass_*> *param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
