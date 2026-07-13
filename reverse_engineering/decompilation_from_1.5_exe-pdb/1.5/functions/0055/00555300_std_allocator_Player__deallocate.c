/*
 * Entry: 00555300
 * Name: std::allocator<Player_*>::deallocate
 * Namespace: std::allocator<Player_*>
 * Signature: void deallocate(allocator<Player_*> * this, Player * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<Player_*>::deallocate(allocator<Player_*> *this,Player **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
