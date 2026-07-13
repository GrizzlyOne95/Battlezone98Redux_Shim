/*
 * Entry: 0055763a
 * Name: do_name
 * Namespace: Global
 * Signature: int do_name(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_name(void)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x96,shell_hwnd,NameDlgProc,0);
  return iVar1;
}
