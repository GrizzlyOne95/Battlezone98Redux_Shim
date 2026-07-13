/*
 * Entry: 00579846
 * Name: do_play_options
 * Namespace: Global
 * Signature: void do_play_options(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl do_play_options(int param_1)

{
  Shell_DialogBoxParam(shell_hInstance,(char *)0x7d,shell_hwnd,PlayOptionsDlgProc,param_1);
  return;
}
