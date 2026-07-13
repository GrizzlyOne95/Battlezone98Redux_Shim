/*
 * Entry: 0059a4fc
 * Name: _SendDlgItemMessageA@20
 * Namespace: Global
 * Signature: LRESULT _SendDlgItemMessageA@20(HWND hDlg, int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LRESULT _SendDlgItemMessageA_20(HWND hDlg,int nIDDlgItem,UINT Msg,WPARAM wParam,LPARAM lParam)

{
  LRESULT LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a4fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = SendDlgItemMessageA(hDlg,nIDDlgItem,Msg,wParam,lParam);
  return LVar1;
}
