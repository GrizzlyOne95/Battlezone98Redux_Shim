/*
 * Entry: 0048394a
 * Name: MCunlock_nonpack_item
 * Namespace: Global
 * Signature: void MCunlock_nonpack_item(MULTICACHE * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl MCunlock_nonpack_item(MULTICACHE *param_1,char *param_2)

{
  cachenode *pcVar1;
  short sVar2;
  
  if (param_1 == (MULTICACHE *)0x0) {
    param_1 = &GlobalCache;
  }
  pcVar1 = MCFindItem(param_1,param_2);
  if (((pcVar1 != (cachenode *)0x0) && (pcVar1->Lock != 0)) &&
     (sVar2 = pcVar1->Lock + -1, pcVar1->Lock = sVar2, sVar2 == 0)) {
    MCadd_to_purge(param_1,pcVar1);
  }
  return;
}
