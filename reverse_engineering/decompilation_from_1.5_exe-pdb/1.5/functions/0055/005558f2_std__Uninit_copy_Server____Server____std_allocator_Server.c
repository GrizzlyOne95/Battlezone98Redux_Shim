/*
 * Entry: 005558f2
 * Name: std::_Uninit_copy<Server_*_*,Server_*_*,std::allocator<Server_*>_>
 * Namespace: std
 * Signature: Server * * _Uninit_copy<Server_*_*,Server_*_*,std::allocator<Server_*>_>(Server * * param_1, Server * * param_2, Server * * param_3, allocator<Server_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Server ** __cdecl
std::_Uninit_copy<Server_*_*,Server_*_*,std::allocator<Server_*>_>
          (Server **param_1,Server **param_2,Server **param_3,allocator<Server_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
