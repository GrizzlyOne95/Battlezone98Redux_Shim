/*
 * Entry: 0059a448
 * Name: _CheckRadioButton@16
 * Namespace: Global
 * Signature: BOOL _CheckRadioButton@16(HWND hDlg, int nIDFirstButton, int nIDLastButton, int nIDCheckButton)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _CheckRadioButton_16(HWND hDlg,int nIDFirstButton,int nIDLastButton,int nIDCheckButton)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a448. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = CheckRadioButton(hDlg,nIDFirstButton,nIDLastButton,nIDCheckButton);
  return BVar1;
}
