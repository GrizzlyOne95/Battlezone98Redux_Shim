/*
 * Entry: 0059a44e
 * Name: _SetDlgItemTextA@12
 * Namespace: Global
 * Signature: BOOL _SetDlgItemTextA@12(HWND hDlg, int nIDDlgItem, LPCSTR lpString)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _SetDlgItemTextA_12(HWND hDlg,int nIDDlgItem,LPCSTR lpString)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a44e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetDlgItemTextA(hDlg,nIDDlgItem,lpString);
  return BVar1;
}
