/*
 * Entry: 00557fd5
 * Name: stdext::unchecked_copy<Player_*_*,Player_*_*>
 * Namespace: stdext
 * Signature: Player * * unchecked_copy<Player_*_*,Player_*_*>(Player * * param_1, Player * * param_2, Player * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Player ** __cdecl
stdext::unchecked_copy<Player_*_*,Player_*_*>(Player **param_1,Player **param_2,Player **param_3)

{
  Player **ppPVar1;
  
  ppPVar1 = std::_Copy_opt<Player_*_*,Player_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Scalar_ptr_iterator_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppPVar1;
}
