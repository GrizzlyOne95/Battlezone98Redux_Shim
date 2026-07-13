/*
 * Entry: 0047c2ce
 * Name: std::allocator<DistributedObject_*>::deallocate
 * Namespace: std::allocator<DistributedObject_*>
 * Signature: void deallocate(allocator<DistributedObject_*> * this, DistributedObject * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<DistributedObject_*>::deallocate
          (allocator<DistributedObject_*> *this,DistributedObject **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
