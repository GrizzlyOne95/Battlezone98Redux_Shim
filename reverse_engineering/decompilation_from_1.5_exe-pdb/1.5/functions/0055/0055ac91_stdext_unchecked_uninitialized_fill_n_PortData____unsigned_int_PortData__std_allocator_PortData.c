/*
 * Entry: 0055ac91
 * Name: stdext::unchecked_uninitialized_fill_n<PortData_*_*,unsigned_int,PortData_*,std::allocator<PortData_*>_>
 * Namespace: stdext
 * Signature: void unchecked_uninitialized_fill_n<PortData_*_*,unsigned_int,PortData_*,std::allocator<PortData_*>_>(PortData * * param_1, uint param_2, PortData * * param_3, allocator<PortData_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::
unchecked_uninitialized_fill_n<PortData_*_*,unsigned_int,PortData_*,std::allocator<PortData_*>_>
          (PortData **param_1,uint param_2,PortData **param_3,allocator<PortData_*> *param_4)

{
  unchecked_fill_n<PortData_*_*,unsigned_int,PortData_*>(param_1,param_2,param_3);
  return;
}
