/*
 * Entry: 0048c97f
 * Name: stdext::_Unchecked_uninitialized_move<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*_*,std::allocator<DistributedObject_*>_>
 * Namespace: stdext
 * Signature: DistributedObject * * _Unchecked_uninitialized_move<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*_*,std::allocator<DistributedObject_*>_>(_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_1, _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_2, DistributedObject * * param_3, allocator<DistributedObject_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DistributedObject ** __cdecl
stdext::
_Unchecked_uninitialized_move<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*_*,std::allocator<DistributedObject_*>_>
          (_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_1,
          _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_2,
          DistributedObject **param_3,allocator<DistributedObject_*> *param_4)

{
  DistributedObject **ppDVar1;
  
  ppDVar1 = unchecked_uninitialized_copy<DistributedObject_*_*,DistributedObject_*_*,std::allocator<DistributedObject_*>_>
                      ((DistributedObject **)param_1._4_4_,(DistributedObject **)param_2._4_4_,
                       param_3,param_4);
  return ppDVar1;
}
