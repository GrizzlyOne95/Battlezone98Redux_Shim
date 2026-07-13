/*
 * Entry: 0055519e
 * Name: std::allocator<Server_*>::deallocate
 * Namespace: std::allocator<Server_*>
 * Signature: void deallocate(allocator<Server_*> * this, Server * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<Server_*>::deallocate(allocator<Server_*> *this,Server **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
