/*
 * Entry: 0052f0b4
 * Name: ExplosionClass::Clean
 * Namespace: ExplosionClass
 * Signature: void Clean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ExplosionClass::Clean(void)

{
  uint uVar1;
  ExplosionClass **ppEVar2;
  
  uVar1 = (int)classList._Mylast - (int)classList._Myfirst;
  while ((uVar1 & 0xfffffffc) != 0) {
    ppEVar2 = std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::back(&classList);
    if (*ppEVar2 != (ExplosionClass *)0x0) {
      (**(code **)(*ppEVar2)->_padding_)(1);
    }
    std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::pop_back(&classList);
    uVar1 = (int)classList._Mylast - (int)classList._Myfirst;
  }
  return;
}
