/*
 * Entry: 00555982
 * Name: std::_Uninit_copy<PortData_*_*,PortData_*_*,std::allocator<PortData_*>_>
 * Namespace: std
 * Signature: PortData * * _Uninit_copy<PortData_*_*,PortData_*_*,std::allocator<PortData_*>_>(PortData * * param_1, PortData * * param_2, PortData * * param_3, allocator<PortData_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PortData ** __cdecl
std::_Uninit_copy<PortData_*_*,PortData_*_*,std::allocator<PortData_*>_>
          (PortData **param_1,PortData **param_2,PortData **param_3,allocator<PortData_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
