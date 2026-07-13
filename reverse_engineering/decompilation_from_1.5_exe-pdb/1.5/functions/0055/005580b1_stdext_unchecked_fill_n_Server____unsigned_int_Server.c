/*
 * Entry: 005580b1
 * Name: stdext::unchecked_fill_n<Server_*_*,unsigned_int,Server_*>
 * Namespace: stdext
 * Signature: void unchecked_fill_n<Server_*_*,unsigned_int,Server_*>(Server * * param_1, uint param_2, Server * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::unchecked_fill_n<Server_*_*,unsigned_int,Server_*>
          (Server **param_1,uint param_2,Server **param_3)

{
  std::_Fill_n<Server_*_*,unsigned_int,Server_*>
            (param_1,param_2,param_3,(random_access_iterator_tag)0x0,
             (_Range_checked_iterator_tag)0x0);
  return;
}
