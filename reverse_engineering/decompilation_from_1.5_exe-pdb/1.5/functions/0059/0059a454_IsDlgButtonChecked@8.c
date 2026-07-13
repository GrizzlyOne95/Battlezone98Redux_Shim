/*
 * Entry: 0059a454
 * Name: _IsDlgButtonChecked@8
 * Namespace: Global
 * Signature: UINT _IsDlgButtonChecked@8(HWND hDlg, int nIDButton)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UINT _IsDlgButtonChecked_8(HWND hDlg,int nIDButton)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a454. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = IsDlgButtonChecked(hDlg,nIDButton);
  return UVar1;
}
