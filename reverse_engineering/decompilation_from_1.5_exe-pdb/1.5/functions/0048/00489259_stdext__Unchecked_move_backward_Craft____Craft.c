/*
 * Entry: 00489259
 * Name: stdext::_Unchecked_move_backward<Craft_*_*,Craft_*_*>
 * Namespace: stdext
 * Signature: Craft * * _Unchecked_move_backward<Craft_*_*,Craft_*_*>(Craft * * param_1, Craft * * param_2, Craft * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Craft ** __cdecl
stdext::_Unchecked_move_backward<Craft_*_*,Craft_*_*>
          (Craft **param_1,Craft **param_2,Craft **param_3)

{
  Craft **ppCVar1;
  
  ppCVar1 = std::
            _Move_backward_opt<Craft_*_*,Craft_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppCVar1;
}
