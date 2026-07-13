/*
 * Entry: 005814b9
 * Name: do_single
 * Namespace: Global
 * Signature: int do_single(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_single(void)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x73,shell_hwnd,SingleDlgProc,0);
  return iVar1;
}
