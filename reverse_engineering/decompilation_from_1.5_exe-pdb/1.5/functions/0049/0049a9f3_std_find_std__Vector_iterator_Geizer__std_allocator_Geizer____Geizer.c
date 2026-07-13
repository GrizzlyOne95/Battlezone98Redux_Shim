/*
 * Entry: 0049a9f3
 * Name: std::find<std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>,Geizer_*>
 * Namespace: std
 * Signature: _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> find<std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>,Geizer_*>(_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> param_1, _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> param_2, Geizer * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> __cdecl
std::find<std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>,Geizer_*>
          (_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> param_1,
          _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> param_2,Geizer **param_3)

{
  Geizer **ppGVar1;
  Geizer **in_stack_00000018;
  
  ppGVar1 = _Find<Geizer_*_*,Geizer_*>((Geizer **)param_2._0_4_,param_3,in_stack_00000018);
  *(undefined4 *)param_1._0_4_ = param_1._4_4_;
  *(Geizer ***)(param_1._0_4_ + 4) = ppGVar1;
  return param_1;
}
