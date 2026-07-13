/*
 * Entry: 0059a4f0
 * Name: _SetTimer@16
 * Namespace: Global
 * Signature: UINT_PTR _SetTimer@16(HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UINT_PTR _SetTimer_16(HWND hWnd,UINT_PTR nIDEvent,UINT uElapse,TIMERPROC lpTimerFunc)

{
  UINT_PTR UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a4f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = SetTimer(hWnd,nIDEvent,uElapse,lpTimerFunc);
  return UVar1;
}
