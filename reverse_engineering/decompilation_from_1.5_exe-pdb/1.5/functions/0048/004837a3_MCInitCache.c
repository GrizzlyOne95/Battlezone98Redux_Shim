/*
 * Entry: 004837a3
 * Name: MCInitCache
 * Namespace: Global
 * Signature: void MCInitCache(MULTICACHE * param_1, long param_2, long param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl MCInitCache(MULTICACHE *param_1,long param_2,long param_3,char *param_4)

{
  cachenode **ppcVar1;
  
  if (param_1 == (MULTICACHE *)0x0) {
    param_1 = &GlobalCache;
  }
  param_1->CacheSize = 0;
  param_1->PurgeHead = (cachenode *)0x0;
  param_1->PurgeTail = (cachenode *)0x0;
  param_1->MaxCacheSize = param_3;
  param_1->hPrjCacheHeap = (void *)0x1;
  ppcVar1 = calloc(1,0x2000);
  param_1->Cache = ppcVar1;
  param_1->CacheMemSize = param_2;
  return;
}
