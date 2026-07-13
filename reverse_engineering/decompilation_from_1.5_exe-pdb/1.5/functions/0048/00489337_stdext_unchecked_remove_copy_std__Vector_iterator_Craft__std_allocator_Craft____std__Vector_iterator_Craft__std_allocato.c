/*
 * Entry: 00489337
 * Name: stdext::unchecked_remove_copy<std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>,std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>,Craft_*>
 * Namespace: stdext
 * Signature: _Vector_iterator<Craft_*,std::allocator<Craft_*>_> unchecked_remove_copy<std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>,std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>,Craft_*>(_Vector_iterator<Craft_*,std::allocator<Craft_*>_> param_1, _Vector_iterator<Craft_*,std::allocator<Craft_*>_> param_2, _Vector_iterator<Craft_*,std::allocator<Craft_*>_> param_3, Craft * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Craft_*,std::allocator<Craft_*>_> __cdecl
stdext::
unchecked_remove_copy<std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>,std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>,Craft_*>
          (_Vector_iterator<Craft_*,std::allocator<Craft_*>_> param_1,
          _Vector_iterator<Craft_*,std::allocator<Craft_*>_> param_2,
          _Vector_iterator<Craft_*,std::allocator<Craft_*>_> param_3,Craft **param_4)

{
  _Vector_iterator<Craft_*,std::allocator<Craft_*>_> _Var1;
  _Range_checked_iterator_tag in_stack_00000020;
  
  _Var1 = std::
          _Remove_copy<Craft_*_*,std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>,Craft_*>
                    ((Craft **)param_1._0_4_,(Craft **)param_2._0_4_,param_3,param_4,
                     in_stack_00000020);
  _Var1._0_4_ = param_1._0_4_;
  return _Var1;
}
