/*
 * Entry: 00516f63
 * Name: std::allocator<ObjectClassInfo_*>::deallocate
 * Namespace: std::allocator<ObjectClassInfo_*>
 * Signature: void deallocate(allocator<ObjectClassInfo_*> * this, ObjectClassInfo * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<ObjectClassInfo_*>::deallocate
          (allocator<ObjectClassInfo_*> *this,ObjectClassInfo **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
