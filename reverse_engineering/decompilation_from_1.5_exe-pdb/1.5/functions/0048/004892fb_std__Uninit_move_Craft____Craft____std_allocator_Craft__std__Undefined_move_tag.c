/*
 * Entry: 004892fb
 * Name: std::_Uninit_move<Craft_*_*,Craft_*_*,std::allocator<Craft_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: Craft * * _Uninit_move<Craft_*_*,Craft_*_*,std::allocator<Craft_*>,std::_Undefined_move_tag>(Craft * * param_1, Craft * * param_2, Craft * * param_3, allocator<Craft_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Craft ** __cdecl
std::_Uninit_move<Craft_*_*,Craft_*_*,std::allocator<Craft_*>,std::_Undefined_move_tag>
          (Craft **param_1,Craft **param_2,Craft **param_3,allocator<Craft_*> *param_4,
          _Undefined_move_tag param_5,_Range_checked_iterator_tag param_6)

{
  Craft **ppCVar1;
  
  ppCVar1 = stdext::unchecked_uninitialized_copy<Craft_*_*,Craft_*_*,std::allocator<Craft_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppCVar1;
}
