/*
 * Entry: 0053f2e0
 * Name: WeaponClass_Clean
 * Namespace: Global
 * Signature: void WeaponClass_Clean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl WeaponClass_Clean(void)

{
  uint uVar1;
  WeaponClass **ppWVar2;
  
  uVar1 = (int)WeaponClass::classList._Mylast - (int)WeaponClass::classList._Myfirst;
  while ((uVar1 & 0xfffffffc) != 0) {
    ppWVar2 = std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::back
                        (&WeaponClass::classList);
    if (*ppWVar2 != (WeaponClass *)0x0) {
      (**(code **)(*ppWVar2)->_padding_)(1);
    }
    std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::pop_back(&WeaponClass::classList);
    uVar1 = (int)WeaponClass::classList._Mylast - (int)WeaponClass::classList._Myfirst;
  }
  return;
}
