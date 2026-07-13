/*
 * Entry: 0048922c
 * Name: stdext::unchecked_copy<Craft_*_*,Craft_*_*>
 * Namespace: stdext
 * Signature: Craft * * unchecked_copy<Craft_*_*,Craft_*_*>(Craft * * param_1, Craft * * param_2, Craft * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Craft ** __cdecl
stdext::unchecked_copy<Craft_*_*,Craft_*_*>(Craft **param_1,Craft **param_2,Craft **param_3)

{
  Craft **ppCVar1;
  
  ppCVar1 = std::_Copy_opt<Craft_*_*,Craft_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Scalar_ptr_iterator_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppCVar1;
}
