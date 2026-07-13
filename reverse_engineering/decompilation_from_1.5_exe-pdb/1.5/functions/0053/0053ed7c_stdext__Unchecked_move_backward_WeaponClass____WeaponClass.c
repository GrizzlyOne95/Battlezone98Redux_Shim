/*
 * Entry: 0053ed7c
 * Name: stdext::_Unchecked_move_backward<WeaponClass_*_*,WeaponClass_*_*>
 * Namespace: stdext
 * Signature: WeaponClass * * _Unchecked_move_backward<WeaponClass_*_*,WeaponClass_*_*>(WeaponClass * * param_1, WeaponClass * * param_2, WeaponClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass ** __cdecl
stdext::_Unchecked_move_backward<WeaponClass_*_*,WeaponClass_*_*>
          (WeaponClass **param_1,WeaponClass **param_2,WeaponClass **param_3)

{
  WeaponClass **ppWVar1;
  
  ppWVar1 = std::
            _Move_backward_opt<WeaponClass_*_*,WeaponClass_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppWVar1;
}
