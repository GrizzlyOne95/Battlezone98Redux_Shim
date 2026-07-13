/*
 * Entry: 00483e90
 * Name: FindItem
 * Namespace: Global
 * Signature: cachenode * FindItem(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

cachenode * __cdecl FindItem(char *param_1)

{
  cachenode *pcVar1;
  
  pcVar1 = MCFindItem((MULTICACHE *)0x0,param_1);
  return pcVar1;
}
