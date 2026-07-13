/*
 * Entry: 0054df0f
 * Name: ExitFailMenu
 * Namespace: Global
 * Signature: void ExitFailMenu(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ExitFailMenu(void)

{
  int iVar1;
  
  ClearMenu();
  iVar1 = GetRunning();
  if (iVar1 == 0) {
    SetRunning(2);
  }
  SetScreenMode(SCREENMODE_SIM);
  return;
}
