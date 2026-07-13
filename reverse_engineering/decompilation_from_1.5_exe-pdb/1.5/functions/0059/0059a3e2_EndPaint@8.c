/*
 * Entry: 0059a3e2
 * Name: _EndPaint@8
 * Namespace: Global
 * Signature: BOOL _EndPaint@8(HWND hWnd, PAINTSTRUCT * lpPaint)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _EndPaint_8(HWND hWnd,PAINTSTRUCT *lpPaint)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a3e2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = EndPaint(hWnd,lpPaint);
  return BVar1;
}
