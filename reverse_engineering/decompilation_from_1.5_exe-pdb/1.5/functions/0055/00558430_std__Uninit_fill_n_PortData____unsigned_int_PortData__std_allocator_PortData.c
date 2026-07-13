/*
 * Entry: 00558430
 * Name: std::_Uninit_fill_n<PortData_*_*,unsigned_int,PortData_*,std::allocator<PortData_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<PortData_*_*,unsigned_int,PortData_*,std::allocator<PortData_*>_>(PortData * * param_1, uint param_2, PortData * * param_3, allocator<PortData_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<PortData_*_*,unsigned_int,PortData_*,std::allocator<PortData_*>_>
          (PortData **param_1,uint param_2,PortData **param_3,allocator<PortData_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<PortData_*_*,unsigned_int,PortData_*>(param_1,param_2,param_3);
  return;
}
