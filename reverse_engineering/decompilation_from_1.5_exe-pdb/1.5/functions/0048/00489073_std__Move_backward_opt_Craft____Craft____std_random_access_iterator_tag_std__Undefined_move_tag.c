/*
 * Entry: 00489073
 * Name: std::_Move_backward_opt<Craft_*_*,Craft_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: Craft * * _Move_backward_opt<Craft_*_*,Craft_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>(Craft * * param_1, Craft * * param_2, Craft * * param_3, random_access_iterator_tag param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Craft ** __cdecl
std::
_Move_backward_opt<Craft_*_*,Craft_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
          (Craft **param_1,Craft **param_2,Craft **param_3,random_access_iterator_tag param_4,
          _Undefined_move_tag param_5,_Range_checked_iterator_tag param_6)

{
  Craft **ppCVar1;
  
  ppCVar1 = _Copy_backward_opt<Craft_*_*,Craft_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,param_4,(_Scalar_ptr_iterator_tag)0x0,
                       (_Range_checked_iterator_tag)0x0);
  return ppCVar1;
}
