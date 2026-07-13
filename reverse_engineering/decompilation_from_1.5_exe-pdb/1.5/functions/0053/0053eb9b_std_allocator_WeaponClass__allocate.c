/*
 * Entry: 0053eb9b
 * Name: std::allocator<WeaponClass_*>::allocate
 * Namespace: std::allocator<WeaponClass_*>
 * Signature: WeaponClass * * allocate(allocator<WeaponClass_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass ** __thiscall
std::allocator<WeaponClass_*>::allocate(allocator<WeaponClass_*> *this,uint param_1)

{
  WeaponClass **ppWVar1;
  
  ppWVar1 = _Allocate<WeaponClass_*>(param_1,(WeaponClass **)0x0);
  return ppWVar1;
}
