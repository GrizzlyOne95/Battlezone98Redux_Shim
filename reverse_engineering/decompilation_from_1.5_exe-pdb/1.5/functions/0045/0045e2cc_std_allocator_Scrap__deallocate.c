/*
 * Entry: 0045e2cc
 * Name: std::allocator<Scrap_*>::deallocate
 * Namespace: std::allocator<Scrap_*>
 * Signature: void deallocate(allocator<Scrap_*> * this, Scrap * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<Scrap_*>::deallocate(allocator<Scrap_*> *this,Scrap **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
