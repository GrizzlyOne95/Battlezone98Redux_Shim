/*
 * Entry: 005356ed
 * Name: OrdnanceClass::Clean
 * Namespace: OrdnanceClass
 * Signature: void Clean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl OrdnanceClass::Clean(void)

{
  uint uVar1;
  OrdnanceClass **ppOVar2;
  
  uVar1 = (int)classList._Mylast - (int)classList._Myfirst;
  while ((uVar1 & 0xfffffffc) != 0) {
    ppOVar2 = std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::back(&classList);
    if (*ppOVar2 != (OrdnanceClass *)0x0) {
      (**(code **)(*ppOVar2)->_padding_)(1);
    }
    std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::pop_back(&classList);
    uVar1 = (int)classList._Mylast - (int)classList._Myfirst;
  }
  return;
}
