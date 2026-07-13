/*
 * Entry: 0059a4de
 * Name: _GetWindowTextA@12
 * Namespace: Global
 * Signature: int _GetWindowTextA@12(HWND hWnd, LPSTR lpString, int nMaxCount)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int _GetWindowTextA_12(HWND hWnd,LPSTR lpString,int nMaxCount)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a4de. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetWindowTextA(hWnd,lpString,nMaxCount);
  return iVar1;
}
