/*
 * Entry: 004adf91
 * Name: stdext::_Unchecked_move_backward<Scanner_*_*,Scanner_*_*>
 * Namespace: stdext
 * Signature: Scanner * * _Unchecked_move_backward<Scanner_*_*,Scanner_*_*>(Scanner * * param_1, Scanner * * param_2, Scanner * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scanner ** __cdecl
stdext::_Unchecked_move_backward<Scanner_*_*,Scanner_*_*>
          (Scanner **param_1,Scanner **param_2,Scanner **param_3)

{
  Scanner **ppSVar1;
  
  ppSVar1 = std::
            _Move_backward_opt<Scanner_*_*,Scanner_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
