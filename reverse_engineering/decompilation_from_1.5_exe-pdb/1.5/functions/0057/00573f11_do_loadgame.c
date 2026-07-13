/*
 * Entry: 00573f11
 * Name: do_loadgame
 * Namespace: Global
 * Signature: int do_loadgame(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_loadgame(int param_1)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x111,shell_hwnd,LoadDlgProc,param_1);
  return iVar1;
}
