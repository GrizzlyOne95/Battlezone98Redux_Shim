/*
 * Entry: 0052f2a3
 * Name: ExplosionClass_Clean
 * Namespace: Global
 * Signature: void ExplosionClass_Clean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ExplosionClass_Clean(void)

{
  uint uVar1;
  ExplosionClass **ppEVar2;
  
  uVar1 = (int)ExplosionClass::classList._Mylast - (int)ExplosionClass::classList._Myfirst;
  while ((uVar1 & 0xfffffffc) != 0) {
    ppEVar2 = std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::back
                        (&ExplosionClass::classList);
    if (*ppEVar2 != (ExplosionClass *)0x0) {
      (**(code **)(*ppEVar2)->_padding_)(1);
    }
    std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::pop_back
              (&ExplosionClass::classList);
    uVar1 = (int)ExplosionClass::classList._Mylast - (int)ExplosionClass::classList._Myfirst;
  }
  return;
}
