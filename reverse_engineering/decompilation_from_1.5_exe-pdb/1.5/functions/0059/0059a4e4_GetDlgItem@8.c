/*
 * Entry: 0059a4e4
 * Name: _GetDlgItem@8
 * Namespace: Global
 * Signature: HWND _GetDlgItem@8(HWND hDlg, int nIDDlgItem)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HWND _GetDlgItem_8(HWND hDlg,int nIDDlgItem)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a4e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetDlgItem(hDlg,nIDDlgItem);
  return pHVar1;
}
