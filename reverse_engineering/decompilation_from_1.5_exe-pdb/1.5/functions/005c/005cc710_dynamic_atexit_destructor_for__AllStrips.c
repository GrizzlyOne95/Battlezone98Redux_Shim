/*
 * Entry: 005cc710
 * Name: `dynamic_atexit_destructor_for_'AllStrips''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'AllStrips''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__AllStrips__(void)

{
  MemoryPool *pMVar1;
  int iVar2;
  
  pathMem = pathMem + -0x3c0000;
  pMVar1 = &planPool;
  iVar2 = 0xffff;
  do {
    pMVar1 = (MemoryPool *)&pMVar1[-4].mGrow;
    iVar2 = iVar2 + -1;
    *(undefined ***)pMVar1 = &Strip::_vftable_;
  } while (-1 < iVar2);
  return;
}
