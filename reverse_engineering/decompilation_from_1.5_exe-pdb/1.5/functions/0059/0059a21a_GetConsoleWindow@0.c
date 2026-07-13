/*
 * Entry: 0059a21a
 * Name: _GetConsoleWindow@0
 * Namespace: Global
 * Signature: HWND _GetConsoleWindow@0(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HWND _GetConsoleWindow_0(void)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a21a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetConsoleWindow();
  return pHVar1;
}
