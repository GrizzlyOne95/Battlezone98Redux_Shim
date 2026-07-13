/*
 * Entry: 00571506
 * Name: do_card
 * Namespace: Global
 * Signature: int do_card(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_card(void)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x107,shell_hwnd,CardDlgProc,0);
  return iVar1;
}
