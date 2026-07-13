/*
 * Entry: 0055582b
 * Name: std::_Copy_backward_opt<PortData_*_*,PortData_*_*,std::random_access_iterator_tag>
 * Namespace: std
 * Signature: PortData * * _Copy_backward_opt<PortData_*_*,PortData_*_*,std::random_access_iterator_tag>(PortData * * param_1, PortData * * param_2, PortData * * param_3, random_access_iterator_tag param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PortData ** __cdecl
std::_Copy_backward_opt<PortData_*_*,PortData_*_*,std::random_access_iterator_tag>
          (PortData **param_1,PortData **param_2,PortData **param_3,
          random_access_iterator_tag param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (0 < iVar1) {
    memmove_s(param_3 + -iVar1,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + -iVar1;
}
