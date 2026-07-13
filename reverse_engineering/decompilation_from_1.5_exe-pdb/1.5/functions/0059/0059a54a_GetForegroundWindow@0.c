/*
 * Entry: 0059a54a
 * Name: _GetForegroundWindow@0
 * Namespace: Global
 * Signature: HWND _GetForegroundWindow@0(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HWND _GetForegroundWindow_0(void)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a54a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetForegroundWindow();
  return pHVar1;
}
