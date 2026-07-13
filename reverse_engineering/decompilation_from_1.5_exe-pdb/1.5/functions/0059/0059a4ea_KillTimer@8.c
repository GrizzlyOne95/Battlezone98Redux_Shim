/*
 * Entry: 0059a4ea
 * Name: _KillTimer@8
 * Namespace: Global
 * Signature: BOOL _KillTimer@8(HWND hWnd, UINT_PTR uIDEvent)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _KillTimer_8(HWND hWnd,UINT_PTR uIDEvent)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a4ea. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = KillTimer(hWnd,uIDEvent);
  return BVar1;
}
