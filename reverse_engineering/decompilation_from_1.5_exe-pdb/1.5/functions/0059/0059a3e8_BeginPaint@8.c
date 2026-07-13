/*
 * Entry: 0059a3e8
 * Name: _BeginPaint@8
 * Namespace: Global
 * Signature: HDC _BeginPaint@8(HWND hWnd, LPPAINTSTRUCT lpPaint)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HDC _BeginPaint_8(HWND hWnd,LPPAINTSTRUCT lpPaint)

{
  HDC pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a3e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = BeginPaint(hWnd,lpPaint);
  return pHVar1;
}
