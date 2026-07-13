/*
 * Entry: 005580fb
 * Name: stdext::unchecked_fill_n<Player_*_*,unsigned_int,Player_*>
 * Namespace: stdext
 * Signature: void unchecked_fill_n<Player_*_*,unsigned_int,Player_*>(Player * * param_1, uint param_2, Player * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::unchecked_fill_n<Player_*_*,unsigned_int,Player_*>
          (Player **param_1,uint param_2,Player **param_3)

{
  std::_Fill_n<Player_*_*,unsigned_int,Player_*>
            (param_1,param_2,param_3,(random_access_iterator_tag)0x0,
             (_Range_checked_iterator_tag)0x0);
  return;
}
