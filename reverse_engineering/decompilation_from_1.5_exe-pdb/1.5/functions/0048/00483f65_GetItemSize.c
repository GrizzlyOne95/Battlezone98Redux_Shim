/*
 * Entry: 00483f65
 * Name: GetItemSize
 * Namespace: Global
 * Signature: long GetItemSize(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl GetItemSize(char *param_1)

{
  long lVar1;
  
  lVar1 = MCGetItemSize((MULTICACHE *)0x0,param_1);
  return lVar1;
}
