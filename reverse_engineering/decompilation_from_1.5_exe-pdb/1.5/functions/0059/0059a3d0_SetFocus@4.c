/*
 * Entry: 0059a3d0
 * Name: _SetFocus@4
 * Namespace: Global
 * Signature: HWND _SetFocus@4(HWND hWnd)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HWND _SetFocus_4(HWND hWnd)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a3d0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = SetFocus(hWnd);
  return pHVar1;
}
