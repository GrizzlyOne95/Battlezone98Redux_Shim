/*
 * Entry: 0054f2e2
 * Name: SetScreenMode
 * Namespace: Global
 * Signature: SCREENMODE SetScreenMode(SCREENMODE param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SCREENMODE __cdecl SetScreenMode(SCREENMODE param_1)

{
  SCREENMODE SVar1;
  
  SVar1 = ScreenMode;
  ScreenMode = SCREENMODE_SIM;
  if (SVar1 != param_1) {
    ScreenMode = param_1;
  }
  return SVar1;
}
