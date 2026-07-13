/*
 * Entry: 004af31b
 * Name: std::find<std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,Scrap_*>
 * Namespace: std
 * Signature: _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> find<std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,Scrap_*>(_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_1, _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_2, Scrap * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> __cdecl
std::find<std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,Scrap_*>
          (_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_1,
          _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_2,Scrap **param_3)

{
  Scrap **ppSVar1;
  Scrap **in_stack_00000018;
  
  ppSVar1 = _Find<Scrap_*_*,Scrap_*>((Scrap **)param_2._0_4_,param_3,in_stack_00000018);
  *(undefined4 *)param_1._0_4_ = param_1._4_4_;
  *(Scrap ***)(param_1._0_4_ + 4) = ppSVar1;
  return param_1;
}
