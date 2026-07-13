/*
 * Entry: 00499308
 * Name: std::allocator<GameObjectClass_*>::deallocate
 * Namespace: std::allocator<GameObjectClass_*>
 * Signature: void deallocate(allocator<GameObjectClass_*> * this, GameObjectClass * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<GameObjectClass_*>::deallocate
          (allocator<GameObjectClass_*> *this,GameObjectClass **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
