/*
 * Entry: 0059a4d2
 * Name: _MoveWindow@24
 * Namespace: Global
 * Signature: BOOL _MoveWindow@24(HWND hWnd, int X, int Y, int nWidth, int nHeight, BOOL bRepaint)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _MoveWindow_24(HWND hWnd,int X,int Y,int nWidth,int nHeight,BOOL bRepaint)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a4d2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = MoveWindow(hWnd,X,Y,nWidth,nHeight,bRepaint);
  return BVar1;
}
