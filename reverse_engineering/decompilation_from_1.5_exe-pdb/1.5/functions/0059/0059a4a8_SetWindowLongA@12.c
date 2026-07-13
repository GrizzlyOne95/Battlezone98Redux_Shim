/*
 * Entry: 0059a4a8
 * Name: _SetWindowLongA@12
 * Namespace: Global
 * Signature: LONG _SetWindowLongA@12(HWND hWnd, int nIndex, LONG dwNewLong)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LONG _SetWindowLongA_12(HWND hWnd,int nIndex,LONG dwNewLong)

{
  LONG LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a4a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = SetWindowLongA(hWnd,nIndex,dwNewLong);
  return LVar1;
}
