/*
 * Entry: 00484799
 * Name: MCFlush_Unlock_items
 * Namespace: Global
 * Signature: void MCFlush_Unlock_items(MULTICACHE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl MCFlush_Unlock_items(MULTICACHE *param_1)

{
  int iVar1;
  cachenode *pcVar2;
  
  if (param_1 == (MULTICACHE *)0x0) {
    param_1 = &GlobalCache;
  }
  iVar1 = 0;
  do {
    for (pcVar2 = *(cachenode **)(iVar1 + (int)param_1->Cache); pcVar2 != (cachenode *)0x0;
        pcVar2 = pcVar2->Next) {
      if (pcVar2->Lock == 0) {
        MCadd_to_purge(param_1,pcVar2);
      }
    }
    iVar1 = iVar1 + 4;
  } while (iVar1 < 0x2000);
  while (param_1->PurgeHead != (cachenode *)0x0) {
    MCReallyNukeItem(param_1,param_1->PurgeHead);
  }
  return;
}
