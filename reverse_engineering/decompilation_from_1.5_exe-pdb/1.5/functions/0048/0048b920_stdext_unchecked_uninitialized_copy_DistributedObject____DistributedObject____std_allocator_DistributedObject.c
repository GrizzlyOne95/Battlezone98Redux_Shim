/*
 * Entry: 0048b920
 * Name: stdext::unchecked_uninitialized_copy<DistributedObject_*_*,DistributedObject_*_*,std::allocator<DistributedObject_*>_>
 * Namespace: stdext
 * Signature: DistributedObject * * unchecked_uninitialized_copy<DistributedObject_*_*,DistributedObject_*_*,std::allocator<DistributedObject_*>_>(DistributedObject * * param_1, DistributedObject * * param_2, DistributedObject * * param_3, allocator<DistributedObject_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DistributedObject ** __cdecl
stdext::
unchecked_uninitialized_copy<DistributedObject_*_*,DistributedObject_*_*,std::allocator<DistributedObject_*>_>
          (DistributedObject **param_1,DistributedObject **param_2,DistributedObject **param_3,
          allocator<DistributedObject_*> *param_4)

{
  DistributedObject **ppDVar1;
  
  ppDVar1 = std::
            _Uninit_copy<DistributedObject_*_*,DistributedObject_*_*,std::allocator<DistributedObject_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppDVar1;
}
