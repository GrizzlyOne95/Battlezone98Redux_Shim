/*
 * Entry: 0053ebf8
 * Name: std::_Move_backward_opt<WeaponClass_*_*,WeaponClass_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: WeaponClass * * _Move_backward_opt<WeaponClass_*_*,WeaponClass_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>(WeaponClass * * param_1, WeaponClass * * param_2, WeaponClass * * param_3, random_access_iterator_tag param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass ** __cdecl
std::
_Move_backward_opt<WeaponClass_*_*,WeaponClass_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
          (WeaponClass **param_1,WeaponClass **param_2,WeaponClass **param_3,
          random_access_iterator_tag param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  WeaponClass **ppWVar1;
  
  ppWVar1 = _Copy_backward_opt<WeaponClass_*_*,WeaponClass_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,param_4,(_Scalar_ptr_iterator_tag)0x0,
                       (_Range_checked_iterator_tag)0x0);
  return ppWVar1;
}
