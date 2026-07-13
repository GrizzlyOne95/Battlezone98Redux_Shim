/*
 * Entry: 0055805c
 * Name: stdext::_Unchecked_move_backward<Player_*_*,Player_*_*>
 * Namespace: stdext
 * Signature: Player * * _Unchecked_move_backward<Player_*_*,Player_*_*>(Player * * param_1, Player * * param_2, Player * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Player ** __cdecl
stdext::_Unchecked_move_backward<Player_*_*,Player_*_*>
          (Player **param_1,Player **param_2,Player **param_3)

{
  Player **ppPVar1;
  
  ppPVar1 = std::
            _Move_backward_opt<Player_*_*,Player_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppPVar1;
}
