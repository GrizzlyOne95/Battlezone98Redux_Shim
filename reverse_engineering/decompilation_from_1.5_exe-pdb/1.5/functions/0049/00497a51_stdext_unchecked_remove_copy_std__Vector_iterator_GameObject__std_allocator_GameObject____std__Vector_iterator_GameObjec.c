/*
 * Entry: 00497a51
 * Name: stdext::unchecked_remove_copy<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,GameObject_*>
 * Namespace: stdext
 * Signature: _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> unchecked_remove_copy<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,GameObject_*>(_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_1, _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_2, _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_3, GameObject * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> __cdecl
stdext::
unchecked_remove_copy<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,GameObject_*>
          (_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_1,
          _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_2,
          _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_3,GameObject **param_4)

{
  _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> _Var1;
  _Range_checked_iterator_tag in_stack_00000020;
  
  _Var1 = std::
          _Remove_copy<GameObject_*_*,std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,GameObject_*>
                    ((GameObject **)param_1._0_4_,(GameObject **)param_2._0_4_,param_3,param_4,
                     in_stack_00000020);
  _Var1._0_4_ = param_1._0_4_;
  return _Var1;
}
