/*
 * Entry: 00563039
 * Name: do_netgame
 * Namespace: Global
 * Signature: int do_netgame(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_netgame(void)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x7ed,shell_hwnd,NetGameDlgProc,0);
  return iVar1;
}
