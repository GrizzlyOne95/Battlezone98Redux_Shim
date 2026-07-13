/*
 * Entry: 004ae16f
 * Name: stdext::unchecked_remove_copy<std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>,std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>,Scanner_*>
 * Namespace: stdext
 * Signature: _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> unchecked_remove_copy<std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>,std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>,Scanner_*>(_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> param_1, _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> param_2, _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> param_3, Scanner * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> __cdecl
stdext::
unchecked_remove_copy<std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>,std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>,Scanner_*>
          (_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> param_1,
          _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> param_2,
          _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> param_3,Scanner **param_4)

{
  _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> _Var1;
  _Range_checked_iterator_tag in_stack_00000020;
  
  _Var1 = std::
          _Remove_copy<Scanner_*_*,std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>,Scanner_*>
                    ((Scanner **)param_1._0_4_,(Scanner **)param_2._0_4_,param_3,param_4,
                     in_stack_00000020);
  _Var1._0_4_ = param_1._0_4_;
  return _Var1;
}
