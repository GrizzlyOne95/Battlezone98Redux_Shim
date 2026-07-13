/*
 * Entry: 0048d1df
 * Name: stdext::unchecked_uninitialized_fill_n<DistributedObject_*_*,unsigned_int,DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Namespace: stdext
 * Signature: void unchecked_uninitialized_fill_n<DistributedObject_*_*,unsigned_int,DistributedObject_*,std::allocator<DistributedObject_*>_>(DistributedObject * * param_1, uint param_2, DistributedObject * * param_3, allocator<DistributedObject_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::
unchecked_uninitialized_fill_n<DistributedObject_*_*,unsigned_int,DistributedObject_*,std::allocator<DistributedObject_*>_>
          (DistributedObject **param_1,uint param_2,DistributedObject **param_3,
          allocator<DistributedObject_*> *param_4)

{
  unchecked_fill_n<DistributedObject_*_*,unsigned_int,DistributedObject_*>(param_1,param_2,param_3);
  return;
}
