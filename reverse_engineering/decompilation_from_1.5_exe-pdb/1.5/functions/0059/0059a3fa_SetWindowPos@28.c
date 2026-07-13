/*
 * Entry: 0059a3fa
 * Name: _SetWindowPos@28
 * Namespace: Global
 * Signature: BOOL _SetWindowPos@28(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _SetWindowPos_28(HWND hWnd,HWND hWndInsertAfter,int X,int Y,int cx,int cy,UINT uFlags)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a3fa. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetWindowPos(hWnd,hWndInsertAfter,X,Y,cx,cy,uFlags);
  return BVar1;
}
