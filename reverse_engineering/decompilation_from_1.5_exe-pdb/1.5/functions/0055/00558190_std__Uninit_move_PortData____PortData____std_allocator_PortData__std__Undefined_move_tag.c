/*
 * Entry: 00558190
 * Name: std::_Uninit_move<PortData_*_*,PortData_*_*,std::allocator<PortData_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: PortData * * _Uninit_move<PortData_*_*,PortData_*_*,std::allocator<PortData_*>,std::_Undefined_move_tag>(PortData * * param_1, PortData * * param_2, PortData * * param_3, allocator<PortData_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PortData ** __cdecl
std::_Uninit_move<PortData_*_*,PortData_*_*,std::allocator<PortData_*>,std::_Undefined_move_tag>
          (PortData **param_1,PortData **param_2,PortData **param_3,allocator<PortData_*> *param_4,
          _Undefined_move_tag param_5,_Range_checked_iterator_tag param_6)

{
  PortData **ppPVar1;
  
  ppPVar1 = stdext::
            unchecked_uninitialized_copy<PortData_*_*,PortData_*_*,std::allocator<PortData_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppPVar1;
}
