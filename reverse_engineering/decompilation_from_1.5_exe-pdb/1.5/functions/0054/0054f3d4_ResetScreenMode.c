/*
 * Entry: 0054f3d4
 * Name: ResetScreenMode
 * Namespace: Global
 * Signature: void ResetScreenMode(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ResetScreenMode(void)

{
  SetScreenMode(SCREENMODE_SIM);
  LastMode = SetScreenMode(SCREENMODE_SIM);
  return;
}
