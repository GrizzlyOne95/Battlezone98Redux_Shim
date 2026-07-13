/*
 * Entry: 0059a4ba
 * Name: _SendMessageA@16
 * Namespace: Global
 * Signature: LRESULT _SendMessageA@16(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LRESULT _SendMessageA_16(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)

{
  LRESULT LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a4ba. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = SendMessageA(hWnd,Msg,wParam,lParam);
  return LVar1;
}
