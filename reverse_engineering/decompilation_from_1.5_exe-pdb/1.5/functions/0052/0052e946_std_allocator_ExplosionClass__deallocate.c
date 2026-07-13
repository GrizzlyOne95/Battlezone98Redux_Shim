/*
 * Entry: 0052e946
 * Name: std::allocator<ExplosionClass_*>::deallocate
 * Namespace: std::allocator<ExplosionClass_*>
 * Signature: void deallocate(allocator<ExplosionClass_*> * this, ExplosionClass * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<ExplosionClass_*>::deallocate
          (allocator<ExplosionClass_*> *this,ExplosionClass **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
