/*
 * Entry: 005ca2c0
 * Name: `dynamic_initializer_for_'AllStrips''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'AllStrips''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__AllStrips__(void)

{
  Strip *pSVar1;
  int iVar2;
  
  pathMem = pathMem + 0x3c0000;
  pSVar1 = AllStrips;
  iVar2 = 0xffff;
  do {
    pSVar1->_padding_ = (int)&Strip::_vftable_;
    pSVar1 = pSVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  atexit(_dynamic_atexit_destructor_for__AllStrips__);
  return;
}
