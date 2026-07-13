/*
 * Entry: 00483739
 * Name: InitCache
 * Namespace: Global
 * Signature: void InitCache(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitCache(void)

{
  MACHINE_CAPS *pMVar1;
  int iVar2;
  ulong *puVar3;
  MACHINE_CAPS local_34;
  ulong local_1c [6];
  
  pMVar1 = GetMachineCaps(&local_34);
  puVar3 = local_1c;
  for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = pMVar1->PhysicalRAM;
    pMVar1 = (MACHINE_CAPS *)&pMVar1->VideoRAM;
    puVar3 = puVar3 + 1;
  }
  GlobalCache.CacheSize = 0;
  GlobalCache.PurgeHead = (cachenode *)0x0;
  GlobalCache.PurgeTail = (cachenode *)0x0;
  GlobalCache.MaxCacheSize = 0x800;
  GlobalCache.hPrjCacheHeap = (void *)0x1;
  GlobalCache.Cache = calloc(1,0x2000);
  GlobalCache.CacheMemSize = 0x500000;
  _unlink("symlog.txt");
  return;
}
