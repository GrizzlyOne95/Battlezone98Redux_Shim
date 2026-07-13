/*
 * Entry: 00581513
 * Name: do_trnmissions
 * Namespace: Global
 * Signature: int do_trnmissions(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_trnmissions(void)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x78,shell_hwnd,TrnMissionsDlgProc,0);
  return iVar1;
}
