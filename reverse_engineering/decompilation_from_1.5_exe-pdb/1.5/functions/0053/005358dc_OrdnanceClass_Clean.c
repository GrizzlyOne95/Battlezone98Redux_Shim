/*
 * Entry: 005358dc
 * Name: OrdnanceClass_Clean
 * Namespace: Global
 * Signature: void OrdnanceClass_Clean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl OrdnanceClass_Clean(void)

{
  uint uVar1;
  OrdnanceClass **ppOVar2;
  
  uVar1 = (int)OrdnanceClass::classList._Mylast - (int)OrdnanceClass::classList._Myfirst;
  while ((uVar1 & 0xfffffffc) != 0) {
    ppOVar2 = std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::back
                        (&OrdnanceClass::classList);
    if (*ppOVar2 != (OrdnanceClass *)0x0) {
      (**(code **)(*ppOVar2)->_padding_)(1);
    }
    std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::pop_back
              (&OrdnanceClass::classList);
    uVar1 = (int)OrdnanceClass::classList._Mylast - (int)OrdnanceClass::classList._Myfirst;
  }
  return;
}
