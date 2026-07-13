/*
 * Entry: 0059a4d8
 * Name: _GetWindow@8
 * Namespace: Global
 * Signature: HWND _GetWindow@8(HWND hWnd, UINT uCmd)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HWND _GetWindow_8(HWND hWnd,UINT uCmd)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a4d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetWindow(hWnd,uCmd);
  return pHVar1;
}
