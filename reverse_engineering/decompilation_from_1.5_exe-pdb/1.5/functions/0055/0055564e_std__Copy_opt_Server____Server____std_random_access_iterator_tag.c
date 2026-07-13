/*
 * Entry: 0055564e
 * Name: std::_Copy_opt<Server_*_*,Server_*_*,std::random_access_iterator_tag>
 * Namespace: std
 * Signature: Server * * _Copy_opt<Server_*_*,Server_*_*,std::random_access_iterator_tag>(Server * * param_1, Server * * param_2, Server * * param_3, random_access_iterator_tag param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Server ** __cdecl
std::_Copy_opt<Server_*_*,Server_*_*,std::random_access_iterator_tag>
          (Server **param_1,Server **param_2,Server **param_3,random_access_iterator_tag param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (0 < iVar1) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
