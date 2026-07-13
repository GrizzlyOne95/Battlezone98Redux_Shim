/*
 * Entry: 005544e4
 * Name: do_game
 * Namespace: Global
 * Signature: int do_game(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_game(void)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x9a,shell_hwnd,GameDlgProc,0);
  return iVar1;
}
