/*
 * Entry: 004c39ef
 * Name: CleanupBuildItem
 * Namespace: Global
 * Signature: void CleanupBuildItem(BuildItem * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CleanupBuildItem(BuildItem *param_1)

{
  int iVar1;
  
  if (param_1->menu != (BuildItem *)0x0) {
    iVar1 = 0;
    do {
      CleanupBuildItem((BuildItem *)(param_1->menu->name + iVar1 + -4));
      iVar1 = iVar1 + 0x24;
    } while (iVar1 < 0x168);
    free(param_1->menu);
    param_1->menu = (BuildItem *)0x0;
  }
  return;
}
