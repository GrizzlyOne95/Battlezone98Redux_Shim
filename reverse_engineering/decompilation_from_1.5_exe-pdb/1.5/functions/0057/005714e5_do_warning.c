/*
 * Entry: 005714e5
 * Name: do_warning
 * Namespace: Global
 * Signature: int do_warning(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_warning(void)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x122,shell_hwnd,WarningDlgProc,0);
  return iVar1;
}
