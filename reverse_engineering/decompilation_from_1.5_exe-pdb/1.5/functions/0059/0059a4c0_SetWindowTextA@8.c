/*
 * Entry: 0059a4c0
 * Name: _SetWindowTextA@8
 * Namespace: Global
 * Signature: BOOL _SetWindowTextA@8(HWND hWnd, LPCSTR lpString)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _SetWindowTextA_8(HWND hWnd,LPCSTR lpString)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a4c0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetWindowTextA(hWnd,lpString);
  return BVar1;
}
