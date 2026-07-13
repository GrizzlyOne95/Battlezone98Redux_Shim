/*
 * Entry: 004ada91
 * Name: std::allocator<Scanner_*>::deallocate
 * Namespace: std::allocator<Scanner_*>
 * Signature: void deallocate(allocator<Scanner_*> * this, Scanner * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<Scanner_*>::deallocate(allocator<Scanner_*> *this,Scanner **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
