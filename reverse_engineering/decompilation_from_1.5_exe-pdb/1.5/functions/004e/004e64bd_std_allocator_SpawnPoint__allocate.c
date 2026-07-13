/*
 * Entry: 004e64bd
 * Name: std::allocator<SpawnPoint_*>::allocate
 * Namespace: std::allocator<SpawnPoint_*>
 * Signature: SpawnPoint * * allocate(allocator<SpawnPoint_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpawnPoint ** __thiscall
std::allocator<SpawnPoint_*>::allocate(allocator<SpawnPoint_*> *this,uint param_1)

{
  SpawnPoint **ppSVar1;
  
  ppSVar1 = _Allocate<SpawnPoint_*>(param_1,(SpawnPoint **)0x0);
  return ppSVar1;
}
