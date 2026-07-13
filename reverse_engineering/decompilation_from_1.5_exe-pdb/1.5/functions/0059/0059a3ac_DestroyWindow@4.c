/*
 * Entry: 0059a3ac
 * Name: _DestroyWindow@4
 * Namespace: Global
 * Signature: BOOL _DestroyWindow@4(HWND hWnd)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _DestroyWindow_4(HWND hWnd)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a3ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = DestroyWindow(hWnd);
  return BVar1;
}
