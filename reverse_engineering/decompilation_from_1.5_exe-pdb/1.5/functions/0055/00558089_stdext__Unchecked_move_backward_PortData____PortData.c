/*
 * Entry: 00558089
 * Name: stdext::_Unchecked_move_backward<PortData_*_*,PortData_*_*>
 * Namespace: stdext
 * Signature: PortData * * _Unchecked_move_backward<PortData_*_*,PortData_*_*>(PortData * * param_1, PortData * * param_2, PortData * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PortData ** __cdecl
stdext::_Unchecked_move_backward<PortData_*_*,PortData_*_*>
          (PortData **param_1,PortData **param_2,PortData **param_3)

{
  PortData **ppPVar1;
  
  ppPVar1 = std::
            _Move_backward_opt<PortData_*_*,PortData_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppPVar1;
}
