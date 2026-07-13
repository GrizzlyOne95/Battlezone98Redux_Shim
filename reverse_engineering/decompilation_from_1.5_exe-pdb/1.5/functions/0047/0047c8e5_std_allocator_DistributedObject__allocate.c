/*
 * Entry: 0047c8e5
 * Name: std::allocator<DistributedObject_*>::allocate
 * Namespace: std::allocator<DistributedObject_*>
 * Signature: DistributedObject * * allocate(allocator<DistributedObject_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DistributedObject ** __thiscall
std::allocator<DistributedObject_*>::allocate(allocator<DistributedObject_*> *this,uint param_1)

{
  DistributedObject **ppDVar1;
  
  ppDVar1 = _Allocate<DistributedObject_*>(param_1,(DistributedObject **)0x0);
  return ppDVar1;
}
