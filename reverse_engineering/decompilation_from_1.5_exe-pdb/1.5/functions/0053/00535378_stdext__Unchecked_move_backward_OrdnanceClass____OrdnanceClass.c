/*
 * Entry: 00535378
 * Name: stdext::_Unchecked_move_backward<OrdnanceClass_*_*,OrdnanceClass_*_*>
 * Namespace: stdext
 * Signature: OrdnanceClass * * _Unchecked_move_backward<OrdnanceClass_*_*,OrdnanceClass_*_*>(OrdnanceClass * * param_1, OrdnanceClass * * param_2, OrdnanceClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass ** __cdecl
stdext::_Unchecked_move_backward<OrdnanceClass_*_*,OrdnanceClass_*_*>
          (OrdnanceClass **param_1,OrdnanceClass **param_2,OrdnanceClass **param_3)

{
  OrdnanceClass **ppOVar1;
  
  ppOVar1 = std::
            _Move_backward_opt<OrdnanceClass_*_*,OrdnanceClass_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppOVar1;
}
