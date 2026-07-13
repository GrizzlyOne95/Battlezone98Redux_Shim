/*
 * Entry: 0048c91d
 * Name: stdext::unchecked_remove_copy<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*>
 * Namespace: stdext
 * Signature: _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> unchecked_remove_copy<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*>(_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_1, _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_2, _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_3, DistributedObject * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> __cdecl
stdext::
unchecked_remove_copy<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*>
          (_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_1,
          _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_2,
          _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_3,
          DistributedObject **param_4)

{
  _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> _Var1;
  _Range_checked_iterator_tag in_stack_00000020;
  
  _Var1 = std::
          _Remove_copy<DistributedObject_*_*,std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*>
                    ((DistributedObject **)param_1._0_4_,(DistributedObject **)param_2._0_4_,param_3
                     ,param_4,in_stack_00000020);
  _Var1._0_4_ = param_1._0_4_;
  return _Var1;
}
