/*
 * Entry: 0059a472
 * Name: _GetDlgItemInt@16
 * Namespace: Global
 * Signature: UINT _GetDlgItemInt@16(HWND hDlg, int nIDDlgItem, BOOL * lpTranslated, BOOL bSigned)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UINT _GetDlgItemInt_16(HWND hDlg,int nIDDlgItem,BOOL *lpTranslated,BOOL bSigned)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a472. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = GetDlgItemInt(hDlg,nIDDlgItem,lpTranslated,bSigned);
  return UVar1;
}
