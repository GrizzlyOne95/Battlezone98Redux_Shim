/*
 * Entry: 004841fc
 * Name: MCNukeItem
 * Namespace: Global
 * Signature: void MCNukeItem(MULTICACHE * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl MCNukeItem(MULTICACHE *param_1,char *param_2)

{
  cachenode *pcVar1;
  
  if (param_1 == (MULTICACHE *)0x0) {
    param_1 = &GlobalCache;
  }
  pcVar1 = MCFindItem(param_1,param_2);
  if (pcVar1 != (cachenode *)0x0) {
    MCReallyNukeItem(param_1,pcVar1);
  }
  return;
}
