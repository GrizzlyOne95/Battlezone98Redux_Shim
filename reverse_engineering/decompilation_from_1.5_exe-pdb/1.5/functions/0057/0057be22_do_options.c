/*
 * Entry: 0057be22
 * Name: do_options
 * Namespace: Global
 * Signature: void do_options(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl do_options(int param_1)

{
  Shell_DialogBoxParam(shell_hInstance,(char *)0x74,shell_hwnd,OptionsDlgProc,param_1);
  return;
}
