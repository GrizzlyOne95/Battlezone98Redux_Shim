/*
 * Entry: 0059a45a
 * Name: _GetDlgItemTextA@16
 * Namespace: Global
 * Signature: UINT _GetDlgItemTextA@16(HWND hDlg, int nIDDlgItem, LPSTR lpString, int cchMax)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UINT _GetDlgItemTextA_16(HWND hDlg,int nIDDlgItem,LPSTR lpString,int cchMax)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a45a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = GetDlgItemTextA(hDlg,nIDDlgItem,lpString,cchMax);
  return UVar1;
}
