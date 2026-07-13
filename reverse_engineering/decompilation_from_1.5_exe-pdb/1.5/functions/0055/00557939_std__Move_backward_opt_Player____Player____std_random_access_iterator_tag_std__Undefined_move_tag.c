/*
 * Entry: 00557939
 * Name: std::_Move_backward_opt<Player_*_*,Player_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: Player * * _Move_backward_opt<Player_*_*,Player_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>(Player * * param_1, Player * * param_2, Player * * param_3, random_access_iterator_tag param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Player ** __cdecl
std::
_Move_backward_opt<Player_*_*,Player_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
          (Player **param_1,Player **param_2,Player **param_3,random_access_iterator_tag param_4,
          _Undefined_move_tag param_5,_Range_checked_iterator_tag param_6)

{
  Player **ppPVar1;
  
  ppPVar1 = _Copy_backward_opt<Player_*_*,Player_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,param_4,(_Scalar_ptr_iterator_tag)0x0,
                       (_Range_checked_iterator_tag)0x0);
  return ppPVar1;
}
