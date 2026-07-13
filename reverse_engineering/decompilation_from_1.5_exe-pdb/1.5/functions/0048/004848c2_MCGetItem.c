/*
 * Entry: 004848c2
 * Name: MCGetItem
 * Namespace: Global
 * Signature: uchar * MCGetItem(MULTICACHE * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar * __cdecl MCGetItem(MULTICACHE *param_1,char *param_2)

{
  uchar *puVar1;
  
  if (param_1 == (MULTICACHE *)0x0) {
    param_1 = &GlobalCache;
  }
  puVar1 = MCUseItem(param_1,param_2);
  return puVar1;
}
