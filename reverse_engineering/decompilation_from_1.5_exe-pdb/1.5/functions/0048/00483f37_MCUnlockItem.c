/*
 * Entry: 00483f37
 * Name: MCUnlockItem
 * Namespace: Global
 * Signature: void MCUnlockItem(MULTICACHE * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl MCUnlockItem(MULTICACHE *param_1,char *param_2)

{
  nUnlockItems = nUnlockItems + 1;
  if (param_1 == (MULTICACHE *)0x0) {
    param_1 = &GlobalCache;
  }
  MCunlock_nonpack_item(param_1,param_2);
  return;
}
