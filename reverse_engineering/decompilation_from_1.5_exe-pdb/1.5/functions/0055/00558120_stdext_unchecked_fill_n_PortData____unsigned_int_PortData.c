/*
 * Entry: 00558120
 * Name: stdext::unchecked_fill_n<PortData_*_*,unsigned_int,PortData_*>
 * Namespace: stdext
 * Signature: void unchecked_fill_n<PortData_*_*,unsigned_int,PortData_*>(PortData * * param_1, uint param_2, PortData * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::unchecked_fill_n<PortData_*_*,unsigned_int,PortData_*>
          (PortData **param_1,uint param_2,PortData **param_3)

{
  std::_Fill_n<PortData_*_*,unsigned_int,PortData_*>
            (param_1,param_2,param_3,(random_access_iterator_tag)0x0,
             (_Range_checked_iterator_tag)0x0);
  return;
}
