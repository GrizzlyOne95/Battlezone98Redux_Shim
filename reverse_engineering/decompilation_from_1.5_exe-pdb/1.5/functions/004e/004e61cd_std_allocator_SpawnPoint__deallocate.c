/*
 * Entry: 004e61cd
 * Name: std::allocator<SpawnPoint_*>::deallocate
 * Namespace: std::allocator<SpawnPoint_*>
 * Signature: void deallocate(allocator<SpawnPoint_*> * this, SpawnPoint * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<SpawnPoint_*>::deallocate
          (allocator<SpawnPoint_*> *this,SpawnPoint **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
