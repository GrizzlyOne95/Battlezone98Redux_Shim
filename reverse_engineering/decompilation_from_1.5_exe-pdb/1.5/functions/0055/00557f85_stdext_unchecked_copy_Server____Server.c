/*
 * Entry: 00557f85
 * Name: stdext::unchecked_copy<Server_*_*,Server_*_*>
 * Namespace: stdext
 * Signature: Server * * unchecked_copy<Server_*_*,Server_*_*>(Server * * param_1, Server * * param_2, Server * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Server ** __cdecl
stdext::unchecked_copy<Server_*_*,Server_*_*>(Server **param_1,Server **param_2,Server **param_3)

{
  Server **ppSVar1;
  
  ppSVar1 = std::_Copy_opt<Server_*_*,Server_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Scalar_ptr_iterator_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
