/*
 * Entry: 0059a47e
 * Name: _ReleaseDC@8
 * Namespace: Global
 * Signature: int _ReleaseDC@8(HWND hWnd, HDC hDC)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int _ReleaseDC_8(HWND hWnd,HDC hDC)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a47e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = ReleaseDC(hWnd,hDC);
  return iVar1;
}
