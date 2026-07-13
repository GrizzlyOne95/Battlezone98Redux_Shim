/*
 * Entry: 00489314
 * Name: std::find<std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>,Craft_*>
 * Namespace: std
 * Signature: _Vector_iterator<Craft_*,std::allocator<Craft_*>_> find<std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>,Craft_*>(_Vector_iterator<Craft_*,std::allocator<Craft_*>_> param_1, _Vector_iterator<Craft_*,std::allocator<Craft_*>_> param_2, Craft * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Craft_*,std::allocator<Craft_*>_> __cdecl
std::find<std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>,Craft_*>
          (_Vector_iterator<Craft_*,std::allocator<Craft_*>_> param_1,
          _Vector_iterator<Craft_*,std::allocator<Craft_*>_> param_2,Craft **param_3)

{
  Craft **ppCVar1;
  Craft **in_stack_00000018;
  
  ppCVar1 = _Find<Craft_*_*,Craft_*>((Craft **)param_2._0_4_,param_3,in_stack_00000018);
  *(undefined4 *)param_1._0_4_ = param_1._4_4_;
  *(Craft ***)(param_1._0_4_ + 4) = ppCVar1;
  return param_1;
}
