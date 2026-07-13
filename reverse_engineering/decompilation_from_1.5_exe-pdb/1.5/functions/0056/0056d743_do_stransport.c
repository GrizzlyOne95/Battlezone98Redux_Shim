/*
 * Entry: 0056d743
 * Name: do_stransport
 * Namespace: Global
 * Signature: int do_stransport(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_stransport(void)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x69,shell_hwnd,STransportDlgProc,0);
  return iVar1;
}
