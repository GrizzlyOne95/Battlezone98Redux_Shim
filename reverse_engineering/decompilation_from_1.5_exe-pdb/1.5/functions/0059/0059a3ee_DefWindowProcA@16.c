/*
 * Entry: 0059a3ee
 * Name: _DefWindowProcA@16
 * Namespace: Global
 * Signature: LRESULT _DefWindowProcA@16(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LRESULT _DefWindowProcA_16(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)

{
  LRESULT LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a3ee. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = DefWindowProcA(hWnd,Msg,wParam,lParam);
  return LVar1;
}
