/*
 * Entry: 0055524f
 * Name: std::allocator<Session_*>::deallocate
 * Namespace: std::allocator<Session_*>
 * Signature: void deallocate(allocator<Session_*> * this, Session * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<Session_*>::deallocate(allocator<Session_*> *this,Session **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
