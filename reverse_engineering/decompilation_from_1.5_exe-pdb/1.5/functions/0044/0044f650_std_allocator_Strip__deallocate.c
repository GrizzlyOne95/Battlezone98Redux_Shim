/*
 * Entry: 0044f650
 * Name: std::allocator<Strip_*>::deallocate
 * Namespace: std::allocator<Strip_*>
 * Signature: void deallocate(allocator<Strip_*> * this, Strip * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<Strip_*>::deallocate(allocator<Strip_*> *this,Strip **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
