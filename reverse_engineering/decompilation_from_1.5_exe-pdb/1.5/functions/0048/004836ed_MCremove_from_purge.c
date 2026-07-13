/*
 * Entry: 004836ed
 * Name: MCremove_from_purge
 * Namespace: Global
 * Signature: void MCremove_from_purge(MULTICACHE * param_1, cachenode * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl MCremove_from_purge(MULTICACHE *param_1,cachenode *param_2)

{
  if (param_1 == (MULTICACHE *)0x0) {
    param_1 = &GlobalCache;
  }
  if (param_2->PurgeNext != (cachenode *)0x0) {
    param_2->PurgeNext->PurgePrev = param_2->PurgePrev;
  }
  if (param_2->PurgePrev != (cachenode *)0x0) {
    param_2->PurgePrev->PurgeNext = param_2->PurgeNext;
  }
  if (param_2 == param_1->PurgeHead) {
    param_1->PurgeHead = param_2->PurgeNext;
  }
  if (param_2 == param_1->PurgeTail) {
    param_1->PurgeTail = param_2->PurgePrev;
  }
  param_2->PurgeNext = (cachenode *)0x0;
  param_2->PurgePrev = (cachenode *)0x0;
  return;
}
