/*
 * Entry: 0059a3b8
 * Name: _TranslateMessage@4
 * Namespace: Global
 * Signature: BOOL _TranslateMessage@4(MSG * lpMsg)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _TranslateMessage_4(MSG *lpMsg)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a3b8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = TranslateMessage(lpMsg);
  return BVar1;
}
