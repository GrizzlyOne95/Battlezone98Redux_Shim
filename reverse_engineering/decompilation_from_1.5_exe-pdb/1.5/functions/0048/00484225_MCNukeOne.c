/*
 * Entry: 00484225
 * Name: MCNukeOne
 * Namespace: Global
 * Signature: int MCNukeOne(MULTICACHE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl MCNukeOne(MULTICACHE *param_1)

{
  if (param_1 == (MULTICACHE *)0x0) {
    param_1 = &GlobalCache;
  }
  if (param_1->PurgeHead != (cachenode *)0x0) {
    MCReallyNukeItem(param_1,param_1->PurgeHead);
    return 1;
  }
  return 0;
}
