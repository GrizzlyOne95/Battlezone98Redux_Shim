/*
 * Entry: 0059a394
 * Name: _GetSystemMenu@8
 * Namespace: Global
 * Signature: HMENU _GetSystemMenu@8(HWND hWnd, BOOL bRevert)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HMENU _GetSystemMenu_8(HWND hWnd,BOOL bRevert)

{
  HMENU pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a394. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetSystemMenu(hWnd,bRevert);
  return pHVar1;
}
