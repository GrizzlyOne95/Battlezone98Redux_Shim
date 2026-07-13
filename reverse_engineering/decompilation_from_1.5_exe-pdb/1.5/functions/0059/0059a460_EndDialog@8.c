/*
 * Entry: 0059a460
 * Name: _EndDialog@8
 * Namespace: Global
 * Signature: BOOL _EndDialog@8(HWND hDlg, INT_PTR nResult)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _EndDialog_8(HWND hDlg,INT_PTR nResult)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a460. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = EndDialog(hDlg,nResult);
  return BVar1;
}
