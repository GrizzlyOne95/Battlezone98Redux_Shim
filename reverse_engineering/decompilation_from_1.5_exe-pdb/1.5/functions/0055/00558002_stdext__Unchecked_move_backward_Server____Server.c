/*
 * Entry: 00558002
 * Name: stdext::_Unchecked_move_backward<Server_*_*,Server_*_*>
 * Namespace: stdext
 * Signature: Server * * _Unchecked_move_backward<Server_*_*,Server_*_*>(Server * * param_1, Server * * param_2, Server * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Server ** __cdecl
stdext::_Unchecked_move_backward<Server_*_*,Server_*_*>
          (Server **param_1,Server **param_2,Server **param_3)

{
  Server **ppSVar1;
  
  ppSVar1 = std::
            _Move_backward_opt<Server_*_*,Server_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
