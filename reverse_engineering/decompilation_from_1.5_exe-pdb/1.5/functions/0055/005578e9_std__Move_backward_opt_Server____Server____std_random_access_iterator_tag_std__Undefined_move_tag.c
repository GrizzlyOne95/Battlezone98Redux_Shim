/*
 * Entry: 005578e9
 * Name: std::_Move_backward_opt<Server_*_*,Server_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: Server * * _Move_backward_opt<Server_*_*,Server_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>(Server * * param_1, Server * * param_2, Server * * param_3, random_access_iterator_tag param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Server ** __cdecl
std::
_Move_backward_opt<Server_*_*,Server_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
          (Server **param_1,Server **param_2,Server **param_3,random_access_iterator_tag param_4,
          _Undefined_move_tag param_5,_Range_checked_iterator_tag param_6)

{
  Server **ppSVar1;
  
  ppSVar1 = _Copy_backward_opt<Server_*_*,Server_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,param_4,(_Scalar_ptr_iterator_tag)0x0,
                       (_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
