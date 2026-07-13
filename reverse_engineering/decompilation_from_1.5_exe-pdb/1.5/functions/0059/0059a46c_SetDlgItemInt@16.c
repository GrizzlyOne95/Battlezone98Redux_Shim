/*
 * Entry: 0059a46c
 * Name: _SetDlgItemInt@16
 * Namespace: Global
 * Signature: BOOL _SetDlgItemInt@16(HWND hDlg, int nIDDlgItem, UINT uValue, BOOL bSigned)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _SetDlgItemInt_16(HWND hDlg,int nIDDlgItem,UINT uValue,BOOL bSigned)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a46c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetDlgItemInt(hDlg,nIDDlgItem,uValue,bSigned);
  return BVar1;
}
