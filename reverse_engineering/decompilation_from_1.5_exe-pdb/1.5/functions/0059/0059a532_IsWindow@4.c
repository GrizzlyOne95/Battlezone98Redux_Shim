/*
 * Entry: 0059a532
 * Name: _IsWindow@4
 * Namespace: Global
 * Signature: BOOL _IsWindow@4(HWND hWnd)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _IsWindow_4(HWND hWnd)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a532. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = IsWindow(hWnd);
  return BVar1;
}
