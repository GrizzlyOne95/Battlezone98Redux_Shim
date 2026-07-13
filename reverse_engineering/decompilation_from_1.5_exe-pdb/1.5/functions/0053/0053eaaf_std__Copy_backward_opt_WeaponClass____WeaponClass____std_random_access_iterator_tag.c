/*
 * Entry: 0053eaaf
 * Name: std::_Copy_backward_opt<WeaponClass_*_*,WeaponClass_*_*,std::random_access_iterator_tag>
 * Namespace: std
 * Signature: WeaponClass * * _Copy_backward_opt<WeaponClass_*_*,WeaponClass_*_*,std::random_access_iterator_tag>(WeaponClass * * param_1, WeaponClass * * param_2, WeaponClass * * param_3, random_access_iterator_tag param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass ** __cdecl
std::_Copy_backward_opt<WeaponClass_*_*,WeaponClass_*_*,std::random_access_iterator_tag>
          (WeaponClass **param_1,WeaponClass **param_2,WeaponClass **param_3,
          random_access_iterator_tag param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (0 < iVar1) {
    memmove_s(param_3 + -iVar1,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + -iVar1;
}
