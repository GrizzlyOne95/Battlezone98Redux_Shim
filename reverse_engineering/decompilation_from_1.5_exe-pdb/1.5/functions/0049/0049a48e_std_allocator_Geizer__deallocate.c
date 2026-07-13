/*
 * Entry: 0049a48e
 * Name: std::allocator<Geizer_*>::deallocate
 * Namespace: std::allocator<Geizer_*>
 * Signature: void deallocate(allocator<Geizer_*> * this, Geizer * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<Geizer_*>::deallocate(allocator<Geizer_*> *this,Geizer **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
