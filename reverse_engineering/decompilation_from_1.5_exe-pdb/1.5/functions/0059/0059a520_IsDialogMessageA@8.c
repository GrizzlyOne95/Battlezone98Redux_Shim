/*
 * Entry: 0059a520
 * Name: _IsDialogMessageA@8
 * Namespace: Global
 * Signature: BOOL _IsDialogMessageA@8(HWND hDlg, LPMSG lpMsg)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _IsDialogMessageA_8(HWND hDlg,LPMSG lpMsg)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a520. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = IsDialogMessageA(hDlg,lpMsg);
  return BVar1;
}
