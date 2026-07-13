/*
 * Entry: 00534f7f
 * Name: std::allocator<OrdnanceClass_*>::deallocate
 * Namespace: std::allocator<OrdnanceClass_*>
 * Signature: void deallocate(allocator<OrdnanceClass_*> * this, OrdnanceClass * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<OrdnanceClass_*>::deallocate
          (allocator<OrdnanceClass_*> *this,OrdnanceClass **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
