/*
 * Entry: 00483dfd
 * Name: cacheName
 * Namespace: Global
 * Signature: char * cacheName(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl cacheName(void *param_1)

{
  cachenode *pcVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    for (pcVar1 = GlobalCache.Cache[iVar2]; pcVar1 != (cachenode *)0x0; pcVar1 = pcVar1->Next) {
      if (pcVar1 + 1 == param_1) {
        return pcVar1->assetname;
      }
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x800);
  return unknown;
}
