/*
 * Entry: 0059a3be
 * Name: _PeekMessageA@20
 * Namespace: Global
 * Signature: BOOL _PeekMessageA@20(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _PeekMessageA_20(LPMSG lpMsg,HWND hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a3be. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = PeekMessageA(lpMsg,hWnd,wMsgFilterMin,wMsgFilterMax,wRemoveMsg);
  return BVar1;
}
