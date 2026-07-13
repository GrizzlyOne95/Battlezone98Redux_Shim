/*
 * Entry: 00558145
 * Name: std::_Uninit_move<Server_*_*,Server_*_*,std::allocator<Server_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: Server * * _Uninit_move<Server_*_*,Server_*_*,std::allocator<Server_*>,std::_Undefined_move_tag>(Server * * param_1, Server * * param_2, Server * * param_3, allocator<Server_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Server ** __cdecl
std::_Uninit_move<Server_*_*,Server_*_*,std::allocator<Server_*>,std::_Undefined_move_tag>
          (Server **param_1,Server **param_2,Server **param_3,allocator<Server_*> *param_4,
          _Undefined_move_tag param_5,_Range_checked_iterator_tag param_6)

{
  Server **ppSVar1;
  
  ppSVar1 = stdext::unchecked_uninitialized_copy<Server_*_*,Server_*_*,std::allocator<Server_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppSVar1;
}
