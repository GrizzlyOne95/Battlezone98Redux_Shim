/*
 * Entry: 004969c8
 * Name: std::allocator<GameObject_*>::deallocate
 * Namespace: std::allocator<GameObject_*>
 * Signature: void deallocate(allocator<GameObject_*> * this, GameObject * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<GameObject_*>::deallocate
          (allocator<GameObject_*> *this,GameObject **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
