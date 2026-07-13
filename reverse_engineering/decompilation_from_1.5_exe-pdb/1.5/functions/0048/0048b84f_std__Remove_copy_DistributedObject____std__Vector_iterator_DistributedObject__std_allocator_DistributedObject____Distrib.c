/*
 * Entry: 0048b84f
 * Name: std::_Remove_copy<DistributedObject_*_*,std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*>
 * Namespace: std
 * Signature: _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> _Remove_copy<DistributedObject_*_*,std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*>(DistributedObject * * param_1, DistributedObject * * param_2, _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_3, DistributedObject * * param_4, _Range_checked_iterator_tag param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> __cdecl
std::
_Remove_copy<DistributedObject_*_*,std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*>
          (DistributedObject **param_1,DistributedObject **param_2,
          _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_3,
          DistributedObject **param_4,_Range_checked_iterator_tag param_5)

{
  DistributedObject **ppDVar1;
  undefined4 in_EDX;
  undefined4 extraout_EDX;
  _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> _Var2;
  undefined3 in_stack_00000019;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> local_c;
  
  for (; param_2 != (DistributedObject **)param_3._0_4_; param_2 = param_2 + 1) {
    if (*param_2 != (DistributedObject *)*_param_5) {
      local_c._padding_ = param_3._4_4_;
      local_c._Myptr = param_4;
      _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::operator++
                ((_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> *
                 )&param_3.field_0x4);
      ppDVar1 = _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
                operator*(&local_c);
      *ppDVar1 = *param_2;
      in_EDX = extraout_EDX;
    }
  }
  *param_1 = (DistributedObject *)param_3._4_4_;
  param_1[1] = (DistributedObject *)param_4;
  _Var2._4_4_ = in_EDX;
  _Var2._0_4_ = param_1;
  return _Var2;
}
