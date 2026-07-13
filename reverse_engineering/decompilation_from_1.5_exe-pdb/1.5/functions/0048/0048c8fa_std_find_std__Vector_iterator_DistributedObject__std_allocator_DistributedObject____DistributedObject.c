/*
 * Entry: 0048c8fa
 * Name: std::find<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*>
 * Namespace: std
 * Signature: _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> find<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*>(_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_1, _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_2, DistributedObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> __cdecl
std::
find<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*>
          (_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_1,
          _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_2,
          DistributedObject **param_3)

{
  DistributedObject **ppDVar1;
  DistributedObject **in_stack_00000018;
  
  ppDVar1 = _Find<DistributedObject_*_*,DistributedObject_*>
                      ((DistributedObject **)param_2._0_4_,param_3,in_stack_00000018);
  *(undefined4 *)param_1._0_4_ = param_1._4_4_;
  *(DistributedObject ***)(param_1._0_4_ + 4) = ppDVar1;
  return param_1;
}
