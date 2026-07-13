/*
 * Entry: 00491bee
 * Name: std::allocator<GameFeature_*>::deallocate
 * Namespace: std::allocator<GameFeature_*>
 * Signature: void deallocate(allocator<GameFeature_*> * this, GameFeature * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<GameFeature_*>::deallocate
          (allocator<GameFeature_*> *this,GameFeature **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
