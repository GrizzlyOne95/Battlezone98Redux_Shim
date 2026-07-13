/*
 * Entry: 00557a68
 * Name: stdext::unchecked_uninitialized_copy<Player_*_*,Player_*_*,std::allocator<Player_*>_>
 * Namespace: stdext
 * Signature: Player * * unchecked_uninitialized_copy<Player_*_*,Player_*_*,std::allocator<Player_*>_>(Player * * param_1, Player * * param_2, Player * * param_3, allocator<Player_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Player ** __cdecl
stdext::unchecked_uninitialized_copy<Player_*_*,Player_*_*,std::allocator<Player_*>_>
          (Player **param_1,Player **param_2,Player **param_3,allocator<Player_*> *param_4)

{
  Player **ppPVar1;
  
  ppPVar1 = std::_Uninit_copy<Player_*_*,Player_*_*,std::allocator<Player_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppPVar1;
}
