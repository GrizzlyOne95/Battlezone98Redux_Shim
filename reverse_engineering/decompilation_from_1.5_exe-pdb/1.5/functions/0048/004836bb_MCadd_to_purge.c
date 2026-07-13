/*
 * Entry: 004836bb
 * Name: MCadd_to_purge
 * Namespace: Global
 * Signature: void MCadd_to_purge(MULTICACHE * param_1, cachenode * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl MCadd_to_purge(MULTICACHE *param_1,cachenode *param_2)

{
  if (param_1 == (MULTICACHE *)0x0) {
    param_1 = &GlobalCache;
  }
  if (param_1->PurgeTail != (cachenode *)0x0) {
    param_1->PurgeTail->PurgeNext = param_2;
  }
  param_2->PurgePrev = param_1->PurgeTail;
  param_1->PurgeTail = param_2;
  param_2->PurgeNext = (cachenode *)0x0;
  if (param_1->PurgeHead == (cachenode *)0x0) {
    param_1->PurgeHead = param_2;
  }
  return;
}
