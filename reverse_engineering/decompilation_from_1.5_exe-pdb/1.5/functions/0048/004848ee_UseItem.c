/*
 * Entry: 004848ee
 * Name: UseItem
 * Namespace: Global
 * Signature: void * UseItem(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl UseItem(char *param_1)

{
  void *pvVar1;
  
  pvVar1 = MCUseItem((MULTICACHE *)0x0,param_1);
  return pvVar1;
}
