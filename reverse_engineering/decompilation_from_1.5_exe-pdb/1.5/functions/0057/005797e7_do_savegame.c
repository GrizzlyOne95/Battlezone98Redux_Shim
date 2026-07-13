/*
 * Entry: 005797e7
 * Name: do_savegame
 * Namespace: Global
 * Signature: int do_savegame(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_savegame(int param_1)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x111,shell_hwnd,SaveDlgProc,param_1);
  return iVar1;
}
