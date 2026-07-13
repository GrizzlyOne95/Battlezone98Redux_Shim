/*
 * Entry: 0053f0f1
 * Name: WeaponClass::Clean
 * Namespace: WeaponClass
 * Signature: void Clean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl WeaponClass::Clean(void)

{
  uint uVar1;
  WeaponClass **ppWVar2;
  
  uVar1 = (int)classList._Mylast - (int)classList._Myfirst;
  while ((uVar1 & 0xfffffffc) != 0) {
    ppWVar2 = std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::back(&classList);
    if (*ppWVar2 != (WeaponClass *)0x0) {
      (**(code **)(*ppWVar2)->_padding_)(1);
    }
    std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::pop_back(&classList);
    uVar1 = (int)classList._Mylast - (int)classList._Myfirst;
  }
  return;
}
