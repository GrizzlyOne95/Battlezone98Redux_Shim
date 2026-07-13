/*
 * Entry: 00581496
 * Name: do_old
 * Namespace: Global
 * Signature: int do_old(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_old(int param_1)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x108,shell_hwnd,OldDlgProc,param_1);
  return iVar1;
}
