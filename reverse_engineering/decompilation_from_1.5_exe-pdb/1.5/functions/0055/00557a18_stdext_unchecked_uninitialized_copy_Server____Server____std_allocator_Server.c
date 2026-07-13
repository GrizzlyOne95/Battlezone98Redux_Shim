/*
 * Entry: 00557a18
 * Name: stdext::unchecked_uninitialized_copy<Server_*_*,Server_*_*,std::allocator<Server_*>_>
 * Namespace: stdext
 * Signature: Server * * unchecked_uninitialized_copy<Server_*_*,Server_*_*,std::allocator<Server_*>_>(Server * * param_1, Server * * param_2, Server * * param_3, allocator<Server_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Server ** __cdecl
stdext::unchecked_uninitialized_copy<Server_*_*,Server_*_*,std::allocator<Server_*>_>
          (Server **param_1,Server **param_2,Server **param_3,allocator<Server_*> *param_4)

{
  Server **ppSVar1;
  
  ppSVar1 = std::_Uninit_copy<Server_*_*,Server_*_*,std::allocator<Server_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
