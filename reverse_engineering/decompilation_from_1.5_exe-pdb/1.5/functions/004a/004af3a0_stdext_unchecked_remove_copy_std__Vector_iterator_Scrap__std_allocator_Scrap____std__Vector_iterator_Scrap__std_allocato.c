/*
 * Entry: 004af3a0
 * Name: stdext::unchecked_remove_copy<std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,Scrap_*>
 * Namespace: stdext
 * Signature: _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> unchecked_remove_copy<std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,Scrap_*>(_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_1, _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_2, _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_3, Scrap * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> __cdecl
stdext::
unchecked_remove_copy<std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,Scrap_*>
          (_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_1,
          _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_2,
          _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_3,Scrap **param_4)

{
  _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> _Var1;
  _Range_checked_iterator_tag in_stack_00000020;
  
  _Var1 = std::
          _Remove_copy<Scrap_*_*,std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,Scrap_*>
                    ((Scrap **)param_1._0_4_,(Scrap **)param_2._0_4_,param_3,param_4,
                     in_stack_00000020);
  _Var1._0_4_ = param_1._0_4_;
  return _Var1;
}
