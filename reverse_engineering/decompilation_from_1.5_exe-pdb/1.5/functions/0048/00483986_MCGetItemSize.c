/*
 * Entry: 00483986
 * Name: MCGetItemSize
 * Namespace: Global
 * Signature: long MCGetItemSize(MULTICACHE * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl MCGetItemSize(MULTICACHE *param_1,char *param_2)

{
  cachenode *pcVar1;
  int iVar2;
  
  nGetItemSize = nGetItemSize + 1;
  if (param_1 == (MULTICACHE *)0x0) {
    param_1 = &GlobalCache;
  }
  if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
    pcVar1 = MCFindItem(param_1,param_2);
    if (pcVar1 != (cachenode *)0x0) {
      return pcVar1->size;
    }
    iVar2 = zixGetFileSize(param_2);
    return iVar2;
  }
  return 0;
}
