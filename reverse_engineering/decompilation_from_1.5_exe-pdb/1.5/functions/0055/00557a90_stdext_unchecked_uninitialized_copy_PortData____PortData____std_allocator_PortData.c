/*
 * Entry: 00557a90
 * Name: stdext::unchecked_uninitialized_copy<PortData_*_*,PortData_*_*,std::allocator<PortData_*>_>
 * Namespace: stdext
 * Signature: PortData * * unchecked_uninitialized_copy<PortData_*_*,PortData_*_*,std::allocator<PortData_*>_>(PortData * * param_1, PortData * * param_2, PortData * * param_3, allocator<PortData_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PortData ** __cdecl
stdext::unchecked_uninitialized_copy<PortData_*_*,PortData_*_*,std::allocator<PortData_*>_>
          (PortData **param_1,PortData **param_2,PortData **param_3,allocator<PortData_*> *param_4)

{
  PortData **ppPVar1;
  
  ppPVar1 = std::_Uninit_copy<PortData_*_*,PortData_*_*,std::allocator<PortData_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppPVar1;
}
