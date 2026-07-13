/*
 * Entry: 00558177
 * Name: std::_Uninit_move<Player_*_*,Player_*_*,std::allocator<Player_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: Player * * _Uninit_move<Player_*_*,Player_*_*,std::allocator<Player_*>,std::_Undefined_move_tag>(Player * * param_1, Player * * param_2, Player * * param_3, allocator<Player_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Player ** __cdecl
std::_Uninit_move<Player_*_*,Player_*_*,std::allocator<Player_*>,std::_Undefined_move_tag>
          (Player **param_1,Player **param_2,Player **param_3,allocator<Player_*> *param_4,
          _Undefined_move_tag param_5,_Range_checked_iterator_tag param_6)

{
  Player **ppPVar1;
  
  ppPVar1 = stdext::unchecked_uninitialized_copy<Player_*_*,Player_*_*,std::allocator<Player_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppPVar1;
}
