/*
 * Entry: 005583f1
 * Name: std::_Uninit_fill_n<Server_*_*,unsigned_int,Server_*,std::allocator<Server_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<Server_*_*,unsigned_int,Server_*,std::allocator<Server_*>_>(Server * * param_1, uint param_2, Server * * param_3, allocator<Server_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<Server_*_*,unsigned_int,Server_*,std::allocator<Server_*>_>
          (Server **param_1,uint param_2,Server **param_3,allocator<Server_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<Server_*_*,unsigned_int,Server_*>(param_1,param_2,param_3);
  return;
}
