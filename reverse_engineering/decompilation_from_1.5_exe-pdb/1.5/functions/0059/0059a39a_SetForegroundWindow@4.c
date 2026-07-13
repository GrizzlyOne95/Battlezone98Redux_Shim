/*
 * Entry: 0059a39a
 * Name: _SetForegroundWindow@4
 * Namespace: Global
 * Signature: BOOL _SetForegroundWindow@4(HWND hWnd)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _SetForegroundWindow_4(HWND hWnd)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a39a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetForegroundWindow(hWnd);
  return BVar1;
}
