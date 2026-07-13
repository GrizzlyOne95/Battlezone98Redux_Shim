/*
 * Entry: 0059a48a
 * Name: _UpdateWindow@4
 * Namespace: Global
 * Signature: BOOL _UpdateWindow@4(HWND hWnd)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _UpdateWindow_4(HWND hWnd)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a48a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = UpdateWindow(hWnd);
  return BVar1;
}
