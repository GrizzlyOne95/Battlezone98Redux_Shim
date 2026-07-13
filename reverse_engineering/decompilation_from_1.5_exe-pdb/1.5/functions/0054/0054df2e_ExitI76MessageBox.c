/*
 * Entry: 0054df2e
 * Name: ExitI76MessageBox
 * Namespace: Global
 * Signature: void ExitI76MessageBox(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ExitI76MessageBox(void)

{
  ClearMenu();
  UnPauseGAS();
  SetScreenMode(SCREENMODE_SIM);
  return;
}
