/*
 * Entry: 004ae099
 * Name: std::find<std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>,Scanner_*>
 * Namespace: std
 * Signature: _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> find<std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>,Scanner_*>(_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> param_1, _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> param_2, Scanner * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> __cdecl
std::find<std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>,Scanner_*>
          (_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> param_1,
          _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> param_2,Scanner **param_3)

{
  Scanner **ppSVar1;
  Scanner **in_stack_00000018;
  
  ppSVar1 = _Find<Scanner_*_*,Scanner_*>((Scanner **)param_2._0_4_,param_3,in_stack_00000018);
  *(undefined4 *)param_1._0_4_ = param_1._4_4_;
  *(Scanner ***)(param_1._0_4_ + 4) = ppSVar1;
  return param_1;
}
