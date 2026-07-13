/*
 * Entry: 0048937a
 * Name: stdext::_Unchecked_uninitialized_move<Craft_*_*,Craft_*_*,std::allocator<Craft_*>_>
 * Namespace: stdext
 * Signature: Craft * * _Unchecked_uninitialized_move<Craft_*_*,Craft_*_*,std::allocator<Craft_*>_>(Craft * * param_1, Craft * * param_2, Craft * * param_3, allocator<Craft_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Craft ** __cdecl
stdext::_Unchecked_uninitialized_move<Craft_*_*,Craft_*_*,std::allocator<Craft_*>_>
          (Craft **param_1,Craft **param_2,Craft **param_3,allocator<Craft_*> *param_4)

{
  Craft **ppCVar1;
  
  ppCVar1 = std::_Uninit_copy<Craft_*_*,Craft_*_*,std::allocator<Craft_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppCVar1;
}
