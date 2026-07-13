/*
 * Entry: 0059a526
 * Name: _GetMessageA@16
 * Namespace: Global
 * Signature: BOOL _GetMessageA@16(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _GetMessageA_16(LPMSG lpMsg,HWND hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a526. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetMessageA(lpMsg,hWnd,wMsgFilterMin,wMsgFilterMax);
  return BVar1;
}
