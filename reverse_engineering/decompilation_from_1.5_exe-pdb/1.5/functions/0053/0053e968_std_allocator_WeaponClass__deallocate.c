/*
 * Entry: 0053e968
 * Name: std::allocator<WeaponClass_*>::deallocate
 * Namespace: std::allocator<WeaponClass_*>
 * Signature: void deallocate(allocator<WeaponClass_*> * this, WeaponClass * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<WeaponClass_*>::deallocate
          (allocator<WeaponClass_*> *this,WeaponClass **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
